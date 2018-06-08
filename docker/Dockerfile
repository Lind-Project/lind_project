FROM archlinux/base

ENV LIND_BASE=/usr/lind_project LIND_SRC=/usr/lind_project/lind
ENV REPY_PATH=/usr/lind_project/lind/repy NACL_SDK_ROOT=/usr/lind_project/lind/repy/sdk
ENV LIND_MONITOR=/usr/lind_project/reference_monitor
ENV LD_LIBRARY_PATH=/lib/glibc
ENV PNACLPYTHON=/usr/bin/python2

WORKDIR /usr
RUN sed -i '/\[multilib\]/,/^$/ s/^#//' /etc/pacman.conf
RUN pacman -Syu --noconfirm base-devel subversion git rsync make \
    gcc-libs lib32-gcc-libs gperf gperftools texinfo python2 \
    python2-pip python2-setuptools python2-virtualenv python-virtualenvwrapper
RUN git clone https://github.com/Lind-Project/lind_project.git

WORKDIR /usr/lind_project
RUN bash -c './caging.sh download || true'
RUN ln -Trsfv /usr/bin/python2 /usr/bin/python
RUN bash -c './caging.sh nacl || true'
RUN ln -Trsfv /usr/bin/python3 /usr/bin/python
RUN bash -c './caging.sh buildglibc || true'
RUN bash -c './caging.sh repy || true'
RUN bash -c './caging.sh install || true'
RUN bash -c './caging.sh liblind || true'

ENTRYPOINT /bin/bash
