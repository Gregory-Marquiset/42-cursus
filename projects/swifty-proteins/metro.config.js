const { getDefaultConfig } = require('expo/metro-config');

const config = getDefaultConfig(__dirname);

// `ligands.txt` est le fichier fourni par le sujet : il est embarqué tel quel
// et lu au runtime, il doit donc être traité comme un asset, pas comme du code.
config.resolver.assetExts.push('txt');

module.exports = config;
