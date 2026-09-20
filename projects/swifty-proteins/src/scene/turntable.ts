import * as THREE from 'three';
import { applyOrbit, type OrbitState } from './camera';

export const TURNTABLE_SIZE = 256;

export const TURNTABLE_FRAMES = 36;

export const TURNTABLE_DELAY_CS = 10;

export type TurntableJob = {
  target: THREE.WebGLRenderTarget;
  frames: Uint8Array[];
  index: number;
  userTheta: number;
  onProgress: (fraction: number) => void;
  resolve: (frames: Uint8Array[] | null) => void;
};

export function beginTurntable(
  orbit: OrbitState,
  onProgress: (fraction: number) => void,
  resolve: (frames: Uint8Array[] | null) => void,
): TurntableJob {
  return {
    target: new THREE.WebGLRenderTarget(TURNTABLE_SIZE, TURNTABLE_SIZE),
    frames: [],
    index: 0,
    userTheta: orbit.theta,
    onProgress,
    resolve,
  };
}

export function advanceTurntable(
  renderer: THREE.WebGLRenderer,
  scene: THREE.Scene,
  camera: THREE.PerspectiveCamera,
  orbit: OrbitState,
  job: TurntableJob,
): boolean {
  orbit.theta = job.userTheta + (2 * Math.PI * job.index) / TURNTABLE_FRAMES;
  applyOrbit(camera, orbit);

  const screenAspect = camera.aspect;
  camera.aspect = 1;
  camera.updateProjectionMatrix();

  renderer.setRenderTarget(job.target);
  renderer.render(scene, camera);
  const raw = new Uint8Array(TURNTABLE_SIZE * TURNTABLE_SIZE * 4);
  renderer.readRenderTargetPixels(job.target, 0, 0, TURNTABLE_SIZE, TURNTABLE_SIZE, raw);
  renderer.setRenderTarget(null);

  camera.aspect = screenAspect;
  camera.updateProjectionMatrix();
  orbit.theta = job.userTheta;

  job.frames.push(flipVertically(raw, TURNTABLE_SIZE));
  job.index += 1;
  job.onProgress(job.index / TURNTABLE_FRAMES);

  return job.index >= TURNTABLE_FRAMES;
}

export function endTurntable(job: TurntableJob): void {
  job.target.dispose();
}

function flipVertically(pixels: Uint8Array, size: number): Uint8Array {
  const flipped = new Uint8Array(pixels.length);
  const stride = size * 4;
  for (let row = 0; row < size; row += 1) {
    const from = (size - 1 - row) * stride;
    flipped.set(pixels.subarray(from, from + stride), row * stride);
  }
  return flipped;
}