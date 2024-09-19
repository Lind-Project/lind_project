#!/bin/bash
#
# try to ease the burden of building lind (rustposix, nacl, and glibc toolchain)
#
# Created by Chris Matthews <cmatthew@cs.uvic.ca>
# Updated by Joey Pabalinas <joeypabalinas@gmail.com>
# Updated by Nicholas Renner <nrenner@nyu.edu>
# Updated by Jonathan Singer <jes965@nyu.edu>

# version and usage strings

# export LD_LIBRARY_PATH just for builds
export LD_LIBRARY_PATH="/lib/glibc"

cd ..
readonly version=1.0.0-rc4
usage+=$'\n'"Lind $version NaCl Toolchain Build Script"$'\n'
usage+=$'\n'
usage+=$'Usage:\n'
usage+=$'\t'"$0 [-ehv] [targets]"$'\n'
usage+=$'\n'
usage+=$'Options:\n'
usage+=$'\t-e\tUse custom environment instead of defaults for directory paths.\n'
usage+=$'\t-h\tDisplay this help.\n'
usage+=$'\t-q\tSilent build (only errors are printed).\n'
usage+=$'\t-v\tDisplay script version.\n'

# track line number and arguments of current function
args="$*"
line="$LINENO"
# set to zero until we actually start building
start_time=0
# signals which trigger abort() function
err_signals=(ERR INT)
# use the default environment by default
default_env=1

# guard against incompatible compiler flags
unset CFLAGS CPATH CPPFLAGS CXXFLAGS LDFLAGS

# wrapper for desired logging command
#
function print() {
	printf '%s\n' "$@"
}

# calculate total build time
#
function get_build_time() {
	if ((start_time)); then
		end_time="$(date +%s)"
		diff_time="$((end_time - start_time))"
		print $'\a' "It took $diff_time seconds"
	fi
	print "" "All done." >&2
}

# print out error information and abort
#
function abort() {
	local func
	func="${FUNCNAME[1]}"
	print "" "[$0:$line] Error: [function: $func()] [arguments: ${args:-(nil)}]." "" >&2
	exit 1
}

# save stdout
exec 9>&1

# cleanup traps
trap -- '{ exec >&9; get_build_time; }' EXIT
trap -- '{ exec >&9; args="$*" line="$LINENO" abort; }' "${err_signals[@]}"

# option handling
while getopts :eqhv opt; do
	case "$opt" in
	# use custom environment
	e)
		default_env=0;;

	# only print errors
	q)
		exec >/dev/null;;

	# show usage information
	h)
		print "$usage" >&2
		exit;;

	# show version information
	v)
		print "Lind $version NaCl Toolchain Build Script" >&2
		exit;;

	# otherwise exit after printing the bad option and usage
	:|?)
		print "Illegal option letter: '$OPTARG'" "$usage" >&2
		false;;
	esac
done
shift "$((OPTIND - 1))"

if ((default_env)); then
	export LIND_PREFIX="${LIND_PREFIX:-$HOME}"
	export LIND_BASE="${LIND_BASE:-$LIND_PREFIX/lind_project}"
	export LIND_SRC="${LIND_SRC:-$LIND_BASE/lind}"
	export LIND_ENV_PATH="${LIND_ENV_PATH:-$LIND_SRC/lindenv}"
	export NACL_SDK_ROOT="${NACL_SDK_ROOT:-$LIND_ENV_PATH/sdk}"
	export PYTHON="${PYTHON:-python2}"
	export PNACLPYTHON="${PNACLPYTHON:-python2}"
	export LD_LIBRARY_PATH="${LD_LIBRARY_PATH:-/lib/glibc}"
	export PATH="${PATH}:-$LIND_PREFIX/lind_project/src/scripts"

	print
	print '======================================================'
	print 'USING DEFAULT LIND ENVIRONMENT:'
	print '======================================================'
	print
	cat <<-EOF
		export LIND_PREFIX="$LIND_PREFIX"
		export LIND_BASE="$LIND_BASE"
		export LIND_SRC="$LIND_SRC"
		export LIND_ENV_PATH="$LIND_ENV_PATH"
		export NACL_SDK_ROOT="$NACL_SDK_ROOT"
		export PYTHON="$PYTHON"
		export PNACLPYTHON="$PNACLPYTHON"
		export LD_LIBRARY_PATH="$LD_LIBRARY_PATH"
		export PATH="$PATH"
	EOF
	print
	print '======================================================'
	print
