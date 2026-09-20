import type { Atom, Bond, BondOrder, Molecule } from './types';

export class CifParseError extends Error {}

const MISSING = new Set(['?', '.']);

const ATOM_CATEGORY = '_chem_comp_atom';
const BOND_CATEGORY = '_chem_comp_bond';

type Loop = { columns: string[]; rows: string[][] };
type CifDocument = { values: Map<string, string>; loops: Map<string, Loop> };

function tokenizeLine(line: string): string[] {
  const tokens: string[] = [];
  let cursor = 0;

  while (cursor < line.length) {
    const character = line[cursor];

    if (character === ' ' || character === '\t') {
      cursor += 1;
      continue;
    }
    if (character === '#') break;

    if (character === '"' || character === "'") {
      let end = cursor + 1;
      while (end < line.length) {
        const closes = line[end] === character && (end + 1 >= line.length || /\s/.test(line[end + 1]));
        if (closes) break;
        end += 1;
      }
      tokens.push(line.slice(cursor + 1, end));
      cursor = end + 1;
      continue;
    }

    let end = cursor;
    while (end < line.length && !/\s/.test(line[end])) end += 1;
    tokens.push(line.slice(cursor, end));
    cursor = end;
  }

  return tokens;
}

const categoryOf = (item: string): string => item.split('.')[0];

function parseCifDocument(text: string): CifDocument {
  const lines = text.split(/\r?\n/);
  const values = new Map<string, string>();
  const loops = new Map<string, Loop>();
  let index = 0;

  const readTextBlock = (): string => {
    const parts = [lines[index].trim().slice(1)];
    index += 1;
    while (index < lines.length && lines[index].trim() !== ';') {
      parts.push(lines[index]);
      index += 1;
    }
    index += 1;
    return parts.join(' ').trim();
  };

  while (index < lines.length) {
    const raw = lines[index];
    const line = raw.trim();

    if (line === '' || line.startsWith('#') || line.startsWith('data_')) {
      index += 1;
      continue;
    }

    if (line === 'loop_') {
      index += 1;
      const columns: string[] = [];
      while (index < lines.length && lines[index].trim().startsWith('_')) {
        columns.push(lines[index].trim().split(/\s+/)[0]);
        index += 1;
      }

      const rows: string[][] = [];
      const pending: string[] = [];
      while (index < lines.length) {
        const current = lines[index].trim();
        if (current === 'loop_' || current.startsWith('_') || current.startsWith('data_')) break;
        if (current === '' || current.startsWith('#')) {
          index += 1;
          continue;
        }
        if (current.startsWith(';')) {
          pending.push(readTextBlock());
        } else {
          pending.push(...tokenizeLine(lines[index]));
          index += 1;
        }
        while (columns.length > 0 && pending.length >= columns.length) {
          rows.push(pending.splice(0, columns.length));
        }
      }

      if (columns.length > 0) loops.set(categoryOf(columns[0]), { columns, rows });
      continue;
    }

    if (line.startsWith('_')) {
      const tokens = tokenizeLine(raw);
      const key = tokens[0];
      if (tokens.length > 1) {
        values.set(key, tokens.slice(1).join(' '));
        index += 1;
        continue;
      }
      index += 1;
      if (index >= lines.length) continue;
      if (lines[index].trim().startsWith(';')) {
        values.set(key, readTextBlock());
      } else {
        values.set(key, tokenizeLine(lines[index])[0] ?? '');
        index += 1;
      }
      continue;
    }

    index += 1;
  }

  return { values, loops };
}

function toNumber(value: string | undefined): number | null {
  if (!value || MISSING.has(value)) return null;
  const parsed = Number(value);
  return Number.isFinite(parsed) ? parsed : null;
}

export function normalizeElement(symbol: string): string {
  const value = symbol.trim();
  if (!value || MISSING.has(value)) return 'X';
  return value[0].toUpperCase() + value.slice(1).toLowerCase();
}

