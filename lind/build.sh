#!/bin/bash
#
# Try to ease the burden of building lind (repy, nacl, and toolchain)
#
# Created by Chris Matthews <cmatthew@cs.uvic.ca>
# Updated by Joey Pabalinas <joeypabalinas@gmail.com>

# Version string
#
readonly version=0.2.1-alpha
#
# PLEASE UPDATE WITH STANDARD SEMANTIC VERSIONING WHEN MAKING CHANGES. [1]
#
#  ___ MAJOR.MINOR.PATCH-PRE_RELEASE ____
#
# Please tag *every* new major, minor, pre-release, and release.
#
# Use alpha -> beta -> rc1 -> rc2 ... for pre-release versions and no
# suffix for releases.
#
# Major version zero (0.y.z) is for initial development. Anything may
# change at any time. The public API should not be considered stable.
# version 1.0.0 defines the public API.
#
# Patch version Z (x.y.Z | x > 0) *MUST* be incremented if only backwards
# compatible bug fixes are introduced. A bug fix is defined as an internal
# change that fixes incorrect behavior.
#
# Minor version Y (x.Y.z | x > 0) *MUST* be incremented if new, backwards
# compatible functionality is introduced to the public API. It *MUST* be
# incremented if any public API functionality is marked as deprecated.
# It _MAY_ be incremented if substantial new functionality or improvements
# are introduced within the private code. It _MAY_ include patch level
# changes. Patch version *MUST* be reset to 0 when minor version is
# incremented.
#
# Major version X (X.y.z | X > 0) *MUST* be incremented if any backwards
# incompatible changes are introduced to the public API. It _MAY_ include
# minor and patch level changes. Patch and minor version *MUST* be reset
# to 0 when major version is incremented.
#
# References:
# [1] https://semver.org/
#
# --
# Joey Pabalinas <joeypabalinas@gmail.com>

# program usage string
usage+=$'\n'"Lind $version build script"$'\n'
usage+=$'\n'
usage+=$'Usage:\n'
usage+=$'\t'"$0 [options] [commands]"$'\n'
usage+=$'\n'
usage+=$'Options:\n'
usage+=$'\t-h, -H\tdisplay this help\n'
usage+=$'\t-v, -V\tdisplay version\n'
usage+=$'\t-e, -E\tuse the default evironment\n'

# DEBUGGING SETTINGS:
#
# Uncomment this to print each command as they are executed
# set -o xtrace
# Uncomment this for debugging. Will stop B on any failed commands
# set -o errexit
# Uncomment this to dump time profiling information out to a file to see where the script is slow
# PS4='+ $(date "+%s.%N")\011 '
# exec 2>"bashstart.$$.log"
# set -x

# Call this instead of print, then we can do things like log and print
# to notifier
#
function print() {
	printf '%s\n' "$@"
	# notify-send \
	#         --icon=/usr/share/icons/gnome/256x256/apps/utilities-terminal.png \
	#         "Build Script" \
	#         "$1" \
	#         >/dev/null 2>&1
}

