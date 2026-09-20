export type ElementInfo = {
  color: number;
  radius: number;
};

export const UNKNOWN_ELEMENT: ElementInfo = { color: 0xff1493, radius: 1.6 };

const ELEMENTS: Record<string, ElementInfo> = {
  H: { color: 0xffffff, radius: 1.2 },
  He: { color: 0xd9ffff, radius: 1.4 },
  Li: { color: 0xcc80ff, radius: 1.82 },
  Be: { color: 0xc2ff00, radius: 1.53 },
  B: { color: 0xffb5b5, radius: 1.92 },
  C: { color: 0x909090, radius: 1.7 },
  N: { color: 0x3050f8, radius: 1.55 },
  O: { color: 0xff0d0d, radius: 1.52 },
  F: { color: 0x90e050, radius: 1.47 },
  Ne: { color: 0xb3e3f5, radius: 1.54 },
  Na: { color: 0xab5cf2, radius: 2.27 },
  Mg: { color: 0x8aff00, radius: 1.73 },
  Al: { color: 0xbfa6a6, radius: 1.84 },
  Si: { color: 0xf0c8a0, radius: 2.1 },
  P: { color: 0xff8000, radius: 1.8 },
  S: { color: 0xffff30, radius: 1.8 },
  Cl: { color: 0x1ff01f, radius: 1.75 },
  Ar: { color: 0x80d1e3, radius: 1.88 },
  K: { color: 0x8f40d4, radius: 2.75 },
  Ca: { color: 0x3dff00, radius: 2.31 },
  Sc: { color: 0xe6e6e6, radius: 2.11 },
  Ti: { color: 0xbfc2c7, radius: 2.0 },
  V: { color: 0xa6a6ab, radius: 2.0 },
  Cr: { color: 0x8a99c7, radius: 2.0 },
  Mn: { color: 0x9c7ac7, radius: 2.0 },
  Fe: { color: 0xe06633, radius: 2.0 },
  Co: { color: 0xf090a0, radius: 2.0 },
  Ni: { color: 0x50d050, radius: 1.63 },
  Cu: { color: 0xc88033, radius: 1.4 },
  Zn: { color: 0x7d80b0, radius: 1.39 },
  Ga: { color: 0xc28f8f, radius: 1.87 },
  Ge: { color: 0x668f8f, radius: 2.11 },
  As: { color: 0xbd80e3, radius: 1.85 },
  Se: { color: 0xffa100, radius: 1.9 },
  Br: { color: 0xa62929, radius: 1.85 },
  Kr: { color: 0x5cb8d1, radius: 2.02 },
  Rb: { color: 0x702eb0, radius: 3.03 },
  Sr: { color: 0x00ff00, radius: 2.49 },
  Y: { color: 0x94ffff, radius: 2.27 },
  Zr: { color: 0x94e0e0, radius: 2.16 },
  Nb: { color: 0x73c2c9, radius: 2.08 },
  Mo: { color: 0x54b5b5, radius: 2.09 },
  Tc: { color: 0x3b9e9e, radius: 2.09 },
  Ru: { color: 0x248f8f, radius: 2.07 },
  Rh: { color: 0x0a7d8c, radius: 1.95 },
  Pd: { color: 0x006985, radius: 1.63 },
  Ag: { color: 0xc0c0c0, radius: 1.72 },
  Cd: { color: 0xffd98f, radius: 1.58 },
  In: { color: 0xa67573, radius: 1.93 },
  Sn: { color: 0x668080, radius: 2.17 },
  Sb: { color: 0x9e63b5, radius: 2.06 },
  Te: { color: 0xd47a00, radius: 2.06 },
  I: { color: 0x940094, radius: 1.98 },
  Xe: { color: 0x429eb0, radius: 2.16 },
  Cs: { color: 0x57178f, radius: 3.43 },
  Ba: { color: 0x00c900, radius: 2.68 },
  La: { color: 0x70d4ff, radius: 2.43 },
  Ce: { color: 0xffffc7, radius: 2.42 },
  Eu: { color: 0x61ffc7, radius: 2.35 },
  Gd: { color: 0x45ffc7, radius: 2.34 },
  Tb: { color: 0x30ffc7, radius: 2.33 },
  Yb: { color: 0x00bf38, radius: 2.26 },
  Hf: { color: 0x4dc2ff, radius: 2.16 },
  Ta: { color: 0x4da6ff, radius: 2.09 },
  W: { color: 0x2194d6, radius: 2.09 },
  Re: { color: 0x267dab, radius: 2.05 },
  Os: { color: 0x266696, radius: 2.03 },
  Ir: { color: 0x175487, radius: 2.03 },
  Pt: { color: 0xd0d0e0, radius: 1.75 },
  Au: { color: 0xffd123, radius: 1.66 },
  Hg: { color: 0xb8b8d0, radius: 1.55 },
  Tl: { color: 0xa6544d, radius: 1.96 },
  Pb: { color: 0x575961, radius: 2.02 },
  Bi: { color: 0x9e4fb5, radius: 2.07 },
  U: { color: 0x008fff, radius: 1.86 },
};

export function elementInfo(symbol: string): ElementInfo {
  return ELEMENTS[symbol] ?? UNKNOWN_ELEMENT;
}

const NAMES: Record<string, string> = {
  H: 'Hydrogène', C: 'Carbone', N: 'Azote', O: 'Oxygène', F: 'Fluor',
  Na: 'Sodium', Mg: 'Magnésium', P: 'Phosphore', S: 'Soufre', Cl: 'Chlore',
  K: 'Potassium', Ca: 'Calcium', Mn: 'Manganèse', Fe: 'Fer', Co: 'Cobalt',
  Ni: 'Nickel', Cu: 'Cuivre', Zn: 'Zinc', Se: 'Sélénium', Br: 'Brome',
  Mo: 'Molybdène', I: 'Iode', Pt: 'Platine', Au: 'Or', Hg: 'Mercure',
  Pb: 'Plomb', Cd: 'Cadmium', Ag: 'Argent', Li: 'Lithium', B: 'Bore',
  Al: 'Aluminium', Si: 'Silicium', Xe: 'Xénon', Ba: 'Baryum', Sr: 'Strontium',
  Cs: 'Césium', Rb: 'Rubidium', W: 'Tungstène', U: 'Uranium', Ru: 'Ruthénium',
};

export function elementName(symbol: string): string | null {
  return NAMES[symbol] ?? null;
}