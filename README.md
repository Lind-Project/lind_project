# Lind

Lind is a single-process sandbox that provides an option to safely execute
programs and control its resource (network, file, memory, cpu, etc.) usage
at the process granularity. Lind executes applications in an isolated
environment from the rest of the applications in the system, and thus
limits the damage of bugs or security flaws in the application.

##### *NOTE: This is a WIP and some features are not yet completely implemented.*

Base and pre-built docker images for the SDK toolchain can be fetched from
the Docker Hub Lind repository at [alyptik/lind](https://hub.docker.com/r/alyptik/lind)
with ` docker pull alyptik/lind:base` and `docker pull alyptik/lind:prebuiltsdk`
respectively.

## Dependencies

* python 2
* virtualenv2 and virtualenvwrapper
        - install using `pip2 install --user virtualenvwrapper virtualenv2`
* gcc
* clang

The following dependencies can be compiled from the source distributions
found in `docker/pkgs.tar.xz`

* make 3.82
* texinfo 4.13

## Usage

Clone the [main Lind repository](https://github.com/Lind-Project/lind_project)
to `~/lind_project`, install the python dependencies using
`pip2 install --user virtualenvwrapper virtualenv`, and finally
run `make` or `./mklind -e` to start the build script using the default
environment.

```bash
./mklind [-ehv] [targets]
```

#### Options

        -e    Use default environment.
        -h    Display this help.
        -v    Display script version.

#### Custom Environment

The default environment of `./mklind -e` consists of

```bash
export LIND_PREFIX="$HOME"
export LIND_BASE="$LIND_PREFIX/lind_project"
export LIND_SRC="$LIND_PREFIX/lind_project/lind"
export LIND_MONITOR="$LIND_PREFIX/lind_project/reference_monitor"
export NACL_SDK_ROOT="$LIND_PREFIX/lind_project/lind/repy/sdk"
export REPY_PATH="$LIND_PREFIX/lind_project/lind/repy"
export PYTHON="python2"
export PNACLPYTHON="python2"
export LD_LIBRARY_PATH="/lib/glibc"

```

as the default set of sane paths for the build.

You can also export these environment variables yourself and use `./mklind`
without the `-e` flag to use custom paths for the build.

##### n.b. `LD_LIBRARY_PATH` needs to be set to `/lib/glibc` unless you are modifying the target installation directory for Repy's modified glibc toolchain.
