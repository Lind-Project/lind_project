#!/bin/bash

# ===========
## variables:

GMP=gmp-6.1.0.tar.bz2
MPFR=mpfr-3.1.4.tar.bz2
MPC=mpc-1.0.3.tar.gz
ISL=isl-0.12.2.tar.bz2
CLOOG=cloog-0.18.1.tar.gz
CLOOG_PPL=cloog-ppl-0.15.11.tar.gz

MIRROR=ftp://gcc.gnu.org/pub/gcc/infrastructure

# we need a pre-release version for ppl so special-case it
# PPL=ppl-1.2pre4.tar.bz2
# PPL_MIRROR=http://bugseng.com/products/ppl/download/ftp/snapshots
PPL=ppl-0.10.2.tar.gz
PPL_MIRROR=https://gcc.gnu.org/pub/gcc/infrastructure
# PPL_MIRROR=http://bugseng.com/external/ppl/download/ftp/releases/0.12.1

# ===========
## functions:

function mkdircd() {
	mkdir -p "$@"
	# cd to the last argument
	cd  "${@: -1}" || return 1
}

function build_gmp() {
	mkdircd build
	../configure --disable-shared --enable-static --prefix="$PREFIX"/gmp
	make -j "$THREADS" && make check && make install
}

function build_mpfr() {
	mkdircd build
	../configure --with-gmp="$PREFIX"/gmp --disable-shared --enable-static \
		--prefix="$PREFIX"/mpfr
	make -j "$THREADS" && make install
}

function build_mpc() {
	mkdircd build
	../configure --with-gmp="$PREFIX"/gmp --with-mpfr="$PREFIX"/mpfr \
		--disable-shared --enable-static --prefix="$PREFIX"/mpc
	make -j "$THREADS" && make install
}

function build_isl() {
	mkdircd build
	../configure --with-gmp-prefix="$PREFIX"/gmp --disable-shared \
		--enable-static --prefix="$PREFIX"/isl
	make -j "$THREADS" && make install
}

function build_cloog() {
	mkdircd build
	../configure --with-gmp-prefix="$PREFIX"/gmp \
		--with-isl-prefix="$PREFIX"/isl --disable-shared \
		--enable-static --prefix="$PREFIX"/cloog
	make -j "$THREADS" && make install
}

function build_gcc() {
	LD_LIBRARY_PATH="$PREFIX"/gmp/lib:"$PREFIX"/mpfr/lib:"$PREFIX"/mpc/lib
	LD_LIBRARY_PATH="$LD_LIBRARY_PATH":"$PREFIX"/isl/lib:"$PREFIX"/cloog/lib
	C_INCLUDE_PATH="$PREFIX"/gmp/include:"$PREFIX"/mpfr/include
	C_INCLUDE_PATH="$C_INCLUDE_PATH":"$PREFIX"/mpc/include
	C_INCLUDE_PATH="$C_INCLUDE_PATH":"$PREFIX"/isl/include
	C_INCLUDE_PATH="$C_INCLUDE_PATH":"$PREFIX"/cloog/include
	CPLUS_INCLUDE_PATH="$PREFIX"/gmp/include:"$PREFIX"/mpfr/include
	CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH":"$PREFIX"/mpc/include
	CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH":"$PREFIX"/isl/include
	CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH":"$PREFIX"/cloog/include
	export LD_LIBRARY_PATH C_INCLUDE_PATH CPLUS_INCLUDE_PATH
	mkdircd build
	../configure --with-gmp="$PREFIX"/gmp --with-mpfr="$PREFIX"/mpfr \
		--with-mpc="$PREFIX"/mpc --with-isl="$PREFIX"/isl \
		--with-cloog="$PREFIX"/cloog --disable-shared \
		--enable-static --disable-multilib --prefix="$PREFIX"/gcc \
		--enable-languages=c,c++,fortran
	make -j "$THREADS" bootstrap && make install
}

function download() {
	(
	local dir="${1%%-*}"
	mkdir -p "$dir"
	cd "$dir" || return 1
	rm -rf ./*
	if [[ "$dir" == ppl ]]; then
		[[ -f "$1" ]] || wget "$PPL_MIRROR"/"$1"
	else
		[[ -f "$1" ]] || wget "$MIRROR"/"$1"
	fi
	)
}

function extract() {
	(
	local dir="${1%%-*}"
	cd "$dir" || return 1
	if [[ -f "$1" ]]; then
		case "$1" in
		*.tar.bz2)
			tar xvjf "$1" ;;
		*.tar.gz)
			tar xvzf "$1" ;;
		*.bz2)
			bunzip2 "$1" ;;
		*.rar)
			unrar x "$1" ;;
		*.gz)
			gunzip "$1" ;;
		*.tar)
			tar xvf "$1" ;;
		*.tbz2)
			tar xvjf "$1" ;;
		*.tgz)
			tar xvzf "$1" ;;
		*.zip)
			unzip "$1" ;;
		*.Z)
			uncompress "$1" ;;
		*.7z)
			7z x "$1" ;;
		*)
			echo "I don't know how to extract '$1" ;;
		esac
		mv "$dir"*/* ./
	else
		echo "'$1' is not a valid file!"
	fi
	)
}

# ======================
## download and extract:

download "$GMP"
extract "$GMP"

download "$MPFR"
extract "$MPFR"

download "$MPC"
extract "$MPC"

download "$ISL"
extract "$ISL"

download "$PPL"
extract "$PPL"

download "$CLOOG"
extract "$CLOOG"

download "$CLOOG_PPL"
extract "$CLOOG_PPL"
