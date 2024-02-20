FROM amd64/ubuntu:18.04

USER root

ADD make-3.82/ /home/make-3.82

RUN apt update
RUN apt install build-essential -y
RUN apt install -y software-properties-common wget
RUN apt install -y gcc-4.8
RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
RUN add-apt-repository 'deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic main'
RUN echo "deb-src http://apt.llvm.org/bionic/ llvm-toolchain-bionic main" >> /etc/apt/sources.list
RUN apt-get update -y
RUN apt-get update && apt-get install -y \
    build-essential \
    git mercurial rsync make perl clang lynx ltrace \
	w3m gawk procps ruby strace gdb reptyr ed \
  	llvm-7 llvm-7-dev clang-7 llvm-7-tools vim \
  	libomp-7-dev elfutils libelf-dev gdb less \
  	netcat htop bc ctags \ 
 	libncurses-dev gcc-multilib gperf diffutils \
	google-perftools texinfo fortune-mod gnupg highlight fasd \
 	python2.7 p7zip fuse ack \
	isc-dhcp-client iputils-ping iproute2 \
 	net-tools openresolv openssh-server subversion \
 	tree psmisc lsof wget pinfo asp unrar inetutils-tools \
 	tmux screen bash-completion mlocate ncdu \
 	bind9 bind9utils bind9-doc dnsutils cowsay \
 	util-linux help2man rlwrap cmake ninja-build capnproto \
    glibc-source libxcrypt-dev linux-tools-generic autoconf autotools-dev automake
RUN apt update

WORKDIR /home/make-3.82
RUN export CC=gcc-4.8
RUN ./configure
RUN make CC=gcc-4.8
RUN make install

RUN bash


