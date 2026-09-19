# 42-cursus

Mes projets de l'école 42 réunis dans un seul dépôt. Chacun se lance avec **une commande** ;
la seule chose à installer est **Docker**.

```bash
git clone https://github.com/Gregory-Marquiset/42-cursus.git
cd 42-cursus
./cursus            # ou : make
```

Le menu propose de compiler et lancer chaque projet. Les projets C/C++ tournent dans une image
Debian avec clang (comme sur les postes de l'école), les projets Docker sont démarrés avec
`docker compose` : on n'installe rien d'autre sur la machine.

## Projets

| Projet | Sujet | Stack | Lancer |
|---|---|---|---|
| [philosophers](projects/philosophers) | Le dîner des philosophes : concurrence, deadlocks, data races | C, pthreads, sémaphores | `./cursus philo` |
| [cpp-modules](projects/cpp-modules) | Piscine C++, modules 00 à 09 : POO, templates, STL | C++98 | `./cursus cpp` |
| [webserv](projects/webserv) | Serveur HTTP/1.1 non bloquant, CGI, upload, multi-ports | C++98, epoll | `./cursus webserv` |
| [inception](projects/inception) | Infrastructure WordPress, une image Docker par service écrite à la main | Docker, nginx, MariaDB, Redis, FTP, Portainer | `./cursus inception` |
| [ft_transcendence](projects/ft_transcendence) | Plateforme web complète en microservices | Node/Fastify, React, PostgreSQL, Vault, WAF, Prometheus/Grafana | `./cursus transcendence` |
| [cloud-1](projects/cloud-1) | Déploiement automatisé d'Inception sur plusieurs serveurs | Terraform, Ansible, Docker | `./cursus cloud-1` |

webserv et ft_transcendence sont des projets d'équipe : leurs dépôts d'origine restent la
référence, avec l'historique et les contributions de chacun
([mcg_webserv](https://github.com/Gregory-Marquiset/mcg_webserv),
[llmcg_transcendence](https://github.com/Gregory-Marquiset/llmcg_transcendence)).

## Utilisation

```bash
./cursus philo philo 5 800 200 200 7          # version, puis arguments du programme
./cursus philo philo_bonus 4 410 200 200
./cursus cpp 09 01 "8 9 * 9 - 9 - 9 - 4 - 1 +" # module, exercice, arguments  -> 42
./cursus webserv                               # http://localhost:1045
./cursus inception                             # https://localhost
./cursus transcendence                         # https://localhost:8001
./cursus cloud-1                               # https://localhost

./cursus status                                # état des stacks Docker
./cursus stop <stack>                          # inception | transcendence | cloud-1
./cursus logs <stack>
./cursus clean                                 # arrête tout, supprime volumes et image outils
```

Sans argument, `./cursus cpp` et `./cursus philo` posent les questions une à une.
Les cibles `make` existent aussi : `make philo ARGS="philo 5 800 200 200"`, `make inception`…

### Ce que fait le lanceur au premier démarrage

- **Image outils** `42-cursus/toolchain` construite une fois (Debian, clang, valgrind, gdb, et
  les interpréteurs CGI de webserv).
- **Secrets générés** au lieu d'être versionnés : mots de passe d'Inception dans
  `projects/inception/srcs/secrets/`, `.env` et certificat auto-signé de Cloud-1. Tout est
  ignoré par git.
- **Une stack à la fois** : Inception et Cloud-1 écoutent toutes deux sur le 443, démarrer
  l'une arrête les autres.
- **Cloud-1 en local** : la stack que Terraform et Ansible déploient sur les serveurs, lancée sur
  la machine, WordPress installé par WP-CLI comme le fait le rôle Ansible. Le déploiement réel
  est décrit dans [projects/cloud-1/README.md](projects/cloud-1/README.md).

### Adaptations pour tourner hors de l'école

Le code des projets est celui rendu en évaluation. Les écarts nécessaires pour les lancer
ailleurs passent par des surcharges compose dans [`launcher/`](launcher), pas par une modification
des projets :

- Inception : le sujet impose des volumes liés à `/home/<login>/data`, remplacés par des volumes
  nommés.
- ft_transcendence : `backup` (service ponctuel) sort du `up`, et le healthcheck d'Adminer suit
  l'image `adminer:latest`, qui a renommé son binaire PHP depuis le rendu.

## Prérequis

- Docker avec le plugin compose (Docker Desktop sur Windows/macOS)
- bash : Linux, macOS, WSL ou Git Bash sous Windows

Ports utilisés : 1045 (webserv), 443, 9443, 21 et 30000-30009 (Inception), 443 et 80 (Cloud-1),
8000, 8001, 8080, 3000, 9090 et 8200 (ft_transcendence).
