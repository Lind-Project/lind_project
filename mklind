#!/bin/bash
#
# try to ease the burden of building lind (repy, nacl, and glibc toolchain)
#
# Created by Chris Matthews <cmatthew@cs.uvic.ca>
# Updated by Joey Pabalinas <joeypabalinas@gmail.com>

# version and usage strings
readonly version=0.9.0-alpha
usage+=$'\n'"Lind $version NaCl Toolchain Build Script"$'\n'
usage+=$'\n'
usage+=$'Usage:\n'
usage+=$'\t'"$0 [-ehv] [targets]"$'\n'
usage+=$'\n'
usage+=$'Options:\n'
usage+=$'\t-e\tUse default environment.\n'
usage+=$'\t-h\tDisplay this help.\n'
usage+=$'\t-v\tDisplay script version.\n'

# uncomment this to print each command as they are executed
# ≈set -o xtrace

# uncomment this for debugging. will stop on any failed commands
# set -o errexit

# uncomment this to dump time profiling information out to a file to see where the script is slow
# ps4='+ $(date "+%s.%n")\011 '
# exec 3>&2 2> bashstart.$$.log
# set -x

# track currently executing function
cur_func="${FUNCNAME[0]}"
cur_line="$LINENO"
args="$*"

# set to zero until we actually start building
start_time=0

# wrapper for desired logging command
#
function print() {
	printf '%s\n' "$@"
	# notify-send \
	#   --icon=/usr/share/icons/gnome/256x256/apps/utilities-terminal.png \
	#   "build script" "$*" >/dev/null 2>&1
}

# calculate total build time
#
function get_build_time() {
	if ((start_time)); then
		end_time="$(date +%s)"
		diff_time="$((end_time - start_time))"
		print $'\a' "It took $diff_time seconds"
	fi
	print "" "All done."
}

# print out error information and abort
#
function abort() {
	print "" "[$0:$cur_line] Error: [function: $cur_func()] [arguments: $args]." >&2
	exit 1
}

# cleanup traps
trap -- 'get_build_time' EXIT
trap -- 'cur_line="$LINENO" args="$*" abort' ERR

# guard against incompatible compiler flags
unset CFLAGS CPATH CPPFLAGS CXXFLAGS LDFLAGS

# check for flags
for word; do
	case "$word" in
	-*e*)
		# setup and print out the default environment
		export LIND_PREFIX="${LIND_PREFIX:-$HOME}"
		export LIND_BASE="${LIND_BASE:-$LIND_PREFIX/lind_project}"
		export LIND_SRC="${LIND_SRC:-$LIND_PREFIX/lind_project/lind}"
		export LIND_MONITOR="${LIND_MONITOR:-$LIND_PREFIX/lind_project/reference_monitor}"
		export NACL_SDK_ROOT="${NACL_SDK_ROOT:-$LIND_PREFIX/lind_project/lind/repy/sdk}"
		export REPY_PATH="${REPY_PATH:-$LIND_PREFIX/lind_project/lind/repy}"
		export PYTHON="${PYTHON:-python2}"
		export PNACLPYTHON="${PNACLPYTHON:-python2}"
		export LD_LIBRARY_PATH="${LD_LIBRARY_PATH:-/lib/glibc}"

		print
		print '======================================================'
		print 'USING DEFAULT NACL ENVIRONMENT:'
		print '======================================================'
		print
		cat <<-EOF
			export LIND_PREFIX="$LIND_PREFIX"
			export LIND_BASE="$LIND_BASE"
			export LIND_SRC="$LIND_SRC"
			export LIND_MONITOR="$LIND_MONITOR"
			export NACL_SDK_ROOT="$NACL_SDK_ROOT"
			export REPY_PATH="$REPY_PATH"
			export PYTHON="$PYTHON"
			export PNACLPYTHON="$PNACLPYTHON"
			export LD_LIBRARY_PATH="$LD_LIBRARY_PATH"
		EOF
		print
		print '======================================================'
		print
		# remove -e flag after setting up environment using '!' as the sentinel
		mapfile -t argv < <(printf '%s\n' "${@//-*e*/!}" | sed '/!/d' | sort | uniq)
		set -- "${argv[@]}"
		unset argv
		;;

	-*v*)
		# exit after printing version
		print "Lind $version NaCl Toolchain Build Script" >&2
		exit
		;;

	-*h*)
		# exit after printing usage
		print "$usage" >&2
		exit
		;;

	-*)
		# stop processing options after '-' or '--'
		if [[ "$word" == -- || "$word" == - ]]; then
			break
		# ignore more than two '-'
		elif [[ -z "${word//-/}" ]]; then
			continue
		fi
		# otherwise exit after printing the bad option and usage
		print "" "Unknown option letter: '${word//-/}'" "$usage" >&2
		false
		;;
	esac
