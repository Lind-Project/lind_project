#!/bin/bash
#
# Try to ease the burden of building lind (repy, nacl, and toolchain)
#
# Created by Chris Matthews <cmatthew@cs.uvic.ca>
# Updated by Joey Pabalinas <joeypabalinas@gmail.com>

# PLEASE UPDATE WITH STANDARD SEMANTIC VERSIONING WHEN MAKING CHANGES. [1]
#
#  _ MAJOR.MINOR.PATCH-PRE_RELEASE _
#
# Please tag *every* new major, minor, pre-release, and release.
#
# Use alpha ->beta ->rc1 ->rc2 ... for pre-release versions and no
# suffix for releases.
#
# Major version zero (0.y.z) is for initial development. Anything may
# change at any time. The public API should not be considered stable.
# version 1.0.0 defines the public API.
#
# Patch version Z (x.y.Z | x >0) *MUST* be incremented if only backwards
# compatible bug fixes are introduced. A bug fix is defined as an internal
# change that fixes incorrect behavior.
#
# Minor version Y (x.Y.z | x >0) *MUST* be incremented if new, backwards
# compatible functionality is introduced to the public API. It *MUST* be
# incremented if any public API functionality is marked as deprecated.
# It _MAY_ be incremented if substantial new functionality or improvements
# are introduced within the private code. It _MAY_ include patch level
# changes. Patch version *MUST* be reset to 0 when minor version is
# incremented.
#
# Major version X (X.y.z | X >0) *MUST* be incremented if any backwards
# incompatible changes are introduced to the public API. It _MAY_ include
# minor and patch level changes. Patch and minor version *MUST* be reset
# to 0 when major version is incremented.
#
# References:
# [1] https://semver.org/
#
# --
# Joey Pabalinas <joeypabalinas@gmail.com>
#
readonly version=0.1.1-alpha

# program usage string
usage+=$'\n'"Lind $version build script"$'\n'
usage+=$'\n'
usage+=$'Usage:\n'
usage+=$'\t'"$0 [options] [command]"$'\n'
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
		PATH="$LIND_SRC/depot_tools:$PATH"
		LD_LIBRARY_PATH=/glibc/
		LIND_BASE="/usr/lind_project"
		LIND_SRC="$LIND_BASE/lind"
		REPY_PATH="$LIND_SRC/nacl"
		NACL_SDK_ROOT="$LIND_SRC/nacl/sdk"
		LIND_MONITOR="$LIND_SRC/reference_monitor"
		export PATH LD_LIBRARY_PATH
		export LIND_BASE LIND_SRC REPY_PATH
		export NACL_SDK_ROOT LIND_MONITOR
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
		if [[ "$word" == - || "$word" == -- ]]; then
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

trap 'print "All done."' EXIT

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
if type -P nproc &>/dev/null; then
	readonly JOBS="$(nproc)"
else
	readonly JOBS='4'
fi
readonly MODE="dbg-$OS_SUBDIR"
readonly LIND_SRC="$LIND_SRC"
readonly MISC_DIR="$LIND_SRC/lind-misc"
readonly NACL_SRC="$LIND_SRC/nacl"
readonly NACL_BASE="$NACL_SRC/native_client"
readonly NACL_THIRD_PARTY="$LIND_SRC/third_party"
readonly NACL_TOOLCHAIN_BASE="$NACL_BASE/tools"
readonly LIND_GLIBC_SRC="$LIND_SRC/lind_glibc"
readonly NACL_REPY="$LIND_SRC/nacl_repy"
readonly NACL_PORTS_DIR="$LIND_SRC/naclports"
readonly NACL_GCC_DIR="$LIND_SRC/nacl-gcc"

readonly REPY_PATH="$REPY_PATH"
readonly REPY_PATH_BIN="$REPY_PATH/bin"
readonly REPY_PATH_REPY="$REPY_PATH/repy"
readonly REPY_PATH_LIB="$REPY_PATH/lib"
readonly REPY_PATH_SDK="$REPY_PATH/sdk"

readonly LIND_GLIBC_URL='https://github.com/Lind-Project/Lind-GlibC.git'
readonly LIND_MISC_URL='https://github.com/Lind-Project/Lind-misc.git'
readonly NACL_REPY_URL='https://github.com/Lind-Project/nacl_repy.git'
readonly NACL_RUNTIME_URL='https://github.com/Lind-Project/native_client.git'

