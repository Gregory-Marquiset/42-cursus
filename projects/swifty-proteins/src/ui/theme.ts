export type ThemeName = 'light' | 'dark';

export type Theme = {
  name: ThemeName;
  background: string;
  surface: string;
  surfaceAlt: string;
  border: string;
  text: string;
  textMuted: string;
  accent: string;
  onAccent: string;
  danger: string;
  success: string;
  scene: string;
};

export const themes: Record<ThemeName, Theme> = {
  light: {
    name: 'light',
    background: '#F4F7FA',
    surface: '#FFFFFF',
    surfaceAlt: '#E9EFF5',
    border: '#D6DFE9',
    text: '#0F1A24',
    textMuted: '#5A6B7D',
    accent: '#0A6FB0',
    onAccent: '#FFFFFF',
    danger: '#C22B2B',
    success: '#2E7D46',
    scene: '#DCE5EE',
  },
  dark: {
    name: 'dark',
    background: '#0B1016',
    surface: '#141C25',
    surfaceAlt: '#1D2833',
    border: '#2A3746',
    text: '#E8EEF4',
    textMuted: '#8A9BAC',
    accent: '#3BA9E8',
    onAccent: '#04121C',
    danger: '#EF6B6B',
    success: '#5EC07E',
    scene: '#070C11',
  },
};

export const spacing = { xs: 4, sm: 8, md: 16, lg: 24, xl: 32 } as const;

export const radius = { sm: 8, md: 14, lg: 22, pill: 999 } as const;