done

if [[ -z "$REPY_PATH" ]]; then
	print "Need to set REPY_PATH" >&2
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
readonly MISC_DIR="$LIND_BASE/lind-misc"
readonly NACL_SRC="$LIND_SRC/nacl_src"
readonly NACL_BASE="$NACL_SRC/native_client"
readonly NACL_TOOLCHAIN_BASE="$NACL_BASE/tools"
readonly LIND_GLIBC_SRC="$LIND_BASE/lind_glibc"
readonly NACL_GCC_SRC="$LIND_BASE/nacl-gcc"
readonly NACL_BINUTILS_SRC="$LIND_BASE/nacl-binutils"
readonly NACL_REPY="$LIND_BASE/nacl_repy"
readonly NACL_PORTS_DIR="$LIND_BASE/naclports"

readonly REPY_PATH="$REPY_PATH"
readonly REPY_PATH_BIN="$REPY_PATH/bin"
readonly REPY_PATH_REPY="$REPY_PATH/repy"
readonly REPY_PATH_LIB="$REPY_PATH/lib"
readonly REPY_PATH_SDK="$REPY_PATH/sdk"
readonly NACL_SDK_ROOT="$REPY_PATH_SDK"

readonly LIND_URL='https://github.com/Lind-Project/lind_project.git'
readonly LIND_EXPERIMENTS_URL='https://github.com/Lind-Project/lind_experiments.git'
readonly LIND_MISC_URL='https://github.com/Lind-Project/Lind-misc.git'
readonly THIRD_PARTY_URL='https://github.com/Lind-Project/third_party.git'
readonly LSS_URL='https://github.com/Lind-Project/linux-syscall-support.git'
readonly NACL_REPY_URL='https://github.com/Lind-Project/nacl_repy.git'
readonly NACL_GCC_URL='https://github.com/Lind-Project/nacl-gcc.git'
readonly NACL_BINUTILS_URL='https://github.com/Lind-Project/nacl-binutils.git'
readonly NACL_GCLIENT_URL='https://github.com/Lind-Project/native_client.git@lind_fork'
readonly NACL_PORTS_URL='https://chromium.googlesource.com/external/naclports.git'
readonly LIND_GLIBC_URL='https://github.com/Lind-Project/Lind-GlibC.git'

readonly -a PYGREPL=(grep '-RPIl' -- '(^|[\s'"'"'"/-])(python)(\s|\.exe|\b)' './')
readonly -a PYGREPV=(grep '-Pv' -- '\.(git|.?html|cc?|h|exp|so\.old|so)\b')
readonly -a PYSED=(sed '-r' 's_(^|[\s'"'"'"/-])(python)(\.exe|\b)_\1\22\3_g')
readonly -a PNACLGREPL=(grep '-RIFwl' -- 'PNACLPYTHON' './')
readonly -a PNACLGREPV=(grep '-Pv' -- '\.(git|.?html|cc?|h|exp|so\.old|so)\b')
readonly -a PNACLSED=(sed -r 's_$\{?PNACLPYTHON\}?_python2_g')
readonly -a RSYNC=(rsync '-Avpa' '--progress=status2' '--force')

