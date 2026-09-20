export type RenderMode = 'ballAndStick' | 'spaceFilling' | 'stick' | 'wireframe';

export type ModeSpec = {
  label: string;
  atomScale: number;
  bondRadius: number;
  lines: boolean;
};

export const MODES: Record<RenderMode, ModeSpec> = {
  ballAndStick: { label: 'Boules et bâtons', atomScale: 0.28, bondRadius: 0.1, lines: false },
  spaceFilling: { label: 'Compact', atomScale: 1, bondRadius: 0, lines: false },
  stick: { label: 'Bâtons', atomScale: 0.09, bondRadius: 0.09, lines: false },
  wireframe: { label: 'Fil de fer', atomScale: 0, bondRadius: 0, lines: true },
};

export const MODE_ORDER: RenderMode[] = ['ballAndStick', 'spaceFilling', 'stick', 'wireframe'];