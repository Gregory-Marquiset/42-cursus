import * as THREE from 'three';

export type OrbitState = {
  theta: number;
  phi: number;
  distance: number;
  target: THREE.Vector3;
};

const MIN_PHI = 0.05;
const MAX_PHI = Math.PI - 0.05;

export const clamp = (value: number, low: number, high: number): number =>
  Math.min(high, Math.max(low, value));

export function framingDistance(boundingRadius: number, fieldOfViewDegrees: number): number {
  const halfAngle = (fieldOfViewDegrees * Math.PI) / 360;
  return (boundingRadius / Math.sin(halfAngle)) * 1.15;
}

export function initialOrbit(boundingRadius: number, fieldOfViewDegrees: number): OrbitState {
  return {
    theta: Math.PI / 4,
    phi: Math.PI / 2.4,
    distance: framingDistance(boundingRadius, fieldOfViewDegrees),
    target: new THREE.Vector3(),
  };
}

export function orbitBy(state: OrbitState, deltaX: number, deltaY: number): void {
  state.theta -= deltaX * 0.008;
  state.phi = clamp(state.phi - deltaY * 0.008, MIN_PHI, MAX_PHI);
}

export function zoomBy(state: OrbitState, scaleChange: number, boundingRadius: number): void {
  state.distance = clamp(state.distance / scaleChange, boundingRadius * 0.35, boundingRadius * 12);
}

export function panBy(
  state: OrbitState,
  camera: THREE.Camera,
  deltaX: number,
  deltaY: number,
): void {
  const speed = state.distance * 0.0022;
  const right = new THREE.Vector3().setFromMatrixColumn(camera.matrix, 0);
  const up = new THREE.Vector3().setFromMatrixColumn(camera.matrix, 1);
  state.target.addScaledVector(right, -deltaX * speed);
  state.target.addScaledVector(up, deltaY * speed);
}

export function applyOrbit(camera: THREE.Camera, state: OrbitState): void {
  const { theta, phi, distance, target } = state;
  camera.position.set(
    target.x + distance * Math.sin(phi) * Math.sin(theta),
    target.y + distance * Math.cos(phi),
    target.z + distance * Math.sin(phi) * Math.cos(theta),
  );
  camera.lookAt(target);
}