# clean downloaded sources
#
function clean_src() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	print "Cleaning $LIND_BASE"
	cd "$LIND_BASE"
	rm -rf lind_experiments lind-misc third_party lss
	rm -rf nacl_repy nacl-gcc nacl-binutils lind_glibc
	print "Cleaning $NACL_SRC"
	cd "$NACL_SRC"
	rm -rf native_client
	print "Cleaning $NACL_PORTS_DIR"
	cd "$NACL_PORTS_DIR"
	rm -rfv src

	cur_func="${FUNCNAME[1]}"
}

# download sources
#
function download_src() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	local pip_bin pip_ver
	local -A git_deps

	# clone and symlink dependencies
	mkdir -p "$LIND_BASE" "$LIND_SRC"
	cd "$LIND_BASE"

	# make sure we are in the git root of "Lind-Project/lind_project"
	if [[ "$(git config remote.origin.url)" != *lind_project* ]]; then
		if ! git remote add origin "$LIND_URL"; then
			print "LIND_BASE already an initialized git directory" >&2
			false
		fi
		git fetch --all
		git checkout master
	fi
	git submodule update --checkout --init --recursive --remote .
	git_deps[lind_experiments]="$LIND_EXPERIMENTS_URL"
	git_deps[lind-misc]="$LIND_MISC_URL"
	git_deps[third_party]="$THIRD_PARTY_URL"
	git_deps[lss]="$LSS_URL"
	git_deps[nacl_repy]="$NACL_REPY_URL"
	git_deps[nacl-gcc]="$NACL_GCC_URL"
	git_deps[nacl-binutils]="$NACL_BINUTILS_URL"
	git_deps[lind_glibc]="$LIND_GLIBC_URL"
	# fallback
	for dir in "${!git_deps[@]}"; do
		[[ ! -e "$dir" ]] && git clone -b lind_fork "${git_deps[$dir]}" "$dir"
		rm -rf "${LIND_SRC:?}/$dir"
		ln -Tsfv "$LIND_BASE/$dir" "$LIND_SRC/$dir"
	done

	# install gclient
	if ! command -v gclient >/dev/null 2>&1; then
		# find pip executable
		if command -v pip2 >/dev/null 2>&1; then
			pip_bin="pip2"
		elif command -v pip >/dev/null 2>&1; then
			pip_bin="pip"
		else
			print "Need to install pip/pip2 in order to build Lind" >&2
			false
		fi
		# check pip version
		pip_ver="$("$pip_bin" --version | sed 's/.*(python \([0-9\.]\+\)).*/\1/')"
		if [[ "$pip_ver" != 2* ]]; then
			print "Need python2 version of pip in order to build Lind" >&2
			false
		fi
		# install virtualenv modules
		if ! "$pip_bin" install -U --user virtualenv2; then
			print "Need python virtualenv2 in order to build Lind" >&2
			false
		fi
		if ! "$pip_bin" install -U --user virtualenvwrapper; then
			print "Need python virtualenvwrapper in order to build Lind" >&2
			false
		fi

		# start up virtualenv
		PATH="$HOME/.local/bin:$PATH"
		VIRTUALENVWRAPPER_PYTHON=/usr/bin/python2
		VIRTUALENVWRAPPER_VIRTUALENV="$(command -v virtualenv2)"
		WORKON_HOME="${WORKON_HOME:-$LIND_BASE/virtualenvs}"
		export PATH VIRTUALENVWRAPPER_PYTHON VIRTUALENVWRAPPER_VIRTUALENV WORKON_HOME
		mkdir -pv "$WORKON_HOME"
		rm -rf "${WORKON_HOME:?}/lind"
		deactivate >/dev/null 2>&1 || true
		.  "$LIND_BASE/virtualenvwrapper.sh"
		mkvirtualenv lind
		workon lind

		# install pip dependencies
		if ! "$pip_bin" install -U SCons gclient virtualenv2 virtualenvwrapper; then
			print "Need to \`pip2 install gclient\` in order to build Lind" >&2
			false
		fi
	fi

	# clone nacl
	if [[ ! -e "$NACL_BASE" ]]; then
		mkdir -p "$NACL_SRC"
		cd "$LIND_BASE"
		gclient config --name=native_client "$NACL_GCLIENT_URL" --git-deps
		gclient sync
		ln -Tsfv "$LIND_BASE/native_client" "$NACL_BASE"
		cd "$NACL_TOOLCHAIN_BASE"
		rm -rf SRC
		make sync-pinned
		cd SRC
		rm -rf glibc gcc binutils
		ln -Tsfv "$LIND_GLIBC_SRC" glibc
		ln -Tsfv "$NACL_GCC_SRC" gcc
		ln -Tsfv "$NACL_BINUTILS_SRC" binutils
	fi

	# clone nacl external ports
	if [[ ! -e "$NACL_PORTS_DIR/src" ]]; then
		mkdir -p "$NACL_PORTS_DIR"
		cd "$NACL_PORTS_DIR"
		gclient config --name=src "$NACL_PORTS_URL" --git-deps
		gclient sync
	fi

	cd "$LIND_BASE"
	rm -rfv _gclient_*

	cur_func="${FUNCNAME[1]}"
}

