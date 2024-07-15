FROM amd64/ubuntu:20.04
LABEL lind "v1.0-lind-base-ubuntu-18.04"
LABEL description "Lind Toolchain (Base)"
LABEL author "Nicholas Renner nrenner@nyu.edu"

ARG DEBIAN_FRONTEND=noninteractive

ADD etc/ /etc/
ADD home/ /home/
ADD root/ /root/

USER root

WORKDIR /
RUN useradd -Um -s/bin/bash -u1000 lind
RUN mkdir -pv "/root/.local/etc/" "/home/lind/.local/etc/"
RUN chown -LR lind:lind "/home/lind/"
RUN chown -LR root:root "/etc/" "/root/"

ADD make-3.82/ /home/make-3.82

RUN apt update
RUN apt install build-essential -y
RUN apt install -y software-properties-common wget
RUN apt install -y gcc-7 g++
# RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
# RUN add-apt-repository 'deb http://apt.llvm.org/focal/ llvm-toolchain-focal main'
# RUN echo "deb-src http://apt.llvm.org/focal/ llvm-toolchain-focal main" >> /etc/apt/sources.list
RUN apt-get update -y
# RUN wget https://apt.llvm.org/llvm.sh
# RUN chmod +x llvm.sh
# RUN ./llvm.sh 19
# RUN apt-get install clang lldb -y
# RUN apt-get install clang-format clang-tidy clang-tools clang clangd libc++-dev libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 libllvm-ocaml-dev libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm -y
RUN apt-get update && apt-get install -y \
    build-essential \
    git mercurial rsync perl lynx ltrace \
	w3m gawk procps ruby strace gdb reptyr ed \
  	vim elfutils libelf-dev gdb less \
  	netcat htop bc ctags \
 	libncurses-dev gcc-multilib gperf diffutils \
	google-perftools texinfo fortune-mod gnupg highlight fasd \
	python2.7 python2.7-dev p7zip fuse ack \
	isc-dhcp-client iputils-ping iproute2 \
 	net-tools openresolv openssh-server subversion \
 	tree psmisc lsof wget pinfo asp unrar inetutils-tools \
 	tmux screen bash-completion mlocate ncdu \
 	bind9 bind9utils bind9-doc dnsutils cowsay \
 	util-linux help2man rlwrap cmake ninja-build capnproto \
    glibc-source libcrypt-dev linux-tools-generic autoconf autotools-dev automake clang libncurses-dev libncurses5-dev libncursesw5-dev \
	lib32ncurses5-dev
RUN apt update

WORKDIR /usr/bin
RUN ln -sf python2 python

# WORKDIR /
# RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- --default-toolchain 1.61.0 -y
# WORKDIR /root/.cargo/bin/
# RUN ./rustup default nightly

# # #RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER lind
WORKDIR /home/lind/

RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- --default-toolchain 1.61.0 -y
ENV PATH="/home/lind/.cargo/bin:$PATH"
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


USER root

WORKDIR /home/make-3.82
RUN export CC=gcc-7
RUN ./configure
RUN make CC=gcc-7
RUN make install

WORKDIR /home/lind/build/texinfo-4.13/
RUN ./configure --prefix="/home/lind/.local" && make install

WORKDIR /home/lind/build/pip2
RUN python get-pip.py
RUN apt-get -y install rr

USER root

WORKDIR /usr/bin
RUN ln -sf make-3.82 make

WORKDIR /home/lind/
RUN rm -rf "/home/lind/build/" "/root/build/"
RUN chown -Rc lind:lind .

USER root

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
