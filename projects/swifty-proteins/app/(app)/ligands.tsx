import { Ionicons } from '@expo/vector-icons';
import { router, Stack, useFocusEffect } from 'expo-router';
import { useCallback, useEffect, useMemo, useState } from 'react';
import {
  ActivityIndicator,
  Alert,
  FlatList,
  Pressable,
  StyleSheet,
  Text,
  TextInput,
  View,
} from 'react-native';
import { filterLigands, loadLigandIds } from '@/ligands/catalog';
import { LigandLoadError, listCachedLigands, loadMolecule } from '@/ligands/repository';
import { useSettings } from '@/settings/SettingsProvider';
import { IconButton } from '@/ui/IconButton';
import { radius, spacing } from '@/ui/theme';
import { useTheme } from '@/ui/ThemeProvider';

const ROW_HEIGHT = 60;

export default function LigandsRoute() {
  const { theme } = useTheme();
  const { settings, toggleFavorite, isFavorite } = useSettings();

  const [ligands, setLigands] = useState<string[]>([]);
  const [query, setQuery] = useState('');
  const [favoritesOnly, setFavoritesOnly] = useState(false);
  const [catalogError, setCatalogError] = useState<string | null>(null);
  const [opening, setOpening] = useState<string | null>(null);
  const [cachedIds, setCachedIds] = useState<Set<string>>(new Set());
  const [comparing, setComparing] = useState(false);
  const [picked, setPicked] = useState<string[]>([]);

  useEffect(() => {
    loadLigandIds()
      .then(setLigands)
      .catch(() => setCatalogError("La liste des ligands n'a pas pu être lue."));
  }, []);

  useFocusEffect(
    useCallback(() => {
      setCachedIds(listCachedLigands());
    }, []),
  );

  const visible = useMemo(() => {
    const base = favoritesOnly ? ligands.filter((id) => settings.favorites.includes(id)) : ligands;
    return filterLigands(base, query);
  }, [ligands, query, favoritesOnly, settings.favorites]);

  const open = useCallback(async (id: string) => {
    setOpening(id);
    try {
      await loadMolecule(id);
      router.push({ pathname: '/ligand/[id]', params: { id } });
    } catch (cause) {
      const message =
        cause instanceof LigandLoadError
          ? cause.message
          : 'Une erreur inattendue est survenue. Veuillez réessayer.';
      Alert.alert(`Ligand ${id}`, message);
    } finally {
      setOpening(null);
    }
  }, []);

  const pick = useCallback((id: string) => {
    setPicked((current) =>
      current.includes(id)
        ? current.filter((value) => value !== id)
        : [...current, id].slice(-2),
    );
  }, []);

  const leaveComparison = useCallback(() => {
    setComparing(false);
    setPicked([]);
  }, []);

  const renderRow = useCallback(
    ({ item }: { item: string }) => (
      <LigandRow
        id={item}
        favorite={isFavorite(item)}
        cached={cachedIds.has(item)}
        picked={comparing ? picked.includes(item) : null}
        onOpen={comparing ? pick : open}
        onToggleFavorite={toggleFavorite}
      />
    ),
    [isFavorite, cachedIds, comparing, picked, pick, open, toggleFavorite],
  );

  return (
    <View style={[styles.root, { backgroundColor: theme.background }]}>
      <Stack.Screen
        options={{
          title: comparing ? 'Choisissez deux ligands' : 'Ligands',
          headerLeft: () => (
            <IconButton
              name={comparing ? 'close' : 'git-compare-outline'}
              label={comparing ? 'Quitter la comparaison' : 'Comparer deux ligands'}
              active={comparing}
              onPress={() => (comparing ? leaveComparison() : setComparing(true))}
            />
          ),
          headerRight: () => (
            <IconButton
              name="settings-outline"
              label="Réglages"
              onPress={() => router.push('/settings')}
            />
          ),
        }}
      />

      <View style={styles.toolbar}>
        <View style={[styles.search, { backgroundColor: theme.surface, borderColor: theme.border }]}>
          <Ionicons name="search" size={18} color={theme.textMuted} />
          <TextInput
            value={query}
            onChangeText={setQuery}
            placeholder="Rechercher un ligand"
            placeholderTextColor={theme.textMuted}
            autoCapitalize="characters"
            autoCorrect={false}
            accessibilityLabel="Rechercher un ligand"
            style={[styles.searchInput, { color: theme.text }]}
          />
          {query.length > 0 && (
            <Pressable onPress={() => setQuery('')} hitSlop={10} accessibilityLabel="Effacer la recherche">
              <Ionicons name="close-circle" size={18} color={theme.textMuted} />
            </Pressable>
          )}
        </View>

        <Pressable
          onPress={() => setFavoritesOnly((value) => !value)}
          accessibilityRole="switch"
          accessibilityState={{ checked: favoritesOnly }}
          accessibilityLabel="N'afficher que les favoris"
          style={[
            styles.favoriteFilter,
            {
              backgroundColor: favoritesOnly ? theme.accent : theme.surface,
              borderColor: favoritesOnly ? theme.accent : theme.border,
            },
          ]}>
          <Ionicons
            name={favoritesOnly ? 'star' : 'star-outline'}
            size={18}
            color={favoritesOnly ? theme.onAccent : theme.textMuted}
          />
        </Pressable>
      </View>

      <Text style={[styles.count, { color: theme.textMuted }]}>
        {catalogError ?? `${visible.length} ligand${visible.length > 1 ? 's' : ''}`}
      </Text>

      <FlatList
        data={visible}
        renderItem={renderRow}
        keyExtractor={(id) => id}
        getItemLayout={(_, index) => ({ length: ROW_HEIGHT, offset: ROW_HEIGHT * index, index })}
        initialNumToRender={16}
        windowSize={11}
        removeClippedSubviews
        keyboardShouldPersistTaps="handled"
        keyboardDismissMode="on-drag"
        ListEmptyComponent={
          ligands.length > 0 ? (
            <Text style={[styles.empty, { color: theme.textMuted }]}>
              {favoritesOnly ? 'Aucun favori pour le moment.' : 'Aucun ligand ne correspond.'}
            </Text>
          ) : null
        }
      />

      {comparing && picked.length === 2 && (
        <View style={[styles.compareBar, { backgroundColor: theme.surface, borderColor: theme.border }]}>
          <Text style={[styles.compareLabel, { color: theme.text }]}>
            {picked[0]} et {picked[1]}
          </Text>
          <Pressable
            onPress={() => {
              router.push({ pathname: '/compare', params: { left: picked[0], right: picked[1] } });
              leaveComparison();
            }}
            accessibilityRole="button"
            style={[styles.compareButton, { backgroundColor: theme.accent }]}>
            <Text style={[styles.compareButtonLabel, { color: theme.onAccent }]}>Comparer</Text>
          </Pressable>
        </View>
      )}

      {opening !== null && (
        <View style={[styles.overlay, { backgroundColor: `${theme.background}E6` }]}>
          <ActivityIndicator size="large" color={theme.accent} />
          <Text style={[styles.overlayLabel, { color: theme.text }]}>Chargement de {opening}…</Text>
        </View>
      )}
    </View>
  );
}

