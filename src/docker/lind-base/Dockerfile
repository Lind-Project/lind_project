FROM archlinux:latest
LABEL lind "v2.0-rc1"
LABEL description "Lind Toolchain (Base)"
LABEL author "Nicholas Renner nrenner@nyu.edu"

ADD etc/ /etc/
ADD home/ /home/
ADD root/ /root/

ARG BRANCH

USER root

WORKDIR /
RUN useradd -Um -s/bin/bash -u1000 lind
RUN mkdir -pv "/root/.local/etc/" "/home/lind/.local/etc/"
RUN chown -LR lind:lind "/home/lind/"
RUN chown -LR root:root "/etc/" "/root/"
RUN pacman-key --init
RUN pacman -Sy archlinux-keyring --noconfirm
RUN pacman -Syu --needed --noconfirm base-devel \
	git mercurial rsync make perl clang lynx ltrace \
	w3m gawk procps-ng ruby strace gdb reptyr ed \
	compiler-rt lib32-clang lib32-llvm lib32-llvm-libs vim \
	llvm llvm-libs openmp elfutils libelf gdb less \
	gnu-netcat zsh zsh-completions htop bc ctags sudo \
	ncurses gcc-libs lib32-gcc-libs gperf diffutils fzf \
	gperftools texinfo fortune-mod gnupg highlight fasd \
	pyenv p7zip fuse3 ack \
	pkgfile dhcpcd iputils python iproute2 \
	net-tools openresolv openssh subversion pacman-contrib \
	tree psmisc lsof wget unrar expac inetutils \
	tmux screen bash-completion mlocate shadow ncdu \
	bind-tools cowsay filesystem linux-headers \
	grml-zsh-config linux-docs man-pages man-db \
	util-linux help2man rlwrap cmake ninja capnproto \
    glibc lib32-glibc libxcrypt perf rustup libpng time
RUN pkgfile --update

USER lind
WORKDIR /home/lind/

RUN rustup default nightly

RUN git config --global user.name "lind"
RUN git config --global user.email "lind@nyu.edu"
RUN git config --global core.excludesFile "/home/lind/.cvsignore"
RUN git clone --progress -j8 https://github.com/Lind-Project/lind_project.git
WORKDIR /home/lind/build/

USER root

WORKDIR /root/
RUN git config --global user.name "root"
RUN git config --global user.email "root@nyu.edu"
RUN git config --global core.excludesFile "/root/.cvsignore"
RUN ln -rsv "/home/lind/lind_project" "./"
WORKDIR /root/build/

USER lind

WORKDIR /home/lind/build/
RUN git clone https://aur.archlinux.org/yay.git
WORKDIR yay
RUN makepkg --noconfirm -sci 

RUN yay --version
RUN yes | yay -S python2 --mflags "--nocheck"
RUN yes | yay -S python2-setuptools --mflags "--nocheck"
RUN yes | yay -S python-setuptools --mflags "--nocheck"
RUN yes | yay -S python2-pip --mflags "--nocheck"

WORKDIR /home/lind/build/make-3.82/
RUN makepkg --noconfirm -sci
WORKDIR /home/lind/build/texinfo-4.13/
RUN ./configure --prefix="/home/lind/.local" && make install
WORKDIR /home/lind/build/pip2
RUN python --version
RUN python2 get-pip.py
WORKDIR /home/lind/build/
RUN git clone https://aur.archlinux.org/rr.git
WORKDIR rr
RUN makepkg --noconfirm -sci

USER root

WORKDIR /usr/sbin
RUN ln -sf python2 python
RUN ln -sf make-3.82 make

WORKDIR /home/lind/
RUN rm -rf "/home/lind/build/" "/root/build/" "/var/cache/pacman/pkg/"
RUN chown -Rc lind:lind .

USER lind

ENV PATH="/root/bin:/home/lind/bin:$PATH"
ENV PATH="/root/.local/bin:/home/lind/.local/bin:$PATH"
ENV PATH="/home/lind/lind_project:$PATH"
ENV PATH="/home/lind/lind_project/lind/lindenv/bin:$PATH"
ENV PATH="/home/lind/lind_project/lind/lindenv/sdk/toolchain/linux_x86_glibc/bin:$PATH"
# This is needed for lindsh and others
ENV PATH="/home/lind/lind_project/src/scripts:$PATH"

# Environment variables for the make toolchain
ENV LIND_PREFIX="/home/lind"
ENV LIND_BASE="$LIND_PREFIX/lind_project"
ENV LIND_SRC="$LIND_BASE/lind"
ENV LIND_ENV_PATH="$LIND_SRC/lindenv"
ENV NACL_SDK_ROOT="$LIND_ENV_PATH/sdk"
ENV PYTHON="python2"
ENV PNACLPYTHON="python2"
ENV LD_LIBRARY_PATH="/home/lind/lind_project/lind/lindenv/:/lib/glibc:"

CMD bash