fi

if [[ -z "$LIND_ENV_PATH" ]]; then
	print "Need to set LIND_ENV_PATH" >&2
	false
fi
if [[ -z "$LIND_BASE" ]]; then
	print "Need to set LIND_BASE" >&2
	false
fi
if [[ -z "$LIND_SRC" ]]; then
	print "Need to set LIND_SRC" >&2
	false
fi

if command -v nproc >/dev/null 2>&1; then
	NPROC="$(($(nproc) + 2))"
else
	NPROC=6
fi
readonly JOBS="${JOBS:-$NPROC}"
readonly OS_NAME="$(uname -s)"
if [[ "$OS_NAME" == Darwin ]]; then
	readonly OS_SUBDIR="mac"
elif [[ "$OS_NAME" == Linux ]]; then
	readonly OS_SUBDIR="linux"
else
	readonly OS_SUBDIR="win"
fi
readonly MODE="dbg-$OS_SUBDIR"
readonly LIND_BASE="$LIND_BASE"
readonly LIND_SRC="$LIND_SRC"
readonly EXPERIMENTS_DIR="$LIND_BASE/lind_experiments"
readonly MISC_DIR="$LIND_BASE/src/scripts"
readonly NACL_SRC="$LIND_SRC/nacl_src"
readonly NACL_BASE="$NACL_SRC/native_client"
readonly NACL_TOOLCHAIN_BASE="$NACL_BASE/tools"
readonly LIND_GLIBC_SRC="$LIND_BASE/src/lind_glibc"
readonly NACL_GCC_SRC="$LIND_BASE/src/nacl-gcc"
readonly NACL_BINUTILS_SRC="$LIND_BASE/src/nacl-binutils"

readonly LIND_ENV_PATH="$LIND_ENV_PATH"
readonly LIND_ENV_PATH_BIN="$LIND_ENV_PATH/bin"
readonly LIND_ENV_PATH_SDK="$LIND_ENV_PATH/sdk"
readonly NACL_SDK_ROOT="$LIND_ENV_PATH_SDK"

readonly LIND_URL='https://github.com/Lind-Project/lind_project.git'
readonly LIND_EXPERIMENTS_URL='https://github.com/Lind-Project/lind_experiments.git'
readonly LIND_MISC_URL='https://github.com/Lind-Project/Lind-misc.git'
readonly LSS_URL='https://github.com/Lind-Project/linux-syscall-support.git'
readonly RUSTPOSIX_URL='https://github.com/Lind-Project/safeposix-rust.git'
readonly NACL_GCC_URL='https://github.com/Lind-Project/nacl-gcc.git'
readonly NACL_BINUTILS_URL='https://github.com/Lind-Project/nacl-binutils.git'
readonly NATIVE_CLIENT_URL='https://github.com/Lind-Project/native_client.git'
readonly LIND_GLIBC_URL='https://github.com/Lind-Project/Lind-GlibC.git'

readonly -a PYGREPL=(grep '-RPIl' -- '(^|[\s'"'"'"/-])(python)(\s|\.exe|\b)' './')
readonly -a PYGREPV=(grep '-Pv' -- '\.(git|.?html|cc?|h|exp|so\.old|so)\b')
readonly -a PYSED=(sed '-r' 's_(^|[\s'"'"'"/-])(python)(\.exe|\b)_\1\22\3_g')
readonly -a PNACLGREPL=(grep '-RIFwl' -- 'PNACLPYTHON' './')
readonly -a PNACLGREPV=(grep '-Pv' -- '\.(git|.?html|cc?|h|exp|so\.old|so)\b')
readonly -a PNACLSED=(sed -r 's_$\{?PNACLPYTHON\}?_python2_g')
readonly -a RSYNC=(rsync '--progress' '-ahhkpvA')

