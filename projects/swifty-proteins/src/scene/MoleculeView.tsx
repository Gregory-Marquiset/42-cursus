import { GLView, type ExpoWebGLRenderingContext } from 'expo-gl';
import {
  forwardRef,
  memo,
  useCallback,
  useEffect,
  useImperativeHandle,
  useMemo,
  useRef,
  useState,
} from 'react';
import { StyleSheet, View, type LayoutChangeEvent } from 'react-native';
import { Gesture, GestureDetector } from 'react-native-gesture-handler';
import type { SharedValue } from 'react-native-reanimated';
import * as THREE from 'three';
import { elementInfo } from '@/chemistry/elements';
import type { Molecule } from '@/ligands/types';
import { applyOrbit, initialOrbit, orbitBy, panBy, zoomBy, type OrbitState } from './camera';
import { buildMolecule, type MoleculeObject } from './molecule';
import type { RenderMode } from './modes';
import { createRenderer } from './renderer';
import {
  advanceTurntable,
  beginTurntable,
  endTurntable,
  type TurntableJob,
} from './turntable';

const FIELD_OF_VIEW = 45;

const TOUCH_RADIUS = 28;

const DEPTH_BIAS = 8;

export const LABEL_HIDDEN = -1000;

export type Selection = { kind: 'atom' | 'bond'; index: number } | null;

export type MoleculeViewHandle = {
  takeSnapshot: (format?: 'png' | 'jpeg') => Promise<string | null>;
  focusOn: (atomIndex: number) => void;
  resetCamera: () => void;
  recordTurntable: (onProgress: (fraction: number) => void) => Promise<Uint8Array[] | null>;
};

type MoleculeViewProps = {
  molecule: Molecule;
  mode: RenderMode;
  backgroundColor: string;
  selection: Selection;
  highlightedElement: string | null;
  measured: [number, number] | null;
  showLabels: boolean;
  labelFrame?: SharedValue<number[]>;
  onSelect: (selection: Selection) => void;
  onFocusAtom: (atomIndex: number) => void;
};

type World = {
  gl: ExpoWebGLRenderingContext;
  renderer: THREE.WebGLRenderer;
  scene: THREE.Scene;
  camera: THREE.PerspectiveCamera;
  orbit: OrbitState;
  object: MoleculeObject | null;
  halo: THREE.Mesh;
  ruler: THREE.Line;
  raycaster: THREE.Raycaster;
  viewport: { width: number; height: number };
  lights: { ambient: THREE.AmbientLight; key: THREE.DirectionalLight; rim: THREE.DirectionalLight };
  transition: CameraTransition | null;
  capture: TurntableJob | null;
};

type CameraTransition = {
  fromTarget: THREE.Vector3;
  toTarget: THREE.Vector3;
  fromDistance: number;
  toDistance: number;
  startedAt: number;
};

const FOCUS_DURATION_MS = 420;

const smoothStep = (t: number): number => t * t * (3 - 2 * t);

