# 42-cursus

*[English version](README.md)*

Tous mes projets du tronc commun de l'école 42 dans un seul dépôt. **Une commande** ouvre une
carte interactive du cursus, et chaque projet se lance depuis cette carte en un clic. La seule
chose à installer est **Docker**.

```bash
git clone https://github.com/Gregory-Marquiset/42-cursus.git
cd 42-cursus
./cursus            # ou : make
```

La commande ouvre **http://localhost:4242**, le « holy graph » du cursus. Un clic sur un projet
affiche ce qu'il fait et avec qui je l'ai réalisé ; le bouton **Lancer** l'exécute :

- les programmes tournent dans un terminal intégré à la page
- les projets graphiques (FdF, cub3D) ouvrent un écran virtuel à côté
- les stacks web (Inception, ft_transcendence, Cloud-1) démarrent, avec les liens pour les ouvrir

## Projets

| Rang | Projet | Ce que c'est | Stack |
|---|---|---|---|
| 00 | [libft](projects/libft) | Ma bibliothèque C, la base de tous les projets suivants | C |
| 01 | [ft_printf](projects/ft_printf) | printf réécrite, drapeaux bonus compris | C, variadiques |
| 01 | [get_next_line](projects/get_next_line) | Lecture ligne par ligne, quelle que soit la taille du buffer | C |
| 01 | [born2beroot](projects/born2beroot) | Serveur Debian durci en VM (la signature de la VM) | Debian, LVM, UFW |
| 02 | [push_swap](projects/push_swap) | Tri avec un jeu d'instructions limité, et le checker | C, algorithmique |
| 02 | [minitalk](projects/minitalk) | Messages client/serveur par signaux UNIX uniquement | C, signaux |
| 02 | [FdF](projects/fdf) | Rendu fil de fer en projection isométrique | C, MiniLibX |
| 03 | [philosophers](projects/philosophers) | Le dîner des philosophes : threads, puis processus et sémaphores | C, pthreads |
| 03 | [minishell](projects/minishell) | Un shell façon bash : parseur, AST, pipes, redirections | C |
| 04 | [NetPractice](projects/netpractice) | Exercices d'adressage IP et de routage | TCP/IP |
| 04 | [cub3D](projects/cub3d) | Moteur de raycasting façon Wolfenstein | C, MiniLibX |
| 04–05 | [Modules C++](projects/cpp-modules) | La piscine C++, modules 00 à 09 | C++98 |
| 05 | [webserv](projects/webserv) | Serveur HTTP non bloquant avec CGI | C++98, epoll |
| 05 | [Inception](projects/inception) | Infrastructure WordPress en conteneurs, chaque image écrite à la main | Docker |
| 06 | [ft_transcendence](projects/ft_transcendence) | Plateforme web complète en microservices | Node, React, Vault, Prometheus |
| — | [Cloud-1](projects/cloud-1) | Inception déployé automatiquement sur plusieurs serveurs | Terraform, Ansible |

### Réalisés avec

