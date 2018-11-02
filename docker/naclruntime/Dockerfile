FROM alyptik/lind:prebuiltsdk
LABEL lind "v1.0-rc4"
LABEL description "Lind NaCl Runtime (Pre-built)"
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
RUN ["./mklind", "-qe", "nacl"]
RUN ["./mklind", "-qe", "repy"]
RUN ["./mklind", "-qe", "install"]
RUN ["/usr/bin/env", "x86_64-nacl-gcc", "test_cases/fork.c", "-o", "lind/repy/repy/fork"]
RUN ["/usr/bin/env", "x86_64-nacl-gcc", "test_cases/hello.c", "-o", "lind/repy/repy/hello"]
WORKDIR /home/lind/lind_project/test_cases/bash/
RUN ["./bootstrap_nacl", "--prefix=/home/lind/lind_project/lind/repy/repy"]
RUN ["/usr/bin/make", "install"]

WORKDIR /home/lind/lind_project/lind/repy/repy/
RUN ["/usr/bin/env", "lindfs", "cp", "./bin/"]
RUN ["/usr/bin/env", "lindfs", "cp", "./lib/"]
RUN ["/usr/bin/env", "lindfs", "cp", "./share/"]
RUN ["/usr/bin/env", "lindfs", "cp", "./fork"]
RUN ["/usr/bin/env", "lindfs", "cp", "./hello"]
RUN ["/usr/bin/env", "lindfs", "cp", "./.bashrc"]
RUN ["/usr/bin/env", "lindfs", "cp", "./.bash_logout"]
RUN ["/usr/bin/env", "lindfs", "cp", "./.bash_profile"]
RUN ["/usr/bin/env", "script", "-qfc", "$(printf '%q ' lind /fork)", "/dev/null"]
RUN ["/usr/bin/env", "script", "-qfc", "$(printf '%q ' lind /hello)", "/dev/null"]
RUN ["/usr/bin/env", "script", "-qfc", "$(printf '%q ' lind /bin/bash --version)", "/dev/null"]

ENTRYPOINT ["/usr/bin/zsh"]
CMD ["-c", "lind /fork; lind /hello; lind /bin/bash --version; exec zsh"]
