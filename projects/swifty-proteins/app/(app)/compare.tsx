import { Stack, useLocalSearchParams } from 'expo-router';
import { useEffect, useState } from 'react';
import { ActivityIndicator, StyleSheet, Text, useWindowDimensions, View } from 'react-native';
import { LigandLoadError, loadMolecule } from '@/ligands/repository';
import type { Molecule } from '@/ligands/types';
import { MoleculeView } from '@/scene/MoleculeView';
import { useSettings } from '@/settings/SettingsProvider';
import { radius, spacing } from '@/ui/theme';
import { useTheme } from '@/ui/ThemeProvider';

export default function CompareRoute() {
  const { left, right } = useLocalSearchParams<{ left: string; right: string }>();
  const { width, height } = useWindowDimensions();

  const side = width > height;

  return (
    <View style={[styles.root, { flexDirection: side ? 'row' : 'column' }]}>
      <Stack.Screen options={{ title: `${left} / ${right}` }} />
      <Pane ligandId={(left ?? '').toUpperCase()} />
      <Pane ligandId={(right ?? '').toUpperCase()} />
    </View>
  );
}

function Pane({ ligandId }: { ligandId: string }) {
  const { theme } = useTheme();
  const { settings } = useSettings();
  const [molecule, setMolecule] = useState<Molecule | null>(null);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    let active = true;
    loadMolecule(ligandId)
      .then(({ molecule: loaded }) => active && setMolecule(loaded))
      .catch((cause) =>
        active
          ? setError(cause instanceof LigandLoadError ? cause.message : 'Chargement impossible.')
          : undefined,
      );
    return () => {
      active = false;
    };
  }, [ligandId]);

  return (
    <View style={[styles.pane, { backgroundColor: theme.scene, borderColor: theme.border }]}>
      {molecule ? (
        <MoleculeView
          molecule={molecule}
          mode={settings.defaultMode}
          backgroundColor={theme.scene}
          selection={null}
          highlightedElement={null}
          measured={null}
          showLabels={false}
          onSelect={() => undefined}
          onFocusAtom={() => undefined}
        />
      ) : (
        <View style={styles.center}>
          {error ? (
            <Text style={[styles.error, { color: theme.danger }]}>{error}</Text>
          ) : (
            <ActivityIndicator color={theme.accent} />
          )}
        </View>
      )}

      <View style={[styles.caption, { backgroundColor: theme.surface, borderColor: theme.border }]}>
        <Text style={[styles.captionTitle, { color: theme.text }]}>{ligandId}</Text>
        {molecule && (
          <Text style={[styles.captionLine, { color: theme.textMuted }]}>
            {molecule.formula} · {molecule.atoms.length} atomes
          </Text>
        )}
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  root: { flex: 1 },
  pane: { flex: 1, borderWidth: StyleSheet.hairlineWidth },
  center: { flex: 1, alignItems: 'center', justifyContent: 'center', padding: spacing.md },
  error: { fontSize: 13, textAlign: 'center' },
  caption: {
    position: 'absolute',
    left: spacing.sm,
    top: spacing.sm,
    paddingHorizontal: spacing.md,
    paddingVertical: spacing.sm,
    borderRadius: radius.md,
    borderWidth: 1,
  },
  captionTitle: { fontSize: 15, fontWeight: '700' },
  captionLine: { fontSize: 12 },
});