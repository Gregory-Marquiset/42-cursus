# Image outils des projets C / C++ : compilateurs, debug, et interpreteurs CGI de webserv
FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential clang valgrind gdb \
        python3 perl nodejs php-cgi \
        curl ca-certificates openssl \
    && rm -rf /var/lib/apt/lists/*

# Comme sur les postes de 42 : cc et c++ pointent vers clang
RUN update-alternatives --set cc /usr/bin/clang \
 && update-alternatives --set c++ /usr/bin/clang++

WORKDIR /work
CMD ["bash"]
