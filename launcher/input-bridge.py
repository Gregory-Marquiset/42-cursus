"""Pont d'entree du "mode jeu" : recoit des evenements souris relatifs et clavier, les injecte
dans l'ecran virtuel par XTest.

noVNC n'envoie que des positions absolues. Un jeu qui recentre le pointeur a chaque image
(cub3d : mlx_mouse_move) lit alors l'ecart entre le centre et la vraie position du curseur du
navigateur, et tourne sans fin. La page capture la souris (Pointer Lock) et envoie des
deplacements relatifs : le jeu recoit ce qu'il attend.

Protocole, une commande par ligne (websockify relaie le websocket vers ce port TCP) :
  m <dx> <dy>          deplacement relatif
  k <1|0> <keysym>     touche enfoncee / relachee (nom X : w, Left, space...)
  b <1|0> <bouton>     bouton de souris
"""
import ctypes
import socketserver

x11 = ctypes.CDLL("libX11.so.6")
xtst = ctypes.CDLL("libXtst.so.6")
x11.XOpenDisplay.restype = ctypes.c_void_p
x11.XOpenDisplay.argtypes = [ctypes.c_char_p]
x11.XStringToKeysym.restype = ctypes.c_ulong
x11.XStringToKeysym.argtypes = [ctypes.c_char_p]
x11.XKeysymToKeycode.restype = ctypes.c_ubyte
x11.XKeysymToKeycode.argtypes = [ctypes.c_void_p, ctypes.c_ulong]
x11.XFlush.argtypes = [ctypes.c_void_p]
xtst.XTestFakeRelativeMotionEvent.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_ulong]
xtst.XTestFakeKeyEvent.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.c_int, ctypes.c_ulong]
xtst.XTestFakeButtonEvent.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.c_int, ctypes.c_ulong]

display = x11.XOpenDisplay(b":0")


def handle(line):
    parts = line.split()
    if len(parts) != 3:
        return
    kind, a, b = parts
    if kind == "m":
        xtst.XTestFakeRelativeMotionEvent(display, int(a), int(b), 0)
    elif kind == "k":
        code = x11.XKeysymToKeycode(display, x11.XStringToKeysym(b.encode()))
        if code:
            xtst.XTestFakeKeyEvent(display, code, a == "1", 0)
    elif kind == "b":
        xtst.XTestFakeButtonEvent(display, int(b), a == "1", 0)
    x11.XFlush(display)


class Handler(socketserver.StreamRequestHandler):
    def handle(self):
        for raw in self.rfile:
            try:
                handle(raw.decode(errors="ignore"))
            except ValueError:
                pass


# Un seul client a la fois : Xlib n'est pas thread-safe sans XInitThreads
socketserver.TCPServer.allow_reuse_address = True
with socketserver.TCPServer(("127.0.0.1", 5901), Handler) as server:
    server.serve_forever()