# Check for flags
for word; do
	case "$word" in
	-*[eE]*)
		# setup and print out the default environment
		PIC=1 GIT_SSH_COMMAND='ssh -o Tunnel=no'
		LD_LIBRARY_PATH=/glibc/ PATH="$LIND_SRC/depot_tools:$PATH"
		LIND_BASE="/usr/lind_project" LIND_SRC="$LIND_BASE/lind"
		REPY_PATH="$LIND_SRC/nacl"
		NACL_SDK_ROOT="$LIND_SRC/nacl/sdk"
		LIND_MONITOR="$LIND_SRC/reference_monitor"
		PNACLPYTHON="$(type -P python2)"
		export GIT_SSH_COMMAND PIC
		export LD_LIBRARY_PATH PATH
		export LIND_BASE LIND_SRC REPY_PATH
		export NACL_SDK_ROOT
		export LIND_MONITOR
		export PNACLPYTHON
		echo
		echo '======================================================'
		echo 'USING DEFAULT NACL ENVIRONMENT:'
		echo '======================================================'
		echo
		cat <<-EOF
		# quieter git submodule updates
		PIC=1 GIT_SSH_COMMAND='ssh -o Tunnel=no'

		# nacl toolchain environment
		LD_LIBRARY_PATH=/glibc/ PATH="$LIND_SRC/depot_tools:\$PATH"

		# base repo paths
		LIND_BASE="/usr/lind_project" LIND_SRC="$LIND_BASE/lind"
		REPY_PATH="$LIND_SRC/nacl"

		# toolchain/sdk roots
		NACL_SDK_ROOT="$LIND_SRC/nacl/sdk"
		LIND_MONITOR="$LIND_SRC/reference_monitor"
		PNACLPYTHON="$(type -P python2)"
		EOF
		echo
		echo '======================================================'
		echo
		# remove -e flag after setting up environment
		mapfile -td ' ' args < <(printf '%s' "${@//-*[eE]*/}")
		set -- "${args[@]}"
		unset args
		;;

	-*[vV]*)
		# exit after printing version
		print "Lind $version build script"
		exit
		;;

	-*[hH]*)
		# exit after printing usage
		print "$usage"
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
		print "" "Unknown option letter: '${word//-/}'" "$usage"
		exit -3
		;;
	esac
done

trap '{ print "All done."; cd "$LIND_SRC" 2>/dev/null; }' EXIT

# Show command that will be executed
print "Command line arguments: $0 $*"

if [[ -z "$REPY_PATH" ]]; then
	print "Need to set REPY_PATH"
	exit -2
fi

if [[ -z "$LIND_SRC" ]]; then
	print "Need to set LIND_SRC"
	exit -2
fi

readonly OS_NAME=$(uname -s)
if [[ "$OS_NAME" == "Darwin" ]]; then
	readonly OS_SUBDIR="mac"
elif [[ "$OS_NAME" == "Linux" ]]; then
	readonly OS_SUBDIR="linux"
else
	readonly OS_SUBDIR="win"
fi
if [[ -n "$JOBS" ]]; then
	readonly JOBS="$JOBS"
elif type -P nproc &>/dev/null; then
	readonly JOBS="$(nproc)"
else
	readonly JOBS='4'
fi
if ((PIC)); then
	# default to position-independant
	# code if $PIC is unset or non-zero
	readonly NACL_PIC=1
else
	readonly NACL_PIC=0
fi
readonly MODE="dbg-$OS_SUBDIR"
readonly LIND_SRC="$LIND_SRC"

readonly LIND_GLIBC_SRC="$LIND_SRC/lind_glibc"
readonly LIND_BINUTILS_SRC="$LIND_SRC/nacl-binutils"
readonly GTEST_DIR="$LIND_SRC/googletest"
readonly MISC_DIR="$LIND_SRC/misc"
readonly NACL_BASE="$LIND_BASE/nacl"
readonly NACL_SRC="$LIND_SRC/native_client"
readonly NACL_GCC_DIR="$LIND_SRC/nacl-gcc"
readonly NACL_REPY="$LIND_SRC/nacl_repy"
readonly NACL_PORTS_DIR="$LIND_SRC/naclports"
readonly NACL_LSS_DIR="$LIND_SRC/linux-syscall-support"
readonly BREAKPAD_DIR="$LIND_BASE/google-breakpad"

readonly NACL_THIRD_PARTY="$NACL_SRC/src/third_party"
readonly NACL_TOOLCHAIN_SRC="$NACL_SRC/tools"
readonly REPY_PATH="$REPY_PATH"
readonly REPY_PATH_BIN="$REPY_PATH/bin"
readonly REPY_PATH_REPY="$REPY_PATH/repy"
readonly REPY_PATH_LIB="$REPY_PATH/lib"
readonly REPY_PATH_SDK="$REPY_PATH/sdk"

