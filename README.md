# Lind - A Portable Lightweight Single-Process Sandbox

Lind is a single process sandbox that provides an option to safely execute
programs and control its resource (network, file, memory, cpu, etc.) usage
at the process granularity. Lind executes applications in an isolated
environment from the rest of the applications in the system, and thus
limits the damage of bugs or security flaws in the application.

Base and pre-built docker images for the SDK toolchain can be fetched from
the Docker Hub Lind repository at [alyptik/lind](https://hub.docker.com/r/alyptik/lind)
with ` docker pull alyptik/lind:base` and `docker pull alyptik/lind:prebuiltsdk`
respectively.

##### As this is a WIP some features are not yet completely implemented.

## Dependencies

* Python 2
* GCC
* Clang

The following dependencies can be compiled from the source distributions
found in "docker/pkgs.tar.xz":

* Make 3.82
* TexInfo 4.13

##### Optional dependencies:
	* Fortune

## Usage

```bash
./mklind [-ehv] [commands]
```

#### Options

	-e      Use default environment.
	-h      Display this help.
	-v      Display script version.