function columnReader(loop: Loop, category: string) {
  const positions = new Map(loop.columns.map((name, position) => [name, position]));
  return (row: string[], item: string): string => {
    const position = positions.get(`${category}.${item}`);
    return position === undefined ? '' : (row[position] ?? '');
  };
}

function readPosition(get: (item: string) => string): [number, number, number] {
  const ideal = ['pdbx_model_Cartn_x_ideal', 'pdbx_model_Cartn_y_ideal', 'pdbx_model_Cartn_z_ideal'];
  const model = ['model_Cartn_x', 'model_Cartn_y', 'model_Cartn_z'];

  for (const keys of [ideal, model]) {
    const coordinates = keys.map((key) => toNumber(get(key)));
    if (coordinates.every((value) => value !== null)) return coordinates as [number, number, number];
  }
  return [0, 0, 0];
}

function toAtom(get: (item: string) => string): Atom {
  return {
    id: get('atom_id'),
    element: normalizeElement(get('type_symbol')),
    position: readPosition(get),
    charge: toNumber(get('charge')) ?? 0,
    aromatic: get('pdbx_aromatic_flag') === 'Y',
  };
}

function readRows(document: CifDocument, category: string): ((item: string) => string)[] {
  const loop = document.loops.get(category);
  if (loop) {
    const read = columnReader(loop, category);
    return loop.rows.map((row) => (item: string) => read(row, item));
  }

  const prefix = `${category}.`;
  const hasSingleRow = [...document.values.keys()].some((key) => key.startsWith(prefix));
  return hasSingleRow ? [(item: string) => document.values.get(prefix + item) ?? ''] : [];
}

function readAtoms(document: CifDocument): Atom[] {
  return readRows(document, ATOM_CATEGORY).map(toAtom);
}

const BOND_ORDERS: Record<string, BondOrder> = { SING: 1, DOUB: 2, TRIP: 3, QUAD: 3, AROM: 1 };

function readBonds(document: CifDocument, atoms: Atom[]): Bond[] {
  const rows = readRows(document, BOND_CATEGORY);
  if (rows.length === 0) return [];

  const indexById = new Map(atoms.map((atom, index) => [atom.id, index]));
  const bonds: Bond[] = [];

  for (const read of rows) {
    const from = indexById.get(read('atom_id_1'));
    const to = indexById.get(read('atom_id_2'));
    if (from === undefined || to === undefined || from === to) continue;
    bonds.push({
      from,
      to,
      order: BOND_ORDERS[read('value_order').toUpperCase()] ?? 1,
      aromatic: read('pdbx_aromatic_flag') === 'Y',
    });
  }

  return bonds;
}

function buildFormula(atoms: Atom[]): string {
  const counts = new Map<string, number>();
  for (const atom of atoms) counts.set(atom.element, (counts.get(atom.element) ?? 0) + 1);

  const symbols = [...counts.keys()].sort();
  const ordered = counts.has('C')
    ? ['C', ...(counts.has('H') ? ['H'] : []), ...symbols.filter((s) => s !== 'C' && s !== 'H')]
    : symbols;

  return ordered.map((symbol) => (counts.get(symbol)! > 1 ? `${symbol}${counts.get(symbol)}` : symbol)).join('');
}

export function parseLigandCif(text: string, fallbackId: string): Molecule {
  if (!text.includes('_chem_comp')) {
    throw new CifParseError("Ce fichier ne décrit pas un ligand (bloc « _chem_comp » absent).");
  }

  const document = parseCifDocument(text);
  const atoms = readAtoms(document);
  if (atoms.length === 0) {
    throw new CifParseError("Aucun atome n'a pu être lu dans ce fichier.");
  }

  const declaredFormula = document.values.get('_chem_comp.formula');
  return {
    id: document.values.get('_chem_comp.id') ?? fallbackId,
    name: document.values.get('_chem_comp.name') ?? fallbackId,
    formula: declaredFormula && !MISSING.has(declaredFormula) ? declaredFormula : buildFormula(atoms),
    weight: toNumber(document.values.get('_chem_comp.formula_weight')),
    atoms,
    bonds: readBonds(document, atoms),
  };
}