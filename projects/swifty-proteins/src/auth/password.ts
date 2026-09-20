import { argon2idAsync } from '@noble/hashes/argon2.js';
import { bytesToHex, hexToBytes, utf8ToBytes } from '@noble/hashes/utils.js';
import * as Crypto from 'expo-crypto';

export type Argon2Params = { t: number; m: number; p: number; dkLen: number };

export const CURRENT_PARAMS: Argon2Params = { t: 1, m: 1024, p: 1, dkLen: 32 };

const SALT_BYTES = 16;

export type PasswordDigest = {
  salt: string;
  hash: string;
  params: Argon2Params;
};

export type ProgressHandler = (fraction: number) => void;

export async function hashPassword(
  password: string,
  onProgress?: ProgressHandler,
): Promise<PasswordDigest> {
  const salt = Crypto.getRandomBytes(SALT_BYTES);
  const hash = await argon2idAsync(utf8ToBytes(password), salt, { ...CURRENT_PARAMS, onProgress });
  return { salt: bytesToHex(salt), hash: bytesToHex(hash), params: CURRENT_PARAMS };
}

export async function verifyPassword(
  password: string,
  digest: PasswordDigest,
  onProgress?: ProgressHandler,
): Promise<boolean> {
  const computed = await argon2idAsync(utf8ToBytes(password), hexToBytes(digest.salt), {
    ...digest.params,
    onProgress,
  });
  return equalsInConstantTime(bytesToHex(computed), digest.hash);
}

export function usesCurrentParams(digest: PasswordDigest): boolean {
  const keys = ['t', 'm', 'p', 'dkLen'] as const;
  return keys.every((key) => digest.params[key] === CURRENT_PARAMS[key]);
}

function equalsInConstantTime(a: string, b: string): boolean {
  if (a.length !== b.length) return false;
  let difference = 0;
  for (let i = 0; i < a.length; i += 1) difference |= a.charCodeAt(i) ^ b.charCodeAt(i);
  return difference === 0;
}

export function describePasswordIssue(password: string): string | null {
  if (password.length < 8) return 'Le mot de passe doit contenir au moins 8 caractères.';
  if (!/[a-zA-Z]/.test(password)) return 'Le mot de passe doit contenir au moins une lettre.';
  if (!/[0-9]/.test(password)) return 'Le mot de passe doit contenir au moins un chiffre.';
  return null;
}

export function describeUsernameIssue(username: string): string | null {
  const value = username.trim();
  if (value.length < 3) return "L'identifiant doit contenir au moins 3 caractères.";
  if (value.length > 20) return "L'identifiant ne doit pas dépasser 20 caractères.";
  if (!/^[a-zA-Z0-9._-]+$/.test(value))
    return "L'identifiant n'accepte que lettres, chiffres, point, tiret et souligné.";
  return null;
}