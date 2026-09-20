import { Directory, File, Paths } from 'expo-file-system';
import { router, Stack, useLocalSearchParams } from 'expo-router';
import * as Haptics from 'expo-haptics';
import * as Sharing from 'expo-sharing';
import { useCallback, useEffect, useMemo, useRef, useState } from 'react';
import {
  ActivityIndicator,
  Alert,
  Platform,
  Pressable,
  ScrollView,
  Share,
  StyleSheet,
  Text,
  useWindowDimensions,
  View,
} from 'react-native';
import Animated, { useAnimatedStyle, useSharedValue, type SharedValue } from 'react-native-reanimated';
import { useSafeAreaInsets } from 'react-native-safe-area-context';
import { useAuth } from '@/auth/AuthProvider';
import { elementName } from '@/chemistry/elements';
import { cachedFileUri, LigandLoadError, loadMolecule } from '@/ligands/repository';
import type { Molecule } from '@/ligands/types';
import { encodeGif } from '@/media/gif';
import { MODE_ORDER, MODES, type RenderMode } from '@/scene/modes';
import {
  TURNTABLE_DELAY_CS,
  TURNTABLE_SIZE,
} from '@/scene/turntable';
import {
  LABEL_HIDDEN,
  MoleculeView,
  type MoleculeViewHandle,
  type Selection,
} from '@/scene/MoleculeView';
import { useSettings } from '@/settings/SettingsProvider';
import { radius, spacing } from '@/ui/theme';
import { ActionSheet } from '@/ui/ActionSheet';
import { IconButton } from '@/ui/IconButton';
import { useTheme } from '@/ui/ThemeProvider';

const MAX_LABELS = 150;

const SHARE_DIRECTORY = 'shares';

