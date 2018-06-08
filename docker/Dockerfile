FROM archlinux/base

ENV LIND_BASE=/usr/lind_project LIND_SRC=/usr/lind_project/lind
ENV REPY_PATH=/usr/lind_project/lind/repy NACL_SDK_ROOT=/usr/lind_project/repy/sdk
ENV LIND_MONITOR=/usr/lind_project/reference_monitor LD_LIBRARY_PATH=/lib/glibc
ENV NACL_SDK_ROOT=/usr/lind_project/lind/repy/sdk
ENV PYTHON=/usr/bin/python2 PNACLPYTHON=/usr/bin/python2

WORKDIR /usr
RUN sed -i '/\[multilib\]/,/^$/ s/^#//' /etc/pacman.conf
RUN pacman -Syu --noconfirm base-devel subversion git rsync make gcc-libs lib32-gcc-libs gperf gperftools texinfo
RUN pacman -Syu --noconfirm python2 python2-pip python2-setuptools python2-virtualenv python-virtualenvwrapper
RUN git clone https://github.com/Lind-Project/lind_project.git
RUN ln -Trsfv /usr/bin/python2 /usr/bin/python

WORKDIR /usr/lind_project
RUN ./caging.sh all
