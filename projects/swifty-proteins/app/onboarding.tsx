import { Ionicons } from '@expo/vector-icons';
import { router } from 'expo-router';
import { useState } from 'react';
import { StyleSheet, Text, View } from 'react-native';
import Animated, { FadeIn } from 'react-native-reanimated';
import { useSettings } from '@/settings/SettingsProvider';
import { Button } from '@/ui/Button';
import { radius, spacing } from '@/ui/theme';
import { useTheme } from '@/ui/ThemeProvider';

const STEPS = [
  {
    icon: 'search-outline',
    title: 'Explorez la base RCSB',
    body: '1243 ligands issus du Protein Data Bank, filtrables à la frappe. Marquez vos préférés d’une étoile.',
  },
  {
    icon: 'cube-outline',
    title: 'Visualisez en trois dimensions',
    body: 'Faites glisser un doigt pour tourner, pincez pour zoomer, glissez à deux doigts pour déplacer la vue.',
  },
  {
    icon: 'information-circle-outline',
    title: 'Interrogez la molécule',
    body: 'Touchez un atome pour ses informations, une liaison pour sa longueur. Double-touchez pour la centrer.',
  },
] as const;

export default function OnboardingRoute() {
  const { theme } = useTheme();
  const { update } = useSettings();
  const [step, setStep] = useState(0);

  const finish = () => {
    update({ onboarded: true });
    router.replace('/login');
  };

  const current = STEPS[step];
  const last = step === STEPS.length - 1;

  return (
    <View style={[styles.root, { backgroundColor: theme.background }]}>
      <Animated.View key={step} entering={FadeIn.duration(320)} style={styles.body}>
        <View style={[styles.icon, { backgroundColor: theme.surfaceAlt }]}>
          <Ionicons name={current.icon} size={44} color={theme.accent} />
        </View>
        <Text style={[styles.title, { color: theme.text }]}>{current.title}</Text>
        <Text style={[styles.text, { color: theme.textMuted }]}>{current.body}</Text>
      </Animated.View>

      <View style={styles.dots}>
        {STEPS.map((item, index) => (
          <View
            key={item.title}
            style={[
              styles.dot,
              { backgroundColor: index === step ? theme.accent : theme.border },
            ]}
          />
        ))}
      </View>

      <View style={styles.actions}>
        <Button
          label={last ? 'Commencer' : 'Suivant'}
          onPress={() => (last ? finish() : setStep((value) => value + 1))}
        />
        {!last && <Button label="Passer" onPress={finish} variant="secondary" />}
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  root: { flex: 1, padding: spacing.lg, justifyContent: 'space-between' },
  body: { flex: 1, alignItems: 'center', justifyContent: 'center', gap: spacing.md },
  icon: { width: 96, height: 96, borderRadius: radius.lg, alignItems: 'center', justifyContent: 'center' },
  title: { fontSize: 24, fontWeight: '700', textAlign: 'center' },
  text: { fontSize: 16, textAlign: 'center', lineHeight: 24, maxWidth: 340 },
  dots: { flexDirection: 'row', justifyContent: 'center', gap: spacing.sm, marginBottom: spacing.lg },
  dot: { width: 8, height: 8, borderRadius: radius.pill },
  actions: { gap: spacing.sm },
});