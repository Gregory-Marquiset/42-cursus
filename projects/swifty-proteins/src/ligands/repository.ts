import { Directory, File, Paths } from 'expo-file-system';
import { CifParseError, parseLigandCif } from './parser';
import type { Molecule } from './types';

const BASE_URL = 'https://files.rcsb.org/ligands/view';
const CACHE_DIRECTORY = 'ligands';
const TIMEOUT_MS = 15000;

const MAX_BYTES = 2 * 1024 * 1024;

export type LoadFailure =
  | 'offline'
  | 'not-found'
  | 'timeout'
  | 'server'
  | 'parse';

export class LigandLoadError extends Error {
  constructor(readonly kind: LoadFailure, message: string) {
    super(message);
  }
}

const MESSAGES: Record<LoadFailure, string> = {
  offline: 'Pas de connexion Internet. Vérifiez votre réseau.',
  'not-found': "Ligand introuvable (404). Il n'existe peut-être pas dans la base.",
  timeout: 'Délai dépassé. Veuillez réessayer.',
  server: 'Le serveur RCSB est momentanément indisponible. Réessayez plus tard.',
  parse: 'Lecture du ligand impossible. Le fichier est peut-être corrompu.',
};

export const describeFailure = (kind: LoadFailure): string => MESSAGES[kind];

function cacheFile(id: string): File {
  return new File(Paths.cache, CACHE_DIRECTORY, `${id}.cif`);
}

function ensureCacheDirectory(): void {
  new Directory(Paths.cache, CACHE_DIRECTORY).create({ idempotent: true });
}

async function download(id: string): Promise<string> {
  const controller = new AbortController();
  const timer = setTimeout(() => controller.abort(), TIMEOUT_MS);

  try {
    const response = await fetch(`${BASE_URL}/${id}.cif`, { signal: controller.signal });
    if (response.status === 404) throw new LigandLoadError('not-found', MESSAGES['not-found']);
    if (!response.ok) throw new LigandLoadError('server', MESSAGES.server);

    const announced = Number(response.headers.get('content-length'));
    if (Number.isFinite(announced) && announced > MAX_BYTES) {
      throw new LigandLoadError('parse', MESSAGES.parse);
    }

    const text = await response.text();
    if (text.length > MAX_BYTES) throw new LigandLoadError('parse', MESSAGES.parse);
    return text;
  } catch (cause) {
    if (cause instanceof LigandLoadError) throw cause;
    const aborted = cause instanceof Error && cause.name === 'AbortError';
    throw new LigandLoadError(aborted ? 'timeout' : 'offline', MESSAGES[aborted ? 'timeout' : 'offline']);
  } finally {
    clearTimeout(timer);
  }
}

export async function fetchLigandSource(id: string): Promise<{ text: string; fromCache: boolean }> {
  const file = cacheFile(id);
  if (file.exists) {
    try {
      return { text: await file.text(), fromCache: true };
    } catch {
      file.delete();
    }
  }

  const text = await download(id);
  try {
    ensureCacheDirectory();
    cacheFile(id).write(text);
  } catch {
  }
  return { text, fromCache: false };
}

export async function loadMolecule(id: string): Promise<{ molecule: Molecule; fromCache: boolean }> {
  const { text, fromCache } = await fetchLigandSource(id);
  try {
    return { molecule: parseLigandCif(text, id), fromCache };
  } catch (cause) {
    if (fromCache) cacheFile(id).delete();
    throw new LigandLoadError('parse', cause instanceof CifParseError ? cause.message : MESSAGES.parse);
  }
}

export function listCachedLigands(): Set<string> {
  const directory = new Directory(Paths.cache, CACHE_DIRECTORY);
  if (!directory.exists) return new Set();
  return new Set(
    directory
      .list()
      .map((entry) => entry.uri.split('/').pop() ?? '')
      .filter((name) => name.endsWith('.cif'))
      .map((name) => name.slice(0, -4)),
  );
}

export function cachedFileUri(id: string): string | null {
  const file = cacheFile(id);
  return file.exists ? file.uri : null;
}

export function clearCache(): void {
  const directory = new Directory(Paths.cache, CACHE_DIRECTORY);
  if (directory.exists) directory.delete();
}