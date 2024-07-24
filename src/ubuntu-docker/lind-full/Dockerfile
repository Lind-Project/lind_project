FROM securesystemslab/lind_ubuntu:lind-glibc
LABEL lind "v2.0-rc1"
LABEL description "Lind Toolchain Full (Pre-built)"
LABEL author "Nicholas Renner nrenner@nyu.edu"

ARG BRANCH
ARG ENV
ARG docker_gid

ENV PATH="/root/bin:/home/lind/bin:$PATH"
ENV PATH="/root/.local/bin:/home/lind/.local/bin:$PATH"
ENV PATH="/home/lind/lind_project:$PATH"
ENV PATH="/home/lind/lind_project/lind/lindenv/bin:$PATH"
ENV PATH="/home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/bin:$PATH"
# This is needed for lindsh and others
ENV PATH="/home/lind/lind_project/src/scripts:$PATH"

# Environment variables for the make toolchain
ENV LIND_PREFIX="/home/lind"
ENV LIND_BASE="$LIND_PREFIX/lind_project"
ENV LIND_SRC="$LIND_BASE/lind"
ENV LIND_ENV_PATH="$LIND_SRC/lindenv"
ENV NACL_SDK_ROOT="$LIND_ENV_PATH/sdk"
ENV PYTHON="python2"
ENV PNACLPYTHON="python2"
ENV LD_LIBRARY_PATH="/home/lind/lind_project/lind/lindenv/:/lib/glibc:"

# Giving the user the ability to use host docker, this is a security risk and should be used with caution
# This is needed for the docker in docker setup, and is not recommended for general use. production contains shouldnt mount
# the docker socket.
USER root

RUN if [ "$ENV" = "ci" ]; then \
    addgroup --gid ${docker_gid} dockerhost && \
    usermod --append --groups ${docker_gid} lind && \
    sg dockerhost -c 'newgrp dockerhost'; \
fi

USER lind

ENV DOCKER_BUILDKIT=0

WORKDIR /home/lind/lind_project

RUN ./src/mklind download

# finish install
RUN git pull --recurse-submodules -t -j8


RUN ./src/mklind rustposix
RUN ./src/mklind nacl
RUN ./src/mklind install

RUN ./src/scripts/base/load_bash.sh
RUN ./src/scripts/base/load_coreutils.sh

WORKDIR /home/lind/lind_project/

