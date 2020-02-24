# Lind [![Build Status](https://travis-ci.org/Lind-Project/lind_project.svg?branch=develop)](https://travis-ci.org/Lind-Project/lind_project)

Lind is a single-process sandbox that provides an option to safely execute
programs and control its resource (network, file, memory, cpu, etc.) usage
at the process granularity. Lind executes applications in an isolated
environment from the rest of the applications in the system, and thus
limits the damage of bugs or security flaws in the application.

##### Lind is currently a work in progress, please bear with us while features are being implemented.

## Building with Docker
Base and pre-built docker images for the SDK toolchain can be fetched from
the Docker Hub Lind repository at [securesystemslab/lind](https://hub.docker.com/r/securesystemslab/lind)
with ` docker pull securesystemslab/lind`.

You can either `make run` or start the container yourself using:

```bash
docker pull securesystemslab/lind
docker run --privileged --ipc=host --cap-add=SYS_PTRACE -it securesystemslab/lind /bin/bash
```

The `--privileged` option is so that /proc is writable, the `--ipc=host` option
is needed to avoid mounting /dev/shm with `noexec` (NaCl needs to be able to
execute mmap()'d sections of /dev/shm) and the `--cap-add=SYS_PTRACE` allows
debugging with applications that use ptrace() such as gdb.

## Building from Scratch
Check out our scratch build wiki, here: [Building Lind from Scratch](https://github.com/Lind-Project/lind_project/wiki/Building-Lind-From-Scratch)

## Security Issues and Bugs
Security issues can be reported by emailing justincappos@gmail.com.

At a minimum, the report must contain the following:
* Description of the vulnerability.
* Steps to reproduce the issue.

Optionally, reports that are emailed can be encrypted with PGP. You should use
PGP key fingerprint E9C0 59EC 0D32 64FA B35F 94AD 465B F9F6 F8EB 475A.

Please do not use the GitHub issue tracker to submit vulnerability reports. The
issue tracker is intended for bug reports and to make feature requests.

## Instructions for Contributors
Development of Lind occurs on the "develop" branch of this repository.
Contributions can be made by submitting GitHub *Pull Requests*. Take a look at
our [development
guidelines](https://github.com/secure-systems-lab/lab-guidelines/blob/master/dev-workflow.md)
for detailed instructions. Submitted code should follow our [style
guidelines](https://github.com/secure-systems-lab/code-style-guidelines) and
must be unit tested.

Contributors must also indicate acceptance of the [Developer Certificate of
Origin (DCO)](https://developercertificate.org/) by appending a `Signed-off-by:
Your Name <example@domain.com>` to each git commit message (see [`git commit
--signoff`](https://git-scm.com/docs/git-commit#Documentation/git-commit.txt---signoff)).


## Acknowledgments
This project is managed by Prof. Justin Cappos and other members of the
[Secure Systems Lab](https://ssl.engineering.nyu.edu/) at NYU.
