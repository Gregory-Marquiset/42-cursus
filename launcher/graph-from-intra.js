// Convertit les donnees du holy graph de l'intra en graph.json pour le portail.
//
//   node launcher/graph-from-intra.js ~/Downloads/holy-graph.json
//
// Le fichier d'entree se recupere sur https://projects.intra.42.fr/projects/graph?login=<login> :
// onglet Network des devtools, la requete JSON qui contient les projets (project_data).
// On garde les positions, l'etat et la note tels quels ; `by` donne le trace de chaque lien.

const fs = require("fs");
const path = require("path");

// slug intra -> projet lancable de ce depot (voir www/projects.json)
const RUNNABLE = {
  "42cursus-libft": ["libft"],
  "42cursus-ft_printf": ["ft_printf"],
  "42cursus-get_next_line": ["get_next_line"],
  "born2beroot": ["born2beroot"],
  "42cursus-push_swap": ["push_swap"],
  "minitalk": ["minitalk"],
  "42cursus-fdf": ["fdf"],
  "42cursus-philosophers": ["philosophers"],
  "42cursus-minishell": ["minishell"],
  "netpractice": ["netpractice"],
  "cub3d": ["cub3d"],
  "webserv": ["webserv"],
  "inception": ["inception"],
  "ft_transcendence": ["ft_transcendence"],
  "42cursus-cloud-1": ["cloud-1"],
};
// les dix modules C++ pointent vers le meme projet, chacun sur son module
for (let i = 0; i <= 9; i++) {
  RUNNABLE[`cpp-module-0${i}`] = ["cpp", ["cpp", `0${i}`]];
}

const input = process.argv[2];
if (!input) {
  console.error("usage: node graph-from-intra.js <holy-graph.json>");
  process.exit(1);
}
const intra = JSON.parse(fs.readFileSync(input, "utf8"));

// Les dix modules C++ se chevauchent sur le graph : ils deviennent deux groupes, places au
// centre de leurs membres, comme les piscines de l'intra.
const GROUPS = [
  { id: "cpp-00-04", name: "CPP 00–04", is: (s) => /^cpp-module-0[0-4]$/.test(s), project: "cpp", args: ["cpp"] },
  { id: "cpp-05-09", name: "CPP 05–09", is: (s) => /^cpp-module-0[5-9]$/.test(s), project: "cpp", args: ["cpp"] },
];

// projets sans position (x = y = 0) : pas places sur le graph de l'intra
// projets echoues : Greg ne veut pas les afficher
const placed = intra.filter((p) => (p.x || p.y) && p.state !== "fail");
const groupOf = (p) => GROUPS.find((g) => g.is(p.slug));

const nodes = [];
for (const p of placed) {
  if (groupOf(p)) continue;
  const [project, args] = RUNNABLE[p.slug] || [];
  nodes.push({
    id: p.id,
    name: p.name,
    slug: p.slug,
    kind: p.kind,
    state: p.state,
    x: p.x,
    y: p.y,
    ...(p.final_mark != null ? { mark: p.final_mark } : {}),
    ...(project ? { project } : {}),
    ...(args ? { args } : {}),
  });
}
const groupId = new Map();        // id d'origine -> id du groupe
for (const g of GROUPS) {
  const members = placed.filter((p) => g.is(p.slug));
  if (!members.length) continue;
  members.forEach((m) => groupId.set(m.id, g.id));
  const avg = (f) => Math.round(members.reduce((a, m) => a + f(m), 0) / members.length);
  const marks = members.map((m) => m.final_mark).filter((m) => m != null);
  nodes.push({
    id: g.id, name: g.name, slug: g.id, kind: "piscine",
    state: members.every((m) => m.state === "done") ? "done" : members[0].state,
    x: avg((m) => m.x), y: avg((m) => m.y),
    ...(marks.length ? { mark: Math.round(marks.reduce((a, b) => a + b) / marks.length) } : {}),
    project: g.project, args: g.args,
  });
}

// L'intra affiche le CV collaboratif, une fois valide, sur le dernier anneau du tronc commun,
// alors que l'export le laisse a l'exterieur. On le remet ou l'intra le dessine.
const PINNED = { "42_collaborative_resume": { ring: 6, angle: -80 } };

// un groupe tombe au milieu de ses membres, parfois sur un voisin : on l'ecarte du centre
// du graph jusqu'a ce qu'il ait la place
const libft = nodes.find((n) => n.slug === "42cursus-libft") || nodes[0];
for (const g of nodes.filter((n) => GROUPS.some((x) => x.id === n.id))) {
  const others = nodes.filter((n) => n !== g);
  const near = () => Math.min(...others.map((n) => Math.hypot(n.x - g.x, n.y - g.y)));
  const a = Math.atan2(g.y - libft.y, g.x - libft.x);
  for (let step = 0; step < 40 && near() < 150; step++) {
    g.x = Math.round(g.x + 15 * Math.cos(a));
    g.y = Math.round(g.y + 15 * Math.sin(a));
  }
}

