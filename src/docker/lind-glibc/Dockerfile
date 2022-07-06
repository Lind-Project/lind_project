FROM securesystemslab/lind:lind-base
LABEL lind "v1.0-rc5"
LABEL description "Lind NaCl Glibc Toolchain (Pre-built)"
LABEL author "Nicholas Renner nrenner@nyu.edu"

ARG BRANCH

ENV PATH "/root/bin:/home/lind/bin:$PATH"
ENV PATH "/root/.local/bin:/home/lind/.local/bin:$PATH"
ENV PATH "/home/lind/lind_project:$PATH"
ENV PATH "/home/lind/lind_project/lind/lindenv/bin:$PATH"
ENV PATH "/home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/bin:$PATH"
# This is needed for lindsh and others
ENV PATH "/home/lind/lind_project/src/scripts:$PATH"

# Environment variables for the make toolchain
ENV LIND_PREFIX "/home/lind"
ENV LIND_BASE "$LIND_PREFIX/lind_project"
ENV LIND_SRC "$LIND_BASE/lind"
ENV LIND_ENV_PATH "$LIND_SRC/lindenv"
ENV NACL_SDK_ROOT "$LIND_ENV_PATH/sdk"
ENV PYTHON "python2"
ENV PNACLPYTHON "python2"

# download source files and make glibc
USER lind

WORKDIR /home/lind/lind_project
RUN pip2 install -r requirements.txt
RUN git checkout develop

RUN ./src/mklind -q download

RUN echo "Lind download complete."

RUN fortune

WORKDIR /home/lind/lind_project
RUN ./src/mklind -q glibc

RUN echo "Glibc installed."