readonly LIND_GLIBC_URL='https://github.com/Lind-Project/Lind-GlibC.git'
readonly LIND_MISC_URL='https://github.com/Lind-Project/Lind-misc.git'
readonly LIND_THIRD_PARTY_URL='https://github.com/Lind-Project/third_party.git'
readonly NACL_LSS_URL='https://github.com/Lind-Project/linux-syscall-support.git'
readonly NACL_REPY_URL='https://github.com/Lind-Project/nacl_repy.git'
readonly NACL_RUNTIME_URL='https://github.com/Lind-Project/native_client.git'

readonly -a PYGREPL=(grep '-lIPR' '(^|'"'"'|"|[[:space:]]|/)(python)([[:space:]]|\.exe|$)' './')
readonly -a PYGREPV=(grep '-vP' -- '\.(git|.?html|cc?|h|exp|so\.old|so)\b')
readonly -a PYSED=(sed '-r' 's_(^|'"'"'|"|[[:space:]]|/)(python)([[:space:]]|\.exe|$)_\1\22\3_g')
readonly -a PNACLGREPL=(grep '-IFRlw' -- "\${PNACLPYTHON}" './')
readonly -a PNACLGREPV=(grep '-vP' -- '\.(git|.?html|cc?|h|exp|so\.old|so)\b')
readonly -a PNACLSED=(sed "s_\${PNACLPYTHON}_python2_g")
readonly -a RSYNC=(rsync '-acrvP' '--info=progress2')

readonly -a SUBMODULES=(lind_glibc nacl-binutils nacl-gcc pnacl-clang
			nacl_repy native_client misc third_party
			googletest google-breakpad linux-syscall-support)

if [[ "$NACL_SDK_ROOT" != "$REPY_PATH_SDK" ]]; then
	print "You need to set \"$NACL_SDK_ROOT\" to \"$REPY_PATH_SDK\""
	exit -2
fi

# Download source files
#
function download_src() {
	mkdir -p "$LIND_SRC"
	cd "$LIND_BASE" || exit 1
	# rm -rf "${LIND_BASE:?}/nacl-gcc"
	# rm -rf "${LIND_BASE:?}/native_client"
	git submodule sync --recursive
	git submodule update --remote
	for dir in "${SUBMODULES[@]}"; do
		rm -f "$LIND_SRC/$dir"
		ln -rs "$dir" "$LIND_SRC/"
	done

	# sync and patch repos
	cd "$LIND_SRC" || exit 1
	ln -Trsfv "${LIND_BASE:?}/nacl-gcc" nacl-gcc
	gclient clean
	gclient config --name=nacl-gcc \
		https://chromium.googlesource.com/native_client/nacl-gcc.git \
		--git-deps && \
		gclient sync
	cd nacl-gcc || exit 1
	# for patch in "${LIND_BASE:?}"/patches/nacl-gcc-*.patch; do
	#         patch -p1 <"$patch" 2>/dev/null || true
	# done
	cd "$LIND_SRC" || exit 1
	ln -Trsfv "${LIND_BASE:?}/native_client" native_client
	gclient config --name=native_client \
		https://github.com/Lind-Project/native_client.git@lind \
		--git-deps && \
		gclient sync
	cd native_client || exit 1
	# for patch in "${LIND_BASE:?}"/patches/native_client-*.patch; do
	#         patch -p1 <"$patch" 2>/dev/null || true
	# done
	cd "$LIND_BASE" || exit 1
	rm -rf "$NACL_BASE"
	mkdir -p "$NACL_BASE"
	cd "$NACL_BASE" || exit 1
	ln -Trsfv "${LIND_BASE:?}/native_client" native_client

	# use custom repos as bases
	cd "$LIND_SRC" || exit 1
	mkdir -p "$NACL_SRC/src/third_party"
	rm -f "$NACL_SRC/src/third_party/lss"
	rm -f "$NACL_SRC/src/trusted/service_runtime/linux/third_party"
	ln -rs "$NACL_LSS_DIR" "$NACL_SRC/src/third_party/lss"
	ln -rs "$NACL_SRC/src/third_party" "$NACL_SRC/src/trusted/service_runtime/linux/"
	mkdir -p "$NACL_PORTS_DIR"
	cd "$NACL_BASE" || exit 1
	gclient config --name=naclports \
		https://chromium.googlesource.com/webports.git \
		--git-deps && \
		gclient sync

	cd "$NACL_TOOLCHAIN_SRC" || exit 1
	rm -rf SRC
	make sync-pinned
	cd .. || exit 1
}