const byId = new Map(nodes.map((n) => [n.id, n]));
const resolve = (id) => (groupId.has(id) ? byId.get(groupId.get(id)) : byId.get(id));

// `by` porte le trace du lien : on le garde tel quel, sauf si une extremite a ete regroupee,
// auquel cas le trace d'origine ne mene plus au bon endroit et une droite suffit
const idByProject = new Map(intra.map((p) => [p.project_id, p.id]));
const edges = [];
const seen = new Set();
for (const p of placed) {
  for (const link of p.by || []) {
    const parentId = idByProject.get(link.parent_id);
    const parent = resolve(parentId), child = resolve(p.id);
    // parent connu mais absent du graph : il a ete retire (projet echoue), le lien part avec lui
    if (parentId !== undefined && !parent) continue;
    if (!child || (parent && parent.id === child.id)) continue;
    const key = (parent ? parent.id : "?" + link.parent_id) + ">" + child.id;
    if (seen.has(key)) continue;
    seen.add(key);
    // une extremite regroupee : le trace d'origine ne mene plus au bon endroit, une droite suffit
    const moved = groupId.has(p.id) || groupId.has(parentId);
    if (moved && !parent) continue;
    edges.push({
      ...(parent ? { from: parent.id } : {}),
      to: child.id,
      points: moved ? [[parent.x, parent.y], [child.x, child.y]] : link.points,
      done: !!parent && parent.state === "done" && child.state === "done",
    });
  }
}

// Les anneaux de l'intra : les projets d'un meme rang sont a la meme distance de Libft.
// On les retrouve en groupant les distances, ce qui evite de les coder en dur.
const center = nodes.find((n) => n.slug === "42cursus-libft") || nodes[0];
const dist = (n) => Math.hypot(n.x - center.x, n.y - center.y);
const rings = [];
for (const r of nodes.map(dist).sort((a, b) => a - b)) {
  if (r < 50 || r > 1010) continue;                    // le centre, puis au-dela du tronc commun
  const last = rings[rings.length - 1];
  if (last && r - last[last.length - 1] < 60) last.push(r);
  else rings.push([r]);
}
const ringRadii = rings.map((g) => Math.round(g.reduce((a, b) => a + b) / g.length));
// Le cercle du tronc commun : les branches d'apres-tronc-commun y prennent racine, donc son rayon
// se lit dans les traces eux-memes — a l'extremite des liens qui ne partent d'aucun projet.
const roots = [];
for (const p of placed) {
  for (const link of p.by || []) {
    if (idByProject.has(link.parent_id) || !link.points) continue;
    for (const pt of link.points) {
      const r = Math.hypot(pt[0] - center.x, pt[1] - center.y);
      if (Math.hypot(pt[0] - p.x, pt[1] - p.y) > 1 && r > 900 && r < 1100) roots.push(r);
    }
  }
}
roots.sort((a, b) => a - b);
const core = roots.length ? Math.round(roots[Math.floor(roots.length / 2)]) : 1000;

for (const [slug, at] of Object.entries(PINNED)) {
  const n = nodes.find((x) => x.slug === slug);
  if (!n || !ringRadii[at.ring - 1]) continue;
  const r = ringRadii[at.ring - 1], a = (at.angle * Math.PI) / 180;
  n.x = Math.round(center.x + r * Math.cos(a));
  n.y = Math.round(center.y + r * Math.sin(a));
  for (let i = edges.length - 1; i >= 0; i--) {
    const e = edges[i];
    if (e.to !== n.id && e.from !== n.id) continue;
    // l'amorce vers le cercle n'a plus lieu d'etre : le projet est maintenant dessus
    if (!e.from || !e.to) { edges.splice(i, 1); continue; }
    if (e.to === n.id) e.points = [e.points[0], [n.x, n.y]];
    else e.points = [[n.x, n.y], e.points[e.points.length - 1]];
  }
}

const xs = nodes.map((n) => n.x), ys = nodes.map((n) => n.y);
const out = {
  center: { x: center.x, y: center.y },
  rings: ringRadii,
  core,
  _comment: "Genere par launcher/graph-from-intra.js a partir du holy graph de l'intra 42",
  bounds: { x0: Math.min(...xs), y0: Math.min(...ys), x1: Math.max(...xs), y1: Math.max(...ys) },
  nodes,
  edges,
};

const dest = path.join(__dirname, "portal", "www", "graph.json");
fs.writeFileSync(dest, JSON.stringify(out, null, 1) + "\n");
console.log(`${nodes.length} projets, ${edges.length} liens -> ${dest}`);
console.log("lancables :", nodes.filter((n) => n.project).length);
