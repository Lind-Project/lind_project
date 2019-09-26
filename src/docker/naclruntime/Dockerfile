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
RUN for c in cpuid dup2 dup fgets fork fork_simple getpid hello mprotec read_input segfault sysconf template write; do x86_64-nacl-gcc "tests/test_cases/$c.c" -o "lind/repy/repy/$c"; done
WORKDIR /home/lind/lind_project/tests/test_cases/bash/
RUN ./bootstrap_nacl --prefix="/home/lind/lind_project/lind/repy/repy"
RUN make install

WORKDIR /home/lind/lind_project/lind/repy/repy/
RUN for f in ./bin/ ./lib/ ./share/ ./cpuid ./dup2 ./dup ./fgets ./fork ./fork_simple ./getpid ./hello ./mprotec ./read ./read_input ./segfault ./sysconf ./template ./write ./.bashrc ./.bash_logout ./.bash_profile; do lindfs cp "$f"; done
RUN for a in /cpuid /dup2 /dup /fgets /fork /fork_simple /getpid /hello /mprotec /read_input /segfault /sysconf /template /write "/bin/bash --version"; do script -qfc "$(printf '%q ' lind $a)" /dev/null; done

# default to running test cases then a shell if no arguments are passed to `docker run`
CMD bash -c 'lind /cpuid; lind /dup2; lind /dup; lind /fgets; lind /fork; lind /fork_simple; lind /getpid; lind /hello; lind /mprotec; lind /read_input; lind /segfault; lind /sysconf; lind /template; lind /write; lind /bin/bash --version; exec bash'
