FROM alyptik/lind:base
LABEL lind "v0.9-alpha"
LABEL description "Lind NaCl Glibc Toolchain (Pre-built)"
MAINTAINER Joey Pabalinas <joeypabalinas@gmail.com>

ENV VIRTUALENVWRAPPER_PYTHON "/usr/bin/python2"
ENV VIRTUALENVWRAPPER_VIRTUALENV "/usr/bin/virtualenv2"
ENV LIND_PREFIX "/root"
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
ENV PATH "/root/.local/bin:$PATH"

WORKDIR /root/lind_project/
RUN ["./mklind", "download"]
RUN ["./mklind", "nacl"]
RUN ["./mklind", "repy"]
RUN ["./mklind", "buildglibc"]
RUN ["./mklind", "install"]
RUN ["./mklind", "liblind"]
RUN ["/usr/bin/env", "x86_64-nacl-gcc", "test_cases/hello.c", "-o", "lind/repy/repy/hello"]

WORKDIR /root/lind_project/lind/repy/repy/
RUN ["/usr/bin/env", "lindfs", "cp", "./hello"]
RUN ["/usr/bin/env", "lindfs", "cp", "../lib"]
RUN ["/usr/bin/env", "script", "-qfc", "lind /hello", "/dev/null"]

CMD ["/usr/bin/bash"]
