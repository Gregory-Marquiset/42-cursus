import { Asset } from 'expo-asset';
import { File } from 'expo-file-system';

const LIGANDS_FILE = require('../../assets/ligands.txt');

let cached: string[] | null = null;

export async function loadLigandIds(): Promise<string[]> {
  if (cached) return cached;

  const [asset] = await Asset.loadAsync(LIGANDS_FILE);
  if (!asset.localUri) await asset.downloadAsync();

  const text = await new File(asset.localUri ?? asset.uri).text();
  cached = text
    .split(/\r?\n/)
    .map((line) => line.trim().toUpperCase())
    .filter((line) => line.length > 0);

  return cached;
}

export function filterLigands(ligands: string[], query: string): string[] {
  const needle = query.trim().toUpperCase();
  if (!needle) return ligands;
  return ligands.filter((id) => id.includes(needle));
}