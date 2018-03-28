#!/bin/bash
# Chris Matthews <cmatthew@cs.uvic.ca>
# Try to ease the burden of building lind (repy, nacl, and toolchain)


# Uncomment this to print each command as they are executed
# ≈set -o xtrace

# Uncomment this for debugging. Will stop B on any failed commands 
# set -o errexit

# Uncomment this to dump time profiling information out to a file to see where the script is slow
# PS4='+ $(date "+%s.%N")\011 '
# exec 3>&2 2> bashstart.$$.log
# set -x
trap 'echo "All done."' EXIT

if [ -z "$REPY_PATH" ]; then
   echo "Need to set REPY_PATH"
   exit 1
fi

if [ -z "$LIND_SRC" ]; then
   echo "Need to set LIND_SRC"
   exit 1
fi

readonly OS_NAME=$(uname -s)
if [ $OS_NAME = "Darwin" ]; then
  readonly OS_SUBDIR="mac"
elif [ $OS_NAME = "Linux" ]; then
  readonly OS_SUBDIR="linux"
else
  readonly OS_SUBDIR="win"
fi
readonly MODE='dbg-'${OS_SUBDIR}
readonly LIND_SRC=${LIND_SRC}
readonly MISC_DIR=${LIND_SRC}/misc
readonly NACL_SRC=${LIND_SRC}/nacl
readonly NACL_BASE=${NACL_SRC}/native_client
readonly NACL_TOOLCHAIN_BASE=${NACL_BASE}/tools
readonly LIND_GLIBC_SRC=${LIND_SRC}/lind_glibc
readonly NACL_REPY=${LIND_SRC}/nacl_repy
readonly NACL_PORTS_DIR=${LIND_SRC}/naclports

readonly REPY_PATH=${REPY_PATH}
readonly REPY_PATH_BIN=${REPY_PATH}/bin
readonly REPY_PATH_REPY=${REPY_PATH}/repy
readonly REPY_PATH_LIB=${REPY_PATH}/lib
readonly REPY_PATH_SDK=${REPY_PATH}/sdk

readonly LIND_GLIBC_URL='https://github.com/Lind-Project/Lind-GlibC.git'
readonly LIND_MISC_URL='https://github.com/Lind-Project/Lind-misc.git'
readonly NACL_REPY_URL='https://github.com/Lind-Project/nacl_repy.git'
readonly NACL_RUNTIME_URL='https://github.com/Lind-Project/native_client.git'

readonly RSYNC='rsync -avrc --force'

if [ "$NACL_SDK_ROOT" != "${REPY_PATH_SDK}" ]; then
  echo "You need to set \$NACL_SDK_ROOT to ${REPY_PATH_SDK}"
  exit 1
fi

function download_src {
  mkdir -p ${LIND_SRC}
  cd ${LIND_SRC} && rm -rf lind_glibc misc nacl_repy nacl
  
  git clone ${LIND_GLIBC_URL} lind_glibc
  cd lind_glibc
  git checkout -b one_proc_model origin/one_proc_model
  cd ..
  
  git clone ${LIND_MISC_URL} misc
  
  git clone ${NACL_REPY_URL} nacl_repy
  
  mkdir -p ${NACL_SRC}
  cd ${NACL_SRC}
  gclient config --name=native_client https://github.com/Lind-Project/native_client.git@lind --git-deps
  gclient sync
  cd ${NACL_TOOLCHAIN_BASE} && rm -fr SRC
  make sync-pinned
  cd SRC
  mv glibc glibc_orig
  ln -s ${LIND_GLIBC_SRC} glibc
  cd ..
  
  mkdir -p ${NACL_PORTS_DIR}
  cd ${NACL_PORTS_DIR}
  gclient config --name=src https://chromium.googlesource.com/external/naclports.git --git-deps
  gclient sync
  
  cd ${LIND_SRC}
}

#
#
#call this instead of echo, then we can do things like log and print to notifier
function print {
    echo $1
    #notify-send --icon=/usr/share/icons/gnome/256x256/apps/utilities-terminal.png "Build Script" "$1" >& /dev/null
}


#
# wipe the entire modular build toolchain build tree, then rebuild it
# Warning: this can take a while!
function clean_toolchain {
     cd ${NACL_TOOLCHAIN_BASE} && rm -rf out BUILD
}


