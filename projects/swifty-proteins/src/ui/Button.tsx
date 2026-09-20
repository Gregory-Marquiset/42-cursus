import { ActivityIndicator, Pressable, StyleSheet, Text, View, type ViewStyle } from 'react-native';
import { radius, spacing } from './theme';
import { useTheme } from './ThemeProvider';

type ButtonProps = {
  label: string;
  onPress: () => void;
  variant?: 'primary' | 'secondary';
  busy?: boolean;
  busyLabel?: string;
  disabled?: boolean;
  style?: ViewStyle;
};

export function Button({
  label,
  onPress,
  variant = 'primary',
  busy = false,
  busyLabel,
  disabled = false,
  style,
}: ButtonProps) {
  const { theme } = useTheme();
  const isPrimary = variant === 'primary';
  const inactive = disabled || busy;

  return (
    <Pressable
      onPress={onPress}
      disabled={inactive}
      accessibilityRole="button"
      accessibilityState={{ disabled: inactive, busy }}
      accessibilityLabel={label}
      style={({ pressed }) => [
        styles.base,
        {
          backgroundColor: isPrimary ? theme.accent : 'transparent',
          borderColor: isPrimary ? theme.accent : theme.border,
          opacity: inactive ? 0.5 : pressed ? 0.8 : 1,
        },
        style,
      ]}>
      {busy ? (
        <View style={styles.busy}>
          <ActivityIndicator color={isPrimary ? theme.onAccent : theme.accent} />
          {busyLabel !== undefined && (
            <Text style={[styles.label, { color: isPrimary ? theme.onAccent : theme.text }]}>
              {busyLabel}
            </Text>
          )}
        </View>
      ) : (
        <Text style={[styles.label, { color: isPrimary ? theme.onAccent : theme.text }]}>
          {label}
        </Text>
      )}
    </Pressable>
  );
}

const styles = StyleSheet.create({
  base: {
    minHeight: 50,
    alignItems: 'center',
    justifyContent: 'center',
    paddingHorizontal: spacing.lg,
    borderRadius: radius.md,
    borderWidth: 1,
  },
  label: { fontSize: 16, fontWeight: '600' },
  busy: { flexDirection: 'row', alignItems: 'center', gap: spacing.sm },
});