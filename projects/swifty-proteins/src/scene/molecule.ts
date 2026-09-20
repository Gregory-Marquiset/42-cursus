import * as THREE from 'three';
import { elementInfo } from '@/chemistry/elements';
import type { Molecule } from '@/ligands/types';
import { MODES, type RenderMode } from './modes';

export type MoleculeObject = {
  group: THREE.Group;
  atomMeshes: THREE.Mesh[];
  bondMeshes: THREE.Mesh[];
  materialsByElement: Map<string, THREE.MeshStandardMaterial>;
  boundingRadius: number;
  positions: THREE.Vector3[];
  dispose: () => void;
};

const UP = new THREE.Vector3(0, 1, 0);

function sphereDetail(atomCount: number): [number, number] {
  if (atomCount <= 80) return [24, 16];
  if (atomCount <= 300) return [16, 12];
  return [10, 8];
}

function perpendicularTo(direction: THREE.Vector3): THREE.Vector3 {
  const reference = Math.abs(direction.y) < 0.9 ? UP : new THREE.Vector3(1, 0, 0);
  return new THREE.Vector3().crossVectors(direction, reference).normalize();
}

function stretchBetween(mesh: THREE.Mesh, start: THREE.Vector3, end: THREE.Vector3, thickness: number) {
  const direction = new THREE.Vector3().subVectors(end, start);
  const length = direction.length();
  mesh.position.copy(start).addScaledVector(direction, 0.5);
  mesh.quaternion.setFromUnitVectors(UP, direction.clone().normalize());
  mesh.scale.set(thickness, length, thickness);
}

export function buildMolecule(molecule: Molecule, mode: RenderMode): MoleculeObject {
  const spec = MODES[mode];
  const group = new THREE.Group();
  const atomMeshes: THREE.Mesh[] = [];
  const bondMeshes: THREE.Mesh[] = [];
  const materialsByElement = new Map<string, THREE.MeshStandardMaterial>();
  const disposables: { dispose: () => void }[] = [];

  const centroid = new THREE.Vector3();
  for (const atom of molecule.atoms) centroid.add(new THREE.Vector3(...atom.position));
  if (molecule.atoms.length > 0) centroid.divideScalar(molecule.atoms.length);

  const positions = molecule.atoms.map((atom) => new THREE.Vector3(...atom.position).sub(centroid));

  const materialFor = (element: string): THREE.MeshStandardMaterial => {
    const existing = materialsByElement.get(element);
    if (existing) return existing;
    const material = new THREE.MeshStandardMaterial({
      color: elementInfo(element).color,
      roughness: 0.34,
      metalness: 0.06,
    });
    materialsByElement.set(element, material);
    disposables.push(material);
    return material;
  };

  const pickOnly = spec.atomScale === 0;
  const [widthSegments, heightSegments] = sphereDetail(molecule.atoms.length);
  const sphere = new THREE.SphereGeometry(1, pickOnly ? 8 : widthSegments, pickOnly ? 6 : heightSegments);
  disposables.push(sphere);

  let pickMaterial: THREE.MeshBasicMaterial | null = null;
  if (pickOnly) {
    pickMaterial = new THREE.MeshBasicMaterial({ transparent: true, opacity: 0, depthWrite: false });
    disposables.push(pickMaterial);
  }

  molecule.atoms.forEach((atom, index) => {
    const mesh = new THREE.Mesh(sphere, pickMaterial ?? materialFor(atom.element));
    mesh.position.copy(positions[index]);
    mesh.scale.setScalar(pickOnly ? 0.28 : elementInfo(atom.element).radius * spec.atomScale);
    mesh.renderOrder = pickOnly ? -1 : 0;
    mesh.userData.atomIndex = index;
    atomMeshes.push(mesh);
    group.add(mesh);
  });

  if (spec.lines) {
    const vertices: number[] = [];
    const colors: number[] = [];
    const tint = new THREE.Color();

    molecule.bonds.forEach((bond) => {
      const start = positions[bond.from];
      const end = positions[bond.to];
      const middle = new THREE.Vector3().addVectors(start, end).multiplyScalar(0.5);

      for (const [a, b, element] of [
        [start, middle, molecule.atoms[bond.from].element],
        [middle, end, molecule.atoms[bond.to].element],
      ] as const) {
        vertices.push(a.x, a.y, a.z, b.x, b.y, b.z);
        tint.setHex(elementInfo(element).color);
        colors.push(tint.r, tint.g, tint.b, tint.r, tint.g, tint.b);
      }
    });

    if (vertices.length > 0) {
      const geometry = new THREE.BufferGeometry();
      geometry.setAttribute('position', new THREE.Float32BufferAttribute(vertices, 3));
      geometry.setAttribute('color', new THREE.Float32BufferAttribute(colors, 3));
      const material = new THREE.LineBasicMaterial({ vertexColors: true });
      disposables.push(geometry, material);
      group.add(new THREE.LineSegments(geometry, material));
    }
  } else if (spec.bondRadius > 0) {
    const cylinder = new THREE.CylinderGeometry(1, 1, 1, 14, 1, true);
    disposables.push(cylinder);

    molecule.bonds.forEach((bond, bondIndex) => {
      const start = positions[bond.from];
      const end = positions[bond.to];
      const middle = new THREE.Vector3().addVectors(start, end).multiplyScalar(0.5);

      const strands = bond.order;
      const offsetAxis = perpendicularTo(new THREE.Vector3().subVectors(end, start).normalize());
      const thickness = spec.bondRadius * (strands === 1 ? 1 : 0.55);
      const spacing = spec.bondRadius * 1.5;

      for (let strand = 0; strand < strands; strand += 1) {
        const shift = offsetAxis
          .clone()
          .multiplyScalar((strand - (strands - 1) / 2) * spacing);

        for (const [from, to, element] of [
          [start, middle, molecule.atoms[bond.from].element],
          [middle, end, molecule.atoms[bond.to].element],
        ] as const) {
          const mesh = new THREE.Mesh(cylinder, materialFor(element));
          stretchBetween(mesh, from.clone().add(shift), to.clone().add(shift), thickness);
          mesh.userData.bondIndex = bondIndex;
          bondMeshes.push(mesh);
          group.add(mesh);
        }
      }
    });
  }

  let boundingRadius = 0;
  molecule.atoms.forEach((atom, index) => {
    const reach = positions[index].length() + elementInfo(atom.element).radius * Math.max(spec.atomScale, 0.3);
    boundingRadius = Math.max(boundingRadius, reach);
  });
  boundingRadius = Math.max(boundingRadius, 1.5);

  return {
    group,
    atomMeshes,
    bondMeshes,
    materialsByElement,
    boundingRadius,
    positions,
    dispose: () => {
      for (const item of disposables) item.dispose();
      group.clear();
    },
  };
}