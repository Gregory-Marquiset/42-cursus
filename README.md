# 42-cursus

*[Version française](README.fr.md)*

All my projects from 42 school's common core in one repository. **One command** opens an
interactive map of the cursus, and every project runs from it in a click. The only thing you
need installed is **Docker**.

```bash
git clone https://github.com/Gregory-Marquiset/42-cursus.git
cd 42-cursus
./cursus            # or: make
```

This opens **http://localhost:4242**: the cursus "holy graph". Click a project to read what it
does and who I built it with, then hit **Run**:

- programs run in a terminal embedded in the page
- graphical projects (FdF, cub3D) open a virtual screen next to it, and the panel lists their controls
- web stacks (Inception, ft_transcendence, Cloud-1) come up with links to open them

## Projects

| Rank | Project | What it is | Stack |
|---|---|---|---|
| 00 | [libft](projects/libft) | My own C library, the base of every later project | C |
| 01 | [ft_printf](projects/ft_printf) | printf reimplemented, bonus flags included | C, variadics |
| 01 | [get_next_line](projects/get_next_line) | Line-by-line reading whatever the buffer size | C |
| 01 | [born2beroot](projects/born2beroot) | Hardened Debian server in a VM (the VM signature) | Debian, LVM, UFW |
| 02 | [push_swap](projects/push_swap) | Sorting with a restricted instruction set, plus the checker | C, algorithms |
| 02 | [minitalk](projects/minitalk) | Client/server messaging over UNIX signals only | C, signals |
| 02 | [FdF](projects/fdf) | Isometric wireframe renderer | C, MiniLibX |
| 03 | [philosophers](projects/philosophers) | Dining philosophers with threads, then processes and semaphores | C, pthreads |
| 03 | [minishell](projects/minishell) | A bash-like shell: parser, AST, pipes, redirections | C |
| 04 | [NetPractice](projects/netpractice) | IP addressing and routing exercises | TCP/IP |
| 04 | [cub3D](projects/cub3d) | Wolfenstein-style raycasting engine | C, MiniLibX |
| 04–05 | [CPP modules](projects/cpp-modules) | The C++ piscine, modules 00 to 09 | C++98 |
| 05 | [webserv](projects/webserv) | Non-blocking HTTP server with CGI | C++98, epoll |
| 05 | [Inception](projects/inception) | Containerised WordPress infrastructure, every image hand-written | Docker |
| 06 | [ft_transcendence](projects/ft_transcendence) | Full microservices web platform | Node, React, Vault, Prometheus |
| 06 | [swifty-proteins](projects/swifty-proteins) | 3D ligand viewer for phones, from the Protein Data Bank (runs from a phone, not from the portal) | React Native, Expo, three.js |
| — | [Cloud-1](projects/cloud-1) | Inception deployed automatically on several servers | Terraform, Ansible |

### Built with

