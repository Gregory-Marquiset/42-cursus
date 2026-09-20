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

// les projets sans position (x = y = 0) ne sont pas places sur le graph de l'intra : on les ecarte
const placed = intra.filter((p) => p.x || p.y);
const byProjectId = new Map(placed.map((p) => [p.project_id, p]));
const nodes = placed.map((p) => {
  const [project, args] = RUNNABLE[p.slug] || [];
  return {
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
  };
});

// `by` porte deja le trace du lien : on ne recalcule rien, on garde les points de l'intra
const edges = [];
for (const p of placed) {
  for (const link of p.by || []) {
    const parent = byProjectId.get(link.parent_id);
    edges.push({
      from: parent ? parent.id : null,
      to: p.id,
      points: link.points,
      done: p.state === "done" && parent && parent.state === "done",
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
const core = Math.round(Math.max(...nodes.map(dist).filter((r) => r <= 1010)) + 45);

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
