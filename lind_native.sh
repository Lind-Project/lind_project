#!/bin/bash

export ENV PATH="$PWD:$PATH"
export ENV PATH="$PWD/lind/lindenv/bin:$PATH"
export ENV PATH="$PWD/lind/lindenv/sdk/toolchain/linux_x86_glibc/bin:$PATH"
# This is needed for lindsh and others
export ENV PATH="$PWD/src/scripts:$PATH"

# Environment variables for the make toolchain
export ENV LIND_PREFIX="${PWD%/*}"
export ENV LIND_BASE="$LIND_PREFIX/lind_project"
export ENV LIND_SRC="$LIND_BASE/lind"
export ENV LIND_ENV_PATH="$LIND_SRC/lindenv"
export ENV NACL_SDK_ROOT="$LIND_ENV_PATH/sdk"
export ENV PYTHON="python2"
export ENV PNACLPYTHON="python2"
export ENV LD_LIBRARY_PATH="$LIND_ENV_PATH:/lib/glibc:"
