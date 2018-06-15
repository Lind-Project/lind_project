FROM alyptik/lind:base
LABEL lind "v0.9-alpha"
LABEL description "Lind NaCl Glibc Toolchain (Pre-built)"
MAINTAINER Joey Pabalinas <joeypabalinas@gmail.com>

ENV PATH "/usr/lind_project/lind/repy/sdk/toolchain/linux_x86_glibc/bin:$PATH"
ENV PATH "/usr/lind_project/lind/repy/bin:$PATH"
ENV PATH "/usr/lind_project:$PATH"
ENV PATH "/root/.local/bin:$PATH"
ENV VIRTUALENVWRAPPER_PYTHON "/usr/bin/python2"
ENV VIRTUALENVWRAPPER_VIRTUALENV "/usr/bin/virtualenv2"
ENV LIND_BASE "/usr/lind_project"
ENV LIND_SRC "/usr/lind_project/lind"
ENV LIND_MONITOR "/usr/lind_project/reference_monitor"
ENV NACL_SDK_ROOT "/usr/lind_project/lind/repy/sdk"
ENV REPY_PATH "/usr/lind_project/lind/repy"
ENV PNACLPYTHON "/usr/bin/python2"
ENV PYTHON "/usr/bin/python2"
ENV LD_LIBRARY_PATH "/lib/glibc"

WORKDIR /usr/lind_project/
RUN ["./mklind", "download"]
RUN ["./mklind", "nacl"]
RUN ["./mklind", "repy"]
RUN ["./mklind", "buildglibc"]
RUN ["./mklind", "install"]
RUN ["./mklind", "liblind"]
RUN ["/usr/bin/rsync", "--info=progress2", "-ahhpvA", "/root/build/glibc/", "lind/repy/lib/glibc/"]
RUN ["/usr/bin/env", "x86_64-nacl-gcc", "test_cases/hello.c", "-o", "lind/repy/repy/hello"]
RUN ["/usr/bin/rm", "-rf", "/root/build/"]

WORKDIR /usr/lind_project/lind/repy/repy/
RUN ["/usr/bin/env", "lindfs", "cp", "./hello"]
RUN ["/usr/bin/env", "lindfs", "cp", "../lib"]
RUN ["/usr/bin/env", "script", "-qfc", "lind /hello", "/dev/null"]

CMD ["/usr/bin/bash"]
