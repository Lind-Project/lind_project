FROM securesystemslab/lind:base
LABEL lind "v1.0-rc5"
LABEL description "Lind NaCl Glibc Toolchain (Pre-built)"
MAINTAINER Joey Pabalinas <joeypabalinas@gmail.com>

ARG BRANCH

ENV PATH "/root/bin:/home/lind/bin:$PATH"
ENV PATH "/root/.local/bin:/home/lind/.local/bin:$PATH"
ENV PATH "/home/lind/lind_project:$PATH"
ENV PATH "/home/lind/lind_project/lind/repy/bin:$PATH"
ENV PATH "/home/lind/lind_project/lind/repy/sdk/toolchain/linux_x86_glibc/bin:$PATH"

USER lind

WORKDIR /home/lind/lind_project/
RUN ./src/mklind -q glibc

CMD bash