# clean downloaded sources
#
function clean_src() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	print "Cleaning Lind..."
	cd "$LIND_BASE"
	rm -rf -- lind_experiments lind-misc lss
	rm -rf -- safeposix-rust nacl-gcc nacl-binutils lind_glibc
}

# download sources
#
function download_src() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	local  nacl_rev
	local -A git_deps toolchain_deps

	# populate associative arrays
	git_deps[lind_experiments]="$LIND_EXPERIMENTS_URL"
	git_deps[lind-misc]="$LIND_MISC_URL"
	git_deps[lss]="$LSS_URL"
	git_deps[safeposix-rust]="$RUSTPOSIX_URL"
	git_deps[nacl-gcc]="$NACL_GCC_URL"
	git_deps[nacl-binutils]="$NACL_BINUTILS_URL"
	git_deps[lind_glibc]="$LIND_GLIBC_URL"
	git_deps[native_client]="$NATIVE_CLIENT_URL"
	toolchain_deps[gcc]="$NACL_GCC_SRC"
	toolchain_deps[glibc]="$LIND_GLIBC_SRC"
	toolchain_deps[binutils]="$NACL_BINUTILS_SRC"

	# clone and symlink dependencies
	mkdir -p "$LIND_BASE" "$LIND_SRC" "$NACL_SRC"
	
	cd "$LIND_BASE"

	# make sure we are in the git root of "Lind-Project/lind_project"
	git init
	if [[ "$(git config remote.origin.url)" != *Lind-Project/lind_project* ]]; then
		if ! git remote add origin "$LIND_URL"; then
			print "LIND_BASE already an initialized git directory" >&2
			false
		fi
		git fetch --all
		#git checkout master
	fi

	# symlink submodules
	git submodule update --init --recursive --remote .
	# iterate through all subdirectories, fetch from remote, restructure lind directory, and checkout to develop
	for dir in "${!git_deps[@]}"; do
		[[ ! -e "src/$dir" ]] && git clone "${git_deps[$dir]}" "src/$dir"
		rm -rf -- "${LIND_SRC:?}/$dir"
		ln -Trsfv "$LIND_BASE/src/$dir" "$LIND_SRC/$dir"
		(cd "$LIND_SRC/$dir" && git checkout develop)
        done

	# initialize native client toolchain
	ln -Trsfv "$LIND_BASE/src/native_client" "$NACL_BASE"
	cd "$LIND_BASE/src"
	# default to develop branch
	nacl_rev="${NATIVE_CLIENT_URL}@${BRANCH:-develop}"
	gclient config --name=native_client --git-deps "$nacl_rev"
	gclient sync

	# symlink toolchain dependencies
	cd "$NACL_TOOLCHAIN_BASE"
	rm -rf -- SRC
	make sync-pinned
	for dir in "${!toolchain_deps[@]}"; do
		rm -rf -- "SRC/$dir"
		ln -Trsfv "${toolchain_deps[$dir]}" "SRC/$dir"
		(cd "SRC/$dir")
	done

	# gclient overwrites our Docker Makefile
	cd "$LIND_BASE"
	git checkout -- Makefile
	rm -rfv -- _gclient_* _bad_scm

	# create lindenv dirs
	cd "$LIND_SRC"
	mkdir -p lindenv/
	mkdir -p lindenv/fs lindenv/bin
}

#checkout glibc, nacl, and safeposix-rust to develop
function update_all() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"
	
	local git_deps=(safeposix-rust lind_glibc native_client)
	
	cd "$LIND_BASE"
	
	git fetch --all
	print "Updating lind_project"
	(git checkout develop && git pull --rebase)
	
	# iterate through all subdirectories, checkout to develop, pull the updates
	for dir in "${git_deps[@]}"; do
		print "Updating $dir"
		(cd "$LIND_SRC/$dir" && git checkout develop && git pull --rebase)
        done
}



