FROM alyptik/lind:base
LABEL lind "v1.0-rc4"
LABEL description "Lind NaCl Glibc Toolchain (Pre-built)"
MAINTAINER Joey Pabalinas <joeypabalinas@gmail.com>

ENV LIND_PREFIX "/home/lind"
ENV LIND_BASE "$LIND_PREFIX/lind_project"
ENV LIND_SRC "$LIND_BASE/lind"
ENV LIND_MONITOR "$LIND_BASE/reference_monitor"
ENV REPY_PATH "$LIND_SRC/repy"
ENV NACL_SDK_ROOT "$REPY_PATH/sdk"
ENV PYTHON "python2"
ENV PNACLPYTHON "python2"
ENV LD_LIBRARY_PATH "/lib/glibc"
ENV PATH "$NACL_SDK_ROOT/toolchain/linux_x86_glibc/bin:$PATH"
ENV PATH "$REPY_PATH/bin:$PATH"
ENV PATH "$LIND_BASE:$PATH"
ENV PATH "/root/bin:/home/lind/bin:$PATH"
ENV PATH "/root/.local/bin:/home/lind/.local/bin:$PATH"

USER lind

WORKDIR /home/lind/lind_project/
RUN ["./mklind", "-qe", "glibc"]

ENTRYPOINT ["/usr/bin/zsh"]
