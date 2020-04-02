FROM securesystemslab/lind:prebuiltsdk
LABEL lind "v1.0-rc5"
LABEL description "Lind NaCl Runtime (Pre-built)"
LABEL author "Nicholas Renner nrenner@nyu.edu"

ARG BRANCH

ENV PATH "/root/bin:/home/lind/bin:$PATH"
ENV PATH "/root/.local/bin:/home/lind/.local/bin:$PATH"
ENV PATH "/home/lind/lind_project:$PATH"
ENV PATH "/home/lind/lind_project/lind/repy/bin:$PATH"
ENV PATH "/home/lind/lind_project/lind/repy/sdk/toolchain/linux_x86_glibc/bin:$PATH"
ENV PATH "/home/lind/lind_project/src/scripts:$PATH"

ENV LIND_PREFIX "/home/lind"
ENV LIND_BASE "$LIND_PREFIX/lind_project"
ENV LIND_SRC "$LIND_BASE/lind"
ENV REPY_PATH "$LIND_SRC/repy"
ENV NACL_SDK_ROOT "$REPY_PATH/sdk"
ENV PYTHON "python2"
ENV PNACLPYTHON "python2"
ENV LD_LIBRARY_PATH "/lib/glibc"

ENV TEST_CASES "cpuid dup2 dup exec fgets fork fork_simple getpid hello mprotec pipe read read_input segfault stat sysconf template write"

USER lind

WORKDIR /home/lind/lind_project/
RUN git pull -t -j8
RUN for t in nacl repy install; do ./src/mklind -q "$t"; done
RUN mkdir -p lind/repy/repy/tests
RUN for c in $TEST_CASES; do x86_64-nacl-gcc -std=c99 "tests/test_cases/$c.c" -o "lind/repy/repy/tests/$c"; done
WORKDIR /home/lind/lind_project/tests/applications/bash/
RUN ./bootstrap_nacl --prefix="/home/lind/lind_project/lind/repy/repy"
RUN make install

# Set up the sandbox and copy bash
WORKDIR /home/lind/lind_project/lind/repy/repy/
RUN for f in ./bin/ ./lib/ ./share/ ./.bashrc ./.bash_logout ./.bash_profile; do lindfs cp "$f"; done

# Copy and run the single-file tests
RUN for f in $TEST_CASES; do lindfs cp "./tests/$f"; done
RUN for a in $TEST_CASES; do script -qfc "$(printf '%q ' lind /tests/$a)" /dev/null; done

# Run the bash test
RUN script -qfc "$(printf '%q ' lind /bin/bash --version)" /dev/null

# default to running test cases then a shell if no arguments are passed to `docker run`
CMD bash -c 'for f in $TEST_CASES; do lind /tests/$f; done; lind /bin/bash --version; exec bash'