# wipe the entire modular build toolchain build tree, then rebuild it
# warning: this can take a while!
#
function clean_toolchain() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	cd "$NACL_TOOLCHAIN_BASE" && rm -rf out BUILD
}

# copy the toolchain into the lindenv subdir
#
function install_to_path() {
	RAWPOSIX_PATH="/home/lind/lind_project/src/safeposix-rust/tmp"

	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"
	mkdir /home/lind/lind_project/src/safeposix-rust/tmp
	# Copy files into the designed location (replace original lindfs)
	mkdir -p "${RAWPOSIX_PATH}/lib/glibc"
	cp -r "$NACL_TOOLCHAIN_BASE/out/nacl-sdk/x86_64-nacl/lib/"* "${RAWPOSIX_PATH}/lib/glibc/"
	cp "$LIND_ENV_PATH/librustposix.so" "${RAWPOSIX_PATH}/"

	print "Done."
}

# run applications test suites.
#
function test_apps() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	set +o errexit

	cd "~/lind/tests" && ./test.sh
}

# run glibc test suites.
#
function test_glibc() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	set -o errexit

	cd "$MISC_DIR/glibc_test"
	make clean
	PATH="$LIND_BASE:$PATH" make all
	cd ..
	rm -rfv -- lind.metadata linddata.*
	lind "$MISC_DIR/glibc_test/glibc_tester.nexe"
}


# update, build and test everything. if there is a problem, freak out.
#
function nightly_build() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	clean_nacl
	clean_src
	clean_toolchain

	download_src
	build_nacl
	build_rustposix
	build_glibc
	install_to_path

}

function build_rustposix() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	print "Building RustPOSIX"
    cd "$LIND_BASE/src/safeposix-rust"
	if [[ "$DEBUG_RUSTPOSIX" == "true" ]]; then 
        cargo build
        cp "target/debug/librustposix.so"  "$LIND_ENV_PATH/librawposix.so"
        # cp "target/debug/lind_fs_utils"  "$LIND_ENV_PATH_BIN/lind_fs_utils"
    elif [[ "$DEBUG_RUSTPOSIX" == "fast" ]]; then 
        RUSTFLAGS="-g" cargo build --release
        cp "target/release/librustposix.so"  "$LIND_ENV_PATH/librawposix.so"
        # cp "target/release/lind_fs_utils"  "$LIND_ENV_PATH_BIN/lind_fs_utils"
    else
        cargo build --release
        cp "target/release/librustposix.so"  "$LIND_ENV_PATH/librawposix.so"
        # cp "target/release/lind_fs_utils"  "$LIND_ENV_PATH_BIN/lind_fs_utils"
    fi
	print "Done."
}

# run the nacl build.
#
function build_nacl() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	print "Building NaCl"

	# the pnacl script doesn't respect PYTHON or PNACLPYTHON
	cd "$NACL_BASE/toolchain/pnacl_linux_x86/newlib/bin"
	"${PYGREPL[@]}" 2>/dev/null \
		| "${PYGREPV[@]}" \
		| while read -r file; do
			# preserve executability
			"${PYSED[@]}" <"$file" >"$file.new"
			cat <"$file.new" >"$file"
			rm -f -- "$file.new"
		done

	# checkout the correct revision
	cd "$NACL_BASE"
	if [[ -n "$BRANCH" ]]; then
		git fetch --all
		# TODO: make branch names consistent across our repositories and
		# avoid the need for the `|| true` here
		#
		# Some branches such as the lind branch in native_client don't have
		# matching branches in the other submodules and the checkout fails
		# if you tried to checkout, say, the lind branch of nacl_repy
		#
		# -jp
		git checkout "$BRANCH" || true
	fi
	# skip broken tests for now
	PATH="$LIND_BASE:$PATH" \
		python2 ./scons.py \
			--verbose \
			--mode="$MODE,nacl" \
			--nacl_glibc \
			-j"$JOBS" \
			nacl_pic=1 \
			werror=0 \
			skip_trusted_tests=1 \
			disable_flaky_tests=1 \
			platform=x86-64
	print "Done building NaCl"
}

