FROM securesystemslab/lind:lind-base
LABEL lind "v2.0-rc1"
LABEL description "Lind NaCl Glibc Toolchain (Pre-built)"
LABEL author "Nicholas Renner nrenner@nyu.edu"

ARG BRANCH
# download source files and make glibc
USER lind

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
ENV LC_COLLATE="C"

WORKDIR /home/lind/lind_project
RUN pip2 install -r requirements.txt
RUN git checkout develop

RUN source ~/.bashrc && ./src/mklind download

RUN echo "Lind download complete."

RUN fortune

WORKDIR /home/lind/lind_project
RUN source ~/.bashrc && ./src/mklind glibc

RUN echo "Glibc installed."


