FROM archlinux/base
LABEL lind "v0.9-alpha"
LABEL description "Lind NaCl Glibc Toolchain (Base)"
MAINTAINER Joey Pabalinas <joeypabalinas@gmail.com>

ADD ["https://raw.githubusercontent.com/Lind-Project/lind_project/master/docker/pkgs.tar.xz", "/"]

ENV VIRTUALENVWRAPPER_PYTHON "/usr/bin/python2"
ENV VIRTUALENVWRAPPER_VIRTUALENV "/usr/bin/virtualenv2"
ENV LIND_PREFIX "/home/lind"
ENV LIND_BASE "$LIND_PREFIX/lind_project"
ENV LIND_SRC "$LIND_BASE/lind"
ENV LIND_MONITOR "$LIND_BASE/reference_monitor"
ENV REPY_PATH "$LIND_SRC/repy"
ENV NACL_SDK_ROOT "$REPY_PATH/sdk"
ENV PYTHON "python2"
ENV PNACLPYTHON "python2"
ENV LD_LIBRARY_PATH "/lib/glibc"
ENV PATH "$NACL_SDK_ROOT/toolchain/linux_x86_glibc/bin:$PATH"
ENV PATH "$REPY_PATH/bin:$PATH"
ENV PATH "$LIND_BASE:$PATH"
ENV PATH "/home/lind/.local/bin:$PATH"

WORKDIR /
RUN ["/usr/bin/useradd", "-m", "-U", "-s", "/bin/bash", "lind"]
RUN ["/usr/bin/bsdtar", "--no-same-permissions", "-xf", "pkgs.tar.xz"]
RUN ["/usr/bin/chown", "-RL","lind:lind", "/home/lind/"]
RUN ["/usr/bin/chown", "-RL","root:root", "/etc/", "/root/"]
RUN ["/usr/bin/pacman", "-Sy", "--needed", "--noconfirm", "gawk", "procps-ng", "ruby"]
RUN ["/usr/bin/pacman", "-Syu", "--needed", "--noconfirm", "base-devel", "w3m", \
    "git", "mercurial", "rsync", "make", "perl", "clang", "lynx", "ed", \
    "compiler-rt", "lib32-clang", "lib32-llvm", "lib32-llvm-libs", "vim", \
    "llvm", "llvm-libs", "openmp", "elfutils", "libelf", "gdb", "less", \
    "gnu-netcat", "zsh", "zsh-completions", "grml-zsh-config", "htop", "bc", \
    "ncurses", "gcc-libs", "lib32-gcc-libs", "gperf", "diffutils", "fzf", \
    "gperftools", "texinfo", "fortune-mod", "gnupg", "highlight", "fasd", \
    "python2", "python2-pip", "python2-setuptools", "p7zip", "fuse3", "ack", \
    "python2-virtualenv", "python-virtualenvwrapper", "pkgfile", "dhcpcd", \
    "iputils","python", "iproute2", "net-tools", "openresolv", "ranger", \
    "openssh", "subversion", "pacman-contrib", "arch-wiki-docs", "tree", \
    "psmisc", "lsof", "wget", "pinfo", "asp","unrar", "expac", "inetutils", \
    "tmux", "screen", "bash-completion", "the_silver_searcher", "mlocate"]
RUN ["/usr/bin/pkgfile", "--update"]

USER lind

WORKDIR /home/lind/build/
RUN ["/usr/bin/lesskey"]
RUN ["/usr/bin/pip2", "install", "--user", "-Ur", "requirements.txt"]
RUN ["/usr/bin/tic", "screen-256color-italic.terminfo"]
WORKDIR /home/lind/build/terminfo-italics/
RUN ["/usr/bin/env", "EUID=1000", "/usr/bin/makepkg", "--noconfirm", "--skipchecksums", "--skippgpcheck", "-sir"]
WORKDIR /home/lind/build/cower/
RUN ["/usr/bin/env", "EUID=1000", "/usr/bin/makepkg", "--noconfirm", "--skipchecksums", "--skippgpcheck", "-sir"]
WORKDIR /home/lind/build/pacaur/
RUN ["/usr/bin/env", "EUID=1000", "/usr/bin/makepkg", "--noconfirm", "--skipchecksums", "--skippgpcheck", "-sir"]
WORKDIR /home/lind/build/make-3.82/
RUN ["/usr/bin/env", "EUID=1000", "/usr/bin/makepkg", "--noconfirm", "--skipchecksums", "--skippgpcheck", "-sir"]
WORKDIR /home/lind/build/texinfo-4.13/
RUN ["./configure", "--prefix=/home/lind/.local"]
RUN ["/usr/bin/make", "install", "PREFIX=/home/lind/.local"]

WORKDIR /home/lind/
RUN ["/usr/bin/git", "config", "--global", "user.name", "Lind"]
RUN ["/usr/bin/git", "config", "--global", "user.email", "wooo@weee.woah"]
RUN ["/usr/bin/git", "config", "--global", "core.excludesFile", "/home/lind/.cvsignore"]
RUN ["/usr/bin/git", "clone", "--progress", "-j4", "https://github.com/Lind-Project/lind_project.git"]

WORKDIR /home/lind/lind_project/
RUN ["/usr/bin/rm", "-rf", "/home/lind/build/", "/var/cache/pacman/pkg/"]

USER root

CMD ["/usr/bin/bash"]
