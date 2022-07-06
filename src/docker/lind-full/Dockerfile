FROM securesystemslab/lind:lind-glibc
LABEL lind "v1.0-rc5"
LABEL description "Lind NaCl Glibc Toolchain (Pre-built)"
LABEL author "Nicholas Renner nrenner@nyu.edu"

ARG BRANCH

ENV PATH "/root/bin:/home/lind/bin:$PATH"
ENV PATH "/root/.local/bin:/home/lind/.local/bin:$PATH"
ENV PATH "/home/lind/lind_project:$PATH"
ENV PATH "/home/lind/lind_project/lind/lindenv/bin:$PATH"
ENV PATH "/home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/bin:$PATH"
# This is needed for lindsh and others
ENV PATH "/home/lind/lind_project/src/scripts:$PATH"

# Environment variables for the make toolchain
ENV LIND_PREFIX "/home/lind"
ENV LIND_BASE "$LIND_PREFIX/lind_project"
ENV LIND_SRC "$LIND_BASE/lind"
ENV LIND_ENV_PATH "$LIND_SRC/lindenv"
ENV NACL_SDK_ROOT "$LIND_ENV_PATH/sdk"
ENV PYTHON "python2"
ENV PNACLPYTHON "python2"
ENV LD_LIBRARY_PATH "/home/lind/lind_project/lind/lindenv/:/lib/glibc:"

ENV TEST_CASES "cpuid dup2 dup exec fgets fork fork_simple getpid hello mprotec pipe read read_input segfault stat sysconf template write"

USER lind

WORKDIR /home/lind/lind_project

# finish install
RUN git pull -t -j8
RUN for t in rustposix nacl install; do ./src/mklind -q "$t"; done
# make tests
run mkdir -p lind/lindenv/tests
run for c in $test_cases; do x86_64-nacl-gcc -std=c99 "tests/test_cases/$c.c" -o "lind/lindenv/tests/$c"; done
# make bash
WORKDIR /home/lind/lind_project/tests/applications/bash/
RUN ./bootstrap_nacl --prefix="/home/lind/lind_project/lind/lindenv"

# Set up the sandbox and copy bash
WORKDIR /home/lind/lind_project/lind/lindenv
RUN for f in ./bin/ ./lib/ ./share/ ./.bashrc ./.bash_logout ./.bash_profile; do lindfs cp "$f"; done

# Copy and run the single-file tests
RUN for f in $TEST_CASES; do lindfs cp "./tests/$f"; done
RUN for a in $TEST_CASES; do script -qfc "$(printf '%q ' lind /tests/$a)" /dev/null; done

# Run the bash test
RUN script -qfc "$(printf '%q ' lind /bin/bash --version)" /dev/null

# default to running test cases then a shell if no arguments are passed to `docker run`
CMD bash -c 'for f in $TEST_CASES; do lind /tests/$f; done; lind /bin/bash --version; exec bash'

WORKDIR /home/lind/lind_project/