# run clean on nacl build.
#
function clean_nacl() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	cd "$NACL_BASE"
	PATH="$LIND_BASE:$PATH" \
		python2 ./scons.py \
			--verbose \
			--mode="$MODE,nacl" \
			--nacl_glibc \
			-j"$JOBS" \
			-c \
			nacl_pic=1 \
			werror=0 \
			platform=x86-64
	print "Done Cleaning NaCl"
}

# build glibc from source
#
function build_glibc() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	PERL_VER=$(perl -e 'print "$^V"' | cut -c 2-5)
	export PERL5LIB=/usr/lib/perl5/$PERL_VER

	# the build is long and boring, so execute this first if it exists
	print ""
	fortune 2>/dev/null || print "Fortune Not Found. Skipping." >&2
	print "" "Copying component.h header to glibc: "

	print "Building glibc"

	# checkout the correct revision
	cd "$NACL_BASE"
	if [[ -n "$BRANCH" ]]; then
		git fetch --all
		# TODO: make branch names consistent across our repositories and
		# avoid the need for the `|| true` here
		#
		# Some branches such as the lind branch in native_client don't have
		# matching branches in the other submodules and the checkout fails
		# if you tried to checkout, say, the lind branch of nacl_repy
		#
		# -jp
		git checkout "$BRANCH" || true
	fi
	# turns out this works better if you do it from the nacl base dir
	cd "$NACL_TOOLCHAIN_BASE"
	rm -rf -- BUILD out
	make clean
	PATH="$LIND_BASE:$PATH" make -j"$JOBS" build-with-glibc

	print "Done building toolchain"
}

# perform an incremental glibc build
#
function update_glibc() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	cd "$NACL_TOOLCHAIN_BASE"
	PATH="$LIND_BASE:$PATH" make -j"$JOBS" updateglibc
}

# perform a clean glibc build
#
function update_glibc2() {
	trap -- 'args="$*" line="$LINENO" abort' "${err_signals[@]}"

	cd "$NACL_TOOLCHAIN_BASE"
	rm -rf -- BUILD/stamp-glibc64
	PATH="$LIND_BASE:$PATH" make -j"$JOBS" BUILD/stamp-glibc64
}

# prompt for target if none given on command line
PS3=$'\n'"Build which target? "
list=(all update rustposix nacl glibc install)
list+=(cleanall cleannacl cleansources cleantoolchain)
list+=(updateglibc updateglibc2 docker nightly testall)
list+=(testapps testglibc download)
if ((!$#)); then
	select choice in "${list[@]}"; do
		set -- "$choice"
		break
	done
fi

# all scripts assume we start here
start_time="$(date +%s)"

# show command that will be executed
print "" "Command line arguments: $0 $*" ""

for word in "$@"; do
	case "$word" in
	download)
		download_src;;
	update)
		update_all;;
	rustposix)
		build_rustposix;;
	nacl)
		build_nacl;;
	glibc)
		build_glibc;;
	all)
		build_rustposix
		build_nacl
		build_glibc
		install_to_path;;
	install)
		install_to_path;;
	cleanall)
		clean_nacl
		clean_src
		clean_toolchain;;
	cleannacl)
		clean_nacl;;
	cleansources)
		clean_src;;
	cleantoolchain)
		clean_toolchain;;
	updateglibc)
		update_glibc;;
	updateglibc2)
		update_glibc2;;
	nightly)
		print "Nightly build"
		nightly_build;;
	testall)
		print "Testing all"
		test_apps
		test_glibc;;
	testapps)
		print "Testing applications"
		test_apps;;
	testglibc)
		print "Testing glibc"
		test_glibc;;
	*)
		print "Error: Did not find a build target for that number. Exiting..." >&2
		abort;;
	esac
done