export default function LigandRoute() {
  const { id } = useLocalSearchParams<{ id: string }>();
  const ligandId = (id ?? '').toUpperCase();
  const { theme } = useTheme();
  const insets = useSafeAreaInsets();
  const { width, height } = useWindowDimensions();
  const landscape = width > height;
  const { settings, toggleFavorite, isFavorite, update } = useSettings();
  const { expectSystemSheet } = useAuth();

  const view = useRef<MoleculeViewHandle>(null);
  const [molecule, setMolecule] = useState<Molecule | null>(null);
  const [error, setError] = useState<string | null>(null);
  const [mode, setMode] = useState<RenderMode>(settings.defaultMode);
  const [selection, setSelection] = useState<Selection>(null);
  const [measuring, setMeasuring] = useState(false);
  const [pendingAtom, setPendingAtom] = useState<number | null>(null);
  const [measured, setMeasured] = useState<[number, number] | null>(null);
  const [recording, setRecording] = useState<number | null>(null);
  const [shareMenuOpen, setShareMenuOpen] = useState(false);
  const labelFrame = useSharedValue<number[]>([]);

  useEffect(() => {
    let active = true;
    loadMolecule(ligandId)
      .then(({ molecule: loaded }) => active && setMolecule(loaded))
      .catch((cause) => {
        if (!active) return;
        setError(
          cause instanceof LigandLoadError ? cause.message : 'Ce ligand n’a pas pu être chargé.',
        );
      });
    return () => {
      active = false;
    };
  }, [ligandId]);

  useEffect(() => {
    if (!error) return;
    Alert.alert(`Ligand ${ligandId}`, error, [{ text: 'Retour', onPress: () => router.back() }]);
  }, [error, ligandId]);

  const handleSelect = useCallback(
    (next: Selection) => {
      if (next) Haptics.selectionAsync().catch(() => undefined);
      setSelection(next);
      if (!measuring) return;

      if (next?.kind !== 'atom') {
        setPendingAtom(null);
        setMeasured(null);
        return;
      }
      setPendingAtom((first) => {
        if (first === null) {
          setMeasured(null);
          return next.index;
        }
        setMeasured(first === next.index ? null : [first, next.index]);
        return null;
      });
    },
    [measuring],
  );

  const focusAtom = useCallback((index: number) => view.current?.focusOn(index), []);

  const toggleMeasuring = useCallback(() => {
    setMeasuring((active) => !active);
    setPendingAtom(null);
    setMeasured(null);
  }, []);

  const shareView = useCallback(
    async (format: 'png' | 'jpeg') => {
      if (!molecule) return;
      const uri = await view.current?.takeSnapshot(format);
      if (!uri) {
        Alert.alert('Partage', 'La capture de la vue 3D a échoué.');
        return;
      }

      const caption = `${molecule.id} — ${molecule.name}`;
      const details = `${molecule.formula} · ${molecule.atoms.length} atomes, ${molecule.bonds.length} liaisons`;

      expectSystemSheet();
      if (Platform.OS === 'ios') {
        await Share.share({ message: `${caption}\n${details}`, url: uri });
        return;
      }

      if (!(await Sharing.isAvailableAsync())) {
        Alert.alert('Partage', "Le partage n'est pas disponible sur cet appareil.");
        return;
      }
      await Sharing.shareAsync(uri, {
        mimeType: format === 'png' ? 'image/png' : 'image/jpeg',
        dialogTitle: `${caption} · ${details}`,
      });
    },
    [expectSystemSheet, molecule],
  );

  const shareTurntable = useCallback(async () => {
    if (!molecule || recording !== null) return;
    try {
      setRecording(0);
      const frames = await view.current?.recordTurntable((f) => setRecording(f * 0.5));
      if (!frames || frames.length === 0) {
        Alert.alert('Partage', "La capture de l'animation a échoué.");
        return;
      }

      const bytes = await encodeGif(
        frames,
        {
          width: TURNTABLE_SIZE,
          height: TURNTABLE_SIZE,
          delayCentiseconds: TURNTABLE_DELAY_CS,
        },
        (f) => setRecording(0.5 + f * 0.5),
      );

      new Directory(Paths.cache, SHARE_DIRECTORY).create({ idempotent: true });
      const file = new File(Paths.cache, SHARE_DIRECTORY, `${ligandId}.gif`);
      file.write(bytes);

      if (!(await Sharing.isAvailableAsync())) {
        Alert.alert('Partage', "Le partage n'est pas disponible sur cet appareil.");
        return;
      }
      expectSystemSheet();
      await Sharing.shareAsync(file.uri, {
        mimeType: 'image/gif',
        dialogTitle: `${molecule.id} — ${molecule.name} · ${molecule.formula}`,
      });
    } catch {
      Alert.alert('Partage', "L'animation n'a pas pu être produite.");
    } finally {
      setRecording(null);
    }
  }, [expectSystemSheet, ligandId, molecule, recording]);

  const shareSource = useCallback(async () => {
    const uri = cachedFileUri(ligandId);
    if (!uri || !(await Sharing.isAvailableAsync())) {
      Alert.alert('Partage', "Le fichier source n'est pas disponible.");
      return;
    }
    expectSystemSheet();
    await Sharing.shareAsync(uri, { mimeType: 'chemical/x-cif', dialogTitle: `${ligandId}.cif` });
  }, [expectSystemSheet, ligandId]);

  const shareOptions = useMemo(
    () => [
      {
        label: 'Image PNG',
        hint: 'Capture de la vue actuelle, sans perte',
        onPress: () => shareView('png'),
      },
      {
        label: 'Image JPEG',
        hint: 'Capture de la vue actuelle, fichier plus léger',
        onPress: () => shareView('jpeg'),
      },
      {
        label: 'Animation GIF',
        hint: 'Un tour complet de la molécule',
        onPress: shareTurntable,
      },
      {
        label: 'Fichier .cif',
        hint: 'Le fichier source du ligand',
        onPress: shareSource,
      },
    ],
    [shareView, shareSource, shareTurntable],
  );

  const openShareMenu = useCallback(() => setShareMenuOpen(true), []);

  const favorite = isFavorite(ligandId);
  const showLabels = settings.showLabels && (molecule?.atoms.length ?? 0) <= MAX_LABELS;

  return (
    <View style={[styles.root, { backgroundColor: theme.scene }]}>
      <Stack.Screen
        options={{
          title: ligandId,
          headerRight: () => (
            <View style={styles.headerActions}>
              <IconButton
                name={favorite ? 'star' : 'star-outline'}
                label={favorite ? 'Retirer des favoris' : 'Ajouter aux favoris'}
                tone={favorite ? 'accent' : 'neutral'}
                onPress={() => toggleFavorite(ligandId)}
              />
              <IconButton
                name="share-outline"
                label="Partager"
                onPress={openShareMenu}
                disabled={!molecule}
              />
            </View>
          ),
        }}
      />

      {molecule ? (
        <>
          <MoleculeView
            ref={view}
            molecule={molecule}
            mode={mode}
            backgroundColor={theme.scene}
            selection={selection}
            highlightedElement={
              selection?.kind === 'atom' ? molecule.atoms[selection.index].element : null
            }
            measured={measured}
            showLabels={showLabels}
            labelFrame={labelFrame}
            onSelect={handleSelect}
            onFocusAtom={focusAtom}
          />

          {showLabels && (
            <View style={StyleSheet.absoluteFill} pointerEvents="none">
              {molecule.atoms.map((atom, index) => (
                <AtomLabel
                  key={index}
                  index={index}
                  frame={labelFrame}
                  text={atom.element}
                  color={theme.text}
                />
              ))}
            </View>
          )}

          <SideTools
            showLabels={settings.showLabels}
            measuring={measuring}
            onToggleLabels={() => update({ showLabels: !settings.showLabels })}
            onToggleMeasuring={toggleMeasuring}
            onReset={() => view.current?.resetCamera()}
          />

          <View
            style={[
              styles.bottom,
              landscape && styles.bottomLandscape,
              { paddingBottom: insets.bottom + spacing.md },
            ]}>
            <View style={[styles.panels, landscape && styles.panelsLandscape]}>
              {measuring && (
                <MeasurementCard molecule={molecule} pending={pendingAtom} measured={measured} />
              )}
              {selection && <InfoCard molecule={molecule} selection={selection} />}
            </View>
            <ModeSelector current={mode} onChange={setMode} landscape={landscape} />
          </View>

          {recording !== null && (
            <View style={[styles.recording, { backgroundColor: theme.background + "E6" }]}>
              <ActivityIndicator size="large" color={theme.accent} />
              <Text style={[styles.loadingLabel, { color: theme.text }]}>
                {`Animation… ${Math.round(recording * 100)} %`}
              </Text>
            </View>
          )}
        </>
      ) : (
        !error && (
          <View style={styles.loading}>
            <ActivityIndicator size="large" color={theme.accent} />
            <Text style={[styles.loadingLabel, { color: theme.text }]}>Préparation du modèle…</Text>
          </View>
        )
      )}

      <ActionSheet
        visible={shareMenuOpen}
        title={`Partager ${ligandId}`}
        options={shareOptions}
        onClose={() => setShareMenuOpen(false)}
      />
    </View>
  );
}

