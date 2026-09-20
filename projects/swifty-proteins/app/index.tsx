import { router } from 'expo-router';
import { useEffect } from 'react';
import { StyleSheet, Text, View } from 'react-native';
import Animated, {
  Easing,
  FadeIn,
  useAnimatedStyle,
  useSharedValue,
  withRepeat,
  withTiming,
} from 'react-native-reanimated';
import { useSettings } from '@/settings/SettingsProvider';
import { radius, spacing } from '@/ui/theme';
import { useTheme } from '@/ui/ThemeProvider';

const SPLASH_DURATION_MS = 1800;

const ORBIT_PERIOD_MS = 3200;

export default function SplashRoute() {
  const { theme } = useTheme();
  const { settings, loading } = useSettings();
  const spin = useSharedValue(0);

  useEffect(() => {
    spin.value = withRepeat(withTiming(1, { duration: ORBIT_PERIOD_MS, easing: Easing.linear }), -1);
  }, []);

  useEffect(() => {
    if (loading) return;
    const timer = setTimeout(
      () => router.replace(settings.onboarded ? '/login' : '/onboarding'),
      SPLASH_DURATION_MS,
    );
    return () => clearTimeout(timer);
  }, [loading, settings.onboarded]);

  const clockwise = useAnimatedStyle(() => ({
    transform: [{ rotateZ: `${spin.value * 360}deg` }, { scaleY: 0.36 }],
  }));
  const counterClockwise = useAnimatedStyle(() => ({
    transform: [{ rotateZ: `${spin.value * -360}deg` }, { scaleY: 0.36 }],
  }));

  return (
    <View style={[styles.root, { backgroundColor: theme.background }]}>
      <View style={styles.atom}>
        <Animated.View style={[styles.orbit, { borderColor: theme.accent }, clockwise]} />
        <Animated.View style={[styles.orbit, { borderColor: theme.accent }, counterClockwise]} />
        <View style={[styles.nucleus, { backgroundColor: theme.accent }]} />
      </View>

      <Animated.Text
        entering={FadeIn.delay(150).duration(600)}
        style={[styles.title, { color: theme.text }]}>
        Swifty Protein
      </Animated.Text>
      <Animated.Text
        entering={FadeIn.delay(450).duration(600)}
        style={[styles.subtitle, { color: theme.textMuted }]}>
        Visualiseur de ligands · RCSB PDB
      </Animated.Text>
    </View>
  );
}

const ATOM_SIZE = 148;

const styles = StyleSheet.create({
  root: { flex: 1, alignItems: 'center', justifyContent: 'center', gap: spacing.sm },
  atom: {
    width: ATOM_SIZE,
    height: ATOM_SIZE,
    alignItems: 'center',
    justifyContent: 'center',
    marginBottom: spacing.lg,
  },
  orbit: {
    position: 'absolute',
    width: ATOM_SIZE,
    height: ATOM_SIZE,
    borderWidth: 2,
    borderRadius: radius.pill,
    opacity: 0.75,
  },
  nucleus: { width: 26, height: 26, borderRadius: radius.pill },
  title: { fontSize: 30, fontWeight: '700', letterSpacing: 0.4 },
  subtitle: { fontSize: 14 },
});