const MoleculeViewComponent = forwardRef<MoleculeViewHandle, MoleculeViewProps>(function MoleculeView(
  props,
  ref,
) {
  const world = useRef<World | null>(null);
  const layout = useRef({ width: 1, height: 1 });
  const frame = useRef<number | null>(null);
  const latest = useRef(props);
  latest.current = props;
  const captureRestore = useRef<{ halo: boolean; ruler: boolean } | null>(null);

  const [contextReady, setContextReady] = useState(false);

  const onLayout = useCallback((event: LayoutChangeEvent) => {
    const { width, height } = event.nativeEvent.layout;
    layout.current = { width, height };
  }, []);

  const onContextCreate = useCallback((gl: ExpoWebGLRenderingContext) => {
    const renderer = createRenderer(gl);
    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(
      FIELD_OF_VIEW,
      gl.drawingBufferWidth / gl.drawingBufferHeight,
      0.1,
      2000,
    );

    const ambient = new THREE.AmbientLight(0xffffff, 0.95);
    scene.add(ambient);
    const key = new THREE.DirectionalLight(0xffffff, 2.1);
    key.position.set(1, 1.4, 1.2);
    const rim = new THREE.DirectionalLight(0x9ec9ff, 0.95);
    rim.position.set(-1.2, -0.7, -1);
    camera.add(key, rim);
    scene.add(camera);

    const halo = new THREE.Mesh(
      new THREE.SphereGeometry(1, 24, 16),
      new THREE.MeshBasicMaterial({
        color: 0xffffff,
        side: THREE.BackSide,
        transparent: true,
        opacity: 0.45,
      }),
    );
    halo.visible = false;
    scene.add(halo);

    const ruler = new THREE.Line(
      new THREE.BufferGeometry().setFromPoints([new THREE.Vector3(), new THREE.Vector3()]),
      new THREE.LineDashedMaterial({ color: 0xffffff, dashSize: 0.18, gapSize: 0.12 }),
    );
    ruler.visible = false;
    scene.add(ruler);

    world.current = {
      gl,
      renderer,
      scene,
      camera,
      orbit: initialOrbit(1.5, FIELD_OF_VIEW),
      object: null,
      halo,
      ruler,
      raycaster: new THREE.Raycaster(),
      viewport: { width: gl.drawingBufferWidth, height: gl.drawingBufferHeight },
      lights: { ambient, key, rim },
      transition: null,
      capture: null,
    };

    const render = () => {
      frame.current = requestAnimationFrame(render);
      const current = world.current;
      if (!current) return;

      const { drawingBufferWidth, drawingBufferHeight } = current.gl;
      if (
        drawingBufferWidth !== current.viewport.width ||
        drawingBufferHeight !== current.viewport.height
      ) {
        current.viewport = { width: drawingBufferWidth, height: drawingBufferHeight };
        current.renderer.setSize(drawingBufferWidth, drawingBufferHeight, false);
        current.camera.aspect = drawingBufferWidth / drawingBufferHeight;
        current.camera.updateProjectionMatrix();
      }

      const move = current.transition;
      if (move) {
        const elapsed = (Date.now() - move.startedAt) / FOCUS_DURATION_MS;
        const progress = smoothStep(Math.min(1, elapsed));
        current.orbit.target.lerpVectors(move.fromTarget, move.toTarget, progress);
        current.orbit.distance =
          move.fromDistance + (move.toDistance - move.fromDistance) * progress;
        if (elapsed >= 1) current.transition = null;
      }

      applyOrbit(current.camera, current.orbit);
      current.renderer.render(current.scene, current.camera);
      current.gl.endFrameEXP();

      const { showLabels, labelFrame } = latest.current;
      if (showLabels && labelFrame) projectLabels(current, labelFrame, layout.current);

      const job = current.capture;
      if (job) {
        const finished = advanceTurntable(
          current.renderer,
          current.scene,
          current.camera,
          current.orbit,
          job,
        );
        if (finished) {
          current.capture = null;
          endTurntable(job);
          const restore = captureRestore.current;
          if (restore) {
            current.halo.visible = restore.halo;
            current.ruler.visible = restore.ruler;
            captureRestore.current = null;
          }
          job.resolve(job.frames);
        }
      }
    };
    render();

    setContextReady(true);
  }, []);

  useEffect(
    () => () => {
      if (frame.current !== null) cancelAnimationFrame(frame.current);
      world.current?.object?.dispose();
      world.current = null;
    },
    [],
  );

  useEffect(() => {
    const current = world.current;
    if (!current) return;

    const keepCamera = current.object !== null;
    current.object?.dispose();
    current.scene.remove(...current.scene.children.filter((child) => child.userData.isMolecule));

    const object = buildMolecule(props.molecule, props.mode);
    object.group.userData.isMolecule = true;
    current.object = object;
    current.scene.add(object.group);

    if (!keepCamera) current.orbit = initialOrbit(object.boundingRadius, FIELD_OF_VIEW);
  }, [contextReady, props.molecule, props.mode]);

  useEffect(() => {
    const current = world.current;
    if (!current?.object) return;

    const { selection, highlightedElement, molecule } = props;
    const object = current.object;

    for (const [element, material] of object.materialsByElement) {
      material.emissive.setHex(element === highlightedElement ? 0x333333 : 0x000000);
    }

    if (selection?.kind === 'atom' && object.atomMeshes[selection.index]) {
      const mesh = object.atomMeshes[selection.index];
      const element = molecule.atoms[selection.index].element;
      current.halo.position.copy(mesh.position);
      current.halo.scale.setScalar(Math.max(mesh.scale.x * 1.35, 0.4));
      (current.halo.material as THREE.MeshBasicMaterial).color.setHex(elementInfo(element).color);
      current.halo.visible = true;
    } else {
      current.halo.visible = false;
    }
  }, [contextReady, props.selection, props.highlightedElement, props.molecule, props.mode]);

  useEffect(() => {
    const current = world.current;
    if (!current?.object) return;

    const { measured } = props;
    if (!measured) {
      current.ruler.visible = false;
      return;
    }
    const [from, to] = measured;
    const points = [current.object.positions[from], current.object.positions[to]];
    if (!points[0] || !points[1]) return;

    current.ruler.geometry.dispose();
    current.ruler.geometry = new THREE.BufferGeometry().setFromPoints(points);
    current.ruler.computeLineDistances();
    current.ruler.visible = true;
  }, [contextReady, props.measured, props.molecule, props.mode]);

  useEffect(() => {
    const current = world.current;
    if (!current) return;

    const background = new THREE.Color(props.backgroundColor);
    current.scene.background = background;

    const { l: lightness } = background.getHSL({ h: 0, s: 0, l: 0 });
    const dark = lightness < 0.5;
    current.lights.ambient.intensity = dark ? 1.15 : 0.7;
    current.lights.key.intensity = dark ? 2.0 : 2.7;
    current.lights.rim.intensity = dark ? 1.2 : 0.7;
  }, [contextReady, props.backgroundColor]);

  useImperativeHandle(
    ref,
    () => ({
      takeSnapshot: async (format = 'png') => {
        const current = world.current;
        if (!current) return null;
        const snapshot = await GLView.takeSnapshotAsync(current.gl, { format });
        return typeof snapshot.uri === 'string' ? snapshot.uri : snapshot.localUri;
      },
      recordTurntable: (onProgress) =>
        new Promise<Uint8Array[] | null>((resolve) => {
          const current = world.current;
          if (!current?.object || current.capture) {
            resolve(null);
            return;
          }
          captureRestore.current = { halo: current.halo.visible, ruler: current.ruler.visible };
          current.halo.visible = false;
          current.ruler.visible = false;
          current.capture = beginTurntable(current.orbit, onProgress, resolve);
        }),
      focusOn: (atomIndex) => {
        const current = world.current;
        const position = current?.object?.positions[atomIndex];
        if (!current || !position) return;
        current.transition = {
          fromTarget: current.orbit.target.clone(),
          toTarget: position.clone(),
          fromDistance: current.orbit.distance,
          toDistance: Math.max(current.orbit.distance * 0.6, 2.2),
          startedAt: Date.now(),
        };
      },
      resetCamera: () => {
        const current = world.current;
        if (!current?.object) return;
        const initial = initialOrbit(current.object.boundingRadius, FIELD_OF_VIEW);
        current.transition = {
          fromTarget: current.orbit.target.clone(),
          toTarget: initial.target.clone(),
          fromDistance: current.orbit.distance,
          toDistance: initial.distance,
          startedAt: Date.now(),
        };
      },
    }),
    [],
  );

  const pickAt = useCallback((x: number, y: number, doubleTap: boolean) => {
    const current = world.current;
    if (!current?.object) return;

    const { width, height } = layout.current;

    const atom = nearestAtom(current, x, y, { width, height });
    if (atom !== null) {
      if (doubleTap) latest.current.onFocusAtom(atom);
      else latest.current.onSelect({ kind: 'atom', index: atom });
      return;
    }
    if (doubleTap) return;

    const pointer = new THREE.Vector2((x / width) * 2 - 1, -(y / height) * 2 + 1);
    current.raycaster.setFromCamera(pointer, current.camera);
    const bondHit = current.raycaster.intersectObjects(current.object.bondMeshes, false)[0];
    latest.current.onSelect(
      bondHit ? { kind: 'bond', index: bondHit.object.userData.bondIndex as number } : null,
    );
  }, []);

  const gesture = useMemo(
    () =>
      Gesture.Simultaneous(
        Gesture.Exclusive(
          Gesture.Tap()
            .numberOfTaps(2)
            .runOnJS(true)
            .onEnd((event) => pickAt(event.x, event.y, true)),
          Gesture.Tap()
            .runOnJS(true)
            .onEnd((event) => pickAt(event.x, event.y, false)),
        ),
        Gesture.Race(
          Gesture.Pan()
            .maxPointers(1)
            .runOnJS(true)
            .onChange((event) => {
              if (world.current) orbitBy(world.current.orbit, event.changeX, event.changeY);
            }),
          Gesture.Pan()
            .minPointers(2)
            .runOnJS(true)
            .onChange((event) => {
              const current = world.current;
              if (current) panBy(current.orbit, current.camera, event.changeX, event.changeY);
            }),
        ),
        Gesture.Pinch()
          .runOnJS(true)
          .onChange((event) => {
            const current = world.current;
            if (current?.object) {
              zoomBy(current.orbit, event.scaleChange, current.object.boundingRadius);
            }
          }),
      ),
    [pickAt],
  );

  return (
    <GestureDetector gesture={gesture}>
      <View style={StyleSheet.absoluteFill} onLayout={onLayout} collapsable={false}>
        <GLView style={StyleSheet.absoluteFill} onContextCreate={onContextCreate} />
      </View>
    </GestureDetector>
  );
});