function SideTools(props: {
  showLabels: boolean;
  measuring: boolean;
  onToggleLabels: () => void;
  onToggleMeasuring: () => void;
  onReset: () => void;
}) {
  return (
    <View style={styles.sideTools}>
      <IconButton
        name="text-outline"
        label="Étiquettes des atomes"
        variant="filled"
        active={props.showLabels}
        onPress={props.onToggleLabels}
      />
      <IconButton
        name="resize-outline"
        label="Mesurer une distance"
        variant="filled"
        active={props.measuring}
        onPress={props.onToggleMeasuring}
      />
      <IconButton
        name="scan-outline"
        label="Recadrer la molécule"
        variant="filled"
        onPress={props.onReset}
      />
    </View>
  );
}

function AtomLabel({
  index,
  frame,
  text,
  color,
}: {
  index: number;
  frame: SharedValue<number[]>;
  text: string;
  color: string;
}) {
  const animatedStyle = useAnimatedStyle(() => {
    const x = frame.value[index * 2];
    const y = frame.value[index * 2 + 1];
    if (x === undefined || x === LABEL_HIDDEN) return { opacity: 0 };
    return { opacity: 1, transform: [{ translateX: x - 10 }, { translateY: y - 9 }] };
  });

  return (
    <Animated.View style={[styles.atomLabel, animatedStyle]}>
      <Text style={[styles.atomLabelText, { color }]}>{text}</Text>
    </Animated.View>
  );
}

function InfoCard({ molecule, selection }: { molecule: Molecule; selection: NonNullable<Selection> }) {
  const { theme } = useTheme();

  if (selection.kind === 'atom') {
    const atom = molecule.atoms[selection.index];
    if (!atom) return null;
    const name = elementName(atom.element);
    return (
      <View style={[styles.card, { backgroundColor: theme.surface, borderColor: theme.border }]}>
        <Text style={[styles.cardTitle, { color: theme.text }]}>
          {atom.element}
          {name ? ` · ${name}` : ''}
        </Text>
        <Text style={[styles.cardLine, { color: theme.textMuted }]}>
          Atome {atom.id}
          {atom.charge !== 0 ? ` · charge ${atom.charge > 0 ? '+' : ''}${atom.charge}` : ''}
          {atom.aromatic ? ' · aromatique' : ''}
        </Text>
        <Text style={[styles.cardLine, { color: theme.textMuted }]}>
          x {atom.position[0].toFixed(2)}   y {atom.position[1].toFixed(2)}   z{' '}
          {atom.position[2].toFixed(2)}
        </Text>
      </View>
    );
  }

  const bond = molecule.bonds[selection.index];
  if (!bond) return null;
  const from = molecule.atoms[bond.from];
  const to = molecule.atoms[bond.to];
  const names = { 1: 'simple', 2: 'double', 3: 'triple' } as const;

  return (
    <View style={[styles.card, { backgroundColor: theme.surface, borderColor: theme.border }]}>
      <Text style={[styles.cardTitle, { color: theme.text }]}>
        Liaison {from.id} — {to.id}
      </Text>
      <Text style={[styles.cardLine, { color: theme.textMuted }]}>
        Type {names[bond.order]}
        {bond.aromatic ? ' · aromatique' : ''} · {distanceBetween(molecule, bond.from, bond.to).toFixed(2)} Å
      </Text>
    </View>
  );
}

