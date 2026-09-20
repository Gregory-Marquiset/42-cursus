"""
Génère les icônes de l'application à partir d'un motif boules-et-bâtons.

L'icône reprend le sujet de l'application : un fragment moléculaire aux
couleurs CPK réelles (carbone gris, oxygène rouge, azote bleu, hydrogène
blanc) sur le fond sombre de l'application. Le dessin est effectué à quatre
fois la taille finale puis réduit, ce qui donne des bords lisses sans
dépendre d'une bibliothèque de rendu vectoriel.

    python3 tools/make-icons.py
"""

from PIL import Image, ImageDraw

SCALE = 4  # suréchantillonnage pour l'anticrénelage
BACKGROUND = (11, 16, 22, 255)  # #0B1016, le fond sombre de l'application

# Couleurs CPK, identiques à src/chemistry/elements.ts
CARBON = (154, 163, 172, 255)  # éclairci pour tenir sur fond sombre
OXYGEN = (255, 13, 13, 255)
NITROGEN = (80, 110, 250, 255)
HYDROGEN = (245, 248, 252, 255)
BOND = (122, 134, 148, 255)

# Fragment : un carbone central relié à trois voisins.
# Coordonnées exprimées en fraction du côté, pour être indépendantes de la taille.
CENTER = (0.50, 0.53)
NEIGHBOURS = [
    ((0.50, 0.235), OXYGEN, 0.088),
    ((0.245, 0.695), NITROGEN, 0.088),
    ((0.755, 0.695), HYDROGEN, 0.070),
]
CARBON_RADIUS = 0.105
BOND_WIDTH = 0.036


def draw_molecule(size, *, background, tint=None, inset=1.0):
    """Dessine le motif. `tint` remplace toutes les couleurs (icône monochrome)."""
    canvas = size * SCALE
    image = Image.new("RGBA", (canvas, canvas), background)
    draw = ImageDraw.Draw(image)

    def point(fraction_xy):
        # `inset` resserre le motif vers le centre, pour la zone sûre d'Android.
        x = (0.5 + (fraction_xy[0] - 0.5) * inset) * canvas
        y = (0.5 + (fraction_xy[1] - 0.5) * inset) * canvas
        return x, y

    center = point(CENTER)
    width = max(1, int(BOND_WIDTH * canvas * inset))

    # Les liaisons d'abord : les sphères doivent les recouvrir.
    for position, colour, _ in NEIGHBOURS:
        end = point(position)
        middle = ((center[0] + end[0]) / 2, (center[1] + end[1]) / 2)
        # Deux moitiés colorées par leur atome, comme dans la vue 3D.
        draw.line([center, middle], fill=tint or BOND, width=width)
        draw.line([middle, end], fill=tint or colour, width=width)
        for cap in (center, middle, end):
            draw.ellipse(
                [cap[0] - width / 2, cap[1] - width / 2, cap[0] + width / 2, cap[1] + width / 2],
                fill=tint or (BOND if cap is center else colour),
            )

    def sphere(position, colour, radius_fraction):
        x, y = point(position)
        r = radius_fraction * canvas * inset
        draw.ellipse([x - r, y - r, x + r, y + r], fill=tint or colour)

    for position, colour, radius in NEIGHBOURS:
        sphere(position, colour, radius)
    sphere(CENTER, CARBON, CARBON_RADIUS)

    return image.resize((size, size), Image.LANCZOS)


def write(path, image):
    image.save(path)
    print(f"  {path}")


if __name__ == "__main__":
    print("Génération des icônes :")
    write("assets/icon.png", draw_molecule(1024, background=BACKGROUND))
    write("assets/favicon.png", draw_molecule(196, background=BACKGROUND))
    # Le splash pose le motif sur un fond transparent : la couleur vient d'app.json.
    write("assets/splash-icon.png", draw_molecule(512, background=(0, 0, 0, 0)))
    # Android découpe l'avant-plan : le motif doit tenir dans les 66 % centraux.
    write("assets/android-icon-foreground.png", draw_molecule(1024, background=(0, 0, 0, 0), inset=0.62))
    write("assets/android-icon-background.png", Image.new("RGBA", (1024, 1024), BACKGROUND))
    write(
        "assets/android-icon-monochrome.png",
        draw_molecule(1024, background=(0, 0, 0, 0), tint=(255, 255, 255, 255), inset=0.62),
    )