# wipe the entire modular build toolchain build tree, then rebuild it
# warning: this can take a while!
#
function clean_toolchain() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	cd "$NACL_TOOLCHAIN_BASE" && rm -rf out BUILD

	cur_func="${FUNCNAME[1]}"
}

# compile liblind and the component programs.
#
function build_liblind() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	print "Building liblind... "
	cd "$MISC_DIR/liblind"
	make clean
	make all
	print "Done."

	cur_func="${FUNCNAME[1]}"
}

# copy the toolchain files into the repy subdir.
#
function install_to_path() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	print "Injecting Libs into Repy install"

	print "** Sending NaCl files to $REPY_PATH **"

	# print "deleting all directories in the $repy_path (except repy folder)"
	# rm -rf "${repy_path_bin:?}"
	# rm -rf "${repy_path_lib:?}"
	# rm -rf "${repy_path_sdk:?}"

	mkdir -p "$REPY_PATH_BIN"
	mkdir -p "$REPY_PATH_LIB/glibc"
	mkdir -p "$REPY_PATH_SDK/toolchain/${OS_SUBDIR}_x86_glibc"
	mkdir -p "$REPY_PATH_SDK/tools"

	# ${rsync} ${nacl_toolchain_base}/out/nacl-sdk/* ${repy_path_sdk}/toolchain/${os_subdir}_x86_glibc
	"${RSYNC[@]}" "$NACL_TOOLCHAIN_BASE/out/nacl-sdk/" "$REPY_PATH_SDK/toolchain/${OS_SUBDIR}_x86_glibc"

	# ${rsync} ${nacl_base}/scons-out/${mode}-x86-64/staging/* ${repy_path_bin}
	"${RSYNC[@]}" "$NACL_BASE/scons-out/${MODE}-x86-64/staging/" "$REPY_PATH_BIN"

	#install scripts
	rm -fv "$REPY_PATH_BIN/lind" "$REPY_PATH_BIN/lindfs"
	cp -fv "$MISC_DIR/lind.sh" "$REPY_PATH_BIN/lind"
	cp -fv "$LIND_BASE/lindfs" "$REPY_PATH_BIN/lindfs"
	chmod +x "$REPY_PATH_BIN/lind" "$REPY_PATH_BIN/lindfs"

	# ${rsync} ${nacl_toolchain_base}/out/nacl-sdk/x86_64-nacl/lib/*  ${repy_path_lib}/glibc
	"${RSYNC[@]}" "$NACL_TOOLCHAIN_BASE/out/nacl-sdk/x86_64-nacl/lib/"  "$REPY_PATH_LIB/glibc"

	cur_func="${FUNCNAME[1]}"
}