function MeasurementCard({
  molecule,
  pending,
  measured,
}: {
  molecule: Molecule;
  pending: number | null;
  measured: [number, number] | null;
}) {
  const { theme } = useTheme();

  const text = measured
    ? `${molecule.atoms[measured[0]].id} — ${molecule.atoms[measured[1]].id} : ${distanceBetween(molecule, measured[0], measured[1]).toFixed(3)} Å`
    : pending !== null
      ? `Premier atome : ${molecule.atoms[pending].id}. Touchez-en un second.`
      : 'Touchez deux atomes pour mesurer leur distance.';

  return (
    <View style={[styles.card, { backgroundColor: theme.accent, borderColor: theme.accent }]}>
      <Text style={[styles.cardLine, { color: theme.onAccent, fontWeight: '600' }]}>{text}</Text>
    </View>
  );
}

function ModeSelector({
  current,
  onChange,
  landscape,
}: {
  current: RenderMode;
  onChange: (mode: RenderMode) => void;
  landscape: boolean;
}) {
  const { theme } = useTheme();

  return (
    <ScrollView
      horizontal
      showsHorizontalScrollIndicator={false}
      style={landscape ? styles.modesLandscape : undefined}
      contentContainerStyle={styles.modes}>
      {MODE_ORDER.map((mode) => {
        const active = mode === current;
        return (
          <Pressable
            key={mode}
            onPress={() => onChange(mode)}
            accessibilityRole="button"
            accessibilityState={{ selected: active }}
            style={[
              styles.chip,
              {
                backgroundColor: active ? theme.accent : theme.surface,
                borderColor: active ? theme.accent : theme.border,
              },
            ]}>
            <Text style={[styles.chipLabel, { color: active ? theme.onAccent : theme.text }]}>
              {MODES[mode].label}
            </Text>
          </Pressable>
        );
      })}
    </ScrollView>
  );
}

function distanceBetween(molecule: Molecule, from: number, to: number): number {
  const a = molecule.atoms[from].position;
  const b = molecule.atoms[to].position;
  return Math.hypot(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

const styles = StyleSheet.create({
  root: { flex: 1 },
  headerActions: { flexDirection: 'row', gap: spacing.md, alignItems: 'center' },
  loading: { flex: 1, alignItems: 'center', justifyContent: 'center', gap: spacing.md },
  loadingLabel: { fontSize: 16, fontWeight: '600' },
  atomLabel: { position: 'absolute', left: 0, top: 0, width: 20, alignItems: 'center' },
  atomLabelText: { fontSize: 11, fontWeight: '700' },
  sideTools: { position: 'absolute', right: spacing.md, top: spacing.md, gap: spacing.sm },
  recording: {
    ...StyleSheet.absoluteFillObject,
    alignItems: 'center',
    justifyContent: 'center',
    gap: spacing.md,
  },
  bottom: {
    position: 'absolute',
    left: 0,
    right: 0,
    bottom: 0,
    gap: spacing.sm,
    paddingHorizontal: spacing.md,
  },
  bottomLandscape: { flexDirection: 'row', alignItems: 'flex-end', gap: spacing.md },
  panels: { gap: spacing.sm },
  panelsLandscape: { flex: 1 },
  modesLandscape: { flexGrow: 0, flexShrink: 1 },
  card: { padding: spacing.md, borderRadius: radius.md, borderWidth: 1, gap: 2 },
  cardTitle: { fontSize: 16, fontWeight: '700' },
  cardLine: { fontSize: 13 },
  modes: { gap: spacing.sm, paddingVertical: spacing.xs },
  chip: {
    paddingHorizontal: spacing.md,
    paddingVertical: spacing.sm,
    borderRadius: radius.pill,
    borderWidth: 1,
  },
  chipLabel: { fontSize: 14, fontWeight: '600' },
});