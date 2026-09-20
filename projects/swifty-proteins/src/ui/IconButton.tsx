import { Ionicons } from '@expo/vector-icons';
import { Pressable, StyleSheet, type ViewStyle } from 'react-native';
import { radius } from './theme';
import { useTheme } from './ThemeProvider';

type IconButtonProps = {
  name: keyof typeof Ionicons.glyphMap;
  label: string;
  onPress: () => void;
  active?: boolean;
  tone?: 'neutral' | 'accent' | 'danger';
  variant?: 'plain' | 'filled';
  disabled?: boolean;
  style?: ViewStyle;
};

const SIZE = 38;

export function IconButton({
  name,
  label,
  onPress,
  active = false,
  tone = 'neutral',
  variant = 'plain',
  disabled = false,
  style,
}: IconButtonProps) {
  const { theme } = useTheme();
  const filled = variant === 'filled';

  const foreground = disabled
    ? theme.textMuted
    : active
      ? filled
        ? theme.onAccent
        : theme.accent
      : tone === 'accent'
        ? theme.accent
        : tone === 'danger'
          ? theme.danger
          : theme.text;

  return (
    <Pressable
      onPress={onPress}
      disabled={disabled}
      accessibilityRole="button"
      accessibilityLabel={label}
      accessibilityState={{ disabled, selected: active }}
      hitSlop={6}
      style={({ pressed }) => [
        styles.base,
        filled && {
          backgroundColor: active ? theme.accent : theme.surface,
          borderColor: active ? theme.accent : theme.border,
          borderWidth: StyleSheet.hairlineWidth,
        },
        { opacity: disabled ? 0.45 : pressed ? 0.55 : 1 },
        style,
      ]}>
      <Ionicons name={name} size={19} color={foreground} />
    </Pressable>
  );
}

const styles = StyleSheet.create({
  base: {
    width: SIZE,
    height: SIZE,
    alignItems: 'center',
    justifyContent: 'center',
    borderRadius: radius.pill,
  },
});