- **minishell** avec [Jérôme Portier](https://github.com/jeportie) (jeportie)
- **cub3D** avec [Charles-Louis Dutel](https://github.com/Charles-Louis-Dutel) (cdutel)
- **webserv** avec [Charles-Louis Dutel](https://github.com/Charles-Louis-Dutel) (cdutel) et
  [Marie Langlois](https://github.com/mlanglois26) (malanglo)
- **ft_transcendence** avec [Charles-Louis Dutel](https://github.com/Charles-Louis-Dutel) (cdutel),
  [Lou Briottet](https://github.com/loubrtt) (lobriott),
  [Mathieu Da Cunha](https://github.com/Me-mathix) (mda-cunh) et
  [Liam Zaengel](https://github.com/fliam25) (lzaengel)

Les projets d'équipe gardent leur propre dépôt, avec tout l'historique et les commits de chacun :
[mcg_webserv](https://github.com/Gregory-Marquiset/mcg_webserv),
[llmcg_transcendence](https://github.com/Gregory-Marquiset/llmcg_transcendence).

## En ligne de commande

Tout ce que fait la page existe aussi depuis un terminal :

```bash
./cursus menu                                  # le meme menu, dans le terminal
./cursus libft | ft_printf                     # petits programmes de demo qui appellent la bibliotheque
./cursus gnl 7 projects/philosophers/philo/src/main.c   # BUFFER_SIZE, fichier
./cursus push_swap 500                         # trie 500 nombres aleatoires, compte les coups, checker
./cursus minitalk "salut"                      # serveur + client
./cursus philo philo 5 800 200 200 7           # version, puis arguments du programme
./cursus minishell
./cursus fdf mars                              # ouvre un ecran sur http://localhost:6080
./cursus cub3d bonus
./cursus cpp 09 01 "8 9 * 9 - 9 - 9 - 4 - 1 +" # module, exercice, arguments  -> 42
./cursus webserv                               # http://localhost:1045
./cursus inception                             # https://localhost
./cursus transcendence                         # https://localhost:8001
./cursus cloud-1                               # https://localhost

./cursus status | stop <stack|portal> | logs <stack> | stop-all
./cursus clean                                 # arrete tout, supprime volumes et images
```

## Fonctionnement

```
./cursus ──► conteneur portail (nginx + ttyd, :4242)
               │  page : graph.json + projects.json
               │  le terminal web execute ./cursus <projet>
               ▼
             daemon Docker de la machine (par son socket)
               ├─ image outils : Ubuntu 22.04, clang 12, valgrind, bibliotheques X11,
               │                 Xvfb + noVNC pour les projets MiniLibX
               └─ docker compose : Inception, ft_transcendence, Cloud-1
```

- **Le compilateur de l'école.** `cc` et `c++` sont clang 12 sous Ubuntu 22.04, comme sur les
  postes de 42. Les clang plus récents ajoutent des warnings qui cassent les `-Werror` des projets.
- **Le portail pilote Docker sans voir les fichiers de la machine.** Le dépôt y est monté au
  chemin que connaît le daemon (`/run/desktop/mnt/host/c/...` avec Docker Desktop sous Windows,
  le même chemin ailleurs) : les conteneurs et les fichiers compose qu'il lance résolvent donc
  correctement leurs montages.
- **Mode jeu pour cub3D.** noVNC n'envoie que des positions absolues, ce qui casse un jeu qui
  recentre la souris à chaque image. La page capture la souris (Pointer Lock) et envoie des
  déplacements relatifs à un petit pont dans le conteneur ([`launcher/input-bridge.py`](launcher/input-bridge.py)),
  qui les injecte dans X par XTest.
- **Les secrets sont générés, jamais versionnés.** Mots de passe d'Inception, `.env` et
  certificat auto-signé de Cloud-1 : créés au premier lancement, ignorés par git.
- **Une stack à la fois.** Inception et Cloud-1 écoutent toutes deux sur le 443 : démarrer
  l'une arrête l'autre.

### Adaptations pour tourner hors de l'école

Le code est celui rendu en évaluation. Ce qu'il faut pour le lancer ailleurs se trouve dans
[`launcher/`](launcher) (surcharges compose, programmes d'appel), pas dans les projets :

- Inception : le sujet impose des volumes liés à `/home/<login>/data`, remplacés par des volumes nommés.
- ft_transcendence : `backup` (service ponctuel) sort du `up`, et le healthcheck d'Adminer suit
  l'image `adminer:latest`, qui a renommé son binaire PHP depuis l'évaluation.
- push_swap : le dernier commit sur vogsphere dépend d'une version de ma libft jamais commitée ;
  ce dépôt contient le commit précédent, complet.
- Bibliothèques (libft, ft_printf, get_next_line) : elles n'ont pas de `main`, de petits
  programmes de démo dans [`launcher/demos/`](launcher/demos) les appellent.

## Prérequis

- Docker avec le plugin compose (Docker Desktop sous Windows et macOS)
- bash : Linux, macOS, WSL, ou Git Bash sous Windows

Ports : 4242 (portail), 6080-6081 (écran virtuel, mode jeu), 1045 (webserv), 443, 9443, 21 et 30000-30009
(Inception), 80 et 443 (Cloud-1), 8000, 8001, 8080, 3000, 9090 et 8200 (ft_transcendence).
