import type { ExpoWebGLRenderingContext } from 'expo-gl';
import * as THREE from 'three';

export function createRenderer(gl: ExpoWebGLRenderingContext): THREE.WebGLRenderer {
  const { drawingBufferWidth: width, drawingBufferHeight: height } = gl;

  const canvas = {
    width,
    height,
    clientWidth: width,
    clientHeight: height,
    style: {},
    addEventListener() {},
    removeEventListener() {},
    getContext: () => gl,
  } as unknown as HTMLCanvasElement;

  const renderer = new THREE.WebGLRenderer({
    canvas,
    context: gl as unknown as WebGL2RenderingContext,
    antialias: true,
    preserveDrawingBuffer: true,
  });
  renderer.setSize(width, height, false);
  return renderer;
}