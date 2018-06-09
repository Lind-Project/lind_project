FROM archlinux/base

ENV PATH="$HOME/.local/bin:$PATH"
env CFLAGS= CPATH= CPPFLAGS= CXXFLAGS= LDFLAGS= LIBRARY_PATH=
ENV LIND_BASE=/usr/lind_project
ENV LIND_SRC=/usr/lind_project/lind
ENV LIND_MONITOR=/usr/lind_project/reference_monitor
ENV NACL_SDK_ROOT=/usr/lind_project/lind/repy/sdk
ENV REPY_PATH=/usr/lind_project/lind/repy
ENV LD_LIBRARY_PATH=/lib/glibc
ENV PYTHON=/usr/bin/python2
ENV PNACLPYTHON=/usr/bin/python2

WORKDIR /usr/bin
RUN sed -i '/^#\[multilib\]/,/^$/ s/^#//' /etc/pacman.conf
RUN pacman -Syu --noconfirm base-devel subversion git rsync make screen ncurses iproute2 \
    clang compiler-rt lib32-clang lib32-llvm lib32-llvm-libs llvm llvm-libs openmp \
    elfutils libelf gdb gnu-netcat vim zsh zsh-completions grml-zsh-config vim ed \
    gcc-libs lib32-gcc-libs gperf gperftools texinfo fortune-mod bash-completion \
    python2 python2-pip python2-setuptools python2-virtualenv python-virtualenvwrapper
RUN ln -Trsfv /usr/bin/python{2,}
RUN ln -Trsfv /usr/bin/pip{2,}

WORKDIR /root
RUN mkdir -pv /root/.terminfo /root/.local
RUN curl -sO http://ftp.gnu.org/gnu/texinfo/texinfo-4.13.tar.gz
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.profile
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.screenrc
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.inputrc
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.aliases
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.bashrc
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.bash_profile
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.bash_functions
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/terminfo-italics.pkg.tar.xz
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/screen-256color-italic.terminfo
RUN pacman -U --noconfirm /root/terminfo-italics.pkg.tar.xz
RUN tic /root/screen-256color-italic.terminfo
RUN ip addr
RUN passwd -d
RUN systemctl enable --now sshd.socket
RUN tar xvf texinfo-4.13.tar.gz

WORKDIR /root/texinfo-4.13
RUN ./configure --prefix=/root/.local
RUN make install PREFIX=/root/.local

WORKDIR /usr
RUN git clone https://github.com/Lind-Project/lind_project.git

WORKDIR /usr/lind_project
RUN screen -dmLS lind
RUN screen -S lind -t build -X screen bash -c './caging.sh all; read -rsn1 -p$"Press any key to exit."; echo'
RUN screen -x lind -t build

ENTRYPOINT /bin/bash
