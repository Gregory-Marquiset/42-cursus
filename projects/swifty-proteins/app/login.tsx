import { Redirect } from 'expo-router';
import { useCallback, useEffect, useState } from 'react';
import {
  Alert,
  KeyboardAvoidingView,
  Linking,
  Platform,
  Pressable,
  ScrollView,
  StyleSheet,
  Text,
  View,
} from 'react-native';
import {
  createAccount,
  deleteAccount,
  findAccount,
  getLastUser,
  rememberLastUser,
  verifyCredentials,
} from '@/auth/accounts';
import { useAuth } from '@/auth/AuthProvider';
import {
  getBiometricAvailability,
  promptBiometric,
  type BiometricAvailability,
} from '@/auth/biometrics';
import { describePasswordIssue, describeUsernameIssue } from '@/auth/password';
import { Button } from '@/ui/Button';
import { TextField } from '@/ui/TextField';
import { radius, spacing } from '@/ui/theme';
import { useTheme } from '@/ui/ThemeProvider';

type Mode = 'signIn' | 'signUp';

export default function LoginRoute() {
  const { theme } = useTheme();
  const { session, signIn } = useAuth();

  const [mode, setMode] = useState<Mode>('signIn');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState<string | null>(null);
  const [busy, setBusy] = useState(false);
  const [progress, setProgress] = useState(0);
  const [biometrics, setBiometrics] = useState<BiometricAvailability | null>(null);
  const [lastUser, setLastUser] = useState<string | null>(null);

  useEffect(() => {
    getBiometricAvailability().then(setBiometrics);
    getLastUser().then((saved) => {
      setLastUser(saved);
      if (saved) setUsername(saved);
    });
  }, []);

  const trackProgress = useCallback((fraction: number) => {
    const percent = Math.round(fraction * 100);
    setProgress((current) => (percent >= current + 5 ? percent : current));
  }, []);

  const switchMode = (next: Mode) => {
    setMode(next);
    setError(null);
    setPassword('');
  };

  const submit = async () => {
    setError(null);

    const usernameIssue = describeUsernameIssue(username);
    if (usernameIssue) return setError(usernameIssue);
    if (mode === 'signUp') {
      const passwordIssue = describePasswordIssue(password);
      if (passwordIssue) return setError(passwordIssue);
    }

    setBusy(true);
    setProgress(0);
    try {
      if (mode === 'signUp') {
        if (await findAccount(username)) {
          setError('Cet identifiant est déjà utilisé.');
          return;
        }
        await createAccount(username, password, trackProgress);
      } else {
        const outcome = await verifyCredentials(username, password, trackProgress);

        if (outcome.status === 'unverifiable') {
          offerAccountReset();
          return;
        }
        if (outcome.status === 'invalid') {
          setError('Identifiant ou mot de passe incorrect.');
          return;
        }
      }
      await rememberLastUser(username);
      signIn(username.trim());
    } catch {
      setError('Une erreur est survenue. Veuillez réessayer.');
    } finally {
      setBusy(false);
    }
  };

  const offerAccountReset = () => {
    Alert.alert(
      'Compte à recréer',
      "Ce compte date d'une version antérieure de l'application et ne peut plus être vérifié. Supprimez-le pour en recréer un avec le même identifiant.",
      [
        { text: 'Annuler', style: 'cancel' },
        {
          text: 'Supprimer le compte',
          style: 'destructive',
          onPress: async () => {
            await deleteAccount(username);
            switchMode('signUp');
          },
        },
      ],
    );
  };

  const unlockWithBiometrics = async () => {
    if (!biometrics?.usable || !lastUser) return;
    const outcome = await promptBiometric(biometrics.label);
    if (outcome.ok) {
      signIn(lastUser);
      return;
    }

    if (outcome.permanent) setBiometrics({ usable: false, reason: outcome.message });
    Alert.alert(
      'Authentification biométrique',
      outcome.message,
      outcome.settings
        ? [
            { text: 'Ouvrir les réglages', onPress: () => Linking.openSettings() },
            { text: 'Fermer', style: 'cancel' },
          ]
        : [{ text: 'Fermer' }],
    );
  };

  if (session) return <Redirect href="/ligands" />;

  const showBiometrics = mode === 'signIn' && biometrics?.usable === true && lastUser !== null;

  return (
    <KeyboardAvoidingView
      style={[styles.root, { backgroundColor: theme.background }]}
      behavior={Platform.OS === 'ios' ? 'padding' : undefined}>
      <ScrollView
        contentContainerStyle={styles.content}
        keyboardShouldPersistTaps="handled"
        keyboardDismissMode="on-drag">
        <View style={styles.header}>
          <Text style={[styles.title, { color: theme.text }]}>
            {mode === 'signIn' ? 'Connexion' : 'Créer un compte'}
          </Text>
          <Text style={[styles.subtitle, { color: theme.textMuted }]}>
            {mode === 'signIn'
              ? 'Identifiez-vous pour accéder aux ligands.'
              : 'Au moins 8 caractères, dont une lettre et un chiffre.'}
          </Text>
        </View>

        <TextField
          label="Identifiant"
          value={username}
          onChangeText={setUsername}
          autoCapitalize="none"
          autoCorrect={false}
          textContentType="username"
          autoComplete="username"
          keyboardType="default"
          returnKeyType="next"
          placeholder="votre identifiant"
        />

        <TextField
          label="Mot de passe"
          value={password}
          onChangeText={setPassword}
          secureTextEntry
          autoCapitalize="none"
          autoCorrect={false}
          textContentType={mode === 'signIn' ? 'password' : 'newPassword'}
          autoComplete={mode === 'signIn' ? 'current-password' : 'new-password'}
          returnKeyType="go"
          onSubmitEditing={submit}
          placeholder="••••••••"
          error={error}
        />

        <Button
          label={mode === 'signIn' ? 'Se connecter' : 'Créer le compte'}
          onPress={submit}
          busy={busy}
          busyLabel={`${progress} %`}
        />

        {showBiometrics && (
          <Button
            label={`Déverrouiller avec ${biometrics.label}`}
            onPress={unlockWithBiometrics}
            variant="secondary"
            disabled={busy}
            style={styles.spaced}
          />
        )}

        {mode === 'signIn' && biometrics?.usable === false && (
          <Text style={[styles.note, { color: theme.textMuted, borderColor: theme.border }]}>
            {biometrics.reason}
          </Text>
        )}

        <Pressable
          onPress={() => switchMode(mode === 'signIn' ? 'signUp' : 'signIn')}
          accessibilityRole="button"
          style={styles.switch}>
          <Text style={[styles.switchLabel, { color: theme.accent }]}>
            {mode === 'signIn' ? 'Pas encore de compte ? En créer un' : "J'ai déjà un compte"}
          </Text>
        </Pressable>
      </ScrollView>
    </KeyboardAvoidingView>
  );
}

const styles = StyleSheet.create({
  root: { flex: 1 },
  content: {
    flexGrow: 1,
    justifyContent: 'center',
    padding: spacing.lg,
    gap: spacing.xs,
    maxWidth: 520,
    width: '100%',
    alignSelf: 'center',
  },
  header: { marginBottom: spacing.lg, gap: spacing.xs },
  title: { fontSize: 28, fontWeight: '700' },
  subtitle: { fontSize: 15 },
  spaced: { marginTop: spacing.sm },
  note: {
    marginTop: spacing.md,
    padding: spacing.md,
    borderRadius: radius.md,
    borderWidth: 1,
    fontSize: 13,
    textAlign: 'center',
  },
  switch: { marginTop: spacing.lg, alignItems: 'center', padding: spacing.sm },
  switchLabel: { fontSize: 15, fontWeight: '600' },
});