readonly -a RSYNC=(rsync -avrc --force)
readonly -a PYGREPL=(grep -lPR '(^|'"'"'|"|[[:space:]]|/)(python)([[:space:]]|\.exe|$)' .)
readonly -a PYGREPV=(grep -vP '\.(git|.?html|cc?|h|exp|so\.old|so)\b')
readonly -a PYSED=(sed -r 's_(^|'"'"'|"|[[:space:]]|/)(python)([[:space:]]|\.exe|$)_\1\22\3_g')

if [[ "$NACL_SDK_ROOT" != "$REPY_PATH_SDK" ]]; then
	print "You need to set \"$NACL_SDK_ROOT\" to \"$REPY_PATH_SDK\""
	exit -2
fi

# Download source files
#
function download_src() {
	mkdir -pv "$LIND_SRC"
	cd "$LIND_BASE" || exit 1

	rm -rfv "${LIND_SRC:?}/lind_glibc"
	git clone "$LIND_GLIBC_URL" lind_glibc
	cd lind_glibc || exit 1
	git checkout i686_caging
	cd .. || exit 1

	rm -rfv "${LIND_SRC:?}/nacl_repy"
	git clone "$NACL_REPY_URL" nacl_repy

	rm -rfv "${LIND_SRC:?}/misc"
	git clone "$LIND_MISC_URL" misc

	ln -rs ./lind_glibc "$LIND_SRC/"
	ln -rs ./nacl_repy "$LIND_SRC/"
	ln -rs ./misc "$LIND_SRC/"

	cd "$LIND_SRC" || exit 1
	rm -rfv "${LIND_SRC:?}/nacl"
	mkdir -pv "$NACL_SRC"

	mkdir -pv "$NACL_BASE"
	cd "$NACL_BASE" || exit 1
	gclient config --name=native_client \
		git@github.com:Lind-Project/native_client.git@i686_caging --git-deps && \
		gclient sync

	mkdir -pv "$NACL_GCC_DIR"
	cd "$NACL_GCC_DIR" || exit 1
	gclient config --name=src \
		git@github.com:Lind-Project/nacl-gcc.git@i686_caging --git-deps && \
		gclient sync

	mkdir -pv "$NACL_PORTS_DIR"
	cd "$NACL_PORTS_DIR" || exit 1
	gclient config --name=src \
		https://chromium.googlesource.com/webports.git --git-deps && \
		gclient sync

	# use custom repos as bases
	cd "$NACL_TOOLCHAIN_BASE" || exit 1
	rm -rfv SRC
	make sync-pinned
	cd SRC || exit 1
	mv glibc glibc_orig
	ln -sv "$LIND_GLIBC_SRC" glibc
	mv gcc gcc_orig
	ln -sv "$NACL_GCC_DIR" gcc
	cd .. || exit 1

	# convert files from python to python2
	"${PYGREPL[@]}" 2>/dev/null | \
		"${PYGREPV[@]}" | \
		while read -r file; do
			# preserve executability
			"${PYSED[@]}" <"$file" >"$file.new"
			cat <"$file.new" >"$file"
			rm "$file.new"
		done

	cd "$LIND_SRC" || exit 1
}


