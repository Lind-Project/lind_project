FROM alyptik/lind:prebuiltsdk
LABEL lind "v1.0-rc5"
LABEL description "Lind NaCl Runtime (Pre-built)"
MAINTAINER Joey Pabalinas <joeypabalinas@gmail.com>

ARG BRANCH

ENV PATH "/root/bin:/home/lind/bin:$PATH"
ENV PATH "/root/.local/bin:/home/lind/.local/bin:$PATH"
ENV PATH "/home/lind/lind_project:$PATH"
ENV PATH "/home/lind/lind_project/lind/repy/bin:$PATH"
ENV PATH "/home/lind/lind_project/lind/repy/sdk/toolchain/linux_x86_glibc/bin:$PATH"

USER lind

WORKDIR /home/lind/lind_project/
RUN git pull -t -j8
RUN for t in nacl repy install; do ./mklind -q "$t"; done
RUN x86_64-nacl-gcc "test_cases/fork.c" -o "lind/repy/repy/fork"
RUN x86_64-nacl-gcc "test_cases/hello.c" -o "lind/repy/repy/hello"
WORKDIR /home/lind/lind_project/test_cases/bash/
RUN ./bootstrap_nacl --prefix="/home/lind/lind_project/lind/repy/repy"
RUN make install

WORKDIR /home/lind/lind_project/lind/repy/repy/
RUN for f in ./bin/ ./lib/ ./share/ ./fork ./hello ./.bashrc ./.bash_logout ./.bash_profile; do lindfs cp "$f"; done
RUN script -qfc "$(printf '%q ' lind /fork)" /dev/null
RUN script -qfc "$(printf '%q ' lind /hello)" /dev/null
RUN script -qfc "$(printf '%q ' lind /bin/bash --version)" /dev/null

# default to running test cases then a shell if no arguments are passed to `docker run`
CMD bash -c 'lind /fork; lind /hello; lind /bin/bash --version; exec bash'
