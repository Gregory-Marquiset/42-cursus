import * as LocalAuthentication from 'expo-local-authentication';

export type BiometricAvailability =
  | { usable: true; label: string }
  | { usable: false; reason: string };

export type BiometricOutcome =
  | { ok: true }
  | {
      ok: false;
      message: string;
      settings: boolean;
      permanent: boolean;
    };

const ERRORS: Record<string, { message: string; settings?: boolean; permanent?: boolean }> = {
  missing_usage_description: {
    message:
      "Face ID n'est pas accessible depuis Expo Go, qui n'en déclare pas l'usage. Il fonctionne dans une version compilée de l'application. Connectez-vous avec votre mot de passe.",
    permanent: true,
  },
  user_cancel: { message: 'Authentification annulée.' },
  app_cancel: { message: "L'authentification a été interrompue par l'application." },
  system_cancel: { message: "L'authentification a été interrompue par le système." },
  user_fallback: { message: 'Connectez-vous avec votre identifiant et votre mot de passe.' },
  authentication_failed: { message: 'Visage non reconnu. Veuillez réessayer.' },
  lockout: { message: 'Trop de tentatives échouées. Utilisez votre mot de passe.' },
  lockout_permanent: {
    message: 'Biométrie verrouillée. Déverrouillez votre appareil avec son code, puis réessayez.',
  },
  not_enrolled: {
    message: "Aucune donnée biométrique n'est enregistrée sur cet appareil.",
    settings: true,
  },
  not_available: {
    message:
      "La biométrie est indisponible pour cette application. Vérifiez qu'elle y est autorisée dans les réglages.",
    settings: true,
  },
  passcode_not_set: { message: "Aucun code n'est configuré sur cet appareil.", settings: true },
  timeout: { message: 'La demande a expiré. Veuillez réessayer.' },
  no_space: { message: "L'appareil manque d'espace pour traiter la demande." },
  unable_to_process: { message: "La demande n'a pas pu être traitée. Veuillez réessayer." },
  invalid_context: { message: 'La demande a été invalidée. Veuillez réessayer.' },
  unknown: {
    message:
      "La biométrie n'a pas répondu. Vérifiez qu'elle est autorisée pour cette application dans les réglages.",
    settings: true,
  },
};

function describeSensor(types: LocalAuthentication.AuthenticationType[]): string {
  const { FACIAL_RECOGNITION, FINGERPRINT, IRIS } = LocalAuthentication.AuthenticationType;
  if (types.includes(FACIAL_RECOGNITION)) return 'Face ID';
  if (types.includes(FINGERPRINT)) return 'Touch ID';
  if (types.includes(IRIS)) return "la reconnaissance de l'iris";
  return 'la biométrie';
}

export async function getBiometricAvailability(): Promise<BiometricAvailability> {
  if (!(await LocalAuthentication.hasHardwareAsync())) {
    return { usable: false, reason: "Cet appareil ne dispose pas de capteur biométrique." };
  }
  if (!(await LocalAuthentication.isEnrolledAsync())) {
    return { usable: false, reason: "Aucune donnée biométrique n'est enregistrée sur cet appareil." };
  }
  return { usable: true, label: describeSensor(await LocalAuthentication.supportedAuthenticationTypesAsync()) };
}

export async function promptBiometric(label: string): Promise<BiometricOutcome> {
  const result = await LocalAuthentication.authenticateAsync({
    promptMessage: `Déverrouiller avec ${label}`,
    cancelLabel: 'Utiliser le mot de passe',
    disableDeviceFallback: true,
  });
  if (result.success) return { ok: true };

  const known = ERRORS[result.error];
  return known
    ? {
        ok: false,
        message: known.message,
        settings: known.settings === true,
        permanent: known.permanent === true,
      }
    : {
        ok: false,
        message: `Authentification impossible (${result.error}).`,
        settings: true,
        permanent: false,
      };
}