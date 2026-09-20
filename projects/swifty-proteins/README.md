# Swifty Protein

Visualiseur 3D de ligands du [RCSB Protein Data Bank](https://www.rcsb.org/), en
React Native. Les fichiers `.cif` sont téléchargés depuis RCSB, analysés par un
parseur écrit pour le projet, et rendus en trois dimensions avec three.js.

## Prérequis

- Node.js 20 ou plus
- L'application **Expo Go** sur le téléphone de test
- Le téléphone et l'ordinateur sur le même réseau

## Installation et lancement

```bash
npm install
npx expo start
```

Puis scanner le QR affiché dans le terminal :

- **Android** — depuis Expo Go, qui a son propre scanner
- **iOS** — avec l'application Appareil photo, qui propose ensuite d'ouvrir Expo Go

Si le réseau isole les clients entre eux, passer par un VPN maillé (Tailscale) et
viser `exp://<adresse>:8081`.

## Structure

```
app/              écrans, routage par fichiers (expo-router)
src/auth/         comptes, mots de passe (Argon2id), biométrie
src/ligands/      téléchargement, cache disque, parseur .cif
src/scene/        scène three.js, caméra, modèles, capture
src/chemistry/    couleurs CPK et rayons atomiques
src/media/        encodeur GIF
src/ui/           thème et composants partagés
tools/            génération des icônes
assets/ligands.txt  liste des ligands proposés
```

## Fonctionnement

Un compte est créé sur l'appareil : seule une empreinte Argon2id du mot de passe
est conservée, dans le magasin sécurisé de la plateforme (Keychain sur iOS,
Keystore sur Android). L'écran de connexion réapparaît à chaque lancement et à
chaque retour d'arrière-plan.

Les ligands déjà consultés restent lisibles sans connexion : leur fichier `.cif`
est conservé dans le cache de l'application.

## Limites connues dans Expo Go

- **Icône** — Expo Go affiche la sienne. L'icône du projet est configurée dans
  `app.json` et n'apparaît que dans une application compilée
  (`eas build -p android --profile preview`).
- **Face ID** — indisponible dans Expo Go, qui ne déclare pas
  `NSFaceIDUsageDescription`. Touch ID et la biométrie Android fonctionnent.
- **Comptes** — enregistrés dans le conteneur d'Expo Go ; désinstaller Expo Go
  les efface.

## Développement

```bash
npx tsc --noEmit
```

## Auteurs

Hugo Rischmann et Gregory Marquiset.

Projet scolaire, sans licence d'utilisation : tous droits réservés.

## Crédits

Structures moléculaires fournies par le RCSB Protein Data Bank.
