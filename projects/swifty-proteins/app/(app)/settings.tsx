import { Ionicons } from '@expo/vector-icons';
import { Stack } from 'expo-router';
import { useState } from 'react';
import {
  Alert,
  Platform,
  Pressable,
  ScrollView,
  StyleSheet,
  Switch,
  Text,
  View,
} from 'react-native';
import { useAuth } from '@/auth/AuthProvider';
import { clearCache } from '@/ligands/repository';
import { MODE_ORDER, MODES } from '@/scene/modes';
import { useSettings } from '@/settings/SettingsProvider';
import { radius, spacing } from '@/ui/theme';
import { useTheme, type ThemePreference } from '@/ui/ThemeProvider';

const THEME_CHOICES: { value: ThemePreference; label: string }[] = [
  { value: 'system', label: 'Système' },
  { value: 'light', label: 'Clair' },
  { value: 'dark', label: 'Sombre' },
];

export default function SettingsRoute() {
  const { theme, preference, setPreference } = useTheme();
  const { settings, update } = useSettings();
  const { session, signOut } = useAuth();
  const [cacheCleared, setCacheCleared] = useState(false);

  const emptyCache = () => {
    Alert.alert(
      'Vider le cache',
      'Les ligands déjà téléchargés ne seront plus consultables hors ligne.',
      [
        { text: 'Annuler', style: 'cancel' },
        {
          text: 'Vider',
          style: 'destructive',
          onPress: () => {
            clearCache();
            setCacheCleared(true);
          },
        },
      ],
    );
  };

  return (
    <ScrollView
      style={{ backgroundColor: theme.background }}
      contentContainerStyle={styles.content}>
      <Stack.Screen options={{ title: 'Réglages' }} />

      <Section title="Apparence">
        <Choices
          options={THEME_CHOICES.map((choice) => ({ key: choice.value, label: choice.label }))}
          selected={preference}
          onSelect={(key) => setPreference(key as ThemePreference)}
        />
      </Section>

      <Section title="Modèle par défaut">
        <Choices
          options={MODE_ORDER.map((mode) => ({ key: mode, label: MODES[mode].label }))}
          selected={settings.defaultMode}
          onSelect={(key) => update({ defaultMode: key as (typeof MODE_ORDER)[number] })}
        />
      </Section>

      <Section title="Vue 3D">
        <View style={[styles.row, { borderColor: theme.border, backgroundColor: theme.surface }]}>
          <Text style={[styles.rowLabel, { color: theme.text }]}>Étiquettes des atomes</Text>
          <Switch
            value={settings.showLabels}
            onValueChange={(value) => update({ showLabels: value })}
            accessibilityLabel="Afficher les étiquettes des atomes"
            style={styles.control}
            trackColor={{ false: theme.border, true: theme.accent }}
            thumbColor={Platform.OS === 'android' ? theme.surface : undefined}
            ios_backgroundColor={theme.border}
          />
        </View>
      </Section>

      <Section title="Données">
        <Pressable
          onPress={emptyCache}
          accessibilityRole="button"
          style={[styles.row, { borderColor: theme.border, backgroundColor: theme.surface }]}>
          <Text style={[styles.rowLabel, { color: theme.text }]}>
            {cacheCleared ? 'Cache vidé' : 'Vider le cache hors ligne'}
          </Text>
          <Ionicons name="trash-outline" size={20} color={theme.textMuted} />
        </Pressable>
        <Text style={[styles.note, { color: theme.textMuted }]}>
          Chaque ligand consulté est conservé sur l’appareil et reste visible sans connexion — la
          liste le signale alors par une icône de nuage. {settings.favorites.length} ligand
          {settings.favorites.length > 1 ? 's' : ''} en favori.
        </Text>
      </Section>

      <Section title="Session">
        <Pressable
          onPress={signOut}
          accessibilityRole="button"
          style={[styles.row, { borderColor: theme.border, backgroundColor: theme.surface }]}>
          <Text style={[styles.rowLabel, { color: theme.danger }]}>
            Se déconnecter ({session?.username})
          </Text>
          <Ionicons name="log-out-outline" size={20} color={theme.danger} />
        </Pressable>
      </Section>

      <Text style={[styles.footer, { color: theme.textMuted }]}>
        Structures fournies par le RCSB Protein Data Bank.
      </Text>
    </ScrollView>
  );
}

function Section({ title, children }: { title: string; children: React.ReactNode }) {
  const { theme } = useTheme();
  return (
    <View style={styles.section}>
      <Text style={[styles.sectionTitle, { color: theme.textMuted }]}>{title.toUpperCase()}</Text>
      {children}
    </View>
  );
}

function Choices({
  options,
  selected,
  onSelect,
}: {
  options: { key: string; label: string }[];
  selected: string;
  onSelect: (key: string) => void;
}) {
  const { theme } = useTheme();
  return (
    <View style={styles.choices}>
      {options.map((option) => {
        const active = option.key === selected;
        return (
          <Pressable
            key={option.key}
            onPress={() => onSelect(option.key)}
            accessibilityRole="radio"
            accessibilityState={{ selected: active }}
            style={[
              styles.choice,
              {
                backgroundColor: active ? theme.accent : theme.surface,
                borderColor: active ? theme.accent : theme.border,
              },
            ]}>
            <Text style={[styles.choiceLabel, { color: active ? theme.onAccent : theme.text }]}>
              {option.label}
            </Text>
          </Pressable>
        );
      })}
    </View>
  );
}

const styles = StyleSheet.create({
  content: { padding: spacing.md, gap: spacing.lg, paddingBottom: spacing.xl },
  section: { gap: spacing.sm },
  sectionTitle: { fontSize: 12, fontWeight: '700', letterSpacing: 0.8 },
  choices: { flexDirection: 'row', flexWrap: 'wrap', gap: spacing.sm },
  choice: {
    paddingHorizontal: spacing.md,
    paddingVertical: spacing.sm,
    borderRadius: radius.pill,
    borderWidth: 1,
  },
  choiceLabel: { fontSize: 14, fontWeight: '600' },
  row: {
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-between',
    gap: spacing.md,
    minHeight: 52,
    paddingVertical: spacing.sm,
    paddingHorizontal: spacing.md,
    borderRadius: radius.md,
    borderWidth: 1,
  },
  rowLabel: { flex: 1, fontSize: 15, fontWeight: '500' },
  control: { alignSelf: 'center' },
  note: { fontSize: 13 },
  footer: { fontSize: 12, textAlign: 'center', marginTop: spacing.md },
});