export type Atom = {
  id: string;
  element: string;
  position: [number, number, number];
  charge: number;
  aromatic: boolean;
};

export type BondOrder = 1 | 2 | 3;

export type Bond = {
  from: number;
  to: number;
  order: BondOrder;
  aromatic: boolean;
};

export type Molecule = {
  id: string;
  name: string;
  formula: string;
  weight: number | null;
  atoms: Atom[];
  bonds: Bond[];
};