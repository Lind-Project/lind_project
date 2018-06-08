FROM archlinux/base

WORKDIR /usr
RUN sed -ni '/\[multilib\]/,/^$/ s/^#//p' /etc/pacman.conf
RUN pacman -Syu --noconfirm base-devel python2 python2-pip python2-setuptools python2-virtualenv python-virtualenvwrapper subversion git rsync make autotools gcc-libs lib32-gcc-libs
RUN git clone https://github.com/Lind-Project/lind_project.git
RUN ln -Trsfv /usr/bin/python2 /usr/bin/python && ln -Trsfv /usr/bin/pip2 /usr/bin/pip
RUN mkdir -p "$HOME/.virtualenvs"

ENV PATH="$HOME/.local/bin:$PATH"
ENV LIND_BASE=/usr/lind_project LIND_SRC=/usr/lind_project/lind
ENV REPY_PATH=/usr/lind_project/lind/repy NACL_SDK_ROOT=/usr/lind_project/repy/sdk
ENV LIND_MONITOR=/usr/lind_project/reference_monitor
ENV LD_LIBRARY_PATH=/lib/glibc NACL_SDK_ROOT=/usr/lind_project/lind/repy/sdk
ENV VIRTUALENVWRAPPER_PYTHON=/usr/bin/python2
ENV VIRTUALENVWRAPPER_VIRTUALENV=/usr/bin/virtualenv2
ENV WORKON_HOME="$HOME/.virtualenvs"

RUN pip install virtualenvwrapper
RUN . /usr/bin/virtualenvwrapper.sh
RUN mkvirtualenv lind
RUN workon lind
RUN pip install -U gclient wheel
RUN easy_install-2.7 -U setuptools
RUN easy_install-2.7 SCons

WORKDIR /usr/lind_project
RUN ./caging.sh all
