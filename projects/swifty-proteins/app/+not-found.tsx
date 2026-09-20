import { router } from 'expo-router';
import { StyleSheet, Text, View } from 'react-native';
import { Button } from '@/ui/Button';
import { spacing } from '@/ui/theme';
import { useTheme } from '@/ui/ThemeProvider';

export default function NotFoundRoute() {
  const { theme } = useTheme();

  return (
    <View style={[styles.root, { backgroundColor: theme.background }]}>
      <Text style={[styles.title, { color: theme.text }]}>Page introuvable</Text>
      <Text style={[styles.text, { color: theme.textMuted }]}>
        Cet écran n’existe pas dans l’application.
      </Text>
      <Button label="Revenir à l’accueil" onPress={() => router.replace('/')} />
    </View>
  );
}

const styles = StyleSheet.create({
  root: { flex: 1, alignItems: 'center', justifyContent: 'center', padding: spacing.lg, gap: spacing.md },
  title: { fontSize: 22, fontWeight: '700' },
  text: { fontSize: 15, textAlign: 'center' },
});