type LigandRowProps = {
  id: string;
  favorite: boolean;
  cached: boolean;
  picked: boolean | null;
  onOpen: (id: string) => void;
  onToggleFavorite: (id: string) => void;
};

function LigandRow({ id, favorite, cached, picked, onOpen, onToggleFavorite }: LigandRowProps) {
  const { theme } = useTheme();

  return (
    <Pressable
      onPress={() => onOpen(id)}
      accessibilityRole="button"
      accessibilityLabel={`Ligand ${id}`}
      style={({ pressed }) => [
        styles.row,
        { borderBottomColor: theme.border, backgroundColor: pressed ? theme.surfaceAlt : 'transparent' },
      ]}>
      <View style={[styles.badge, { backgroundColor: theme.surfaceAlt }]}>
        <Text style={[styles.badgeText, { color: theme.accent }]}>{id.slice(0, 2)}</Text>
      </View>

      <View style={styles.rowText}>
        <Text style={[styles.rowTitle, { color: theme.text }]}>{id}</Text>
      </View>

      {cached && (
        <Ionicons
          name="cloud-done-outline"
          size={17}
          color={theme.textMuted}
          accessibilityLabel="Déjà consulté, disponible hors ligne"
        />
      )}

      {picked === null ? (
        <IconButton
          name={favorite ? 'star' : 'star-outline'}
          label={favorite ? `Retirer ${id} des favoris` : `Ajouter ${id} aux favoris`}
          tone={favorite ? 'accent' : 'neutral'}
          onPress={() => onToggleFavorite(id)}
        />
      ) : (
        <Ionicons
          name={picked ? 'checkmark-circle' : 'ellipse-outline'}
          size={22}
          color={picked ? theme.accent : theme.textMuted}
        />
      )}
    </Pressable>
  );
}

const styles = StyleSheet.create({
  root: { flex: 1 },
  toolbar: { flexDirection: 'row', gap: spacing.sm, padding: spacing.md, paddingBottom: spacing.sm },
  search: {
    flex: 1,
    flexDirection: 'row',
    alignItems: 'center',
    gap: spacing.sm,
    height: 44,
    paddingHorizontal: spacing.md,
    borderRadius: radius.md,
    borderWidth: 1,
  },
  searchInput: { flex: 1, fontSize: 16 },
  favoriteFilter: {
    width: 44,
    height: 44,
    alignItems: 'center',
    justifyContent: 'center',
    borderRadius: radius.md,
    borderWidth: 1,
  },
  count: { paddingHorizontal: spacing.md, paddingBottom: spacing.sm, fontSize: 13 },
  compareBar: {
    position: 'absolute',
    left: spacing.md,
    right: spacing.md,
    bottom: spacing.lg,
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-between',
    padding: spacing.md,
    borderRadius: radius.md,
    borderWidth: 1,
  },
  compareLabel: { fontSize: 15, fontWeight: '600' },
  compareButton: {
    paddingHorizontal: spacing.lg,
    paddingVertical: spacing.sm,
    borderRadius: radius.pill,
  },
  compareButtonLabel: { fontSize: 15, fontWeight: '700' },
  row: {
    height: ROW_HEIGHT,
    flexDirection: 'row',
    alignItems: 'center',
    gap: spacing.md,
    paddingHorizontal: spacing.md,
    borderBottomWidth: StyleSheet.hairlineWidth,
  },
  badge: { width: 38, height: 38, borderRadius: radius.sm, alignItems: 'center', justifyContent: 'center' },
  badgeText: { fontSize: 14, fontWeight: '700' },
  rowText: { flex: 1 },
  rowTitle: { fontSize: 17, fontWeight: '600', letterSpacing: 0.5 },
  empty: { textAlign: 'center', marginTop: spacing.xl, fontSize: 15 },
  overlay: { ...StyleSheet.absoluteFillObject, alignItems: 'center', justifyContent: 'center', gap: spacing.md },
  overlayLabel: { fontSize: 16, fontWeight: '600' },
});