# Lind

Lind is a single-process sandbox that provides an option to safely execute
programs and control its resource (network, file, memory, cpu, etc.) usage
at the process granularity. Lind executes applications in an isolated
environment from the rest of the applications in the system, and thus
limits the damage of bugs or security flaws in the application.

##### *NOTE: This is a WIP and some features are not yet completely implemented.*

Base and pre-built docker images for the SDK toolchain can be fetched from
the Docker Hub Lind repository at [alyptik/lind](https://hub.docker.com/r/alyptik/lind)
with ` docker pull alyptik/lind`.

You can either `make run` or start the container yourself using:

```bash
docker pull alyptik/lind
docker run --privileged --ipc=host --cap-add=SYS_PTRACE -it alyptik/lind /bin/bash
```

The `--privileged` option is so that /proc is writable, the `--ipc=host` option
is needed to avoid mounting /dev/shm with `noexec` (NaCl needs to be able to
execute mmap()'d sections of /dev/shm) and the `--cap-add=SYS_PTRACE` allows
debugging with applications that use ptrace() such as gdb.

## Build Script Dependencies

If you decide to instead build Lind on your host system, the following
dependencies are required:

* python 2
* virtualenv2 and virtualenvwrapper
        - install using `pip2 install --user virtualenv`
* gcc
* clang

The following dependencies can be compiled from the source distributions
found in `docker/pkgs.tar.xz`

* make 3.82
* texinfo 4.13

## Usage

Clone the [main Lind repository](https://github.com/Lind-Project/lind_project) to `~/lind_project`, install the python
dependencies using `pip2 install --user virtualenv`, and then run `./mklind`
to start the build script using the default environment.

```bash
./mklind [-ehv] [targets]
```

#### Options

        -e      Use custom environment instead of defaults for directory paths.
        -h      Display this help.
        -q      Silent build (only errors are printed).
        -v      Display script version.

#### Custom Environment

The default environment of `./mklind` consists of

```bash
export LIND_PREFIX="$HOME"
export LIND_BASE="$LIND_PREFIX/lind_project"
export LIND_SRC="$LIND_BASE/lind"
export LIND_MONITOR="$LIND_BASE/reference_monitor"
export REPY_PATH="$LIND_SRC/repy"
export NACL_SDK_ROOT="$REPY_PATH/sdk"
export PYTHON="python2"
export PNACLPYTHON="python2"
export LD_LIBRARY_PATH="/lib/glibc"
```

as the default set of sane paths for the build.

You can also export these environment variables yourself and use `./mklind`
with the `-e` flag to use custom paths for the build.

##### n.b. `LD_LIBRARY_PATH` needs to be set to `/lib/glibc` unless you are modifying the target directory for Repy's modified glibc toolchain installation.
