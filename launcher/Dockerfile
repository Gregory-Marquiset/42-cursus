# Image outils des projets C / C++ : compilateurs, debug, bibliotheques des projets,
# interpreteurs CGI de webserv, et un ecran virtuel (Xvfb + noVNC) pour fdf et cub3d
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential clang-12 valgrind gdb \
        libreadline-dev libx11-dev libxext-dev libbsd-dev zlib1g-dev \
        python3 perl nodejs php-cgi \
        xvfb x11vnc novnc websockify procps \
        curl ca-certificates openssl \
    && rm -rf /var/lib/apt/lists/*

# Comme sur les postes de 42 (Ubuntu 22.04) : cc et c++ sont clang 12. Les clang suivants
# ajoutent des warnings (-Wunused-but-set-variable...) qui cassent les -Werror des projets.
RUN update-alternatives --install /usr/bin/cc  cc  /usr/bin/clang-12   100 \
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-12 100

WORKDIR /work
CMD ["bash"]