# Wipe the entire modular build toolchain build tree, then rebuild it
# Warning: this can take a while!
#
function clean_toolchain() {
	cd "$NACL_TOOLCHAIN_BASE" || exit 1
	rm -rfv out BUILD
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
	# rm -rfv "${REPY_PATH_BIN:?}"
	# rm -rfv "${REPY_PATH_LIB:?}"
	# rm -rfv "${REPY_PATH_SDK:?}"

	mkdir -pv "$REPY_PATH_BIN"
	mkdir -pv "$REPY_PATH_LIB/glibc"
	mkdir -pv "$REPY_PATH_SDK/toolchain/${OS_SUBDIR}_x86_glibc"
	mkdir -pv "$REPY_PATH_SDK/tools"

	"${RSYNC[@]}" "${NACL_TOOLCHAIN_BASE:?}/out/nacl-sdk/" "${REPY_PATH_SDK:?}/toolchain/${OS_SUBDIR:?}_x86_glibc/"
	# we need some files from the original sdk to help compile some applications (e.g. zlib)
	# "${RSYNC[@]}" "${MISC_DIR:?}/${OS_SUBDIR:?}_pepper_28_tools/" "${REPY_PATH_SDK:?}/tools/"

	"${RSYNC[@]}" "${NACL_BASE:?}/scons-out/${MODE:?}-x86-64/staging/" "${REPY_PATH_BIN:?}/"

	#install script
	cp -f "${MISC_DIR:?}/lind.sh" "${REPY_PATH_BIN:?}/lind"
	chmod +x "$REPY_PATH_BIN/lind"

	"${RSYNC[@]}" "${NACL_TOOLCHAIN_BASE:?}/out/nacl-sdk/x86_64-nacl/lib/"  "${REPY_PATH_LIB:?}/glibc/"
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
		mkdir -pv "${REPY_PATH}"
	fi

}


# Install repy into "$REPY_PATH" with the prepare_tests script.
#
function build_repy() {
	# set -o errexit
	mkdir -pv "$REPY_PATH_REPY"

	print "Building Repy in \"$NACL_REPY\" to \"$REPY_PATH\""

	cd "$NACL_REPY" || exit 1
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
	rm -rfv "${REPY_PATH:?}"
	mkdir -pv "${REPY_PATH}"
}


# Run the NaCl build.
#
function build_nacl() {
	print "Building NaCl"
	cd "$NACL_BASE" || exit 1

	# build NaCl with glibc tests
	./scons --verbose --mode="$MODE,nacl" platform=x86-64 --nacl_glibc -j4
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
	cd "${NACL_BASE}"
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
	rm -fv "$NACL_SRC/third_party"
	cp -fvp component.h "$LIND_GLIBC_SRC/sysdeps/nacl/"
	ln -rsv "$NACL_THIRD_PARTY" "$NACL_SRC/"
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
	cd "$NACL_TOOLCHAIN_BASE" || exit 1
	rm -rfv BUILD out
	make -j"$JOBS" clean build-with-glibc || exit -1
	print "Done building toolchain"
}


# Update glibc toolchain
#
function update_glibc() {
	cd "$NACL_TOOLCHAIN_BASE" || exit 1
	make updateglibc
}


# Update glibc 64bit toolchain
#
function update_glibc2() {
	cd "$NACL_TOOLCHAIN_BASE" || exit 1
	rm -fv BUILD/stamp-glibc64
	make BUILD/stamp-glibc64
}


# Run the glibc tester
#
function glibc_tester() {
	set -o errexit

	cd "$MISC_DIR/glibc_test/" || exit 1
	make clean all

	cd .. || exit 1
	rm -rfv lind.metadata linddata.*
	lind "$MISC_DIR/glibc_test/glibc_tester.nexe"
}

PS3='build what: '

list+=(all repy nacl buildglibc updateglibc updateglibc2 cleantoolchain)
list+=(download cleannacl install liblind test_repy test_glibc test_apps)
list+=(sdk rpc test nightly)

if ((!$#)); then
	select choice in "${list[@]}"; do
		set -- "$choice"
		break
	done
fi

start_time=$(date +%s)

# All scripts assume we start here
while (($#)); do
	if [[ "$1" == repy ]]; then
		build_repy
	elif [[ "$1" == nacl ]]; then
		build_nacl
	elif [[ "$1" == buildglibc ]]; then
		build_glibc
	elif [[ "$1" == updateglibc ]]; then
		update_glibc
	elif [[ "$1" == updateglibc2 ]]; then
		update_glibc2
	elif [[ "$1" == download ]]; then
		download_src
	elif [[ "$1" == all ]]; then
		download_src
		build_nacl
		build_glibc
		build_repy
		install_to_path
	elif [[ "$1" == cleantoolchain ]]; then
		print "Cleaning Toolchain"
		clean_toolchain
	elif [[ "$1" == install ]]; then
		print "Installing libs into install dir"
		install_to_path
	elif [[ "$1" == cleannacl ]]; then
		print "Cleaning NaCl"
		clean_nacl
	elif [[ "$1" == liblind ]]; then
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
