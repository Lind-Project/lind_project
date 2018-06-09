FROM archlinux/base

ENV LIND_BASE=/usr/lind_project
ENV LIND_SRC=/usr/lind_project/lind
ENV LIND_MONITOR=/usr/lind_project/reference_monitor
ENV NACL_SDK_ROOT=/usr/lind_project/lind/repy/sdk
ENV REPY_PATH=/usr/lind_project/lind/repy
ENV LD_LIBRARY_PATH=/lib/glibc
ENV PYTHON=/usr/bin/python2
ENV PNACLPYTHON=/usr/bin/python2
ENV PATH="$HOME/.local/bin:$PATH"

RUN sed -i '/^#\[multilib\]/,/^$/ s/^#//' /etc/pacman.conf
RUN pacman -Syu --noconfirm base-devel subversion git rsync make screen ncurses \
    clang compiler-rt lib32-clang lib32-llvm lib32-llvm-libs llvm llvm-libs openmp \
    elfutils libelf gdb gnu-netcat vim zsh zsh-completions grml-zsh-config vim ed \
    gcc-libs lib32-gcc-libs gperf gperftools texinfo fortune-mod bash-completion \
    python2 python2-pip python2-setuptools python2-virtualenv python-virtualenvwrapper

WORKDIR /root
RUN mkdir -p ~/.terminfo ~/.local
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
RUN tar xvf texinfo-4.13.tar.gz
RUN bash -c 'cd texinfo-4.13 &&./configure --PREfix=/root/.local && PREFIX=/root/.local make install'
RUN pacman -U --noconfirm /root/terminfox-italics.pkg.tar.xz
RUN tic screen-256color-italic
RUN ip a
RUN passwd -d
RUN systemctl enable --now sshd.socket

WORKDIR /usr
RUN ln -Trsfv /usr/bin/python{2,}
RUN ln -Trsfv /usr/bin/pip{2,}
RUN git clone https://github.com/Lind-Project/lind_project.git

WORKDIR /usr/lind_project
RUN screen -dmLS lind env -u CFLAGS CPATH CPPFLAGS CXXFLAGS LDFLAGS LIBRARY_PATH /caging.sh all
RUN screen -x lind

ENTRYPOINT /bin/bash
