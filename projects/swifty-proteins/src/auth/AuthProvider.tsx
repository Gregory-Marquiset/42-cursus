import {
  createContext,
  useContext,
  useEffect,
  useMemo,
  useRef,
  useState,
  type ReactNode,
} from 'react';
import { AppState } from 'react-native';

export type Session = { username: string };

type AuthContextValue = {
  session: Session | null;
  signIn: (username: string) => void;
  signOut: () => void;
  expectSystemSheet: () => void;
};

const AuthContext = createContext<AuthContextValue | null>(null);

export function AuthProvider({ children }: { children: ReactNode }) {
  const [session, setSession] = useState<Session | null>(null);
  const systemSheetOpen = useRef(false);

  useEffect(() => {
    const subscription = AppState.addEventListener('change', (state) => {
      if (state === 'active') {
        systemSheetOpen.current = false;
        return;
      }
      if (state !== 'background') return;
      if (systemSheetOpen.current) return;
      setSession(null);
    });
    return () => subscription.remove();
  }, []);

  const value = useMemo<AuthContextValue>(
    () => ({
      session,
      signIn: (username) => setSession({ username }),
      signOut: () => setSession(null),
      expectSystemSheet: () => {
        systemSheetOpen.current = true;
      },
    }),
    [session],
  );

  return <AuthContext.Provider value={value}>{children}</AuthContext.Provider>;
}

export function useAuth(): AuthContextValue {
  const context = useContext(AuthContext);
  if (!context) throw new Error('useAuth() doit être appelé dans un <AuthProvider>.');
  return context;
}