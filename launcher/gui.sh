#!/bin/sh
# Ecran virtuel pour les projets MiniLibX (fdf, cub3d) : Xvfb + VNC, affiche dans le navigateur
# par noVNC (port 6080). Le port 6081 recoit les entrees du "mode jeu" (voir input-bridge.py).
# Usage : gui.sh <commande...>
Xvfb :0 -screen 0 1280x800x24 -nolisten tcp >/dev/null 2>&1 &
sleep 1
x11vnc -display :0 -nopw -forever -shared -quiet -repeat >/dev/null 2>&1 &
websockify --web /usr/share/novnc 6080 localhost:5900 >/dev/null 2>&1 &
python3 "$(dirname "$0")/input-bridge.py" &
websockify 6081 localhost:5901 >/dev/null 2>&1 &
export DISPLAY=:0
exec "$@"
