#!/bin/sh
# CURSUS_ROOT : le depot, monte au chemin que le daemon Docker connait (les bind mounts lances
# depuis ce conteneur sont resolus par le daemon, pas par le conteneur)
mkdir -p /portal
ln -sfn "$CURSUS_ROOT/launcher/portal/www" /portal/www
ln -sfn "$CURSUS_ROOT/projects" /portal/projects      # pour servir les sujets (PDF)
nginx
# -a : la page passe la commande en parametres d'URL (?arg=philo&arg=philo)
exec ttyd -p 7681 -i lo -b /term -W -a -O -t fontSize=14 -t 'theme={"background":"#0b1020"}' \
    -t titleFixed=42-cursus bash "$CURSUS_ROOT/cursus" web