# Setup base toolchain structure
#
function setup_toolchain() {
	local -a dirs
	toolchain_dirs=(binutils gcc glibc)

	# use custom repos as bases
	cd "$NACL_TOOLCHAIN_SRC/SRC" || exit 1
	for dir in "${toolchain_dirs[@]}"; do
		rm -f "$dir" || mv -v "$dir" "${dir}_orig"
	done 2>/dev/null
	ln -s "$LIND_BINUTILS_SRC" binutils
	ln -s "$NACL_GCC_DIR" gcc
	ln -s "$LIND_GLIBC_SRC" glibc

	# convert files from python to python2
	cd "$NACL_SRC" || exit 1
	"${PYGREPL[@]}" 2>/dev/null | \
		"${PYGREPV[@]}" | \
		while read -r file; do
			# preserve executability
			"${PYSED[@]}" <"$file" >"$file.new"
			cat <"$file.new" >"$file"
			rm -v "$file.new"
		done

	cd "$NACL_THIRD_PARTY" || exit 1
	mv gtest gtest_orig
	ln -rs "$GTEST_DIR/googletest" gtest
	cd "$GTEST_DIR" || exit 1
	cmake .
	make

	rm -f "$REPY_PATH/breakpad"
	ln -rs "$BREAKPAD_DIR" "$REPY_PATH/breakpad"
	cd "$REPY_PATH/breakpad" || exit 1
	rm -rf src
	ln -rs "$BREAKPAD_DIR" src


	# sed to python2
	cd "$NACL_SRC" || exit 1
	"${PNACLGREPL[@]}" 2>/dev/null | \
		"${PNACLGREPV[@]}" | \
		while read -r file; do
			# preserve executability
			"${PNACLSEDSED[@]}" <"$file" >"$file.new"
			cat <"$file.new" >"$file"
			rm "$file.new"
		done

	cd "$LIND_SRC" || exit 1
}


# Wipe the entire modular build toolchain build tree, then rebuild it
# Warning: this can take a while!
#
function clean_toolchain() {
	cd "$NACL_TOOLCHAIN_SRC" || exit 1
	rm -rf out BUILD
}


# Compile liblind and the compoent programs.
#
function build_liblind() {
	print "Building liblind... "
	cd "$MISC_DIR/liblind" || exit 1
	make clean all
	print "done."
}


