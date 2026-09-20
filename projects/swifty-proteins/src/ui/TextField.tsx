import { Ionicons } from '@expo/vector-icons';
import { useState } from 'react';
import { Pressable, StyleSheet, Text, TextInput, View, type TextInputProps } from 'react-native';
import { radius, spacing } from './theme';
import { useTheme } from './ThemeProvider';

type TextFieldProps = TextInputProps & {
  label: string;
  error?: string | null;
};

export function TextField({ label, error, secureTextEntry, ...inputProps }: TextFieldProps) {
  const { theme } = useTheme();
  const [revealed, setRevealed] = useState(false);
  const masked = secureTextEntry === true;

  return (
    <View style={styles.wrapper}>
      <Text style={[styles.label, { color: theme.textMuted }]}>{label}</Text>

      <View
        style={[
          styles.field,
          {
            backgroundColor: theme.surface,
            borderColor: error ? theme.danger : theme.border,
          },
        ]}>
        <TextInput
          {...inputProps}
          accessibilityLabel={label}
          secureTextEntry={masked && !revealed}
          placeholderTextColor={theme.textMuted}
          style={[styles.input, { color: theme.text }]}
        />

        {masked && (
          <Pressable
            onPress={() => setRevealed((value) => !value)}
            hitSlop={10}
            accessibilityRole="button"
            accessibilityState={{ selected: revealed }}
            accessibilityLabel={revealed ? 'Masquer le mot de passe' : 'Afficher le mot de passe'}>
            <Ionicons
              name={revealed ? 'eye-off-outline' : 'eye-outline'}
              size={20}
              color={theme.textMuted}
            />
          </Pressable>
        )}
      </View>

      <Text style={[styles.error, { color: theme.danger }]} numberOfLines={2}>
        {error ?? ' '}
      </Text>
    </View>
  );
}

const styles = StyleSheet.create({
  wrapper: { gap: spacing.xs },
  label: { fontSize: 13, fontWeight: '600' },
  field: {
    flexDirection: 'row',
    alignItems: 'center',
    gap: spacing.sm,
    minHeight: 50,
    paddingHorizontal: spacing.md,
    borderRadius: radius.md,
    borderWidth: 1,
  },
  input: { flex: 1, fontSize: 16, paddingVertical: spacing.sm },
  error: { fontSize: 12, minHeight: 32 },
});