- **minishell** with [Jérôme Portier](https://github.com/jeportie) (jeportie)
- **cub3D** with [Charles-Louis Dutel](https://github.com/Charles-Louis-Dutel) (cdutel)
- **webserv** with [Charles-Louis Dutel](https://github.com/Charles-Louis-Dutel) (cdutel) and
  [Marie Langlois](https://github.com/mlanglois26) (malanglo)
- **ft_transcendence** with [Charles-Louis Dutel](https://github.com/Charles-Louis-Dutel) (cdutel),
  [Lou Briottet](https://github.com/loubrtt) (lobriott),
  [Mathieu Da Cunha](https://github.com/Me-mathix) (mda-cunh) and
  [Liam Zaengel](https://github.com/fliam25) (lzaengel)

The team projects keep their own repositories, with the full history and everyone's commits:
[mcg_webserv](https://github.com/Gregory-Marquiset/mcg_webserv),
[llmcg_transcendence](https://github.com/Gregory-Marquiset/llmcg_transcendence).

## Command line

Everything in the web page is also available from a terminal:

```bash
./cursus menu                                  # the same menu, in the terminal
./cursus libft | ft_printf                     # small demo programs calling the library
./cursus gnl 7 projects/philosophers/philo/src/main.c   # BUFFER_SIZE, file
./cursus push_swap 500                         # sort 500 random numbers, count moves, run the checker
./cursus minitalk "hello"                      # server + client
./cursus philo philo 5 800 200 200 7           # version, then the program's arguments
./cursus minishell
./cursus fdf mars                              # opens a screen on http://localhost:6080
./cursus cub3d bonus
./cursus cpp 09 01 "8 9 * 9 - 9 - 9 - 4 - 1 +" # module, exercise, arguments  -> 42
./cursus webserv                               # http://localhost:1045
./cursus inception                             # https://localhost
./cursus transcendence                         # https://localhost:8001
./cursus cloud-1                               # https://localhost

./cursus status | stop <stack|portal> | logs <stack> | stop-all
./cursus clean                                 # stop everything, remove volumes and images
```

## How it works

```
./cursus ──► portal container (nginx + ttyd, :4242)
               │  page: graph.json + projects.json
               │  web terminal runs ./cursus <project>
               ▼
             host Docker daemon (through its socket)
               ├─ toolchain image: Ubuntu 22.04, clang 12, valgrind, X11 libs,
               │                   Xvfb + noVNC for MiniLibX projects
               └─ docker compose: Inception, ft_transcendence, Cloud-1
```

- Each project page opens its **subject**, the PDF handed out by 42, right in the page.

- **Same compiler as the school.** `cc` and `c++` are clang 12 on Ubuntu 22.04, like 42's
  workstations. Newer clangs add warnings that break the projects' `-Werror`.
- **The portal drives Docker without seeing the host's filesystem.** The repository is mounted
  at the path the Docker daemon knows (`/run/desktop/mnt/host/c/...` on Docker Desktop for
  Windows, the same path elsewhere), so the containers and compose files it starts resolve
  their bind mounts correctly.
- **Real holy graph.** Node positions, states and marks come from my graph on the 42 intranet,
  converted by [`launcher/graph-from-intra.js`](launcher/graph-from-intra.js).
- **Game mode for cub3D.** noVNC only sends absolute pointer positions, which breaks a game that
  re-centres the mouse every frame. The page captures the mouse (Pointer Lock) and sends relative
  moves to a small bridge in the container ([`launcher/input-bridge.py`](launcher/input-bridge.py)),
  which injects them into X with XTest.
- **Secrets are generated, never committed.** Inception's passwords, Cloud-1's `.env` and
  self-signed certificate are created on first run and ignored by git.
- **One stack at a time.** Inception and Cloud-1 both listen on 443, so starting one stops
  the other.

### Changes needed to run outside the school

The code is what was submitted for evaluation. Anything needed to run it elsewhere lives in
[`launcher/`](launcher) as compose overrides or wrappers, not in the projects:

- Inception: the subject requires volumes bound to `/home/<login>/data`, replaced by named volumes.
- ft_transcendence: `backup` (a one-shot service) is left out of `up`, and Adminer's healthcheck
  follows `adminer:latest`, which renamed its PHP binary after the project was graded.
- push_swap: the last commit on vogsphere depends on a version of my libft that was never
  committed; this repository holds the previous commit, which is complete.
- Libraries (libft, ft_printf, get_next_line) have no `main`: small demo programs in
  [`launcher/demos/`](launcher/demos) call them.

## Deployment

The portal also runs permanently on a VM in my Proxmox homelab, behind a password:
[gmarquis-42.duckdns.org](https://gmarquis-42.duckdns.org).

The web terminal runs code, so the machine is treated accordingly:

- **Rootless Docker** — the daemon runs under a dedicated account with no root access to the VM.
  The low ports some projects need are opened through `net.ipv4.ip_unprivileged_port_start`,
  not by granting privileges.
- **One way in** — the firewall only accepts the portal's port from the reverse proxy, which
  terminates TLS and requires authentication.
- **The launcher does not trust what it is given** — no `eval`, and every argument (module,
  exercise, map, config) must match a file in the repository.
- **Restarts on its own** — a user systemd service brings the portal back at boot.

```bash
CURSUS_BIND=0.0.0.0 CURSUS_NO_BROWSER=1 ./cursus     # listen for a reverse proxy, no browser
```

## Requirements

- Docker with the compose plugin (Docker Desktop on Windows and macOS)
- bash: Linux, macOS, WSL, or Git Bash on Windows

Ports: 4242 (portal), 6080-6081 (virtual screen, game mode), 1045 (webserv), 443, 9443, 21 and 30000-30009
(Inception), 80 and 443 (Cloud-1), 8000, 8001, 8080, 3000, 9090 and 8200 (ft_transcendence).