# Copy the toolchain files into the repy subdir.
#
function install_to_path() {
	# nothing should fail here.
	set -o errexit

	print "Injecting Libs into RePy install"
	print "** Sending NaCl stuff to \"${REPY_PATH}\""

	# print "Deleting all directories in the "${REPY_PATH}" (except repy folder)"
	# rm -rf "${REPY_PATH_BIN:?}"
	# rm -rf "${REPY_PATH_LIB:?}"
	# rm -rf "${REPY_PATH_SDK:?}"

	mkdir -p "$REPY_PATH_BIN"
	mkdir -p "$REPY_PATH_LIB/glibc"
	mkdir -p "$REPY_PATH/toolchain/${OS_SUBDIR}_x86_glibc"
	mkdir -p "$REPY_PATH_SDK/tools"
	mkdir -p "$NACL_TOOLCHAIN_SRC/toolchain/${OS_SUBDIR}_x86_glibc"

	# "${RSYNC[@]}" \
	#         "${NACL_TOOLCHAIN_SRC:?}/out/nacl-sdk/" \
	#         "$NACL_SRC/toolchain/${OS_SUBDIR}_x86_glibc"
	# "${RSYNC[@]}" \
	#         "${NACL_TOOLCHAIN_SRC:?}/out/nacl-sdk/x86_64-nacl/lib/"  \
	#         "$NACL_SRC/toolchain/${OS_SUBDIR}_x86/glibc/"
	# we need some files from the original sdk to help compile some applications (e.g. zlib)
	# "${RSYNC[@]}" "${MISC_DIR:?}/${OS_SUBDIR:?}_pepper_28_tools/" "${REPY_PATH_SDK:?}/tools/"


	"${RSYNC[@]}" \
		"${NACL_TOOLCHAIN_SRC:?}/out/nacl-sdk"/* \
		"${REPY_PATH_SDK:?}/toolchain/${OS_SUBDIR:?}_x86_glibc"

	#install script
	cp -f "${MISC_DIR:?}/lind.sh" "${REPY_PATH_BIN:?}/lind"
	ln -Trsfv "${REPY_PATH_SDK:?}/toolchain" "${NACL_SRC:?}/toolchain"
	chmod +x "$REPY_PATH_BIN/lind"

	"${RSYNC[@]}" \
		"${NACL_TOOLCHAIN_SRC:?}/out/nacl-sdk/x86_64-nacl/lib"/*  \
		"${REPY_PATH_LIB:?}/glibc"

	"${RSYNC[@]}" \
		"${NACL_SRC:?}/scons-out/${MODE:?}-x86-64/staging"/* \
		"${REPY_PATH_BIN:?}/"
}


# Run the RePy unit tests.
#
function test_repy() {
	cd "$REPY_PATH/repy/" || exit 1
	# some of our unit tests fail
	set +o errexit
	for file in ut_lind_*; do
		print "$file"
		# trap 'python2 "$REPY_PATH/repy/repy.py" --safebinary \
		#         "$REPY_PATH/repy/restrictions.lind" "$REPY_PATH/repy/lind_server.py" "$@"' INT TERM EXIT
		# trap ';' TERM
		python2 "$file"
		# trap 'python2 "$file"' INT TERM EXIT
	done

	# run the struct test
	file=ut_seattlelibtests_teststruct.py
	print "$file"
	python2 "$file"
}


# Run the applications test stuites.
#
function test_apps() {
	set +o errexit
	cd "$MISC_DIR/tests" || exit 1
	./test.sh
}


# Check the REPY_PATH location to make sure it is safe to be installing stuff there.
#
function check_install_dir() {

	# and if it does not exit, make it.
	if [[ ! -d "$REPY_PATH" ]]; then
		mkdir -p "${REPY_PATH}"
	fi

}


# Install repy into "$REPY_PATH" with the prepare_tests script.
#
function build_repy() {
	# set -o errexit
	mkdir -p "$REPY_PATH_REPY"

	print "Building Repy in \"$NACL_REPY\" to \"$REPY_PATH_REPY\""

	cd "$NACL_REPY" || exit 1
	cp seattlelib/xmlrpc/* "$REPY_PATH_REPY/"
	python2 preparetest.py -t -f "$REPY_PATH_REPY"
	print "Done building Repy in \"$REPY_PATH_REPY\""

	cd seattlelib || exit 1
	# set -o errexit
	for file in *.mix; do
		"$MISC_DIR/check_includes.sh" "$file"
	done

	set +o errexit
	# etags  --language-force=python *.mix *.repy
}


# Update, build and test everything. If there is a problem, freak out.
#
function nightly_build() {
	set -o errexit
	# Clean
	# clean_install
	# clean_nacl
	# clean_toolchain
	# check_install_dir
	# Update
	"$LIND_SRC/Lind-misc/global_update.sh"
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

}


# Clean install path
#
function clean_install() {
	rm -rf "${REPY_PATH:?}"
	mkdir -p "${REPY_PATH}"
}


# Run the NaCl build.
#
function build_nacl() {
	local rc mode_dir
	local -a dirs

	dirs+=(src/trusted/validator/)
	dirs+=(src/trusted/validator/x86/)
	dirs+=(src/trusted/service_runtime/)
	dirs+=(src/trusted/validator/x86/decoder/)
	dirs+=(tests/unittests/trusted/bits/)
	dirs+=(tests/unittests/trusted/platform_qualify/)
	dirs+=(src/shared/gio/)

	print "Building NaCl"

	# set base out directory
	cd "$NACL_SRC" || exit 1
	if ((NACL_PIC)); then
		mode_dir="scons-out/nacl-x86-64-pic-glibc"
	else
		mode_dir="scons-out/nacl-x86-64-glibc"
	fi

	# symlink gtest dirs
	for dir in "${dirs[@]}"; do
		mkdir -p "$dir"
		rm -f "$dir/gtest"
		ln -rs "$GTEST_DIR/googletest/include/gtest" "$dir"
	done

	# symlink library and include directories
	if [[ -d scons-out/nacl_irt-x86-64 ]]; then
		mv scons-out/nacl_irt-x86-64{,_orig}
	fi
	rm -f scons-out/nacl_irt-x86-64
	ln -rs $mode_dir scons-out/nacl_irt-x86-64
	mkdir -p \
		src/untrusted/minidump_generator \
		scons-out/nacl_irt-x86-64/lib \
		scons-out/nacl_irt-x86-64/obj/src/untrusted/nacl \
		scons-out/nacl_irt-x86-64/obj/src/shared/srpc \
		scons-out/nacl_irt-x86-64/obj/src/untrusted/nacl \
		scons-out/nacl_irt-x86-64/obj/src/shared/platform \
		scons-out/nacl_irt-x86-64/lib \
		"$mode_dir/obj/src"
	rm -f \
		src/untrusted/minidump_generator/breakpad \
		"$mode_dir/obj/src/third_party"
	ln -rs "$REPY_PATH/breakpad" src/untrusted/minidump_generator/
	ln -rs "$NACL_THIRD_PARTY" "$mode_dir/obj/src/"

	# build NaCl with glibc tests
	./scons --mode="nacl" --verbose -j"$JOBS" \
		platform=x86-64 nacl_pic="$NACL_PIC" \
		build_bin
	./scons --mode="nacl" --verbose -j"$JOBS" \
		platform=x86-64 nacl_pic="$NACL_PIC" \
		bindir=scons-out/nacl_irt-x86-64/staging \
		install_bin
	./scons --mode="$MODE,nacl" --verbose -j"$JOBS" --nacl_glibc \
		platform=x86-64 nacl_pic="$NACL_PIC"

	# and check
	rc="$?"
	if ((rc != 0)); then
		print "NaCl Build Failed [Exit Code: $rc]" $'\a'
		exit "$rc"
	fi

	print "Done building NaCl"
}


# Run clean on nacl build.
#
function clean_nacl() {
	cd "$NACL_SRC"
	./scons --mode="$MODE,nacl" platform=x86-64 --nacl_glibc -c
	print "Done Cleaning NaCl"
}


# Build glibc from source
#
function build_glibc() {
	# the build is long and boring, so execute this first if it exists
	if type -P fortune &>/dev/null; then
		fortune
	else
		print "Fortune Not Found. Skipping."
	fi

	print "Copy component.h header to glibc: "
	cd "$MISC_DIR/liblind" || exit 1
	rm -f "$NACL_SRC/third_party/getdeps.sh"
	rm -f "$NACL_SRC/third_party"
	cp -fp component.h "$LIND_GLIBC_SRC/sysdeps/nacl/"
	ln -rs "$NACL_THIRD_PARTY" "$NACL_SRC/"
	ln -rs "$LIND_SRC/getdeps.sh" "$NACL_THIRD_PARTY/"
	cd "$NACL_THIRD_PARTY" || exit 1
	./getdeps.sh
	print "done."

	print "Building glibc"

	# if extra files (like editor temp files) are in the subdir glibc tries to compile them too.
	# move them here so they dont cause a problem
	cd "$LIND_GLIBC_SRC/sysdeps/nacl/" || exit 1
	shopt -s nullglob
	for f in .\#*; do
		print "moving editor backupfile \"$f\" so it does not get caught in build."
		mv -f "$f" .
	done

	# turns out this works better if you do it from the nacl base dir
	cd "$NACL_TOOLCHAIN_SRC" || exit 1
	rm -rf BUILD out
	make -j"$JOBS" clean build-with-glibc || exit -1
	print "Done building toolchain"
}


# Update glibc toolchain
#
function update_glibc() {
	cd "$NACL_TOOLCHAIN_SRC" || exit 1
	make updateglibc
}


# Update glibc 64bit toolchain
#
function update_glibc2() {
	cd "$NACL_TOOLCHAIN_SRC" || exit 1
	rm -f BUILD/stamp-glibc64
	make BUILD/stamp-glibc64
}


# Run the glibc tester
#
function glibc_tester() {
	set -o errexit

	cd "$MISC_DIR/glibc_test/" || exit 1
	make clean all

	cd .. || exit 1
	rm -rf lind.metadata linddata.*
	lind "$MISC_DIR/glibc_test/glibc_tester.nexe"
}

PS3='build what: '

list+=(all download setup_toolchain)
list+=(build_glibc build_repy)
list+=(build_liblind install_toolchain)
list+=(build_nacl nightly)
list+=(clean_toolchain clean_nacl)
list+=(update_glibc update_glibc64)
list+=(test_repy test_glibc test_apps test)
# unimplemented
# list+=(sdk rpc)

if ((!$#)); then
	select choice in "${list[@]}"; do
		set -- "$choice"
		break
	done
fi

start_time=$(date +%s)

# All scripts assume we start here
while (($#)); do
	if [[ "$1" == build_repy ]]; then
		build_repy
	elif [[ "$1" == build_nacl ]]; then
		build_nacl
	elif [[ "$1" == build_glibc ]]; then
		build_glibc
	elif [[ "$1" == update_glibc ]]; then
		update_glibc
	elif [[ "$1" == update_glibc64 ]]; then
		update_glibc2
	elif [[ "$1" == download ]]; then
		download_src
	elif [[ "$1" == setup_toolchain ]]; then
		setup_toolchain
	elif [[ "$1" == all ]]; then
		download_src
		setup_toolchain
		build_glibc
		build_repy
		install_to_path
		build_liblind
		build_nacl
	elif [[ "$1" == clean_toolchain ]]; then
		print "Cleaning Toolchain"
		clean_toolchain
	elif [[ "$1" == install_toolchain ]]; then
		print "Installing libs into install dir"
		install_to_path
	elif [[ "$1" == clean_nacl ]]; then
		print "Cleaning NaCl"
		clean_nacl
	elif [[ "$1" == build_liblind ]]; then
		print "Building LibLind"
		build_liblind
	elif [[ "$1" == test_repy ]]; then
		print "Testing Repy"
		test_repy
	elif [[ "$1" == test_glibc ]]; then
		print "Testing GLibC"
		glibc_tester
	elif [[ "$1" == test_apps ]]; then
		print "Testing Applications"
		test_apps
	elif [[ "$1" == test ]]; then
		print "Testing All"
		test_repy
		glibc_tester
		test_apps
	elif [[ "$1" == nightly ]]; then
		print "Nightly Build"
		nightly_build
	else
		print "Error: Did not find a build target named \"$1\". Exiting..."
		exit 1
	fi
	shift
done

end_time="$(date +%s)"
time_diff="$((end_time - start_time))"

print "It took $time_diff seconds" $'\a'
