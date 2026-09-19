#!/bin/sh
# Ecran virtuel pour les projets MiniLibX (fdf, cub3d) : Xvfb + VNC, affiche dans le navigateur par noVNC
# Usage : gui.sh <commande...>   ->  http://localhost:6080
Xvfb :0 -screen 0 1280x800x24 -nolisten tcp >/dev/null 2>&1 &
sleep 1
x11vnc -display :0 -nopw -forever -shared -quiet >/dev/null 2>&1 &
websockify --web /usr/share/novnc 6080 localhost:5900 >/dev/null 2>&1 &
export DISPLAY=:0
exec "$@"
