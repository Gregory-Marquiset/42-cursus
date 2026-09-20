import { Redirect, Stack } from 'expo-router';
import { Platform } from 'react-native';
import { useAuth } from '@/auth/AuthProvider';
import { useTheme } from '@/ui/ThemeProvider';

const androidHeaderInset = Platform.OS === 'android' ? { statusBarTranslucent: true } : null;

export default function ProtectedLayout() {
  const { session } = useAuth();
  const { theme } = useTheme();

  if (!session) return <Redirect href="/login" />;

  return (
    <Stack
      screenOptions={{
        headerStyle: { backgroundColor: theme.surface },
        headerTintColor: theme.text,
        headerTitleStyle: { color: theme.text },
        contentStyle: { backgroundColor: theme.background },
        ...androidHeaderInset,
      }}
    />
  );
}