# Compile liblind and the compoent programs.
# 
# 
function build_liblind {
    echo -ne "Building liblind... "
    cd ${MISC_DIR}/liblind && make clean all > /dev/null
    echo "done."

}


# Copy the toolchain files into the repy subdir.
#
# 
function install_to_path {
    # nothing should fail here.
    set -o errexit

    echo "Injecting Libs into RePy install"

    print "**Sending NaCl stuff to ${REPY_PATH}"

    #echo "Deleting all directories in the ${REPY_PATH} (except repy folder)"
    #rm -rf ${REPY_PATH_BIN}
    #rm -rf ${REPY_PATH_LIB}
    #rm -rf ${REPY_PATH_SDK}

    mkdir -p ${REPY_PATH_BIN}
    mkdir -p ${REPY_PATH_LIB}/glibc
    mkdir -p ${REPY_PATH_SDK}/toolchain/${OS_SUBDIR}_x86_glibc
    mkdir -p ${REPY_PATH_SDK}/tools

    ${RSYNC} ${NACL_TOOLCHAIN_BASE}/out/nacl-sdk/* ${REPY_PATH_SDK}/toolchain/${OS_SUBDIR}_x86_glibc
    #we need some files from the original sdk to help compile some applications (e.g. zlib)
    #${RSYNC} ${MISC_DIR}/${OS_SUBDIR}_pepper_28_tools/* ${REPY_PATH_SDK}/tools

    ${RSYNC} ${NACL_BASE}/scons-out/${MODE}-x86-64/staging/* ${REPY_PATH_BIN}

    #install script
    cp -f ${MISC_DIR}/lind.sh ${REPY_PATH_BIN}/lind
    chmod +x ${REPY_PATH_BIN}/lind
    
    ${RSYNC} ${NACL_TOOLCHAIN_BASE}/out/nacl-sdk/x86_64-nacl/lib/*  ${REPY_PATH_LIB}/glibc
}


# Run the RePy unit tests.
#
#
function test_repy {
    cd $REPY_PATH/repy/
    set +o errexit  # some of our unit tests fail
    for file in ut_lind_*; do 
	    echo $file 
        #trap 'python2.6 ${REPY_PATH}/repy/repy.py --safebinary ${REPY_PATH}/repy/restrictions.lind ${REPY_PATH}/repy/lind_server.py $@' INT TERM EXIT
        trap ';' TERM
        python $file
	    #trap 'python $file' INT TERM EXIT  
    done

    # run the struct test
    file=ut_seattlelibtests_teststruct.py
    echo $file 
    python $file  

}


# Run the applications test stuites.
#
#
function test_apps {
    set +o errexit
    cd ${MISC_DIR}/tests
	./test.sh
}

# Check the REPY_PATH location to make sure it is safe to be installing stuff there.
#
#
function check_install_dir {

    # and if it does not exit, make it.
    if [ ! -d "$REPY_PATH" ]; then
	mkdir -p ${REPY_PATH}
    fi

}


# Install repy into $REPY_PATH with the prepare_tests script.
#
#
function build_repy {

    set -o errexit

    mkdir -p ${REPY_PATH_REPY}

    print "Building Repy in $REPY_SRC to $REPY_PATH" 
    cd ${NACL_REPY}
    python preparetest.py -t -f ${REPY_PATH_REPY}
    print "Done building Repy in ${REPY_PATH_REPY}"
    cd seattlelib
    set -o errexit
    for file in *.mix
    do
	${MISC_DIR}/check_includes.sh $file
    done
    set +o errexit
    #etags  --language-force=python *.mix *.repy
}


# Update, build and test everything. If there is a problem, freak out.
#
#
function nightly_build {
    set -o errexit
    # Clean
    # clean_install
    # clean_nacl
    # clean_toolchain
    # check_install_dir
    # Update
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

}

function clean_install {
    rm -rf $REPY_PATH
    mkdir -p $REPY_PATH
}


# Run the NaCl build.
#
#
function build_nacl {
     print "Building NaCl"
     cd ${NACL_BASE} || exit -1

     # build NaCl with glibc tests
     ./scons --verbose --mode=${MODE},nacl platform=x86-64 --nacl_glibc -j4
     # and check
     rc=$?
     if [ "$rc" -ne "0" ]; then
	     print "NaCl Build Failed($rc)"
	     echo -e "\a"
	     exit $rc
     fi

     print "Done building NaCl $rc"
}


# Run clean on nacl build.
#
#
function clean_nacl {
     cd ${NACL_BASE}
     ./scons --mode=${MODE},nacl platform=x86-64 --nacl_glibc -c
     print "Done Cleaning NaCl"
}


# Build glibc from source
#
#
function build_glibc {
     # the build is long and borning, so execute this first if it exists
     type -P fortune &>/dev/null && fortune || echo "Fortune Not Found. Skipping." 

     echo -ne "Copy component.h header to glibc: "
     cd ${MISC_DIR}/liblind
     cp -fvp component.h ${LIND_GLIBC_SRC}/sysdeps/nacl/
     echo "done."

     echo "Building glibc"

     # if extra files (like editor temp files) are in the subdir glibc tries to compile them too.
     # move them here so they dont cause a problem
     cd ${LIND_GLIBC_SRC}/sysdeps/nacl/
     shopt -s nullglob
     for f in .#*;
     do
	 print "moving editor backupfile ${f} so it does not get caught in build."
	 mv -f ${f} .
     done

     #turns out this works better if you do it from the nacl base dir
     cd ${NACL_TOOLCHAIN_BASE} && rm -fr BUILD out
     make clean build-with-glibc -j4 || exit -1
     
     print "Done building toolchain"
}

function update_glibc {
    cd ${NACL_TOOLCHAIN_BASE} && make updateglibc
}

function update_glibc2 {
    cd ${NACL_TOOLCHAIN_BASE} && rm BUILD/stamp-glibc64
    make BUILD/stamp-glibc64
}

# Run the glibc tester
#
#
function glibc_tester {
    set -o errexit

    cd ${MISC_DIR}/glibc_test/
    make clean all
    cd ..
    rm -rfv lind.metadata linddata.*
    lind ${MISC_DIR}/glibc_test/glibc_tester.nexe
}

PS3="build what: " 
list="all repy nacl buildglibc updateglibc updateglibc2 cleantoolchain download cleannacl install liblind test_repy test_glibc test_apps sdk rpc test nightly"
word=""
if  test -z "$1" 
then
    select foo in $list;
    do
       args=("$foo")
       break
    done
else
    args=("$@")
fi

START_TIME=$(date +%s)

# all scripts assume we start here
echo ${args[0]} ${args[1]}
ELEMENTS=${#args[@]}
for  (( i=0;i<$ELEMENTS;i++));
do
    word=${args[${i}]}
    if [ "$word" = "repy" ]; then
	    build_repy
    elif [ "$word" = "nacl" ]; then
	    build_nacl
    elif [ "$word" = "buildglibc" ]; then
	    build_glibc
    elif [ "$word" = "updateglibc" ]; then
            update_glibc
    elif [ "$word" = "updateglibc2" ]; then
            update_glibc2
    elif [ "$word" = "download" ]; then
            download_src
    elif [ "$word" = "all" ]; then
            download_src
	    build_nacl
	    build_glibc
	    build_repy
	    install_to_path
    elif [ "$word" = "cleantoolchain" ]; then
	    print "Cleaning Toolchain"
	    clean_toolchain
    elif [ "$word" = "install" ]; then
	    print "Installing libs into install dir"
	    install_to_path
    elif [ "$word" = "cleannacl" ]; then
	    print "Cleaning NaCl"
	    clean_nacl
    elif [ "$word" = "liblind" ]; then
	    print "Building LibLind"
	    build_liblind
    elif [ "$word" = "test_repy" ]; then
	    print "Testing Repy"
	    test_repy
    elif [ "$word" = "test_glibc" ]; then
	    print "Testing GLibC"
	    glibc_tester
    elif [ "$word" = "test_apps" ]; then
	    print "Testing Applications"
	    test_apps
    elif [ "$word" = "test" ]; then
	    print "Testing All"
	    test_repy
	    glibc_tester
	    test_apps
    elif [ "$word" = "nightly" ]; then
	    print "Nightly Build"
	    nightly_build
    else 
	    echo "Error: Did not find a build target named $word. Exiting..."
	    exit 1
    fi
done


END_TIME=$(date +%s)
DIFF=$(( $END_TIME - $START_TIME ))
echo "It took $DIFF seconds"
echo -e "\a"


