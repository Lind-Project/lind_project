if [ -f /etc/lsb-release ]; then
    . /etc/lsb-release
    if [ "$DISTRIB_ID" = "Ubuntu" ]; then
        export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
    fi
fi

./configure CC=/usr/local/gcc-4.4.3/bin/gcc CXX=/usr/local/gcc-4.4.3/bin/g++
make
