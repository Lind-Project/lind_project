FROM archlinux/base
LABEL lind "v0.9-alpha"
LABEL description "Lind NaCl Glibc Toolchain (Base)"
MAINTAINER Joey Pabalinas <joeypabalinas@gmail.com>

ADD ["https://raw.githubusercontent.com/Lind-Project/lind_project/master/docker/pkgs.tar.xz", "/"]

WORKDIR /
RUN ["/usr/bin/bsdtar", "--no-same-permissions", "-xf", "pkgs.tar.xz"]
RUN ["/usr/bin/chown", "-RL","root:root", "/etc/", "/romklindot/"]
RUN ["/usr/bin/pacman", "-Sy", "--noconfirm", "gawk", "inetutils", "procps-ng", "ruby"]
RUN ["/usr/bin/pacman", "-Syu", "--noconfirm", "base-devel", "w3m", \
    "git", "mercurial", "rsync", "make", "perl", "clang", "lynx", "ed", \
    "compiler-rt", "lib32-clang", "lib32-llvm", "lib32-llvm-libs", "vim", \
    "llvm", "llvm-libs", "openmp", "elfutils", "libelf", "gdb", "less", \
    "gnu-netcat", "zsh", "zsh-completions", "grml-zsh-config", "htop", \
    "ncurses", "gcc-libs", "lib32-gcc-libs", "gperf", "diffutils", "fzf", \
    "gperftools", "texinfo", "fortune-mod", "gnupg", "highlight", "fasd", \
    "python2", "python2-pip", "python2-setuptools", "p7zip", "fuse3", "ack", \
    "python2-virtualenv", "python-virtualenvwrapper", "pkgfile", "dhcpcd", \
    "iputils","python", "iproute2", "net-tools", "openresolv", "ranger", \
    "openssh", "subversion", "pacman-contrib", "arch-wiki-docs", "tree", \
    "psmisc", "lsof", "wget", "pinfo", "asp", "bc", "unrar", "expac", \
    "tmux", "screen", "bash-completion", "the_silver_searcher", "mlocate"]
RUN ["/usr/bin/pkgfile", "--update"]
WORKDIR /usr/bin/
RUN ["/usr/bin/ln",  "-Trsfv", "python2", "python"]
WORKDIR /root/build/
RUN ["/usr/bin/lesskey"]
RUN ["/usr/bin/pip2", "install", "--user", "-Ur", "requirements.txt"]
RUN ["/usr/bin/tic", "screen-256color-italic.terminfo"]

WORKDIR /root/build/terminfo-italics/
RUN ["/usr/bin/env", "EUID=1000", "/usr/bin/makepkg", "--noconfirm", "--skipchecksums", "--skippgpcheck", "-sir"]
WORKDIR /root/build/cower/
RUN ["/usr/bin/env", "EUID=1000", "/usr/bin/makepkg", "--noconfirm", "--skipchecksums", "--skippgpcheck", "-sir"]
WORKDIR /root/build/pacaur/
RUN ["/usr/bin/env", "EUID=1000", "/usr/bin/makepkg", "--noconfirm", "--skipchecksums", "--skippgpcheck", "-sir"]
WORKDIR /root/build/make-3.82/
RUN ["/usr/bin/env", "EUID=1000", "/usr/bin/makepkg", "--noconfirm", "--skipchecksums", "--skippgpcheck", "-sir"]
WORKDIR /root/build/texinfo-4.13/
RUN ["./configure", "--prefix=/root/.local"]
RUN ["/usr/bin/make", "install", "PREFIX=/root/.local"]

WORKDIR /usr/
RUN ["/usr/bin/git", "config", "--global", "user.name", "Lind"]
RUN ["/usr/bin/git", "config", "--global", "user.email", "wooo@weee.woah"]
RUN ["/usr/bin/git", "config", "--global", "core.excludesFile", "/root/.cvsignore"]
RUN ["/usr/bin/git", "clone", "--progress", "-j4", "https://github.com/Lind-Project/lind_project.git"]

WORKDIR /usr/lind_project/
RUN ["/usr/bin/mkdir", "-pv", "lind/repy/lib/glibc/"]
RUN ["/usr/bin/ln", "-sv", "test_cases", "lind/repy/"]
RUN ["/usr/bin/rsync", "--info=progress2", "--msgs2stderr", "-ahhpvA", "/root/build/tls", "lind/repy/lib/glibc/"]
RUN ["/usr/bin/rm", "-rf", "/root/build/", "/var/cache/pacman/pkg/"]

CMD ["/usr/bin/bash"]
