FROM alyptik/lind:base
LABEL lind "v0.10-beta"
LABEL description "Lind NaCl Runtime (Pre-built)"
MAINTAINER Joey Pabalinas <joeypabalinas@gmail.com>

ENV VIRTUALENVWRAPPER_PYTHON "/usr/bin/python2"
ENV VIRTUALENVWRAPPER_VIRTUALENV "/usr/bin/virtualenv2"
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
RUN ["./mklind", "download"]
RUN ["./mklind", "nacl"]
RUN ["./mklind", "repy"]
RUN ["./mklind", "glibc"]
RUN ["./mklind", "install"]
RUN ["./mklind", "cleanall"]
WORKDIR /home/lind/lind_project/
RUN ["/usr/bin/env", "x86_64-nacl-gcc", "test_cases/fork.c", "-o", "lind/repy/repy/fork"]
RUN ["/usr/bin/env", "x86_64-nacl-gcc", "test_cases/hello.c", "-o", "lind/repy/repy/hello"]

WORKDIR /home/lind/lind_project/lind/repy/repy/
RUN ["/usr/bin/env", "lindfs", "cp", "./fork"]
RUN ["/usr/bin/env", "lindfs", "cp", "./hello"]
RUN ["/usr/bin/env", "script", "-qfc", "lind /fork", "/dev/null"]
RUN ["/usr/bin/env", "script", "-qfc", "lind /hello", "/dev/null"]

ENTRYPOINT ["/usr/bin/zsh"]
CMD ["-c", "print -r '[lind /fork]'; lind /fork; print -r - '[lind /hello]'; lind /hello; exec zsh"]
