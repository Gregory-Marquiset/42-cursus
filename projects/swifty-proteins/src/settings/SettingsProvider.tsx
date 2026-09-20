import AsyncStorage from '@react-native-async-storage/async-storage';
import * as Haptics from 'expo-haptics';
import { createContext, useContext, useEffect, useMemo, useState, type ReactNode } from 'react';
import type { RenderMode } from '@/scene/modes';

const STORAGE_KEY = 'settings.v1';

export type Settings = {
  defaultMode: RenderMode;
  showLabels: boolean;
  favorites: string[];
  onboarded: boolean;
};

const DEFAULTS: Settings = {
  defaultMode: 'ballAndStick',
  showLabels: false,
  favorites: [],
  onboarded: false,
};

type SettingsContextValue = {
  settings: Settings;
  loading: boolean;
  update: (patch: Partial<Settings>) => void;
  toggleFavorite: (ligandId: string) => void;
  isFavorite: (ligandId: string) => boolean;
};

const SettingsContext = createContext<SettingsContextValue | null>(null);

export function SettingsProvider({ children }: { children: ReactNode }) {
  const [settings, setSettings] = useState<Settings>(DEFAULTS);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    AsyncStorage.getItem(STORAGE_KEY)
      .then((raw) => {
        if (raw) setSettings({ ...DEFAULTS, ...(JSON.parse(raw) as Partial<Settings>) });
      })
      .catch(() => undefined)
      .finally(() => setLoading(false));
  }, []);

  const value = useMemo<SettingsContextValue>(() => {
    const persist = (next: Settings) => {
      setSettings(next);
      AsyncStorage.setItem(STORAGE_KEY, JSON.stringify(next)).catch(() => undefined);
    };

    return {
      settings,
      loading,
      update: (patch) => persist({ ...settings, ...patch }),
      isFavorite: (ligandId) => settings.favorites.includes(ligandId),
      toggleFavorite: (ligandId) => {
        Haptics.impactAsync(Haptics.ImpactFeedbackStyle.Light).catch(() => undefined);
        persist({
          ...settings,
          favorites: settings.favorites.includes(ligandId)
            ? settings.favorites.filter((id) => id !== ligandId)
            : [...settings.favorites, ligandId].sort(),
        });
      },
    };
  }, [settings, loading]);

  return <SettingsContext.Provider value={value}>{children}</SettingsContext.Provider>;
}

export function useSettings(): SettingsContextValue {
  const context = useContext(SettingsContext);
  if (!context) throw new Error('useSettings() doit être appelé dans un <SettingsProvider>.');
  return context;
}