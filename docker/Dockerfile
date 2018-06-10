FROM archlinux/base

ENV PATH="/root/.local/bin:$PATH"
ENV WORKON_HOME=/usr/lind_project/virtualenvs
ENV VIRTUALENVWRAPPER_PYTHON=/usr/bin/python2
ENV VIRTUALENVWRAPPER_VIRTUALENV=/usr/bin/virtualenv2
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
RUN pacman -Syu --noconfirm base-devel subversion rsync make screen ncurses perl ruby \
    clang compiler-rt lib32-clang lib32-llvm lib32-llvm-libs llvm llvm-libs openmp \
    elfutils libelf gdb gnu-netcat vim zsh zsh-completions grml-zsh-config vim ed \
    gcc-libs lib32-gcc-libs gperf gperftools texinfo fortune-mod bash-completion git \
    python2 python2-pip python2-setuptools python2-virtualenv python-virtualenvwrapper
RUN ln -Trsfv /usr/bin/python{2,}
RUN ln -Trsfv /usr/bin/pip{2,}

WORKDIR /root
RUN mkdir -pv /root/.local/bin /root/.terminfo
RUN curl -sO http://ftp.gnu.org/gnu/texinfo/texinfo-4.13.tar.gz
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.profile
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.screenrc
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.inputrc
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.aliases
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.bashrc
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.bash_profile
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/.bash_functions
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/terminfo-italics.pkg.tar.xz
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/make-3.82.pkg.tar.xz
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/screen-256color-italic.terminfo
RUN pacman -U --noconfirm /root/terminfo-italics.pkg.tar.xz /root/make-3.82.pkg.tar.xz
RUN tic /root/screen-256color-italic.terminfo
RUN tar xvf texinfo-4.13.tar.gz
RUN pip2 install --user virtualenv2 virtualenvwrapper

WORKDIR /root/texinfo-4.13
RUN ./configure --prefix=/root/.local
RUN make install PREFIX=/root/.local

WORKDIR /root/.local/bin
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/scripts/e
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/scripts/g
RUN curl -sO https://raw.githubusercontent.com/alyptik/dotfiles/master/scripts/tl
RUN chmod +x e g tl

WORKDIR /usr
RUN git config --global user.email "nomail@nomail.com"
RUN git config --global user.name "Lind Docker Build"
RUN git clone -j4 --recursive --shallow-submodules https://github.com/Lind-Project/lind_project.git

WORKDIR /usr/lind_project
RUN ./mklind download
RUN ./mklind nacl
RUN ./mklind repy
RUN ./mklind buildglibc
RUN ./mklind install
RUN ./mklind liblind

ENTRYPOINT /bin/bash
