import { Modal, Platform, Pressable, ScrollView, StyleSheet, Text, View } from 'react-native';
import { useCallback, useRef } from 'react';
import { useSafeAreaInsets } from 'react-native-safe-area-context';
import { radius, spacing } from './theme';
import { useTheme } from './ThemeProvider';

export type ActionSheetOption = {
  label: string;
  hint?: string;
  onPress: () => void;
};

type ActionSheetProps = {
  visible: boolean;
  title: string;
  options: ActionSheetOption[];
  onClose: () => void;
};

export function ActionSheet({ visible, title, options, onClose }: ActionSheetProps) {
  const { theme } = useTheme();
  const insets = useSafeAreaInsets();
  const pending = useRef<(() => void) | null>(null);

  const runPending = useCallback(() => {
    const action = pending.current;
    pending.current = null;
    action?.();
  }, []);

  const choose = useCallback(
    (action: () => void) => {
      pending.current = action;
      onClose();
      if (Platform.OS !== 'ios') runPending();
    },
    [onClose, runPending],
  );

  return (
    <Modal
      visible={visible}
      transparent
      animationType="fade"
      onRequestClose={onClose}
      onDismiss={Platform.OS === 'ios' ? runPending : undefined}
      statusBarTranslucent>
      <Pressable
        style={styles.backdrop}
        accessibilityRole="button"
        accessibilityLabel="Fermer le menu"
        onPress={onClose}>
        <Pressable
          style={[
            styles.sheet,
            {
              backgroundColor: theme.surface,
              borderColor: theme.border,
              paddingBottom: insets.bottom + spacing.md,
            },
          ]}
          onPress={() => {}}>
          <Text style={[styles.title, { color: theme.textMuted }]}>{title}</Text>

          <ScrollView bounces={false}>
            {options.map((option) => (
              <Pressable
                key={option.label}
                accessibilityRole="button"
                accessibilityLabel={option.label}
                accessibilityHint={option.hint}
                onPress={() => choose(option.onPress)}
                style={({ pressed }) => [
                  styles.option,
                  { borderColor: theme.border, opacity: pressed ? 0.6 : 1 },
                ]}>
                <Text style={[styles.optionLabel, { color: theme.text }]}>{option.label}</Text>
                {option.hint !== undefined && (
                  <Text style={[styles.optionHint, { color: theme.textMuted }]}>{option.hint}</Text>
                )}
              </Pressable>
            ))}
          </ScrollView>

          <Pressable
            accessibilityRole="button"
            accessibilityLabel="Annuler"
            onPress={onClose}
            style={({ pressed }) => [
              styles.cancel,
              { borderColor: theme.border, opacity: pressed ? 0.6 : 1 },
            ]}>
            <Text style={[styles.cancelLabel, { color: theme.text }]}>Annuler</Text>
          </Pressable>
        </Pressable>
      </Pressable>
    </Modal>
  );
}

const styles = StyleSheet.create({
  backdrop: {
    flex: 1,
    justifyContent: 'flex-end',
    backgroundColor: 'rgba(0, 0, 0, 0.55)',
  },
  sheet: {
    borderTopLeftRadius: radius.md,
    borderTopRightRadius: radius.md,
    borderWidth: 1,
    paddingHorizontal: spacing.md,
    paddingTop: spacing.md,
    gap: spacing.xs,
    maxHeight: '80%',
  },
  title: { fontSize: 13, fontWeight: '600', paddingHorizontal: spacing.xs },
  option: {
    minHeight: 56,
    justifyContent: 'center',
    paddingVertical: spacing.sm,
    paddingHorizontal: spacing.xs,
    borderBottomWidth: StyleSheet.hairlineWidth,
  },
  optionLabel: { fontSize: 16, fontWeight: '600' },
  optionHint: { fontSize: 13, marginTop: 2 },
  cancel: {
    minHeight: 50,
    alignItems: 'center',
    justifyContent: 'center',
    marginTop: spacing.sm,
    borderRadius: radius.md,
    borderWidth: 1,
  },
  cancelLabel: { fontSize: 16, fontWeight: '600' },
});