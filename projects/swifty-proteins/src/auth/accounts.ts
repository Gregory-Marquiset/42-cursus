import { sha256 } from '@noble/hashes/sha2.js';
import { bytesToHex, utf8ToBytes } from '@noble/hashes/utils.js';
import * as SecureStore from 'expo-secure-store';
import {
  hashPassword,
  usesCurrentParams,
  verifyPassword,
  type PasswordDigest,
  type ProgressHandler,
} from './password';

export type Account = PasswordDigest & { username: string; createdAt: string };

export type VerifyOutcome =
  | { status: 'ok'; account: Account }
  | { status: 'invalid' }
  | { status: 'unverifiable' };

const LAST_USER_KEY = 'session.lastUser';

export function normalizeUsername(username: string): string {
  return username.trim().toLowerCase();
}

function storageKey(username: string): string {
  return `account.${bytesToHex(sha256(utf8ToBytes(normalizeUsername(username))))}`;
}

export async function findAccount(username: string): Promise<Account | null> {
  const raw = await SecureStore.getItemAsync(storageKey(username));
  return raw ? (JSON.parse(raw) as Account) : null;
}

export async function createAccount(
  username: string,
  password: string,
  onProgress?: ProgressHandler,
): Promise<Account> {
  const account: Account = {
    username: username.trim(),
    createdAt: new Date().toISOString(),
    ...(await hashPassword(password, onProgress)),
  };
  await SecureStore.setItemAsync(storageKey(username), JSON.stringify(account));
  return account;
}

export async function verifyCredentials(
  username: string,
  password: string,
  onProgress?: ProgressHandler,
): Promise<VerifyOutcome> {
  const account = await findAccount(username);
  if (!account) return { status: 'invalid' };

  if (!account.params) return { status: 'unverifiable' };

  if (!(await verifyPassword(password, account, onProgress))) return { status: 'invalid' };

  if (!usesCurrentParams(account)) {
    const upgraded: Account = { ...account, ...(await hashPassword(password)) };
    await SecureStore.setItemAsync(storageKey(username), JSON.stringify(upgraded));
    return { status: 'ok', account: upgraded };
  }

  return { status: 'ok', account };
}

export async function deleteAccount(username: string): Promise<void> {
  await SecureStore.deleteItemAsync(storageKey(username));
}

export async function rememberLastUser(username: string): Promise<void> {
  await SecureStore.setItemAsync(LAST_USER_KEY, username.trim());
}

export async function getLastUser(): Promise<string | null> {
  return SecureStore.getItemAsync(LAST_USER_KEY);
}