export const MoleculeView = memo(MoleculeViewComponent);

function nearestAtom(
  world: World,
  x: number,
  y: number,
  size: { width: number; height: number },
): number | null {
  const object = world.object;
  if (!object) return null;

  const projected = new THREE.Vector3();
  let best: number | null = null;
  let bestScore = Number.POSITIVE_INFINITY;

  object.positions.forEach((position, index) => {
    projected.copy(position).project(world.camera);
    if (projected.z < -1 || projected.z > 1) return;

    const screenX = ((projected.x + 1) / 2) * size.width;
    const screenY = ((1 - projected.y) / 2) * size.height;
    const distance = Math.hypot(screenX - x, screenY - y);
    if (distance > TOUCH_RADIUS) return;

    const score = distance + projected.z * DEPTH_BIAS;
    if (score < bestScore) {
      bestScore = score;
      best = index;
    }
  });

  return best;
}

function projectLabels(
  world: World,
  frame: SharedValue<number[]>,
  size: { width: number; height: number },
): void {
  const object = world.object;
  if (!object) return;

  const projected = new THREE.Vector3();
  const next = new Array<number>(object.positions.length * 2);

  object.positions.forEach((position, index) => {
    projected.copy(position).project(world.camera);
    const visible = projected.z >= -1 && projected.z <= 1;
    next[index * 2] = visible ? ((projected.x + 1) / 2) * size.width : LABEL_HIDDEN;
    next[index * 2 + 1] = visible ? ((1 - projected.y) / 2) * size.height : LABEL_HIDDEN;
  });

  frame.value = next;
}