# run the repy unit tests.
#
function test_repy() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	# some of our unit tests fail
	set +o errexit

	cd "$REPY_PATH/repy"

	for file in ut_lind_*; do
		print "$file"
		trap '' TERM
		python2 "$file"
		# trap 'python2 "$file"' int term exit
		trap - TERM
	done

	# run the struct test
	file="ut_seattlelibtests_teststruct.py"
	print "$file"
	python "$file"

	cur_func="${FUNCNAME[1]}"
}

# run the applications test stuites.
#
function test_apps() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	set +o errexit

	cd "$MISC_DIR/tests" && ./test.sh

	cur_func="${FUNCNAME[1]}"
}

# check the $repy_path location to make sure it is safe to be installing stuff there.
#
function check_install_dir() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	[[ ! -d "$REPY_PATH" && -e "$REPY_PATH" ]] && false
	# and if it does not exit, make it.
	mkdir -p "$REPY_PATH"

	cur_func="${FUNCNAME[1]}"
}

# install repy into $repy_path with the prepare_tests script.
#
function build_repy() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	set -o errexit

	mkdir -p "$REPY_PATH_REPY"
	print "Building Repy in $REPY_SRC to $REPY_PATH"
	cd "$NACL_REPY"
	cp -v seattlelib/xmlrpc* "$REPY_PATH_REPY/"
	python2 preparetest.py -t -f "$REPY_PATH_REPY"
	print "Done building Repy in \"$REPY_PATH_REPY\""
	cd seattlelib
	set -o errexit
	for file in *.mix; do
		"$MISC_DIR/check_includes.sh" "$file"
	done
	set +o errexit
	ctags  --language-force=python ./*.mix ./*.repy || true

	cur_func="${FUNCNAME[1]}"
}

# update, build and test everything. if there is a problem, freak out.
#
function nightly_build() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	set -o errexit

	# clean
	# clean_install
	# clean_nacl
	# clean_toolchain
	# check_install_dir
	# update
	~/lind/misc/global_update.sh

	# build
	# build_toolchain
	# build_rpc
	# build_glibc
	# build_nacl
	# build_repy
	# build_sdk
	# install_to_path

	# test repy
	test_repy

	# test glibc
	test_glibc

	# test applications
	test_apps

	cur_func="${FUNCNAME[1]}"
}

# clean repy install
#
function clean_install() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	rm -rf "$REPY_PATH"
	mkdir -p "$REPY_PATH"

	cur_func="${FUNCNAME[1]}"
}

# run the nacl build.
#
function build_nacl() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	print "Building NaCl"

	# the pnacl script doesn't respect PYTHON or PNACLPYTHON
	cd "$NACL_BASE/toolchain/pnacl_linux_x86/newlib/bin"
	"${PYGREPL[@]}" 2>/dev/null \
		| "${PYGREPV[@]}" \
		| while read -r file; do
			# preserve executability
			"${PYSED[@]}" <"$file" >"$file.new"
			cat <"$file.new" >"$file"
			rm -f "$file.new"
		done

	# build nacl with glibc tests
	cd "$NACL_BASE"
	PATH="$LIND_BASE:$PATH" \
		python2 ./scons.py --verbose --mode="$MODE,nacl" \
		nacl_pic=1 werror=0 \
		platform=x86-64 --nacl_glibc -j4
	rc="$?"
	if ((rc)); then
		print "" "NaCl Build Failed: exit status [$rc]" $'\a' >&2
		false
	fi

	print "Done building NaCl $rc"

	cur_func="${FUNCNAME[1]}"
}

# run clean on nacl build.
#
function clean_nacl() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	cd "$NACL_BASE"
	./scons --mode="$MODE,nacl" platform=x86-64 --nacl_glibc -c
	print "Done Cleaning NaCl"

	cur_func="${FUNCNAME[1]}"
}

# build glibc from source
#
function build_glibc() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	# the build is long and borning, so execute this first if it exists
	print ""
	if command -v fortune >/dev/null 2>&1; then
		fortune
	else
		print "Fortune Not Found. Skipping." >&2
	fi
	print "" "Copy component.h header to glibc: "
	cd "$MISC_DIR/liblind"
	mkdir -p "$LIND_GLIBC_SRC/sysdeps/nacl/sysdeps/nacl/"
	cp -fvp component.h "$LIND_GLIBC_SRC/sysdeps/nacl/"

	print "Building glibc"

	# turns out this works better if you do it from the nacl base dir
	cd "$NACL_TOOLCHAIN_BASE"
	rm -fr BUILD out
	make clean

	# ??? not quite sure why these
	# weird constructs are needed
	#
	# -jp
	PATH="$LIND_BASE:$PATH" make build-with-glibc -j4 \
		|| PATH="$LIND_BASE:$PATH" make build-with-glibc -j4 \
		|| false

	print "Done building toolchain"

	cur_func="${FUNCNAME[1]}"
}

# perform an incremental glibc compile
#
function update_glibc() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	cd "$NACL_TOOLCHAIN_BASE" \
		 && PATH="$LIND_BASE:$PATH" make updateglibc

	cur_func="${FUNCNAME[1]}"
}

# perform a clean glibc compile
#
function update_glibc2() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	cd "$NACL_TOOLCHAIN_BASE"
	rm -rf BUILD/stamp-glibc64
	PATH="$LIND_BASE:$PATH" make BUILD/stamp-glibc64

	cur_func="${FUNCNAME[1]}"
}

# run the glibc tester
#
function glibc_tester() {
	trap -- 'cur_line="$LINENO" args="$*" abort' ERR
	cur_func="${FUNCNAME[0]}"

	set -o errexit

	cd "$MISC_DIR/glibc_test"
	make clean
	PATH="$LIND_BASE:$PATH" make all
	cd ..
	rm -rfv lind.metadata linddata.*
	lind "$MISC_DIR/glibc_test/glibc_tester.nexe"

	cur_func="${FUNCNAME[1]}"
}

# prompt for target if none given on command line
PS3=$'\n'"Build which target? "
list=(all repy nacl buildglibc updateglibc updateglibc2)
list+=(download cleansources cleantoolchain cleannacl install)
list+=(liblind sdk rpc)
list+=(test_repy test_glibc test_apps test_all nightly)
if ((!$#)); then
	select choice in "${list[@]}"; do
		set -- "$choice"
		break
	done
fi

# all scripts assume we start here
start_time=$(date +%s)

# show command that will be executed
print "" "Command line arguments: $0 $*" ""

for word in "$@"; do
	case "$word" in
	repy)
		build_repy;;
	nacl)
		build_nacl;;
	buildglibc)
		build_glibc;;
	updateglibc)
		update_glibc;;
	updateglibc2)
		update_glibc2;;
	all)
		download_src
		build_nacl
		build_repy
		build_glibc
		install_to_path
		build_liblind;;
	install)
		install_to_path;;
	download)
		download_src;;
	cleansources)
		clean_src;;
	cleantoolchain)
		clean_toolchain;;
	cleannacl)
		clean_nacl;;
	liblind)
		build_liblind;;
	test_repy)
		test_repy;;
	test_glibc)
		print "Testing GLibC"
		glibc_tester;;
	test_apps)
		print "Testing Applications"
		test_apps;;
	test_all)
		print "Testing All"
		test_repy
		glibc_tester
		test_apps;;
	nightly)
		print "Nightly Build"
		nightly_build;;
	*)
		print "Error: Did not find a build target for that number. Exiting..." >&2
		abort;;
	esac
done
