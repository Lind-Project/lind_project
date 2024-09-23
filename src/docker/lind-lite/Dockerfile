FROM base-lite:latest as build
LABEL lind "v2.0-rc1"
LABEL description "Lind NaCl Glibc Toolchain (Pre-built)"
LABEL author "Nicholas Renner nrenner@nyu.edu"

ARG BRANCH
# download source files and make glibc
USER lind

ENV PATH="/root/bin:/home/lind/bin:$PATH"
ENV PATH="/root/.local/bin:/root/.cargo/env:/home/lind/.local/bin:$PATH"
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
ENV LC_COLLATE="C"

USER lind
WORKDIR /home/lind/lind_project
RUN pip2 install -r requirements.txt
RUN git pull --recurse-submodules -t -j8
RUN ./src/mklind download
USER root
RUN ./src/mklind glibc
USER lind
RUN ./src/mklind rustposix
RUN ./src/mklind nacl
RUN ./src/mklind install

FROM base-lite:latest as prod

COPY --from=build /home/lind/lind_project/lind /home/lind/lind_project/lind
WORKDIR /home/lind/lind_project
RUN git submodule update --init tests/native-rustposix
RUN ./src/scripts/base/compile_bash.sh
RUN ./src/scripts/base/load_bash.sh
RUN ./src/scripts/base/load_coreutils.sh
USER root
RUN ./tests/ipc_performance/total_runtime/setup.sh
WORKDIR /home/lind/lind_project/tests/ipc_performance/total_runtime
RUN ./compile.sh
RUN mkdir data
USER lind
# RUN /home/lind/lind_project/src/scripts/rawposix/rawposix_install.sh
# RUN /home/lind/lind_project/src/scripts/rawposix/rawposix_base.sh
# finish install
WORKDIR /home/lind/lind_project


#RUN x86_64-nacl-gcc /home/lind/lind_project/tests/test_cases/hello.c -o /home/lind/lind_project/hello.nexe && lindfs cp /home/lind/lind_project/hello.nexe hello.nexe && lind /hello.nexe

# Set the default shell to bash
SHELL ["/bin/bash"]
