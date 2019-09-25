FROM securesystemslab/lind:prebuiltsdk
LABEL lind "v1.0-rc5"
LABEL description "Lind NaCl Runtime (Pre-built)"
MAINTAINER Nicholas Renner <nrenner@nyu.edu>

ARG BRANCH

ENV PATH "/root/bin:/home/lind/bin:$PATH"
ENV PATH "/root/.local/bin:/home/lind/.local/bin:$PATH"
ENV PATH "/home/lind/lind_project:$PATH"
ENV PATH "/home/lind/lind_project/lind/repy/bin:$PATH"
ENV PATH "/home/lind/lind_project/lind/repy/sdk/toolchain/linux_x86_glibc/bin:$PATH"

USER lind

WORKDIR /home/lind/lind_project/
RUN git pull -t -j8
RUN for t in nacl repy install; do ./src/mklind -q "$t"; done
RUN x86_64-nacl-gcc "tests/test_cases/cpuid.c" -o "lind/repy/repy/cpuid"
RUN x86_64-nacl-gcc "tests/test_cases/dup2.c" -o "lind/repy/repy/dup2"
RUN x86_64-nacl-gcc "tests/test_cases/dup.c" -o "lind/repy/repy/dup"
RUN x86_64-nacl-gcc "tests/test_cases/fgets.c" -o "lind/repy/repy/fgets"
RUN x86_64-nacl-gcc "tests/test_cases/fork.c" -o "lind/repy/repy/fork"
RUN x86_64-nacl-gcc "tests/test_cases/fork_simple.c" -o "lind/repy/repy/fork_simple"
RUN x86_64-nacl-gcc "tests/test_cases/getpid.c" -o "lind/repy/repy/getpid"
RUN x86_64-nacl-gcc "tests/test_cases/hello.c" -o "lind/repy/repy/hello"
RUN x86_64-nacl-gcc "tests/test_cases/mprotec.c" -o "lind/repy/repy/mprotec"
RUN x86_64-nacl-gcc "tests/test_cases/read_input.c" -o "lind/repy/repy/read_input"
RUN x86_64-nacl-gcc "tests/test_cases/segfault.c" -o "lind/repy/repy/segfault"
RUN x86_64-nacl-gcc "tests/test_cases/sysconf.c" -o "lind/repy/repy/sysconf"
RUN x86_64-nacl-gcc "tests/test_cases/template.c" -o "lind/repy/repy/template"
RUN x86_64-nacl-gcc "tests/test_cases/write.c" -o "lind/repy/repy/write"
WORKDIR /home/lind/lind_project/tests/test_cases/bash/
RUN ./bootstrap_nacl --prefix="/home/lind/lind_project/lind/repy/repy"
RUN make install

WORKDIR /home/lind/lind_project/lind/repy/repy/
RUN for f in ./bin/ ./lib/ ./share/ ./cpuid ./dup2 ./dup ./fgets ./fork ./fork_simple ./getpid ./hello ./mprotec ./read ./read_input ./segfault ./sysconf ./template ./write ./.bashrc ./.bash_logout ./.bash_profile; do lindfs cp "$f"; done
RUN script -qfc "$(printf '%q ' lind /cpuid)" /dev/null
RUN script -qfc "$(printf '%q ' lind /dup2)" /dev/null
RUN script -qfc "$(printf '%q ' lind /dup)" /dev/null
RUN script -qfc "$(printf '%q ' lind /fgets)" /dev/null
RUN script -qfc "$(printf '%q ' lind /fork)" /dev/null
RUN script -qfc "$(printf '%q ' lind /fork_simple)" /dev/null
RUN script -qfc "$(printf '%q ' lind /getpid)" /dev/null
RUN script -qfc "$(printf '%q ' lind /hello)" /dev/null
RUN script -qfc "$(printf '%q ' lind /mprotec)" /dev/null
RUN script -qfc "$(printf '%q ' lind /read_input)" /dev/null
RUN script -qfc "$(printf '%q ' lind /segfault)" /dev/null
RUN script -qfc "$(printf '%q ' lind /sysconf)" /dev/null
RUN script -qfc "$(printf '%q ' lind /template)" /dev/null
RUN script -qfc "$(printf '%q ' lind /write)" /dev/null
RUN script -qfc "$(printf '%q ' lind /bin/bash --version)" /dev/null

# default to running test cases then a shell if no arguments are passed to `docker run`
CMD bash -c 'lind /cpuid; lind /dup2; lind /dup; lind /fgets; lind /fork; lind /fork_simple; lind /getpid; lind /hello; lind /mprotec; lind /read_input; lind /segfault; lind /sysconf; lind /template; lind /write; lind /bin/bash --version; exec bash'
