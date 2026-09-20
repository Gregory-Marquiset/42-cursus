import AsyncStorage from '@react-native-async-storage/async-storage';
import { createContext, useContext, useEffect, useMemo, useState, type ReactNode } from 'react';
import { useColorScheme } from 'react-native';
import { themes, type Theme, type ThemeName } from './theme';

export type ThemePreference = ThemeName | 'system';

const STORAGE_KEY = 'settings.theme';

type ThemeContextValue = {
  theme: Theme;
  preference: ThemePreference;
  setPreference: (next: ThemePreference) => void;
};

const ThemeContext = createContext<ThemeContextValue | null>(null);

function isPreference(value: string | null): value is ThemePreference {
  return value === 'light' || value === 'dark' || value === 'system';
}

export function ThemeProvider({ children }: { children: ReactNode }) {
  const systemScheme: ThemeName = useColorScheme() === 'dark' ? 'dark' : 'light';
  const [preference, setStored] = useState<ThemePreference>('system');

  useEffect(() => {
    AsyncStorage.getItem(STORAGE_KEY)
      .then((saved) => isPreference(saved) && setStored(saved))
      .catch(() => undefined);
  }, []);

  const value = useMemo<ThemeContextValue>(
    () => ({
      theme: themes[preference === 'system' ? systemScheme : preference],
      preference,
      setPreference: (next) => {
        setStored(next);
        AsyncStorage.setItem(STORAGE_KEY, next).catch(() => undefined);
      },
    }),
    [preference, systemScheme],
  );

  return <ThemeContext.Provider value={value}>{children}</ThemeContext.Provider>;
}

export function useTheme(): ThemeContextValue {
  const context = useContext(ThemeContext);
  if (!context) throw new Error('useTheme() doit être appelé dans un <ThemeProvider>.');
  return context;
}