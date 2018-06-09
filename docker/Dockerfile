FROM archlinux/base

ENV LIND_BASE=/usr/lind_project LIND_SRC=/usr/lind_project/lind
ENV REPY_PATH=/usr/lind_project/lind/repy NACL_SDK_ROOT=/usr/lind_project/lind/repy/sdk
ENV LIND_MONITOR=/usr/lind_project/reference_monitor
ENV LD_LIBRARY_PATH=/lib/glibc
ENV PYTHON=/usr/bin/python2
ENV PNACLPYTHON=/usr/bin/python2

WORKDIR /usr
RUN sed -i '/\[multilib\]/,/^$/ s/^#//' /etc/pacman.conf
RUN pacman -Syu --noconfirm base-devel subversion git rsync make openmp \
    clang compiler-rt lib32-clang lib32-llvm lib32-llvm-libs llvm llvm-libs \
    gcc-libs lib32-gcc-libs gperf gperftools texinfo fortune-mod bash-completion \
    python2 python2-pip python2-setuptools python2-virtualenv python-virtualenvwrapper
RUN git clone https://github.com/Lind-Project/lind_project.git
RUN ln -Trsfv /usr/bin/python{2,}

WORKDIR /usr/lind_project
RUN bash -c './caging.sh all'
RUN curl -o /root/.profile https://raw.githubusercontent.com/alyptik/dotfiles/master/.profile
RUN curl -o /root/.inputrc https://raw.githubusercontent.com/alyptik/dotfiles/master/.inputrc
RUN curl -o /root/.aliases https://raw.githubusercontent.com/alyptik/dotfiles/master/.aliases
RUN curl -o /root/.bashrc https://raw.githubusercontent.com/alyptik/dotfiles/master/.bashrc
RUN curl -o /root/.bash_functions https://raw.githubusercontent.com/alyptik/dotfiles/master/.bash_functions
RUN curl -o /root/.bash_profile https://raw.githubusercontent.com/alyptik/dotfiles/master/.bash_profile

ENTRYPOINT /bin/bash
