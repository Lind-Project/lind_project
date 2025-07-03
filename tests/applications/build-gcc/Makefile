
# Makefile.in is generated from Makefile.tpl by 'autogen Makefile.def'.
#
# Makefile for directory with subdirs to build.
#   Copyright (C) 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998,
#   1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2009
#   Free Software Foundation
#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING3.  If not see
# <http://www.gnu.org/licenses/>.
#

# First, test for a proper version of make, but only where one is required.

ifeq (,$(.VARIABLES)) # The variable .VARIABLES, new with 3.80, is never empty.
$(error GNU make version 3.80 or newer is required.)
endif

# -------------------------------
# Standard Autoconf-set variables
# -------------------------------
VPATH=../gcc-4.4.3

build_alias=x86_64-unknown-linux-gnu
build_vendor=unknown
build_os=linux-gnu
build=x86_64-unknown-linux-gnu
host_alias=x86_64-unknown-linux-gnu
host_vendor=unknown
host_os=linux-gnu
host=x86_64-unknown-linux-gnu
target_alias=x86_64-unknown-linux-gnu
target_vendor=unknown
target_os=linux-gnu
target=x86_64-unknown-linux-gnu

program_transform_name = s,y,y,

prefix = /usr/local/gcc-4.4.3/
exec_prefix = ${prefix}

srcdir = ../gcc-4.4.3

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
includedir = ${prefix}/include
oldincludedir = /usr/include
infodir = ${prefix}/info
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc
pdfdir = ${docdir}
htmldir = ${docdir}
mandir = ${prefix}/man
man1dir = $(mandir)/man1
man2dir = $(mandir)/man2
man3dir = $(mandir)/man3
man4dir = $(mandir)/man4
man5dir = $(mandir)/man5
man6dir = $(mandir)/man6
man7dir = $(mandir)/man7
man8dir = $(mandir)/man8
man9dir = $(mandir)/man9

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
LN = ln
LN_S = ln -s
MAINT = #
MAINTAINER_MODE_FALSE = 
MAINTAINER_MODE_TRUE = #

# -------------------------------------------------
# Miscellaneous non-standard autoconf-set variables
# -------------------------------------------------

# The gcc driver likes to know the arguments it was configured with.
TOPLEVEL_CONFIGURE_ARGUMENTS=../gcc-4.4.3/configure CC=gcc CFLAGS='-fgnu89-inline -g -O2' CXXFLAGS='-fgnu89-inline -g -O2' --prefix=/usr/local/gcc-4.4.3/ --enable-checking=release --enable-languages=c,c++ --disable-multili

tooldir = ${exec_prefix}/x86_64-unknown-linux-gnu
build_tooldir = ${exec_prefix}/x86_64-unknown-linux-gnu

GDB_NLM_DEPS = 

# This is the name of the environment variable used for the path to
# the libraries.
RPATH_ENVVAR = LD_LIBRARY_PATH

# On targets where RPATH_ENVVAR is PATH, a subdirectory of the GCC build path
# is used instead of the directory itself to avoid including built
# executables in PATH.
GCC_SHLIB_SUBDIR = 

# Build programs are put under this directory.
BUILD_SUBDIR = build-x86_64-unknown-linux-gnu
# This is set by the configure script to the arguments to use when configuring
# directories built for the build system.
BUILD_CONFIGARGS = --cache-file=../config.cache '--prefix=/usr/local/gcc-4.4.3/' '--enable-checking=release' '--disable-multili' '--enable-languages=c,c++' --program-transform-name='s,y,y,' --with-build-subdir="$(BUILD_SUBDIR)"

# This is the list of variables to export in the environment when
# configuring any subdirectory.  It must also be exported whenever
# recursing into a build directory in case that directory's Makefile
# re-runs configure.
BASE_EXPORTS = \
	FLEX="$(FLEX)"; export FLEX; \
	LEX="$(LEX)"; export LEX; \
	BISON="$(BISON)"; export BISON; \
	YACC="$(YACC)"; export YACC; \
	M4="$(M4)"; export M4; \
	MAKEINFO="$(MAKEINFO)"; export MAKEINFO;

# This is the list of variables to export in the environment when
# configuring subdirectories for the build system.
BUILD_EXPORTS = \
	$(BASE_EXPORTS) \
	AR="$(AR_FOR_BUILD)"; export AR; \
	AS="$(AS_FOR_BUILD)"; export AS; \
	CC="$(CC_FOR_BUILD)"; export CC; \
	CFLAGS="$(CFLAGS_FOR_BUILD)"; export CFLAGS; \
	CONFIG_SHELL="$(SHELL)"; export CONFIG_SHELL; \
	CXX="$(CXX_FOR_BUILD)"; export CXX; \
	CXXFLAGS="$(CXXFLAGS_FOR_BUILD)"; export CXXFLAGS; \
	GCJ="$(GCJ_FOR_BUILD)"; export GCJ; \
	GFORTRAN="$(GFORTRAN_FOR_BUILD)"; export GFORTRAN; \
	DLLTOOL="$(DLLTOOL_FOR_BUILD)"; export DLLTOOL; \
	LD="$(LD_FOR_BUILD)"; export LD; \
	LDFLAGS="$(LDFLAGS_FOR_BUILD)"; export LDFLAGS; \
	NM="$(NM_FOR_BUILD)"; export NM; \
	RANLIB="$(RANLIB_FOR_BUILD)"; export RANLIB; \
	WINDRES="$(WINDRES_FOR_BUILD)"; export WINDRES; \
	WINDMC="$(WINDMC_FOR_BUILD)"; export WINDMC;

# These variables must be set on the make command line for directories
# built for the build system to override those in BASE_FLAGS_TO_PASSS.
EXTRA_BUILD_FLAGS = \
	CFLAGS="$(CFLAGS_FOR_BUILD)" \
	LDFLAGS="$(LDFLAGS_FOR_BUILD)"

# This is the list of directories to built for the host system.
SUBDIRS =  intl libiberty libcpp libdecnumber gmp mpfr fixincludes gcc
# This is set by the configure script to the arguments to use when configuring
# directories built for the host system.
HOST_CONFIGARGS = --cache-file=./config.cache  '--prefix=/usr/local/gcc-4.4.3/' '--enable-checking=release' '--disable-multili' '--enable-languages=c,c++' --program-transform-name='s,y,y,'
# Host programs are put under this directory, which is . except if building
# with srcdir=..
HOST_SUBDIR = .
# This is the list of variables to export in the environment when
# configuring subdirectories for the host system.  We need to pass
# some to the GCC configure because of its hybrid host/target nature.
HOST_EXPORTS = \
	$(BASE_EXPORTS) \
	CC="$(CC)"; export CC; \
	ADA_CFLAGS="$(ADA_CFLAGS)"; export ADA_CFLAGS; \
	CFLAGS="$(CFLAGS)"; export CFLAGS; \
	CONFIG_SHELL="$(SHELL)"; export CONFIG_SHELL; \
	CXX="$(CXX)"; export CXX; \
	CXXFLAGS="$(CXXFLAGS)"; export CXXFLAGS; \
	AR="$(AR)"; export AR; \
	AS="$(AS)"; export AS; \
	CC_FOR_BUILD="$(CC_FOR_BUILD)"; export CC_FOR_BUILD; \
	DLLTOOL="$(DLLTOOL)"; export DLLTOOL; \
	LD="$(LD)"; export LD; \
	LDFLAGS="$(LDFLAGS)"; export LDFLAGS; \
	NM="$(NM)"; export NM; \
	RANLIB="$(RANLIB)"; export RANLIB; \
	WINDRES="$(WINDRES)"; export WINDRES; \
	WINDMC="$(WINDMC)"; export WINDMC; \
	OBJCOPY="$(OBJCOPY)"; export OBJCOPY; \
	OBJDUMP="$(OBJDUMP)"; export OBJDUMP; \
	AR_FOR_TARGET="$(AR_FOR_TARGET)"; export AR_FOR_TARGET; \
	AS_FOR_TARGET="$(AS_FOR_TARGET)"; export AS_FOR_TARGET; \
	GCC_FOR_TARGET="$(GCC_FOR_TARGET)"; export GCC_FOR_TARGET; \
	LD_FOR_TARGET="$(LD_FOR_TARGET)"; export LD_FOR_TARGET; \
	NM_FOR_TARGET="$(NM_FOR_TARGET)"; export NM_FOR_TARGET; \
	OBJDUMP_FOR_TARGET="$(OBJDUMP_FOR_TARGET)"; export OBJDUMP_FOR_TARGET; \
	RANLIB_FOR_TARGET="$(RANLIB_FOR_TARGET)"; export RANLIB_FOR_TARGET; \
	TOPLEVEL_CONFIGURE_ARGUMENTS="$(TOPLEVEL_CONFIGURE_ARGUMENTS)"; export TOPLEVEL_CONFIGURE_ARGUMENTS; \
	GMPLIBS="$(HOST_GMPLIBS)"; export GMPLIBS; \
	GMPINC="$(HOST_GMPINC)"; export GMPINC; \
	PPLLIBS="$(HOST_PPLLIBS)"; export PPLLIBS; \
	PPLINC="$(HOST_PPLINC)"; export PPLINC; \
	CLOOGLIBS="$(HOST_CLOOGLIBS)"; export CLOOGLIBS; \
	CLOOGINC="$(HOST_CLOOGINC)"; export CLOOGINC; \
	$(RPATH_ENVVAR)=`echo "$(TARGET_LIB_PATH)$$$(RPATH_ENVVAR)" | sed 's,::*,:,g;s,^:*,,;s,:*$$,,'`; export $(RPATH_ENVVAR); \
	$(RPATH_ENVVAR)=`echo "$(HOST_LIB_PATH)$$$(RPATH_ENVVAR)" | sed 's,::*,:,g;s,^:*,,;s,:*$$,,'`; export $(RPATH_ENVVAR);

# Similar, for later GCC stages.
POSTSTAGE1_HOST_EXPORTS = \
	$(HOST_EXPORTS) \
	CC="$(STAGE_CC_WRAPPER) $$r/$(HOST_SUBDIR)/prev-gcc/xgcc$(exeext) \
	  -B$$r/$(HOST_SUBDIR)/prev-gcc/ -B$(build_tooldir)/bin/"; export CC; \
	CC_FOR_BUILD="$(STAGE_CC_WRAPPER) \
	  $$r/$(HOST_SUBDIR)/prev-gcc/xgcc$(exeext) \
	  -B$$r/$(HOST_SUBDIR)/prev-gcc/ \
	  -B$(build_tooldir)/bin/"; export CC_FOR_BUILD; \
	LDFLAGS="$(BOOT_LDFLAGS)"; export LDFLAGS;

# Target libraries are put under this directory:
TARGET_SUBDIR = x86_64-unknown-linux-gnu
# This is set by the configure script to the arguments to use when configuring
# directories built for the target.
TARGET_CONFIGARGS = --cache-file=./config.cache --enable-multilib '--prefix=/usr/local/gcc-4.4.3/' '--enable-checking=release' '--disable-multili' '--enable-languages=c,c++' --program-transform-name='s,y,y,' --with-target-subdir="$(TARGET_SUBDIR)"
# This is the list of variables to export in the environment when
# configuring subdirectories for the host system.
BASE_TARGET_EXPORTS = \
	$(BASE_EXPORTS) \
	AR="$(AR_FOR_TARGET)"; export AR; \
	AS="$(COMPILER_AS_FOR_TARGET)"; export AS; \
	CC="$(CC_FOR_TARGET)"; export CC; \
	CFLAGS="$(CFLAGS_FOR_TARGET) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CONFIG_SHELL="$(SHELL)"; export CONFIG_SHELL; \
	CPPFLAGS="$(CPPFLAGS_FOR_TARGET)"; export CPPFLAGS; \
	CXXFLAGS="$(CXXFLAGS_FOR_TARGET) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS; \
	GCJ="$(GCJ_FOR_TARGET)"; export GCJ; \
	GFORTRAN="$(GFORTRAN_FOR_TARGET)"; export GFORTRAN; \
	DLLTOOL="$(DLLTOOL_FOR_TARGET)"; export DLLTOOL; \
	LD="$(COMPILER_LD_FOR_TARGET)"; export LD; \
	LDFLAGS="$(LDFLAGS_FOR_TARGET)"; export LDFLAGS; \
	LIPO="$(LIPO_FOR_TARGET)"; export LIPO; \
	NM="$(COMPILER_NM_FOR_TARGET)"; export NM; \
	OBJDUMP="$(OBJDUMP_FOR_TARGET)"; export OBJDUMP; \
	RANLIB="$(RANLIB_FOR_TARGET)"; export RANLIB; \
	STRIP="$(STRIP_FOR_TARGET)"; export STRIP; \
	WINDRES="$(WINDRES_FOR_TARGET)"; export WINDRES; \
	WINDMC="$(WINDMC_FOR_TARGET)"; export WINDMC; \
	$(RPATH_ENVVAR)=`echo "$(HOST_LIB_PATH)$(TARGET_LIB_PATH)$$$(RPATH_ENVVAR)" | sed 's,::*,:,g;s,^:*,,;s,:*$$,,'`; export $(RPATH_ENVVAR);

RAW_CXX_TARGET_EXPORTS = \
	$(BASE_TARGET_EXPORTS) \
	CXX_FOR_TARGET="$(RAW_CXX_FOR_TARGET)"; export CXX_FOR_TARGET; \
	CXX="$(RAW_CXX_FOR_TARGET)"; export CXX;

NORMAL_TARGET_EXPORTS = \
	$(BASE_TARGET_EXPORTS) \
	CXX="$(CXX_FOR_TARGET)"; export CXX;

# Where to find GMP
HOST_GMPLIBS = -L$$r/$(HOST_SUBDIR)/gmp/.libs -L$$r/$(HOST_SUBDIR)/gmp/_libs -L$$r/$(HOST_SUBDIR)/mpfr/.libs -L$$r/$(HOST_SUBDIR)/mpfr/_libs -lmpfr -lgmp
HOST_GMPINC = -I$$r/$(HOST_SUBDIR)/gmp -I$$s/gmp -I$$r/$(HOST_SUBDIR)/mpfr -I$$s/mpfr 

# Where to find PPL
HOST_PPLLIBS = 
HOST_PPLINC = 

# Where to find CLOOG
HOST_CLOOGLIBS = 
HOST_CLOOGINC = 

# ----------------------------------------------
# Programs producing files for the BUILD machine
# ----------------------------------------------

SHELL = /bin/bash

# pwd command to use.  Allow user to override default by setting PWDCMD in
# the environment to account for automounters.  The make variable must not
# be called PWDCMD, otherwise the value set here is passed to make
# subprocesses and overrides the setting from the user's environment.
# Don't use PWD since it is a common shell environment variable and we
# don't want to corrupt it.
PWD_COMMAND = $${PWDCMD-pwd}

# compilers to use to create programs which must be run in the build
# environment.
AR_FOR_BUILD = $(AR)
AS_FOR_BUILD = $(AS)
CC_FOR_BUILD = $(CC)
CFLAGS_FOR_BUILD = -fgnu89-inline -g -O2
CXXFLAGS_FOR_BUILD = -fgnu89-inline -g -O2
CXX_FOR_BUILD = $(CXX)
DLLTOOL_FOR_BUILD = $(DLLTOOL)
GCJ_FOR_BUILD = $(GCJ)
GFORTRAN_FOR_BUILD = $(GFORTRAN)
LDFLAGS_FOR_BUILD = 
LD_FOR_BUILD = $(LD)
NM_FOR_BUILD = $(NM)
RANLIB_FOR_BUILD = $(RANLIB)
WINDMC_FOR_BUILD = $(WINDMC)
WINDRES_FOR_BUILD = $(WINDRES)

# Special variables passed down in EXTRA_GCC_FLAGS.  They are defined
# here so that they can be overridden by Makefile fragments.
BUILD_PREFIX = @BUILD_PREFIX@
BUILD_PREFIX_1 = @BUILD_PREFIX_1@

# Flags to pass to stage2 and later makes.  They are defined
# here so that they can be overridden by Makefile fragments.
BOOT_CFLAGS= -g -O2
BOOT_LDFLAGS=
BOOT_ADAFLAGS=-gnatpg -gnata

BISON = bison
YACC = bison -y
FLEX = /home/lind/lind_project/tests/applications/gcc-4.4.3/missing flex
LEX = /home/lind/lind_project/tests/applications/gcc-4.4.3/missing flex
M4 = m4
MAKEINFO = makeinfo
EXPECT = expect
RUNTEST = runtest

# This just becomes part of the MAKEINFO definition passed down to
# sub-makes.  It lets flags be given on the command line while still
# using the makeinfo from the object tree.
# (Default to avoid splitting info files by setting the threshold high.)
MAKEINFOFLAGS = --split-size=5000000

# ---------------------------------------------
# Programs producing files for the HOST machine
# ---------------------------------------------

AS = as
AR = ar
AR_FLAGS = rc
CC = gcc -fgnu89-inline
CXX = g++ -fgnu89-inline
DLLTOOL = dlltool
LD = ld
LIPO = lipo
NM = nm
OBJDUMP = objdump
RANLIB = ranlib
STRIP = strip
WINDRES = windres
WINDMC = windmc

GNATBIND = no
GNATMAKE = no

CFLAGS = -fgnu89-inline -g -O2
LDFLAGS = 
LIBCFLAGS = $(CFLAGS)
CXXFLAGS = -fgnu89-inline -g -O2
LIBCXXFLAGS = $(CXXFLAGS) -fno-implicit-templates

# Only build the C compiler for stage1, because that is the only one that
# we can guarantee will build with the native compiler, and also it is the
# only thing useful for building stage2. STAGE1_CFLAGS (via CFLAGS),
# MAKEINFO and MAKEINFOFLAGS are explicitly passed here to make them
# overrideable (for a bootstrap build stage1 also builds gcc.info).

STAGE1_CHECKING=--enable-checking=release,types
STAGE1_LANGUAGES=c

STAGE1_CFLAGS=-g -fkeep-inline-functions
STAGE2_CFLAGS=$(BOOT_CFLAGS)
STAGE3_CFLAGS=$(BOOT_CFLAGS)
STAGE4_CFLAGS=$(BOOT_CFLAGS)

STAGE1_LIBCFLAGS=$(CFLAGS_FOR_TARGET)
STAGE2_LIBCFLAGS=$(CFLAGS_FOR_TARGET)
STAGE3_LIBCFLAGS=$(CFLAGS_FOR_TARGET)
STAGE4_LIBCFLAGS=$(CFLAGS_FOR_TARGET)

do-compare = cmp --ignore-initial=16 $$f1 $$f2
do-compare3 = $(do-compare)
do-compare-debug = $(SHELL) $(srcdir)/contrib/compare-debug $$f1 $$f2

# -----------------------------------------------
# Programs producing files for the TARGET machine
# -----------------------------------------------

FLAGS_FOR_TARGET =  -B$(build_tooldir)/bin/ -B$(build_tooldir)/lib/ -isystem $(build_tooldir)/include -isystem $(build_tooldir)/sys-include

AR_FOR_TARGET=$(AR)
AS_FOR_TARGET=$(AS)
CC_FOR_TARGET=$(STAGE_CC_WRAPPER) $$r/$(HOST_SUBDIR)/gcc/xgcc -B$$r/$(HOST_SUBDIR)/gcc/ $(FLAGS_FOR_TARGET)

# If GCC_FOR_TARGET is not overriden on the command line, then this
# variable is passed down to the gcc Makefile, where it is used to
# build libgcc2.a.  We define it here so that it can itself be
# overridden on the command line.
GCC_FOR_TARGET=$(STAGE_CC_WRAPPER) $$r/$(HOST_SUBDIR)/gcc/xgcc -B$$r/$(HOST_SUBDIR)/gcc/ $(FLAGS_FOR_TARGET)
CXX_FOR_TARGET=$(STAGE_CC_WRAPPER) $$r/$(HOST_SUBDIR)/gcc/g++ -B$$r/$(HOST_SUBDIR)/gcc/ -nostdinc++ `test ! -f $$r/$(TARGET_SUBDIR)/libstdc++-v3/scripts/testsuite_flags || $(SHELL) $$r/$(TARGET_SUBDIR)/libstdc++-v3/scripts/testsuite_flags --build-includes` -L$$r/$(TARGET_SUBDIR)/libstdc++-v3/src -L$$r/$(TARGET_SUBDIR)/libstdc++-v3/src/.libs $(FLAGS_FOR_TARGET)
RAW_CXX_FOR_TARGET=$(STAGE_CC_WRAPPER) $$r/$(HOST_SUBDIR)/gcc/xgcc -shared-libgcc -B$$r/$(HOST_SUBDIR)/gcc -nostdinc++ -L$$r/$(TARGET_SUBDIR)/libstdc++-v3/src -L$$r/$(TARGET_SUBDIR)/libstdc++-v3/src/.libs $(FLAGS_FOR_TARGET)
GCJ_FOR_TARGET=$(STAGE_CC_WRAPPER) $(GCJ) $(FLAGS_FOR_TARGET)
GFORTRAN_FOR_TARGET=$(STAGE_CC_WRAPPER) $(GFORTRAN) $(FLAGS_FOR_TARGET)
DLLTOOL_FOR_TARGET=$(DLLTOOL)
LD_FOR_TARGET=$(LD)

LIPO_FOR_TARGET=$(LIPO)
NM_FOR_TARGET=$(NM)
OBJDUMP_FOR_TARGET=$(OBJDUMP)
RANLIB_FOR_TARGET=$(RANLIB)
STRIP_FOR_TARGET=$(STRIP)
WINDRES_FOR_TARGET=$(WINDRES)
WINDMC_FOR_TARGET=$(WINDMC)

COMPILER_AS_FOR_TARGET=$$r/$(HOST_SUBDIR)/gcc/as
COMPILER_LD_FOR_TARGET=$$r/$(HOST_SUBDIR)/gcc/collect-ld
COMPILER_NM_FOR_TARGET=$$r/$(HOST_SUBDIR)/gcc/nm

CFLAGS_FOR_TARGET = -fgnu89-inline -g -O2
CXXFLAGS_FOR_TARGET = -fgnu89-inline -g -O2
SYSROOT_CFLAGS_FOR_TARGET = 
DEBUG_PREFIX_CFLAGS_FOR_TARGET = 

LIBCFLAGS_FOR_TARGET = $(CFLAGS_FOR_TARGET)
LIBCXXFLAGS_FOR_TARGET = $(CXXFLAGS_FOR_TARGET) -fno-implicit-templates
LDFLAGS_FOR_TARGET = 

# ------------------------------------
# Miscellaneous targets and flag lists
# ------------------------------------

# The first rule in the file had better be this one.  Don't put any above it.
# This lives here to allow makefile fragments to contain dependencies.
all:

#### host and target specific makefile fragments come in here.

CXXFLAGS_FOR_TARGET = $(CXXFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) \
	$(DEBUG_PREFIX_CFLAGS_FOR_TARGET) -D_GNU_SOURCE



###

# This is the list of directories that may be needed in RPATH_ENVVAR
# so that prorgams built for the target machine work.
TARGET_LIB_PATH = $(TARGET_LIB_PATH_libstdc++-v3)$(TARGET_LIB_PATH_libmudflap)$(TARGET_LIB_PATH_libssp)$(TARGET_LIB_PATH_libgomp)$(HOST_LIB_PATH_gcc)

TARGET_LIB_PATH_libstdc++-v3 = $$r/$(TARGET_SUBDIR)/libstdc++-v3/.libs:

TARGET_LIB_PATH_libmudflap = $$r/$(TARGET_SUBDIR)/libmudflap/.libs:

TARGET_LIB_PATH_libssp = $$r/$(TARGET_SUBDIR)/libssp/.libs:

TARGET_LIB_PATH_libgomp = $$r/$(TARGET_SUBDIR)/libgomp/.libs:



# This is the list of directories that may be needed in RPATH_ENVVAR
# so that programs built for the host machine work.
HOST_LIB_PATH = $(HOST_LIB_PATH_bfd)$(HOST_LIB_PATH_opcodes)$(HOST_LIB_PATH_gmp)$(HOST_LIB_PATH_mpfr)$(HOST_LIB_PATH_ppl)$(HOST_LIB_PATH_cloog)

# Define HOST_LIB_PATH_gcc here, for the sake of TARGET_LIB_PATH, ouch
HOST_LIB_PATH_gcc = $$r/$(HOST_SUBDIR)/gcc$(GCC_SHLIB_SUBDIR):$$r/$(HOST_SUBDIR)/prev-gcc$(GCC_SHLIB_SUBDIR):




HOST_LIB_PATH_gmp = \
  $$r/$(HOST_SUBDIR)/gmp/.libs:$$r/$(HOST_SUBDIR)/prev-gmp/.libs:

HOST_LIB_PATH_mpfr = \
  $$r/$(HOST_SUBDIR)/mpfr/.libs:$$r/$(HOST_SUBDIR)/prev-mpfr/.libs:




# Flags to pass down to all sub-makes.
BASE_FLAGS_TO_PASS = \
	"DESTDIR=$(DESTDIR)" \
	"RPATH_ENVVAR=$(RPATH_ENVVAR)" \
	"TARGET_SUBDIR=$(TARGET_SUBDIR)" \
	"bindir=$(bindir)" \
	"datadir=$(datadir)" \
	"exec_prefix=$(exec_prefix)" \
	"includedir=$(includedir)" \
	"datarootdir=$(datarootdir)" \
	"docdir=$(docdir)" \
	"infodir=$(infodir)" \
	"pdfdir=$(pdfdir)" \
	"htmldir=$(htmldir)" \
	"libdir=$(libdir)" \
	"libexecdir=$(libexecdir)" \
	"lispdir=$(lispdir)" \
	"localstatedir=$(localstatedir)" \
	"mandir=$(mandir)" \
	"oldincludedir=$(oldincludedir)" \
	"prefix=$(prefix)" \
	"sbindir=$(sbindir)" \
	"sharedstatedir=$(sharedstatedir)" \
	"sysconfdir=$(sysconfdir)" \
	"tooldir=$(tooldir)" \
	"build_tooldir=$(build_tooldir)" \
	"target_alias=$(target_alias)" \
	"BISON=$(BISON)" \
	"CC_FOR_BUILD=$(CC_FOR_BUILD)" \
	"CFLAGS_FOR_BUILD=$(CFLAGS_FOR_BUILD)" \
	"CXX_FOR_BUILD=$(CXX_FOR_BUILD)" \
	"EXPECT=$(EXPECT)" \
	"FLEX=$(FLEX)" \
	"INSTALL=$(INSTALL)" \
	"INSTALL_DATA=$(INSTALL_DATA)" \
	"INSTALL_PROGRAM=$(INSTALL_PROGRAM)" \
	"INSTALL_SCRIPT=$(INSTALL_SCRIPT)" \
	"LDFLAGS_FOR_BUILD=$(LDFLAGS_FOR_BUILD)" \
	"LEX=$(LEX)" \
	"M4=$(M4)" \
	"MAKE=$(MAKE)" \
	"RUNTEST=$(RUNTEST)" \
	"RUNTESTFLAGS=$(RUNTESTFLAGS)" \
	"SHELL=$(SHELL)" \
	"YACC=$(YACC)" \
	"`echo 'ADAFLAGS=$(ADAFLAGS)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`" \
	"ADA_CFLAGS=$(ADA_CFLAGS)" \
	"AR_FLAGS=$(AR_FLAGS)" \
	"`echo 'BOOT_ADAFLAGS=$(BOOT_ADAFLAGS)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`" \
	"BOOT_CFLAGS=$(BOOT_CFLAGS)" \
	"BOOT_LDFLAGS=$(BOOT_LDFLAGS)" \
	"CFLAGS=$(CFLAGS)" \
	"CXXFLAGS=$(CXXFLAGS)" \
	"LDFLAGS=$(LDFLAGS)" \
	"LIBCFLAGS=$(LIBCFLAGS)" \
	"LIBCXXFLAGS=$(LIBCXXFLAGS)" \
	"STAGE1_CFLAGS=$(STAGE1_CFLAGS)" \
	"STAGE1_CHECKING=$(STAGE1_CHECKING)" \
	"STAGE1_LANGUAGES=$(STAGE1_LANGUAGES)" \
	"STAGE2_CFLAGS=$(STAGE2_CFLAGS)" \
	"STAGE3_CFLAGS=$(STAGE3_CFLAGS)" \
	"STAGE4_CFLAGS=$(STAGE4_CFLAGS)" \
	"GNATBIND=$(GNATBIND)" \
	"GNATMAKE=$(GNATMAKE)" \
	"AR_FOR_TARGET=$(AR_FOR_TARGET)" \
	"AS_FOR_TARGET=$(AS_FOR_TARGET)" \
	"CC_FOR_TARGET=$(CC_FOR_TARGET)" \
	"CFLAGS_FOR_TARGET=$(CFLAGS_FOR_TARGET)" \
	"CPPFLAGS_FOR_TARGET=$(CPPFLAGS_FOR_TARGET)" \
	"CXX_FOR_TARGET=$(CXX_FOR_TARGET)" \
	"CXXFLAGS_FOR_TARGET=$(CXXFLAGS_FOR_TARGET)" \
	"DLLTOOL_FOR_TARGET=$(DLLTOOL_FOR_TARGET)" \
	"GCJ_FOR_TARGET=$(GCJ_FOR_TARGET)" \
	"GFORTRAN_FOR_TARGET=$(GFORTRAN_FOR_TARGET)" \
	"LD_FOR_TARGET=$(LD_FOR_TARGET)" \
	"LIPO_FOR_TARGET=$(LIPO_FOR_TARGET)" \
	"LDFLAGS_FOR_TARGET=$(LDFLAGS_FOR_TARGET)" \
	"LIBCFLAGS_FOR_TARGET=$(LIBCFLAGS_FOR_TARGET)" \
	"LIBCXXFLAGS_FOR_TARGET=$(LIBCXXFLAGS_FOR_TARGET)" \
	"NM_FOR_TARGET=$(NM_FOR_TARGET)" \
	"OBJDUMP_FOR_TARGET=$(OBJDUMP_FOR_TARGET)" \
	"RANLIB_FOR_TARGET=$(RANLIB_FOR_TARGET)" \
	"STRIP_FOR_TARGET=$(STRIP_FOR_TARGET)" \
	"WINDRES_FOR_TARGET=$(WINDRES_FOR_TARGET)" \
	"WINDMC_FOR_TARGET=$(WINDMC_FOR_TARGET)" \
	"`echo 'LANGUAGES=$(LANGUAGES)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`" \
	"LEAN=$(LEAN)" \
	"CONFIG_SHELL=$(SHELL)" \
	"MAKEINFO=$(MAKEINFO) $(MAKEINFOFLAGS)" 

# We leave this in just in case, but it is not needed anymore.
RECURSE_FLAGS_TO_PASS = $(BASE_FLAGS_TO_PASS)

# Flags to pass down to most sub-makes, in which we're building with
# the host environment.
EXTRA_HOST_FLAGS = \
	'AR=$(AR)' \
	'AS=$(AS)' \
	'CC=$(CC)' \
	'CXX=$(CXX)' \
	'DLLTOOL=$(DLLTOOL)' \
	'LD=$(LD)' \
	'LIPO=$(LIPO)' \
	'NM=$(NM)' \
	'OBJDUMP=$(OBJDUMP)' \
	'RANLIB=$(RANLIB)' \
	'STRIP=$(STRIP)' \
	'WINDRES=$(WINDRES)' \
	'WINDMC=$(WINDMC)'

FLAGS_TO_PASS = $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)

# Flags that are concerned with the location of the X11 include files
# and library files
#
# NOTE: until the top-level is getting the values via autoconf, it only
# causes problems to have this top-level Makefile overriding the autoconf-set
# values in child directories.  Only variables that don't conflict with
# autoconf'ed ones should be passed by X11_FLAGS_TO_PASS for now.
#
X11_FLAGS_TO_PASS = \
	'X11_EXTRA_CFLAGS=$(X11_EXTRA_CFLAGS)' \
	'X11_EXTRA_LIBS=$(X11_EXTRA_LIBS)'

# Flags to pass to stage2 and later makes.

POSTSTAGE1_FLAGS_TO_PASS = \
	CC="$${CC}" CC_FOR_BUILD="$${CC_FOR_BUILD}" \
	GNATBIND="$$r/$(HOST_SUBDIR)/prev-gcc/gnatbind" \
	LDFLAGS="$(BOOT_LDFLAGS)" \
	"`echo 'ADAFLAGS=$(BOOT_ADAFLAGS)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`"

# Flags to pass down to makes which are built with the target environment.
# The double $ decreases the length of the command line; those variables
# are set in BASE_FLAGS_TO_PASS, and the sub-make will expand them.  The
# *_CFLAGS_FOR_TARGET variables are not passed down and most often empty,
# so we expand them here.
EXTRA_TARGET_FLAGS = \
	'AR=$$(AR_FOR_TARGET)' \
	'AS=$(COMPILER_AS_FOR_TARGET)' \
	'CC=$$(CC_FOR_TARGET)' \
	'CFLAGS=$$(CFLAGS_FOR_TARGET) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)' \
	'CXX=$$(CXX_FOR_TARGET)' \
	'CXXFLAGS=$$(CXXFLAGS_FOR_TARGET) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)' \
	'DLLTOOL=$$(DLLTOOL_FOR_TARGET)' \
	'LD=$(COMPILER_LD_FOR_TARGET)' \
	'LDFLAGS=$$(LDFLAGS_FOR_TARGET)' \
	'LIBCFLAGS=$$(LIBCFLAGS_FOR_TARGET) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)' \
	'LIBCXXFLAGS=$$(LIBCXXFLAGS_FOR_TARGET) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)' \
	'NM=$(COMPILER_NM_FOR_TARGET)' \
	'OBJDUMP=$$(OBJDUMP_FOR_TARGET)' \
	'RANLIB=$$(RANLIB_FOR_TARGET)' \
	'WINDRES=$$(WINDRES_FOR_TARGET)' \
	'WINDMC=$$(WINDMC_FOR_TARGET)'

TARGET_FLAGS_TO_PASS = $(BASE_FLAGS_TO_PASS) $(EXTRA_TARGET_FLAGS)

# Flags to pass down to gcc.  gcc builds a library, libgcc.a, so it
# unfortunately needs the native compiler and the target ar and
# ranlib.
# If any variables are added here, they must be added to do-*, below.
# The BUILD_* variables are a special case, which are used for the gcc
# cross-building scheme.
EXTRA_GCC_FLAGS = \
	"GCC_FOR_TARGET=$(GCC_FOR_TARGET)" \
	"`echo 'STMP_FIXPROTO=$(STMP_FIXPROTO)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`" \
	"`echo 'LIMITS_H_TEST=$(LIMITS_H_TEST)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`" \
	"`echo 'LIBGCC2_CFLAGS=$(LIBGCC2_CFLAGS)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`" \
	"`echo 'LIBGCC2_DEBUG_CFLAGS=$(LIBGCC2_DEBUG_CFLAGS)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`" \
	"`echo 'LIBGCC2_INCLUDES=$(LIBGCC2_INCLUDES)' | sed -e s'/[^=][^=]*=$$/XFOO=/'`"

GCC_FLAGS_TO_PASS = $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS)

.PHONY: configure-host
configure-host:  \
    maybe-configure-ash \
    maybe-configure-autoconf \
    maybe-configure-automake \
    maybe-configure-bash \
    maybe-configure-bfd \
    maybe-configure-opcodes \
    maybe-configure-binutils \
    maybe-configure-bison \
    maybe-configure-byacc \
    maybe-configure-bzip2 \
    maybe-configure-dejagnu \
    maybe-configure-diff \
    maybe-configure-dosutils \
    maybe-configure-etc \
    maybe-configure-fastjar \
    maybe-configure-fileutils \
    maybe-configure-findutils \
    maybe-configure-find \
    maybe-configure-fixincludes \
    maybe-configure-flex \
    maybe-configure-gas \
    maybe-configure-gcc \
    maybe-configure-gawk \
    maybe-configure-gettext \
    maybe-configure-gmp \
    maybe-configure-mpfr \
    maybe-configure-ppl \
    maybe-configure-cloog \
    maybe-configure-gnuserv \
    maybe-configure-gold \
    maybe-configure-gprof \
    maybe-configure-gzip \
    maybe-configure-hello \
    maybe-configure-indent \
    maybe-configure-intl \
    maybe-configure-tcl \
    maybe-configure-itcl \
    maybe-configure-ld \
    maybe-configure-libcpp \
    maybe-configure-libdecnumber \
    maybe-configure-libgui \
    maybe-configure-libiberty \
    maybe-configure-libiconv \
    maybe-configure-libtool \
    maybe-configure-m4 \
    maybe-configure-make \
    maybe-configure-mmalloc \
    maybe-configure-patch \
    maybe-configure-perl \
    maybe-configure-prms \
    maybe-configure-rcs \
    maybe-configure-readline \
    maybe-configure-release \
    maybe-configure-recode \
    maybe-configure-sed \
    maybe-configure-send-pr \
    maybe-configure-shellutils \
    maybe-configure-sid \
    maybe-configure-sim \
    maybe-configure-tar \
    maybe-configure-texinfo \
    maybe-configure-textutils \
    maybe-configure-time \
    maybe-configure-uudecode \
    maybe-configure-wdiff \
    maybe-configure-zip \
    maybe-configure-zlib \
    maybe-configure-gdb \
    maybe-configure-expect \
    maybe-configure-guile \
    maybe-configure-tk \
    maybe-configure-libtermcap \
    maybe-configure-utils \
    maybe-configure-gnattools
.PHONY: configure-target
configure-target:  \
    maybe-configure-target-libstdc++-v3 \
    maybe-configure-target-libmudflap \
    maybe-configure-target-libssp \
    maybe-configure-target-newlib \
    maybe-configure-target-libgcc \
    maybe-configure-target-libgfortran \
    maybe-configure-target-libobjc \
    maybe-configure-target-libtermcap \
    maybe-configure-target-winsup \
    maybe-configure-target-libgloss \
    maybe-configure-target-libiberty \
    maybe-configure-target-gperf \
    maybe-configure-target-examples \
    maybe-configure-target-libffi \
    maybe-configure-target-libjava \
    maybe-configure-target-zlib \
    maybe-configure-target-boehm-gc \
    maybe-configure-target-qthreads \
    maybe-configure-target-rda \
    maybe-configure-target-libada \
    maybe-configure-target-libgomp

# The target built for a native non-bootstrap build.
.PHONY: all
all:
	[ -f stage_final ] || echo stage3 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) `cat stage_final`-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if [ -f stage_last ]; then \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target; \
	else \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-host all-target; \
	fi

.PHONY: all-build

all-build: maybe-all-build-libiberty
all-build: maybe-all-build-bison
all-build: maybe-all-build-byacc
all-build: maybe-all-build-flex
all-build: maybe-all-build-m4
all-build: maybe-all-build-texinfo
all-build: maybe-all-build-fixincludes

.PHONY: all-host

all-host: maybe-all-ash
all-host: maybe-all-autoconf
all-host: maybe-all-automake
all-host: maybe-all-bash
all-host: maybe-all-bison
all-host: maybe-all-byacc
all-host: maybe-all-bzip2
all-host: maybe-all-dejagnu
all-host: maybe-all-diff
all-host: maybe-all-dosutils
all-host: maybe-all-etc
all-host: maybe-all-fastjar
all-host: maybe-all-fileutils
all-host: maybe-all-findutils
all-host: maybe-all-find
all-host: maybe-all-fixincludes
all-host: maybe-all-flex
all-host: maybe-all-gawk
all-host: maybe-all-gettext
all-host: maybe-all-gnuserv
all-host: maybe-all-gprof
all-host: maybe-all-gzip
all-host: maybe-all-hello
all-host: maybe-all-indent
all-host: maybe-all-tcl
all-host: maybe-all-itcl
all-host: maybe-all-libgui
all-host: maybe-all-libiconv
all-host: maybe-all-libtool
all-host: maybe-all-m4
all-host: maybe-all-make
all-host: maybe-all-mmalloc
all-host: maybe-all-patch
all-host: maybe-all-perl
all-host: maybe-all-prms
all-host: maybe-all-rcs
all-host: maybe-all-readline
all-host: maybe-all-release
all-host: maybe-all-recode
all-host: maybe-all-sed
all-host: maybe-all-send-pr
all-host: maybe-all-shellutils
all-host: maybe-all-sid
all-host: maybe-all-sim
all-host: maybe-all-tar
all-host: maybe-all-texinfo
all-host: maybe-all-textutils
all-host: maybe-all-time
all-host: maybe-all-uudecode
all-host: maybe-all-wdiff
all-host: maybe-all-zip
all-host: maybe-all-gdb
all-host: maybe-all-expect
all-host: maybe-all-guile
all-host: maybe-all-tk
all-host: maybe-all-libtermcap
all-host: maybe-all-utils
all-host: maybe-all-gnattools

.PHONY: all-target

all-target: maybe-all-target-libstdc++-v3
all-target: maybe-all-target-libmudflap
all-target: maybe-all-target-libssp
all-target: maybe-all-target-newlib
all-target: maybe-all-target-libgfortran
all-target: maybe-all-target-libobjc
all-target: maybe-all-target-libtermcap
all-target: maybe-all-target-winsup
all-target: maybe-all-target-libgloss
all-target: maybe-all-target-libiberty
all-target: maybe-all-target-gperf
all-target: maybe-all-target-examples
all-target: maybe-all-target-libffi
all-target: maybe-all-target-libjava
all-target: maybe-all-target-zlib
all-target: maybe-all-target-boehm-gc
all-target: maybe-all-target-qthreads
all-target: maybe-all-target-rda
all-target: maybe-all-target-libada
all-target: maybe-all-target-libgomp

# Do a target for all the subdirectories.  A ``make do-X'' will do a
# ``make X'' in all subdirectories (because, in general, there is a
# dependency (below) of X upon do-X, a ``make X'' will also do this,
# but it may do additional work as well).

.PHONY: do-info
do-info:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) info-host \
	  info-target


.PHONY: info-host

info-host: maybe-info-ash
info-host: maybe-info-autoconf
info-host: maybe-info-automake
info-host: maybe-info-bash
info-host: maybe-info-bfd
info-host: maybe-info-opcodes
info-host: maybe-info-binutils
info-host: maybe-info-bison
info-host: maybe-info-byacc
info-host: maybe-info-bzip2
info-host: maybe-info-dejagnu
info-host: maybe-info-diff
info-host: maybe-info-dosutils
info-host: maybe-info-etc
info-host: maybe-info-fastjar
info-host: maybe-info-fileutils
info-host: maybe-info-findutils
info-host: maybe-info-find
info-host: maybe-info-fixincludes
info-host: maybe-info-flex
info-host: maybe-info-gas
info-host: maybe-info-gcc
info-host: maybe-info-gawk
info-host: maybe-info-gettext
info-host: maybe-info-gmp
info-host: maybe-info-mpfr
info-host: maybe-info-ppl
info-host: maybe-info-cloog
info-host: maybe-info-gnuserv
info-host: maybe-info-gold
info-host: maybe-info-gprof
info-host: maybe-info-gzip
info-host: maybe-info-hello
info-host: maybe-info-indent
info-host: maybe-info-intl
info-host: maybe-info-tcl
info-host: maybe-info-itcl
info-host: maybe-info-ld
info-host: maybe-info-libcpp
info-host: maybe-info-libdecnumber
info-host: maybe-info-libgui
info-host: maybe-info-libiberty
info-host: maybe-info-libiconv
info-host: maybe-info-libtool
info-host: maybe-info-m4
info-host: maybe-info-make
info-host: maybe-info-mmalloc
info-host: maybe-info-patch
info-host: maybe-info-perl
info-host: maybe-info-prms
info-host: maybe-info-rcs
info-host: maybe-info-readline
info-host: maybe-info-release
info-host: maybe-info-recode
info-host: maybe-info-sed
info-host: maybe-info-send-pr
info-host: maybe-info-shellutils
info-host: maybe-info-sid
info-host: maybe-info-sim
info-host: maybe-info-tar
info-host: maybe-info-texinfo
info-host: maybe-info-textutils
info-host: maybe-info-time
info-host: maybe-info-uudecode
info-host: maybe-info-wdiff
info-host: maybe-info-zip
info-host: maybe-info-zlib
info-host: maybe-info-gdb
info-host: maybe-info-expect
info-host: maybe-info-guile
info-host: maybe-info-tk
info-host: maybe-info-libtermcap
info-host: maybe-info-utils
info-host: maybe-info-gnattools

.PHONY: info-target

info-target: maybe-info-target-libstdc++-v3
info-target: maybe-info-target-libmudflap
info-target: maybe-info-target-libssp
info-target: maybe-info-target-newlib
info-target: maybe-info-target-libgcc
info-target: maybe-info-target-libgfortran
info-target: maybe-info-target-libobjc
info-target: maybe-info-target-libtermcap
info-target: maybe-info-target-winsup
info-target: maybe-info-target-libgloss
info-target: maybe-info-target-libiberty
info-target: maybe-info-target-gperf
info-target: maybe-info-target-examples
info-target: maybe-info-target-libffi
info-target: maybe-info-target-libjava
info-target: maybe-info-target-zlib
info-target: maybe-info-target-boehm-gc
info-target: maybe-info-target-qthreads
info-target: maybe-info-target-rda
info-target: maybe-info-target-libada
info-target: maybe-info-target-libgomp

.PHONY: do-dvi
do-dvi:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) dvi-host \
	  dvi-target


.PHONY: dvi-host

dvi-host: maybe-dvi-ash
dvi-host: maybe-dvi-autoconf
dvi-host: maybe-dvi-automake
dvi-host: maybe-dvi-bash
dvi-host: maybe-dvi-bfd
dvi-host: maybe-dvi-opcodes
dvi-host: maybe-dvi-binutils
dvi-host: maybe-dvi-bison
dvi-host: maybe-dvi-byacc
dvi-host: maybe-dvi-bzip2
dvi-host: maybe-dvi-dejagnu
dvi-host: maybe-dvi-diff
dvi-host: maybe-dvi-dosutils
dvi-host: maybe-dvi-etc
dvi-host: maybe-dvi-fastjar
dvi-host: maybe-dvi-fileutils
dvi-host: maybe-dvi-findutils
dvi-host: maybe-dvi-find
dvi-host: maybe-dvi-fixincludes
dvi-host: maybe-dvi-flex
dvi-host: maybe-dvi-gas
dvi-host: maybe-dvi-gcc
dvi-host: maybe-dvi-gawk
dvi-host: maybe-dvi-gettext
dvi-host: maybe-dvi-gmp
dvi-host: maybe-dvi-mpfr
dvi-host: maybe-dvi-ppl
dvi-host: maybe-dvi-cloog
dvi-host: maybe-dvi-gnuserv
dvi-host: maybe-dvi-gold
dvi-host: maybe-dvi-gprof
dvi-host: maybe-dvi-gzip
dvi-host: maybe-dvi-hello
dvi-host: maybe-dvi-indent
dvi-host: maybe-dvi-intl
dvi-host: maybe-dvi-tcl
dvi-host: maybe-dvi-itcl
dvi-host: maybe-dvi-ld
dvi-host: maybe-dvi-libcpp
dvi-host: maybe-dvi-libdecnumber
dvi-host: maybe-dvi-libgui
dvi-host: maybe-dvi-libiberty
dvi-host: maybe-dvi-libiconv
dvi-host: maybe-dvi-libtool
dvi-host: maybe-dvi-m4
dvi-host: maybe-dvi-make
dvi-host: maybe-dvi-mmalloc
dvi-host: maybe-dvi-patch
dvi-host: maybe-dvi-perl
dvi-host: maybe-dvi-prms
dvi-host: maybe-dvi-rcs
dvi-host: maybe-dvi-readline
dvi-host: maybe-dvi-release
dvi-host: maybe-dvi-recode
dvi-host: maybe-dvi-sed
dvi-host: maybe-dvi-send-pr
dvi-host: maybe-dvi-shellutils
dvi-host: maybe-dvi-sid
dvi-host: maybe-dvi-sim
dvi-host: maybe-dvi-tar
dvi-host: maybe-dvi-texinfo
dvi-host: maybe-dvi-textutils
dvi-host: maybe-dvi-time
dvi-host: maybe-dvi-uudecode
dvi-host: maybe-dvi-wdiff
dvi-host: maybe-dvi-zip
dvi-host: maybe-dvi-zlib
dvi-host: maybe-dvi-gdb
dvi-host: maybe-dvi-expect
dvi-host: maybe-dvi-guile
dvi-host: maybe-dvi-tk
dvi-host: maybe-dvi-libtermcap
dvi-host: maybe-dvi-utils
dvi-host: maybe-dvi-gnattools

.PHONY: dvi-target

dvi-target: maybe-dvi-target-libstdc++-v3
dvi-target: maybe-dvi-target-libmudflap
dvi-target: maybe-dvi-target-libssp
dvi-target: maybe-dvi-target-newlib
dvi-target: maybe-dvi-target-libgcc
dvi-target: maybe-dvi-target-libgfortran
dvi-target: maybe-dvi-target-libobjc
dvi-target: maybe-dvi-target-libtermcap
dvi-target: maybe-dvi-target-winsup
dvi-target: maybe-dvi-target-libgloss
dvi-target: maybe-dvi-target-libiberty
dvi-target: maybe-dvi-target-gperf
dvi-target: maybe-dvi-target-examples
dvi-target: maybe-dvi-target-libffi
dvi-target: maybe-dvi-target-libjava
dvi-target: maybe-dvi-target-zlib
dvi-target: maybe-dvi-target-boehm-gc
dvi-target: maybe-dvi-target-qthreads
dvi-target: maybe-dvi-target-rda
dvi-target: maybe-dvi-target-libada
dvi-target: maybe-dvi-target-libgomp

.PHONY: do-pdf
do-pdf:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) pdf-host \
	  pdf-target


.PHONY: pdf-host

pdf-host: maybe-pdf-ash
pdf-host: maybe-pdf-autoconf
pdf-host: maybe-pdf-automake
pdf-host: maybe-pdf-bash
pdf-host: maybe-pdf-bfd
pdf-host: maybe-pdf-opcodes
pdf-host: maybe-pdf-binutils
pdf-host: maybe-pdf-bison
pdf-host: maybe-pdf-byacc
pdf-host: maybe-pdf-bzip2
pdf-host: maybe-pdf-dejagnu
pdf-host: maybe-pdf-diff
pdf-host: maybe-pdf-dosutils
pdf-host: maybe-pdf-etc
pdf-host: maybe-pdf-fastjar
pdf-host: maybe-pdf-fileutils
pdf-host: maybe-pdf-findutils
pdf-host: maybe-pdf-find
pdf-host: maybe-pdf-fixincludes
pdf-host: maybe-pdf-flex
pdf-host: maybe-pdf-gas
pdf-host: maybe-pdf-gcc
pdf-host: maybe-pdf-gawk
pdf-host: maybe-pdf-gettext
pdf-host: maybe-pdf-gmp
pdf-host: maybe-pdf-mpfr
pdf-host: maybe-pdf-ppl
pdf-host: maybe-pdf-cloog
pdf-host: maybe-pdf-gnuserv
pdf-host: maybe-pdf-gold
pdf-host: maybe-pdf-gprof
pdf-host: maybe-pdf-gzip
pdf-host: maybe-pdf-hello
pdf-host: maybe-pdf-indent
pdf-host: maybe-pdf-intl
pdf-host: maybe-pdf-tcl
pdf-host: maybe-pdf-itcl
pdf-host: maybe-pdf-ld
pdf-host: maybe-pdf-libcpp
pdf-host: maybe-pdf-libdecnumber
pdf-host: maybe-pdf-libgui
pdf-host: maybe-pdf-libiberty
pdf-host: maybe-pdf-libiconv
pdf-host: maybe-pdf-libtool
pdf-host: maybe-pdf-m4
pdf-host: maybe-pdf-make
pdf-host: maybe-pdf-mmalloc
pdf-host: maybe-pdf-patch
pdf-host: maybe-pdf-perl
pdf-host: maybe-pdf-prms
pdf-host: maybe-pdf-rcs
pdf-host: maybe-pdf-readline
pdf-host: maybe-pdf-release
pdf-host: maybe-pdf-recode
pdf-host: maybe-pdf-sed
pdf-host: maybe-pdf-send-pr
pdf-host: maybe-pdf-shellutils
pdf-host: maybe-pdf-sid
pdf-host: maybe-pdf-sim
pdf-host: maybe-pdf-tar
pdf-host: maybe-pdf-texinfo
pdf-host: maybe-pdf-textutils
pdf-host: maybe-pdf-time
pdf-host: maybe-pdf-uudecode
pdf-host: maybe-pdf-wdiff
pdf-host: maybe-pdf-zip
pdf-host: maybe-pdf-zlib
pdf-host: maybe-pdf-gdb
pdf-host: maybe-pdf-expect
pdf-host: maybe-pdf-guile
pdf-host: maybe-pdf-tk
pdf-host: maybe-pdf-libtermcap
pdf-host: maybe-pdf-utils
pdf-host: maybe-pdf-gnattools

.PHONY: pdf-target

pdf-target: maybe-pdf-target-libstdc++-v3
pdf-target: maybe-pdf-target-libmudflap
pdf-target: maybe-pdf-target-libssp
pdf-target: maybe-pdf-target-newlib
pdf-target: maybe-pdf-target-libgcc
pdf-target: maybe-pdf-target-libgfortran
pdf-target: maybe-pdf-target-libobjc
pdf-target: maybe-pdf-target-libtermcap
pdf-target: maybe-pdf-target-winsup
pdf-target: maybe-pdf-target-libgloss
pdf-target: maybe-pdf-target-libiberty
pdf-target: maybe-pdf-target-gperf
pdf-target: maybe-pdf-target-examples
pdf-target: maybe-pdf-target-libffi
pdf-target: maybe-pdf-target-libjava
pdf-target: maybe-pdf-target-zlib
pdf-target: maybe-pdf-target-boehm-gc
pdf-target: maybe-pdf-target-qthreads
pdf-target: maybe-pdf-target-rda
pdf-target: maybe-pdf-target-libada
pdf-target: maybe-pdf-target-libgomp

.PHONY: do-html
do-html:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) html-host \
	  html-target


.PHONY: html-host

html-host: maybe-html-ash
html-host: maybe-html-autoconf
html-host: maybe-html-automake
html-host: maybe-html-bash
html-host: maybe-html-bfd
html-host: maybe-html-opcodes
html-host: maybe-html-binutils
html-host: maybe-html-bison
html-host: maybe-html-byacc
html-host: maybe-html-bzip2
html-host: maybe-html-dejagnu
html-host: maybe-html-diff
html-host: maybe-html-dosutils
html-host: maybe-html-etc
html-host: maybe-html-fastjar
html-host: maybe-html-fileutils
html-host: maybe-html-findutils
html-host: maybe-html-find
html-host: maybe-html-fixincludes
html-host: maybe-html-flex
html-host: maybe-html-gas
html-host: maybe-html-gcc
html-host: maybe-html-gawk
html-host: maybe-html-gettext
html-host: maybe-html-gmp
html-host: maybe-html-mpfr
html-host: maybe-html-ppl
html-host: maybe-html-cloog
html-host: maybe-html-gnuserv
html-host: maybe-html-gold
html-host: maybe-html-gprof
html-host: maybe-html-gzip
html-host: maybe-html-hello
html-host: maybe-html-indent
html-host: maybe-html-intl
html-host: maybe-html-tcl
html-host: maybe-html-itcl
html-host: maybe-html-ld
html-host: maybe-html-libcpp
html-host: maybe-html-libdecnumber
html-host: maybe-html-libgui
html-host: maybe-html-libiberty
html-host: maybe-html-libiconv
html-host: maybe-html-libtool
html-host: maybe-html-m4
html-host: maybe-html-make
html-host: maybe-html-mmalloc
html-host: maybe-html-patch
html-host: maybe-html-perl
html-host: maybe-html-prms
html-host: maybe-html-rcs
html-host: maybe-html-readline
html-host: maybe-html-release
html-host: maybe-html-recode
html-host: maybe-html-sed
html-host: maybe-html-send-pr
html-host: maybe-html-shellutils
html-host: maybe-html-sid
html-host: maybe-html-sim
html-host: maybe-html-tar
html-host: maybe-html-texinfo
html-host: maybe-html-textutils
html-host: maybe-html-time
html-host: maybe-html-uudecode
html-host: maybe-html-wdiff
html-host: maybe-html-zip
html-host: maybe-html-zlib
html-host: maybe-html-gdb
html-host: maybe-html-expect
html-host: maybe-html-guile
html-host: maybe-html-tk
html-host: maybe-html-libtermcap
html-host: maybe-html-utils
html-host: maybe-html-gnattools

.PHONY: html-target

html-target: maybe-html-target-libstdc++-v3
html-target: maybe-html-target-libmudflap
html-target: maybe-html-target-libssp
html-target: maybe-html-target-newlib
html-target: maybe-html-target-libgcc
html-target: maybe-html-target-libgfortran
html-target: maybe-html-target-libobjc
html-target: maybe-html-target-libtermcap
html-target: maybe-html-target-winsup
html-target: maybe-html-target-libgloss
html-target: maybe-html-target-libiberty
html-target: maybe-html-target-gperf
html-target: maybe-html-target-examples
html-target: maybe-html-target-libffi
html-target: maybe-html-target-libjava
html-target: maybe-html-target-zlib
html-target: maybe-html-target-boehm-gc
html-target: maybe-html-target-qthreads
html-target: maybe-html-target-rda
html-target: maybe-html-target-libada
html-target: maybe-html-target-libgomp

.PHONY: do-TAGS
do-TAGS:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) TAGS-host \
	  TAGS-target


.PHONY: TAGS-host

TAGS-host: maybe-TAGS-ash
TAGS-host: maybe-TAGS-autoconf
TAGS-host: maybe-TAGS-automake
TAGS-host: maybe-TAGS-bash
TAGS-host: maybe-TAGS-bfd
TAGS-host: maybe-TAGS-opcodes
TAGS-host: maybe-TAGS-binutils
TAGS-host: maybe-TAGS-bison
TAGS-host: maybe-TAGS-byacc
TAGS-host: maybe-TAGS-bzip2
TAGS-host: maybe-TAGS-dejagnu
TAGS-host: maybe-TAGS-diff
TAGS-host: maybe-TAGS-dosutils
TAGS-host: maybe-TAGS-etc
TAGS-host: maybe-TAGS-fastjar
TAGS-host: maybe-TAGS-fileutils
TAGS-host: maybe-TAGS-findutils
TAGS-host: maybe-TAGS-find
TAGS-host: maybe-TAGS-fixincludes
TAGS-host: maybe-TAGS-flex
TAGS-host: maybe-TAGS-gas
TAGS-host: maybe-TAGS-gcc
TAGS-host: maybe-TAGS-gawk
TAGS-host: maybe-TAGS-gettext
TAGS-host: maybe-TAGS-gmp
TAGS-host: maybe-TAGS-mpfr
TAGS-host: maybe-TAGS-ppl
TAGS-host: maybe-TAGS-cloog
TAGS-host: maybe-TAGS-gnuserv
TAGS-host: maybe-TAGS-gold
TAGS-host: maybe-TAGS-gprof
TAGS-host: maybe-TAGS-gzip
TAGS-host: maybe-TAGS-hello
TAGS-host: maybe-TAGS-indent
TAGS-host: maybe-TAGS-intl
TAGS-host: maybe-TAGS-tcl
TAGS-host: maybe-TAGS-itcl
TAGS-host: maybe-TAGS-ld
TAGS-host: maybe-TAGS-libcpp
TAGS-host: maybe-TAGS-libdecnumber
TAGS-host: maybe-TAGS-libgui
TAGS-host: maybe-TAGS-libiberty
TAGS-host: maybe-TAGS-libiconv
TAGS-host: maybe-TAGS-libtool
TAGS-host: maybe-TAGS-m4
TAGS-host: maybe-TAGS-make
TAGS-host: maybe-TAGS-mmalloc
TAGS-host: maybe-TAGS-patch
TAGS-host: maybe-TAGS-perl
TAGS-host: maybe-TAGS-prms
TAGS-host: maybe-TAGS-rcs
TAGS-host: maybe-TAGS-readline
TAGS-host: maybe-TAGS-release
TAGS-host: maybe-TAGS-recode
TAGS-host: maybe-TAGS-sed
TAGS-host: maybe-TAGS-send-pr
TAGS-host: maybe-TAGS-shellutils
TAGS-host: maybe-TAGS-sid
TAGS-host: maybe-TAGS-sim
TAGS-host: maybe-TAGS-tar
TAGS-host: maybe-TAGS-texinfo
TAGS-host: maybe-TAGS-textutils
TAGS-host: maybe-TAGS-time
TAGS-host: maybe-TAGS-uudecode
TAGS-host: maybe-TAGS-wdiff
TAGS-host: maybe-TAGS-zip
TAGS-host: maybe-TAGS-zlib
TAGS-host: maybe-TAGS-gdb
TAGS-host: maybe-TAGS-expect
TAGS-host: maybe-TAGS-guile
TAGS-host: maybe-TAGS-tk
TAGS-host: maybe-TAGS-libtermcap
TAGS-host: maybe-TAGS-utils
TAGS-host: maybe-TAGS-gnattools

.PHONY: TAGS-target

TAGS-target: maybe-TAGS-target-libstdc++-v3
TAGS-target: maybe-TAGS-target-libmudflap
TAGS-target: maybe-TAGS-target-libssp
TAGS-target: maybe-TAGS-target-newlib
TAGS-target: maybe-TAGS-target-libgcc
TAGS-target: maybe-TAGS-target-libgfortran
TAGS-target: maybe-TAGS-target-libobjc
TAGS-target: maybe-TAGS-target-libtermcap
TAGS-target: maybe-TAGS-target-winsup
TAGS-target: maybe-TAGS-target-libgloss
TAGS-target: maybe-TAGS-target-libiberty
TAGS-target: maybe-TAGS-target-gperf
TAGS-target: maybe-TAGS-target-examples
TAGS-target: maybe-TAGS-target-libffi
TAGS-target: maybe-TAGS-target-libjava
TAGS-target: maybe-TAGS-target-zlib
TAGS-target: maybe-TAGS-target-boehm-gc
TAGS-target: maybe-TAGS-target-qthreads
TAGS-target: maybe-TAGS-target-rda
TAGS-target: maybe-TAGS-target-libada
TAGS-target: maybe-TAGS-target-libgomp

.PHONY: do-install-info
do-install-info:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) install-info-host \
	  install-info-target


.PHONY: install-info-host

install-info-host: maybe-install-info-ash
install-info-host: maybe-install-info-autoconf
install-info-host: maybe-install-info-automake
install-info-host: maybe-install-info-bash
install-info-host: maybe-install-info-bfd
install-info-host: maybe-install-info-opcodes
install-info-host: maybe-install-info-binutils
install-info-host: maybe-install-info-bison
install-info-host: maybe-install-info-byacc
install-info-host: maybe-install-info-bzip2
install-info-host: maybe-install-info-dejagnu
install-info-host: maybe-install-info-diff
install-info-host: maybe-install-info-dosutils
install-info-host: maybe-install-info-etc
install-info-host: maybe-install-info-fastjar
install-info-host: maybe-install-info-fileutils
install-info-host: maybe-install-info-findutils
install-info-host: maybe-install-info-find
install-info-host: maybe-install-info-fixincludes
install-info-host: maybe-install-info-flex
install-info-host: maybe-install-info-gas
install-info-host: maybe-install-info-gcc
install-info-host: maybe-install-info-gawk
install-info-host: maybe-install-info-gettext
install-info-host: maybe-install-info-gmp
install-info-host: maybe-install-info-mpfr
install-info-host: maybe-install-info-ppl
install-info-host: maybe-install-info-cloog
install-info-host: maybe-install-info-gnuserv
install-info-host: maybe-install-info-gold
install-info-host: maybe-install-info-gprof
install-info-host: maybe-install-info-gzip
install-info-host: maybe-install-info-hello
install-info-host: maybe-install-info-indent
install-info-host: maybe-install-info-intl
install-info-host: maybe-install-info-tcl
install-info-host: maybe-install-info-itcl
install-info-host: maybe-install-info-ld
install-info-host: maybe-install-info-libcpp
install-info-host: maybe-install-info-libdecnumber
install-info-host: maybe-install-info-libgui
install-info-host: maybe-install-info-libiberty
install-info-host: maybe-install-info-libiconv
install-info-host: maybe-install-info-libtool
install-info-host: maybe-install-info-m4
install-info-host: maybe-install-info-make
install-info-host: maybe-install-info-mmalloc
install-info-host: maybe-install-info-patch
install-info-host: maybe-install-info-perl
install-info-host: maybe-install-info-prms
install-info-host: maybe-install-info-rcs
install-info-host: maybe-install-info-readline
install-info-host: maybe-install-info-release
install-info-host: maybe-install-info-recode
install-info-host: maybe-install-info-sed
install-info-host: maybe-install-info-send-pr
install-info-host: maybe-install-info-shellutils
install-info-host: maybe-install-info-sid
install-info-host: maybe-install-info-sim
install-info-host: maybe-install-info-tar
install-info-host: maybe-install-info-texinfo
install-info-host: maybe-install-info-textutils
install-info-host: maybe-install-info-time
install-info-host: maybe-install-info-uudecode
install-info-host: maybe-install-info-wdiff
install-info-host: maybe-install-info-zip
install-info-host: maybe-install-info-zlib
install-info-host: maybe-install-info-gdb
install-info-host: maybe-install-info-expect
install-info-host: maybe-install-info-guile
install-info-host: maybe-install-info-tk
install-info-host: maybe-install-info-libtermcap
install-info-host: maybe-install-info-utils
install-info-host: maybe-install-info-gnattools

.PHONY: install-info-target

install-info-target: maybe-install-info-target-libstdc++-v3
install-info-target: maybe-install-info-target-libmudflap
install-info-target: maybe-install-info-target-libssp
install-info-target: maybe-install-info-target-newlib
install-info-target: maybe-install-info-target-libgcc
install-info-target: maybe-install-info-target-libgfortran
install-info-target: maybe-install-info-target-libobjc
install-info-target: maybe-install-info-target-libtermcap
install-info-target: maybe-install-info-target-winsup
install-info-target: maybe-install-info-target-libgloss
install-info-target: maybe-install-info-target-libiberty
install-info-target: maybe-install-info-target-gperf
install-info-target: maybe-install-info-target-examples
install-info-target: maybe-install-info-target-libffi
install-info-target: maybe-install-info-target-libjava
install-info-target: maybe-install-info-target-zlib
install-info-target: maybe-install-info-target-boehm-gc
install-info-target: maybe-install-info-target-qthreads
install-info-target: maybe-install-info-target-rda
install-info-target: maybe-install-info-target-libada
install-info-target: maybe-install-info-target-libgomp

.PHONY: do-install-pdf
do-install-pdf:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) install-pdf-host \
	  install-pdf-target


.PHONY: install-pdf-host

install-pdf-host: maybe-install-pdf-ash
install-pdf-host: maybe-install-pdf-autoconf
install-pdf-host: maybe-install-pdf-automake
install-pdf-host: maybe-install-pdf-bash
install-pdf-host: maybe-install-pdf-bfd
install-pdf-host: maybe-install-pdf-opcodes
install-pdf-host: maybe-install-pdf-binutils
install-pdf-host: maybe-install-pdf-bison
install-pdf-host: maybe-install-pdf-byacc
install-pdf-host: maybe-install-pdf-bzip2
install-pdf-host: maybe-install-pdf-dejagnu
install-pdf-host: maybe-install-pdf-diff
install-pdf-host: maybe-install-pdf-dosutils
install-pdf-host: maybe-install-pdf-etc
install-pdf-host: maybe-install-pdf-fastjar
install-pdf-host: maybe-install-pdf-fileutils
install-pdf-host: maybe-install-pdf-findutils
install-pdf-host: maybe-install-pdf-find
install-pdf-host: maybe-install-pdf-fixincludes
install-pdf-host: maybe-install-pdf-flex
install-pdf-host: maybe-install-pdf-gas
install-pdf-host: maybe-install-pdf-gcc
install-pdf-host: maybe-install-pdf-gawk
install-pdf-host: maybe-install-pdf-gettext
install-pdf-host: maybe-install-pdf-gmp
install-pdf-host: maybe-install-pdf-mpfr
install-pdf-host: maybe-install-pdf-ppl
install-pdf-host: maybe-install-pdf-cloog
install-pdf-host: maybe-install-pdf-gnuserv
install-pdf-host: maybe-install-pdf-gold
install-pdf-host: maybe-install-pdf-gprof
install-pdf-host: maybe-install-pdf-gzip
install-pdf-host: maybe-install-pdf-hello
install-pdf-host: maybe-install-pdf-indent
install-pdf-host: maybe-install-pdf-intl
install-pdf-host: maybe-install-pdf-tcl
install-pdf-host: maybe-install-pdf-itcl
install-pdf-host: maybe-install-pdf-ld
install-pdf-host: maybe-install-pdf-libcpp
install-pdf-host: maybe-install-pdf-libdecnumber
install-pdf-host: maybe-install-pdf-libgui
install-pdf-host: maybe-install-pdf-libiberty
install-pdf-host: maybe-install-pdf-libiconv
install-pdf-host: maybe-install-pdf-libtool
install-pdf-host: maybe-install-pdf-m4
install-pdf-host: maybe-install-pdf-make
install-pdf-host: maybe-install-pdf-mmalloc
install-pdf-host: maybe-install-pdf-patch
install-pdf-host: maybe-install-pdf-perl
install-pdf-host: maybe-install-pdf-prms
install-pdf-host: maybe-install-pdf-rcs
install-pdf-host: maybe-install-pdf-readline
install-pdf-host: maybe-install-pdf-release
install-pdf-host: maybe-install-pdf-recode
install-pdf-host: maybe-install-pdf-sed
install-pdf-host: maybe-install-pdf-send-pr
install-pdf-host: maybe-install-pdf-shellutils
install-pdf-host: maybe-install-pdf-sid
install-pdf-host: maybe-install-pdf-sim
install-pdf-host: maybe-install-pdf-tar
install-pdf-host: maybe-install-pdf-texinfo
install-pdf-host: maybe-install-pdf-textutils
install-pdf-host: maybe-install-pdf-time
install-pdf-host: maybe-install-pdf-uudecode
install-pdf-host: maybe-install-pdf-wdiff
install-pdf-host: maybe-install-pdf-zip
install-pdf-host: maybe-install-pdf-zlib
install-pdf-host: maybe-install-pdf-gdb
install-pdf-host: maybe-install-pdf-expect
install-pdf-host: maybe-install-pdf-guile
install-pdf-host: maybe-install-pdf-tk
install-pdf-host: maybe-install-pdf-libtermcap
install-pdf-host: maybe-install-pdf-utils
install-pdf-host: maybe-install-pdf-gnattools

.PHONY: install-pdf-target

install-pdf-target: maybe-install-pdf-target-libstdc++-v3
install-pdf-target: maybe-install-pdf-target-libmudflap
install-pdf-target: maybe-install-pdf-target-libssp
install-pdf-target: maybe-install-pdf-target-newlib
install-pdf-target: maybe-install-pdf-target-libgcc
install-pdf-target: maybe-install-pdf-target-libgfortran
install-pdf-target: maybe-install-pdf-target-libobjc
install-pdf-target: maybe-install-pdf-target-libtermcap
install-pdf-target: maybe-install-pdf-target-winsup
install-pdf-target: maybe-install-pdf-target-libgloss
install-pdf-target: maybe-install-pdf-target-libiberty
install-pdf-target: maybe-install-pdf-target-gperf
install-pdf-target: maybe-install-pdf-target-examples
install-pdf-target: maybe-install-pdf-target-libffi
install-pdf-target: maybe-install-pdf-target-libjava
install-pdf-target: maybe-install-pdf-target-zlib
install-pdf-target: maybe-install-pdf-target-boehm-gc
install-pdf-target: maybe-install-pdf-target-qthreads
install-pdf-target: maybe-install-pdf-target-rda
install-pdf-target: maybe-install-pdf-target-libada
install-pdf-target: maybe-install-pdf-target-libgomp

.PHONY: do-install-html
do-install-html:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) install-html-host \
	  install-html-target


.PHONY: install-html-host

install-html-host: maybe-install-html-ash
install-html-host: maybe-install-html-autoconf
install-html-host: maybe-install-html-automake
install-html-host: maybe-install-html-bash
install-html-host: maybe-install-html-bfd
install-html-host: maybe-install-html-opcodes
install-html-host: maybe-install-html-binutils
install-html-host: maybe-install-html-bison
install-html-host: maybe-install-html-byacc
install-html-host: maybe-install-html-bzip2
install-html-host: maybe-install-html-dejagnu
install-html-host: maybe-install-html-diff
install-html-host: maybe-install-html-dosutils
install-html-host: maybe-install-html-etc
install-html-host: maybe-install-html-fastjar
install-html-host: maybe-install-html-fileutils
install-html-host: maybe-install-html-findutils
install-html-host: maybe-install-html-find
install-html-host: maybe-install-html-fixincludes
install-html-host: maybe-install-html-flex
install-html-host: maybe-install-html-gas
install-html-host: maybe-install-html-gcc
install-html-host: maybe-install-html-gawk
install-html-host: maybe-install-html-gettext
install-html-host: maybe-install-html-gmp
install-html-host: maybe-install-html-mpfr
install-html-host: maybe-install-html-ppl
install-html-host: maybe-install-html-cloog
install-html-host: maybe-install-html-gnuserv
install-html-host: maybe-install-html-gold
install-html-host: maybe-install-html-gprof
install-html-host: maybe-install-html-gzip
install-html-host: maybe-install-html-hello
install-html-host: maybe-install-html-indent
install-html-host: maybe-install-html-intl
install-html-host: maybe-install-html-tcl
install-html-host: maybe-install-html-itcl
install-html-host: maybe-install-html-ld
install-html-host: maybe-install-html-libcpp
install-html-host: maybe-install-html-libdecnumber
install-html-host: maybe-install-html-libgui
install-html-host: maybe-install-html-libiberty
install-html-host: maybe-install-html-libiconv
install-html-host: maybe-install-html-libtool
install-html-host: maybe-install-html-m4
install-html-host: maybe-install-html-make
install-html-host: maybe-install-html-mmalloc
install-html-host: maybe-install-html-patch
install-html-host: maybe-install-html-perl
install-html-host: maybe-install-html-prms
install-html-host: maybe-install-html-rcs
install-html-host: maybe-install-html-readline
install-html-host: maybe-install-html-release
install-html-host: maybe-install-html-recode
install-html-host: maybe-install-html-sed
install-html-host: maybe-install-html-send-pr
install-html-host: maybe-install-html-shellutils
install-html-host: maybe-install-html-sid
install-html-host: maybe-install-html-sim
install-html-host: maybe-install-html-tar
install-html-host: maybe-install-html-texinfo
install-html-host: maybe-install-html-textutils
install-html-host: maybe-install-html-time
install-html-host: maybe-install-html-uudecode
install-html-host: maybe-install-html-wdiff
install-html-host: maybe-install-html-zip
install-html-host: maybe-install-html-zlib
install-html-host: maybe-install-html-gdb
install-html-host: maybe-install-html-expect
install-html-host: maybe-install-html-guile
install-html-host: maybe-install-html-tk
install-html-host: maybe-install-html-libtermcap
install-html-host: maybe-install-html-utils
install-html-host: maybe-install-html-gnattools

.PHONY: install-html-target

install-html-target: maybe-install-html-target-libstdc++-v3
install-html-target: maybe-install-html-target-libmudflap
install-html-target: maybe-install-html-target-libssp
install-html-target: maybe-install-html-target-newlib
install-html-target: maybe-install-html-target-libgcc
install-html-target: maybe-install-html-target-libgfortran
install-html-target: maybe-install-html-target-libobjc
install-html-target: maybe-install-html-target-libtermcap
install-html-target: maybe-install-html-target-winsup
install-html-target: maybe-install-html-target-libgloss
install-html-target: maybe-install-html-target-libiberty
install-html-target: maybe-install-html-target-gperf
install-html-target: maybe-install-html-target-examples
install-html-target: maybe-install-html-target-libffi
install-html-target: maybe-install-html-target-libjava
install-html-target: maybe-install-html-target-zlib
install-html-target: maybe-install-html-target-boehm-gc
install-html-target: maybe-install-html-target-qthreads
install-html-target: maybe-install-html-target-rda
install-html-target: maybe-install-html-target-libada
install-html-target: maybe-install-html-target-libgomp

.PHONY: do-installcheck
do-installcheck:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) installcheck-host \
	  installcheck-target


.PHONY: installcheck-host

installcheck-host: maybe-installcheck-ash
installcheck-host: maybe-installcheck-autoconf
installcheck-host: maybe-installcheck-automake
installcheck-host: maybe-installcheck-bash
installcheck-host: maybe-installcheck-bfd
installcheck-host: maybe-installcheck-opcodes
installcheck-host: maybe-installcheck-binutils
installcheck-host: maybe-installcheck-bison
installcheck-host: maybe-installcheck-byacc
installcheck-host: maybe-installcheck-bzip2
installcheck-host: maybe-installcheck-dejagnu
installcheck-host: maybe-installcheck-diff
installcheck-host: maybe-installcheck-dosutils
installcheck-host: maybe-installcheck-etc
installcheck-host: maybe-installcheck-fastjar
installcheck-host: maybe-installcheck-fileutils
installcheck-host: maybe-installcheck-findutils
installcheck-host: maybe-installcheck-find
installcheck-host: maybe-installcheck-fixincludes
installcheck-host: maybe-installcheck-flex
installcheck-host: maybe-installcheck-gas
installcheck-host: maybe-installcheck-gcc
installcheck-host: maybe-installcheck-gawk
installcheck-host: maybe-installcheck-gettext
installcheck-host: maybe-installcheck-gmp
installcheck-host: maybe-installcheck-mpfr
installcheck-host: maybe-installcheck-ppl
installcheck-host: maybe-installcheck-cloog
installcheck-host: maybe-installcheck-gnuserv
installcheck-host: maybe-installcheck-gold
installcheck-host: maybe-installcheck-gprof
installcheck-host: maybe-installcheck-gzip
installcheck-host: maybe-installcheck-hello
installcheck-host: maybe-installcheck-indent
installcheck-host: maybe-installcheck-intl
installcheck-host: maybe-installcheck-tcl
installcheck-host: maybe-installcheck-itcl
installcheck-host: maybe-installcheck-ld
installcheck-host: maybe-installcheck-libcpp
installcheck-host: maybe-installcheck-libdecnumber
installcheck-host: maybe-installcheck-libgui
installcheck-host: maybe-installcheck-libiberty
installcheck-host: maybe-installcheck-libiconv
installcheck-host: maybe-installcheck-libtool
installcheck-host: maybe-installcheck-m4
installcheck-host: maybe-installcheck-make
installcheck-host: maybe-installcheck-mmalloc
installcheck-host: maybe-installcheck-patch
installcheck-host: maybe-installcheck-perl
installcheck-host: maybe-installcheck-prms
installcheck-host: maybe-installcheck-rcs
installcheck-host: maybe-installcheck-readline
installcheck-host: maybe-installcheck-release
installcheck-host: maybe-installcheck-recode
installcheck-host: maybe-installcheck-sed
installcheck-host: maybe-installcheck-send-pr
installcheck-host: maybe-installcheck-shellutils
installcheck-host: maybe-installcheck-sid
installcheck-host: maybe-installcheck-sim
installcheck-host: maybe-installcheck-tar
installcheck-host: maybe-installcheck-texinfo
installcheck-host: maybe-installcheck-textutils
installcheck-host: maybe-installcheck-time
installcheck-host: maybe-installcheck-uudecode
installcheck-host: maybe-installcheck-wdiff
installcheck-host: maybe-installcheck-zip
installcheck-host: maybe-installcheck-zlib
installcheck-host: maybe-installcheck-gdb
installcheck-host: maybe-installcheck-expect
installcheck-host: maybe-installcheck-guile
installcheck-host: maybe-installcheck-tk
installcheck-host: maybe-installcheck-libtermcap
installcheck-host: maybe-installcheck-utils
installcheck-host: maybe-installcheck-gnattools

.PHONY: installcheck-target

installcheck-target: maybe-installcheck-target-libstdc++-v3
installcheck-target: maybe-installcheck-target-libmudflap
installcheck-target: maybe-installcheck-target-libssp
installcheck-target: maybe-installcheck-target-newlib
installcheck-target: maybe-installcheck-target-libgcc
installcheck-target: maybe-installcheck-target-libgfortran
installcheck-target: maybe-installcheck-target-libobjc
installcheck-target: maybe-installcheck-target-libtermcap
installcheck-target: maybe-installcheck-target-winsup
installcheck-target: maybe-installcheck-target-libgloss
installcheck-target: maybe-installcheck-target-libiberty
installcheck-target: maybe-installcheck-target-gperf
installcheck-target: maybe-installcheck-target-examples
installcheck-target: maybe-installcheck-target-libffi
installcheck-target: maybe-installcheck-target-libjava
installcheck-target: maybe-installcheck-target-zlib
installcheck-target: maybe-installcheck-target-boehm-gc
installcheck-target: maybe-installcheck-target-qthreads
installcheck-target: maybe-installcheck-target-rda
installcheck-target: maybe-installcheck-target-libada
installcheck-target: maybe-installcheck-target-libgomp

.PHONY: do-mostlyclean
do-mostlyclean:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) mostlyclean-host \
	  mostlyclean-target


.PHONY: mostlyclean-host

mostlyclean-host: maybe-mostlyclean-ash
mostlyclean-host: maybe-mostlyclean-autoconf
mostlyclean-host: maybe-mostlyclean-automake
mostlyclean-host: maybe-mostlyclean-bash
mostlyclean-host: maybe-mostlyclean-bfd
mostlyclean-host: maybe-mostlyclean-opcodes
mostlyclean-host: maybe-mostlyclean-binutils
mostlyclean-host: maybe-mostlyclean-bison
mostlyclean-host: maybe-mostlyclean-byacc
mostlyclean-host: maybe-mostlyclean-bzip2
mostlyclean-host: maybe-mostlyclean-dejagnu
mostlyclean-host: maybe-mostlyclean-diff
mostlyclean-host: maybe-mostlyclean-dosutils
mostlyclean-host: maybe-mostlyclean-etc
mostlyclean-host: maybe-mostlyclean-fastjar
mostlyclean-host: maybe-mostlyclean-fileutils
mostlyclean-host: maybe-mostlyclean-findutils
mostlyclean-host: maybe-mostlyclean-find
mostlyclean-host: maybe-mostlyclean-fixincludes
mostlyclean-host: maybe-mostlyclean-flex
mostlyclean-host: maybe-mostlyclean-gas
mostlyclean-host: maybe-mostlyclean-gcc
mostlyclean-host: maybe-mostlyclean-gawk
mostlyclean-host: maybe-mostlyclean-gettext
mostlyclean-host: maybe-mostlyclean-gmp
mostlyclean-host: maybe-mostlyclean-mpfr
mostlyclean-host: maybe-mostlyclean-ppl
mostlyclean-host: maybe-mostlyclean-cloog
mostlyclean-host: maybe-mostlyclean-gnuserv
mostlyclean-host: maybe-mostlyclean-gold
mostlyclean-host: maybe-mostlyclean-gprof
mostlyclean-host: maybe-mostlyclean-gzip
mostlyclean-host: maybe-mostlyclean-hello
mostlyclean-host: maybe-mostlyclean-indent
mostlyclean-host: maybe-mostlyclean-intl
mostlyclean-host: maybe-mostlyclean-tcl
mostlyclean-host: maybe-mostlyclean-itcl
mostlyclean-host: maybe-mostlyclean-ld
mostlyclean-host: maybe-mostlyclean-libcpp
mostlyclean-host: maybe-mostlyclean-libdecnumber
mostlyclean-host: maybe-mostlyclean-libgui
mostlyclean-host: maybe-mostlyclean-libiberty
mostlyclean-host: maybe-mostlyclean-libiconv
mostlyclean-host: maybe-mostlyclean-libtool
mostlyclean-host: maybe-mostlyclean-m4
mostlyclean-host: maybe-mostlyclean-make
mostlyclean-host: maybe-mostlyclean-mmalloc
mostlyclean-host: maybe-mostlyclean-patch
mostlyclean-host: maybe-mostlyclean-perl
mostlyclean-host: maybe-mostlyclean-prms
mostlyclean-host: maybe-mostlyclean-rcs
mostlyclean-host: maybe-mostlyclean-readline
mostlyclean-host: maybe-mostlyclean-release
mostlyclean-host: maybe-mostlyclean-recode
mostlyclean-host: maybe-mostlyclean-sed
mostlyclean-host: maybe-mostlyclean-send-pr
mostlyclean-host: maybe-mostlyclean-shellutils
mostlyclean-host: maybe-mostlyclean-sid
mostlyclean-host: maybe-mostlyclean-sim
mostlyclean-host: maybe-mostlyclean-tar
mostlyclean-host: maybe-mostlyclean-texinfo
mostlyclean-host: maybe-mostlyclean-textutils
mostlyclean-host: maybe-mostlyclean-time
mostlyclean-host: maybe-mostlyclean-uudecode
mostlyclean-host: maybe-mostlyclean-wdiff
mostlyclean-host: maybe-mostlyclean-zip
mostlyclean-host: maybe-mostlyclean-zlib
mostlyclean-host: maybe-mostlyclean-gdb
mostlyclean-host: maybe-mostlyclean-expect
mostlyclean-host: maybe-mostlyclean-guile
mostlyclean-host: maybe-mostlyclean-tk
mostlyclean-host: maybe-mostlyclean-libtermcap
mostlyclean-host: maybe-mostlyclean-utils
mostlyclean-host: maybe-mostlyclean-gnattools

.PHONY: mostlyclean-target

mostlyclean-target: maybe-mostlyclean-target-libstdc++-v3
mostlyclean-target: maybe-mostlyclean-target-libmudflap
mostlyclean-target: maybe-mostlyclean-target-libssp
mostlyclean-target: maybe-mostlyclean-target-newlib
mostlyclean-target: maybe-mostlyclean-target-libgcc
mostlyclean-target: maybe-mostlyclean-target-libgfortran
mostlyclean-target: maybe-mostlyclean-target-libobjc
mostlyclean-target: maybe-mostlyclean-target-libtermcap
mostlyclean-target: maybe-mostlyclean-target-winsup
mostlyclean-target: maybe-mostlyclean-target-libgloss
mostlyclean-target: maybe-mostlyclean-target-libiberty
mostlyclean-target: maybe-mostlyclean-target-gperf
mostlyclean-target: maybe-mostlyclean-target-examples
mostlyclean-target: maybe-mostlyclean-target-libffi
mostlyclean-target: maybe-mostlyclean-target-libjava
mostlyclean-target: maybe-mostlyclean-target-zlib
mostlyclean-target: maybe-mostlyclean-target-boehm-gc
mostlyclean-target: maybe-mostlyclean-target-qthreads
mostlyclean-target: maybe-mostlyclean-target-rda
mostlyclean-target: maybe-mostlyclean-target-libada
mostlyclean-target: maybe-mostlyclean-target-libgomp

.PHONY: do-clean
do-clean:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) clean-host \
	  clean-target


.PHONY: clean-host

clean-host: maybe-clean-ash
clean-host: maybe-clean-autoconf
clean-host: maybe-clean-automake
clean-host: maybe-clean-bash
clean-host: maybe-clean-bfd
clean-host: maybe-clean-opcodes
clean-host: maybe-clean-binutils
clean-host: maybe-clean-bison
clean-host: maybe-clean-byacc
clean-host: maybe-clean-bzip2
clean-host: maybe-clean-dejagnu
clean-host: maybe-clean-diff
clean-host: maybe-clean-dosutils
clean-host: maybe-clean-etc
clean-host: maybe-clean-fastjar
clean-host: maybe-clean-fileutils
clean-host: maybe-clean-findutils
clean-host: maybe-clean-find
clean-host: maybe-clean-fixincludes
clean-host: maybe-clean-flex
clean-host: maybe-clean-gas
clean-host: maybe-clean-gcc
clean-host: maybe-clean-gawk
clean-host: maybe-clean-gettext
clean-host: maybe-clean-gmp
clean-host: maybe-clean-mpfr
clean-host: maybe-clean-ppl
clean-host: maybe-clean-cloog
clean-host: maybe-clean-gnuserv
clean-host: maybe-clean-gold
clean-host: maybe-clean-gprof
clean-host: maybe-clean-gzip
clean-host: maybe-clean-hello
clean-host: maybe-clean-indent
clean-host: maybe-clean-intl
clean-host: maybe-clean-tcl
clean-host: maybe-clean-itcl
clean-host: maybe-clean-ld
clean-host: maybe-clean-libcpp
clean-host: maybe-clean-libdecnumber
clean-host: maybe-clean-libgui
clean-host: maybe-clean-libiberty
clean-host: maybe-clean-libiconv
clean-host: maybe-clean-libtool
clean-host: maybe-clean-m4
clean-host: maybe-clean-make
clean-host: maybe-clean-mmalloc
clean-host: maybe-clean-patch
clean-host: maybe-clean-perl
clean-host: maybe-clean-prms
clean-host: maybe-clean-rcs
clean-host: maybe-clean-readline
clean-host: maybe-clean-release
clean-host: maybe-clean-recode
clean-host: maybe-clean-sed
clean-host: maybe-clean-send-pr
clean-host: maybe-clean-shellutils
clean-host: maybe-clean-sid
clean-host: maybe-clean-sim
clean-host: maybe-clean-tar
clean-host: maybe-clean-texinfo
clean-host: maybe-clean-textutils
clean-host: maybe-clean-time
clean-host: maybe-clean-uudecode
clean-host: maybe-clean-wdiff
clean-host: maybe-clean-zip
clean-host: maybe-clean-zlib
clean-host: maybe-clean-gdb
clean-host: maybe-clean-expect
clean-host: maybe-clean-guile
clean-host: maybe-clean-tk
clean-host: maybe-clean-libtermcap
clean-host: maybe-clean-utils
clean-host: maybe-clean-gnattools

.PHONY: clean-target

clean-target: maybe-clean-target-libstdc++-v3
clean-target: maybe-clean-target-libmudflap
clean-target: maybe-clean-target-libssp
clean-target: maybe-clean-target-newlib
clean-target: maybe-clean-target-libgcc
clean-target: maybe-clean-target-libgfortran
clean-target: maybe-clean-target-libobjc
clean-target: maybe-clean-target-libtermcap
clean-target: maybe-clean-target-winsup
clean-target: maybe-clean-target-libgloss
clean-target: maybe-clean-target-libiberty
clean-target: maybe-clean-target-gperf
clean-target: maybe-clean-target-examples
clean-target: maybe-clean-target-libffi
clean-target: maybe-clean-target-libjava
clean-target: maybe-clean-target-zlib
clean-target: maybe-clean-target-boehm-gc
clean-target: maybe-clean-target-qthreads
clean-target: maybe-clean-target-rda
clean-target: maybe-clean-target-libada
clean-target: maybe-clean-target-libgomp

.PHONY: do-distclean
do-distclean:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) distclean-host \
	  distclean-target


.PHONY: distclean-host

distclean-host: maybe-distclean-ash
distclean-host: maybe-distclean-autoconf
distclean-host: maybe-distclean-automake
distclean-host: maybe-distclean-bash
distclean-host: maybe-distclean-bfd
distclean-host: maybe-distclean-opcodes
distclean-host: maybe-distclean-binutils
distclean-host: maybe-distclean-bison
distclean-host: maybe-distclean-byacc
distclean-host: maybe-distclean-bzip2
distclean-host: maybe-distclean-dejagnu
distclean-host: maybe-distclean-diff
distclean-host: maybe-distclean-dosutils
distclean-host: maybe-distclean-etc
distclean-host: maybe-distclean-fastjar
distclean-host: maybe-distclean-fileutils
distclean-host: maybe-distclean-findutils
distclean-host: maybe-distclean-find
distclean-host: maybe-distclean-fixincludes
distclean-host: maybe-distclean-flex
distclean-host: maybe-distclean-gas
distclean-host: maybe-distclean-gcc
distclean-host: maybe-distclean-gawk
distclean-host: maybe-distclean-gettext
distclean-host: maybe-distclean-gmp
distclean-host: maybe-distclean-mpfr
distclean-host: maybe-distclean-ppl
distclean-host: maybe-distclean-cloog
distclean-host: maybe-distclean-gnuserv
distclean-host: maybe-distclean-gold
distclean-host: maybe-distclean-gprof
distclean-host: maybe-distclean-gzip
distclean-host: maybe-distclean-hello
distclean-host: maybe-distclean-indent
distclean-host: maybe-distclean-intl
distclean-host: maybe-distclean-tcl
distclean-host: maybe-distclean-itcl
distclean-host: maybe-distclean-ld
distclean-host: maybe-distclean-libcpp
distclean-host: maybe-distclean-libdecnumber
distclean-host: maybe-distclean-libgui
distclean-host: maybe-distclean-libiberty
distclean-host: maybe-distclean-libiconv
distclean-host: maybe-distclean-libtool
distclean-host: maybe-distclean-m4
distclean-host: maybe-distclean-make
distclean-host: maybe-distclean-mmalloc
distclean-host: maybe-distclean-patch
distclean-host: maybe-distclean-perl
distclean-host: maybe-distclean-prms
distclean-host: maybe-distclean-rcs
distclean-host: maybe-distclean-readline
distclean-host: maybe-distclean-release
distclean-host: maybe-distclean-recode
distclean-host: maybe-distclean-sed
distclean-host: maybe-distclean-send-pr
distclean-host: maybe-distclean-shellutils
distclean-host: maybe-distclean-sid
distclean-host: maybe-distclean-sim
distclean-host: maybe-distclean-tar
distclean-host: maybe-distclean-texinfo
distclean-host: maybe-distclean-textutils
distclean-host: maybe-distclean-time
distclean-host: maybe-distclean-uudecode
distclean-host: maybe-distclean-wdiff
distclean-host: maybe-distclean-zip
distclean-host: maybe-distclean-zlib
distclean-host: maybe-distclean-gdb
distclean-host: maybe-distclean-expect
distclean-host: maybe-distclean-guile
distclean-host: maybe-distclean-tk
distclean-host: maybe-distclean-libtermcap
distclean-host: maybe-distclean-utils
distclean-host: maybe-distclean-gnattools

.PHONY: distclean-target

distclean-target: maybe-distclean-target-libstdc++-v3
distclean-target: maybe-distclean-target-libmudflap
distclean-target: maybe-distclean-target-libssp
distclean-target: maybe-distclean-target-newlib
distclean-target: maybe-distclean-target-libgcc
distclean-target: maybe-distclean-target-libgfortran
distclean-target: maybe-distclean-target-libobjc
distclean-target: maybe-distclean-target-libtermcap
distclean-target: maybe-distclean-target-winsup
distclean-target: maybe-distclean-target-libgloss
distclean-target: maybe-distclean-target-libiberty
distclean-target: maybe-distclean-target-gperf
distclean-target: maybe-distclean-target-examples
distclean-target: maybe-distclean-target-libffi
distclean-target: maybe-distclean-target-libjava
distclean-target: maybe-distclean-target-zlib
distclean-target: maybe-distclean-target-boehm-gc
distclean-target: maybe-distclean-target-qthreads
distclean-target: maybe-distclean-target-rda
distclean-target: maybe-distclean-target-libada
distclean-target: maybe-distclean-target-libgomp

.PHONY: do-maintainer-clean
do-maintainer-clean:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) maintainer-clean-host \
	  maintainer-clean-target


.PHONY: maintainer-clean-host

maintainer-clean-host: maybe-maintainer-clean-ash
maintainer-clean-host: maybe-maintainer-clean-autoconf
maintainer-clean-host: maybe-maintainer-clean-automake
maintainer-clean-host: maybe-maintainer-clean-bash
maintainer-clean-host: maybe-maintainer-clean-bfd
maintainer-clean-host: maybe-maintainer-clean-opcodes
maintainer-clean-host: maybe-maintainer-clean-binutils
maintainer-clean-host: maybe-maintainer-clean-bison
maintainer-clean-host: maybe-maintainer-clean-byacc
maintainer-clean-host: maybe-maintainer-clean-bzip2
maintainer-clean-host: maybe-maintainer-clean-dejagnu
maintainer-clean-host: maybe-maintainer-clean-diff
maintainer-clean-host: maybe-maintainer-clean-dosutils
maintainer-clean-host: maybe-maintainer-clean-etc
maintainer-clean-host: maybe-maintainer-clean-fastjar
maintainer-clean-host: maybe-maintainer-clean-fileutils
maintainer-clean-host: maybe-maintainer-clean-findutils
maintainer-clean-host: maybe-maintainer-clean-find
maintainer-clean-host: maybe-maintainer-clean-fixincludes
maintainer-clean-host: maybe-maintainer-clean-flex
maintainer-clean-host: maybe-maintainer-clean-gas
maintainer-clean-host: maybe-maintainer-clean-gcc
maintainer-clean-host: maybe-maintainer-clean-gawk
maintainer-clean-host: maybe-maintainer-clean-gettext
maintainer-clean-host: maybe-maintainer-clean-gmp
maintainer-clean-host: maybe-maintainer-clean-mpfr
maintainer-clean-host: maybe-maintainer-clean-ppl
maintainer-clean-host: maybe-maintainer-clean-cloog
maintainer-clean-host: maybe-maintainer-clean-gnuserv
maintainer-clean-host: maybe-maintainer-clean-gold
maintainer-clean-host: maybe-maintainer-clean-gprof
maintainer-clean-host: maybe-maintainer-clean-gzip
maintainer-clean-host: maybe-maintainer-clean-hello
maintainer-clean-host: maybe-maintainer-clean-indent
maintainer-clean-host: maybe-maintainer-clean-intl
maintainer-clean-host: maybe-maintainer-clean-tcl
maintainer-clean-host: maybe-maintainer-clean-itcl
maintainer-clean-host: maybe-maintainer-clean-ld
maintainer-clean-host: maybe-maintainer-clean-libcpp
maintainer-clean-host: maybe-maintainer-clean-libdecnumber
maintainer-clean-host: maybe-maintainer-clean-libgui
maintainer-clean-host: maybe-maintainer-clean-libiberty
maintainer-clean-host: maybe-maintainer-clean-libiconv
maintainer-clean-host: maybe-maintainer-clean-libtool
maintainer-clean-host: maybe-maintainer-clean-m4
maintainer-clean-host: maybe-maintainer-clean-make
maintainer-clean-host: maybe-maintainer-clean-mmalloc
maintainer-clean-host: maybe-maintainer-clean-patch
maintainer-clean-host: maybe-maintainer-clean-perl
maintainer-clean-host: maybe-maintainer-clean-prms
maintainer-clean-host: maybe-maintainer-clean-rcs
maintainer-clean-host: maybe-maintainer-clean-readline
maintainer-clean-host: maybe-maintainer-clean-release
maintainer-clean-host: maybe-maintainer-clean-recode
maintainer-clean-host: maybe-maintainer-clean-sed
maintainer-clean-host: maybe-maintainer-clean-send-pr
maintainer-clean-host: maybe-maintainer-clean-shellutils
maintainer-clean-host: maybe-maintainer-clean-sid
maintainer-clean-host: maybe-maintainer-clean-sim
maintainer-clean-host: maybe-maintainer-clean-tar
maintainer-clean-host: maybe-maintainer-clean-texinfo
maintainer-clean-host: maybe-maintainer-clean-textutils
maintainer-clean-host: maybe-maintainer-clean-time
maintainer-clean-host: maybe-maintainer-clean-uudecode
maintainer-clean-host: maybe-maintainer-clean-wdiff
maintainer-clean-host: maybe-maintainer-clean-zip
maintainer-clean-host: maybe-maintainer-clean-zlib
maintainer-clean-host: maybe-maintainer-clean-gdb
maintainer-clean-host: maybe-maintainer-clean-expect
maintainer-clean-host: maybe-maintainer-clean-guile
maintainer-clean-host: maybe-maintainer-clean-tk
maintainer-clean-host: maybe-maintainer-clean-libtermcap
maintainer-clean-host: maybe-maintainer-clean-utils
maintainer-clean-host: maybe-maintainer-clean-gnattools

.PHONY: maintainer-clean-target

maintainer-clean-target: maybe-maintainer-clean-target-libstdc++-v3
maintainer-clean-target: maybe-maintainer-clean-target-libmudflap
maintainer-clean-target: maybe-maintainer-clean-target-libssp
maintainer-clean-target: maybe-maintainer-clean-target-newlib
maintainer-clean-target: maybe-maintainer-clean-target-libgcc
maintainer-clean-target: maybe-maintainer-clean-target-libgfortran
maintainer-clean-target: maybe-maintainer-clean-target-libobjc
maintainer-clean-target: maybe-maintainer-clean-target-libtermcap
maintainer-clean-target: maybe-maintainer-clean-target-winsup
maintainer-clean-target: maybe-maintainer-clean-target-libgloss
maintainer-clean-target: maybe-maintainer-clean-target-libiberty
maintainer-clean-target: maybe-maintainer-clean-target-gperf
maintainer-clean-target: maybe-maintainer-clean-target-examples
maintainer-clean-target: maybe-maintainer-clean-target-libffi
maintainer-clean-target: maybe-maintainer-clean-target-libjava
maintainer-clean-target: maybe-maintainer-clean-target-zlib
maintainer-clean-target: maybe-maintainer-clean-target-boehm-gc
maintainer-clean-target: maybe-maintainer-clean-target-qthreads
maintainer-clean-target: maybe-maintainer-clean-target-rda
maintainer-clean-target: maybe-maintainer-clean-target-libada
maintainer-clean-target: maybe-maintainer-clean-target-libgomp


# Here are the targets which correspond to the do-X targets.

.PHONY: info installcheck dvi pdf html
.PHONY: install-info install-pdf install-html
.PHONY: clean distclean mostlyclean maintainer-clean realclean
.PHONY: local-clean local-distclean local-maintainer-clean
info: do-info
installcheck: do-installcheck
dvi: do-dvi
pdf: do-pdf
html: do-html

# Make sure makeinfo is built before we do a `make info', if we're
# in fact building texinfo.
do-info: maybe-all-texinfo

install-info: do-install-info dir.info
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if [ -f dir.info ] ; then \
	  $(INSTALL_DATA) dir.info $(DESTDIR)$(infodir)/dir.info ; \
	else true ; fi

install-pdf: do-install-pdf

install-html: do-install-html

local-clean:
	-rm -f *.a TEMP errs core *.o *~ \#* TAGS *.E *.log

local-distclean:
	-rm -f Makefile config.status config.cache mh-frag mt-frag
	-rm -f maybedep.tmp serdep.tmp
	-if [ "$(TARGET_SUBDIR)" != "." ]; then \
	  rm -rf $(TARGET_SUBDIR); \
	else true; fi
	-rm -rf $(BUILD_SUBDIR)
	-if [ "$(HOST_SUBDIR)" != "." ]; then \
	  rm -rf $(HOST_SUBDIR); \
	else true; fi
	-rm -f texinfo/po/Makefile texinfo/po/Makefile.in texinfo/info/Makefile
	-rm -f texinfo/doc/Makefile texinfo/po/POTFILES
	-rmdir texinfo/doc texinfo/info texinfo/intl texinfo/lib 2>/dev/null
	-rmdir texinfo/makeinfo texinfo/po texinfo/util 2>/dev/null
	-rmdir fastjar gcc libiberty texinfo zlib 2>/dev/null

local-maintainer-clean:
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

clean: do-clean local-clean
mostlyclean: do-mostlyclean local-clean
distclean: do-distclean local-clean local-distclean
maintainer-clean: local-maintainer-clean do-maintainer-clean local-clean 
maintainer-clean: local-distclean
realclean: maintainer-clean

# Check target.

.PHONY: check do-check
check: do-check

# Only include modules actually being configured and built.
.PHONY: check-host
check-host:  \
    maybe-check-ash \
    maybe-check-autoconf \
    maybe-check-automake \
    maybe-check-bash \
    maybe-check-bfd \
    maybe-check-opcodes \
    maybe-check-binutils \
    maybe-check-bison \
    maybe-check-byacc \
    maybe-check-bzip2 \
    maybe-check-dejagnu \
    maybe-check-diff \
    maybe-check-dosutils \
    maybe-check-etc \
    maybe-check-fastjar \
    maybe-check-fileutils \
    maybe-check-findutils \
    maybe-check-find \
    maybe-check-fixincludes \
    maybe-check-flex \
    maybe-check-gas \
    maybe-check-gcc \
    maybe-check-gawk \
    maybe-check-gettext \
    maybe-check-gmp \
    maybe-check-mpfr \
    maybe-check-ppl \
    maybe-check-cloog \
    maybe-check-gnuserv \
    maybe-check-gold \
    maybe-check-gprof \
    maybe-check-gzip \
    maybe-check-hello \
    maybe-check-indent \
    maybe-check-intl \
    maybe-check-tcl \
    maybe-check-itcl \
    maybe-check-ld \
    maybe-check-libcpp \
    maybe-check-libdecnumber \
    maybe-check-libgui \
    maybe-check-libiberty \
    maybe-check-libiconv \
    maybe-check-libtool \
    maybe-check-m4 \
    maybe-check-make \
    maybe-check-mmalloc \
    maybe-check-patch \
    maybe-check-perl \
    maybe-check-prms \
    maybe-check-rcs \
    maybe-check-readline \
    maybe-check-release \
    maybe-check-recode \
    maybe-check-sed \
    maybe-check-send-pr \
    maybe-check-shellutils \
    maybe-check-sid \
    maybe-check-sim \
    maybe-check-tar \
    maybe-check-texinfo \
    maybe-check-textutils \
    maybe-check-time \
    maybe-check-uudecode \
    maybe-check-wdiff \
    maybe-check-zip \
    maybe-check-zlib \
    maybe-check-gdb \
    maybe-check-expect \
    maybe-check-guile \
    maybe-check-tk \
    maybe-check-libtermcap \
    maybe-check-utils \
    maybe-check-gnattools

.PHONY: check-target
check-target:  \
    maybe-check-target-libstdc++-v3 \
    maybe-check-target-libmudflap \
    maybe-check-target-libssp \
    maybe-check-target-newlib \
    maybe-check-target-libgcc \
    maybe-check-target-libgfortran \
    maybe-check-target-libobjc \
    maybe-check-target-libtermcap \
    maybe-check-target-winsup \
    maybe-check-target-libgloss \
    maybe-check-target-libiberty \
    maybe-check-target-gperf \
    maybe-check-target-examples \
    maybe-check-target-libffi \
    maybe-check-target-libjava \
    maybe-check-target-zlib \
    maybe-check-target-boehm-gc \
    maybe-check-target-qthreads \
    maybe-check-target-rda \
    maybe-check-target-libada \
    maybe-check-target-libgomp

do-check:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) check-host check-target

# Automated reporting of test results.

warning.log: build.log
	$(srcdir)/contrib/warn_summary build.log > $@

mail-report.log:
	if test x'$(BOOT_CFLAGS)' != x''; then \
	    BOOT_CFLAGS='$(BOOT_CFLAGS)'; export BOOT_CFLAGS; \
	fi; \
	$(srcdir)/contrib/test_summary -t >$@
	chmod +x $@
	echo If you really want to send e-mail, run ./$@ now

mail-report-with-warnings.log: warning.log
	if test x'$(BOOT_CFLAGS)' != x''; then \
	    BOOT_CFLAGS='$(BOOT_CFLAGS)'; export BOOT_CFLAGS; \
	fi; \
	$(srcdir)/contrib/test_summary -t -i warning.log >$@
	chmod +x $@
	echo If you really want to send e-mail, run ./$@ now

# Installation targets.

.PHONY: install uninstall
install:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) installdirs install-host install-target

.PHONY: install-host-nogcc
install-host-nogcc:  \
    maybe-install-ash \
    maybe-install-autoconf \
    maybe-install-automake \
    maybe-install-bash \
    maybe-install-bfd \
    maybe-install-opcodes \
    maybe-install-binutils \
    maybe-install-bison \
    maybe-install-byacc \
    maybe-install-bzip2 \
    maybe-install-dejagnu \
    maybe-install-diff \
    maybe-install-dosutils \
    maybe-install-etc \
    maybe-install-fastjar \
    maybe-install-fileutils \
    maybe-install-findutils \
    maybe-install-find \
    maybe-install-fixincludes \
    maybe-install-flex \
    maybe-install-gas \
    maybe-install-gawk \
    maybe-install-gettext \
    maybe-install-gmp \
    maybe-install-mpfr \
    maybe-install-ppl \
    maybe-install-cloog \
    maybe-install-gnuserv \
    maybe-install-gold \
    maybe-install-gprof \
    maybe-install-gzip \
    maybe-install-hello \
    maybe-install-indent \
    maybe-install-intl \
    maybe-install-tcl \
    maybe-install-itcl \
    maybe-install-ld \
    maybe-install-libcpp \
    maybe-install-libdecnumber \
    maybe-install-libgui \
    maybe-install-libiberty \
    maybe-install-libiconv \
    maybe-install-libtool \
    maybe-install-m4 \
    maybe-install-make \
    maybe-install-mmalloc \
    maybe-install-patch \
    maybe-install-perl \
    maybe-install-prms \
    maybe-install-rcs \
    maybe-install-readline \
    maybe-install-release \
    maybe-install-recode \
    maybe-install-sed \
    maybe-install-send-pr \
    maybe-install-shellutils \
    maybe-install-sid \
    maybe-install-sim \
    maybe-install-tar \
    maybe-install-texinfo \
    maybe-install-textutils \
    maybe-install-time \
    maybe-install-uudecode \
    maybe-install-wdiff \
    maybe-install-zip \
    maybe-install-zlib \
    maybe-install-gdb \
    maybe-install-expect \
    maybe-install-guile \
    maybe-install-tk \
    maybe-install-libtermcap \
    maybe-install-utils \
    maybe-install-gnattools

.PHONY: install-host
install-host:  \
    maybe-install-ash \
    maybe-install-autoconf \
    maybe-install-automake \
    maybe-install-bash \
    maybe-install-bfd \
    maybe-install-opcodes \
    maybe-install-binutils \
    maybe-install-bison \
    maybe-install-byacc \
    maybe-install-bzip2 \
    maybe-install-dejagnu \
    maybe-install-diff \
    maybe-install-dosutils \
    maybe-install-etc \
    maybe-install-fastjar \
    maybe-install-fileutils \
    maybe-install-findutils \
    maybe-install-find \
    maybe-install-fixincludes \
    maybe-install-flex \
    maybe-install-gas \
    maybe-install-gcc \
    maybe-install-gawk \
    maybe-install-gettext \
    maybe-install-gmp \
    maybe-install-mpfr \
    maybe-install-ppl \
    maybe-install-cloog \
    maybe-install-gnuserv \
    maybe-install-gold \
    maybe-install-gprof \
    maybe-install-gzip \
    maybe-install-hello \
    maybe-install-indent \
    maybe-install-intl \
    maybe-install-tcl \
    maybe-install-itcl \
    maybe-install-ld \
    maybe-install-libcpp \
    maybe-install-libdecnumber \
    maybe-install-libgui \
    maybe-install-libiberty \
    maybe-install-libiconv \
    maybe-install-libtool \
    maybe-install-m4 \
    maybe-install-make \
    maybe-install-mmalloc \
    maybe-install-patch \
    maybe-install-perl \
    maybe-install-prms \
    maybe-install-rcs \
    maybe-install-readline \
    maybe-install-release \
    maybe-install-recode \
    maybe-install-sed \
    maybe-install-send-pr \
    maybe-install-shellutils \
    maybe-install-sid \
    maybe-install-sim \
    maybe-install-tar \
    maybe-install-texinfo \
    maybe-install-textutils \
    maybe-install-time \
    maybe-install-uudecode \
    maybe-install-wdiff \
    maybe-install-zip \
    maybe-install-zlib \
    maybe-install-gdb \
    maybe-install-expect \
    maybe-install-guile \
    maybe-install-tk \
    maybe-install-libtermcap \
    maybe-install-utils \
    maybe-install-gnattools

.PHONY: install-target
install-target:  \
    maybe-install-target-libstdc++-v3 \
    maybe-install-target-libmudflap \
    maybe-install-target-libssp \
    maybe-install-target-newlib \
    maybe-install-target-libgcc \
    maybe-install-target-libgfortran \
    maybe-install-target-libobjc \
    maybe-install-target-libtermcap \
    maybe-install-target-winsup \
    maybe-install-target-libgloss \
    maybe-install-target-libiberty \
    maybe-install-target-gperf \
    maybe-install-target-examples \
    maybe-install-target-libffi \
    maybe-install-target-libjava \
    maybe-install-target-zlib \
    maybe-install-target-boehm-gc \
    maybe-install-target-qthreads \
    maybe-install-target-rda \
    maybe-install-target-libada \
    maybe-install-target-libgomp

uninstall:
	@echo "the uninstall target is not supported in this tree"

.PHONY: install.all
install.all: install-no-fixedincludes
	@if [ -f ./gcc/Makefile ] ; then \
		r=`${PWD_COMMAND}` ; export r ; \
		s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
		$(HOST_EXPORTS) \
		(cd ./gcc && \
		$(MAKE) $(FLAGS_TO_PASS) install-headers) ; \
	else \
		true ; \
	fi

# install-no-fixedincludes is used because Cygnus can not distribute
# the fixed header files.
.PHONY: install-no-fixedincludes
install-no-fixedincludes: installdirs install-host-nogcc \
	install-target gcc-no-fixedincludes

### other supporting targets

MAKEDIRS= \
	$(DESTDIR)$(prefix) \
	$(DESTDIR)$(exec_prefix)
.PHONY: installdirs
installdirs: mkinstalldirs
	$(SHELL) $(srcdir)/mkinstalldirs $(MAKEDIRS)

dir.info: do-install-info
	if [ -f $(srcdir)/texinfo/gen-info-dir ] ; then \
	  $(srcdir)/texinfo/gen-info-dir $(DESTDIR)$(infodir) $(srcdir)/texinfo/dir.info-template > dir.info.new ; \
	  mv -f dir.info.new dir.info ; \
	else true ; \
	fi

dist:
	@echo "Building a full distribution of this tree isn't done"
	@echo "via 'make dist'.  Check out the etc/ subdirectory" 

etags tags: TAGS

# Right now this just builds TAGS in each subdirectory.  emacs19 has the
# ability to use several tags files at once, so there is probably no need
# to combine them into one big TAGS file (like CVS 1.3 does).  We could
# (if we felt like it) have this Makefile write a piece of elisp which
# the user could load to tell emacs19 where all the TAGS files we just
# built are.
TAGS: do-TAGS

# ------------------------------------
# Macros for configure and all targets
# ------------------------------------





# --------------------------------------
# Modules which run on the build machine
# --------------------------------------


.PHONY: configure-build-libiberty maybe-configure-build-libiberty
maybe-configure-build-libiberty:
configure-build-libiberty: stage_current
maybe-configure-build-libiberty: configure-build-libiberty
configure-build-libiberty: 
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(BUILD_SUBDIR)/libiberty/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(BUILD_SUBDIR)/libiberty ; \
	$(BUILD_EXPORTS) \
	echo Configuring in $(BUILD_SUBDIR)/libiberty; \
	cd "$(BUILD_SUBDIR)/libiberty" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(BUILD_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	rm -f no-such-file || : ; \
	CONFIG_SITE=no-such-file $(SHELL) $${libsrcdir}/configure \
	  $(BUILD_CONFIGARGS) --build=${build_alias} --host=${build_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1





.PHONY: all-build-libiberty maybe-all-build-libiberty
maybe-all-build-libiberty:
all-build-libiberty: stage_current
TARGET-build-libiberty=all
maybe-all-build-libiberty: all-build-libiberty
all-build-libiberty: configure-build-libiberty
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(BUILD_EXPORTS) \
	(cd $(BUILD_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_BUILD_FLAGS)  \
		$(TARGET-build-libiberty))





.PHONY: configure-build-bison maybe-configure-build-bison
maybe-configure-build-bison:
configure-build-bison: stage_current





.PHONY: all-build-bison maybe-all-build-bison
maybe-all-build-bison:
all-build-bison: stage_current





.PHONY: configure-build-byacc maybe-configure-build-byacc
maybe-configure-build-byacc:
configure-build-byacc: stage_current





.PHONY: all-build-byacc maybe-all-build-byacc
maybe-all-build-byacc:
all-build-byacc: stage_current





.PHONY: configure-build-flex maybe-configure-build-flex
maybe-configure-build-flex:
configure-build-flex: stage_current





.PHONY: all-build-flex maybe-all-build-flex
maybe-all-build-flex:
all-build-flex: stage_current





.PHONY: configure-build-m4 maybe-configure-build-m4
maybe-configure-build-m4:
configure-build-m4: stage_current





.PHONY: all-build-m4 maybe-all-build-m4
maybe-all-build-m4:
all-build-m4: stage_current





.PHONY: configure-build-texinfo maybe-configure-build-texinfo
maybe-configure-build-texinfo:
configure-build-texinfo: stage_current





.PHONY: all-build-texinfo maybe-all-build-texinfo
maybe-all-build-texinfo:
all-build-texinfo: stage_current





.PHONY: configure-build-fixincludes maybe-configure-build-fixincludes
maybe-configure-build-fixincludes:
configure-build-fixincludes: stage_current
maybe-configure-build-fixincludes: configure-build-fixincludes
configure-build-fixincludes: 
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(BUILD_SUBDIR)/fixincludes/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(BUILD_SUBDIR)/fixincludes ; \
	$(BUILD_EXPORTS) \
	echo Configuring in $(BUILD_SUBDIR)/fixincludes; \
	cd "$(BUILD_SUBDIR)/fixincludes" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(BUILD_SUBDIR)/fixincludes/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/fixincludes"; \
	libsrcdir="$$s/fixincludes"; \
	rm -f no-such-file || : ; \
	CONFIG_SITE=no-such-file $(SHELL) $${libsrcdir}/configure \
	  $(BUILD_CONFIGARGS) --build=${build_alias} --host=${build_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1





.PHONY: all-build-fixincludes maybe-all-build-fixincludes
maybe-all-build-fixincludes:
all-build-fixincludes: stage_current
TARGET-build-fixincludes=all
maybe-all-build-fixincludes: all-build-fixincludes
all-build-fixincludes: configure-build-fixincludes
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(BUILD_EXPORTS) \
	(cd $(BUILD_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_BUILD_FLAGS)  \
		$(TARGET-build-fixincludes))





# --------------------------------------
# Modules which run on the host machine
# --------------------------------------


.PHONY: configure-ash maybe-configure-ash
maybe-configure-ash:
configure-ash: stage_current





.PHONY: all-ash maybe-all-ash
maybe-all-ash:
all-ash: stage_current




.PHONY: check-ash maybe-check-ash
maybe-check-ash:

.PHONY: install-ash maybe-install-ash
maybe-install-ash:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-ash info-ash
maybe-info-ash:

.PHONY: maybe-dvi-ash dvi-ash
maybe-dvi-ash:

.PHONY: maybe-pdf-ash pdf-ash
maybe-pdf-ash:

.PHONY: maybe-html-ash html-ash
maybe-html-ash:

.PHONY: maybe-TAGS-ash TAGS-ash
maybe-TAGS-ash:

.PHONY: maybe-install-info-ash install-info-ash
maybe-install-info-ash:

.PHONY: maybe-install-pdf-ash install-pdf-ash
maybe-install-pdf-ash:

.PHONY: maybe-install-html-ash install-html-ash
maybe-install-html-ash:

.PHONY: maybe-installcheck-ash installcheck-ash
maybe-installcheck-ash:

.PHONY: maybe-mostlyclean-ash mostlyclean-ash
maybe-mostlyclean-ash:

.PHONY: maybe-clean-ash clean-ash
maybe-clean-ash:

.PHONY: maybe-distclean-ash distclean-ash
maybe-distclean-ash:

.PHONY: maybe-maintainer-clean-ash maintainer-clean-ash
maybe-maintainer-clean-ash:



.PHONY: configure-autoconf maybe-configure-autoconf
maybe-configure-autoconf:
configure-autoconf: stage_current





.PHONY: all-autoconf maybe-all-autoconf
maybe-all-autoconf:
all-autoconf: stage_current




.PHONY: check-autoconf maybe-check-autoconf
maybe-check-autoconf:

.PHONY: install-autoconf maybe-install-autoconf
maybe-install-autoconf:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-autoconf info-autoconf
maybe-info-autoconf:

.PHONY: maybe-dvi-autoconf dvi-autoconf
maybe-dvi-autoconf:

.PHONY: maybe-pdf-autoconf pdf-autoconf
maybe-pdf-autoconf:

.PHONY: maybe-html-autoconf html-autoconf
maybe-html-autoconf:

.PHONY: maybe-TAGS-autoconf TAGS-autoconf
maybe-TAGS-autoconf:

.PHONY: maybe-install-info-autoconf install-info-autoconf
maybe-install-info-autoconf:

.PHONY: maybe-install-pdf-autoconf install-pdf-autoconf
maybe-install-pdf-autoconf:

.PHONY: maybe-install-html-autoconf install-html-autoconf
maybe-install-html-autoconf:

.PHONY: maybe-installcheck-autoconf installcheck-autoconf
maybe-installcheck-autoconf:

.PHONY: maybe-mostlyclean-autoconf mostlyclean-autoconf
maybe-mostlyclean-autoconf:

.PHONY: maybe-clean-autoconf clean-autoconf
maybe-clean-autoconf:

.PHONY: maybe-distclean-autoconf distclean-autoconf
maybe-distclean-autoconf:

.PHONY: maybe-maintainer-clean-autoconf maintainer-clean-autoconf
maybe-maintainer-clean-autoconf:



.PHONY: configure-automake maybe-configure-automake
maybe-configure-automake:
configure-automake: stage_current





.PHONY: all-automake maybe-all-automake
maybe-all-automake:
all-automake: stage_current




.PHONY: check-automake maybe-check-automake
maybe-check-automake:

.PHONY: install-automake maybe-install-automake
maybe-install-automake:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-automake info-automake
maybe-info-automake:

.PHONY: maybe-dvi-automake dvi-automake
maybe-dvi-automake:

.PHONY: maybe-pdf-automake pdf-automake
maybe-pdf-automake:

.PHONY: maybe-html-automake html-automake
maybe-html-automake:

.PHONY: maybe-TAGS-automake TAGS-automake
maybe-TAGS-automake:

.PHONY: maybe-install-info-automake install-info-automake
maybe-install-info-automake:

.PHONY: maybe-install-pdf-automake install-pdf-automake
maybe-install-pdf-automake:

.PHONY: maybe-install-html-automake install-html-automake
maybe-install-html-automake:

.PHONY: maybe-installcheck-automake installcheck-automake
maybe-installcheck-automake:

.PHONY: maybe-mostlyclean-automake mostlyclean-automake
maybe-mostlyclean-automake:

.PHONY: maybe-clean-automake clean-automake
maybe-clean-automake:

.PHONY: maybe-distclean-automake distclean-automake
maybe-distclean-automake:

.PHONY: maybe-maintainer-clean-automake maintainer-clean-automake
maybe-maintainer-clean-automake:



.PHONY: configure-bash maybe-configure-bash
maybe-configure-bash:
configure-bash: stage_current





.PHONY: all-bash maybe-all-bash
maybe-all-bash:
all-bash: stage_current




.PHONY: check-bash maybe-check-bash
maybe-check-bash:

.PHONY: install-bash maybe-install-bash
maybe-install-bash:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-bash info-bash
maybe-info-bash:

.PHONY: maybe-dvi-bash dvi-bash
maybe-dvi-bash:

.PHONY: maybe-pdf-bash pdf-bash
maybe-pdf-bash:

.PHONY: maybe-html-bash html-bash
maybe-html-bash:

.PHONY: maybe-TAGS-bash TAGS-bash
maybe-TAGS-bash:

.PHONY: maybe-install-info-bash install-info-bash
maybe-install-info-bash:

.PHONY: maybe-install-pdf-bash install-pdf-bash
maybe-install-pdf-bash:

.PHONY: maybe-install-html-bash install-html-bash
maybe-install-html-bash:

.PHONY: maybe-installcheck-bash installcheck-bash
maybe-installcheck-bash:

.PHONY: maybe-mostlyclean-bash mostlyclean-bash
maybe-mostlyclean-bash:

.PHONY: maybe-clean-bash clean-bash
maybe-clean-bash:

.PHONY: maybe-distclean-bash distclean-bash
maybe-distclean-bash:

.PHONY: maybe-maintainer-clean-bash maintainer-clean-bash
maybe-maintainer-clean-bash:



.PHONY: configure-bfd maybe-configure-bfd
maybe-configure-bfd:
configure-bfd: stage_current



.PHONY: configure-stage1-bfd maybe-configure-stage1-bfd
maybe-configure-stage1-bfd:

.PHONY: configure-stage2-bfd maybe-configure-stage2-bfd
maybe-configure-stage2-bfd:

.PHONY: configure-stageb2g0-bfd maybe-configure-stageb2g0-bfd
maybe-configure-stageb2g0-bfd:

.PHONY: configure-stage3-bfd maybe-configure-stage3-bfd
maybe-configure-stage3-bfd:

.PHONY: configure-stageb3g2-bfd maybe-configure-stageb3g2-bfd
maybe-configure-stageb3g2-bfd:

.PHONY: configure-stage4-bfd maybe-configure-stage4-bfd
maybe-configure-stage4-bfd:

.PHONY: configure-stageprofile-bfd maybe-configure-stageprofile-bfd
maybe-configure-stageprofile-bfd:

.PHONY: configure-stagefeedback-bfd maybe-configure-stagefeedback-bfd
maybe-configure-stagefeedback-bfd:





.PHONY: all-bfd maybe-all-bfd
maybe-all-bfd:
all-bfd: stage_current



.PHONY: all-stage1-bfd maybe-all-stage1-bfd
.PHONY: clean-stage1-bfd maybe-clean-stage1-bfd
maybe-all-stage1-bfd:
maybe-clean-stage1-bfd:


.PHONY: all-stage2-bfd maybe-all-stage2-bfd
.PHONY: clean-stage2-bfd maybe-clean-stage2-bfd
maybe-all-stage2-bfd:
maybe-clean-stage2-bfd:


.PHONY: all-stageb2g0-bfd maybe-all-stageb2g0-bfd
.PHONY: clean-stageb2g0-bfd maybe-clean-stageb2g0-bfd
maybe-all-stageb2g0-bfd:
maybe-clean-stageb2g0-bfd:


.PHONY: all-stage3-bfd maybe-all-stage3-bfd
.PHONY: clean-stage3-bfd maybe-clean-stage3-bfd
maybe-all-stage3-bfd:
maybe-clean-stage3-bfd:


.PHONY: all-stageb3g2-bfd maybe-all-stageb3g2-bfd
.PHONY: clean-stageb3g2-bfd maybe-clean-stageb3g2-bfd
maybe-all-stageb3g2-bfd:
maybe-clean-stageb3g2-bfd:


.PHONY: all-stage4-bfd maybe-all-stage4-bfd
.PHONY: clean-stage4-bfd maybe-clean-stage4-bfd
maybe-all-stage4-bfd:
maybe-clean-stage4-bfd:


.PHONY: all-stageprofile-bfd maybe-all-stageprofile-bfd
.PHONY: clean-stageprofile-bfd maybe-clean-stageprofile-bfd
maybe-all-stageprofile-bfd:
maybe-clean-stageprofile-bfd:


.PHONY: all-stagefeedback-bfd maybe-all-stagefeedback-bfd
.PHONY: clean-stagefeedback-bfd maybe-clean-stagefeedback-bfd
maybe-all-stagefeedback-bfd:
maybe-clean-stagefeedback-bfd:





.PHONY: check-bfd maybe-check-bfd
maybe-check-bfd:

.PHONY: install-bfd maybe-install-bfd
maybe-install-bfd:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-bfd info-bfd
maybe-info-bfd:

.PHONY: maybe-dvi-bfd dvi-bfd
maybe-dvi-bfd:

.PHONY: maybe-pdf-bfd pdf-bfd
maybe-pdf-bfd:

.PHONY: maybe-html-bfd html-bfd
maybe-html-bfd:

.PHONY: maybe-TAGS-bfd TAGS-bfd
maybe-TAGS-bfd:

.PHONY: maybe-install-info-bfd install-info-bfd
maybe-install-info-bfd:

.PHONY: maybe-install-pdf-bfd install-pdf-bfd
maybe-install-pdf-bfd:

.PHONY: maybe-install-html-bfd install-html-bfd
maybe-install-html-bfd:

.PHONY: maybe-installcheck-bfd installcheck-bfd
maybe-installcheck-bfd:

.PHONY: maybe-mostlyclean-bfd mostlyclean-bfd
maybe-mostlyclean-bfd:

.PHONY: maybe-clean-bfd clean-bfd
maybe-clean-bfd:

.PHONY: maybe-distclean-bfd distclean-bfd
maybe-distclean-bfd:

.PHONY: maybe-maintainer-clean-bfd maintainer-clean-bfd
maybe-maintainer-clean-bfd:



.PHONY: configure-opcodes maybe-configure-opcodes
maybe-configure-opcodes:
configure-opcodes: stage_current



.PHONY: configure-stage1-opcodes maybe-configure-stage1-opcodes
maybe-configure-stage1-opcodes:

.PHONY: configure-stage2-opcodes maybe-configure-stage2-opcodes
maybe-configure-stage2-opcodes:

.PHONY: configure-stageb2g0-opcodes maybe-configure-stageb2g0-opcodes
maybe-configure-stageb2g0-opcodes:

.PHONY: configure-stage3-opcodes maybe-configure-stage3-opcodes
maybe-configure-stage3-opcodes:

.PHONY: configure-stageb3g2-opcodes maybe-configure-stageb3g2-opcodes
maybe-configure-stageb3g2-opcodes:

.PHONY: configure-stage4-opcodes maybe-configure-stage4-opcodes
maybe-configure-stage4-opcodes:

.PHONY: configure-stageprofile-opcodes maybe-configure-stageprofile-opcodes
maybe-configure-stageprofile-opcodes:

.PHONY: configure-stagefeedback-opcodes maybe-configure-stagefeedback-opcodes
maybe-configure-stagefeedback-opcodes:





.PHONY: all-opcodes maybe-all-opcodes
maybe-all-opcodes:
all-opcodes: stage_current



.PHONY: all-stage1-opcodes maybe-all-stage1-opcodes
.PHONY: clean-stage1-opcodes maybe-clean-stage1-opcodes
maybe-all-stage1-opcodes:
maybe-clean-stage1-opcodes:


.PHONY: all-stage2-opcodes maybe-all-stage2-opcodes
.PHONY: clean-stage2-opcodes maybe-clean-stage2-opcodes
maybe-all-stage2-opcodes:
maybe-clean-stage2-opcodes:


.PHONY: all-stageb2g0-opcodes maybe-all-stageb2g0-opcodes
.PHONY: clean-stageb2g0-opcodes maybe-clean-stageb2g0-opcodes
maybe-all-stageb2g0-opcodes:
maybe-clean-stageb2g0-opcodes:


.PHONY: all-stage3-opcodes maybe-all-stage3-opcodes
.PHONY: clean-stage3-opcodes maybe-clean-stage3-opcodes
maybe-all-stage3-opcodes:
maybe-clean-stage3-opcodes:


.PHONY: all-stageb3g2-opcodes maybe-all-stageb3g2-opcodes
.PHONY: clean-stageb3g2-opcodes maybe-clean-stageb3g2-opcodes
maybe-all-stageb3g2-opcodes:
maybe-clean-stageb3g2-opcodes:


.PHONY: all-stage4-opcodes maybe-all-stage4-opcodes
.PHONY: clean-stage4-opcodes maybe-clean-stage4-opcodes
maybe-all-stage4-opcodes:
maybe-clean-stage4-opcodes:


.PHONY: all-stageprofile-opcodes maybe-all-stageprofile-opcodes
.PHONY: clean-stageprofile-opcodes maybe-clean-stageprofile-opcodes
maybe-all-stageprofile-opcodes:
maybe-clean-stageprofile-opcodes:


.PHONY: all-stagefeedback-opcodes maybe-all-stagefeedback-opcodes
.PHONY: clean-stagefeedback-opcodes maybe-clean-stagefeedback-opcodes
maybe-all-stagefeedback-opcodes:
maybe-clean-stagefeedback-opcodes:





.PHONY: check-opcodes maybe-check-opcodes
maybe-check-opcodes:

.PHONY: install-opcodes maybe-install-opcodes
maybe-install-opcodes:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-opcodes info-opcodes
maybe-info-opcodes:

.PHONY: maybe-dvi-opcodes dvi-opcodes
maybe-dvi-opcodes:

.PHONY: maybe-pdf-opcodes pdf-opcodes
maybe-pdf-opcodes:

.PHONY: maybe-html-opcodes html-opcodes
maybe-html-opcodes:

.PHONY: maybe-TAGS-opcodes TAGS-opcodes
maybe-TAGS-opcodes:

.PHONY: maybe-install-info-opcodes install-info-opcodes
maybe-install-info-opcodes:

.PHONY: maybe-install-pdf-opcodes install-pdf-opcodes
maybe-install-pdf-opcodes:

.PHONY: maybe-install-html-opcodes install-html-opcodes
maybe-install-html-opcodes:

.PHONY: maybe-installcheck-opcodes installcheck-opcodes
maybe-installcheck-opcodes:

.PHONY: maybe-mostlyclean-opcodes mostlyclean-opcodes
maybe-mostlyclean-opcodes:

.PHONY: maybe-clean-opcodes clean-opcodes
maybe-clean-opcodes:

.PHONY: maybe-distclean-opcodes distclean-opcodes
maybe-distclean-opcodes:

.PHONY: maybe-maintainer-clean-opcodes maintainer-clean-opcodes
maybe-maintainer-clean-opcodes:



.PHONY: configure-binutils maybe-configure-binutils
maybe-configure-binutils:
configure-binutils: stage_current



.PHONY: configure-stage1-binutils maybe-configure-stage1-binutils
maybe-configure-stage1-binutils:

.PHONY: configure-stage2-binutils maybe-configure-stage2-binutils
maybe-configure-stage2-binutils:

.PHONY: configure-stageb2g0-binutils maybe-configure-stageb2g0-binutils
maybe-configure-stageb2g0-binutils:

.PHONY: configure-stage3-binutils maybe-configure-stage3-binutils
maybe-configure-stage3-binutils:

.PHONY: configure-stageb3g2-binutils maybe-configure-stageb3g2-binutils
maybe-configure-stageb3g2-binutils:

.PHONY: configure-stage4-binutils maybe-configure-stage4-binutils
maybe-configure-stage4-binutils:

.PHONY: configure-stageprofile-binutils maybe-configure-stageprofile-binutils
maybe-configure-stageprofile-binutils:

.PHONY: configure-stagefeedback-binutils maybe-configure-stagefeedback-binutils
maybe-configure-stagefeedback-binutils:





.PHONY: all-binutils maybe-all-binutils
maybe-all-binutils:
all-binutils: stage_current



.PHONY: all-stage1-binutils maybe-all-stage1-binutils
.PHONY: clean-stage1-binutils maybe-clean-stage1-binutils
maybe-all-stage1-binutils:
maybe-clean-stage1-binutils:


.PHONY: all-stage2-binutils maybe-all-stage2-binutils
.PHONY: clean-stage2-binutils maybe-clean-stage2-binutils
maybe-all-stage2-binutils:
maybe-clean-stage2-binutils:


.PHONY: all-stageb2g0-binutils maybe-all-stageb2g0-binutils
.PHONY: clean-stageb2g0-binutils maybe-clean-stageb2g0-binutils
maybe-all-stageb2g0-binutils:
maybe-clean-stageb2g0-binutils:


.PHONY: all-stage3-binutils maybe-all-stage3-binutils
.PHONY: clean-stage3-binutils maybe-clean-stage3-binutils
maybe-all-stage3-binutils:
maybe-clean-stage3-binutils:


.PHONY: all-stageb3g2-binutils maybe-all-stageb3g2-binutils
.PHONY: clean-stageb3g2-binutils maybe-clean-stageb3g2-binutils
maybe-all-stageb3g2-binutils:
maybe-clean-stageb3g2-binutils:


.PHONY: all-stage4-binutils maybe-all-stage4-binutils
.PHONY: clean-stage4-binutils maybe-clean-stage4-binutils
maybe-all-stage4-binutils:
maybe-clean-stage4-binutils:


.PHONY: all-stageprofile-binutils maybe-all-stageprofile-binutils
.PHONY: clean-stageprofile-binutils maybe-clean-stageprofile-binutils
maybe-all-stageprofile-binutils:
maybe-clean-stageprofile-binutils:


.PHONY: all-stagefeedback-binutils maybe-all-stagefeedback-binutils
.PHONY: clean-stagefeedback-binutils maybe-clean-stagefeedback-binutils
maybe-all-stagefeedback-binutils:
maybe-clean-stagefeedback-binutils:





.PHONY: check-binutils maybe-check-binutils
maybe-check-binutils:

.PHONY: install-binutils maybe-install-binutils
maybe-install-binutils:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-binutils info-binutils
maybe-info-binutils:

.PHONY: maybe-dvi-binutils dvi-binutils
maybe-dvi-binutils:

.PHONY: maybe-pdf-binutils pdf-binutils
maybe-pdf-binutils:

.PHONY: maybe-html-binutils html-binutils
maybe-html-binutils:

.PHONY: maybe-TAGS-binutils TAGS-binutils
maybe-TAGS-binutils:

.PHONY: maybe-install-info-binutils install-info-binutils
maybe-install-info-binutils:

.PHONY: maybe-install-pdf-binutils install-pdf-binutils
maybe-install-pdf-binutils:

.PHONY: maybe-install-html-binutils install-html-binutils
maybe-install-html-binutils:

.PHONY: maybe-installcheck-binutils installcheck-binutils
maybe-installcheck-binutils:

.PHONY: maybe-mostlyclean-binutils mostlyclean-binutils
maybe-mostlyclean-binutils:

.PHONY: maybe-clean-binutils clean-binutils
maybe-clean-binutils:

.PHONY: maybe-distclean-binutils distclean-binutils
maybe-distclean-binutils:

.PHONY: maybe-maintainer-clean-binutils maintainer-clean-binutils
maybe-maintainer-clean-binutils:



.PHONY: configure-bison maybe-configure-bison
maybe-configure-bison:
configure-bison: stage_current





.PHONY: all-bison maybe-all-bison
maybe-all-bison:
all-bison: stage_current




.PHONY: check-bison maybe-check-bison
maybe-check-bison:

.PHONY: install-bison maybe-install-bison
maybe-install-bison:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-bison info-bison
maybe-info-bison:

.PHONY: maybe-dvi-bison dvi-bison
maybe-dvi-bison:

.PHONY: maybe-pdf-bison pdf-bison
maybe-pdf-bison:

.PHONY: maybe-html-bison html-bison
maybe-html-bison:

.PHONY: maybe-TAGS-bison TAGS-bison
maybe-TAGS-bison:

.PHONY: maybe-install-info-bison install-info-bison
maybe-install-info-bison:

.PHONY: maybe-install-pdf-bison install-pdf-bison
maybe-install-pdf-bison:

.PHONY: maybe-install-html-bison install-html-bison
maybe-install-html-bison:

.PHONY: maybe-installcheck-bison installcheck-bison
maybe-installcheck-bison:

.PHONY: maybe-mostlyclean-bison mostlyclean-bison
maybe-mostlyclean-bison:

.PHONY: maybe-clean-bison clean-bison
maybe-clean-bison:

.PHONY: maybe-distclean-bison distclean-bison
maybe-distclean-bison:

.PHONY: maybe-maintainer-clean-bison maintainer-clean-bison
maybe-maintainer-clean-bison:



.PHONY: configure-byacc maybe-configure-byacc
maybe-configure-byacc:
configure-byacc: stage_current





.PHONY: all-byacc maybe-all-byacc
maybe-all-byacc:
all-byacc: stage_current




.PHONY: check-byacc maybe-check-byacc
maybe-check-byacc:

.PHONY: install-byacc maybe-install-byacc
maybe-install-byacc:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-byacc info-byacc
maybe-info-byacc:

.PHONY: maybe-dvi-byacc dvi-byacc
maybe-dvi-byacc:

.PHONY: maybe-pdf-byacc pdf-byacc
maybe-pdf-byacc:

.PHONY: maybe-html-byacc html-byacc
maybe-html-byacc:

.PHONY: maybe-TAGS-byacc TAGS-byacc
maybe-TAGS-byacc:

.PHONY: maybe-install-info-byacc install-info-byacc
maybe-install-info-byacc:

.PHONY: maybe-install-pdf-byacc install-pdf-byacc
maybe-install-pdf-byacc:

.PHONY: maybe-install-html-byacc install-html-byacc
maybe-install-html-byacc:

.PHONY: maybe-installcheck-byacc installcheck-byacc
maybe-installcheck-byacc:

.PHONY: maybe-mostlyclean-byacc mostlyclean-byacc
maybe-mostlyclean-byacc:

.PHONY: maybe-clean-byacc clean-byacc
maybe-clean-byacc:

.PHONY: maybe-distclean-byacc distclean-byacc
maybe-distclean-byacc:

.PHONY: maybe-maintainer-clean-byacc maintainer-clean-byacc
maybe-maintainer-clean-byacc:



.PHONY: configure-bzip2 maybe-configure-bzip2
maybe-configure-bzip2:
configure-bzip2: stage_current





.PHONY: all-bzip2 maybe-all-bzip2
maybe-all-bzip2:
all-bzip2: stage_current




.PHONY: check-bzip2 maybe-check-bzip2
maybe-check-bzip2:

.PHONY: install-bzip2 maybe-install-bzip2
maybe-install-bzip2:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-bzip2 info-bzip2
maybe-info-bzip2:

.PHONY: maybe-dvi-bzip2 dvi-bzip2
maybe-dvi-bzip2:

.PHONY: maybe-pdf-bzip2 pdf-bzip2
maybe-pdf-bzip2:

.PHONY: maybe-html-bzip2 html-bzip2
maybe-html-bzip2:

.PHONY: maybe-TAGS-bzip2 TAGS-bzip2
maybe-TAGS-bzip2:

.PHONY: maybe-install-info-bzip2 install-info-bzip2
maybe-install-info-bzip2:

.PHONY: maybe-install-pdf-bzip2 install-pdf-bzip2
maybe-install-pdf-bzip2:

.PHONY: maybe-install-html-bzip2 install-html-bzip2
maybe-install-html-bzip2:

.PHONY: maybe-installcheck-bzip2 installcheck-bzip2
maybe-installcheck-bzip2:

.PHONY: maybe-mostlyclean-bzip2 mostlyclean-bzip2
maybe-mostlyclean-bzip2:

.PHONY: maybe-clean-bzip2 clean-bzip2
maybe-clean-bzip2:

.PHONY: maybe-distclean-bzip2 distclean-bzip2
maybe-distclean-bzip2:

.PHONY: maybe-maintainer-clean-bzip2 maintainer-clean-bzip2
maybe-maintainer-clean-bzip2:



.PHONY: configure-dejagnu maybe-configure-dejagnu
maybe-configure-dejagnu:
configure-dejagnu: stage_current





.PHONY: all-dejagnu maybe-all-dejagnu
maybe-all-dejagnu:
all-dejagnu: stage_current




.PHONY: check-dejagnu maybe-check-dejagnu
maybe-check-dejagnu:

.PHONY: install-dejagnu maybe-install-dejagnu
maybe-install-dejagnu:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-dejagnu info-dejagnu
maybe-info-dejagnu:

.PHONY: maybe-dvi-dejagnu dvi-dejagnu
maybe-dvi-dejagnu:

.PHONY: maybe-pdf-dejagnu pdf-dejagnu
maybe-pdf-dejagnu:

.PHONY: maybe-html-dejagnu html-dejagnu
maybe-html-dejagnu:

.PHONY: maybe-TAGS-dejagnu TAGS-dejagnu
maybe-TAGS-dejagnu:

.PHONY: maybe-install-info-dejagnu install-info-dejagnu
maybe-install-info-dejagnu:

.PHONY: maybe-install-pdf-dejagnu install-pdf-dejagnu
maybe-install-pdf-dejagnu:

.PHONY: maybe-install-html-dejagnu install-html-dejagnu
maybe-install-html-dejagnu:

.PHONY: maybe-installcheck-dejagnu installcheck-dejagnu
maybe-installcheck-dejagnu:

.PHONY: maybe-mostlyclean-dejagnu mostlyclean-dejagnu
maybe-mostlyclean-dejagnu:

.PHONY: maybe-clean-dejagnu clean-dejagnu
maybe-clean-dejagnu:

.PHONY: maybe-distclean-dejagnu distclean-dejagnu
maybe-distclean-dejagnu:

.PHONY: maybe-maintainer-clean-dejagnu maintainer-clean-dejagnu
maybe-maintainer-clean-dejagnu:



.PHONY: configure-diff maybe-configure-diff
maybe-configure-diff:
configure-diff: stage_current





.PHONY: all-diff maybe-all-diff
maybe-all-diff:
all-diff: stage_current




.PHONY: check-diff maybe-check-diff
maybe-check-diff:

.PHONY: install-diff maybe-install-diff
maybe-install-diff:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-diff info-diff
maybe-info-diff:

.PHONY: maybe-dvi-diff dvi-diff
maybe-dvi-diff:

.PHONY: maybe-pdf-diff pdf-diff
maybe-pdf-diff:

.PHONY: maybe-html-diff html-diff
maybe-html-diff:

.PHONY: maybe-TAGS-diff TAGS-diff
maybe-TAGS-diff:

.PHONY: maybe-install-info-diff install-info-diff
maybe-install-info-diff:

.PHONY: maybe-install-pdf-diff install-pdf-diff
maybe-install-pdf-diff:

.PHONY: maybe-install-html-diff install-html-diff
maybe-install-html-diff:

.PHONY: maybe-installcheck-diff installcheck-diff
maybe-installcheck-diff:

.PHONY: maybe-mostlyclean-diff mostlyclean-diff
maybe-mostlyclean-diff:

.PHONY: maybe-clean-diff clean-diff
maybe-clean-diff:

.PHONY: maybe-distclean-diff distclean-diff
maybe-distclean-diff:

.PHONY: maybe-maintainer-clean-diff maintainer-clean-diff
maybe-maintainer-clean-diff:



.PHONY: configure-dosutils maybe-configure-dosutils
maybe-configure-dosutils:
configure-dosutils: stage_current





.PHONY: all-dosutils maybe-all-dosutils
maybe-all-dosutils:
all-dosutils: stage_current




.PHONY: check-dosutils maybe-check-dosutils
maybe-check-dosutils:

.PHONY: install-dosutils maybe-install-dosutils
maybe-install-dosutils:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-dosutils info-dosutils
maybe-info-dosutils:

.PHONY: maybe-dvi-dosutils dvi-dosutils
maybe-dvi-dosutils:

.PHONY: maybe-pdf-dosutils pdf-dosutils
maybe-pdf-dosutils:

.PHONY: maybe-html-dosutils html-dosutils
maybe-html-dosutils:

.PHONY: maybe-TAGS-dosutils TAGS-dosutils
maybe-TAGS-dosutils:

.PHONY: maybe-install-info-dosutils install-info-dosutils
maybe-install-info-dosutils:

.PHONY: maybe-install-pdf-dosutils install-pdf-dosutils
maybe-install-pdf-dosutils:

.PHONY: maybe-install-html-dosutils install-html-dosutils
maybe-install-html-dosutils:

.PHONY: maybe-installcheck-dosutils installcheck-dosutils
maybe-installcheck-dosutils:

.PHONY: maybe-mostlyclean-dosutils mostlyclean-dosutils
maybe-mostlyclean-dosutils:

.PHONY: maybe-clean-dosutils clean-dosutils
maybe-clean-dosutils:

.PHONY: maybe-distclean-dosutils distclean-dosutils
maybe-distclean-dosutils:

.PHONY: maybe-maintainer-clean-dosutils maintainer-clean-dosutils
maybe-maintainer-clean-dosutils:



.PHONY: configure-etc maybe-configure-etc
maybe-configure-etc:
configure-etc: stage_current





.PHONY: all-etc maybe-all-etc
maybe-all-etc:
all-etc: stage_current




.PHONY: check-etc maybe-check-etc
maybe-check-etc:

.PHONY: install-etc maybe-install-etc
maybe-install-etc:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-etc info-etc
maybe-info-etc:

.PHONY: maybe-dvi-etc dvi-etc
maybe-dvi-etc:

.PHONY: maybe-pdf-etc pdf-etc
maybe-pdf-etc:

.PHONY: maybe-html-etc html-etc
maybe-html-etc:

.PHONY: maybe-TAGS-etc TAGS-etc
maybe-TAGS-etc:

.PHONY: maybe-install-info-etc install-info-etc
maybe-install-info-etc:

.PHONY: maybe-install-pdf-etc install-pdf-etc
maybe-install-pdf-etc:

.PHONY: maybe-install-html-etc install-html-etc
maybe-install-html-etc:

.PHONY: maybe-installcheck-etc installcheck-etc
maybe-installcheck-etc:

.PHONY: maybe-mostlyclean-etc mostlyclean-etc
maybe-mostlyclean-etc:

.PHONY: maybe-clean-etc clean-etc
maybe-clean-etc:

.PHONY: maybe-distclean-etc distclean-etc
maybe-distclean-etc:

.PHONY: maybe-maintainer-clean-etc maintainer-clean-etc
maybe-maintainer-clean-etc:



.PHONY: configure-fastjar maybe-configure-fastjar
maybe-configure-fastjar:
configure-fastjar: stage_current





.PHONY: all-fastjar maybe-all-fastjar
maybe-all-fastjar:
all-fastjar: stage_current




.PHONY: check-fastjar maybe-check-fastjar
maybe-check-fastjar:

.PHONY: install-fastjar maybe-install-fastjar
maybe-install-fastjar:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-fastjar info-fastjar
maybe-info-fastjar:

.PHONY: maybe-dvi-fastjar dvi-fastjar
maybe-dvi-fastjar:

.PHONY: maybe-pdf-fastjar pdf-fastjar
maybe-pdf-fastjar:

.PHONY: maybe-html-fastjar html-fastjar
maybe-html-fastjar:

.PHONY: maybe-TAGS-fastjar TAGS-fastjar
maybe-TAGS-fastjar:

.PHONY: maybe-install-info-fastjar install-info-fastjar
maybe-install-info-fastjar:

.PHONY: maybe-install-pdf-fastjar install-pdf-fastjar
maybe-install-pdf-fastjar:

.PHONY: maybe-install-html-fastjar install-html-fastjar
maybe-install-html-fastjar:

.PHONY: maybe-installcheck-fastjar installcheck-fastjar
maybe-installcheck-fastjar:

.PHONY: maybe-mostlyclean-fastjar mostlyclean-fastjar
maybe-mostlyclean-fastjar:

.PHONY: maybe-clean-fastjar clean-fastjar
maybe-clean-fastjar:

.PHONY: maybe-distclean-fastjar distclean-fastjar
maybe-distclean-fastjar:

.PHONY: maybe-maintainer-clean-fastjar maintainer-clean-fastjar
maybe-maintainer-clean-fastjar:



.PHONY: configure-fileutils maybe-configure-fileutils
maybe-configure-fileutils:
configure-fileutils: stage_current





.PHONY: all-fileutils maybe-all-fileutils
maybe-all-fileutils:
all-fileutils: stage_current




.PHONY: check-fileutils maybe-check-fileutils
maybe-check-fileutils:

.PHONY: install-fileutils maybe-install-fileutils
maybe-install-fileutils:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-fileutils info-fileutils
maybe-info-fileutils:

.PHONY: maybe-dvi-fileutils dvi-fileutils
maybe-dvi-fileutils:

.PHONY: maybe-pdf-fileutils pdf-fileutils
maybe-pdf-fileutils:

.PHONY: maybe-html-fileutils html-fileutils
maybe-html-fileutils:

.PHONY: maybe-TAGS-fileutils TAGS-fileutils
maybe-TAGS-fileutils:

.PHONY: maybe-install-info-fileutils install-info-fileutils
maybe-install-info-fileutils:

.PHONY: maybe-install-pdf-fileutils install-pdf-fileutils
maybe-install-pdf-fileutils:

.PHONY: maybe-install-html-fileutils install-html-fileutils
maybe-install-html-fileutils:

.PHONY: maybe-installcheck-fileutils installcheck-fileutils
maybe-installcheck-fileutils:

.PHONY: maybe-mostlyclean-fileutils mostlyclean-fileutils
maybe-mostlyclean-fileutils:

.PHONY: maybe-clean-fileutils clean-fileutils
maybe-clean-fileutils:

.PHONY: maybe-distclean-fileutils distclean-fileutils
maybe-distclean-fileutils:

.PHONY: maybe-maintainer-clean-fileutils maintainer-clean-fileutils
maybe-maintainer-clean-fileutils:



.PHONY: configure-findutils maybe-configure-findutils
maybe-configure-findutils:
configure-findutils: stage_current





.PHONY: all-findutils maybe-all-findutils
maybe-all-findutils:
all-findutils: stage_current




.PHONY: check-findutils maybe-check-findutils
maybe-check-findutils:

.PHONY: install-findutils maybe-install-findutils
maybe-install-findutils:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-findutils info-findutils
maybe-info-findutils:

.PHONY: maybe-dvi-findutils dvi-findutils
maybe-dvi-findutils:

.PHONY: maybe-pdf-findutils pdf-findutils
maybe-pdf-findutils:

.PHONY: maybe-html-findutils html-findutils
maybe-html-findutils:

.PHONY: maybe-TAGS-findutils TAGS-findutils
maybe-TAGS-findutils:

.PHONY: maybe-install-info-findutils install-info-findutils
maybe-install-info-findutils:

.PHONY: maybe-install-pdf-findutils install-pdf-findutils
maybe-install-pdf-findutils:

.PHONY: maybe-install-html-findutils install-html-findutils
maybe-install-html-findutils:

.PHONY: maybe-installcheck-findutils installcheck-findutils
maybe-installcheck-findutils:

.PHONY: maybe-mostlyclean-findutils mostlyclean-findutils
maybe-mostlyclean-findutils:

.PHONY: maybe-clean-findutils clean-findutils
maybe-clean-findutils:

.PHONY: maybe-distclean-findutils distclean-findutils
maybe-distclean-findutils:

.PHONY: maybe-maintainer-clean-findutils maintainer-clean-findutils
maybe-maintainer-clean-findutils:



.PHONY: configure-find maybe-configure-find
maybe-configure-find:
configure-find: stage_current





.PHONY: all-find maybe-all-find
maybe-all-find:
all-find: stage_current




.PHONY: check-find maybe-check-find
maybe-check-find:

.PHONY: install-find maybe-install-find
maybe-install-find:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-find info-find
maybe-info-find:

.PHONY: maybe-dvi-find dvi-find
maybe-dvi-find:

.PHONY: maybe-pdf-find pdf-find
maybe-pdf-find:

.PHONY: maybe-html-find html-find
maybe-html-find:

.PHONY: maybe-TAGS-find TAGS-find
maybe-TAGS-find:

.PHONY: maybe-install-info-find install-info-find
maybe-install-info-find:

.PHONY: maybe-install-pdf-find install-pdf-find
maybe-install-pdf-find:

.PHONY: maybe-install-html-find install-html-find
maybe-install-html-find:

.PHONY: maybe-installcheck-find installcheck-find
maybe-installcheck-find:

.PHONY: maybe-mostlyclean-find mostlyclean-find
maybe-mostlyclean-find:

.PHONY: maybe-clean-find clean-find
maybe-clean-find:

.PHONY: maybe-distclean-find distclean-find
maybe-distclean-find:

.PHONY: maybe-maintainer-clean-find maintainer-clean-find
maybe-maintainer-clean-find:



.PHONY: configure-fixincludes maybe-configure-fixincludes
maybe-configure-fixincludes:
configure-fixincludes: stage_current
maybe-configure-fixincludes: configure-fixincludes
configure-fixincludes: 
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/fixincludes/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/fixincludes ; \
	$(HOST_EXPORTS) \
	echo Configuring in $(HOST_SUBDIR)/fixincludes; \
	cd "$(HOST_SUBDIR)/fixincludes" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/fixincludes/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/fixincludes"; \
	libsrcdir="$$s/fixincludes"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1





.PHONY: all-fixincludes maybe-all-fixincludes
maybe-all-fixincludes:
all-fixincludes: stage_current
TARGET-fixincludes=all
maybe-all-fixincludes: all-fixincludes
all-fixincludes: configure-fixincludes
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)  \
		$(TARGET-fixincludes))




.PHONY: check-fixincludes maybe-check-fixincludes
maybe-check-fixincludes:
maybe-check-fixincludes: check-fixincludes

check-fixincludes:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(FLAGS_TO_PASS)  check)


.PHONY: install-fixincludes maybe-install-fixincludes
maybe-install-fixincludes:
maybe-install-fixincludes: install-fixincludes

install-fixincludes: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-fixincludes info-fixincludes
maybe-info-fixincludes:
maybe-info-fixincludes: info-fixincludes

info-fixincludes: \
    configure-fixincludes 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing info in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          info) \
	  || exit 1


.PHONY: maybe-dvi-fixincludes dvi-fixincludes
maybe-dvi-fixincludes:
maybe-dvi-fixincludes: dvi-fixincludes

dvi-fixincludes: \
    configure-fixincludes 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing dvi in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          dvi) \
	  || exit 1


.PHONY: maybe-pdf-fixincludes pdf-fixincludes
maybe-pdf-fixincludes:
maybe-pdf-fixincludes: pdf-fixincludes

pdf-fixincludes: \
    configure-fixincludes 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing pdf in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          pdf) \
	  || exit 1


.PHONY: maybe-html-fixincludes html-fixincludes
maybe-html-fixincludes:
maybe-html-fixincludes: html-fixincludes

html-fixincludes: \
    configure-fixincludes 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing html in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          html) \
	  || exit 1


.PHONY: maybe-TAGS-fixincludes TAGS-fixincludes
maybe-TAGS-fixincludes:
maybe-TAGS-fixincludes: TAGS-fixincludes

# fixincludes doesn't support TAGS.
TAGS-fixincludes:


.PHONY: maybe-install-info-fixincludes install-info-fixincludes
maybe-install-info-fixincludes:
maybe-install-info-fixincludes: install-info-fixincludes

install-info-fixincludes: \
    configure-fixincludes \
    info-fixincludes 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-info in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-fixincludes install-pdf-fixincludes
maybe-install-pdf-fixincludes:
maybe-install-pdf-fixincludes: install-pdf-fixincludes

install-pdf-fixincludes: \
    configure-fixincludes \
    pdf-fixincludes 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-pdf in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-fixincludes install-html-fixincludes
maybe-install-html-fixincludes:
maybe-install-html-fixincludes: install-html-fixincludes

install-html-fixincludes: \
    configure-fixincludes \
    html-fixincludes 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-html in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-html) \
	  || exit 1


.PHONY: maybe-installcheck-fixincludes installcheck-fixincludes
maybe-installcheck-fixincludes:
maybe-installcheck-fixincludes: installcheck-fixincludes

installcheck-fixincludes: \
    configure-fixincludes 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing installcheck in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-fixincludes mostlyclean-fixincludes
maybe-mostlyclean-fixincludes:
maybe-mostlyclean-fixincludes: mostlyclean-fixincludes

mostlyclean-fixincludes: 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing mostlyclean in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-fixincludes clean-fixincludes
maybe-clean-fixincludes:
maybe-clean-fixincludes: clean-fixincludes

clean-fixincludes: 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing clean in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          clean) \
	  || exit 1


.PHONY: maybe-distclean-fixincludes distclean-fixincludes
maybe-distclean-fixincludes:
maybe-distclean-fixincludes: distclean-fixincludes

distclean-fixincludes: 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing distclean in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-fixincludes maintainer-clean-fixincludes
maybe-maintainer-clean-fixincludes:
maybe-maintainer-clean-fixincludes: maintainer-clean-fixincludes

maintainer-clean-fixincludes: 
	@: $(MAKE); $(unstage)
	@[ -f ./fixincludes/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing maintainer-clean in fixincludes" ; \
	(cd $(HOST_SUBDIR)/fixincludes && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          maintainer-clean) \
	  || exit 1




.PHONY: configure-flex maybe-configure-flex
maybe-configure-flex:
configure-flex: stage_current





.PHONY: all-flex maybe-all-flex
maybe-all-flex:
all-flex: stage_current




.PHONY: check-flex maybe-check-flex
maybe-check-flex:

.PHONY: install-flex maybe-install-flex
maybe-install-flex:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-flex info-flex
maybe-info-flex:

.PHONY: maybe-dvi-flex dvi-flex
maybe-dvi-flex:

.PHONY: maybe-pdf-flex pdf-flex
maybe-pdf-flex:

.PHONY: maybe-html-flex html-flex
maybe-html-flex:

.PHONY: maybe-TAGS-flex TAGS-flex
maybe-TAGS-flex:

.PHONY: maybe-install-info-flex install-info-flex
maybe-install-info-flex:

.PHONY: maybe-install-pdf-flex install-pdf-flex
maybe-install-pdf-flex:

.PHONY: maybe-install-html-flex install-html-flex
maybe-install-html-flex:

.PHONY: maybe-installcheck-flex installcheck-flex
maybe-installcheck-flex:

.PHONY: maybe-mostlyclean-flex mostlyclean-flex
maybe-mostlyclean-flex:

.PHONY: maybe-clean-flex clean-flex
maybe-clean-flex:

.PHONY: maybe-distclean-flex distclean-flex
maybe-distclean-flex:

.PHONY: maybe-maintainer-clean-flex maintainer-clean-flex
maybe-maintainer-clean-flex:



.PHONY: configure-gas maybe-configure-gas
maybe-configure-gas:
configure-gas: stage_current



.PHONY: configure-stage1-gas maybe-configure-stage1-gas
maybe-configure-stage1-gas:

.PHONY: configure-stage2-gas maybe-configure-stage2-gas
maybe-configure-stage2-gas:

.PHONY: configure-stageb2g0-gas maybe-configure-stageb2g0-gas
maybe-configure-stageb2g0-gas:

.PHONY: configure-stage3-gas maybe-configure-stage3-gas
maybe-configure-stage3-gas:

.PHONY: configure-stageb3g2-gas maybe-configure-stageb3g2-gas
maybe-configure-stageb3g2-gas:

.PHONY: configure-stage4-gas maybe-configure-stage4-gas
maybe-configure-stage4-gas:

.PHONY: configure-stageprofile-gas maybe-configure-stageprofile-gas
maybe-configure-stageprofile-gas:

.PHONY: configure-stagefeedback-gas maybe-configure-stagefeedback-gas
maybe-configure-stagefeedback-gas:





.PHONY: all-gas maybe-all-gas
maybe-all-gas:
all-gas: stage_current



.PHONY: all-stage1-gas maybe-all-stage1-gas
.PHONY: clean-stage1-gas maybe-clean-stage1-gas
maybe-all-stage1-gas:
maybe-clean-stage1-gas:


.PHONY: all-stage2-gas maybe-all-stage2-gas
.PHONY: clean-stage2-gas maybe-clean-stage2-gas
maybe-all-stage2-gas:
maybe-clean-stage2-gas:


.PHONY: all-stageb2g0-gas maybe-all-stageb2g0-gas
.PHONY: clean-stageb2g0-gas maybe-clean-stageb2g0-gas
maybe-all-stageb2g0-gas:
maybe-clean-stageb2g0-gas:


.PHONY: all-stage3-gas maybe-all-stage3-gas
.PHONY: clean-stage3-gas maybe-clean-stage3-gas
maybe-all-stage3-gas:
maybe-clean-stage3-gas:


.PHONY: all-stageb3g2-gas maybe-all-stageb3g2-gas
.PHONY: clean-stageb3g2-gas maybe-clean-stageb3g2-gas
maybe-all-stageb3g2-gas:
maybe-clean-stageb3g2-gas:


.PHONY: all-stage4-gas maybe-all-stage4-gas
.PHONY: clean-stage4-gas maybe-clean-stage4-gas
maybe-all-stage4-gas:
maybe-clean-stage4-gas:


.PHONY: all-stageprofile-gas maybe-all-stageprofile-gas
.PHONY: clean-stageprofile-gas maybe-clean-stageprofile-gas
maybe-all-stageprofile-gas:
maybe-clean-stageprofile-gas:


.PHONY: all-stagefeedback-gas maybe-all-stagefeedback-gas
.PHONY: clean-stagefeedback-gas maybe-clean-stagefeedback-gas
maybe-all-stagefeedback-gas:
maybe-clean-stagefeedback-gas:





.PHONY: check-gas maybe-check-gas
maybe-check-gas:

.PHONY: install-gas maybe-install-gas
maybe-install-gas:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gas info-gas
maybe-info-gas:

.PHONY: maybe-dvi-gas dvi-gas
maybe-dvi-gas:

.PHONY: maybe-pdf-gas pdf-gas
maybe-pdf-gas:

.PHONY: maybe-html-gas html-gas
maybe-html-gas:

.PHONY: maybe-TAGS-gas TAGS-gas
maybe-TAGS-gas:

.PHONY: maybe-install-info-gas install-info-gas
maybe-install-info-gas:

.PHONY: maybe-install-pdf-gas install-pdf-gas
maybe-install-pdf-gas:

.PHONY: maybe-install-html-gas install-html-gas
maybe-install-html-gas:

.PHONY: maybe-installcheck-gas installcheck-gas
maybe-installcheck-gas:

.PHONY: maybe-mostlyclean-gas mostlyclean-gas
maybe-mostlyclean-gas:

.PHONY: maybe-clean-gas clean-gas
maybe-clean-gas:

.PHONY: maybe-distclean-gas distclean-gas
maybe-distclean-gas:

.PHONY: maybe-maintainer-clean-gas maintainer-clean-gas
maybe-maintainer-clean-gas:



.PHONY: configure-gcc maybe-configure-gcc
maybe-configure-gcc:
configure-gcc: stage_current
maybe-configure-gcc: configure-gcc
configure-gcc: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	$(HOST_EXPORTS) \
	echo Configuring in $(HOST_SUBDIR)/gcc; \
	cd "$(HOST_SUBDIR)/gcc" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1



.PHONY: configure-stage1-gcc maybe-configure-stage1-gcc
maybe-configure-stage1-gcc:
maybe-configure-stage1-gcc: configure-stage1-gcc
configure-stage1-gcc:
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(HOST_EXPORTS)  \
	CFLAGS="$(STAGE1_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE1_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 1 in $(HOST_SUBDIR)/gcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	cd $(HOST_SUBDIR)/gcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	   \
	  --disable-intermodule $(STAGE1_CHECKING) 	  --disable-coverage --enable-languages="$(STAGE1_LANGUAGES)" 

.PHONY: configure-stage2-gcc maybe-configure-stage2-gcc
maybe-configure-stage2-gcc:
maybe-configure-stage2-gcc: configure-stage2-gcc
configure-stage2-gcc:
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 2 in $(HOST_SUBDIR)/gcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	cd $(HOST_SUBDIR)/gcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb2g0-gcc maybe-configure-stageb2g0-gcc
maybe-configure-stageb2g0-gcc:
maybe-configure-stageb2g0-gcc: configure-stageb2g0-gcc
configure-stageb2g0-gcc:
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -g0"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -g0"; export CXXFLAGS;  \
	echo Configuring stage b2g0 in $(HOST_SUBDIR)/gcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	cd $(HOST_SUBDIR)/gcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage3-gcc maybe-configure-stage3-gcc
maybe-configure-stage3-gcc:
maybe-configure-stage3-gcc: configure-stage3-gcc
configure-stage3-gcc:
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 3 in $(HOST_SUBDIR)/gcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	cd $(HOST_SUBDIR)/gcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb3g2-gcc maybe-configure-stageb3g2-gcc
maybe-configure-stageb3g2-gcc:
maybe-configure-stageb3g2-gcc: configure-stageb3g2-gcc
configure-stageb3g2-gcc:
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -g2"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -g2"; export CXXFLAGS;  \
	echo Configuring stage b3g2 in $(HOST_SUBDIR)/gcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	cd $(HOST_SUBDIR)/gcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage4-gcc maybe-configure-stage4-gcc
maybe-configure-stage4-gcc:
maybe-configure-stage4-gcc: configure-stage4-gcc
configure-stage4-gcc:
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE4_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE4_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 4 in $(HOST_SUBDIR)/gcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	cd $(HOST_SUBDIR)/gcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageprofile-gcc maybe-configure-stageprofile-gcc
maybe-configure-stageprofile-gcc:
maybe-configure-stageprofile-gcc: configure-stageprofile-gcc
configure-stageprofile-gcc:
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CXXFLAGS;  \
	echo Configuring stage profile in $(HOST_SUBDIR)/gcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	cd $(HOST_SUBDIR)/gcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stagefeedback-gcc maybe-configure-stagefeedback-gcc
maybe-configure-stagefeedback-gcc:
maybe-configure-stagefeedback-gcc: configure-stagefeedback-gcc
configure-stagefeedback-gcc:
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gcc/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CXXFLAGS;  \
	echo Configuring stage feedback in $(HOST_SUBDIR)/gcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gcc ; \
	cd $(HOST_SUBDIR)/gcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gcc"; \
	libsrcdir="$$s/gcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   





.PHONY: all-gcc maybe-all-gcc
maybe-all-gcc:
all-gcc: stage_current
TARGET-gcc=all
maybe-all-gcc: all-gcc
all-gcc: configure-gcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS) \
		$(TARGET-gcc))



.PHONY: all-stage1-gcc maybe-all-stage1-gcc
.PHONY: clean-stage1-gcc maybe-clean-stage1-gcc
maybe-all-stage1-gcc:
maybe-clean-stage1-gcc:
maybe-all-stage1-gcc: all-stage1-gcc
all-stage1: all-stage1-gcc
TARGET-stage1-gcc = $(TARGET-gcc)
all-stage1-gcc: configure-stage1-gcc
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE1_CFLAGS)" CXXFLAGS="$(STAGE1_CFLAGS)" \
		LIBCFLAGS="$(STAGE1_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" $(EXTRA_HOST_FLAGS)  $(EXTRA_GCC_FLAGS) \
		$(TARGET-stage1-gcc)

maybe-clean-stage1-gcc: clean-stage1-gcc
clean-stage1: clean-stage1-gcc
clean-stage1-gcc:
	@if [ $(current_stage) = stage1 ]; then \
	  [ -f $(HOST_SUBDIR)/gcc/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage1-gcc/Makefile ] || exit 0; \
	  $(MAKE) stage1-start; \
	fi; \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(EXTRA_GCC_FLAGS) clean


.PHONY: all-stage2-gcc maybe-all-stage2-gcc
.PHONY: clean-stage2-gcc maybe-clean-stage2-gcc
maybe-all-stage2-gcc:
maybe-clean-stage2-gcc:
maybe-all-stage2-gcc: all-stage2-gcc
all-stage2: all-stage2-gcc
TARGET-stage2-gcc = $(TARGET-gcc)
all-stage2-gcc: configure-stage2-gcc
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS)" CXXFLAGS="$(STAGE2_CFLAGS)" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) \
		$(TARGET-stage2-gcc)

maybe-clean-stage2-gcc: clean-stage2-gcc
clean-stage2: clean-stage2-gcc
clean-stage2-gcc:
	@if [ $(current_stage) = stage2 ]; then \
	  [ -f $(HOST_SUBDIR)/gcc/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage2-gcc/Makefile ] || exit 0; \
	  $(MAKE) stage2-start; \
	fi; \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(EXTRA_GCC_FLAGS) clean


.PHONY: all-stageb2g0-gcc maybe-all-stageb2g0-gcc
.PHONY: clean-stageb2g0-gcc maybe-clean-stageb2g0-gcc
maybe-all-stageb2g0-gcc:
maybe-clean-stageb2g0-gcc:
maybe-all-stageb2g0-gcc: all-stageb2g0-gcc
all-stageb2g0: all-stageb2g0-gcc
TARGET-stageb2g0-gcc = $(TARGET-gcc)
all-stageb2g0-gcc: configure-stageb2g0-gcc
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -g0" CXXFLAGS="$(STAGE2_CFLAGS) -g0" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS) -g0" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) \
		$(TARGET-stageb2g0-gcc)

maybe-clean-stageb2g0-gcc: clean-stageb2g0-gcc
clean-stageb2g0: clean-stageb2g0-gcc
clean-stageb2g0-gcc:
	@if [ $(current_stage) = stageb2g0 ]; then \
	  [ -f $(HOST_SUBDIR)/gcc/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb2g0-gcc/Makefile ] || exit 0; \
	  $(MAKE) stageb2g0-start; \
	fi; \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(EXTRA_GCC_FLAGS) clean


.PHONY: all-stage3-gcc maybe-all-stage3-gcc
.PHONY: clean-stage3-gcc maybe-clean-stage3-gcc
maybe-all-stage3-gcc:
maybe-clean-stage3-gcc:
maybe-all-stage3-gcc: all-stage3-gcc
all-stage3: all-stage3-gcc
TARGET-stage3-gcc = $(TARGET-gcc)
all-stage3-gcc: configure-stage3-gcc
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS)" CXXFLAGS="$(STAGE3_CFLAGS)" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) \
		$(TARGET-stage3-gcc)

maybe-clean-stage3-gcc: clean-stage3-gcc
clean-stage3: clean-stage3-gcc
clean-stage3-gcc:
	@if [ $(current_stage) = stage3 ]; then \
	  [ -f $(HOST_SUBDIR)/gcc/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage3-gcc/Makefile ] || exit 0; \
	  $(MAKE) stage3-start; \
	fi; \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(EXTRA_GCC_FLAGS) clean


.PHONY: all-stageb3g2-gcc maybe-all-stageb3g2-gcc
.PHONY: clean-stageb3g2-gcc maybe-clean-stageb3g2-gcc
maybe-all-stageb3g2-gcc:
maybe-clean-stageb3g2-gcc:
maybe-all-stageb3g2-gcc: all-stageb3g2-gcc
all-stageb3g2: all-stageb3g2-gcc
TARGET-stageb3g2-gcc = $(TARGET-gcc)
all-stageb3g2-gcc: configure-stageb3g2-gcc
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -g2" CXXFLAGS="$(STAGE3_CFLAGS) -g2" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -g2" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) \
		$(TARGET-stageb3g2-gcc)

maybe-clean-stageb3g2-gcc: clean-stageb3g2-gcc
clean-stageb3g2: clean-stageb3g2-gcc
clean-stageb3g2-gcc:
	@if [ $(current_stage) = stageb3g2 ]; then \
	  [ -f $(HOST_SUBDIR)/gcc/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb3g2-gcc/Makefile ] || exit 0; \
	  $(MAKE) stageb3g2-start; \
	fi; \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(EXTRA_GCC_FLAGS) clean


.PHONY: all-stage4-gcc maybe-all-stage4-gcc
.PHONY: clean-stage4-gcc maybe-clean-stage4-gcc
maybe-all-stage4-gcc:
maybe-clean-stage4-gcc:
maybe-all-stage4-gcc: all-stage4-gcc
all-stage4: all-stage4-gcc
TARGET-stage4-gcc = $(TARGET-gcc)
all-stage4-gcc: configure-stage4-gcc
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE4_CFLAGS)" CXXFLAGS="$(STAGE4_CFLAGS)" \
		LIBCFLAGS="$(STAGE4_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) \
		$(TARGET-stage4-gcc)

maybe-clean-stage4-gcc: clean-stage4-gcc
clean-stage4: clean-stage4-gcc
clean-stage4-gcc:
	@if [ $(current_stage) = stage4 ]; then \
	  [ -f $(HOST_SUBDIR)/gcc/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage4-gcc/Makefile ] || exit 0; \
	  $(MAKE) stage4-start; \
	fi; \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(EXTRA_GCC_FLAGS) clean


.PHONY: all-stageprofile-gcc maybe-all-stageprofile-gcc
.PHONY: clean-stageprofile-gcc maybe-clean-stageprofile-gcc
maybe-all-stageprofile-gcc:
maybe-clean-stageprofile-gcc:
maybe-all-stageprofile-gcc: all-stageprofile-gcc
all-stageprofile: all-stageprofile-gcc
TARGET-stageprofile-gcc = $(TARGET-gcc)
all-stageprofile-gcc: configure-stageprofile-gcc
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) \
		$(TARGET-stageprofile-gcc)

maybe-clean-stageprofile-gcc: clean-stageprofile-gcc
clean-stageprofile: clean-stageprofile-gcc
clean-stageprofile-gcc:
	@if [ $(current_stage) = stageprofile ]; then \
	  [ -f $(HOST_SUBDIR)/gcc/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageprofile-gcc/Makefile ] || exit 0; \
	  $(MAKE) stageprofile-start; \
	fi; \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(EXTRA_GCC_FLAGS) clean


.PHONY: all-stagefeedback-gcc maybe-all-stagefeedback-gcc
.PHONY: clean-stagefeedback-gcc maybe-clean-stagefeedback-gcc
maybe-all-stagefeedback-gcc:
maybe-clean-stagefeedback-gcc:
maybe-all-stagefeedback-gcc: all-stagefeedback-gcc
all-stagefeedback: all-stagefeedback-gcc
TARGET-stagefeedback-gcc = $(TARGET-gcc)
all-stagefeedback-gcc: configure-stagefeedback-gcc
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -fprofile-use" CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) \
		$(TARGET-stagefeedback-gcc)

maybe-clean-stagefeedback-gcc: clean-stagefeedback-gcc
clean-stagefeedback: clean-stagefeedback-gcc
clean-stagefeedback-gcc:
	@if [ $(current_stage) = stagefeedback ]; then \
	  [ -f $(HOST_SUBDIR)/gcc/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stagefeedback-gcc/Makefile ] || exit 0; \
	  $(MAKE) stagefeedback-start; \
	fi; \
	cd $(HOST_SUBDIR)/gcc && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(EXTRA_GCC_FLAGS) clean





.PHONY: check-gcc maybe-check-gcc
maybe-check-gcc:
maybe-check-gcc: check-gcc

check-gcc:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) check)


.PHONY: install-gcc maybe-install-gcc
maybe-install-gcc:
maybe-install-gcc: install-gcc

install-gcc: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS) install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gcc info-gcc
maybe-info-gcc:
maybe-info-gcc: info-gcc

info-gcc: \
    configure-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing info in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          info) \
	  || exit 1


.PHONY: maybe-dvi-gcc dvi-gcc
maybe-dvi-gcc:
maybe-dvi-gcc: dvi-gcc

dvi-gcc: \
    configure-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing dvi in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          dvi) \
	  || exit 1


.PHONY: maybe-pdf-gcc pdf-gcc
maybe-pdf-gcc:
maybe-pdf-gcc: pdf-gcc

pdf-gcc: \
    configure-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing pdf in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          pdf) \
	  || exit 1


.PHONY: maybe-html-gcc html-gcc
maybe-html-gcc:
maybe-html-gcc: html-gcc

html-gcc: \
    configure-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing html in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          html) \
	  || exit 1


.PHONY: maybe-TAGS-gcc TAGS-gcc
maybe-TAGS-gcc:
maybe-TAGS-gcc: TAGS-gcc

TAGS-gcc: \
    configure-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing TAGS in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          TAGS) \
	  || exit 1


.PHONY: maybe-install-info-gcc install-info-gcc
maybe-install-info-gcc:
maybe-install-info-gcc: install-info-gcc

install-info-gcc: \
    configure-gcc \
    info-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-info in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-gcc install-pdf-gcc
maybe-install-pdf-gcc:
maybe-install-pdf-gcc: install-pdf-gcc

install-pdf-gcc: \
    configure-gcc \
    pdf-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-pdf in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-gcc install-html-gcc
maybe-install-html-gcc:
maybe-install-html-gcc: install-html-gcc

install-html-gcc: \
    configure-gcc \
    html-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-html in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-html) \
	  || exit 1


.PHONY: maybe-installcheck-gcc installcheck-gcc
maybe-installcheck-gcc:
maybe-installcheck-gcc: installcheck-gcc

installcheck-gcc: \
    configure-gcc 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing installcheck in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-gcc mostlyclean-gcc
maybe-mostlyclean-gcc:
maybe-mostlyclean-gcc: mostlyclean-gcc

mostlyclean-gcc: 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing mostlyclean in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-gcc clean-gcc
maybe-clean-gcc:
maybe-clean-gcc: clean-gcc

clean-gcc: 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing clean in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          clean) \
	  || exit 1


.PHONY: maybe-distclean-gcc distclean-gcc
maybe-distclean-gcc:
maybe-distclean-gcc: distclean-gcc

distclean-gcc: 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing distclean in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-gcc maintainer-clean-gcc
maybe-maintainer-clean-gcc:
maybe-maintainer-clean-gcc: maintainer-clean-gcc

maintainer-clean-gcc: 
	@[ -f ./gcc/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) $(EXTRA_GCC_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing maintainer-clean in gcc" ; \
	(cd $(HOST_SUBDIR)/gcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          maintainer-clean) \
	  || exit 1




.PHONY: configure-gawk maybe-configure-gawk
maybe-configure-gawk:
configure-gawk: stage_current





.PHONY: all-gawk maybe-all-gawk
maybe-all-gawk:
all-gawk: stage_current




.PHONY: check-gawk maybe-check-gawk
maybe-check-gawk:

.PHONY: install-gawk maybe-install-gawk
maybe-install-gawk:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gawk info-gawk
maybe-info-gawk:

.PHONY: maybe-dvi-gawk dvi-gawk
maybe-dvi-gawk:

.PHONY: maybe-pdf-gawk pdf-gawk
maybe-pdf-gawk:

.PHONY: maybe-html-gawk html-gawk
maybe-html-gawk:

.PHONY: maybe-TAGS-gawk TAGS-gawk
maybe-TAGS-gawk:

.PHONY: maybe-install-info-gawk install-info-gawk
maybe-install-info-gawk:

.PHONY: maybe-install-pdf-gawk install-pdf-gawk
maybe-install-pdf-gawk:

.PHONY: maybe-install-html-gawk install-html-gawk
maybe-install-html-gawk:

.PHONY: maybe-installcheck-gawk installcheck-gawk
maybe-installcheck-gawk:

.PHONY: maybe-mostlyclean-gawk mostlyclean-gawk
maybe-mostlyclean-gawk:

.PHONY: maybe-clean-gawk clean-gawk
maybe-clean-gawk:

.PHONY: maybe-distclean-gawk distclean-gawk
maybe-distclean-gawk:

.PHONY: maybe-maintainer-clean-gawk maintainer-clean-gawk
maybe-maintainer-clean-gawk:



.PHONY: configure-gettext maybe-configure-gettext
maybe-configure-gettext:
configure-gettext: stage_current





.PHONY: all-gettext maybe-all-gettext
maybe-all-gettext:
all-gettext: stage_current




.PHONY: check-gettext maybe-check-gettext
maybe-check-gettext:

.PHONY: install-gettext maybe-install-gettext
maybe-install-gettext:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gettext info-gettext
maybe-info-gettext:

.PHONY: maybe-dvi-gettext dvi-gettext
maybe-dvi-gettext:

.PHONY: maybe-pdf-gettext pdf-gettext
maybe-pdf-gettext:

.PHONY: maybe-html-gettext html-gettext
maybe-html-gettext:

.PHONY: maybe-TAGS-gettext TAGS-gettext
maybe-TAGS-gettext:

.PHONY: maybe-install-info-gettext install-info-gettext
maybe-install-info-gettext:

.PHONY: maybe-install-pdf-gettext install-pdf-gettext
maybe-install-pdf-gettext:

.PHONY: maybe-install-html-gettext install-html-gettext
maybe-install-html-gettext:

.PHONY: maybe-installcheck-gettext installcheck-gettext
maybe-installcheck-gettext:

.PHONY: maybe-mostlyclean-gettext mostlyclean-gettext
maybe-mostlyclean-gettext:

.PHONY: maybe-clean-gettext clean-gettext
maybe-clean-gettext:

.PHONY: maybe-distclean-gettext distclean-gettext
maybe-distclean-gettext:

.PHONY: maybe-maintainer-clean-gettext maintainer-clean-gettext
maybe-maintainer-clean-gettext:



.PHONY: configure-gmp maybe-configure-gmp
maybe-configure-gmp:
configure-gmp: stage_current
maybe-configure-gmp: configure-gmp
configure-gmp: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	$(HOST_EXPORTS) \
	echo Configuring in $(HOST_SUBDIR)/gmp; \
	cd "$(HOST_SUBDIR)/gmp" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} --disable-shared \
	  || exit 1



.PHONY: configure-stage1-gmp maybe-configure-stage1-gmp
maybe-configure-stage1-gmp:
maybe-configure-stage1-gmp: configure-stage1-gmp
configure-stage1-gmp:
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(HOST_EXPORTS)  \
	CFLAGS="$(STAGE1_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE1_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 1 in $(HOST_SUBDIR)/gmp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	cd $(HOST_SUBDIR)/gmp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	   \
	  --disable-intermodule $(STAGE1_CHECKING) 	  --disable-coverage --enable-languages="$(STAGE1_LANGUAGES)" --disable-shared

.PHONY: configure-stage2-gmp maybe-configure-stage2-gmp
maybe-configure-stage2-gmp:
maybe-configure-stage2-gmp: configure-stage2-gmp
configure-stage2-gmp:
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 2 in $(HOST_SUBDIR)/gmp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	cd $(HOST_SUBDIR)/gmp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared

.PHONY: configure-stageb2g0-gmp maybe-configure-stageb2g0-gmp
maybe-configure-stageb2g0-gmp:
maybe-configure-stageb2g0-gmp: configure-stageb2g0-gmp
configure-stageb2g0-gmp:
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -g0"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -g0"; export CXXFLAGS;  \
	echo Configuring stage b2g0 in $(HOST_SUBDIR)/gmp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	cd $(HOST_SUBDIR)/gmp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared

.PHONY: configure-stage3-gmp maybe-configure-stage3-gmp
maybe-configure-stage3-gmp:
maybe-configure-stage3-gmp: configure-stage3-gmp
configure-stage3-gmp:
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 3 in $(HOST_SUBDIR)/gmp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	cd $(HOST_SUBDIR)/gmp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared

.PHONY: configure-stageb3g2-gmp maybe-configure-stageb3g2-gmp
maybe-configure-stageb3g2-gmp:
maybe-configure-stageb3g2-gmp: configure-stageb3g2-gmp
configure-stageb3g2-gmp:
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -g2"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -g2"; export CXXFLAGS;  \
	echo Configuring stage b3g2 in $(HOST_SUBDIR)/gmp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	cd $(HOST_SUBDIR)/gmp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared

.PHONY: configure-stage4-gmp maybe-configure-stage4-gmp
maybe-configure-stage4-gmp:
maybe-configure-stage4-gmp: configure-stage4-gmp
configure-stage4-gmp:
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE4_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE4_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 4 in $(HOST_SUBDIR)/gmp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	cd $(HOST_SUBDIR)/gmp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared

.PHONY: configure-stageprofile-gmp maybe-configure-stageprofile-gmp
maybe-configure-stageprofile-gmp:
maybe-configure-stageprofile-gmp: configure-stageprofile-gmp
configure-stageprofile-gmp:
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CXXFLAGS;  \
	echo Configuring stage profile in $(HOST_SUBDIR)/gmp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	cd $(HOST_SUBDIR)/gmp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared

.PHONY: configure-stagefeedback-gmp maybe-configure-stagefeedback-gmp
maybe-configure-stagefeedback-gmp:
maybe-configure-stagefeedback-gmp: configure-stagefeedback-gmp
configure-stagefeedback-gmp:
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/gmp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CXXFLAGS;  \
	echo Configuring stage feedback in $(HOST_SUBDIR)/gmp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/gmp ; \
	cd $(HOST_SUBDIR)/gmp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/gmp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/gmp"; \
	libsrcdir="$$s/gmp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared





.PHONY: all-gmp maybe-all-gmp
maybe-all-gmp:
all-gmp: stage_current
TARGET-gmp=all
maybe-all-gmp: all-gmp
all-gmp: configure-gmp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)  \
		$(TARGET-gmp))



.PHONY: all-stage1-gmp maybe-all-stage1-gmp
.PHONY: clean-stage1-gmp maybe-clean-stage1-gmp
maybe-all-stage1-gmp:
maybe-clean-stage1-gmp:
maybe-all-stage1-gmp: all-stage1-gmp
all-stage1: all-stage1-gmp
TARGET-stage1-gmp = $(TARGET-gmp)
all-stage1-gmp: configure-stage1-gmp
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE1_CFLAGS)" CXXFLAGS="$(STAGE1_CFLAGS)" \
		LIBCFLAGS="$(STAGE1_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" $(EXTRA_HOST_FLAGS)   \
		$(TARGET-stage1-gmp)

maybe-clean-stage1-gmp: clean-stage1-gmp
clean-stage1: clean-stage1-gmp
clean-stage1-gmp:
	@if [ $(current_stage) = stage1 ]; then \
	  [ -f $(HOST_SUBDIR)/gmp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage1-gmp/Makefile ] || exit 0; \
	  $(MAKE) stage1-start; \
	fi; \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		 clean


.PHONY: all-stage2-gmp maybe-all-stage2-gmp
.PHONY: clean-stage2-gmp maybe-clean-stage2-gmp
maybe-all-stage2-gmp:
maybe-clean-stage2-gmp:
maybe-all-stage2-gmp: all-stage2-gmp
all-stage2: all-stage2-gmp
TARGET-stage2-gmp = $(TARGET-gmp)
all-stage2-gmp: configure-stage2-gmp
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS)" CXXFLAGS="$(STAGE2_CFLAGS)" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage2-gmp)

maybe-clean-stage2-gmp: clean-stage2-gmp
clean-stage2: clean-stage2-gmp
clean-stage2-gmp:
	@if [ $(current_stage) = stage2 ]; then \
	  [ -f $(HOST_SUBDIR)/gmp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage2-gmp/Makefile ] || exit 0; \
	  $(MAKE) stage2-start; \
	fi; \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb2g0-gmp maybe-all-stageb2g0-gmp
.PHONY: clean-stageb2g0-gmp maybe-clean-stageb2g0-gmp
maybe-all-stageb2g0-gmp:
maybe-clean-stageb2g0-gmp:
maybe-all-stageb2g0-gmp: all-stageb2g0-gmp
all-stageb2g0: all-stageb2g0-gmp
TARGET-stageb2g0-gmp = $(TARGET-gmp)
all-stageb2g0-gmp: configure-stageb2g0-gmp
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -g0" CXXFLAGS="$(STAGE2_CFLAGS) -g0" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS) -g0" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb2g0-gmp)

maybe-clean-stageb2g0-gmp: clean-stageb2g0-gmp
clean-stageb2g0: clean-stageb2g0-gmp
clean-stageb2g0-gmp:
	@if [ $(current_stage) = stageb2g0 ]; then \
	  [ -f $(HOST_SUBDIR)/gmp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb2g0-gmp/Makefile ] || exit 0; \
	  $(MAKE) stageb2g0-start; \
	fi; \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage3-gmp maybe-all-stage3-gmp
.PHONY: clean-stage3-gmp maybe-clean-stage3-gmp
maybe-all-stage3-gmp:
maybe-clean-stage3-gmp:
maybe-all-stage3-gmp: all-stage3-gmp
all-stage3: all-stage3-gmp
TARGET-stage3-gmp = $(TARGET-gmp)
all-stage3-gmp: configure-stage3-gmp
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS)" CXXFLAGS="$(STAGE3_CFLAGS)" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage3-gmp)

maybe-clean-stage3-gmp: clean-stage3-gmp
clean-stage3: clean-stage3-gmp
clean-stage3-gmp:
	@if [ $(current_stage) = stage3 ]; then \
	  [ -f $(HOST_SUBDIR)/gmp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage3-gmp/Makefile ] || exit 0; \
	  $(MAKE) stage3-start; \
	fi; \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb3g2-gmp maybe-all-stageb3g2-gmp
.PHONY: clean-stageb3g2-gmp maybe-clean-stageb3g2-gmp
maybe-all-stageb3g2-gmp:
maybe-clean-stageb3g2-gmp:
maybe-all-stageb3g2-gmp: all-stageb3g2-gmp
all-stageb3g2: all-stageb3g2-gmp
TARGET-stageb3g2-gmp = $(TARGET-gmp)
all-stageb3g2-gmp: configure-stageb3g2-gmp
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -g2" CXXFLAGS="$(STAGE3_CFLAGS) -g2" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -g2" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb3g2-gmp)

maybe-clean-stageb3g2-gmp: clean-stageb3g2-gmp
clean-stageb3g2: clean-stageb3g2-gmp
clean-stageb3g2-gmp:
	@if [ $(current_stage) = stageb3g2 ]; then \
	  [ -f $(HOST_SUBDIR)/gmp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb3g2-gmp/Makefile ] || exit 0; \
	  $(MAKE) stageb3g2-start; \
	fi; \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage4-gmp maybe-all-stage4-gmp
.PHONY: clean-stage4-gmp maybe-clean-stage4-gmp
maybe-all-stage4-gmp:
maybe-clean-stage4-gmp:
maybe-all-stage4-gmp: all-stage4-gmp
all-stage4: all-stage4-gmp
TARGET-stage4-gmp = $(TARGET-gmp)
all-stage4-gmp: configure-stage4-gmp
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE4_CFLAGS)" CXXFLAGS="$(STAGE4_CFLAGS)" \
		LIBCFLAGS="$(STAGE4_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage4-gmp)

maybe-clean-stage4-gmp: clean-stage4-gmp
clean-stage4: clean-stage4-gmp
clean-stage4-gmp:
	@if [ $(current_stage) = stage4 ]; then \
	  [ -f $(HOST_SUBDIR)/gmp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage4-gmp/Makefile ] || exit 0; \
	  $(MAKE) stage4-start; \
	fi; \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageprofile-gmp maybe-all-stageprofile-gmp
.PHONY: clean-stageprofile-gmp maybe-clean-stageprofile-gmp
maybe-all-stageprofile-gmp:
maybe-clean-stageprofile-gmp:
maybe-all-stageprofile-gmp: all-stageprofile-gmp
all-stageprofile: all-stageprofile-gmp
TARGET-stageprofile-gmp = $(TARGET-gmp)
all-stageprofile-gmp: configure-stageprofile-gmp
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageprofile-gmp)

maybe-clean-stageprofile-gmp: clean-stageprofile-gmp
clean-stageprofile: clean-stageprofile-gmp
clean-stageprofile-gmp:
	@if [ $(current_stage) = stageprofile ]; then \
	  [ -f $(HOST_SUBDIR)/gmp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageprofile-gmp/Makefile ] || exit 0; \
	  $(MAKE) stageprofile-start; \
	fi; \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stagefeedback-gmp maybe-all-stagefeedback-gmp
.PHONY: clean-stagefeedback-gmp maybe-clean-stagefeedback-gmp
maybe-all-stagefeedback-gmp:
maybe-clean-stagefeedback-gmp:
maybe-all-stagefeedback-gmp: all-stagefeedback-gmp
all-stagefeedback: all-stagefeedback-gmp
TARGET-stagefeedback-gmp = $(TARGET-gmp)
all-stagefeedback-gmp: configure-stagefeedback-gmp
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -fprofile-use" CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stagefeedback-gmp)

maybe-clean-stagefeedback-gmp: clean-stagefeedback-gmp
clean-stagefeedback: clean-stagefeedback-gmp
clean-stagefeedback-gmp:
	@if [ $(current_stage) = stagefeedback ]; then \
	  [ -f $(HOST_SUBDIR)/gmp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stagefeedback-gmp/Makefile ] || exit 0; \
	  $(MAKE) stagefeedback-start; \
	fi; \
	cd $(HOST_SUBDIR)/gmp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean





.PHONY: check-gmp maybe-check-gmp
maybe-check-gmp:
maybe-check-gmp: check-gmp

check-gmp:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(FLAGS_TO_PASS)  check)


.PHONY: install-gmp maybe-install-gmp
maybe-install-gmp:
maybe-install-gmp: install-gmp

install-gmp:


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gmp info-gmp
maybe-info-gmp:
maybe-info-gmp: info-gmp

info-gmp: \
    configure-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing info in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          info) \
	  || exit 1


.PHONY: maybe-dvi-gmp dvi-gmp
maybe-dvi-gmp:
maybe-dvi-gmp: dvi-gmp

dvi-gmp: \
    configure-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing dvi in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          dvi) \
	  || exit 1


.PHONY: maybe-pdf-gmp pdf-gmp
maybe-pdf-gmp:
maybe-pdf-gmp: pdf-gmp

pdf-gmp: \
    configure-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing pdf in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          pdf) \
	  || exit 1


.PHONY: maybe-html-gmp html-gmp
maybe-html-gmp:
maybe-html-gmp: html-gmp

html-gmp: \
    configure-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing html in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          html) \
	  || exit 1


.PHONY: maybe-TAGS-gmp TAGS-gmp
maybe-TAGS-gmp:
maybe-TAGS-gmp: TAGS-gmp

TAGS-gmp: \
    configure-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing TAGS in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          TAGS) \
	  || exit 1


.PHONY: maybe-install-info-gmp install-info-gmp
maybe-install-info-gmp:
maybe-install-info-gmp: install-info-gmp

install-info-gmp: \
    configure-gmp \
    info-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-info in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-gmp install-pdf-gmp
maybe-install-pdf-gmp:
maybe-install-pdf-gmp: install-pdf-gmp

install-pdf-gmp: \
    configure-gmp \
    pdf-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-pdf in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-gmp install-html-gmp
maybe-install-html-gmp:
maybe-install-html-gmp: install-html-gmp

install-html-gmp: \
    configure-gmp \
    html-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-html in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-html) \
	  || exit 1


.PHONY: maybe-installcheck-gmp installcheck-gmp
maybe-installcheck-gmp:
maybe-installcheck-gmp: installcheck-gmp

installcheck-gmp: \
    configure-gmp 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing installcheck in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-gmp mostlyclean-gmp
maybe-mostlyclean-gmp:
maybe-mostlyclean-gmp: mostlyclean-gmp

mostlyclean-gmp: 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing mostlyclean in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-gmp clean-gmp
maybe-clean-gmp:
maybe-clean-gmp: clean-gmp

clean-gmp: 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing clean in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          clean) \
	  || exit 1


.PHONY: maybe-distclean-gmp distclean-gmp
maybe-distclean-gmp:
maybe-distclean-gmp: distclean-gmp

distclean-gmp: 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing distclean in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-gmp maintainer-clean-gmp
maybe-maintainer-clean-gmp:
maybe-maintainer-clean-gmp: maintainer-clean-gmp

maintainer-clean-gmp: 
	@[ -f ./gmp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing maintainer-clean in gmp" ; \
	(cd $(HOST_SUBDIR)/gmp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          maintainer-clean) \
	  || exit 1




.PHONY: configure-mpfr maybe-configure-mpfr
maybe-configure-mpfr:
configure-mpfr: stage_current
maybe-configure-mpfr: configure-mpfr
configure-mpfr: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	$(HOST_EXPORTS) \
	echo Configuring in $(HOST_SUBDIR)/mpfr; \
	cd "$(HOST_SUBDIR)/mpfr" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp \
	  || exit 1



.PHONY: configure-stage1-mpfr maybe-configure-stage1-mpfr
maybe-configure-stage1-mpfr:
maybe-configure-stage1-mpfr: configure-stage1-mpfr
configure-stage1-mpfr:
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(HOST_EXPORTS)  \
	CFLAGS="$(STAGE1_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE1_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 1 in $(HOST_SUBDIR)/mpfr ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	cd $(HOST_SUBDIR)/mpfr || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	   \
	  --disable-intermodule $(STAGE1_CHECKING) 	  --disable-coverage --enable-languages="$(STAGE1_LANGUAGES)" --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp

.PHONY: configure-stage2-mpfr maybe-configure-stage2-mpfr
maybe-configure-stage2-mpfr:
maybe-configure-stage2-mpfr: configure-stage2-mpfr
configure-stage2-mpfr:
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 2 in $(HOST_SUBDIR)/mpfr ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	cd $(HOST_SUBDIR)/mpfr || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp

.PHONY: configure-stageb2g0-mpfr maybe-configure-stageb2g0-mpfr
maybe-configure-stageb2g0-mpfr:
maybe-configure-stageb2g0-mpfr: configure-stageb2g0-mpfr
configure-stageb2g0-mpfr:
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -g0"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -g0"; export CXXFLAGS;  \
	echo Configuring stage b2g0 in $(HOST_SUBDIR)/mpfr ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	cd $(HOST_SUBDIR)/mpfr || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp

.PHONY: configure-stage3-mpfr maybe-configure-stage3-mpfr
maybe-configure-stage3-mpfr:
maybe-configure-stage3-mpfr: configure-stage3-mpfr
configure-stage3-mpfr:
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 3 in $(HOST_SUBDIR)/mpfr ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	cd $(HOST_SUBDIR)/mpfr || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp

.PHONY: configure-stageb3g2-mpfr maybe-configure-stageb3g2-mpfr
maybe-configure-stageb3g2-mpfr:
maybe-configure-stageb3g2-mpfr: configure-stageb3g2-mpfr
configure-stageb3g2-mpfr:
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -g2"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -g2"; export CXXFLAGS;  \
	echo Configuring stage b3g2 in $(HOST_SUBDIR)/mpfr ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	cd $(HOST_SUBDIR)/mpfr || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp

.PHONY: configure-stage4-mpfr maybe-configure-stage4-mpfr
maybe-configure-stage4-mpfr:
maybe-configure-stage4-mpfr: configure-stage4-mpfr
configure-stage4-mpfr:
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE4_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE4_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 4 in $(HOST_SUBDIR)/mpfr ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	cd $(HOST_SUBDIR)/mpfr || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp

.PHONY: configure-stageprofile-mpfr maybe-configure-stageprofile-mpfr
maybe-configure-stageprofile-mpfr:
maybe-configure-stageprofile-mpfr: configure-stageprofile-mpfr
configure-stageprofile-mpfr:
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CXXFLAGS;  \
	echo Configuring stage profile in $(HOST_SUBDIR)/mpfr ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	cd $(HOST_SUBDIR)/mpfr || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp

.PHONY: configure-stagefeedback-mpfr maybe-configure-stagefeedback-mpfr
maybe-configure-stagefeedback-mpfr:
maybe-configure-stagefeedback-mpfr: configure-stagefeedback-mpfr
configure-stagefeedback-mpfr:
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/mpfr/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CXXFLAGS;  \
	echo Configuring stage feedback in $(HOST_SUBDIR)/mpfr ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/mpfr ; \
	cd $(HOST_SUBDIR)/mpfr || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/mpfr/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/mpfr"; \
	libsrcdir="$$s/mpfr"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=none-${host_vendor}-${host_os} \
	  --target=none-${host_vendor}-${host_os} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   --disable-shared --with-gmp-build=$$r/$(HOST_SUBDIR)/gmp





.PHONY: all-mpfr maybe-all-mpfr
maybe-all-mpfr:
all-mpfr: stage_current
TARGET-mpfr=all
maybe-all-mpfr: all-mpfr
all-mpfr: configure-mpfr
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)  \
		$(TARGET-mpfr))



.PHONY: all-stage1-mpfr maybe-all-stage1-mpfr
.PHONY: clean-stage1-mpfr maybe-clean-stage1-mpfr
maybe-all-stage1-mpfr:
maybe-clean-stage1-mpfr:
maybe-all-stage1-mpfr: all-stage1-mpfr
all-stage1: all-stage1-mpfr
TARGET-stage1-mpfr = $(TARGET-mpfr)
all-stage1-mpfr: configure-stage1-mpfr
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE1_CFLAGS)" CXXFLAGS="$(STAGE1_CFLAGS)" \
		LIBCFLAGS="$(STAGE1_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" $(EXTRA_HOST_FLAGS)   \
		$(TARGET-stage1-mpfr)

maybe-clean-stage1-mpfr: clean-stage1-mpfr
clean-stage1: clean-stage1-mpfr
clean-stage1-mpfr:
	@if [ $(current_stage) = stage1 ]; then \
	  [ -f $(HOST_SUBDIR)/mpfr/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage1-mpfr/Makefile ] || exit 0; \
	  $(MAKE) stage1-start; \
	fi; \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		 clean


.PHONY: all-stage2-mpfr maybe-all-stage2-mpfr
.PHONY: clean-stage2-mpfr maybe-clean-stage2-mpfr
maybe-all-stage2-mpfr:
maybe-clean-stage2-mpfr:
maybe-all-stage2-mpfr: all-stage2-mpfr
all-stage2: all-stage2-mpfr
TARGET-stage2-mpfr = $(TARGET-mpfr)
all-stage2-mpfr: configure-stage2-mpfr
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS)" CXXFLAGS="$(STAGE2_CFLAGS)" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage2-mpfr)

maybe-clean-stage2-mpfr: clean-stage2-mpfr
clean-stage2: clean-stage2-mpfr
clean-stage2-mpfr:
	@if [ $(current_stage) = stage2 ]; then \
	  [ -f $(HOST_SUBDIR)/mpfr/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage2-mpfr/Makefile ] || exit 0; \
	  $(MAKE) stage2-start; \
	fi; \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb2g0-mpfr maybe-all-stageb2g0-mpfr
.PHONY: clean-stageb2g0-mpfr maybe-clean-stageb2g0-mpfr
maybe-all-stageb2g0-mpfr:
maybe-clean-stageb2g0-mpfr:
maybe-all-stageb2g0-mpfr: all-stageb2g0-mpfr
all-stageb2g0: all-stageb2g0-mpfr
TARGET-stageb2g0-mpfr = $(TARGET-mpfr)
all-stageb2g0-mpfr: configure-stageb2g0-mpfr
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -g0" CXXFLAGS="$(STAGE2_CFLAGS) -g0" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS) -g0" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb2g0-mpfr)

maybe-clean-stageb2g0-mpfr: clean-stageb2g0-mpfr
clean-stageb2g0: clean-stageb2g0-mpfr
clean-stageb2g0-mpfr:
	@if [ $(current_stage) = stageb2g0 ]; then \
	  [ -f $(HOST_SUBDIR)/mpfr/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb2g0-mpfr/Makefile ] || exit 0; \
	  $(MAKE) stageb2g0-start; \
	fi; \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage3-mpfr maybe-all-stage3-mpfr
.PHONY: clean-stage3-mpfr maybe-clean-stage3-mpfr
maybe-all-stage3-mpfr:
maybe-clean-stage3-mpfr:
maybe-all-stage3-mpfr: all-stage3-mpfr
all-stage3: all-stage3-mpfr
TARGET-stage3-mpfr = $(TARGET-mpfr)
all-stage3-mpfr: configure-stage3-mpfr
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS)" CXXFLAGS="$(STAGE3_CFLAGS)" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage3-mpfr)

maybe-clean-stage3-mpfr: clean-stage3-mpfr
clean-stage3: clean-stage3-mpfr
clean-stage3-mpfr:
	@if [ $(current_stage) = stage3 ]; then \
	  [ -f $(HOST_SUBDIR)/mpfr/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage3-mpfr/Makefile ] || exit 0; \
	  $(MAKE) stage3-start; \
	fi; \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb3g2-mpfr maybe-all-stageb3g2-mpfr
.PHONY: clean-stageb3g2-mpfr maybe-clean-stageb3g2-mpfr
maybe-all-stageb3g2-mpfr:
maybe-clean-stageb3g2-mpfr:
maybe-all-stageb3g2-mpfr: all-stageb3g2-mpfr
all-stageb3g2: all-stageb3g2-mpfr
TARGET-stageb3g2-mpfr = $(TARGET-mpfr)
all-stageb3g2-mpfr: configure-stageb3g2-mpfr
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -g2" CXXFLAGS="$(STAGE3_CFLAGS) -g2" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -g2" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb3g2-mpfr)

maybe-clean-stageb3g2-mpfr: clean-stageb3g2-mpfr
clean-stageb3g2: clean-stageb3g2-mpfr
clean-stageb3g2-mpfr:
	@if [ $(current_stage) = stageb3g2 ]; then \
	  [ -f $(HOST_SUBDIR)/mpfr/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb3g2-mpfr/Makefile ] || exit 0; \
	  $(MAKE) stageb3g2-start; \
	fi; \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage4-mpfr maybe-all-stage4-mpfr
.PHONY: clean-stage4-mpfr maybe-clean-stage4-mpfr
maybe-all-stage4-mpfr:
maybe-clean-stage4-mpfr:
maybe-all-stage4-mpfr: all-stage4-mpfr
all-stage4: all-stage4-mpfr
TARGET-stage4-mpfr = $(TARGET-mpfr)
all-stage4-mpfr: configure-stage4-mpfr
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE4_CFLAGS)" CXXFLAGS="$(STAGE4_CFLAGS)" \
		LIBCFLAGS="$(STAGE4_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage4-mpfr)

maybe-clean-stage4-mpfr: clean-stage4-mpfr
clean-stage4: clean-stage4-mpfr
clean-stage4-mpfr:
	@if [ $(current_stage) = stage4 ]; then \
	  [ -f $(HOST_SUBDIR)/mpfr/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage4-mpfr/Makefile ] || exit 0; \
	  $(MAKE) stage4-start; \
	fi; \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageprofile-mpfr maybe-all-stageprofile-mpfr
.PHONY: clean-stageprofile-mpfr maybe-clean-stageprofile-mpfr
maybe-all-stageprofile-mpfr:
maybe-clean-stageprofile-mpfr:
maybe-all-stageprofile-mpfr: all-stageprofile-mpfr
all-stageprofile: all-stageprofile-mpfr
TARGET-stageprofile-mpfr = $(TARGET-mpfr)
all-stageprofile-mpfr: configure-stageprofile-mpfr
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageprofile-mpfr)

maybe-clean-stageprofile-mpfr: clean-stageprofile-mpfr
clean-stageprofile: clean-stageprofile-mpfr
clean-stageprofile-mpfr:
	@if [ $(current_stage) = stageprofile ]; then \
	  [ -f $(HOST_SUBDIR)/mpfr/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageprofile-mpfr/Makefile ] || exit 0; \
	  $(MAKE) stageprofile-start; \
	fi; \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stagefeedback-mpfr maybe-all-stagefeedback-mpfr
.PHONY: clean-stagefeedback-mpfr maybe-clean-stagefeedback-mpfr
maybe-all-stagefeedback-mpfr:
maybe-clean-stagefeedback-mpfr:
maybe-all-stagefeedback-mpfr: all-stagefeedback-mpfr
all-stagefeedback: all-stagefeedback-mpfr
TARGET-stagefeedback-mpfr = $(TARGET-mpfr)
all-stagefeedback-mpfr: configure-stagefeedback-mpfr
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -fprofile-use" CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stagefeedback-mpfr)

maybe-clean-stagefeedback-mpfr: clean-stagefeedback-mpfr
clean-stagefeedback: clean-stagefeedback-mpfr
clean-stagefeedback-mpfr:
	@if [ $(current_stage) = stagefeedback ]; then \
	  [ -f $(HOST_SUBDIR)/mpfr/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stagefeedback-mpfr/Makefile ] || exit 0; \
	  $(MAKE) stagefeedback-start; \
	fi; \
	cd $(HOST_SUBDIR)/mpfr && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean





.PHONY: check-mpfr maybe-check-mpfr
maybe-check-mpfr:
maybe-check-mpfr: check-mpfr

check-mpfr:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(FLAGS_TO_PASS)  check)


.PHONY: install-mpfr maybe-install-mpfr
maybe-install-mpfr:
maybe-install-mpfr: install-mpfr

install-mpfr:


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-mpfr info-mpfr
maybe-info-mpfr:
maybe-info-mpfr: info-mpfr

info-mpfr: \
    configure-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing info in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          info) \
	  || exit 1


.PHONY: maybe-dvi-mpfr dvi-mpfr
maybe-dvi-mpfr:
maybe-dvi-mpfr: dvi-mpfr

dvi-mpfr: \
    configure-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing dvi in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          dvi) \
	  || exit 1


.PHONY: maybe-pdf-mpfr pdf-mpfr
maybe-pdf-mpfr:
maybe-pdf-mpfr: pdf-mpfr

pdf-mpfr: \
    configure-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing pdf in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          pdf) \
	  || exit 1


.PHONY: maybe-html-mpfr html-mpfr
maybe-html-mpfr:
maybe-html-mpfr: html-mpfr

html-mpfr: \
    configure-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing html in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          html) \
	  || exit 1


.PHONY: maybe-TAGS-mpfr TAGS-mpfr
maybe-TAGS-mpfr:
maybe-TAGS-mpfr: TAGS-mpfr

TAGS-mpfr: \
    configure-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing TAGS in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          TAGS) \
	  || exit 1


.PHONY: maybe-install-info-mpfr install-info-mpfr
maybe-install-info-mpfr:
maybe-install-info-mpfr: install-info-mpfr

install-info-mpfr: \
    configure-mpfr \
    info-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-info in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-mpfr install-pdf-mpfr
maybe-install-pdf-mpfr:
maybe-install-pdf-mpfr: install-pdf-mpfr

install-pdf-mpfr: \
    configure-mpfr \
    pdf-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-pdf in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-mpfr install-html-mpfr
maybe-install-html-mpfr:
maybe-install-html-mpfr: install-html-mpfr

install-html-mpfr: \
    configure-mpfr \
    html-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-html in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-html) \
	  || exit 1


.PHONY: maybe-installcheck-mpfr installcheck-mpfr
maybe-installcheck-mpfr:
maybe-installcheck-mpfr: installcheck-mpfr

installcheck-mpfr: \
    configure-mpfr 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing installcheck in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-mpfr mostlyclean-mpfr
maybe-mostlyclean-mpfr:
maybe-mostlyclean-mpfr: mostlyclean-mpfr

mostlyclean-mpfr: 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing mostlyclean in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-mpfr clean-mpfr
maybe-clean-mpfr:
maybe-clean-mpfr: clean-mpfr

clean-mpfr: 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing clean in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          clean) \
	  || exit 1


.PHONY: maybe-distclean-mpfr distclean-mpfr
maybe-distclean-mpfr:
maybe-distclean-mpfr: distclean-mpfr

distclean-mpfr: 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing distclean in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-mpfr maintainer-clean-mpfr
maybe-maintainer-clean-mpfr:
maybe-maintainer-clean-mpfr: maintainer-clean-mpfr

maintainer-clean-mpfr: 
	@[ -f ./mpfr/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing maintainer-clean in mpfr" ; \
	(cd $(HOST_SUBDIR)/mpfr && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          maintainer-clean) \
	  || exit 1




.PHONY: configure-ppl maybe-configure-ppl
maybe-configure-ppl:
configure-ppl: stage_current



.PHONY: configure-stage1-ppl maybe-configure-stage1-ppl
maybe-configure-stage1-ppl:

.PHONY: configure-stage2-ppl maybe-configure-stage2-ppl
maybe-configure-stage2-ppl:

.PHONY: configure-stageb2g0-ppl maybe-configure-stageb2g0-ppl
maybe-configure-stageb2g0-ppl:

.PHONY: configure-stage3-ppl maybe-configure-stage3-ppl
maybe-configure-stage3-ppl:

.PHONY: configure-stageb3g2-ppl maybe-configure-stageb3g2-ppl
maybe-configure-stageb3g2-ppl:

.PHONY: configure-stage4-ppl maybe-configure-stage4-ppl
maybe-configure-stage4-ppl:

.PHONY: configure-stageprofile-ppl maybe-configure-stageprofile-ppl
maybe-configure-stageprofile-ppl:

.PHONY: configure-stagefeedback-ppl maybe-configure-stagefeedback-ppl
maybe-configure-stagefeedback-ppl:





.PHONY: all-ppl maybe-all-ppl
maybe-all-ppl:
all-ppl: stage_current



.PHONY: all-stage1-ppl maybe-all-stage1-ppl
.PHONY: clean-stage1-ppl maybe-clean-stage1-ppl
maybe-all-stage1-ppl:
maybe-clean-stage1-ppl:


.PHONY: all-stage2-ppl maybe-all-stage2-ppl
.PHONY: clean-stage2-ppl maybe-clean-stage2-ppl
maybe-all-stage2-ppl:
maybe-clean-stage2-ppl:


.PHONY: all-stageb2g0-ppl maybe-all-stageb2g0-ppl
.PHONY: clean-stageb2g0-ppl maybe-clean-stageb2g0-ppl
maybe-all-stageb2g0-ppl:
maybe-clean-stageb2g0-ppl:


.PHONY: all-stage3-ppl maybe-all-stage3-ppl
.PHONY: clean-stage3-ppl maybe-clean-stage3-ppl
maybe-all-stage3-ppl:
maybe-clean-stage3-ppl:


.PHONY: all-stageb3g2-ppl maybe-all-stageb3g2-ppl
.PHONY: clean-stageb3g2-ppl maybe-clean-stageb3g2-ppl
maybe-all-stageb3g2-ppl:
maybe-clean-stageb3g2-ppl:


.PHONY: all-stage4-ppl maybe-all-stage4-ppl
.PHONY: clean-stage4-ppl maybe-clean-stage4-ppl
maybe-all-stage4-ppl:
maybe-clean-stage4-ppl:


.PHONY: all-stageprofile-ppl maybe-all-stageprofile-ppl
.PHONY: clean-stageprofile-ppl maybe-clean-stageprofile-ppl
maybe-all-stageprofile-ppl:
maybe-clean-stageprofile-ppl:


.PHONY: all-stagefeedback-ppl maybe-all-stagefeedback-ppl
.PHONY: clean-stagefeedback-ppl maybe-clean-stagefeedback-ppl
maybe-all-stagefeedback-ppl:
maybe-clean-stagefeedback-ppl:





.PHONY: check-ppl maybe-check-ppl
maybe-check-ppl:

.PHONY: install-ppl maybe-install-ppl
maybe-install-ppl:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-ppl info-ppl
maybe-info-ppl:

.PHONY: maybe-dvi-ppl dvi-ppl
maybe-dvi-ppl:

.PHONY: maybe-pdf-ppl pdf-ppl
maybe-pdf-ppl:

.PHONY: maybe-html-ppl html-ppl
maybe-html-ppl:

.PHONY: maybe-TAGS-ppl TAGS-ppl
maybe-TAGS-ppl:

.PHONY: maybe-install-info-ppl install-info-ppl
maybe-install-info-ppl:

.PHONY: maybe-install-pdf-ppl install-pdf-ppl
maybe-install-pdf-ppl:

.PHONY: maybe-install-html-ppl install-html-ppl
maybe-install-html-ppl:

.PHONY: maybe-installcheck-ppl installcheck-ppl
maybe-installcheck-ppl:

.PHONY: maybe-mostlyclean-ppl mostlyclean-ppl
maybe-mostlyclean-ppl:

.PHONY: maybe-clean-ppl clean-ppl
maybe-clean-ppl:

.PHONY: maybe-distclean-ppl distclean-ppl
maybe-distclean-ppl:

.PHONY: maybe-maintainer-clean-ppl maintainer-clean-ppl
maybe-maintainer-clean-ppl:



.PHONY: configure-cloog maybe-configure-cloog
maybe-configure-cloog:
configure-cloog: stage_current



.PHONY: configure-stage1-cloog maybe-configure-stage1-cloog
maybe-configure-stage1-cloog:

.PHONY: configure-stage2-cloog maybe-configure-stage2-cloog
maybe-configure-stage2-cloog:

.PHONY: configure-stageb2g0-cloog maybe-configure-stageb2g0-cloog
maybe-configure-stageb2g0-cloog:

.PHONY: configure-stage3-cloog maybe-configure-stage3-cloog
maybe-configure-stage3-cloog:

.PHONY: configure-stageb3g2-cloog maybe-configure-stageb3g2-cloog
maybe-configure-stageb3g2-cloog:

.PHONY: configure-stage4-cloog maybe-configure-stage4-cloog
maybe-configure-stage4-cloog:

.PHONY: configure-stageprofile-cloog maybe-configure-stageprofile-cloog
maybe-configure-stageprofile-cloog:

.PHONY: configure-stagefeedback-cloog maybe-configure-stagefeedback-cloog
maybe-configure-stagefeedback-cloog:





.PHONY: all-cloog maybe-all-cloog
maybe-all-cloog:
all-cloog: stage_current



.PHONY: all-stage1-cloog maybe-all-stage1-cloog
.PHONY: clean-stage1-cloog maybe-clean-stage1-cloog
maybe-all-stage1-cloog:
maybe-clean-stage1-cloog:


.PHONY: all-stage2-cloog maybe-all-stage2-cloog
.PHONY: clean-stage2-cloog maybe-clean-stage2-cloog
maybe-all-stage2-cloog:
maybe-clean-stage2-cloog:


.PHONY: all-stageb2g0-cloog maybe-all-stageb2g0-cloog
.PHONY: clean-stageb2g0-cloog maybe-clean-stageb2g0-cloog
maybe-all-stageb2g0-cloog:
maybe-clean-stageb2g0-cloog:


.PHONY: all-stage3-cloog maybe-all-stage3-cloog
.PHONY: clean-stage3-cloog maybe-clean-stage3-cloog
maybe-all-stage3-cloog:
maybe-clean-stage3-cloog:


.PHONY: all-stageb3g2-cloog maybe-all-stageb3g2-cloog
.PHONY: clean-stageb3g2-cloog maybe-clean-stageb3g2-cloog
maybe-all-stageb3g2-cloog:
maybe-clean-stageb3g2-cloog:


.PHONY: all-stage4-cloog maybe-all-stage4-cloog
.PHONY: clean-stage4-cloog maybe-clean-stage4-cloog
maybe-all-stage4-cloog:
maybe-clean-stage4-cloog:


.PHONY: all-stageprofile-cloog maybe-all-stageprofile-cloog
.PHONY: clean-stageprofile-cloog maybe-clean-stageprofile-cloog
maybe-all-stageprofile-cloog:
maybe-clean-stageprofile-cloog:


.PHONY: all-stagefeedback-cloog maybe-all-stagefeedback-cloog
.PHONY: clean-stagefeedback-cloog maybe-clean-stagefeedback-cloog
maybe-all-stagefeedback-cloog:
maybe-clean-stagefeedback-cloog:





.PHONY: check-cloog maybe-check-cloog
maybe-check-cloog:

.PHONY: install-cloog maybe-install-cloog
maybe-install-cloog:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-cloog info-cloog
maybe-info-cloog:

.PHONY: maybe-dvi-cloog dvi-cloog
maybe-dvi-cloog:

.PHONY: maybe-pdf-cloog pdf-cloog
maybe-pdf-cloog:

.PHONY: maybe-html-cloog html-cloog
maybe-html-cloog:

.PHONY: maybe-TAGS-cloog TAGS-cloog
maybe-TAGS-cloog:

.PHONY: maybe-install-info-cloog install-info-cloog
maybe-install-info-cloog:

.PHONY: maybe-install-pdf-cloog install-pdf-cloog
maybe-install-pdf-cloog:

.PHONY: maybe-install-html-cloog install-html-cloog
maybe-install-html-cloog:

.PHONY: maybe-installcheck-cloog installcheck-cloog
maybe-installcheck-cloog:

.PHONY: maybe-mostlyclean-cloog mostlyclean-cloog
maybe-mostlyclean-cloog:

.PHONY: maybe-clean-cloog clean-cloog
maybe-clean-cloog:

.PHONY: maybe-distclean-cloog distclean-cloog
maybe-distclean-cloog:

.PHONY: maybe-maintainer-clean-cloog maintainer-clean-cloog
maybe-maintainer-clean-cloog:



.PHONY: configure-gnuserv maybe-configure-gnuserv
maybe-configure-gnuserv:
configure-gnuserv: stage_current





.PHONY: all-gnuserv maybe-all-gnuserv
maybe-all-gnuserv:
all-gnuserv: stage_current




.PHONY: check-gnuserv maybe-check-gnuserv
maybe-check-gnuserv:

.PHONY: install-gnuserv maybe-install-gnuserv
maybe-install-gnuserv:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gnuserv info-gnuserv
maybe-info-gnuserv:

.PHONY: maybe-dvi-gnuserv dvi-gnuserv
maybe-dvi-gnuserv:

.PHONY: maybe-pdf-gnuserv pdf-gnuserv
maybe-pdf-gnuserv:

.PHONY: maybe-html-gnuserv html-gnuserv
maybe-html-gnuserv:

.PHONY: maybe-TAGS-gnuserv TAGS-gnuserv
maybe-TAGS-gnuserv:

.PHONY: maybe-install-info-gnuserv install-info-gnuserv
maybe-install-info-gnuserv:

.PHONY: maybe-install-pdf-gnuserv install-pdf-gnuserv
maybe-install-pdf-gnuserv:

.PHONY: maybe-install-html-gnuserv install-html-gnuserv
maybe-install-html-gnuserv:

.PHONY: maybe-installcheck-gnuserv installcheck-gnuserv
maybe-installcheck-gnuserv:

.PHONY: maybe-mostlyclean-gnuserv mostlyclean-gnuserv
maybe-mostlyclean-gnuserv:

.PHONY: maybe-clean-gnuserv clean-gnuserv
maybe-clean-gnuserv:

.PHONY: maybe-distclean-gnuserv distclean-gnuserv
maybe-distclean-gnuserv:

.PHONY: maybe-maintainer-clean-gnuserv maintainer-clean-gnuserv
maybe-maintainer-clean-gnuserv:



.PHONY: configure-gold maybe-configure-gold
maybe-configure-gold:
configure-gold: stage_current



.PHONY: configure-stage1-gold maybe-configure-stage1-gold
maybe-configure-stage1-gold:

.PHONY: configure-stage2-gold maybe-configure-stage2-gold
maybe-configure-stage2-gold:

.PHONY: configure-stageb2g0-gold maybe-configure-stageb2g0-gold
maybe-configure-stageb2g0-gold:

.PHONY: configure-stage3-gold maybe-configure-stage3-gold
maybe-configure-stage3-gold:

.PHONY: configure-stageb3g2-gold maybe-configure-stageb3g2-gold
maybe-configure-stageb3g2-gold:

.PHONY: configure-stage4-gold maybe-configure-stage4-gold
maybe-configure-stage4-gold:

.PHONY: configure-stageprofile-gold maybe-configure-stageprofile-gold
maybe-configure-stageprofile-gold:

.PHONY: configure-stagefeedback-gold maybe-configure-stagefeedback-gold
maybe-configure-stagefeedback-gold:





.PHONY: all-gold maybe-all-gold
maybe-all-gold:
all-gold: stage_current



.PHONY: all-stage1-gold maybe-all-stage1-gold
.PHONY: clean-stage1-gold maybe-clean-stage1-gold
maybe-all-stage1-gold:
maybe-clean-stage1-gold:


.PHONY: all-stage2-gold maybe-all-stage2-gold
.PHONY: clean-stage2-gold maybe-clean-stage2-gold
maybe-all-stage2-gold:
maybe-clean-stage2-gold:


.PHONY: all-stageb2g0-gold maybe-all-stageb2g0-gold
.PHONY: clean-stageb2g0-gold maybe-clean-stageb2g0-gold
maybe-all-stageb2g0-gold:
maybe-clean-stageb2g0-gold:


.PHONY: all-stage3-gold maybe-all-stage3-gold
.PHONY: clean-stage3-gold maybe-clean-stage3-gold
maybe-all-stage3-gold:
maybe-clean-stage3-gold:


.PHONY: all-stageb3g2-gold maybe-all-stageb3g2-gold
.PHONY: clean-stageb3g2-gold maybe-clean-stageb3g2-gold
maybe-all-stageb3g2-gold:
maybe-clean-stageb3g2-gold:


.PHONY: all-stage4-gold maybe-all-stage4-gold
.PHONY: clean-stage4-gold maybe-clean-stage4-gold
maybe-all-stage4-gold:
maybe-clean-stage4-gold:


.PHONY: all-stageprofile-gold maybe-all-stageprofile-gold
.PHONY: clean-stageprofile-gold maybe-clean-stageprofile-gold
maybe-all-stageprofile-gold:
maybe-clean-stageprofile-gold:


.PHONY: all-stagefeedback-gold maybe-all-stagefeedback-gold
.PHONY: clean-stagefeedback-gold maybe-clean-stagefeedback-gold
maybe-all-stagefeedback-gold:
maybe-clean-stagefeedback-gold:





.PHONY: check-gold maybe-check-gold
maybe-check-gold:

.PHONY: install-gold maybe-install-gold
maybe-install-gold:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gold info-gold
maybe-info-gold:

.PHONY: maybe-dvi-gold dvi-gold
maybe-dvi-gold:

.PHONY: maybe-pdf-gold pdf-gold
maybe-pdf-gold:

.PHONY: maybe-html-gold html-gold
maybe-html-gold:

.PHONY: maybe-TAGS-gold TAGS-gold
maybe-TAGS-gold:

.PHONY: maybe-install-info-gold install-info-gold
maybe-install-info-gold:

.PHONY: maybe-install-pdf-gold install-pdf-gold
maybe-install-pdf-gold:

.PHONY: maybe-install-html-gold install-html-gold
maybe-install-html-gold:

.PHONY: maybe-installcheck-gold installcheck-gold
maybe-installcheck-gold:

.PHONY: maybe-mostlyclean-gold mostlyclean-gold
maybe-mostlyclean-gold:

.PHONY: maybe-clean-gold clean-gold
maybe-clean-gold:

.PHONY: maybe-distclean-gold distclean-gold
maybe-distclean-gold:

.PHONY: maybe-maintainer-clean-gold maintainer-clean-gold
maybe-maintainer-clean-gold:



.PHONY: configure-gprof maybe-configure-gprof
maybe-configure-gprof:
configure-gprof: stage_current





.PHONY: all-gprof maybe-all-gprof
maybe-all-gprof:
all-gprof: stage_current




.PHONY: check-gprof maybe-check-gprof
maybe-check-gprof:

.PHONY: install-gprof maybe-install-gprof
maybe-install-gprof:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gprof info-gprof
maybe-info-gprof:

.PHONY: maybe-dvi-gprof dvi-gprof
maybe-dvi-gprof:

.PHONY: maybe-pdf-gprof pdf-gprof
maybe-pdf-gprof:

.PHONY: maybe-html-gprof html-gprof
maybe-html-gprof:

.PHONY: maybe-TAGS-gprof TAGS-gprof
maybe-TAGS-gprof:

.PHONY: maybe-install-info-gprof install-info-gprof
maybe-install-info-gprof:

.PHONY: maybe-install-pdf-gprof install-pdf-gprof
maybe-install-pdf-gprof:

.PHONY: maybe-install-html-gprof install-html-gprof
maybe-install-html-gprof:

.PHONY: maybe-installcheck-gprof installcheck-gprof
maybe-installcheck-gprof:

.PHONY: maybe-mostlyclean-gprof mostlyclean-gprof
maybe-mostlyclean-gprof:

.PHONY: maybe-clean-gprof clean-gprof
maybe-clean-gprof:

.PHONY: maybe-distclean-gprof distclean-gprof
maybe-distclean-gprof:

.PHONY: maybe-maintainer-clean-gprof maintainer-clean-gprof
maybe-maintainer-clean-gprof:



.PHONY: configure-gzip maybe-configure-gzip
maybe-configure-gzip:
configure-gzip: stage_current





.PHONY: all-gzip maybe-all-gzip
maybe-all-gzip:
all-gzip: stage_current




.PHONY: check-gzip maybe-check-gzip
maybe-check-gzip:

.PHONY: install-gzip maybe-install-gzip
maybe-install-gzip:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gzip info-gzip
maybe-info-gzip:

.PHONY: maybe-dvi-gzip dvi-gzip
maybe-dvi-gzip:

.PHONY: maybe-pdf-gzip pdf-gzip
maybe-pdf-gzip:

.PHONY: maybe-html-gzip html-gzip
maybe-html-gzip:

.PHONY: maybe-TAGS-gzip TAGS-gzip
maybe-TAGS-gzip:

.PHONY: maybe-install-info-gzip install-info-gzip
maybe-install-info-gzip:

.PHONY: maybe-install-pdf-gzip install-pdf-gzip
maybe-install-pdf-gzip:

.PHONY: maybe-install-html-gzip install-html-gzip
maybe-install-html-gzip:

.PHONY: maybe-installcheck-gzip installcheck-gzip
maybe-installcheck-gzip:

.PHONY: maybe-mostlyclean-gzip mostlyclean-gzip
maybe-mostlyclean-gzip:

.PHONY: maybe-clean-gzip clean-gzip
maybe-clean-gzip:

.PHONY: maybe-distclean-gzip distclean-gzip
maybe-distclean-gzip:

.PHONY: maybe-maintainer-clean-gzip maintainer-clean-gzip
maybe-maintainer-clean-gzip:



.PHONY: configure-hello maybe-configure-hello
maybe-configure-hello:
configure-hello: stage_current





.PHONY: all-hello maybe-all-hello
maybe-all-hello:
all-hello: stage_current




.PHONY: check-hello maybe-check-hello
maybe-check-hello:

.PHONY: install-hello maybe-install-hello
maybe-install-hello:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-hello info-hello
maybe-info-hello:

.PHONY: maybe-dvi-hello dvi-hello
maybe-dvi-hello:

.PHONY: maybe-pdf-hello pdf-hello
maybe-pdf-hello:

.PHONY: maybe-html-hello html-hello
maybe-html-hello:

.PHONY: maybe-TAGS-hello TAGS-hello
maybe-TAGS-hello:

.PHONY: maybe-install-info-hello install-info-hello
maybe-install-info-hello:

.PHONY: maybe-install-pdf-hello install-pdf-hello
maybe-install-pdf-hello:

.PHONY: maybe-install-html-hello install-html-hello
maybe-install-html-hello:

.PHONY: maybe-installcheck-hello installcheck-hello
maybe-installcheck-hello:

.PHONY: maybe-mostlyclean-hello mostlyclean-hello
maybe-mostlyclean-hello:

.PHONY: maybe-clean-hello clean-hello
maybe-clean-hello:

.PHONY: maybe-distclean-hello distclean-hello
maybe-distclean-hello:

.PHONY: maybe-maintainer-clean-hello maintainer-clean-hello
maybe-maintainer-clean-hello:



.PHONY: configure-indent maybe-configure-indent
maybe-configure-indent:
configure-indent: stage_current





.PHONY: all-indent maybe-all-indent
maybe-all-indent:
all-indent: stage_current




.PHONY: check-indent maybe-check-indent
maybe-check-indent:

.PHONY: install-indent maybe-install-indent
maybe-install-indent:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-indent info-indent
maybe-info-indent:

.PHONY: maybe-dvi-indent dvi-indent
maybe-dvi-indent:

.PHONY: maybe-pdf-indent pdf-indent
maybe-pdf-indent:

.PHONY: maybe-html-indent html-indent
maybe-html-indent:

.PHONY: maybe-TAGS-indent TAGS-indent
maybe-TAGS-indent:

.PHONY: maybe-install-info-indent install-info-indent
maybe-install-info-indent:

.PHONY: maybe-install-pdf-indent install-pdf-indent
maybe-install-pdf-indent:

.PHONY: maybe-install-html-indent install-html-indent
maybe-install-html-indent:

.PHONY: maybe-installcheck-indent installcheck-indent
maybe-installcheck-indent:

.PHONY: maybe-mostlyclean-indent mostlyclean-indent
maybe-mostlyclean-indent:

.PHONY: maybe-clean-indent clean-indent
maybe-clean-indent:

.PHONY: maybe-distclean-indent distclean-indent
maybe-distclean-indent:

.PHONY: maybe-maintainer-clean-indent maintainer-clean-indent
maybe-maintainer-clean-indent:



.PHONY: configure-intl maybe-configure-intl
maybe-configure-intl:
configure-intl: stage_current
maybe-configure-intl: configure-intl
configure-intl: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	$(HOST_EXPORTS) \
	echo Configuring in $(HOST_SUBDIR)/intl; \
	cd "$(HOST_SUBDIR)/intl" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1



.PHONY: configure-stage1-intl maybe-configure-stage1-intl
maybe-configure-stage1-intl:
maybe-configure-stage1-intl: configure-stage1-intl
configure-stage1-intl:
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(HOST_EXPORTS)  \
	CFLAGS="$(STAGE1_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE1_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 1 in $(HOST_SUBDIR)/intl ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	cd $(HOST_SUBDIR)/intl || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	   \
	  --disable-intermodule $(STAGE1_CHECKING) 	  --disable-coverage --enable-languages="$(STAGE1_LANGUAGES)" 

.PHONY: configure-stage2-intl maybe-configure-stage2-intl
maybe-configure-stage2-intl:
maybe-configure-stage2-intl: configure-stage2-intl
configure-stage2-intl:
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 2 in $(HOST_SUBDIR)/intl ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	cd $(HOST_SUBDIR)/intl || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb2g0-intl maybe-configure-stageb2g0-intl
maybe-configure-stageb2g0-intl:
maybe-configure-stageb2g0-intl: configure-stageb2g0-intl
configure-stageb2g0-intl:
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -g0"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -g0"; export CXXFLAGS;  \
	echo Configuring stage b2g0 in $(HOST_SUBDIR)/intl ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	cd $(HOST_SUBDIR)/intl || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage3-intl maybe-configure-stage3-intl
maybe-configure-stage3-intl:
maybe-configure-stage3-intl: configure-stage3-intl
configure-stage3-intl:
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 3 in $(HOST_SUBDIR)/intl ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	cd $(HOST_SUBDIR)/intl || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb3g2-intl maybe-configure-stageb3g2-intl
maybe-configure-stageb3g2-intl:
maybe-configure-stageb3g2-intl: configure-stageb3g2-intl
configure-stageb3g2-intl:
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -g2"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -g2"; export CXXFLAGS;  \
	echo Configuring stage b3g2 in $(HOST_SUBDIR)/intl ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	cd $(HOST_SUBDIR)/intl || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage4-intl maybe-configure-stage4-intl
maybe-configure-stage4-intl:
maybe-configure-stage4-intl: configure-stage4-intl
configure-stage4-intl:
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE4_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE4_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 4 in $(HOST_SUBDIR)/intl ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	cd $(HOST_SUBDIR)/intl || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageprofile-intl maybe-configure-stageprofile-intl
maybe-configure-stageprofile-intl:
maybe-configure-stageprofile-intl: configure-stageprofile-intl
configure-stageprofile-intl:
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CXXFLAGS;  \
	echo Configuring stage profile in $(HOST_SUBDIR)/intl ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	cd $(HOST_SUBDIR)/intl || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stagefeedback-intl maybe-configure-stagefeedback-intl
maybe-configure-stagefeedback-intl:
maybe-configure-stagefeedback-intl: configure-stagefeedback-intl
configure-stagefeedback-intl:
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/intl/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CXXFLAGS;  \
	echo Configuring stage feedback in $(HOST_SUBDIR)/intl ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/intl ; \
	cd $(HOST_SUBDIR)/intl || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/intl/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/intl"; \
	libsrcdir="$$s/intl"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   





.PHONY: all-intl maybe-all-intl
maybe-all-intl:
all-intl: stage_current
TARGET-intl=all
maybe-all-intl: all-intl
all-intl: configure-intl
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)  \
		$(TARGET-intl))



.PHONY: all-stage1-intl maybe-all-stage1-intl
.PHONY: clean-stage1-intl maybe-clean-stage1-intl
maybe-all-stage1-intl:
maybe-clean-stage1-intl:
maybe-all-stage1-intl: all-stage1-intl
all-stage1: all-stage1-intl
TARGET-stage1-intl = $(TARGET-intl)
all-stage1-intl: configure-stage1-intl
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE1_CFLAGS)" CXXFLAGS="$(STAGE1_CFLAGS)" \
		LIBCFLAGS="$(STAGE1_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" $(EXTRA_HOST_FLAGS)   \
		$(TARGET-stage1-intl)

maybe-clean-stage1-intl: clean-stage1-intl
clean-stage1: clean-stage1-intl
clean-stage1-intl:
	@if [ $(current_stage) = stage1 ]; then \
	  [ -f $(HOST_SUBDIR)/intl/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage1-intl/Makefile ] || exit 0; \
	  $(MAKE) stage1-start; \
	fi; \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		 clean


.PHONY: all-stage2-intl maybe-all-stage2-intl
.PHONY: clean-stage2-intl maybe-clean-stage2-intl
maybe-all-stage2-intl:
maybe-clean-stage2-intl:
maybe-all-stage2-intl: all-stage2-intl
all-stage2: all-stage2-intl
TARGET-stage2-intl = $(TARGET-intl)
all-stage2-intl: configure-stage2-intl
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS)" CXXFLAGS="$(STAGE2_CFLAGS)" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage2-intl)

maybe-clean-stage2-intl: clean-stage2-intl
clean-stage2: clean-stage2-intl
clean-stage2-intl:
	@if [ $(current_stage) = stage2 ]; then \
	  [ -f $(HOST_SUBDIR)/intl/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage2-intl/Makefile ] || exit 0; \
	  $(MAKE) stage2-start; \
	fi; \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb2g0-intl maybe-all-stageb2g0-intl
.PHONY: clean-stageb2g0-intl maybe-clean-stageb2g0-intl
maybe-all-stageb2g0-intl:
maybe-clean-stageb2g0-intl:
maybe-all-stageb2g0-intl: all-stageb2g0-intl
all-stageb2g0: all-stageb2g0-intl
TARGET-stageb2g0-intl = $(TARGET-intl)
all-stageb2g0-intl: configure-stageb2g0-intl
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -g0" CXXFLAGS="$(STAGE2_CFLAGS) -g0" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS) -g0" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb2g0-intl)

maybe-clean-stageb2g0-intl: clean-stageb2g0-intl
clean-stageb2g0: clean-stageb2g0-intl
clean-stageb2g0-intl:
	@if [ $(current_stage) = stageb2g0 ]; then \
	  [ -f $(HOST_SUBDIR)/intl/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb2g0-intl/Makefile ] || exit 0; \
	  $(MAKE) stageb2g0-start; \
	fi; \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage3-intl maybe-all-stage3-intl
.PHONY: clean-stage3-intl maybe-clean-stage3-intl
maybe-all-stage3-intl:
maybe-clean-stage3-intl:
maybe-all-stage3-intl: all-stage3-intl
all-stage3: all-stage3-intl
TARGET-stage3-intl = $(TARGET-intl)
all-stage3-intl: configure-stage3-intl
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS)" CXXFLAGS="$(STAGE3_CFLAGS)" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage3-intl)

maybe-clean-stage3-intl: clean-stage3-intl
clean-stage3: clean-stage3-intl
clean-stage3-intl:
	@if [ $(current_stage) = stage3 ]; then \
	  [ -f $(HOST_SUBDIR)/intl/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage3-intl/Makefile ] || exit 0; \
	  $(MAKE) stage3-start; \
	fi; \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb3g2-intl maybe-all-stageb3g2-intl
.PHONY: clean-stageb3g2-intl maybe-clean-stageb3g2-intl
maybe-all-stageb3g2-intl:
maybe-clean-stageb3g2-intl:
maybe-all-stageb3g2-intl: all-stageb3g2-intl
all-stageb3g2: all-stageb3g2-intl
TARGET-stageb3g2-intl = $(TARGET-intl)
all-stageb3g2-intl: configure-stageb3g2-intl
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -g2" CXXFLAGS="$(STAGE3_CFLAGS) -g2" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -g2" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb3g2-intl)

maybe-clean-stageb3g2-intl: clean-stageb3g2-intl
clean-stageb3g2: clean-stageb3g2-intl
clean-stageb3g2-intl:
	@if [ $(current_stage) = stageb3g2 ]; then \
	  [ -f $(HOST_SUBDIR)/intl/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb3g2-intl/Makefile ] || exit 0; \
	  $(MAKE) stageb3g2-start; \
	fi; \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage4-intl maybe-all-stage4-intl
.PHONY: clean-stage4-intl maybe-clean-stage4-intl
maybe-all-stage4-intl:
maybe-clean-stage4-intl:
maybe-all-stage4-intl: all-stage4-intl
all-stage4: all-stage4-intl
TARGET-stage4-intl = $(TARGET-intl)
all-stage4-intl: configure-stage4-intl
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE4_CFLAGS)" CXXFLAGS="$(STAGE4_CFLAGS)" \
		LIBCFLAGS="$(STAGE4_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage4-intl)

maybe-clean-stage4-intl: clean-stage4-intl
clean-stage4: clean-stage4-intl
clean-stage4-intl:
	@if [ $(current_stage) = stage4 ]; then \
	  [ -f $(HOST_SUBDIR)/intl/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage4-intl/Makefile ] || exit 0; \
	  $(MAKE) stage4-start; \
	fi; \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageprofile-intl maybe-all-stageprofile-intl
.PHONY: clean-stageprofile-intl maybe-clean-stageprofile-intl
maybe-all-stageprofile-intl:
maybe-clean-stageprofile-intl:
maybe-all-stageprofile-intl: all-stageprofile-intl
all-stageprofile: all-stageprofile-intl
TARGET-stageprofile-intl = $(TARGET-intl)
all-stageprofile-intl: configure-stageprofile-intl
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageprofile-intl)

maybe-clean-stageprofile-intl: clean-stageprofile-intl
clean-stageprofile: clean-stageprofile-intl
clean-stageprofile-intl:
	@if [ $(current_stage) = stageprofile ]; then \
	  [ -f $(HOST_SUBDIR)/intl/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageprofile-intl/Makefile ] || exit 0; \
	  $(MAKE) stageprofile-start; \
	fi; \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stagefeedback-intl maybe-all-stagefeedback-intl
.PHONY: clean-stagefeedback-intl maybe-clean-stagefeedback-intl
maybe-all-stagefeedback-intl:
maybe-clean-stagefeedback-intl:
maybe-all-stagefeedback-intl: all-stagefeedback-intl
all-stagefeedback: all-stagefeedback-intl
TARGET-stagefeedback-intl = $(TARGET-intl)
all-stagefeedback-intl: configure-stagefeedback-intl
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -fprofile-use" CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stagefeedback-intl)

maybe-clean-stagefeedback-intl: clean-stagefeedback-intl
clean-stagefeedback: clean-stagefeedback-intl
clean-stagefeedback-intl:
	@if [ $(current_stage) = stagefeedback ]; then \
	  [ -f $(HOST_SUBDIR)/intl/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stagefeedback-intl/Makefile ] || exit 0; \
	  $(MAKE) stagefeedback-start; \
	fi; \
	cd $(HOST_SUBDIR)/intl && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean





.PHONY: check-intl maybe-check-intl
maybe-check-intl:
maybe-check-intl: check-intl

check-intl:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(FLAGS_TO_PASS)  check)


.PHONY: install-intl maybe-install-intl
maybe-install-intl:
maybe-install-intl: install-intl

install-intl: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-intl info-intl
maybe-info-intl:
maybe-info-intl: info-intl

info-intl: \
    configure-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing info in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          info) \
	  || exit 1


.PHONY: maybe-dvi-intl dvi-intl
maybe-dvi-intl:
maybe-dvi-intl: dvi-intl

dvi-intl: \
    configure-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing dvi in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          dvi) \
	  || exit 1


.PHONY: maybe-pdf-intl pdf-intl
maybe-pdf-intl:
maybe-pdf-intl: pdf-intl

pdf-intl: \
    configure-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing pdf in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          pdf) \
	  || exit 1


.PHONY: maybe-html-intl html-intl
maybe-html-intl:
maybe-html-intl: html-intl

html-intl: \
    configure-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing html in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          html) \
	  || exit 1


.PHONY: maybe-TAGS-intl TAGS-intl
maybe-TAGS-intl:
maybe-TAGS-intl: TAGS-intl

TAGS-intl: \
    configure-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing TAGS in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          TAGS) \
	  || exit 1


.PHONY: maybe-install-info-intl install-info-intl
maybe-install-info-intl:
maybe-install-info-intl: install-info-intl

install-info-intl: \
    configure-intl \
    info-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-info in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-intl install-pdf-intl
maybe-install-pdf-intl:
maybe-install-pdf-intl: install-pdf-intl

install-pdf-intl: \
    configure-intl \
    pdf-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-pdf in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-intl install-html-intl
maybe-install-html-intl:
maybe-install-html-intl: install-html-intl

install-html-intl: \
    configure-intl \
    html-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-html in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-html) \
	  || exit 1


.PHONY: maybe-installcheck-intl installcheck-intl
maybe-installcheck-intl:
maybe-installcheck-intl: installcheck-intl

installcheck-intl: \
    configure-intl 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing installcheck in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-intl mostlyclean-intl
maybe-mostlyclean-intl:
maybe-mostlyclean-intl: mostlyclean-intl

mostlyclean-intl: 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing mostlyclean in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-intl clean-intl
maybe-clean-intl:
maybe-clean-intl: clean-intl

clean-intl: 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing clean in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          clean) \
	  || exit 1


.PHONY: maybe-distclean-intl distclean-intl
maybe-distclean-intl:
maybe-distclean-intl: distclean-intl

distclean-intl: 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing distclean in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-intl maintainer-clean-intl
maybe-maintainer-clean-intl:
maybe-maintainer-clean-intl: maintainer-clean-intl

maintainer-clean-intl: 
	@[ -f ./intl/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing maintainer-clean in intl" ; \
	(cd $(HOST_SUBDIR)/intl && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          maintainer-clean) \
	  || exit 1




.PHONY: configure-tcl maybe-configure-tcl
maybe-configure-tcl:
configure-tcl: stage_current





.PHONY: all-tcl maybe-all-tcl
maybe-all-tcl:
all-tcl: stage_current




.PHONY: check-tcl maybe-check-tcl
maybe-check-tcl:

.PHONY: install-tcl maybe-install-tcl
maybe-install-tcl:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-tcl info-tcl
maybe-info-tcl:

.PHONY: maybe-dvi-tcl dvi-tcl
maybe-dvi-tcl:

.PHONY: maybe-pdf-tcl pdf-tcl
maybe-pdf-tcl:

.PHONY: maybe-html-tcl html-tcl
maybe-html-tcl:

.PHONY: maybe-TAGS-tcl TAGS-tcl
maybe-TAGS-tcl:

.PHONY: maybe-install-info-tcl install-info-tcl
maybe-install-info-tcl:

.PHONY: maybe-install-pdf-tcl install-pdf-tcl
maybe-install-pdf-tcl:

.PHONY: maybe-install-html-tcl install-html-tcl
maybe-install-html-tcl:

.PHONY: maybe-installcheck-tcl installcheck-tcl
maybe-installcheck-tcl:

.PHONY: maybe-mostlyclean-tcl mostlyclean-tcl
maybe-mostlyclean-tcl:

.PHONY: maybe-clean-tcl clean-tcl
maybe-clean-tcl:

.PHONY: maybe-distclean-tcl distclean-tcl
maybe-distclean-tcl:

.PHONY: maybe-maintainer-clean-tcl maintainer-clean-tcl
maybe-maintainer-clean-tcl:



.PHONY: configure-itcl maybe-configure-itcl
maybe-configure-itcl:
configure-itcl: stage_current





.PHONY: all-itcl maybe-all-itcl
maybe-all-itcl:
all-itcl: stage_current




.PHONY: check-itcl maybe-check-itcl
maybe-check-itcl:

.PHONY: install-itcl maybe-install-itcl
maybe-install-itcl:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-itcl info-itcl
maybe-info-itcl:

.PHONY: maybe-dvi-itcl dvi-itcl
maybe-dvi-itcl:

.PHONY: maybe-pdf-itcl pdf-itcl
maybe-pdf-itcl:

.PHONY: maybe-html-itcl html-itcl
maybe-html-itcl:

.PHONY: maybe-TAGS-itcl TAGS-itcl
maybe-TAGS-itcl:

.PHONY: maybe-install-info-itcl install-info-itcl
maybe-install-info-itcl:

.PHONY: maybe-install-pdf-itcl install-pdf-itcl
maybe-install-pdf-itcl:

.PHONY: maybe-install-html-itcl install-html-itcl
maybe-install-html-itcl:

.PHONY: maybe-installcheck-itcl installcheck-itcl
maybe-installcheck-itcl:

.PHONY: maybe-mostlyclean-itcl mostlyclean-itcl
maybe-mostlyclean-itcl:

.PHONY: maybe-clean-itcl clean-itcl
maybe-clean-itcl:

.PHONY: maybe-distclean-itcl distclean-itcl
maybe-distclean-itcl:

.PHONY: maybe-maintainer-clean-itcl maintainer-clean-itcl
maybe-maintainer-clean-itcl:



.PHONY: configure-ld maybe-configure-ld
maybe-configure-ld:
configure-ld: stage_current



.PHONY: configure-stage1-ld maybe-configure-stage1-ld
maybe-configure-stage1-ld:

.PHONY: configure-stage2-ld maybe-configure-stage2-ld
maybe-configure-stage2-ld:

.PHONY: configure-stageb2g0-ld maybe-configure-stageb2g0-ld
maybe-configure-stageb2g0-ld:

.PHONY: configure-stage3-ld maybe-configure-stage3-ld
maybe-configure-stage3-ld:

.PHONY: configure-stageb3g2-ld maybe-configure-stageb3g2-ld
maybe-configure-stageb3g2-ld:

.PHONY: configure-stage4-ld maybe-configure-stage4-ld
maybe-configure-stage4-ld:

.PHONY: configure-stageprofile-ld maybe-configure-stageprofile-ld
maybe-configure-stageprofile-ld:

.PHONY: configure-stagefeedback-ld maybe-configure-stagefeedback-ld
maybe-configure-stagefeedback-ld:





.PHONY: all-ld maybe-all-ld
maybe-all-ld:
all-ld: stage_current



.PHONY: all-stage1-ld maybe-all-stage1-ld
.PHONY: clean-stage1-ld maybe-clean-stage1-ld
maybe-all-stage1-ld:
maybe-clean-stage1-ld:


.PHONY: all-stage2-ld maybe-all-stage2-ld
.PHONY: clean-stage2-ld maybe-clean-stage2-ld
maybe-all-stage2-ld:
maybe-clean-stage2-ld:


.PHONY: all-stageb2g0-ld maybe-all-stageb2g0-ld
.PHONY: clean-stageb2g0-ld maybe-clean-stageb2g0-ld
maybe-all-stageb2g0-ld:
maybe-clean-stageb2g0-ld:


.PHONY: all-stage3-ld maybe-all-stage3-ld
.PHONY: clean-stage3-ld maybe-clean-stage3-ld
maybe-all-stage3-ld:
maybe-clean-stage3-ld:


.PHONY: all-stageb3g2-ld maybe-all-stageb3g2-ld
.PHONY: clean-stageb3g2-ld maybe-clean-stageb3g2-ld
maybe-all-stageb3g2-ld:
maybe-clean-stageb3g2-ld:


.PHONY: all-stage4-ld maybe-all-stage4-ld
.PHONY: clean-stage4-ld maybe-clean-stage4-ld
maybe-all-stage4-ld:
maybe-clean-stage4-ld:


.PHONY: all-stageprofile-ld maybe-all-stageprofile-ld
.PHONY: clean-stageprofile-ld maybe-clean-stageprofile-ld
maybe-all-stageprofile-ld:
maybe-clean-stageprofile-ld:


.PHONY: all-stagefeedback-ld maybe-all-stagefeedback-ld
.PHONY: clean-stagefeedback-ld maybe-clean-stagefeedback-ld
maybe-all-stagefeedback-ld:
maybe-clean-stagefeedback-ld:





.PHONY: check-ld maybe-check-ld
maybe-check-ld:

.PHONY: install-ld maybe-install-ld
maybe-install-ld:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-ld info-ld
maybe-info-ld:

.PHONY: maybe-dvi-ld dvi-ld
maybe-dvi-ld:

.PHONY: maybe-pdf-ld pdf-ld
maybe-pdf-ld:

.PHONY: maybe-html-ld html-ld
maybe-html-ld:

.PHONY: maybe-TAGS-ld TAGS-ld
maybe-TAGS-ld:

.PHONY: maybe-install-info-ld install-info-ld
maybe-install-info-ld:

.PHONY: maybe-install-pdf-ld install-pdf-ld
maybe-install-pdf-ld:

.PHONY: maybe-install-html-ld install-html-ld
maybe-install-html-ld:

.PHONY: maybe-installcheck-ld installcheck-ld
maybe-installcheck-ld:

.PHONY: maybe-mostlyclean-ld mostlyclean-ld
maybe-mostlyclean-ld:

.PHONY: maybe-clean-ld clean-ld
maybe-clean-ld:

.PHONY: maybe-distclean-ld distclean-ld
maybe-distclean-ld:

.PHONY: maybe-maintainer-clean-ld maintainer-clean-ld
maybe-maintainer-clean-ld:



.PHONY: configure-libcpp maybe-configure-libcpp
maybe-configure-libcpp:
configure-libcpp: stage_current
maybe-configure-libcpp: configure-libcpp
configure-libcpp: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	$(HOST_EXPORTS) \
	echo Configuring in $(HOST_SUBDIR)/libcpp; \
	cd "$(HOST_SUBDIR)/libcpp" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1



.PHONY: configure-stage1-libcpp maybe-configure-stage1-libcpp
maybe-configure-stage1-libcpp:
maybe-configure-stage1-libcpp: configure-stage1-libcpp
configure-stage1-libcpp:
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(HOST_EXPORTS)  \
	CFLAGS="$(STAGE1_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE1_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 1 in $(HOST_SUBDIR)/libcpp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	cd $(HOST_SUBDIR)/libcpp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	   \
	  --disable-intermodule $(STAGE1_CHECKING) 	  --disable-coverage --enable-languages="$(STAGE1_LANGUAGES)" 

.PHONY: configure-stage2-libcpp maybe-configure-stage2-libcpp
maybe-configure-stage2-libcpp:
maybe-configure-stage2-libcpp: configure-stage2-libcpp
configure-stage2-libcpp:
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 2 in $(HOST_SUBDIR)/libcpp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	cd $(HOST_SUBDIR)/libcpp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb2g0-libcpp maybe-configure-stageb2g0-libcpp
maybe-configure-stageb2g0-libcpp:
maybe-configure-stageb2g0-libcpp: configure-stageb2g0-libcpp
configure-stageb2g0-libcpp:
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -g0"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -g0"; export CXXFLAGS;  \
	echo Configuring stage b2g0 in $(HOST_SUBDIR)/libcpp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	cd $(HOST_SUBDIR)/libcpp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage3-libcpp maybe-configure-stage3-libcpp
maybe-configure-stage3-libcpp:
maybe-configure-stage3-libcpp: configure-stage3-libcpp
configure-stage3-libcpp:
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 3 in $(HOST_SUBDIR)/libcpp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	cd $(HOST_SUBDIR)/libcpp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb3g2-libcpp maybe-configure-stageb3g2-libcpp
maybe-configure-stageb3g2-libcpp:
maybe-configure-stageb3g2-libcpp: configure-stageb3g2-libcpp
configure-stageb3g2-libcpp:
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -g2"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -g2"; export CXXFLAGS;  \
	echo Configuring stage b3g2 in $(HOST_SUBDIR)/libcpp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	cd $(HOST_SUBDIR)/libcpp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage4-libcpp maybe-configure-stage4-libcpp
maybe-configure-stage4-libcpp:
maybe-configure-stage4-libcpp: configure-stage4-libcpp
configure-stage4-libcpp:
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE4_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE4_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 4 in $(HOST_SUBDIR)/libcpp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	cd $(HOST_SUBDIR)/libcpp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageprofile-libcpp maybe-configure-stageprofile-libcpp
maybe-configure-stageprofile-libcpp:
maybe-configure-stageprofile-libcpp: configure-stageprofile-libcpp
configure-stageprofile-libcpp:
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CXXFLAGS;  \
	echo Configuring stage profile in $(HOST_SUBDIR)/libcpp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	cd $(HOST_SUBDIR)/libcpp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stagefeedback-libcpp maybe-configure-stagefeedback-libcpp
maybe-configure-stagefeedback-libcpp:
maybe-configure-stagefeedback-libcpp: configure-stagefeedback-libcpp
configure-stagefeedback-libcpp:
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libcpp/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CXXFLAGS;  \
	echo Configuring stage feedback in $(HOST_SUBDIR)/libcpp ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libcpp ; \
	cd $(HOST_SUBDIR)/libcpp || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libcpp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libcpp"; \
	libsrcdir="$$s/libcpp"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   





.PHONY: all-libcpp maybe-all-libcpp
maybe-all-libcpp:
all-libcpp: stage_current
TARGET-libcpp=all
maybe-all-libcpp: all-libcpp
all-libcpp: configure-libcpp
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)  \
		$(TARGET-libcpp))



.PHONY: all-stage1-libcpp maybe-all-stage1-libcpp
.PHONY: clean-stage1-libcpp maybe-clean-stage1-libcpp
maybe-all-stage1-libcpp:
maybe-clean-stage1-libcpp:
maybe-all-stage1-libcpp: all-stage1-libcpp
all-stage1: all-stage1-libcpp
TARGET-stage1-libcpp = $(TARGET-libcpp)
all-stage1-libcpp: configure-stage1-libcpp
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE1_CFLAGS)" CXXFLAGS="$(STAGE1_CFLAGS)" \
		LIBCFLAGS="$(STAGE1_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" $(EXTRA_HOST_FLAGS)   \
		$(TARGET-stage1-libcpp)

maybe-clean-stage1-libcpp: clean-stage1-libcpp
clean-stage1: clean-stage1-libcpp
clean-stage1-libcpp:
	@if [ $(current_stage) = stage1 ]; then \
	  [ -f $(HOST_SUBDIR)/libcpp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage1-libcpp/Makefile ] || exit 0; \
	  $(MAKE) stage1-start; \
	fi; \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		 clean


.PHONY: all-stage2-libcpp maybe-all-stage2-libcpp
.PHONY: clean-stage2-libcpp maybe-clean-stage2-libcpp
maybe-all-stage2-libcpp:
maybe-clean-stage2-libcpp:
maybe-all-stage2-libcpp: all-stage2-libcpp
all-stage2: all-stage2-libcpp
TARGET-stage2-libcpp = $(TARGET-libcpp)
all-stage2-libcpp: configure-stage2-libcpp
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS)" CXXFLAGS="$(STAGE2_CFLAGS)" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage2-libcpp)

maybe-clean-stage2-libcpp: clean-stage2-libcpp
clean-stage2: clean-stage2-libcpp
clean-stage2-libcpp:
	@if [ $(current_stage) = stage2 ]; then \
	  [ -f $(HOST_SUBDIR)/libcpp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage2-libcpp/Makefile ] || exit 0; \
	  $(MAKE) stage2-start; \
	fi; \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb2g0-libcpp maybe-all-stageb2g0-libcpp
.PHONY: clean-stageb2g0-libcpp maybe-clean-stageb2g0-libcpp
maybe-all-stageb2g0-libcpp:
maybe-clean-stageb2g0-libcpp:
maybe-all-stageb2g0-libcpp: all-stageb2g0-libcpp
all-stageb2g0: all-stageb2g0-libcpp
TARGET-stageb2g0-libcpp = $(TARGET-libcpp)
all-stageb2g0-libcpp: configure-stageb2g0-libcpp
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -g0" CXXFLAGS="$(STAGE2_CFLAGS) -g0" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS) -g0" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb2g0-libcpp)

maybe-clean-stageb2g0-libcpp: clean-stageb2g0-libcpp
clean-stageb2g0: clean-stageb2g0-libcpp
clean-stageb2g0-libcpp:
	@if [ $(current_stage) = stageb2g0 ]; then \
	  [ -f $(HOST_SUBDIR)/libcpp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb2g0-libcpp/Makefile ] || exit 0; \
	  $(MAKE) stageb2g0-start; \
	fi; \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage3-libcpp maybe-all-stage3-libcpp
.PHONY: clean-stage3-libcpp maybe-clean-stage3-libcpp
maybe-all-stage3-libcpp:
maybe-clean-stage3-libcpp:
maybe-all-stage3-libcpp: all-stage3-libcpp
all-stage3: all-stage3-libcpp
TARGET-stage3-libcpp = $(TARGET-libcpp)
all-stage3-libcpp: configure-stage3-libcpp
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS)" CXXFLAGS="$(STAGE3_CFLAGS)" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage3-libcpp)

maybe-clean-stage3-libcpp: clean-stage3-libcpp
clean-stage3: clean-stage3-libcpp
clean-stage3-libcpp:
	@if [ $(current_stage) = stage3 ]; then \
	  [ -f $(HOST_SUBDIR)/libcpp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage3-libcpp/Makefile ] || exit 0; \
	  $(MAKE) stage3-start; \
	fi; \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb3g2-libcpp maybe-all-stageb3g2-libcpp
.PHONY: clean-stageb3g2-libcpp maybe-clean-stageb3g2-libcpp
maybe-all-stageb3g2-libcpp:
maybe-clean-stageb3g2-libcpp:
maybe-all-stageb3g2-libcpp: all-stageb3g2-libcpp
all-stageb3g2: all-stageb3g2-libcpp
TARGET-stageb3g2-libcpp = $(TARGET-libcpp)
all-stageb3g2-libcpp: configure-stageb3g2-libcpp
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -g2" CXXFLAGS="$(STAGE3_CFLAGS) -g2" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -g2" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb3g2-libcpp)

maybe-clean-stageb3g2-libcpp: clean-stageb3g2-libcpp
clean-stageb3g2: clean-stageb3g2-libcpp
clean-stageb3g2-libcpp:
	@if [ $(current_stage) = stageb3g2 ]; then \
	  [ -f $(HOST_SUBDIR)/libcpp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb3g2-libcpp/Makefile ] || exit 0; \
	  $(MAKE) stageb3g2-start; \
	fi; \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage4-libcpp maybe-all-stage4-libcpp
.PHONY: clean-stage4-libcpp maybe-clean-stage4-libcpp
maybe-all-stage4-libcpp:
maybe-clean-stage4-libcpp:
maybe-all-stage4-libcpp: all-stage4-libcpp
all-stage4: all-stage4-libcpp
TARGET-stage4-libcpp = $(TARGET-libcpp)
all-stage4-libcpp: configure-stage4-libcpp
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE4_CFLAGS)" CXXFLAGS="$(STAGE4_CFLAGS)" \
		LIBCFLAGS="$(STAGE4_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage4-libcpp)

maybe-clean-stage4-libcpp: clean-stage4-libcpp
clean-stage4: clean-stage4-libcpp
clean-stage4-libcpp:
	@if [ $(current_stage) = stage4 ]; then \
	  [ -f $(HOST_SUBDIR)/libcpp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage4-libcpp/Makefile ] || exit 0; \
	  $(MAKE) stage4-start; \
	fi; \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageprofile-libcpp maybe-all-stageprofile-libcpp
.PHONY: clean-stageprofile-libcpp maybe-clean-stageprofile-libcpp
maybe-all-stageprofile-libcpp:
maybe-clean-stageprofile-libcpp:
maybe-all-stageprofile-libcpp: all-stageprofile-libcpp
all-stageprofile: all-stageprofile-libcpp
TARGET-stageprofile-libcpp = $(TARGET-libcpp)
all-stageprofile-libcpp: configure-stageprofile-libcpp
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageprofile-libcpp)

maybe-clean-stageprofile-libcpp: clean-stageprofile-libcpp
clean-stageprofile: clean-stageprofile-libcpp
clean-stageprofile-libcpp:
	@if [ $(current_stage) = stageprofile ]; then \
	  [ -f $(HOST_SUBDIR)/libcpp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageprofile-libcpp/Makefile ] || exit 0; \
	  $(MAKE) stageprofile-start; \
	fi; \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stagefeedback-libcpp maybe-all-stagefeedback-libcpp
.PHONY: clean-stagefeedback-libcpp maybe-clean-stagefeedback-libcpp
maybe-all-stagefeedback-libcpp:
maybe-clean-stagefeedback-libcpp:
maybe-all-stagefeedback-libcpp: all-stagefeedback-libcpp
all-stagefeedback: all-stagefeedback-libcpp
TARGET-stagefeedback-libcpp = $(TARGET-libcpp)
all-stagefeedback-libcpp: configure-stagefeedback-libcpp
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -fprofile-use" CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stagefeedback-libcpp)

maybe-clean-stagefeedback-libcpp: clean-stagefeedback-libcpp
clean-stagefeedback: clean-stagefeedback-libcpp
clean-stagefeedback-libcpp:
	@if [ $(current_stage) = stagefeedback ]; then \
	  [ -f $(HOST_SUBDIR)/libcpp/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stagefeedback-libcpp/Makefile ] || exit 0; \
	  $(MAKE) stagefeedback-start; \
	fi; \
	cd $(HOST_SUBDIR)/libcpp && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean





.PHONY: check-libcpp maybe-check-libcpp
maybe-check-libcpp:
maybe-check-libcpp: check-libcpp

check-libcpp:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(FLAGS_TO_PASS)  check)


.PHONY: install-libcpp maybe-install-libcpp
maybe-install-libcpp:
maybe-install-libcpp: install-libcpp

install-libcpp: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-libcpp info-libcpp
maybe-info-libcpp:
maybe-info-libcpp: info-libcpp

info-libcpp: \
    configure-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing info in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          info) \
	  || exit 1


.PHONY: maybe-dvi-libcpp dvi-libcpp
maybe-dvi-libcpp:
maybe-dvi-libcpp: dvi-libcpp

dvi-libcpp: \
    configure-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing dvi in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          dvi) \
	  || exit 1


.PHONY: maybe-pdf-libcpp pdf-libcpp
maybe-pdf-libcpp:
maybe-pdf-libcpp: pdf-libcpp

pdf-libcpp: \
    configure-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing pdf in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          pdf) \
	  || exit 1


.PHONY: maybe-html-libcpp html-libcpp
maybe-html-libcpp:
maybe-html-libcpp: html-libcpp

html-libcpp: \
    configure-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing html in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          html) \
	  || exit 1


.PHONY: maybe-TAGS-libcpp TAGS-libcpp
maybe-TAGS-libcpp:
maybe-TAGS-libcpp: TAGS-libcpp

TAGS-libcpp: \
    configure-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing TAGS in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          TAGS) \
	  || exit 1


.PHONY: maybe-install-info-libcpp install-info-libcpp
maybe-install-info-libcpp:
maybe-install-info-libcpp: install-info-libcpp

install-info-libcpp: \
    configure-libcpp \
    info-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-info in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-libcpp install-pdf-libcpp
maybe-install-pdf-libcpp:
maybe-install-pdf-libcpp: install-pdf-libcpp

install-pdf-libcpp: \
    configure-libcpp \
    pdf-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-pdf in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-libcpp install-html-libcpp
maybe-install-html-libcpp:
maybe-install-html-libcpp: install-html-libcpp

install-html-libcpp: \
    configure-libcpp \
    html-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-html in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-html) \
	  || exit 1


.PHONY: maybe-installcheck-libcpp installcheck-libcpp
maybe-installcheck-libcpp:
maybe-installcheck-libcpp: installcheck-libcpp

installcheck-libcpp: \
    configure-libcpp 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing installcheck in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-libcpp mostlyclean-libcpp
maybe-mostlyclean-libcpp:
maybe-mostlyclean-libcpp: mostlyclean-libcpp

mostlyclean-libcpp: 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing mostlyclean in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-libcpp clean-libcpp
maybe-clean-libcpp:
maybe-clean-libcpp: clean-libcpp

clean-libcpp: 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing clean in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          clean) \
	  || exit 1


.PHONY: maybe-distclean-libcpp distclean-libcpp
maybe-distclean-libcpp:
maybe-distclean-libcpp: distclean-libcpp

distclean-libcpp: 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing distclean in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-libcpp maintainer-clean-libcpp
maybe-maintainer-clean-libcpp:
maybe-maintainer-clean-libcpp: maintainer-clean-libcpp

maintainer-clean-libcpp: 
	@[ -f ./libcpp/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing maintainer-clean in libcpp" ; \
	(cd $(HOST_SUBDIR)/libcpp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          maintainer-clean) \
	  || exit 1




.PHONY: configure-libdecnumber maybe-configure-libdecnumber
maybe-configure-libdecnumber:
configure-libdecnumber: stage_current
maybe-configure-libdecnumber: configure-libdecnumber
configure-libdecnumber: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	$(HOST_EXPORTS) \
	echo Configuring in $(HOST_SUBDIR)/libdecnumber; \
	cd "$(HOST_SUBDIR)/libdecnumber" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1



.PHONY: configure-stage1-libdecnumber maybe-configure-stage1-libdecnumber
maybe-configure-stage1-libdecnumber:
maybe-configure-stage1-libdecnumber: configure-stage1-libdecnumber
configure-stage1-libdecnumber:
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(HOST_EXPORTS)  \
	CFLAGS="$(STAGE1_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE1_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 1 in $(HOST_SUBDIR)/libdecnumber ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	cd $(HOST_SUBDIR)/libdecnumber || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	   \
	  --disable-intermodule $(STAGE1_CHECKING) 	  --disable-coverage --enable-languages="$(STAGE1_LANGUAGES)" 

.PHONY: configure-stage2-libdecnumber maybe-configure-stage2-libdecnumber
maybe-configure-stage2-libdecnumber:
maybe-configure-stage2-libdecnumber: configure-stage2-libdecnumber
configure-stage2-libdecnumber:
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 2 in $(HOST_SUBDIR)/libdecnumber ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	cd $(HOST_SUBDIR)/libdecnumber || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb2g0-libdecnumber maybe-configure-stageb2g0-libdecnumber
maybe-configure-stageb2g0-libdecnumber:
maybe-configure-stageb2g0-libdecnumber: configure-stageb2g0-libdecnumber
configure-stageb2g0-libdecnumber:
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -g0"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -g0"; export CXXFLAGS;  \
	echo Configuring stage b2g0 in $(HOST_SUBDIR)/libdecnumber ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	cd $(HOST_SUBDIR)/libdecnumber || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage3-libdecnumber maybe-configure-stage3-libdecnumber
maybe-configure-stage3-libdecnumber:
maybe-configure-stage3-libdecnumber: configure-stage3-libdecnumber
configure-stage3-libdecnumber:
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 3 in $(HOST_SUBDIR)/libdecnumber ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	cd $(HOST_SUBDIR)/libdecnumber || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb3g2-libdecnumber maybe-configure-stageb3g2-libdecnumber
maybe-configure-stageb3g2-libdecnumber:
maybe-configure-stageb3g2-libdecnumber: configure-stageb3g2-libdecnumber
configure-stageb3g2-libdecnumber:
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -g2"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -g2"; export CXXFLAGS;  \
	echo Configuring stage b3g2 in $(HOST_SUBDIR)/libdecnumber ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	cd $(HOST_SUBDIR)/libdecnumber || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage4-libdecnumber maybe-configure-stage4-libdecnumber
maybe-configure-stage4-libdecnumber:
maybe-configure-stage4-libdecnumber: configure-stage4-libdecnumber
configure-stage4-libdecnumber:
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE4_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE4_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 4 in $(HOST_SUBDIR)/libdecnumber ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	cd $(HOST_SUBDIR)/libdecnumber || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageprofile-libdecnumber maybe-configure-stageprofile-libdecnumber
maybe-configure-stageprofile-libdecnumber:
maybe-configure-stageprofile-libdecnumber: configure-stageprofile-libdecnumber
configure-stageprofile-libdecnumber:
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CXXFLAGS;  \
	echo Configuring stage profile in $(HOST_SUBDIR)/libdecnumber ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	cd $(HOST_SUBDIR)/libdecnumber || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stagefeedback-libdecnumber maybe-configure-stagefeedback-libdecnumber
maybe-configure-stagefeedback-libdecnumber:
maybe-configure-stagefeedback-libdecnumber: configure-stagefeedback-libdecnumber
configure-stagefeedback-libdecnumber:
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libdecnumber/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CXXFLAGS;  \
	echo Configuring stage feedback in $(HOST_SUBDIR)/libdecnumber ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libdecnumber ; \
	cd $(HOST_SUBDIR)/libdecnumber || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libdecnumber/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libdecnumber"; \
	libsrcdir="$$s/libdecnumber"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   





.PHONY: all-libdecnumber maybe-all-libdecnumber
maybe-all-libdecnumber:
all-libdecnumber: stage_current
TARGET-libdecnumber=all
maybe-all-libdecnumber: all-libdecnumber
all-libdecnumber: configure-libdecnumber
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)  \
		$(TARGET-libdecnumber))



.PHONY: all-stage1-libdecnumber maybe-all-stage1-libdecnumber
.PHONY: clean-stage1-libdecnumber maybe-clean-stage1-libdecnumber
maybe-all-stage1-libdecnumber:
maybe-clean-stage1-libdecnumber:
maybe-all-stage1-libdecnumber: all-stage1-libdecnumber
all-stage1: all-stage1-libdecnumber
TARGET-stage1-libdecnumber = $(TARGET-libdecnumber)
all-stage1-libdecnumber: configure-stage1-libdecnumber
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE1_CFLAGS)" CXXFLAGS="$(STAGE1_CFLAGS)" \
		LIBCFLAGS="$(STAGE1_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" $(EXTRA_HOST_FLAGS)   \
		$(TARGET-stage1-libdecnumber)

maybe-clean-stage1-libdecnumber: clean-stage1-libdecnumber
clean-stage1: clean-stage1-libdecnumber
clean-stage1-libdecnumber:
	@if [ $(current_stage) = stage1 ]; then \
	  [ -f $(HOST_SUBDIR)/libdecnumber/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage1-libdecnumber/Makefile ] || exit 0; \
	  $(MAKE) stage1-start; \
	fi; \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		 clean


.PHONY: all-stage2-libdecnumber maybe-all-stage2-libdecnumber
.PHONY: clean-stage2-libdecnumber maybe-clean-stage2-libdecnumber
maybe-all-stage2-libdecnumber:
maybe-clean-stage2-libdecnumber:
maybe-all-stage2-libdecnumber: all-stage2-libdecnumber
all-stage2: all-stage2-libdecnumber
TARGET-stage2-libdecnumber = $(TARGET-libdecnumber)
all-stage2-libdecnumber: configure-stage2-libdecnumber
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS)" CXXFLAGS="$(STAGE2_CFLAGS)" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage2-libdecnumber)

maybe-clean-stage2-libdecnumber: clean-stage2-libdecnumber
clean-stage2: clean-stage2-libdecnumber
clean-stage2-libdecnumber:
	@if [ $(current_stage) = stage2 ]; then \
	  [ -f $(HOST_SUBDIR)/libdecnumber/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage2-libdecnumber/Makefile ] || exit 0; \
	  $(MAKE) stage2-start; \
	fi; \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb2g0-libdecnumber maybe-all-stageb2g0-libdecnumber
.PHONY: clean-stageb2g0-libdecnumber maybe-clean-stageb2g0-libdecnumber
maybe-all-stageb2g0-libdecnumber:
maybe-clean-stageb2g0-libdecnumber:
maybe-all-stageb2g0-libdecnumber: all-stageb2g0-libdecnumber
all-stageb2g0: all-stageb2g0-libdecnumber
TARGET-stageb2g0-libdecnumber = $(TARGET-libdecnumber)
all-stageb2g0-libdecnumber: configure-stageb2g0-libdecnumber
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -g0" CXXFLAGS="$(STAGE2_CFLAGS) -g0" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS) -g0" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb2g0-libdecnumber)

maybe-clean-stageb2g0-libdecnumber: clean-stageb2g0-libdecnumber
clean-stageb2g0: clean-stageb2g0-libdecnumber
clean-stageb2g0-libdecnumber:
	@if [ $(current_stage) = stageb2g0 ]; then \
	  [ -f $(HOST_SUBDIR)/libdecnumber/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb2g0-libdecnumber/Makefile ] || exit 0; \
	  $(MAKE) stageb2g0-start; \
	fi; \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage3-libdecnumber maybe-all-stage3-libdecnumber
.PHONY: clean-stage3-libdecnumber maybe-clean-stage3-libdecnumber
maybe-all-stage3-libdecnumber:
maybe-clean-stage3-libdecnumber:
maybe-all-stage3-libdecnumber: all-stage3-libdecnumber
all-stage3: all-stage3-libdecnumber
TARGET-stage3-libdecnumber = $(TARGET-libdecnumber)
all-stage3-libdecnumber: configure-stage3-libdecnumber
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS)" CXXFLAGS="$(STAGE3_CFLAGS)" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage3-libdecnumber)

maybe-clean-stage3-libdecnumber: clean-stage3-libdecnumber
clean-stage3: clean-stage3-libdecnumber
clean-stage3-libdecnumber:
	@if [ $(current_stage) = stage3 ]; then \
	  [ -f $(HOST_SUBDIR)/libdecnumber/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage3-libdecnumber/Makefile ] || exit 0; \
	  $(MAKE) stage3-start; \
	fi; \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb3g2-libdecnumber maybe-all-stageb3g2-libdecnumber
.PHONY: clean-stageb3g2-libdecnumber maybe-clean-stageb3g2-libdecnumber
maybe-all-stageb3g2-libdecnumber:
maybe-clean-stageb3g2-libdecnumber:
maybe-all-stageb3g2-libdecnumber: all-stageb3g2-libdecnumber
all-stageb3g2: all-stageb3g2-libdecnumber
TARGET-stageb3g2-libdecnumber = $(TARGET-libdecnumber)
all-stageb3g2-libdecnumber: configure-stageb3g2-libdecnumber
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -g2" CXXFLAGS="$(STAGE3_CFLAGS) -g2" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -g2" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb3g2-libdecnumber)

maybe-clean-stageb3g2-libdecnumber: clean-stageb3g2-libdecnumber
clean-stageb3g2: clean-stageb3g2-libdecnumber
clean-stageb3g2-libdecnumber:
	@if [ $(current_stage) = stageb3g2 ]; then \
	  [ -f $(HOST_SUBDIR)/libdecnumber/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb3g2-libdecnumber/Makefile ] || exit 0; \
	  $(MAKE) stageb3g2-start; \
	fi; \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage4-libdecnumber maybe-all-stage4-libdecnumber
.PHONY: clean-stage4-libdecnumber maybe-clean-stage4-libdecnumber
maybe-all-stage4-libdecnumber:
maybe-clean-stage4-libdecnumber:
maybe-all-stage4-libdecnumber: all-stage4-libdecnumber
all-stage4: all-stage4-libdecnumber
TARGET-stage4-libdecnumber = $(TARGET-libdecnumber)
all-stage4-libdecnumber: configure-stage4-libdecnumber
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE4_CFLAGS)" CXXFLAGS="$(STAGE4_CFLAGS)" \
		LIBCFLAGS="$(STAGE4_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage4-libdecnumber)

maybe-clean-stage4-libdecnumber: clean-stage4-libdecnumber
clean-stage4: clean-stage4-libdecnumber
clean-stage4-libdecnumber:
	@if [ $(current_stage) = stage4 ]; then \
	  [ -f $(HOST_SUBDIR)/libdecnumber/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage4-libdecnumber/Makefile ] || exit 0; \
	  $(MAKE) stage4-start; \
	fi; \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageprofile-libdecnumber maybe-all-stageprofile-libdecnumber
.PHONY: clean-stageprofile-libdecnumber maybe-clean-stageprofile-libdecnumber
maybe-all-stageprofile-libdecnumber:
maybe-clean-stageprofile-libdecnumber:
maybe-all-stageprofile-libdecnumber: all-stageprofile-libdecnumber
all-stageprofile: all-stageprofile-libdecnumber
TARGET-stageprofile-libdecnumber = $(TARGET-libdecnumber)
all-stageprofile-libdecnumber: configure-stageprofile-libdecnumber
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageprofile-libdecnumber)

maybe-clean-stageprofile-libdecnumber: clean-stageprofile-libdecnumber
clean-stageprofile: clean-stageprofile-libdecnumber
clean-stageprofile-libdecnumber:
	@if [ $(current_stage) = stageprofile ]; then \
	  [ -f $(HOST_SUBDIR)/libdecnumber/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageprofile-libdecnumber/Makefile ] || exit 0; \
	  $(MAKE) stageprofile-start; \
	fi; \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stagefeedback-libdecnumber maybe-all-stagefeedback-libdecnumber
.PHONY: clean-stagefeedback-libdecnumber maybe-clean-stagefeedback-libdecnumber
maybe-all-stagefeedback-libdecnumber:
maybe-clean-stagefeedback-libdecnumber:
maybe-all-stagefeedback-libdecnumber: all-stagefeedback-libdecnumber
all-stagefeedback: all-stagefeedback-libdecnumber
TARGET-stagefeedback-libdecnumber = $(TARGET-libdecnumber)
all-stagefeedback-libdecnumber: configure-stagefeedback-libdecnumber
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -fprofile-use" CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stagefeedback-libdecnumber)

maybe-clean-stagefeedback-libdecnumber: clean-stagefeedback-libdecnumber
clean-stagefeedback: clean-stagefeedback-libdecnumber
clean-stagefeedback-libdecnumber:
	@if [ $(current_stage) = stagefeedback ]; then \
	  [ -f $(HOST_SUBDIR)/libdecnumber/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stagefeedback-libdecnumber/Makefile ] || exit 0; \
	  $(MAKE) stagefeedback-start; \
	fi; \
	cd $(HOST_SUBDIR)/libdecnumber && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean





.PHONY: check-libdecnumber maybe-check-libdecnumber
maybe-check-libdecnumber:
maybe-check-libdecnumber: check-libdecnumber

check-libdecnumber:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(FLAGS_TO_PASS)  check)


.PHONY: install-libdecnumber maybe-install-libdecnumber
maybe-install-libdecnumber:
maybe-install-libdecnumber: install-libdecnumber

install-libdecnumber: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-libdecnumber info-libdecnumber
maybe-info-libdecnumber:
maybe-info-libdecnumber: info-libdecnumber

info-libdecnumber: \
    configure-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing info in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          info) \
	  || exit 1


.PHONY: maybe-dvi-libdecnumber dvi-libdecnumber
maybe-dvi-libdecnumber:
maybe-dvi-libdecnumber: dvi-libdecnumber

dvi-libdecnumber: \
    configure-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing dvi in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          dvi) \
	  || exit 1


.PHONY: maybe-pdf-libdecnumber pdf-libdecnumber
maybe-pdf-libdecnumber:
maybe-pdf-libdecnumber: pdf-libdecnumber

pdf-libdecnumber: \
    configure-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing pdf in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          pdf) \
	  || exit 1


.PHONY: maybe-html-libdecnumber html-libdecnumber
maybe-html-libdecnumber:
maybe-html-libdecnumber: html-libdecnumber

html-libdecnumber: \
    configure-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing html in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          html) \
	  || exit 1


.PHONY: maybe-TAGS-libdecnumber TAGS-libdecnumber
maybe-TAGS-libdecnumber:
maybe-TAGS-libdecnumber: TAGS-libdecnumber

TAGS-libdecnumber: \
    configure-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing TAGS in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          TAGS) \
	  || exit 1


.PHONY: maybe-install-info-libdecnumber install-info-libdecnumber
maybe-install-info-libdecnumber:
maybe-install-info-libdecnumber: install-info-libdecnumber

install-info-libdecnumber: \
    configure-libdecnumber \
    info-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-info in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-libdecnumber install-pdf-libdecnumber
maybe-install-pdf-libdecnumber:
maybe-install-pdf-libdecnumber: install-pdf-libdecnumber

install-pdf-libdecnumber: \
    configure-libdecnumber \
    pdf-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-pdf in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-libdecnumber install-html-libdecnumber
maybe-install-html-libdecnumber:
maybe-install-html-libdecnumber: install-html-libdecnumber

install-html-libdecnumber: \
    configure-libdecnumber \
    html-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-html in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-html) \
	  || exit 1


.PHONY: maybe-installcheck-libdecnumber installcheck-libdecnumber
maybe-installcheck-libdecnumber:
maybe-installcheck-libdecnumber: installcheck-libdecnumber

installcheck-libdecnumber: \
    configure-libdecnumber 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing installcheck in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-libdecnumber mostlyclean-libdecnumber
maybe-mostlyclean-libdecnumber:
maybe-mostlyclean-libdecnumber: mostlyclean-libdecnumber

mostlyclean-libdecnumber: 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing mostlyclean in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-libdecnumber clean-libdecnumber
maybe-clean-libdecnumber:
maybe-clean-libdecnumber: clean-libdecnumber

clean-libdecnumber: 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing clean in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          clean) \
	  || exit 1


.PHONY: maybe-distclean-libdecnumber distclean-libdecnumber
maybe-distclean-libdecnumber:
maybe-distclean-libdecnumber: distclean-libdecnumber

distclean-libdecnumber: 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing distclean in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-libdecnumber maintainer-clean-libdecnumber
maybe-maintainer-clean-libdecnumber:
maybe-maintainer-clean-libdecnumber: maintainer-clean-libdecnumber

maintainer-clean-libdecnumber: 
	@[ -f ./libdecnumber/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing maintainer-clean in libdecnumber" ; \
	(cd $(HOST_SUBDIR)/libdecnumber && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          maintainer-clean) \
	  || exit 1




.PHONY: configure-libgui maybe-configure-libgui
maybe-configure-libgui:
configure-libgui: stage_current





.PHONY: all-libgui maybe-all-libgui
maybe-all-libgui:
all-libgui: stage_current




.PHONY: check-libgui maybe-check-libgui
maybe-check-libgui:

.PHONY: install-libgui maybe-install-libgui
maybe-install-libgui:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-libgui info-libgui
maybe-info-libgui:

.PHONY: maybe-dvi-libgui dvi-libgui
maybe-dvi-libgui:

.PHONY: maybe-pdf-libgui pdf-libgui
maybe-pdf-libgui:

.PHONY: maybe-html-libgui html-libgui
maybe-html-libgui:

.PHONY: maybe-TAGS-libgui TAGS-libgui
maybe-TAGS-libgui:

.PHONY: maybe-install-info-libgui install-info-libgui
maybe-install-info-libgui:

.PHONY: maybe-install-pdf-libgui install-pdf-libgui
maybe-install-pdf-libgui:

.PHONY: maybe-install-html-libgui install-html-libgui
maybe-install-html-libgui:

.PHONY: maybe-installcheck-libgui installcheck-libgui
maybe-installcheck-libgui:

.PHONY: maybe-mostlyclean-libgui mostlyclean-libgui
maybe-mostlyclean-libgui:

.PHONY: maybe-clean-libgui clean-libgui
maybe-clean-libgui:

.PHONY: maybe-distclean-libgui distclean-libgui
maybe-distclean-libgui:

.PHONY: maybe-maintainer-clean-libgui maintainer-clean-libgui
maybe-maintainer-clean-libgui:



.PHONY: configure-libiberty maybe-configure-libiberty
maybe-configure-libiberty:
configure-libiberty: stage_current
maybe-configure-libiberty: configure-libiberty
configure-libiberty: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	$(HOST_EXPORTS) \
	echo Configuring in $(HOST_SUBDIR)/libiberty; \
	cd "$(HOST_SUBDIR)/libiberty" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1



.PHONY: configure-stage1-libiberty maybe-configure-stage1-libiberty
maybe-configure-stage1-libiberty:
maybe-configure-stage1-libiberty: configure-stage1-libiberty
configure-stage1-libiberty:
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(HOST_EXPORTS)  \
	CFLAGS="$(STAGE1_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE1_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 1 in $(HOST_SUBDIR)/libiberty ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	cd $(HOST_SUBDIR)/libiberty || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	   \
	  --disable-intermodule $(STAGE1_CHECKING) 	  --disable-coverage --enable-languages="$(STAGE1_LANGUAGES)" 

.PHONY: configure-stage2-libiberty maybe-configure-stage2-libiberty
maybe-configure-stage2-libiberty:
maybe-configure-stage2-libiberty: configure-stage2-libiberty
configure-stage2-libiberty:
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 2 in $(HOST_SUBDIR)/libiberty ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	cd $(HOST_SUBDIR)/libiberty || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb2g0-libiberty maybe-configure-stageb2g0-libiberty
maybe-configure-stageb2g0-libiberty:
maybe-configure-stageb2g0-libiberty: configure-stageb2g0-libiberty
configure-stageb2g0-libiberty:
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -g0"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -g0"; export CXXFLAGS;  \
	echo Configuring stage b2g0 in $(HOST_SUBDIR)/libiberty ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	cd $(HOST_SUBDIR)/libiberty || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage3-libiberty maybe-configure-stage3-libiberty
maybe-configure-stage3-libiberty:
maybe-configure-stage3-libiberty: configure-stage3-libiberty
configure-stage3-libiberty:
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 3 in $(HOST_SUBDIR)/libiberty ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	cd $(HOST_SUBDIR)/libiberty || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb3g2-libiberty maybe-configure-stageb3g2-libiberty
maybe-configure-stageb3g2-libiberty:
maybe-configure-stageb3g2-libiberty: configure-stageb3g2-libiberty
configure-stageb3g2-libiberty:
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -g2"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -g2"; export CXXFLAGS;  \
	echo Configuring stage b3g2 in $(HOST_SUBDIR)/libiberty ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	cd $(HOST_SUBDIR)/libiberty || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage4-libiberty maybe-configure-stage4-libiberty
maybe-configure-stage4-libiberty:
maybe-configure-stage4-libiberty: configure-stage4-libiberty
configure-stage4-libiberty:
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE4_CFLAGS)"; export CFLAGS; \
	CXXFLAGS="$(STAGE4_CFLAGS)"; export CXXFLAGS;  \
	echo Configuring stage 4 in $(HOST_SUBDIR)/libiberty ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	cd $(HOST_SUBDIR)/libiberty || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageprofile-libiberty maybe-configure-stageprofile-libiberty
maybe-configure-stageprofile-libiberty:
maybe-configure-stageprofile-libiberty: configure-stageprofile-libiberty
configure-stageprofile-libiberty:
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate"; export CXXFLAGS;  \
	echo Configuring stage profile in $(HOST_SUBDIR)/libiberty ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	cd $(HOST_SUBDIR)/libiberty || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stagefeedback-libiberty maybe-configure-stagefeedback-libiberty
maybe-configure-stagefeedback-libiberty:
maybe-configure-stagefeedback-libiberty: configure-stagefeedback-libiberty
configure-stagefeedback-libiberty:
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	test ! -f $(HOST_SUBDIR)/libiberty/Makefile || exit 0; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS)  \
	CFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use"; export CXXFLAGS;  \
	echo Configuring stage feedback in $(HOST_SUBDIR)/libiberty ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)/libiberty ; \
	cd $(HOST_SUBDIR)/libiberty || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(HOST_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(HOST_CONFIGARGS) --build=${build_alias} --host=${host_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   





.PHONY: all-libiberty maybe-all-libiberty
maybe-all-libiberty:
all-libiberty: stage_current
TARGET-libiberty=all
maybe-all-libiberty: all-libiberty
all-libiberty: configure-libiberty
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)  \
		$(TARGET-libiberty))



.PHONY: all-stage1-libiberty maybe-all-stage1-libiberty
.PHONY: clean-stage1-libiberty maybe-clean-stage1-libiberty
maybe-all-stage1-libiberty:
maybe-clean-stage1-libiberty:
maybe-all-stage1-libiberty: all-stage1-libiberty
all-stage1: all-stage1-libiberty
TARGET-stage1-libiberty = $(TARGET-libiberty)
all-stage1-libiberty: configure-stage1-libiberty
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE1_CFLAGS)" CXXFLAGS="$(STAGE1_CFLAGS)" \
		LIBCFLAGS="$(STAGE1_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" $(EXTRA_HOST_FLAGS)   \
		$(TARGET-stage1-libiberty)

maybe-clean-stage1-libiberty: clean-stage1-libiberty
clean-stage1: clean-stage1-libiberty
clean-stage1-libiberty:
	@if [ $(current_stage) = stage1 ]; then \
	  [ -f $(HOST_SUBDIR)/libiberty/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage1-libiberty/Makefile ] || exit 0; \
	  $(MAKE) stage1-start; \
	fi; \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		 clean


.PHONY: all-stage2-libiberty maybe-all-stage2-libiberty
.PHONY: clean-stage2-libiberty maybe-clean-stage2-libiberty
maybe-all-stage2-libiberty:
maybe-clean-stage2-libiberty:
maybe-all-stage2-libiberty: all-stage2-libiberty
all-stage2: all-stage2-libiberty
TARGET-stage2-libiberty = $(TARGET-libiberty)
all-stage2-libiberty: configure-stage2-libiberty
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS)" CXXFLAGS="$(STAGE2_CFLAGS)" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage2-libiberty)

maybe-clean-stage2-libiberty: clean-stage2-libiberty
clean-stage2: clean-stage2-libiberty
clean-stage2-libiberty:
	@if [ $(current_stage) = stage2 ]; then \
	  [ -f $(HOST_SUBDIR)/libiberty/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage2-libiberty/Makefile ] || exit 0; \
	  $(MAKE) stage2-start; \
	fi; \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb2g0-libiberty maybe-all-stageb2g0-libiberty
.PHONY: clean-stageb2g0-libiberty maybe-clean-stageb2g0-libiberty
maybe-all-stageb2g0-libiberty:
maybe-clean-stageb2g0-libiberty:
maybe-all-stageb2g0-libiberty: all-stageb2g0-libiberty
all-stageb2g0: all-stageb2g0-libiberty
TARGET-stageb2g0-libiberty = $(TARGET-libiberty)
all-stageb2g0-libiberty: configure-stageb2g0-libiberty
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -g0" CXXFLAGS="$(STAGE2_CFLAGS) -g0" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS) -g0" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb2g0-libiberty)

maybe-clean-stageb2g0-libiberty: clean-stageb2g0-libiberty
clean-stageb2g0: clean-stageb2g0-libiberty
clean-stageb2g0-libiberty:
	@if [ $(current_stage) = stageb2g0 ]; then \
	  [ -f $(HOST_SUBDIR)/libiberty/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb2g0-libiberty/Makefile ] || exit 0; \
	  $(MAKE) stageb2g0-start; \
	fi; \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage3-libiberty maybe-all-stage3-libiberty
.PHONY: clean-stage3-libiberty maybe-clean-stage3-libiberty
maybe-all-stage3-libiberty:
maybe-clean-stage3-libiberty:
maybe-all-stage3-libiberty: all-stage3-libiberty
all-stage3: all-stage3-libiberty
TARGET-stage3-libiberty = $(TARGET-libiberty)
all-stage3-libiberty: configure-stage3-libiberty
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS)" CXXFLAGS="$(STAGE3_CFLAGS)" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage3-libiberty)

maybe-clean-stage3-libiberty: clean-stage3-libiberty
clean-stage3: clean-stage3-libiberty
clean-stage3-libiberty:
	@if [ $(current_stage) = stage3 ]; then \
	  [ -f $(HOST_SUBDIR)/libiberty/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage3-libiberty/Makefile ] || exit 0; \
	  $(MAKE) stage3-start; \
	fi; \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageb3g2-libiberty maybe-all-stageb3g2-libiberty
.PHONY: clean-stageb3g2-libiberty maybe-clean-stageb3g2-libiberty
maybe-all-stageb3g2-libiberty:
maybe-clean-stageb3g2-libiberty:
maybe-all-stageb3g2-libiberty: all-stageb3g2-libiberty
all-stageb3g2: all-stageb3g2-libiberty
TARGET-stageb3g2-libiberty = $(TARGET-libiberty)
all-stageb3g2-libiberty: configure-stageb3g2-libiberty
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -g2" CXXFLAGS="$(STAGE3_CFLAGS) -g2" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -g2" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageb3g2-libiberty)

maybe-clean-stageb3g2-libiberty: clean-stageb3g2-libiberty
clean-stageb3g2: clean-stageb3g2-libiberty
clean-stageb3g2-libiberty:
	@if [ $(current_stage) = stageb3g2 ]; then \
	  [ -f $(HOST_SUBDIR)/libiberty/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageb3g2-libiberty/Makefile ] || exit 0; \
	  $(MAKE) stageb3g2-start; \
	fi; \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stage4-libiberty maybe-all-stage4-libiberty
.PHONY: clean-stage4-libiberty maybe-clean-stage4-libiberty
maybe-all-stage4-libiberty:
maybe-clean-stage4-libiberty:
maybe-all-stage4-libiberty: all-stage4-libiberty
all-stage4: all-stage4-libiberty
TARGET-stage4-libiberty = $(TARGET-libiberty)
all-stage4-libiberty: configure-stage4-libiberty
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE4_CFLAGS)" CXXFLAGS="$(STAGE4_CFLAGS)" \
		LIBCFLAGS="$(STAGE4_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stage4-libiberty)

maybe-clean-stage4-libiberty: clean-stage4-libiberty
clean-stage4: clean-stage4-libiberty
clean-stage4-libiberty:
	@if [ $(current_stage) = stage4 ]; then \
	  [ -f $(HOST_SUBDIR)/libiberty/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stage4-libiberty/Makefile ] || exit 0; \
	  $(MAKE) stage4-start; \
	fi; \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stageprofile-libiberty maybe-all-stageprofile-libiberty
.PHONY: clean-stageprofile-libiberty maybe-clean-stageprofile-libiberty
maybe-all-stageprofile-libiberty:
maybe-clean-stageprofile-libiberty:
maybe-all-stageprofile-libiberty: all-stageprofile-libiberty
all-stageprofile: all-stageprofile-libiberty
TARGET-stageprofile-libiberty = $(TARGET-libiberty)
all-stageprofile-libiberty: configure-stageprofile-libiberty
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stageprofile-libiberty)

maybe-clean-stageprofile-libiberty: clean-stageprofile-libiberty
clean-stageprofile: clean-stageprofile-libiberty
clean-stageprofile-libiberty:
	@if [ $(current_stage) = stageprofile ]; then \
	  [ -f $(HOST_SUBDIR)/libiberty/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stageprofile-libiberty/Makefile ] || exit 0; \
	  $(MAKE) stageprofile-start; \
	fi; \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean


.PHONY: all-stagefeedback-libiberty maybe-all-stagefeedback-libiberty
.PHONY: clean-stagefeedback-libiberty maybe-clean-stagefeedback-libiberty
maybe-all-stagefeedback-libiberty:
maybe-clean-stagefeedback-libiberty:
maybe-all-stagefeedback-libiberty: all-stagefeedback-libiberty
all-stagefeedback: all-stagefeedback-libiberty
TARGET-stagefeedback-libiberty = $(TARGET-libiberty)
all-stagefeedback-libiberty: configure-stagefeedback-libiberty
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	$(POSTSTAGE1_HOST_EXPORTS) \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -fprofile-use" CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" $(EXTRA_HOST_FLAGS) $(POSTSTAGE1_FLAGS_TO_PASS)  \
		$(TARGET-stagefeedback-libiberty)

maybe-clean-stagefeedback-libiberty: clean-stagefeedback-libiberty
clean-stagefeedback: clean-stagefeedback-libiberty
clean-stagefeedback-libiberty:
	@if [ $(current_stage) = stagefeedback ]; then \
	  [ -f $(HOST_SUBDIR)/libiberty/Makefile ] || exit 0; \
	else \
	  [ -f $(HOST_SUBDIR)/stagefeedback-libiberty/Makefile ] || exit 0; \
	  $(MAKE) stagefeedback-start; \
	fi; \
	cd $(HOST_SUBDIR)/libiberty && \
	$(MAKE) $(EXTRA_HOST_FLAGS)  \
		$(POSTSTAGE1_FLAGS_TO_PASS)  \
		 clean





.PHONY: check-libiberty maybe-check-libiberty
maybe-check-libiberty:
maybe-check-libiberty: check-libiberty

check-libiberty:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(FLAGS_TO_PASS)  check)


.PHONY: install-libiberty maybe-install-libiberty
maybe-install-libiberty:
maybe-install-libiberty: install-libiberty

install-libiberty: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-libiberty info-libiberty
maybe-info-libiberty:
maybe-info-libiberty: info-libiberty

info-libiberty: \
    configure-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing info in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          info) \
	  || exit 1


.PHONY: maybe-dvi-libiberty dvi-libiberty
maybe-dvi-libiberty:
maybe-dvi-libiberty: dvi-libiberty

dvi-libiberty: \
    configure-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing dvi in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          dvi) \
	  || exit 1


.PHONY: maybe-pdf-libiberty pdf-libiberty
maybe-pdf-libiberty:
maybe-pdf-libiberty: pdf-libiberty

pdf-libiberty: \
    configure-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing pdf in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          pdf) \
	  || exit 1


.PHONY: maybe-html-libiberty html-libiberty
maybe-html-libiberty:
maybe-html-libiberty: html-libiberty

html-libiberty: \
    configure-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing html in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          html) \
	  || exit 1


.PHONY: maybe-TAGS-libiberty TAGS-libiberty
maybe-TAGS-libiberty:
maybe-TAGS-libiberty: TAGS-libiberty

TAGS-libiberty: \
    configure-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing TAGS in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          TAGS) \
	  || exit 1


.PHONY: maybe-install-info-libiberty install-info-libiberty
maybe-install-info-libiberty:
maybe-install-info-libiberty: install-info-libiberty

install-info-libiberty: \
    configure-libiberty \
    info-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-info in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-libiberty install-pdf-libiberty
maybe-install-pdf-libiberty:
maybe-install-pdf-libiberty: install-pdf-libiberty

install-pdf-libiberty: \
    configure-libiberty \
    pdf-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-pdf in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-libiberty install-html-libiberty
maybe-install-html-libiberty:
maybe-install-html-libiberty: install-html-libiberty

install-html-libiberty: \
    configure-libiberty \
    html-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing install-html in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          install-html) \
	  || exit 1


.PHONY: maybe-installcheck-libiberty installcheck-libiberty
maybe-installcheck-libiberty:
maybe-installcheck-libiberty: installcheck-libiberty

installcheck-libiberty: \
    configure-libiberty 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing installcheck in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-libiberty mostlyclean-libiberty
maybe-mostlyclean-libiberty:
maybe-mostlyclean-libiberty: mostlyclean-libiberty

mostlyclean-libiberty: 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing mostlyclean in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-libiberty clean-libiberty
maybe-clean-libiberty:
maybe-clean-libiberty: clean-libiberty

clean-libiberty: 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing clean in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          clean) \
	  || exit 1


.PHONY: maybe-distclean-libiberty distclean-libiberty
maybe-distclean-libiberty:
maybe-distclean-libiberty: distclean-libiberty

distclean-libiberty: 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing distclean in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-libiberty maintainer-clean-libiberty
maybe-maintainer-clean-libiberty:
maybe-maintainer-clean-libiberty: maintainer-clean-libiberty

maintainer-clean-libiberty: 
	@[ -f ./libiberty/Makefile ] || exit 0; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(HOST_EXPORTS) \
	for flag in $(EXTRA_HOST_FLAGS) ; do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	echo "Doing maintainer-clean in libiberty" ; \
	(cd $(HOST_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	          maintainer-clean) \
	  || exit 1




.PHONY: configure-libiconv maybe-configure-libiconv
maybe-configure-libiconv:
configure-libiconv: stage_current





.PHONY: all-libiconv maybe-all-libiconv
maybe-all-libiconv:
all-libiconv: stage_current




.PHONY: check-libiconv maybe-check-libiconv
maybe-check-libiconv:

.PHONY: install-libiconv maybe-install-libiconv
maybe-install-libiconv:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-libiconv info-libiconv
maybe-info-libiconv:

.PHONY: maybe-dvi-libiconv dvi-libiconv
maybe-dvi-libiconv:

.PHONY: maybe-pdf-libiconv pdf-libiconv
maybe-pdf-libiconv:

.PHONY: maybe-html-libiconv html-libiconv
maybe-html-libiconv:

.PHONY: maybe-TAGS-libiconv TAGS-libiconv
maybe-TAGS-libiconv:

.PHONY: maybe-install-info-libiconv install-info-libiconv
maybe-install-info-libiconv:

.PHONY: maybe-install-pdf-libiconv install-pdf-libiconv
maybe-install-pdf-libiconv:

.PHONY: maybe-install-html-libiconv install-html-libiconv
maybe-install-html-libiconv:

.PHONY: maybe-installcheck-libiconv installcheck-libiconv
maybe-installcheck-libiconv:

.PHONY: maybe-mostlyclean-libiconv mostlyclean-libiconv
maybe-mostlyclean-libiconv:

.PHONY: maybe-clean-libiconv clean-libiconv
maybe-clean-libiconv:

.PHONY: maybe-distclean-libiconv distclean-libiconv
maybe-distclean-libiconv:

.PHONY: maybe-maintainer-clean-libiconv maintainer-clean-libiconv
maybe-maintainer-clean-libiconv:



.PHONY: configure-libtool maybe-configure-libtool
maybe-configure-libtool:
configure-libtool: stage_current





.PHONY: all-libtool maybe-all-libtool
maybe-all-libtool:
all-libtool: stage_current




.PHONY: check-libtool maybe-check-libtool
maybe-check-libtool:

.PHONY: install-libtool maybe-install-libtool
maybe-install-libtool:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-libtool info-libtool
maybe-info-libtool:

.PHONY: maybe-dvi-libtool dvi-libtool
maybe-dvi-libtool:

.PHONY: maybe-pdf-libtool pdf-libtool
maybe-pdf-libtool:

.PHONY: maybe-html-libtool html-libtool
maybe-html-libtool:

.PHONY: maybe-TAGS-libtool TAGS-libtool
maybe-TAGS-libtool:

.PHONY: maybe-install-info-libtool install-info-libtool
maybe-install-info-libtool:

.PHONY: maybe-install-pdf-libtool install-pdf-libtool
maybe-install-pdf-libtool:

.PHONY: maybe-install-html-libtool install-html-libtool
maybe-install-html-libtool:

.PHONY: maybe-installcheck-libtool installcheck-libtool
maybe-installcheck-libtool:

.PHONY: maybe-mostlyclean-libtool mostlyclean-libtool
maybe-mostlyclean-libtool:

.PHONY: maybe-clean-libtool clean-libtool
maybe-clean-libtool:

.PHONY: maybe-distclean-libtool distclean-libtool
maybe-distclean-libtool:

.PHONY: maybe-maintainer-clean-libtool maintainer-clean-libtool
maybe-maintainer-clean-libtool:



.PHONY: configure-m4 maybe-configure-m4
maybe-configure-m4:
configure-m4: stage_current





.PHONY: all-m4 maybe-all-m4
maybe-all-m4:
all-m4: stage_current




.PHONY: check-m4 maybe-check-m4
maybe-check-m4:

.PHONY: install-m4 maybe-install-m4
maybe-install-m4:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-m4 info-m4
maybe-info-m4:

.PHONY: maybe-dvi-m4 dvi-m4
maybe-dvi-m4:

.PHONY: maybe-pdf-m4 pdf-m4
maybe-pdf-m4:

.PHONY: maybe-html-m4 html-m4
maybe-html-m4:

.PHONY: maybe-TAGS-m4 TAGS-m4
maybe-TAGS-m4:

.PHONY: maybe-install-info-m4 install-info-m4
maybe-install-info-m4:

.PHONY: maybe-install-pdf-m4 install-pdf-m4
maybe-install-pdf-m4:

.PHONY: maybe-install-html-m4 install-html-m4
maybe-install-html-m4:

.PHONY: maybe-installcheck-m4 installcheck-m4
maybe-installcheck-m4:

.PHONY: maybe-mostlyclean-m4 mostlyclean-m4
maybe-mostlyclean-m4:

.PHONY: maybe-clean-m4 clean-m4
maybe-clean-m4:

.PHONY: maybe-distclean-m4 distclean-m4
maybe-distclean-m4:

.PHONY: maybe-maintainer-clean-m4 maintainer-clean-m4
maybe-maintainer-clean-m4:



.PHONY: configure-make maybe-configure-make
maybe-configure-make:
configure-make: stage_current





.PHONY: all-make maybe-all-make
maybe-all-make:
all-make: stage_current




.PHONY: check-make maybe-check-make
maybe-check-make:

.PHONY: install-make maybe-install-make
maybe-install-make:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-make info-make
maybe-info-make:

.PHONY: maybe-dvi-make dvi-make
maybe-dvi-make:

.PHONY: maybe-pdf-make pdf-make
maybe-pdf-make:

.PHONY: maybe-html-make html-make
maybe-html-make:

.PHONY: maybe-TAGS-make TAGS-make
maybe-TAGS-make:

.PHONY: maybe-install-info-make install-info-make
maybe-install-info-make:

.PHONY: maybe-install-pdf-make install-pdf-make
maybe-install-pdf-make:

.PHONY: maybe-install-html-make install-html-make
maybe-install-html-make:

.PHONY: maybe-installcheck-make installcheck-make
maybe-installcheck-make:

.PHONY: maybe-mostlyclean-make mostlyclean-make
maybe-mostlyclean-make:

.PHONY: maybe-clean-make clean-make
maybe-clean-make:

.PHONY: maybe-distclean-make distclean-make
maybe-distclean-make:

.PHONY: maybe-maintainer-clean-make maintainer-clean-make
maybe-maintainer-clean-make:



.PHONY: configure-mmalloc maybe-configure-mmalloc
maybe-configure-mmalloc:
configure-mmalloc: stage_current





.PHONY: all-mmalloc maybe-all-mmalloc
maybe-all-mmalloc:
all-mmalloc: stage_current




.PHONY: check-mmalloc maybe-check-mmalloc
maybe-check-mmalloc:

.PHONY: install-mmalloc maybe-install-mmalloc
maybe-install-mmalloc:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-mmalloc info-mmalloc
maybe-info-mmalloc:

.PHONY: maybe-dvi-mmalloc dvi-mmalloc
maybe-dvi-mmalloc:

.PHONY: maybe-pdf-mmalloc pdf-mmalloc
maybe-pdf-mmalloc:

.PHONY: maybe-html-mmalloc html-mmalloc
maybe-html-mmalloc:

.PHONY: maybe-TAGS-mmalloc TAGS-mmalloc
maybe-TAGS-mmalloc:

.PHONY: maybe-install-info-mmalloc install-info-mmalloc
maybe-install-info-mmalloc:

.PHONY: maybe-install-pdf-mmalloc install-pdf-mmalloc
maybe-install-pdf-mmalloc:

.PHONY: maybe-install-html-mmalloc install-html-mmalloc
maybe-install-html-mmalloc:

.PHONY: maybe-installcheck-mmalloc installcheck-mmalloc
maybe-installcheck-mmalloc:

.PHONY: maybe-mostlyclean-mmalloc mostlyclean-mmalloc
maybe-mostlyclean-mmalloc:

.PHONY: maybe-clean-mmalloc clean-mmalloc
maybe-clean-mmalloc:

.PHONY: maybe-distclean-mmalloc distclean-mmalloc
maybe-distclean-mmalloc:

.PHONY: maybe-maintainer-clean-mmalloc maintainer-clean-mmalloc
maybe-maintainer-clean-mmalloc:



.PHONY: configure-patch maybe-configure-patch
maybe-configure-patch:
configure-patch: stage_current





.PHONY: all-patch maybe-all-patch
maybe-all-patch:
all-patch: stage_current




.PHONY: check-patch maybe-check-patch
maybe-check-patch:

.PHONY: install-patch maybe-install-patch
maybe-install-patch:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-patch info-patch
maybe-info-patch:

.PHONY: maybe-dvi-patch dvi-patch
maybe-dvi-patch:

.PHONY: maybe-pdf-patch pdf-patch
maybe-pdf-patch:

.PHONY: maybe-html-patch html-patch
maybe-html-patch:

.PHONY: maybe-TAGS-patch TAGS-patch
maybe-TAGS-patch:

.PHONY: maybe-install-info-patch install-info-patch
maybe-install-info-patch:

.PHONY: maybe-install-pdf-patch install-pdf-patch
maybe-install-pdf-patch:

.PHONY: maybe-install-html-patch install-html-patch
maybe-install-html-patch:

.PHONY: maybe-installcheck-patch installcheck-patch
maybe-installcheck-patch:

.PHONY: maybe-mostlyclean-patch mostlyclean-patch
maybe-mostlyclean-patch:

.PHONY: maybe-clean-patch clean-patch
maybe-clean-patch:

.PHONY: maybe-distclean-patch distclean-patch
maybe-distclean-patch:

.PHONY: maybe-maintainer-clean-patch maintainer-clean-patch
maybe-maintainer-clean-patch:



.PHONY: configure-perl maybe-configure-perl
maybe-configure-perl:
configure-perl: stage_current





.PHONY: all-perl maybe-all-perl
maybe-all-perl:
all-perl: stage_current




.PHONY: check-perl maybe-check-perl
maybe-check-perl:

.PHONY: install-perl maybe-install-perl
maybe-install-perl:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-perl info-perl
maybe-info-perl:

.PHONY: maybe-dvi-perl dvi-perl
maybe-dvi-perl:

.PHONY: maybe-pdf-perl pdf-perl
maybe-pdf-perl:

.PHONY: maybe-html-perl html-perl
maybe-html-perl:

.PHONY: maybe-TAGS-perl TAGS-perl
maybe-TAGS-perl:

.PHONY: maybe-install-info-perl install-info-perl
maybe-install-info-perl:

.PHONY: maybe-install-pdf-perl install-pdf-perl
maybe-install-pdf-perl:

.PHONY: maybe-install-html-perl install-html-perl
maybe-install-html-perl:

.PHONY: maybe-installcheck-perl installcheck-perl
maybe-installcheck-perl:

.PHONY: maybe-mostlyclean-perl mostlyclean-perl
maybe-mostlyclean-perl:

.PHONY: maybe-clean-perl clean-perl
maybe-clean-perl:

.PHONY: maybe-distclean-perl distclean-perl
maybe-distclean-perl:

.PHONY: maybe-maintainer-clean-perl maintainer-clean-perl
maybe-maintainer-clean-perl:



.PHONY: configure-prms maybe-configure-prms
maybe-configure-prms:
configure-prms: stage_current





.PHONY: all-prms maybe-all-prms
maybe-all-prms:
all-prms: stage_current




.PHONY: check-prms maybe-check-prms
maybe-check-prms:

.PHONY: install-prms maybe-install-prms
maybe-install-prms:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-prms info-prms
maybe-info-prms:

.PHONY: maybe-dvi-prms dvi-prms
maybe-dvi-prms:

.PHONY: maybe-pdf-prms pdf-prms
maybe-pdf-prms:

.PHONY: maybe-html-prms html-prms
maybe-html-prms:

.PHONY: maybe-TAGS-prms TAGS-prms
maybe-TAGS-prms:

.PHONY: maybe-install-info-prms install-info-prms
maybe-install-info-prms:

.PHONY: maybe-install-pdf-prms install-pdf-prms
maybe-install-pdf-prms:

.PHONY: maybe-install-html-prms install-html-prms
maybe-install-html-prms:

.PHONY: maybe-installcheck-prms installcheck-prms
maybe-installcheck-prms:

.PHONY: maybe-mostlyclean-prms mostlyclean-prms
maybe-mostlyclean-prms:

.PHONY: maybe-clean-prms clean-prms
maybe-clean-prms:

.PHONY: maybe-distclean-prms distclean-prms
maybe-distclean-prms:

.PHONY: maybe-maintainer-clean-prms maintainer-clean-prms
maybe-maintainer-clean-prms:



.PHONY: configure-rcs maybe-configure-rcs
maybe-configure-rcs:
configure-rcs: stage_current





.PHONY: all-rcs maybe-all-rcs
maybe-all-rcs:
all-rcs: stage_current




.PHONY: check-rcs maybe-check-rcs
maybe-check-rcs:

.PHONY: install-rcs maybe-install-rcs
maybe-install-rcs:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-rcs info-rcs
maybe-info-rcs:

.PHONY: maybe-dvi-rcs dvi-rcs
maybe-dvi-rcs:

.PHONY: maybe-pdf-rcs pdf-rcs
maybe-pdf-rcs:

.PHONY: maybe-html-rcs html-rcs
maybe-html-rcs:

.PHONY: maybe-TAGS-rcs TAGS-rcs
maybe-TAGS-rcs:

.PHONY: maybe-install-info-rcs install-info-rcs
maybe-install-info-rcs:

.PHONY: maybe-install-pdf-rcs install-pdf-rcs
maybe-install-pdf-rcs:

.PHONY: maybe-install-html-rcs install-html-rcs
maybe-install-html-rcs:

.PHONY: maybe-installcheck-rcs installcheck-rcs
maybe-installcheck-rcs:

.PHONY: maybe-mostlyclean-rcs mostlyclean-rcs
maybe-mostlyclean-rcs:

.PHONY: maybe-clean-rcs clean-rcs
maybe-clean-rcs:

.PHONY: maybe-distclean-rcs distclean-rcs
maybe-distclean-rcs:

.PHONY: maybe-maintainer-clean-rcs maintainer-clean-rcs
maybe-maintainer-clean-rcs:



.PHONY: configure-readline maybe-configure-readline
maybe-configure-readline:
configure-readline: stage_current





.PHONY: all-readline maybe-all-readline
maybe-all-readline:
all-readline: stage_current




.PHONY: check-readline maybe-check-readline
maybe-check-readline:

.PHONY: install-readline maybe-install-readline
maybe-install-readline:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-readline info-readline
maybe-info-readline:

.PHONY: maybe-dvi-readline dvi-readline
maybe-dvi-readline:

.PHONY: maybe-pdf-readline pdf-readline
maybe-pdf-readline:

.PHONY: maybe-html-readline html-readline
maybe-html-readline:

.PHONY: maybe-TAGS-readline TAGS-readline
maybe-TAGS-readline:

.PHONY: maybe-install-info-readline install-info-readline
maybe-install-info-readline:

.PHONY: maybe-install-pdf-readline install-pdf-readline
maybe-install-pdf-readline:

.PHONY: maybe-install-html-readline install-html-readline
maybe-install-html-readline:

.PHONY: maybe-installcheck-readline installcheck-readline
maybe-installcheck-readline:

.PHONY: maybe-mostlyclean-readline mostlyclean-readline
maybe-mostlyclean-readline:

.PHONY: maybe-clean-readline clean-readline
maybe-clean-readline:

.PHONY: maybe-distclean-readline distclean-readline
maybe-distclean-readline:

.PHONY: maybe-maintainer-clean-readline maintainer-clean-readline
maybe-maintainer-clean-readline:



.PHONY: configure-release maybe-configure-release
maybe-configure-release:
configure-release: stage_current





.PHONY: all-release maybe-all-release
maybe-all-release:
all-release: stage_current




.PHONY: check-release maybe-check-release
maybe-check-release:

.PHONY: install-release maybe-install-release
maybe-install-release:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-release info-release
maybe-info-release:

.PHONY: maybe-dvi-release dvi-release
maybe-dvi-release:

.PHONY: maybe-pdf-release pdf-release
maybe-pdf-release:

.PHONY: maybe-html-release html-release
maybe-html-release:

.PHONY: maybe-TAGS-release TAGS-release
maybe-TAGS-release:

.PHONY: maybe-install-info-release install-info-release
maybe-install-info-release:

.PHONY: maybe-install-pdf-release install-pdf-release
maybe-install-pdf-release:

.PHONY: maybe-install-html-release install-html-release
maybe-install-html-release:

.PHONY: maybe-installcheck-release installcheck-release
maybe-installcheck-release:

.PHONY: maybe-mostlyclean-release mostlyclean-release
maybe-mostlyclean-release:

.PHONY: maybe-clean-release clean-release
maybe-clean-release:

.PHONY: maybe-distclean-release distclean-release
maybe-distclean-release:

.PHONY: maybe-maintainer-clean-release maintainer-clean-release
maybe-maintainer-clean-release:



.PHONY: configure-recode maybe-configure-recode
maybe-configure-recode:
configure-recode: stage_current





.PHONY: all-recode maybe-all-recode
maybe-all-recode:
all-recode: stage_current




.PHONY: check-recode maybe-check-recode
maybe-check-recode:

.PHONY: install-recode maybe-install-recode
maybe-install-recode:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-recode info-recode
maybe-info-recode:

.PHONY: maybe-dvi-recode dvi-recode
maybe-dvi-recode:

.PHONY: maybe-pdf-recode pdf-recode
maybe-pdf-recode:

.PHONY: maybe-html-recode html-recode
maybe-html-recode:

.PHONY: maybe-TAGS-recode TAGS-recode
maybe-TAGS-recode:

.PHONY: maybe-install-info-recode install-info-recode
maybe-install-info-recode:

.PHONY: maybe-install-pdf-recode install-pdf-recode
maybe-install-pdf-recode:

.PHONY: maybe-install-html-recode install-html-recode
maybe-install-html-recode:

.PHONY: maybe-installcheck-recode installcheck-recode
maybe-installcheck-recode:

.PHONY: maybe-mostlyclean-recode mostlyclean-recode
maybe-mostlyclean-recode:

.PHONY: maybe-clean-recode clean-recode
maybe-clean-recode:

.PHONY: maybe-distclean-recode distclean-recode
maybe-distclean-recode:

.PHONY: maybe-maintainer-clean-recode maintainer-clean-recode
maybe-maintainer-clean-recode:



.PHONY: configure-sed maybe-configure-sed
maybe-configure-sed:
configure-sed: stage_current





.PHONY: all-sed maybe-all-sed
maybe-all-sed:
all-sed: stage_current




.PHONY: check-sed maybe-check-sed
maybe-check-sed:

.PHONY: install-sed maybe-install-sed
maybe-install-sed:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-sed info-sed
maybe-info-sed:

.PHONY: maybe-dvi-sed dvi-sed
maybe-dvi-sed:

.PHONY: maybe-pdf-sed pdf-sed
maybe-pdf-sed:

.PHONY: maybe-html-sed html-sed
maybe-html-sed:

.PHONY: maybe-TAGS-sed TAGS-sed
maybe-TAGS-sed:

.PHONY: maybe-install-info-sed install-info-sed
maybe-install-info-sed:

.PHONY: maybe-install-pdf-sed install-pdf-sed
maybe-install-pdf-sed:

.PHONY: maybe-install-html-sed install-html-sed
maybe-install-html-sed:

.PHONY: maybe-installcheck-sed installcheck-sed
maybe-installcheck-sed:

.PHONY: maybe-mostlyclean-sed mostlyclean-sed
maybe-mostlyclean-sed:

.PHONY: maybe-clean-sed clean-sed
maybe-clean-sed:

.PHONY: maybe-distclean-sed distclean-sed
maybe-distclean-sed:

.PHONY: maybe-maintainer-clean-sed maintainer-clean-sed
maybe-maintainer-clean-sed:



.PHONY: configure-send-pr maybe-configure-send-pr
maybe-configure-send-pr:
configure-send-pr: stage_current





.PHONY: all-send-pr maybe-all-send-pr
maybe-all-send-pr:
all-send-pr: stage_current




.PHONY: check-send-pr maybe-check-send-pr
maybe-check-send-pr:

.PHONY: install-send-pr maybe-install-send-pr
maybe-install-send-pr:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-send-pr info-send-pr
maybe-info-send-pr:

.PHONY: maybe-dvi-send-pr dvi-send-pr
maybe-dvi-send-pr:

.PHONY: maybe-pdf-send-pr pdf-send-pr
maybe-pdf-send-pr:

.PHONY: maybe-html-send-pr html-send-pr
maybe-html-send-pr:

.PHONY: maybe-TAGS-send-pr TAGS-send-pr
maybe-TAGS-send-pr:

.PHONY: maybe-install-info-send-pr install-info-send-pr
maybe-install-info-send-pr:

.PHONY: maybe-install-pdf-send-pr install-pdf-send-pr
maybe-install-pdf-send-pr:

.PHONY: maybe-install-html-send-pr install-html-send-pr
maybe-install-html-send-pr:

.PHONY: maybe-installcheck-send-pr installcheck-send-pr
maybe-installcheck-send-pr:

.PHONY: maybe-mostlyclean-send-pr mostlyclean-send-pr
maybe-mostlyclean-send-pr:

.PHONY: maybe-clean-send-pr clean-send-pr
maybe-clean-send-pr:

.PHONY: maybe-distclean-send-pr distclean-send-pr
maybe-distclean-send-pr:

.PHONY: maybe-maintainer-clean-send-pr maintainer-clean-send-pr
maybe-maintainer-clean-send-pr:



.PHONY: configure-shellutils maybe-configure-shellutils
maybe-configure-shellutils:
configure-shellutils: stage_current





.PHONY: all-shellutils maybe-all-shellutils
maybe-all-shellutils:
all-shellutils: stage_current




.PHONY: check-shellutils maybe-check-shellutils
maybe-check-shellutils:

.PHONY: install-shellutils maybe-install-shellutils
maybe-install-shellutils:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-shellutils info-shellutils
maybe-info-shellutils:

.PHONY: maybe-dvi-shellutils dvi-shellutils
maybe-dvi-shellutils:

.PHONY: maybe-pdf-shellutils pdf-shellutils
maybe-pdf-shellutils:

.PHONY: maybe-html-shellutils html-shellutils
maybe-html-shellutils:

.PHONY: maybe-TAGS-shellutils TAGS-shellutils
maybe-TAGS-shellutils:

.PHONY: maybe-install-info-shellutils install-info-shellutils
maybe-install-info-shellutils:

.PHONY: maybe-install-pdf-shellutils install-pdf-shellutils
maybe-install-pdf-shellutils:

.PHONY: maybe-install-html-shellutils install-html-shellutils
maybe-install-html-shellutils:

.PHONY: maybe-installcheck-shellutils installcheck-shellutils
maybe-installcheck-shellutils:

.PHONY: maybe-mostlyclean-shellutils mostlyclean-shellutils
maybe-mostlyclean-shellutils:

.PHONY: maybe-clean-shellutils clean-shellutils
maybe-clean-shellutils:

.PHONY: maybe-distclean-shellutils distclean-shellutils
maybe-distclean-shellutils:

.PHONY: maybe-maintainer-clean-shellutils maintainer-clean-shellutils
maybe-maintainer-clean-shellutils:



.PHONY: configure-sid maybe-configure-sid
maybe-configure-sid:
configure-sid: stage_current





.PHONY: all-sid maybe-all-sid
maybe-all-sid:
all-sid: stage_current




.PHONY: check-sid maybe-check-sid
maybe-check-sid:

.PHONY: install-sid maybe-install-sid
maybe-install-sid:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-sid info-sid
maybe-info-sid:

.PHONY: maybe-dvi-sid dvi-sid
maybe-dvi-sid:

.PHONY: maybe-pdf-sid pdf-sid
maybe-pdf-sid:

.PHONY: maybe-html-sid html-sid
maybe-html-sid:

.PHONY: maybe-TAGS-sid TAGS-sid
maybe-TAGS-sid:

.PHONY: maybe-install-info-sid install-info-sid
maybe-install-info-sid:

.PHONY: maybe-install-pdf-sid install-pdf-sid
maybe-install-pdf-sid:

.PHONY: maybe-install-html-sid install-html-sid
maybe-install-html-sid:

.PHONY: maybe-installcheck-sid installcheck-sid
maybe-installcheck-sid:

.PHONY: maybe-mostlyclean-sid mostlyclean-sid
maybe-mostlyclean-sid:

.PHONY: maybe-clean-sid clean-sid
maybe-clean-sid:

.PHONY: maybe-distclean-sid distclean-sid
maybe-distclean-sid:

.PHONY: maybe-maintainer-clean-sid maintainer-clean-sid
maybe-maintainer-clean-sid:



.PHONY: configure-sim maybe-configure-sim
maybe-configure-sim:
configure-sim: stage_current





.PHONY: all-sim maybe-all-sim
maybe-all-sim:
all-sim: stage_current




.PHONY: check-sim maybe-check-sim
maybe-check-sim:

.PHONY: install-sim maybe-install-sim
maybe-install-sim:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-sim info-sim
maybe-info-sim:

.PHONY: maybe-dvi-sim dvi-sim
maybe-dvi-sim:

.PHONY: maybe-pdf-sim pdf-sim
maybe-pdf-sim:

.PHONY: maybe-html-sim html-sim
maybe-html-sim:

.PHONY: maybe-TAGS-sim TAGS-sim
maybe-TAGS-sim:

.PHONY: maybe-install-info-sim install-info-sim
maybe-install-info-sim:

.PHONY: maybe-install-pdf-sim install-pdf-sim
maybe-install-pdf-sim:

.PHONY: maybe-install-html-sim install-html-sim
maybe-install-html-sim:

.PHONY: maybe-installcheck-sim installcheck-sim
maybe-installcheck-sim:

.PHONY: maybe-mostlyclean-sim mostlyclean-sim
maybe-mostlyclean-sim:

.PHONY: maybe-clean-sim clean-sim
maybe-clean-sim:

.PHONY: maybe-distclean-sim distclean-sim
maybe-distclean-sim:

.PHONY: maybe-maintainer-clean-sim maintainer-clean-sim
maybe-maintainer-clean-sim:



.PHONY: configure-tar maybe-configure-tar
maybe-configure-tar:
configure-tar: stage_current





.PHONY: all-tar maybe-all-tar
maybe-all-tar:
all-tar: stage_current




.PHONY: check-tar maybe-check-tar
maybe-check-tar:

.PHONY: install-tar maybe-install-tar
maybe-install-tar:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-tar info-tar
maybe-info-tar:

.PHONY: maybe-dvi-tar dvi-tar
maybe-dvi-tar:

.PHONY: maybe-pdf-tar pdf-tar
maybe-pdf-tar:

.PHONY: maybe-html-tar html-tar
maybe-html-tar:

.PHONY: maybe-TAGS-tar TAGS-tar
maybe-TAGS-tar:

.PHONY: maybe-install-info-tar install-info-tar
maybe-install-info-tar:

.PHONY: maybe-install-pdf-tar install-pdf-tar
maybe-install-pdf-tar:

.PHONY: maybe-install-html-tar install-html-tar
maybe-install-html-tar:

.PHONY: maybe-installcheck-tar installcheck-tar
maybe-installcheck-tar:

.PHONY: maybe-mostlyclean-tar mostlyclean-tar
maybe-mostlyclean-tar:

.PHONY: maybe-clean-tar clean-tar
maybe-clean-tar:

.PHONY: maybe-distclean-tar distclean-tar
maybe-distclean-tar:

.PHONY: maybe-maintainer-clean-tar maintainer-clean-tar
maybe-maintainer-clean-tar:



.PHONY: configure-texinfo maybe-configure-texinfo
maybe-configure-texinfo:
configure-texinfo: stage_current





.PHONY: all-texinfo maybe-all-texinfo
maybe-all-texinfo:
all-texinfo: stage_current




.PHONY: check-texinfo maybe-check-texinfo
maybe-check-texinfo:

.PHONY: install-texinfo maybe-install-texinfo
maybe-install-texinfo:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-texinfo info-texinfo
maybe-info-texinfo:

.PHONY: maybe-dvi-texinfo dvi-texinfo
maybe-dvi-texinfo:

.PHONY: maybe-pdf-texinfo pdf-texinfo
maybe-pdf-texinfo:

.PHONY: maybe-html-texinfo html-texinfo
maybe-html-texinfo:

.PHONY: maybe-TAGS-texinfo TAGS-texinfo
maybe-TAGS-texinfo:

.PHONY: maybe-install-info-texinfo install-info-texinfo
maybe-install-info-texinfo:

.PHONY: maybe-install-pdf-texinfo install-pdf-texinfo
maybe-install-pdf-texinfo:

.PHONY: maybe-install-html-texinfo install-html-texinfo
maybe-install-html-texinfo:

.PHONY: maybe-installcheck-texinfo installcheck-texinfo
maybe-installcheck-texinfo:

.PHONY: maybe-mostlyclean-texinfo mostlyclean-texinfo
maybe-mostlyclean-texinfo:

.PHONY: maybe-clean-texinfo clean-texinfo
maybe-clean-texinfo:

.PHONY: maybe-distclean-texinfo distclean-texinfo
maybe-distclean-texinfo:

.PHONY: maybe-maintainer-clean-texinfo maintainer-clean-texinfo
maybe-maintainer-clean-texinfo:



.PHONY: configure-textutils maybe-configure-textutils
maybe-configure-textutils:
configure-textutils: stage_current





.PHONY: all-textutils maybe-all-textutils
maybe-all-textutils:
all-textutils: stage_current




.PHONY: check-textutils maybe-check-textutils
maybe-check-textutils:

.PHONY: install-textutils maybe-install-textutils
maybe-install-textutils:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-textutils info-textutils
maybe-info-textutils:

.PHONY: maybe-dvi-textutils dvi-textutils
maybe-dvi-textutils:

.PHONY: maybe-pdf-textutils pdf-textutils
maybe-pdf-textutils:

.PHONY: maybe-html-textutils html-textutils
maybe-html-textutils:

.PHONY: maybe-TAGS-textutils TAGS-textutils
maybe-TAGS-textutils:

.PHONY: maybe-install-info-textutils install-info-textutils
maybe-install-info-textutils:

.PHONY: maybe-install-pdf-textutils install-pdf-textutils
maybe-install-pdf-textutils:

.PHONY: maybe-install-html-textutils install-html-textutils
maybe-install-html-textutils:

.PHONY: maybe-installcheck-textutils installcheck-textutils
maybe-installcheck-textutils:

.PHONY: maybe-mostlyclean-textutils mostlyclean-textutils
maybe-mostlyclean-textutils:

.PHONY: maybe-clean-textutils clean-textutils
maybe-clean-textutils:

.PHONY: maybe-distclean-textutils distclean-textutils
maybe-distclean-textutils:

.PHONY: maybe-maintainer-clean-textutils maintainer-clean-textutils
maybe-maintainer-clean-textutils:



.PHONY: configure-time maybe-configure-time
maybe-configure-time:
configure-time: stage_current





.PHONY: all-time maybe-all-time
maybe-all-time:
all-time: stage_current




.PHONY: check-time maybe-check-time
maybe-check-time:

.PHONY: install-time maybe-install-time
maybe-install-time:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-time info-time
maybe-info-time:

.PHONY: maybe-dvi-time dvi-time
maybe-dvi-time:

.PHONY: maybe-pdf-time pdf-time
maybe-pdf-time:

.PHONY: maybe-html-time html-time
maybe-html-time:

.PHONY: maybe-TAGS-time TAGS-time
maybe-TAGS-time:

.PHONY: maybe-install-info-time install-info-time
maybe-install-info-time:

.PHONY: maybe-install-pdf-time install-pdf-time
maybe-install-pdf-time:

.PHONY: maybe-install-html-time install-html-time
maybe-install-html-time:

.PHONY: maybe-installcheck-time installcheck-time
maybe-installcheck-time:

.PHONY: maybe-mostlyclean-time mostlyclean-time
maybe-mostlyclean-time:

.PHONY: maybe-clean-time clean-time
maybe-clean-time:

.PHONY: maybe-distclean-time distclean-time
maybe-distclean-time:

.PHONY: maybe-maintainer-clean-time maintainer-clean-time
maybe-maintainer-clean-time:



.PHONY: configure-uudecode maybe-configure-uudecode
maybe-configure-uudecode:
configure-uudecode: stage_current





.PHONY: all-uudecode maybe-all-uudecode
maybe-all-uudecode:
all-uudecode: stage_current




.PHONY: check-uudecode maybe-check-uudecode
maybe-check-uudecode:

.PHONY: install-uudecode maybe-install-uudecode
maybe-install-uudecode:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-uudecode info-uudecode
maybe-info-uudecode:

.PHONY: maybe-dvi-uudecode dvi-uudecode
maybe-dvi-uudecode:

.PHONY: maybe-pdf-uudecode pdf-uudecode
maybe-pdf-uudecode:

.PHONY: maybe-html-uudecode html-uudecode
maybe-html-uudecode:

.PHONY: maybe-TAGS-uudecode TAGS-uudecode
maybe-TAGS-uudecode:

.PHONY: maybe-install-info-uudecode install-info-uudecode
maybe-install-info-uudecode:

.PHONY: maybe-install-pdf-uudecode install-pdf-uudecode
maybe-install-pdf-uudecode:

.PHONY: maybe-install-html-uudecode install-html-uudecode
maybe-install-html-uudecode:

.PHONY: maybe-installcheck-uudecode installcheck-uudecode
maybe-installcheck-uudecode:

.PHONY: maybe-mostlyclean-uudecode mostlyclean-uudecode
maybe-mostlyclean-uudecode:

.PHONY: maybe-clean-uudecode clean-uudecode
maybe-clean-uudecode:

.PHONY: maybe-distclean-uudecode distclean-uudecode
maybe-distclean-uudecode:

.PHONY: maybe-maintainer-clean-uudecode maintainer-clean-uudecode
maybe-maintainer-clean-uudecode:



.PHONY: configure-wdiff maybe-configure-wdiff
maybe-configure-wdiff:
configure-wdiff: stage_current





.PHONY: all-wdiff maybe-all-wdiff
maybe-all-wdiff:
all-wdiff: stage_current




.PHONY: check-wdiff maybe-check-wdiff
maybe-check-wdiff:

.PHONY: install-wdiff maybe-install-wdiff
maybe-install-wdiff:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-wdiff info-wdiff
maybe-info-wdiff:

.PHONY: maybe-dvi-wdiff dvi-wdiff
maybe-dvi-wdiff:

.PHONY: maybe-pdf-wdiff pdf-wdiff
maybe-pdf-wdiff:

.PHONY: maybe-html-wdiff html-wdiff
maybe-html-wdiff:

.PHONY: maybe-TAGS-wdiff TAGS-wdiff
maybe-TAGS-wdiff:

.PHONY: maybe-install-info-wdiff install-info-wdiff
maybe-install-info-wdiff:

.PHONY: maybe-install-pdf-wdiff install-pdf-wdiff
maybe-install-pdf-wdiff:

.PHONY: maybe-install-html-wdiff install-html-wdiff
maybe-install-html-wdiff:

.PHONY: maybe-installcheck-wdiff installcheck-wdiff
maybe-installcheck-wdiff:

.PHONY: maybe-mostlyclean-wdiff mostlyclean-wdiff
maybe-mostlyclean-wdiff:

.PHONY: maybe-clean-wdiff clean-wdiff
maybe-clean-wdiff:

.PHONY: maybe-distclean-wdiff distclean-wdiff
maybe-distclean-wdiff:

.PHONY: maybe-maintainer-clean-wdiff maintainer-clean-wdiff
maybe-maintainer-clean-wdiff:



.PHONY: configure-zip maybe-configure-zip
maybe-configure-zip:
configure-zip: stage_current





.PHONY: all-zip maybe-all-zip
maybe-all-zip:
all-zip: stage_current




.PHONY: check-zip maybe-check-zip
maybe-check-zip:

.PHONY: install-zip maybe-install-zip
maybe-install-zip:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-zip info-zip
maybe-info-zip:

.PHONY: maybe-dvi-zip dvi-zip
maybe-dvi-zip:

.PHONY: maybe-pdf-zip pdf-zip
maybe-pdf-zip:

.PHONY: maybe-html-zip html-zip
maybe-html-zip:

.PHONY: maybe-TAGS-zip TAGS-zip
maybe-TAGS-zip:

.PHONY: maybe-install-info-zip install-info-zip
maybe-install-info-zip:

.PHONY: maybe-install-pdf-zip install-pdf-zip
maybe-install-pdf-zip:

.PHONY: maybe-install-html-zip install-html-zip
maybe-install-html-zip:

.PHONY: maybe-installcheck-zip installcheck-zip
maybe-installcheck-zip:

.PHONY: maybe-mostlyclean-zip mostlyclean-zip
maybe-mostlyclean-zip:

.PHONY: maybe-clean-zip clean-zip
maybe-clean-zip:

.PHONY: maybe-distclean-zip distclean-zip
maybe-distclean-zip:

.PHONY: maybe-maintainer-clean-zip maintainer-clean-zip
maybe-maintainer-clean-zip:



.PHONY: configure-zlib maybe-configure-zlib
maybe-configure-zlib:
configure-zlib: stage_current



.PHONY: configure-stage1-zlib maybe-configure-stage1-zlib
maybe-configure-stage1-zlib:

.PHONY: configure-stage2-zlib maybe-configure-stage2-zlib
maybe-configure-stage2-zlib:

.PHONY: configure-stageb2g0-zlib maybe-configure-stageb2g0-zlib
maybe-configure-stageb2g0-zlib:

.PHONY: configure-stage3-zlib maybe-configure-stage3-zlib
maybe-configure-stage3-zlib:

.PHONY: configure-stageb3g2-zlib maybe-configure-stageb3g2-zlib
maybe-configure-stageb3g2-zlib:

.PHONY: configure-stage4-zlib maybe-configure-stage4-zlib
maybe-configure-stage4-zlib:

.PHONY: configure-stageprofile-zlib maybe-configure-stageprofile-zlib
maybe-configure-stageprofile-zlib:

.PHONY: configure-stagefeedback-zlib maybe-configure-stagefeedback-zlib
maybe-configure-stagefeedback-zlib:





.PHONY: all-zlib maybe-all-zlib
maybe-all-zlib:
all-zlib: stage_current



.PHONY: all-stage1-zlib maybe-all-stage1-zlib
.PHONY: clean-stage1-zlib maybe-clean-stage1-zlib
maybe-all-stage1-zlib:
maybe-clean-stage1-zlib:


.PHONY: all-stage2-zlib maybe-all-stage2-zlib
.PHONY: clean-stage2-zlib maybe-clean-stage2-zlib
maybe-all-stage2-zlib:
maybe-clean-stage2-zlib:


.PHONY: all-stageb2g0-zlib maybe-all-stageb2g0-zlib
.PHONY: clean-stageb2g0-zlib maybe-clean-stageb2g0-zlib
maybe-all-stageb2g0-zlib:
maybe-clean-stageb2g0-zlib:


.PHONY: all-stage3-zlib maybe-all-stage3-zlib
.PHONY: clean-stage3-zlib maybe-clean-stage3-zlib
maybe-all-stage3-zlib:
maybe-clean-stage3-zlib:


.PHONY: all-stageb3g2-zlib maybe-all-stageb3g2-zlib
.PHONY: clean-stageb3g2-zlib maybe-clean-stageb3g2-zlib
maybe-all-stageb3g2-zlib:
maybe-clean-stageb3g2-zlib:


.PHONY: all-stage4-zlib maybe-all-stage4-zlib
.PHONY: clean-stage4-zlib maybe-clean-stage4-zlib
maybe-all-stage4-zlib:
maybe-clean-stage4-zlib:


.PHONY: all-stageprofile-zlib maybe-all-stageprofile-zlib
.PHONY: clean-stageprofile-zlib maybe-clean-stageprofile-zlib
maybe-all-stageprofile-zlib:
maybe-clean-stageprofile-zlib:


.PHONY: all-stagefeedback-zlib maybe-all-stagefeedback-zlib
.PHONY: clean-stagefeedback-zlib maybe-clean-stagefeedback-zlib
maybe-all-stagefeedback-zlib:
maybe-clean-stagefeedback-zlib:





.PHONY: check-zlib maybe-check-zlib
maybe-check-zlib:

.PHONY: install-zlib maybe-install-zlib
maybe-install-zlib:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-zlib info-zlib
maybe-info-zlib:

.PHONY: maybe-dvi-zlib dvi-zlib
maybe-dvi-zlib:

.PHONY: maybe-pdf-zlib pdf-zlib
maybe-pdf-zlib:

.PHONY: maybe-html-zlib html-zlib
maybe-html-zlib:

.PHONY: maybe-TAGS-zlib TAGS-zlib
maybe-TAGS-zlib:

.PHONY: maybe-install-info-zlib install-info-zlib
maybe-install-info-zlib:

.PHONY: maybe-install-pdf-zlib install-pdf-zlib
maybe-install-pdf-zlib:

.PHONY: maybe-install-html-zlib install-html-zlib
maybe-install-html-zlib:

.PHONY: maybe-installcheck-zlib installcheck-zlib
maybe-installcheck-zlib:

.PHONY: maybe-mostlyclean-zlib mostlyclean-zlib
maybe-mostlyclean-zlib:

.PHONY: maybe-clean-zlib clean-zlib
maybe-clean-zlib:

.PHONY: maybe-distclean-zlib distclean-zlib
maybe-distclean-zlib:

.PHONY: maybe-maintainer-clean-zlib maintainer-clean-zlib
maybe-maintainer-clean-zlib:



.PHONY: configure-gdb maybe-configure-gdb
maybe-configure-gdb:
configure-gdb: stage_current





.PHONY: all-gdb maybe-all-gdb
maybe-all-gdb:
all-gdb: stage_current




.PHONY: check-gdb maybe-check-gdb
maybe-check-gdb:

.PHONY: install-gdb maybe-install-gdb
maybe-install-gdb:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gdb info-gdb
maybe-info-gdb:

.PHONY: maybe-dvi-gdb dvi-gdb
maybe-dvi-gdb:

.PHONY: maybe-pdf-gdb pdf-gdb
maybe-pdf-gdb:

.PHONY: maybe-html-gdb html-gdb
maybe-html-gdb:

.PHONY: maybe-TAGS-gdb TAGS-gdb
maybe-TAGS-gdb:

.PHONY: maybe-install-info-gdb install-info-gdb
maybe-install-info-gdb:

.PHONY: maybe-install-pdf-gdb install-pdf-gdb
maybe-install-pdf-gdb:

.PHONY: maybe-install-html-gdb install-html-gdb
maybe-install-html-gdb:

.PHONY: maybe-installcheck-gdb installcheck-gdb
maybe-installcheck-gdb:

.PHONY: maybe-mostlyclean-gdb mostlyclean-gdb
maybe-mostlyclean-gdb:

.PHONY: maybe-clean-gdb clean-gdb
maybe-clean-gdb:

.PHONY: maybe-distclean-gdb distclean-gdb
maybe-distclean-gdb:

.PHONY: maybe-maintainer-clean-gdb maintainer-clean-gdb
maybe-maintainer-clean-gdb:



.PHONY: configure-expect maybe-configure-expect
maybe-configure-expect:
configure-expect: stage_current





.PHONY: all-expect maybe-all-expect
maybe-all-expect:
all-expect: stage_current




.PHONY: check-expect maybe-check-expect
maybe-check-expect:

.PHONY: install-expect maybe-install-expect
maybe-install-expect:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-expect info-expect
maybe-info-expect:

.PHONY: maybe-dvi-expect dvi-expect
maybe-dvi-expect:

.PHONY: maybe-pdf-expect pdf-expect
maybe-pdf-expect:

.PHONY: maybe-html-expect html-expect
maybe-html-expect:

.PHONY: maybe-TAGS-expect TAGS-expect
maybe-TAGS-expect:

.PHONY: maybe-install-info-expect install-info-expect
maybe-install-info-expect:

.PHONY: maybe-install-pdf-expect install-pdf-expect
maybe-install-pdf-expect:

.PHONY: maybe-install-html-expect install-html-expect
maybe-install-html-expect:

.PHONY: maybe-installcheck-expect installcheck-expect
maybe-installcheck-expect:

.PHONY: maybe-mostlyclean-expect mostlyclean-expect
maybe-mostlyclean-expect:

.PHONY: maybe-clean-expect clean-expect
maybe-clean-expect:

.PHONY: maybe-distclean-expect distclean-expect
maybe-distclean-expect:

.PHONY: maybe-maintainer-clean-expect maintainer-clean-expect
maybe-maintainer-clean-expect:



.PHONY: configure-guile maybe-configure-guile
maybe-configure-guile:
configure-guile: stage_current





.PHONY: all-guile maybe-all-guile
maybe-all-guile:
all-guile: stage_current




.PHONY: check-guile maybe-check-guile
maybe-check-guile:

.PHONY: install-guile maybe-install-guile
maybe-install-guile:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-guile info-guile
maybe-info-guile:

.PHONY: maybe-dvi-guile dvi-guile
maybe-dvi-guile:

.PHONY: maybe-pdf-guile pdf-guile
maybe-pdf-guile:

.PHONY: maybe-html-guile html-guile
maybe-html-guile:

.PHONY: maybe-TAGS-guile TAGS-guile
maybe-TAGS-guile:

.PHONY: maybe-install-info-guile install-info-guile
maybe-install-info-guile:

.PHONY: maybe-install-pdf-guile install-pdf-guile
maybe-install-pdf-guile:

.PHONY: maybe-install-html-guile install-html-guile
maybe-install-html-guile:

.PHONY: maybe-installcheck-guile installcheck-guile
maybe-installcheck-guile:

.PHONY: maybe-mostlyclean-guile mostlyclean-guile
maybe-mostlyclean-guile:

.PHONY: maybe-clean-guile clean-guile
maybe-clean-guile:

.PHONY: maybe-distclean-guile distclean-guile
maybe-distclean-guile:

.PHONY: maybe-maintainer-clean-guile maintainer-clean-guile
maybe-maintainer-clean-guile:



.PHONY: configure-tk maybe-configure-tk
maybe-configure-tk:
configure-tk: stage_current





.PHONY: all-tk maybe-all-tk
maybe-all-tk:
all-tk: stage_current




.PHONY: check-tk maybe-check-tk
maybe-check-tk:

.PHONY: install-tk maybe-install-tk
maybe-install-tk:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-tk info-tk
maybe-info-tk:

.PHONY: maybe-dvi-tk dvi-tk
maybe-dvi-tk:

.PHONY: maybe-pdf-tk pdf-tk
maybe-pdf-tk:

.PHONY: maybe-html-tk html-tk
maybe-html-tk:

.PHONY: maybe-TAGS-tk TAGS-tk
maybe-TAGS-tk:

.PHONY: maybe-install-info-tk install-info-tk
maybe-install-info-tk:

.PHONY: maybe-install-pdf-tk install-pdf-tk
maybe-install-pdf-tk:

.PHONY: maybe-install-html-tk install-html-tk
maybe-install-html-tk:

.PHONY: maybe-installcheck-tk installcheck-tk
maybe-installcheck-tk:

.PHONY: maybe-mostlyclean-tk mostlyclean-tk
maybe-mostlyclean-tk:

.PHONY: maybe-clean-tk clean-tk
maybe-clean-tk:

.PHONY: maybe-distclean-tk distclean-tk
maybe-distclean-tk:

.PHONY: maybe-maintainer-clean-tk maintainer-clean-tk
maybe-maintainer-clean-tk:



.PHONY: configure-libtermcap maybe-configure-libtermcap
maybe-configure-libtermcap:
configure-libtermcap: stage_current





.PHONY: all-libtermcap maybe-all-libtermcap
maybe-all-libtermcap:
all-libtermcap: stage_current




.PHONY: check-libtermcap maybe-check-libtermcap
maybe-check-libtermcap:

.PHONY: install-libtermcap maybe-install-libtermcap
maybe-install-libtermcap:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-libtermcap info-libtermcap
maybe-info-libtermcap:

.PHONY: maybe-dvi-libtermcap dvi-libtermcap
maybe-dvi-libtermcap:

.PHONY: maybe-pdf-libtermcap pdf-libtermcap
maybe-pdf-libtermcap:

.PHONY: maybe-html-libtermcap html-libtermcap
maybe-html-libtermcap:

.PHONY: maybe-TAGS-libtermcap TAGS-libtermcap
maybe-TAGS-libtermcap:

.PHONY: maybe-install-info-libtermcap install-info-libtermcap
maybe-install-info-libtermcap:

.PHONY: maybe-install-pdf-libtermcap install-pdf-libtermcap
maybe-install-pdf-libtermcap:

.PHONY: maybe-install-html-libtermcap install-html-libtermcap
maybe-install-html-libtermcap:

.PHONY: maybe-installcheck-libtermcap installcheck-libtermcap
maybe-installcheck-libtermcap:

.PHONY: maybe-mostlyclean-libtermcap mostlyclean-libtermcap
maybe-mostlyclean-libtermcap:

.PHONY: maybe-clean-libtermcap clean-libtermcap
maybe-clean-libtermcap:

.PHONY: maybe-distclean-libtermcap distclean-libtermcap
maybe-distclean-libtermcap:

.PHONY: maybe-maintainer-clean-libtermcap maintainer-clean-libtermcap
maybe-maintainer-clean-libtermcap:



.PHONY: configure-utils maybe-configure-utils
maybe-configure-utils:
configure-utils: stage_current





.PHONY: all-utils maybe-all-utils
maybe-all-utils:
all-utils: stage_current




.PHONY: check-utils maybe-check-utils
maybe-check-utils:

.PHONY: install-utils maybe-install-utils
maybe-install-utils:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-utils info-utils
maybe-info-utils:

.PHONY: maybe-dvi-utils dvi-utils
maybe-dvi-utils:

.PHONY: maybe-pdf-utils pdf-utils
maybe-pdf-utils:

.PHONY: maybe-html-utils html-utils
maybe-html-utils:

.PHONY: maybe-TAGS-utils TAGS-utils
maybe-TAGS-utils:

.PHONY: maybe-install-info-utils install-info-utils
maybe-install-info-utils:

.PHONY: maybe-install-pdf-utils install-pdf-utils
maybe-install-pdf-utils:

.PHONY: maybe-install-html-utils install-html-utils
maybe-install-html-utils:

.PHONY: maybe-installcheck-utils installcheck-utils
maybe-installcheck-utils:

.PHONY: maybe-mostlyclean-utils mostlyclean-utils
maybe-mostlyclean-utils:

.PHONY: maybe-clean-utils clean-utils
maybe-clean-utils:

.PHONY: maybe-distclean-utils distclean-utils
maybe-distclean-utils:

.PHONY: maybe-maintainer-clean-utils maintainer-clean-utils
maybe-maintainer-clean-utils:



.PHONY: configure-gnattools maybe-configure-gnattools
maybe-configure-gnattools:
configure-gnattools: stage_current





.PHONY: all-gnattools maybe-all-gnattools
maybe-all-gnattools:
all-gnattools: stage_current




.PHONY: check-gnattools maybe-check-gnattools
maybe-check-gnattools:

.PHONY: install-gnattools maybe-install-gnattools
maybe-install-gnattools:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-gnattools info-gnattools
maybe-info-gnattools:

.PHONY: maybe-dvi-gnattools dvi-gnattools
maybe-dvi-gnattools:

.PHONY: maybe-pdf-gnattools pdf-gnattools
maybe-pdf-gnattools:

.PHONY: maybe-html-gnattools html-gnattools
maybe-html-gnattools:

.PHONY: maybe-TAGS-gnattools TAGS-gnattools
maybe-TAGS-gnattools:

.PHONY: maybe-install-info-gnattools install-info-gnattools
maybe-install-info-gnattools:

.PHONY: maybe-install-pdf-gnattools install-pdf-gnattools
maybe-install-pdf-gnattools:

.PHONY: maybe-install-html-gnattools install-html-gnattools
maybe-install-html-gnattools:

.PHONY: maybe-installcheck-gnattools installcheck-gnattools
maybe-installcheck-gnattools:

.PHONY: maybe-mostlyclean-gnattools mostlyclean-gnattools
maybe-mostlyclean-gnattools:

.PHONY: maybe-clean-gnattools clean-gnattools
maybe-clean-gnattools:

.PHONY: maybe-distclean-gnattools distclean-gnattools
maybe-distclean-gnattools:

.PHONY: maybe-maintainer-clean-gnattools maintainer-clean-gnattools
maybe-maintainer-clean-gnattools:



# ---------------------------------------
# Modules which run on the target machine
# ---------------------------------------




.PHONY: configure-target-libstdc++-v3 maybe-configure-target-libstdc++-v3
maybe-configure-target-libstdc++-v3:
configure-target-libstdc++-v3: stage_current
maybe-configure-target-libstdc++-v3: configure-target-libstdc++-v3
configure-target-libstdc++-v3: 
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libstdc++-v3..."; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libstdc++-v3 ; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libstdc++-v3/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libstdc++-v3/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libstdc++-v3/multilib.tmp $(TARGET_SUBDIR)/libstdc++-v3/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libstdc++-v3/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile; \
	    mv $(TARGET_SUBDIR)/libstdc++-v3/multilib.tmp $(TARGET_SUBDIR)/libstdc++-v3/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libstdc++-v3/multilib.tmp $(TARGET_SUBDIR)/libstdc++-v3/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libstdc++-v3 ; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo Configuring in $(TARGET_SUBDIR)/libstdc++-v3; \
	cd "$(TARGET_SUBDIR)/libstdc++-v3" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libstdc++-v3/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libstdc++-v3"; \
	libsrcdir="$$s/libstdc++-v3"; \
	rm -f no-such-file || : ; \
	CONFIG_SITE=no-such-file $(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1





.PHONY: all-target-libstdc++-v3 maybe-all-target-libstdc++-v3
maybe-all-target-libstdc++-v3:
all-target-libstdc++-v3: stage_current
TARGET-target-libstdc++-v3=all
maybe-all-target-libstdc++-v3: all-target-libstdc++-v3
all-target-libstdc++-v3: configure-target-libstdc++-v3
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_TARGET_FLAGS) 'CXX=$$(RAW_CXX_FOR_TARGET)' 'CXX_FOR_TARGET=$$(RAW_CXX_FOR_TARGET)'  \
		$(TARGET-target-libstdc++-v3))





.PHONY: check-target-libstdc++-v3 maybe-check-target-libstdc++-v3
maybe-check-target-libstdc++-v3:
maybe-check-target-libstdc++-v3: check-target-libstdc++-v3

check-target-libstdc++-v3:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)  'CXX=$$(RAW_CXX_FOR_TARGET)' 'CXX_FOR_TARGET=$$(RAW_CXX_FOR_TARGET)'   check)


.PHONY: install-target-libstdc++-v3 maybe-install-target-libstdc++-v3
maybe-install-target-libstdc++-v3:
maybe-install-target-libstdc++-v3: install-target-libstdc++-v3

install-target-libstdc++-v3: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libstdc++-v3 info-target-libstdc++-v3
maybe-info-target-libstdc++-v3:
maybe-info-target-libstdc++-v3: info-target-libstdc++-v3

info-target-libstdc++-v3: \
    configure-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing info in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           info) \
	  || exit 1


.PHONY: maybe-dvi-target-libstdc++-v3 dvi-target-libstdc++-v3
maybe-dvi-target-libstdc++-v3:
maybe-dvi-target-libstdc++-v3: dvi-target-libstdc++-v3

dvi-target-libstdc++-v3: \
    configure-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing dvi in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           dvi) \
	  || exit 1


.PHONY: maybe-pdf-target-libstdc++-v3 pdf-target-libstdc++-v3
maybe-pdf-target-libstdc++-v3:
maybe-pdf-target-libstdc++-v3: pdf-target-libstdc++-v3

pdf-target-libstdc++-v3: \
    configure-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing pdf in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           pdf) \
	  || exit 1


.PHONY: maybe-html-target-libstdc++-v3 html-target-libstdc++-v3
maybe-html-target-libstdc++-v3:
maybe-html-target-libstdc++-v3: html-target-libstdc++-v3

html-target-libstdc++-v3: \
    configure-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing html in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           html) \
	  || exit 1


.PHONY: maybe-TAGS-target-libstdc++-v3 TAGS-target-libstdc++-v3
maybe-TAGS-target-libstdc++-v3:
maybe-TAGS-target-libstdc++-v3: TAGS-target-libstdc++-v3

TAGS-target-libstdc++-v3: \
    configure-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing TAGS in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           TAGS) \
	  || exit 1


.PHONY: maybe-install-info-target-libstdc++-v3 install-info-target-libstdc++-v3
maybe-install-info-target-libstdc++-v3:
maybe-install-info-target-libstdc++-v3: install-info-target-libstdc++-v3

install-info-target-libstdc++-v3: \
    configure-target-libstdc++-v3 \
    info-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing install-info in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-target-libstdc++-v3 install-pdf-target-libstdc++-v3
maybe-install-pdf-target-libstdc++-v3:
maybe-install-pdf-target-libstdc++-v3: install-pdf-target-libstdc++-v3

install-pdf-target-libstdc++-v3: \
    configure-target-libstdc++-v3 \
    pdf-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing install-pdf in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-target-libstdc++-v3 install-html-target-libstdc++-v3
maybe-install-html-target-libstdc++-v3:
maybe-install-html-target-libstdc++-v3: install-html-target-libstdc++-v3

install-html-target-libstdc++-v3: \
    configure-target-libstdc++-v3 \
    html-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing install-html in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-html) \
	  || exit 1


.PHONY: maybe-installcheck-target-libstdc++-v3 installcheck-target-libstdc++-v3
maybe-installcheck-target-libstdc++-v3:
maybe-installcheck-target-libstdc++-v3: installcheck-target-libstdc++-v3

installcheck-target-libstdc++-v3: \
    configure-target-libstdc++-v3 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing installcheck in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-target-libstdc++-v3 mostlyclean-target-libstdc++-v3
maybe-mostlyclean-target-libstdc++-v3:
maybe-mostlyclean-target-libstdc++-v3: mostlyclean-target-libstdc++-v3

mostlyclean-target-libstdc++-v3: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing mostlyclean in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-target-libstdc++-v3 clean-target-libstdc++-v3
maybe-clean-target-libstdc++-v3:
maybe-clean-target-libstdc++-v3: clean-target-libstdc++-v3

clean-target-libstdc++-v3: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing clean in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           clean) \
	  || exit 1


.PHONY: maybe-distclean-target-libstdc++-v3 distclean-target-libstdc++-v3
maybe-distclean-target-libstdc++-v3:
maybe-distclean-target-libstdc++-v3: distclean-target-libstdc++-v3

distclean-target-libstdc++-v3: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing distclean in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-target-libstdc++-v3 maintainer-clean-target-libstdc++-v3
maybe-maintainer-clean-target-libstdc++-v3:
maybe-maintainer-clean-target-libstdc++-v3: maintainer-clean-target-libstdc++-v3

maintainer-clean-target-libstdc++-v3: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libstdc++-v3/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(RAW_CXX_TARGET_EXPORTS) \
	echo "Doing maintainer-clean in $(TARGET_SUBDIR)/libstdc++-v3" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libstdc++-v3 && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           maintainer-clean) \
	  || exit 1






.PHONY: configure-target-libmudflap maybe-configure-target-libmudflap
maybe-configure-target-libmudflap:
configure-target-libmudflap: stage_current
maybe-configure-target-libmudflap: configure-target-libmudflap
configure-target-libmudflap: 
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libmudflap..."; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libmudflap ; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libmudflap/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libmudflap/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libmudflap/multilib.tmp $(TARGET_SUBDIR)/libmudflap/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libmudflap/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libmudflap/Makefile; \
	    mv $(TARGET_SUBDIR)/libmudflap/multilib.tmp $(TARGET_SUBDIR)/libmudflap/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libmudflap/multilib.tmp $(TARGET_SUBDIR)/libmudflap/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libmudflap/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libmudflap ; \
	$(NORMAL_TARGET_EXPORTS) \
	echo Configuring in $(TARGET_SUBDIR)/libmudflap; \
	cd "$(TARGET_SUBDIR)/libmudflap" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libmudflap/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libmudflap"; \
	libsrcdir="$$s/libmudflap"; \
	rm -f no-such-file || : ; \
	CONFIG_SITE=no-such-file $(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1





.PHONY: all-target-libmudflap maybe-all-target-libmudflap
maybe-all-target-libmudflap:
all-target-libmudflap: stage_current
TARGET-target-libmudflap=all
maybe-all-target-libmudflap: all-target-libmudflap
all-target-libmudflap: configure-target-libmudflap
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_TARGET_FLAGS)  \
		$(TARGET-target-libmudflap))





.PHONY: check-target-libmudflap maybe-check-target-libmudflap
maybe-check-target-libmudflap:
maybe-check-target-libmudflap: check-target-libmudflap

check-target-libmudflap:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)   check)


.PHONY: install-target-libmudflap maybe-install-target-libmudflap
maybe-install-target-libmudflap:
maybe-install-target-libmudflap: install-target-libmudflap

install-target-libmudflap: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libmudflap info-target-libmudflap
maybe-info-target-libmudflap:
maybe-info-target-libmudflap: info-target-libmudflap

info-target-libmudflap: \
    configure-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing info in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           info) \
	  || exit 1


.PHONY: maybe-dvi-target-libmudflap dvi-target-libmudflap
maybe-dvi-target-libmudflap:
maybe-dvi-target-libmudflap: dvi-target-libmudflap

dvi-target-libmudflap: \
    configure-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing dvi in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           dvi) \
	  || exit 1


.PHONY: maybe-pdf-target-libmudflap pdf-target-libmudflap
maybe-pdf-target-libmudflap:
maybe-pdf-target-libmudflap: pdf-target-libmudflap

pdf-target-libmudflap: \
    configure-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing pdf in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           pdf) \
	  || exit 1


.PHONY: maybe-html-target-libmudflap html-target-libmudflap
maybe-html-target-libmudflap:
maybe-html-target-libmudflap: html-target-libmudflap

html-target-libmudflap: \
    configure-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing html in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           html) \
	  || exit 1


.PHONY: maybe-TAGS-target-libmudflap TAGS-target-libmudflap
maybe-TAGS-target-libmudflap:
maybe-TAGS-target-libmudflap: TAGS-target-libmudflap

TAGS-target-libmudflap: \
    configure-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing TAGS in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           TAGS) \
	  || exit 1


.PHONY: maybe-install-info-target-libmudflap install-info-target-libmudflap
maybe-install-info-target-libmudflap:
maybe-install-info-target-libmudflap: install-info-target-libmudflap

install-info-target-libmudflap: \
    configure-target-libmudflap \
    info-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-info in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-target-libmudflap install-pdf-target-libmudflap
maybe-install-pdf-target-libmudflap:
maybe-install-pdf-target-libmudflap: install-pdf-target-libmudflap

install-pdf-target-libmudflap: \
    configure-target-libmudflap \
    pdf-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-pdf in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-target-libmudflap install-html-target-libmudflap
maybe-install-html-target-libmudflap:
maybe-install-html-target-libmudflap: install-html-target-libmudflap

install-html-target-libmudflap: \
    configure-target-libmudflap \
    html-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-html in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-html) \
	  || exit 1


.PHONY: maybe-installcheck-target-libmudflap installcheck-target-libmudflap
maybe-installcheck-target-libmudflap:
maybe-installcheck-target-libmudflap: installcheck-target-libmudflap

installcheck-target-libmudflap: \
    configure-target-libmudflap 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing installcheck in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-target-libmudflap mostlyclean-target-libmudflap
maybe-mostlyclean-target-libmudflap:
maybe-mostlyclean-target-libmudflap: mostlyclean-target-libmudflap

mostlyclean-target-libmudflap: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing mostlyclean in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-target-libmudflap clean-target-libmudflap
maybe-clean-target-libmudflap:
maybe-clean-target-libmudflap: clean-target-libmudflap

clean-target-libmudflap: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing clean in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           clean) \
	  || exit 1


.PHONY: maybe-distclean-target-libmudflap distclean-target-libmudflap
maybe-distclean-target-libmudflap:
maybe-distclean-target-libmudflap: distclean-target-libmudflap

distclean-target-libmudflap: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing distclean in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-target-libmudflap maintainer-clean-target-libmudflap
maybe-maintainer-clean-target-libmudflap:
maybe-maintainer-clean-target-libmudflap: maintainer-clean-target-libmudflap

maintainer-clean-target-libmudflap: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libmudflap/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing maintainer-clean in $(TARGET_SUBDIR)/libmudflap" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libmudflap && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           maintainer-clean) \
	  || exit 1






.PHONY: configure-target-libssp maybe-configure-target-libssp
maybe-configure-target-libssp:
configure-target-libssp: stage_current
maybe-configure-target-libssp: configure-target-libssp
configure-target-libssp: 
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libssp..."; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libssp ; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libssp/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libssp/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libssp/multilib.tmp $(TARGET_SUBDIR)/libssp/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libssp/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libssp/Makefile; \
	    mv $(TARGET_SUBDIR)/libssp/multilib.tmp $(TARGET_SUBDIR)/libssp/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libssp/multilib.tmp $(TARGET_SUBDIR)/libssp/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libssp/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libssp ; \
	$(NORMAL_TARGET_EXPORTS) \
	echo Configuring in $(TARGET_SUBDIR)/libssp; \
	cd "$(TARGET_SUBDIR)/libssp" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libssp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libssp"; \
	libsrcdir="$$s/libssp"; \
	rm -f no-such-file || : ; \
	CONFIG_SITE=no-such-file $(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1





.PHONY: all-target-libssp maybe-all-target-libssp
maybe-all-target-libssp:
all-target-libssp: stage_current
TARGET-target-libssp=all
maybe-all-target-libssp: all-target-libssp
all-target-libssp: configure-target-libssp
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_TARGET_FLAGS)  \
		$(TARGET-target-libssp))





.PHONY: check-target-libssp maybe-check-target-libssp
maybe-check-target-libssp:
maybe-check-target-libssp: check-target-libssp

check-target-libssp:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)   check)


.PHONY: install-target-libssp maybe-install-target-libssp
maybe-install-target-libssp:
maybe-install-target-libssp: install-target-libssp

install-target-libssp: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libssp info-target-libssp
maybe-info-target-libssp:
maybe-info-target-libssp: info-target-libssp

info-target-libssp: \
    configure-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing info in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           info) \
	  || exit 1


.PHONY: maybe-dvi-target-libssp dvi-target-libssp
maybe-dvi-target-libssp:
maybe-dvi-target-libssp: dvi-target-libssp

dvi-target-libssp: \
    configure-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing dvi in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           dvi) \
	  || exit 1


.PHONY: maybe-pdf-target-libssp pdf-target-libssp
maybe-pdf-target-libssp:
maybe-pdf-target-libssp: pdf-target-libssp

pdf-target-libssp: \
    configure-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing pdf in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           pdf) \
	  || exit 1


.PHONY: maybe-html-target-libssp html-target-libssp
maybe-html-target-libssp:
maybe-html-target-libssp: html-target-libssp

html-target-libssp: \
    configure-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing html in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           html) \
	  || exit 1


.PHONY: maybe-TAGS-target-libssp TAGS-target-libssp
maybe-TAGS-target-libssp:
maybe-TAGS-target-libssp: TAGS-target-libssp

TAGS-target-libssp: \
    configure-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing TAGS in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           TAGS) \
	  || exit 1


.PHONY: maybe-install-info-target-libssp install-info-target-libssp
maybe-install-info-target-libssp:
maybe-install-info-target-libssp: install-info-target-libssp

install-info-target-libssp: \
    configure-target-libssp \
    info-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-info in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-target-libssp install-pdf-target-libssp
maybe-install-pdf-target-libssp:
maybe-install-pdf-target-libssp: install-pdf-target-libssp

install-pdf-target-libssp: \
    configure-target-libssp \
    pdf-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-pdf in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-target-libssp install-html-target-libssp
maybe-install-html-target-libssp:
maybe-install-html-target-libssp: install-html-target-libssp

install-html-target-libssp: \
    configure-target-libssp \
    html-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-html in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-html) \
	  || exit 1


.PHONY: maybe-installcheck-target-libssp installcheck-target-libssp
maybe-installcheck-target-libssp:
maybe-installcheck-target-libssp: installcheck-target-libssp

installcheck-target-libssp: \
    configure-target-libssp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing installcheck in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-target-libssp mostlyclean-target-libssp
maybe-mostlyclean-target-libssp:
maybe-mostlyclean-target-libssp: mostlyclean-target-libssp

mostlyclean-target-libssp: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing mostlyclean in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-target-libssp clean-target-libssp
maybe-clean-target-libssp:
maybe-clean-target-libssp: clean-target-libssp

clean-target-libssp: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing clean in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           clean) \
	  || exit 1


.PHONY: maybe-distclean-target-libssp distclean-target-libssp
maybe-distclean-target-libssp:
maybe-distclean-target-libssp: distclean-target-libssp

distclean-target-libssp: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing distclean in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-target-libssp maintainer-clean-target-libssp
maybe-maintainer-clean-target-libssp:
maybe-maintainer-clean-target-libssp: maintainer-clean-target-libssp

maintainer-clean-target-libssp: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libssp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing maintainer-clean in $(TARGET_SUBDIR)/libssp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libssp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           maintainer-clean) \
	  || exit 1






.PHONY: configure-target-newlib maybe-configure-target-newlib
maybe-configure-target-newlib:
configure-target-newlib: stage_current





.PHONY: all-target-newlib maybe-all-target-newlib
maybe-all-target-newlib:
all-target-newlib: stage_current





.PHONY: check-target-newlib maybe-check-target-newlib
maybe-check-target-newlib:

.PHONY: install-target-newlib maybe-install-target-newlib
maybe-install-target-newlib:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-newlib info-target-newlib
maybe-info-target-newlib:

.PHONY: maybe-dvi-target-newlib dvi-target-newlib
maybe-dvi-target-newlib:

.PHONY: maybe-pdf-target-newlib pdf-target-newlib
maybe-pdf-target-newlib:

.PHONY: maybe-html-target-newlib html-target-newlib
maybe-html-target-newlib:

.PHONY: maybe-TAGS-target-newlib TAGS-target-newlib
maybe-TAGS-target-newlib:

.PHONY: maybe-install-info-target-newlib install-info-target-newlib
maybe-install-info-target-newlib:

.PHONY: maybe-install-pdf-target-newlib install-pdf-target-newlib
maybe-install-pdf-target-newlib:

.PHONY: maybe-install-html-target-newlib install-html-target-newlib
maybe-install-html-target-newlib:

.PHONY: maybe-installcheck-target-newlib installcheck-target-newlib
maybe-installcheck-target-newlib:

.PHONY: maybe-mostlyclean-target-newlib mostlyclean-target-newlib
maybe-mostlyclean-target-newlib:

.PHONY: maybe-clean-target-newlib clean-target-newlib
maybe-clean-target-newlib:

.PHONY: maybe-distclean-target-newlib distclean-target-newlib
maybe-distclean-target-newlib:

.PHONY: maybe-maintainer-clean-target-newlib maintainer-clean-target-newlib
maybe-maintainer-clean-target-newlib:





.PHONY: configure-target-libgcc maybe-configure-target-libgcc
maybe-configure-target-libgcc:
configure-target-libgcc: stage_current
maybe-configure-target-libgcc: configure-target-libgcc
configure-target-libgcc: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	$(NORMAL_TARGET_EXPORTS) \
	echo Configuring in $(TARGET_SUBDIR)/libgcc; \
	cd "$(TARGET_SUBDIR)/libgcc" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	rm -f no-such-file || : ; \
	CONFIG_SITE=no-such-file $(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1



.PHONY: configure-stage1-target-libgcc maybe-configure-stage1-target-libgcc
maybe-configure-stage1-target-libgcc:
maybe-configure-stage1-target-libgcc: configure-stage1-target-libgcc
configure-stage1-target-libgcc:
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(NORMAL_TARGET_EXPORTS)  \
	CFLAGS="$(STAGE1_LIBCFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CXXFLAGS="$(STAGE1_LIBCFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS;  \
	echo Configuring stage 1 in $(TARGET_SUBDIR)/libgcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	cd $(TARGET_SUBDIR)/libgcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption} \
	   \
	  --disable-intermodule $(STAGE1_CHECKING) 	  --disable-coverage --enable-languages="$(STAGE1_LANGUAGES)" 

.PHONY: configure-stage2-target-libgcc maybe-configure-stage2-target-libgcc
maybe-configure-stage2-target-libgcc:
maybe-configure-stage2-target-libgcc: configure-stage2-target-libgcc
configure-stage2-target-libgcc:
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(NORMAL_TARGET_EXPORTS) \
	  \
	CFLAGS="$(STAGE2_LIBCFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_LIBCFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS;  \
	echo Configuring stage 2 in $(TARGET_SUBDIR)/libgcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	cd $(TARGET_SUBDIR)/libgcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb2g0-target-libgcc maybe-configure-stageb2g0-target-libgcc
maybe-configure-stageb2g0-target-libgcc:
maybe-configure-stageb2g0-target-libgcc: configure-stageb2g0-target-libgcc
configure-stageb2g0-target-libgcc:
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(NORMAL_TARGET_EXPORTS) \
	  \
	CFLAGS="$(STAGE2_LIBCFLAGS) -g0 $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_LIBCFLAGS) -g0 $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS;  \
	echo Configuring stage b2g0 in $(TARGET_SUBDIR)/libgcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	cd $(TARGET_SUBDIR)/libgcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage3-target-libgcc maybe-configure-stage3-target-libgcc
maybe-configure-stage3-target-libgcc:
maybe-configure-stage3-target-libgcc: configure-stage3-target-libgcc
configure-stage3-target-libgcc:
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(NORMAL_TARGET_EXPORTS) \
	  \
	CFLAGS="$(STAGE3_LIBCFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_LIBCFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS;  \
	echo Configuring stage 3 in $(TARGET_SUBDIR)/libgcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	cd $(TARGET_SUBDIR)/libgcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageb3g2-target-libgcc maybe-configure-stageb3g2-target-libgcc
maybe-configure-stageb3g2-target-libgcc:
maybe-configure-stageb3g2-target-libgcc: configure-stageb3g2-target-libgcc
configure-stageb3g2-target-libgcc:
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(NORMAL_TARGET_EXPORTS) \
	  \
	CFLAGS="$(STAGE3_LIBCFLAGS) -g2 $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_LIBCFLAGS) -g2 $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS;  \
	echo Configuring stage b3g2 in $(TARGET_SUBDIR)/libgcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	cd $(TARGET_SUBDIR)/libgcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stage4-target-libgcc maybe-configure-stage4-target-libgcc
maybe-configure-stage4-target-libgcc:
maybe-configure-stage4-target-libgcc: configure-stage4-target-libgcc
configure-stage4-target-libgcc:
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(NORMAL_TARGET_EXPORTS) \
	  \
	CFLAGS="$(STAGE4_CFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CXXFLAGS="$(STAGE4_CFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS;  \
	echo Configuring stage 4 in $(TARGET_SUBDIR)/libgcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	cd $(TARGET_SUBDIR)/libgcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stageprofile-target-libgcc maybe-configure-stageprofile-target-libgcc
maybe-configure-stageprofile-target-libgcc:
maybe-configure-stageprofile-target-libgcc: configure-stageprofile-target-libgcc
configure-stageprofile-target-libgcc:
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(NORMAL_TARGET_EXPORTS) \
	  \
	CFLAGS="$(STAGE2_LIBCFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CXXFLAGS="$(STAGE2_LIBCFLAGS) $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS;  \
	echo Configuring stage profile in $(TARGET_SUBDIR)/libgcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	cd $(TARGET_SUBDIR)/libgcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   

.PHONY: configure-stagefeedback-target-libgcc maybe-configure-stagefeedback-target-libgcc
maybe-configure-stagefeedback-target-libgcc:
maybe-configure-stagefeedback-target-libgcc: configure-stagefeedback-target-libgcc
configure-stagefeedback-target-libgcc:
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgcc..."; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgcc/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgcc/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgcc/Makefile; \
	    mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgcc/multilib.tmp $(TARGET_SUBDIR)/libgcc/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgcc/Makefile || exit 0; \
	$(NORMAL_TARGET_EXPORTS) \
	  \
	CFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CFLAGS; \
	CXXFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use $(SYSROOT_CFLAGS_FOR_TARGET) $(DEBUG_PREFIX_CFLAGS_FOR_TARGET)"; export CXXFLAGS;  \
	echo Configuring stage feedback in $(TARGET_SUBDIR)/libgcc ; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgcc ; \
	cd $(TARGET_SUBDIR)/libgcc || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgcc/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgcc"; \
	libsrcdir="$$s/libgcc"; \
	$(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption} \
	  --with-build-libsubdir=$(HOST_SUBDIR) \
	   





.PHONY: all-target-libgcc maybe-all-target-libgcc
maybe-all-target-libgcc:
all-target-libgcc: stage_current
TARGET-target-libgcc=all
maybe-all-target-libgcc: all-target-libgcc
all-target-libgcc: configure-target-libgcc
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_TARGET_FLAGS)  \
		$(TARGET-target-libgcc))



.PHONY: all-stage1-target-libgcc maybe-all-stage1-target-libgcc
.PHONY: clean-stage1-target-libgcc maybe-clean-stage1-target-libgcc
maybe-all-stage1-target-libgcc:
maybe-clean-stage1-target-libgcc:
maybe-all-stage1-target-libgcc: all-stage1-target-libgcc
all-stage1: all-stage1-target-libgcc
TARGET-stage1-target-libgcc = $(TARGET-target-libgcc)
all-stage1-target-libgcc: configure-stage1-target-libgcc
	@[ $(current_stage) = stage1 ] || $(MAKE) stage1-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE1_CFLAGS)" CXXFLAGS="$(STAGE1_CFLAGS)" \
		LIBCFLAGS="$(STAGE1_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE1_LIBCFLAGS)" $(EXTRA_TARGET_FLAGS)   \
		$(TARGET-stage1-target-libgcc)

maybe-clean-stage1-target-libgcc: clean-stage1-target-libgcc
clean-stage1: clean-stage1-target-libgcc
clean-stage1-target-libgcc:
	@if [ $(current_stage) = stage1 ]; then \
	  [ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0; \
	else \
	  [ -f $(TARGET_SUBDIR)/stage1-libgcc/Makefile ] || exit 0; \
	  $(MAKE) stage1-start; \
	fi; \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(EXTRA_TARGET_FLAGS)  \
		 clean


.PHONY: all-stage2-target-libgcc maybe-all-stage2-target-libgcc
.PHONY: clean-stage2-target-libgcc maybe-clean-stage2-target-libgcc
maybe-all-stage2-target-libgcc:
maybe-clean-stage2-target-libgcc:
maybe-all-stage2-target-libgcc: all-stage2-target-libgcc
all-stage2: all-stage2-target-libgcc
TARGET-stage2-target-libgcc = $(TARGET-target-libgcc)
all-stage2-target-libgcc: configure-stage2-target-libgcc
	@[ $(current_stage) = stage2 ] || $(MAKE) stage2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	 \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS)" CXXFLAGS="$(STAGE2_CFLAGS)" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_TARGET_FLAGS)   \
		$(TARGET-stage2-target-libgcc)

maybe-clean-stage2-target-libgcc: clean-stage2-target-libgcc
clean-stage2: clean-stage2-target-libgcc
clean-stage2-target-libgcc:
	@if [ $(current_stage) = stage2 ]; then \
	  [ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0; \
	else \
	  [ -f $(TARGET_SUBDIR)/stage2-libgcc/Makefile ] || exit 0; \
	  $(MAKE) stage2-start; \
	fi; \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(EXTRA_TARGET_FLAGS)  \
		  \
		 clean


.PHONY: all-stageb2g0-target-libgcc maybe-all-stageb2g0-target-libgcc
.PHONY: clean-stageb2g0-target-libgcc maybe-clean-stageb2g0-target-libgcc
maybe-all-stageb2g0-target-libgcc:
maybe-clean-stageb2g0-target-libgcc:
maybe-all-stageb2g0-target-libgcc: all-stageb2g0-target-libgcc
all-stageb2g0: all-stageb2g0-target-libgcc
TARGET-stageb2g0-target-libgcc = $(TARGET-target-libgcc)
all-stageb2g0-target-libgcc: configure-stageb2g0-target-libgcc
	@[ $(current_stage) = stageb2g0 ] || $(MAKE) stageb2g0-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	 \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -g0" CXXFLAGS="$(STAGE2_CFLAGS) -g0" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS) -g0" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS) -g0" $(EXTRA_TARGET_FLAGS)   \
		$(TARGET-stageb2g0-target-libgcc)

maybe-clean-stageb2g0-target-libgcc: clean-stageb2g0-target-libgcc
clean-stageb2g0: clean-stageb2g0-target-libgcc
clean-stageb2g0-target-libgcc:
	@if [ $(current_stage) = stageb2g0 ]; then \
	  [ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0; \
	else \
	  [ -f $(TARGET_SUBDIR)/stageb2g0-libgcc/Makefile ] || exit 0; \
	  $(MAKE) stageb2g0-start; \
	fi; \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(EXTRA_TARGET_FLAGS)  \
		  \
		 clean


.PHONY: all-stage3-target-libgcc maybe-all-stage3-target-libgcc
.PHONY: clean-stage3-target-libgcc maybe-clean-stage3-target-libgcc
maybe-all-stage3-target-libgcc:
maybe-clean-stage3-target-libgcc:
maybe-all-stage3-target-libgcc: all-stage3-target-libgcc
all-stage3: all-stage3-target-libgcc
TARGET-stage3-target-libgcc = $(TARGET-target-libgcc)
all-stage3-target-libgcc: configure-stage3-target-libgcc
	@[ $(current_stage) = stage3 ] || $(MAKE) stage3-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	 \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS)" CXXFLAGS="$(STAGE3_CFLAGS)" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS)" $(EXTRA_TARGET_FLAGS)   \
		$(TARGET-stage3-target-libgcc)

maybe-clean-stage3-target-libgcc: clean-stage3-target-libgcc
clean-stage3: clean-stage3-target-libgcc
clean-stage3-target-libgcc:
	@if [ $(current_stage) = stage3 ]; then \
	  [ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0; \
	else \
	  [ -f $(TARGET_SUBDIR)/stage3-libgcc/Makefile ] || exit 0; \
	  $(MAKE) stage3-start; \
	fi; \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(EXTRA_TARGET_FLAGS)  \
		  \
		 clean


.PHONY: all-stageb3g2-target-libgcc maybe-all-stageb3g2-target-libgcc
.PHONY: clean-stageb3g2-target-libgcc maybe-clean-stageb3g2-target-libgcc
maybe-all-stageb3g2-target-libgcc:
maybe-clean-stageb3g2-target-libgcc:
maybe-all-stageb3g2-target-libgcc: all-stageb3g2-target-libgcc
all-stageb3g2: all-stageb3g2-target-libgcc
TARGET-stageb3g2-target-libgcc = $(TARGET-target-libgcc)
all-stageb3g2-target-libgcc: configure-stageb3g2-target-libgcc
	@[ $(current_stage) = stageb3g2 ] || $(MAKE) stageb3g2-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	 \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -g2" CXXFLAGS="$(STAGE3_CFLAGS) -g2" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -g2" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -g2" $(EXTRA_TARGET_FLAGS)   \
		$(TARGET-stageb3g2-target-libgcc)

maybe-clean-stageb3g2-target-libgcc: clean-stageb3g2-target-libgcc
clean-stageb3g2: clean-stageb3g2-target-libgcc
clean-stageb3g2-target-libgcc:
	@if [ $(current_stage) = stageb3g2 ]; then \
	  [ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0; \
	else \
	  [ -f $(TARGET_SUBDIR)/stageb3g2-libgcc/Makefile ] || exit 0; \
	  $(MAKE) stageb3g2-start; \
	fi; \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(EXTRA_TARGET_FLAGS)  \
		  \
		 clean


.PHONY: all-stage4-target-libgcc maybe-all-stage4-target-libgcc
.PHONY: clean-stage4-target-libgcc maybe-clean-stage4-target-libgcc
maybe-all-stage4-target-libgcc:
maybe-clean-stage4-target-libgcc:
maybe-all-stage4-target-libgcc: all-stage4-target-libgcc
all-stage4: all-stage4-target-libgcc
TARGET-stage4-target-libgcc = $(TARGET-target-libgcc)
all-stage4-target-libgcc: configure-stage4-target-libgcc
	@[ $(current_stage) = stage4 ] || $(MAKE) stage4-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	 \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE4_CFLAGS)" CXXFLAGS="$(STAGE4_CFLAGS)" \
		LIBCFLAGS="$(STAGE4_CFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE4_CFLAGS)" $(EXTRA_TARGET_FLAGS)   \
		$(TARGET-stage4-target-libgcc)

maybe-clean-stage4-target-libgcc: clean-stage4-target-libgcc
clean-stage4: clean-stage4-target-libgcc
clean-stage4-target-libgcc:
	@if [ $(current_stage) = stage4 ]; then \
	  [ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0; \
	else \
	  [ -f $(TARGET_SUBDIR)/stage4-libgcc/Makefile ] || exit 0; \
	  $(MAKE) stage4-start; \
	fi; \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(EXTRA_TARGET_FLAGS)  \
		  \
		 clean


.PHONY: all-stageprofile-target-libgcc maybe-all-stageprofile-target-libgcc
.PHONY: clean-stageprofile-target-libgcc maybe-clean-stageprofile-target-libgcc
maybe-all-stageprofile-target-libgcc:
maybe-clean-stageprofile-target-libgcc:
maybe-all-stageprofile-target-libgcc: all-stageprofile-target-libgcc
all-stageprofile: all-stageprofile-target-libgcc
TARGET-stageprofile-target-libgcc = $(TARGET-target-libgcc)
all-stageprofile-target-libgcc: configure-stageprofile-target-libgcc
	@[ $(current_stage) = stageprofile ] || $(MAKE) stageprofile-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	 \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" CXXFLAGS="$(STAGE2_CFLAGS) -fprofile-generate" \
		LIBCFLAGS="$(STAGE2_LIBCFLAGS)" \
		CFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(STAGE2_LIBCFLAGS)" $(EXTRA_TARGET_FLAGS)   \
		$(TARGET-stageprofile-target-libgcc)

maybe-clean-stageprofile-target-libgcc: clean-stageprofile-target-libgcc
clean-stageprofile: clean-stageprofile-target-libgcc
clean-stageprofile-target-libgcc:
	@if [ $(current_stage) = stageprofile ]; then \
	  [ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0; \
	else \
	  [ -f $(TARGET_SUBDIR)/stageprofile-libgcc/Makefile ] || exit 0; \
	  $(MAKE) stageprofile-start; \
	fi; \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(EXTRA_TARGET_FLAGS)  \
		  \
		 clean


.PHONY: all-stagefeedback-target-libgcc maybe-all-stagefeedback-target-libgcc
.PHONY: clean-stagefeedback-target-libgcc maybe-clean-stagefeedback-target-libgcc
maybe-all-stagefeedback-target-libgcc:
maybe-clean-stagefeedback-target-libgcc:
maybe-all-stagefeedback-target-libgcc: all-stagefeedback-target-libgcc
all-stagefeedback: all-stagefeedback-target-libgcc
TARGET-stagefeedback-target-libgcc = $(TARGET-target-libgcc)
all-stagefeedback-target-libgcc: configure-stagefeedback-target-libgcc
	@[ $(current_stage) = stagefeedback ] || $(MAKE) stagefeedback-start
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	 \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(BASE_FLAGS_TO_PASS) \
		CFLAGS="$(STAGE3_CFLAGS) -fprofile-use" CXXFLAGS="$(STAGE3_CFLAGS) -fprofile-use" \
		LIBCFLAGS="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" \
		CXXFLAGS_FOR_TARGET="$(STAGE3_LIBCFLAGS) -fprofile-use" $(EXTRA_TARGET_FLAGS)   \
		$(TARGET-stagefeedback-target-libgcc)

maybe-clean-stagefeedback-target-libgcc: clean-stagefeedback-target-libgcc
clean-stagefeedback: clean-stagefeedback-target-libgcc
clean-stagefeedback-target-libgcc:
	@if [ $(current_stage) = stagefeedback ]; then \
	  [ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0; \
	else \
	  [ -f $(TARGET_SUBDIR)/stagefeedback-libgcc/Makefile ] || exit 0; \
	  $(MAKE) stagefeedback-start; \
	fi; \
	cd $(TARGET_SUBDIR)/libgcc && \
	$(MAKE) $(EXTRA_TARGET_FLAGS)  \
		  \
		 clean






.PHONY: check-target-libgcc maybe-check-target-libgcc
maybe-check-target-libgcc:
maybe-check-target-libgcc: check-target-libgcc

# Dummy target for uncheckable module.
check-target-libgcc:


.PHONY: install-target-libgcc maybe-install-target-libgcc
maybe-install-target-libgcc:
maybe-install-target-libgcc: install-target-libgcc

install-target-libgcc: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libgcc info-target-libgcc
maybe-info-target-libgcc:
maybe-info-target-libgcc: info-target-libgcc

info-target-libgcc: \
    configure-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing info in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           info) \
	  || exit 1


.PHONY: maybe-dvi-target-libgcc dvi-target-libgcc
maybe-dvi-target-libgcc:
maybe-dvi-target-libgcc: dvi-target-libgcc

dvi-target-libgcc: \
    configure-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing dvi in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           dvi) \
	  || exit 1


.PHONY: maybe-pdf-target-libgcc pdf-target-libgcc
maybe-pdf-target-libgcc:
maybe-pdf-target-libgcc: pdf-target-libgcc

pdf-target-libgcc: \
    configure-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing pdf in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           pdf) \
	  || exit 1


.PHONY: maybe-html-target-libgcc html-target-libgcc
maybe-html-target-libgcc:
maybe-html-target-libgcc: html-target-libgcc

html-target-libgcc: \
    configure-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing html in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           html) \
	  || exit 1


.PHONY: maybe-TAGS-target-libgcc TAGS-target-libgcc
maybe-TAGS-target-libgcc:
maybe-TAGS-target-libgcc: TAGS-target-libgcc

TAGS-target-libgcc: \
    configure-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing TAGS in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           TAGS) \
	  || exit 1


.PHONY: maybe-install-info-target-libgcc install-info-target-libgcc
maybe-install-info-target-libgcc:
maybe-install-info-target-libgcc: install-info-target-libgcc

install-info-target-libgcc: \
    configure-target-libgcc \
    info-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-info in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-target-libgcc install-pdf-target-libgcc
maybe-install-pdf-target-libgcc:
maybe-install-pdf-target-libgcc: install-pdf-target-libgcc

install-pdf-target-libgcc: \
    configure-target-libgcc \
    pdf-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-pdf in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-target-libgcc install-html-target-libgcc
maybe-install-html-target-libgcc:
maybe-install-html-target-libgcc: install-html-target-libgcc

install-html-target-libgcc: \
    configure-target-libgcc \
    html-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-html in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-html) \
	  || exit 1


.PHONY: maybe-installcheck-target-libgcc installcheck-target-libgcc
maybe-installcheck-target-libgcc:
maybe-installcheck-target-libgcc: installcheck-target-libgcc

installcheck-target-libgcc: \
    configure-target-libgcc 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing installcheck in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-target-libgcc mostlyclean-target-libgcc
maybe-mostlyclean-target-libgcc:
maybe-mostlyclean-target-libgcc: mostlyclean-target-libgcc

mostlyclean-target-libgcc: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing mostlyclean in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-target-libgcc clean-target-libgcc
maybe-clean-target-libgcc:
maybe-clean-target-libgcc: clean-target-libgcc

clean-target-libgcc: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing clean in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           clean) \
	  || exit 1


.PHONY: maybe-distclean-target-libgcc distclean-target-libgcc
maybe-distclean-target-libgcc:
maybe-distclean-target-libgcc: distclean-target-libgcc

distclean-target-libgcc: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing distclean in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-target-libgcc maintainer-clean-target-libgcc
maybe-maintainer-clean-target-libgcc:
maybe-maintainer-clean-target-libgcc: maintainer-clean-target-libgcc

maintainer-clean-target-libgcc: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgcc/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing maintainer-clean in $(TARGET_SUBDIR)/libgcc" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgcc && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           maintainer-clean) \
	  || exit 1






.PHONY: configure-target-libgfortran maybe-configure-target-libgfortran
maybe-configure-target-libgfortran:
configure-target-libgfortran: stage_current





.PHONY: all-target-libgfortran maybe-all-target-libgfortran
maybe-all-target-libgfortran:
all-target-libgfortran: stage_current





.PHONY: check-target-libgfortran maybe-check-target-libgfortran
maybe-check-target-libgfortran:

.PHONY: install-target-libgfortran maybe-install-target-libgfortran
maybe-install-target-libgfortran:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libgfortran info-target-libgfortran
maybe-info-target-libgfortran:

.PHONY: maybe-dvi-target-libgfortran dvi-target-libgfortran
maybe-dvi-target-libgfortran:

.PHONY: maybe-pdf-target-libgfortran pdf-target-libgfortran
maybe-pdf-target-libgfortran:

.PHONY: maybe-html-target-libgfortran html-target-libgfortran
maybe-html-target-libgfortran:

.PHONY: maybe-TAGS-target-libgfortran TAGS-target-libgfortran
maybe-TAGS-target-libgfortran:

.PHONY: maybe-install-info-target-libgfortran install-info-target-libgfortran
maybe-install-info-target-libgfortran:

.PHONY: maybe-install-pdf-target-libgfortran install-pdf-target-libgfortran
maybe-install-pdf-target-libgfortran:

.PHONY: maybe-install-html-target-libgfortran install-html-target-libgfortran
maybe-install-html-target-libgfortran:

.PHONY: maybe-installcheck-target-libgfortran installcheck-target-libgfortran
maybe-installcheck-target-libgfortran:

.PHONY: maybe-mostlyclean-target-libgfortran mostlyclean-target-libgfortran
maybe-mostlyclean-target-libgfortran:

.PHONY: maybe-clean-target-libgfortran clean-target-libgfortran
maybe-clean-target-libgfortran:

.PHONY: maybe-distclean-target-libgfortran distclean-target-libgfortran
maybe-distclean-target-libgfortran:

.PHONY: maybe-maintainer-clean-target-libgfortran maintainer-clean-target-libgfortran
maybe-maintainer-clean-target-libgfortran:





.PHONY: configure-target-libobjc maybe-configure-target-libobjc
maybe-configure-target-libobjc:
configure-target-libobjc: stage_current





.PHONY: all-target-libobjc maybe-all-target-libobjc
maybe-all-target-libobjc:
all-target-libobjc: stage_current





.PHONY: check-target-libobjc maybe-check-target-libobjc
maybe-check-target-libobjc:

.PHONY: install-target-libobjc maybe-install-target-libobjc
maybe-install-target-libobjc:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libobjc info-target-libobjc
maybe-info-target-libobjc:

.PHONY: maybe-dvi-target-libobjc dvi-target-libobjc
maybe-dvi-target-libobjc:

.PHONY: maybe-pdf-target-libobjc pdf-target-libobjc
maybe-pdf-target-libobjc:

.PHONY: maybe-html-target-libobjc html-target-libobjc
maybe-html-target-libobjc:

.PHONY: maybe-TAGS-target-libobjc TAGS-target-libobjc
maybe-TAGS-target-libobjc:

.PHONY: maybe-install-info-target-libobjc install-info-target-libobjc
maybe-install-info-target-libobjc:

.PHONY: maybe-install-pdf-target-libobjc install-pdf-target-libobjc
maybe-install-pdf-target-libobjc:

.PHONY: maybe-install-html-target-libobjc install-html-target-libobjc
maybe-install-html-target-libobjc:

.PHONY: maybe-installcheck-target-libobjc installcheck-target-libobjc
maybe-installcheck-target-libobjc:

.PHONY: maybe-mostlyclean-target-libobjc mostlyclean-target-libobjc
maybe-mostlyclean-target-libobjc:

.PHONY: maybe-clean-target-libobjc clean-target-libobjc
maybe-clean-target-libobjc:

.PHONY: maybe-distclean-target-libobjc distclean-target-libobjc
maybe-distclean-target-libobjc:

.PHONY: maybe-maintainer-clean-target-libobjc maintainer-clean-target-libobjc
maybe-maintainer-clean-target-libobjc:





.PHONY: configure-target-libtermcap maybe-configure-target-libtermcap
maybe-configure-target-libtermcap:
configure-target-libtermcap: stage_current





.PHONY: all-target-libtermcap maybe-all-target-libtermcap
maybe-all-target-libtermcap:
all-target-libtermcap: stage_current





.PHONY: check-target-libtermcap maybe-check-target-libtermcap
maybe-check-target-libtermcap:

.PHONY: install-target-libtermcap maybe-install-target-libtermcap
maybe-install-target-libtermcap:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libtermcap info-target-libtermcap
maybe-info-target-libtermcap:

.PHONY: maybe-dvi-target-libtermcap dvi-target-libtermcap
maybe-dvi-target-libtermcap:

.PHONY: maybe-pdf-target-libtermcap pdf-target-libtermcap
maybe-pdf-target-libtermcap:

.PHONY: maybe-html-target-libtermcap html-target-libtermcap
maybe-html-target-libtermcap:

.PHONY: maybe-TAGS-target-libtermcap TAGS-target-libtermcap
maybe-TAGS-target-libtermcap:

.PHONY: maybe-install-info-target-libtermcap install-info-target-libtermcap
maybe-install-info-target-libtermcap:

.PHONY: maybe-install-pdf-target-libtermcap install-pdf-target-libtermcap
maybe-install-pdf-target-libtermcap:

.PHONY: maybe-install-html-target-libtermcap install-html-target-libtermcap
maybe-install-html-target-libtermcap:

.PHONY: maybe-installcheck-target-libtermcap installcheck-target-libtermcap
maybe-installcheck-target-libtermcap:

.PHONY: maybe-mostlyclean-target-libtermcap mostlyclean-target-libtermcap
maybe-mostlyclean-target-libtermcap:

.PHONY: maybe-clean-target-libtermcap clean-target-libtermcap
maybe-clean-target-libtermcap:

.PHONY: maybe-distclean-target-libtermcap distclean-target-libtermcap
maybe-distclean-target-libtermcap:

.PHONY: maybe-maintainer-clean-target-libtermcap maintainer-clean-target-libtermcap
maybe-maintainer-clean-target-libtermcap:





.PHONY: configure-target-winsup maybe-configure-target-winsup
maybe-configure-target-winsup:
configure-target-winsup: stage_current





.PHONY: all-target-winsup maybe-all-target-winsup
maybe-all-target-winsup:
all-target-winsup: stage_current





.PHONY: check-target-winsup maybe-check-target-winsup
maybe-check-target-winsup:

.PHONY: install-target-winsup maybe-install-target-winsup
maybe-install-target-winsup:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-winsup info-target-winsup
maybe-info-target-winsup:

.PHONY: maybe-dvi-target-winsup dvi-target-winsup
maybe-dvi-target-winsup:

.PHONY: maybe-pdf-target-winsup pdf-target-winsup
maybe-pdf-target-winsup:

.PHONY: maybe-html-target-winsup html-target-winsup
maybe-html-target-winsup:

.PHONY: maybe-TAGS-target-winsup TAGS-target-winsup
maybe-TAGS-target-winsup:

.PHONY: maybe-install-info-target-winsup install-info-target-winsup
maybe-install-info-target-winsup:

.PHONY: maybe-install-pdf-target-winsup install-pdf-target-winsup
maybe-install-pdf-target-winsup:

.PHONY: maybe-install-html-target-winsup install-html-target-winsup
maybe-install-html-target-winsup:

.PHONY: maybe-installcheck-target-winsup installcheck-target-winsup
maybe-installcheck-target-winsup:

.PHONY: maybe-mostlyclean-target-winsup mostlyclean-target-winsup
maybe-mostlyclean-target-winsup:

.PHONY: maybe-clean-target-winsup clean-target-winsup
maybe-clean-target-winsup:

.PHONY: maybe-distclean-target-winsup distclean-target-winsup
maybe-distclean-target-winsup:

.PHONY: maybe-maintainer-clean-target-winsup maintainer-clean-target-winsup
maybe-maintainer-clean-target-winsup:





.PHONY: configure-target-libgloss maybe-configure-target-libgloss
maybe-configure-target-libgloss:
configure-target-libgloss: stage_current





.PHONY: all-target-libgloss maybe-all-target-libgloss
maybe-all-target-libgloss:
all-target-libgloss: stage_current





.PHONY: check-target-libgloss maybe-check-target-libgloss
maybe-check-target-libgloss:

.PHONY: install-target-libgloss maybe-install-target-libgloss
maybe-install-target-libgloss:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libgloss info-target-libgloss
maybe-info-target-libgloss:

.PHONY: maybe-dvi-target-libgloss dvi-target-libgloss
maybe-dvi-target-libgloss:

.PHONY: maybe-pdf-target-libgloss pdf-target-libgloss
maybe-pdf-target-libgloss:

.PHONY: maybe-html-target-libgloss html-target-libgloss
maybe-html-target-libgloss:

.PHONY: maybe-TAGS-target-libgloss TAGS-target-libgloss
maybe-TAGS-target-libgloss:

.PHONY: maybe-install-info-target-libgloss install-info-target-libgloss
maybe-install-info-target-libgloss:

.PHONY: maybe-install-pdf-target-libgloss install-pdf-target-libgloss
maybe-install-pdf-target-libgloss:

.PHONY: maybe-install-html-target-libgloss install-html-target-libgloss
maybe-install-html-target-libgloss:

.PHONY: maybe-installcheck-target-libgloss installcheck-target-libgloss
maybe-installcheck-target-libgloss:

.PHONY: maybe-mostlyclean-target-libgloss mostlyclean-target-libgloss
maybe-mostlyclean-target-libgloss:

.PHONY: maybe-clean-target-libgloss clean-target-libgloss
maybe-clean-target-libgloss:

.PHONY: maybe-distclean-target-libgloss distclean-target-libgloss
maybe-distclean-target-libgloss:

.PHONY: maybe-maintainer-clean-target-libgloss maintainer-clean-target-libgloss
maybe-maintainer-clean-target-libgloss:





.PHONY: configure-target-libiberty maybe-configure-target-libiberty
maybe-configure-target-libiberty:
configure-target-libiberty: stage_current
maybe-configure-target-libiberty: configure-target-libiberty
configure-target-libiberty: 
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libiberty..."; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libiberty ; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libiberty/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libiberty/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libiberty/multilib.tmp $(TARGET_SUBDIR)/libiberty/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libiberty/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libiberty/Makefile; \
	    mv $(TARGET_SUBDIR)/libiberty/multilib.tmp $(TARGET_SUBDIR)/libiberty/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libiberty/multilib.tmp $(TARGET_SUBDIR)/libiberty/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libiberty/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libiberty ; \
	$(NORMAL_TARGET_EXPORTS) \
	echo Configuring in $(TARGET_SUBDIR)/libiberty; \
	cd "$(TARGET_SUBDIR)/libiberty" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libiberty/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libiberty"; \
	libsrcdir="$$s/libiberty"; \
	rm -f no-such-file || : ; \
	CONFIG_SITE=no-such-file $(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1





.PHONY: all-target-libiberty maybe-all-target-libiberty
maybe-all-target-libiberty:
all-target-libiberty: stage_current
TARGET-target-libiberty=all
maybe-all-target-libiberty: all-target-libiberty
all-target-libiberty: configure-target-libiberty
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_TARGET_FLAGS)  \
		$(TARGET-target-libiberty))





.PHONY: check-target-libiberty maybe-check-target-libiberty
maybe-check-target-libiberty:
maybe-check-target-libiberty: check-target-libiberty

check-target-libiberty:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)   check)


.PHONY: install-target-libiberty maybe-install-target-libiberty
maybe-install-target-libiberty:
maybe-install-target-libiberty: install-target-libiberty

install-target-libiberty: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libiberty info-target-libiberty
maybe-info-target-libiberty:
maybe-info-target-libiberty: info-target-libiberty

info-target-libiberty: \
    configure-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing info in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           info) \
	  || exit 1


.PHONY: maybe-dvi-target-libiberty dvi-target-libiberty
maybe-dvi-target-libiberty:
maybe-dvi-target-libiberty: dvi-target-libiberty

dvi-target-libiberty: \
    configure-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing dvi in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           dvi) \
	  || exit 1


.PHONY: maybe-pdf-target-libiberty pdf-target-libiberty
maybe-pdf-target-libiberty:
maybe-pdf-target-libiberty: pdf-target-libiberty

pdf-target-libiberty: \
    configure-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing pdf in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           pdf) \
	  || exit 1


.PHONY: maybe-html-target-libiberty html-target-libiberty
maybe-html-target-libiberty:
maybe-html-target-libiberty: html-target-libiberty

html-target-libiberty: \
    configure-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing html in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           html) \
	  || exit 1


.PHONY: maybe-TAGS-target-libiberty TAGS-target-libiberty
maybe-TAGS-target-libiberty:
maybe-TAGS-target-libiberty: TAGS-target-libiberty

TAGS-target-libiberty: \
    configure-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing TAGS in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           TAGS) \
	  || exit 1


.PHONY: maybe-install-info-target-libiberty install-info-target-libiberty
maybe-install-info-target-libiberty:
maybe-install-info-target-libiberty: install-info-target-libiberty

install-info-target-libiberty: \
    configure-target-libiberty \
    info-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-info in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-target-libiberty install-pdf-target-libiberty
maybe-install-pdf-target-libiberty:
maybe-install-pdf-target-libiberty: install-pdf-target-libiberty

install-pdf-target-libiberty: \
    configure-target-libiberty \
    pdf-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-pdf in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-target-libiberty install-html-target-libiberty
maybe-install-html-target-libiberty:
maybe-install-html-target-libiberty: install-html-target-libiberty

install-html-target-libiberty: \
    configure-target-libiberty \
    html-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-html in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-html) \
	  || exit 1


.PHONY: maybe-installcheck-target-libiberty installcheck-target-libiberty
maybe-installcheck-target-libiberty:
maybe-installcheck-target-libiberty: installcheck-target-libiberty

installcheck-target-libiberty: \
    configure-target-libiberty 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing installcheck in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-target-libiberty mostlyclean-target-libiberty
maybe-mostlyclean-target-libiberty:
maybe-mostlyclean-target-libiberty: mostlyclean-target-libiberty

mostlyclean-target-libiberty: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing mostlyclean in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-target-libiberty clean-target-libiberty
maybe-clean-target-libiberty:
maybe-clean-target-libiberty: clean-target-libiberty

clean-target-libiberty: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing clean in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           clean) \
	  || exit 1


.PHONY: maybe-distclean-target-libiberty distclean-target-libiberty
maybe-distclean-target-libiberty:
maybe-distclean-target-libiberty: distclean-target-libiberty

distclean-target-libiberty: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing distclean in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-target-libiberty maintainer-clean-target-libiberty
maybe-maintainer-clean-target-libiberty:
maybe-maintainer-clean-target-libiberty: maintainer-clean-target-libiberty

maintainer-clean-target-libiberty: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libiberty/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing maintainer-clean in $(TARGET_SUBDIR)/libiberty" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libiberty && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           maintainer-clean) \
	  || exit 1






.PHONY: configure-target-gperf maybe-configure-target-gperf
maybe-configure-target-gperf:
configure-target-gperf: stage_current





.PHONY: all-target-gperf maybe-all-target-gperf
maybe-all-target-gperf:
all-target-gperf: stage_current





.PHONY: check-target-gperf maybe-check-target-gperf
maybe-check-target-gperf:

.PHONY: install-target-gperf maybe-install-target-gperf
maybe-install-target-gperf:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-gperf info-target-gperf
maybe-info-target-gperf:

.PHONY: maybe-dvi-target-gperf dvi-target-gperf
maybe-dvi-target-gperf:

.PHONY: maybe-pdf-target-gperf pdf-target-gperf
maybe-pdf-target-gperf:

.PHONY: maybe-html-target-gperf html-target-gperf
maybe-html-target-gperf:

.PHONY: maybe-TAGS-target-gperf TAGS-target-gperf
maybe-TAGS-target-gperf:

.PHONY: maybe-install-info-target-gperf install-info-target-gperf
maybe-install-info-target-gperf:

.PHONY: maybe-install-pdf-target-gperf install-pdf-target-gperf
maybe-install-pdf-target-gperf:

.PHONY: maybe-install-html-target-gperf install-html-target-gperf
maybe-install-html-target-gperf:

.PHONY: maybe-installcheck-target-gperf installcheck-target-gperf
maybe-installcheck-target-gperf:

.PHONY: maybe-mostlyclean-target-gperf mostlyclean-target-gperf
maybe-mostlyclean-target-gperf:

.PHONY: maybe-clean-target-gperf clean-target-gperf
maybe-clean-target-gperf:

.PHONY: maybe-distclean-target-gperf distclean-target-gperf
maybe-distclean-target-gperf:

.PHONY: maybe-maintainer-clean-target-gperf maintainer-clean-target-gperf
maybe-maintainer-clean-target-gperf:





.PHONY: configure-target-examples maybe-configure-target-examples
maybe-configure-target-examples:
configure-target-examples: stage_current





.PHONY: all-target-examples maybe-all-target-examples
maybe-all-target-examples:
all-target-examples: stage_current





.PHONY: check-target-examples maybe-check-target-examples
maybe-check-target-examples:

.PHONY: install-target-examples maybe-install-target-examples
maybe-install-target-examples:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-examples info-target-examples
maybe-info-target-examples:

.PHONY: maybe-dvi-target-examples dvi-target-examples
maybe-dvi-target-examples:

.PHONY: maybe-pdf-target-examples pdf-target-examples
maybe-pdf-target-examples:

.PHONY: maybe-html-target-examples html-target-examples
maybe-html-target-examples:

.PHONY: maybe-TAGS-target-examples TAGS-target-examples
maybe-TAGS-target-examples:

.PHONY: maybe-install-info-target-examples install-info-target-examples
maybe-install-info-target-examples:

.PHONY: maybe-install-pdf-target-examples install-pdf-target-examples
maybe-install-pdf-target-examples:

.PHONY: maybe-install-html-target-examples install-html-target-examples
maybe-install-html-target-examples:

.PHONY: maybe-installcheck-target-examples installcheck-target-examples
maybe-installcheck-target-examples:

.PHONY: maybe-mostlyclean-target-examples mostlyclean-target-examples
maybe-mostlyclean-target-examples:

.PHONY: maybe-clean-target-examples clean-target-examples
maybe-clean-target-examples:

.PHONY: maybe-distclean-target-examples distclean-target-examples
maybe-distclean-target-examples:

.PHONY: maybe-maintainer-clean-target-examples maintainer-clean-target-examples
maybe-maintainer-clean-target-examples:





.PHONY: configure-target-libffi maybe-configure-target-libffi
maybe-configure-target-libffi:
configure-target-libffi: stage_current





.PHONY: all-target-libffi maybe-all-target-libffi
maybe-all-target-libffi:
all-target-libffi: stage_current





.PHONY: check-target-libffi maybe-check-target-libffi
maybe-check-target-libffi:

.PHONY: install-target-libffi maybe-install-target-libffi
maybe-install-target-libffi:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libffi info-target-libffi
maybe-info-target-libffi:

.PHONY: maybe-dvi-target-libffi dvi-target-libffi
maybe-dvi-target-libffi:

.PHONY: maybe-pdf-target-libffi pdf-target-libffi
maybe-pdf-target-libffi:

.PHONY: maybe-html-target-libffi html-target-libffi
maybe-html-target-libffi:

.PHONY: maybe-TAGS-target-libffi TAGS-target-libffi
maybe-TAGS-target-libffi:

.PHONY: maybe-install-info-target-libffi install-info-target-libffi
maybe-install-info-target-libffi:

.PHONY: maybe-install-pdf-target-libffi install-pdf-target-libffi
maybe-install-pdf-target-libffi:

.PHONY: maybe-install-html-target-libffi install-html-target-libffi
maybe-install-html-target-libffi:

.PHONY: maybe-installcheck-target-libffi installcheck-target-libffi
maybe-installcheck-target-libffi:

.PHONY: maybe-mostlyclean-target-libffi mostlyclean-target-libffi
maybe-mostlyclean-target-libffi:

.PHONY: maybe-clean-target-libffi clean-target-libffi
maybe-clean-target-libffi:

.PHONY: maybe-distclean-target-libffi distclean-target-libffi
maybe-distclean-target-libffi:

.PHONY: maybe-maintainer-clean-target-libffi maintainer-clean-target-libffi
maybe-maintainer-clean-target-libffi:





.PHONY: configure-target-libjava maybe-configure-target-libjava
maybe-configure-target-libjava:
configure-target-libjava: stage_current





.PHONY: all-target-libjava maybe-all-target-libjava
maybe-all-target-libjava:
all-target-libjava: stage_current





.PHONY: check-target-libjava maybe-check-target-libjava
maybe-check-target-libjava:

.PHONY: install-target-libjava maybe-install-target-libjava
maybe-install-target-libjava:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libjava info-target-libjava
maybe-info-target-libjava:

.PHONY: maybe-dvi-target-libjava dvi-target-libjava
maybe-dvi-target-libjava:

.PHONY: maybe-pdf-target-libjava pdf-target-libjava
maybe-pdf-target-libjava:

.PHONY: maybe-html-target-libjava html-target-libjava
maybe-html-target-libjava:

.PHONY: maybe-TAGS-target-libjava TAGS-target-libjava
maybe-TAGS-target-libjava:

.PHONY: maybe-install-info-target-libjava install-info-target-libjava
maybe-install-info-target-libjava:

.PHONY: maybe-install-pdf-target-libjava install-pdf-target-libjava
maybe-install-pdf-target-libjava:

.PHONY: maybe-install-html-target-libjava install-html-target-libjava
maybe-install-html-target-libjava:

.PHONY: maybe-installcheck-target-libjava installcheck-target-libjava
maybe-installcheck-target-libjava:

.PHONY: maybe-mostlyclean-target-libjava mostlyclean-target-libjava
maybe-mostlyclean-target-libjava:

.PHONY: maybe-clean-target-libjava clean-target-libjava
maybe-clean-target-libjava:

.PHONY: maybe-distclean-target-libjava distclean-target-libjava
maybe-distclean-target-libjava:

.PHONY: maybe-maintainer-clean-target-libjava maintainer-clean-target-libjava
maybe-maintainer-clean-target-libjava:





.PHONY: configure-target-zlib maybe-configure-target-zlib
maybe-configure-target-zlib:
configure-target-zlib: stage_current





.PHONY: all-target-zlib maybe-all-target-zlib
maybe-all-target-zlib:
all-target-zlib: stage_current





.PHONY: check-target-zlib maybe-check-target-zlib
maybe-check-target-zlib:

.PHONY: install-target-zlib maybe-install-target-zlib
maybe-install-target-zlib:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-zlib info-target-zlib
maybe-info-target-zlib:

.PHONY: maybe-dvi-target-zlib dvi-target-zlib
maybe-dvi-target-zlib:

.PHONY: maybe-pdf-target-zlib pdf-target-zlib
maybe-pdf-target-zlib:

.PHONY: maybe-html-target-zlib html-target-zlib
maybe-html-target-zlib:

.PHONY: maybe-TAGS-target-zlib TAGS-target-zlib
maybe-TAGS-target-zlib:

.PHONY: maybe-install-info-target-zlib install-info-target-zlib
maybe-install-info-target-zlib:

.PHONY: maybe-install-pdf-target-zlib install-pdf-target-zlib
maybe-install-pdf-target-zlib:

.PHONY: maybe-install-html-target-zlib install-html-target-zlib
maybe-install-html-target-zlib:

.PHONY: maybe-installcheck-target-zlib installcheck-target-zlib
maybe-installcheck-target-zlib:

.PHONY: maybe-mostlyclean-target-zlib mostlyclean-target-zlib
maybe-mostlyclean-target-zlib:

.PHONY: maybe-clean-target-zlib clean-target-zlib
maybe-clean-target-zlib:

.PHONY: maybe-distclean-target-zlib distclean-target-zlib
maybe-distclean-target-zlib:

.PHONY: maybe-maintainer-clean-target-zlib maintainer-clean-target-zlib
maybe-maintainer-clean-target-zlib:





.PHONY: configure-target-boehm-gc maybe-configure-target-boehm-gc
maybe-configure-target-boehm-gc:
configure-target-boehm-gc: stage_current





.PHONY: all-target-boehm-gc maybe-all-target-boehm-gc
maybe-all-target-boehm-gc:
all-target-boehm-gc: stage_current





.PHONY: check-target-boehm-gc maybe-check-target-boehm-gc
maybe-check-target-boehm-gc:

.PHONY: install-target-boehm-gc maybe-install-target-boehm-gc
maybe-install-target-boehm-gc:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-boehm-gc info-target-boehm-gc
maybe-info-target-boehm-gc:

.PHONY: maybe-dvi-target-boehm-gc dvi-target-boehm-gc
maybe-dvi-target-boehm-gc:

.PHONY: maybe-pdf-target-boehm-gc pdf-target-boehm-gc
maybe-pdf-target-boehm-gc:

.PHONY: maybe-html-target-boehm-gc html-target-boehm-gc
maybe-html-target-boehm-gc:

.PHONY: maybe-TAGS-target-boehm-gc TAGS-target-boehm-gc
maybe-TAGS-target-boehm-gc:

.PHONY: maybe-install-info-target-boehm-gc install-info-target-boehm-gc
maybe-install-info-target-boehm-gc:

.PHONY: maybe-install-pdf-target-boehm-gc install-pdf-target-boehm-gc
maybe-install-pdf-target-boehm-gc:

.PHONY: maybe-install-html-target-boehm-gc install-html-target-boehm-gc
maybe-install-html-target-boehm-gc:

.PHONY: maybe-installcheck-target-boehm-gc installcheck-target-boehm-gc
maybe-installcheck-target-boehm-gc:

.PHONY: maybe-mostlyclean-target-boehm-gc mostlyclean-target-boehm-gc
maybe-mostlyclean-target-boehm-gc:

.PHONY: maybe-clean-target-boehm-gc clean-target-boehm-gc
maybe-clean-target-boehm-gc:

.PHONY: maybe-distclean-target-boehm-gc distclean-target-boehm-gc
maybe-distclean-target-boehm-gc:

.PHONY: maybe-maintainer-clean-target-boehm-gc maintainer-clean-target-boehm-gc
maybe-maintainer-clean-target-boehm-gc:





.PHONY: configure-target-qthreads maybe-configure-target-qthreads
maybe-configure-target-qthreads:
configure-target-qthreads: stage_current





.PHONY: all-target-qthreads maybe-all-target-qthreads
maybe-all-target-qthreads:
all-target-qthreads: stage_current





.PHONY: check-target-qthreads maybe-check-target-qthreads
maybe-check-target-qthreads:

.PHONY: install-target-qthreads maybe-install-target-qthreads
maybe-install-target-qthreads:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-qthreads info-target-qthreads
maybe-info-target-qthreads:

.PHONY: maybe-dvi-target-qthreads dvi-target-qthreads
maybe-dvi-target-qthreads:

.PHONY: maybe-pdf-target-qthreads pdf-target-qthreads
maybe-pdf-target-qthreads:

.PHONY: maybe-html-target-qthreads html-target-qthreads
maybe-html-target-qthreads:

.PHONY: maybe-TAGS-target-qthreads TAGS-target-qthreads
maybe-TAGS-target-qthreads:

.PHONY: maybe-install-info-target-qthreads install-info-target-qthreads
maybe-install-info-target-qthreads:

.PHONY: maybe-install-pdf-target-qthreads install-pdf-target-qthreads
maybe-install-pdf-target-qthreads:

.PHONY: maybe-install-html-target-qthreads install-html-target-qthreads
maybe-install-html-target-qthreads:

.PHONY: maybe-installcheck-target-qthreads installcheck-target-qthreads
maybe-installcheck-target-qthreads:

.PHONY: maybe-mostlyclean-target-qthreads mostlyclean-target-qthreads
maybe-mostlyclean-target-qthreads:

.PHONY: maybe-clean-target-qthreads clean-target-qthreads
maybe-clean-target-qthreads:

.PHONY: maybe-distclean-target-qthreads distclean-target-qthreads
maybe-distclean-target-qthreads:

.PHONY: maybe-maintainer-clean-target-qthreads maintainer-clean-target-qthreads
maybe-maintainer-clean-target-qthreads:





.PHONY: configure-target-rda maybe-configure-target-rda
maybe-configure-target-rda:
configure-target-rda: stage_current





.PHONY: all-target-rda maybe-all-target-rda
maybe-all-target-rda:
all-target-rda: stage_current





.PHONY: check-target-rda maybe-check-target-rda
maybe-check-target-rda:

.PHONY: install-target-rda maybe-install-target-rda
maybe-install-target-rda:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-rda info-target-rda
maybe-info-target-rda:

.PHONY: maybe-dvi-target-rda dvi-target-rda
maybe-dvi-target-rda:

.PHONY: maybe-pdf-target-rda pdf-target-rda
maybe-pdf-target-rda:

.PHONY: maybe-html-target-rda html-target-rda
maybe-html-target-rda:

.PHONY: maybe-TAGS-target-rda TAGS-target-rda
maybe-TAGS-target-rda:

.PHONY: maybe-install-info-target-rda install-info-target-rda
maybe-install-info-target-rda:

.PHONY: maybe-install-pdf-target-rda install-pdf-target-rda
maybe-install-pdf-target-rda:

.PHONY: maybe-install-html-target-rda install-html-target-rda
maybe-install-html-target-rda:

.PHONY: maybe-installcheck-target-rda installcheck-target-rda
maybe-installcheck-target-rda:

.PHONY: maybe-mostlyclean-target-rda mostlyclean-target-rda
maybe-mostlyclean-target-rda:

.PHONY: maybe-clean-target-rda clean-target-rda
maybe-clean-target-rda:

.PHONY: maybe-distclean-target-rda distclean-target-rda
maybe-distclean-target-rda:

.PHONY: maybe-maintainer-clean-target-rda maintainer-clean-target-rda
maybe-maintainer-clean-target-rda:





.PHONY: configure-target-libada maybe-configure-target-libada
maybe-configure-target-libada:
configure-target-libada: stage_current





.PHONY: all-target-libada maybe-all-target-libada
maybe-all-target-libada:
all-target-libada: stage_current





.PHONY: check-target-libada maybe-check-target-libada
maybe-check-target-libada:

.PHONY: install-target-libada maybe-install-target-libada
maybe-install-target-libada:

# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libada info-target-libada
maybe-info-target-libada:

.PHONY: maybe-dvi-target-libada dvi-target-libada
maybe-dvi-target-libada:

.PHONY: maybe-pdf-target-libada pdf-target-libada
maybe-pdf-target-libada:

.PHONY: maybe-html-target-libada html-target-libada
maybe-html-target-libada:

.PHONY: maybe-TAGS-target-libada TAGS-target-libada
maybe-TAGS-target-libada:

.PHONY: maybe-install-info-target-libada install-info-target-libada
maybe-install-info-target-libada:

.PHONY: maybe-install-pdf-target-libada install-pdf-target-libada
maybe-install-pdf-target-libada:

.PHONY: maybe-install-html-target-libada install-html-target-libada
maybe-install-html-target-libada:

.PHONY: maybe-installcheck-target-libada installcheck-target-libada
maybe-installcheck-target-libada:

.PHONY: maybe-mostlyclean-target-libada mostlyclean-target-libada
maybe-mostlyclean-target-libada:

.PHONY: maybe-clean-target-libada clean-target-libada
maybe-clean-target-libada:

.PHONY: maybe-distclean-target-libada distclean-target-libada
maybe-distclean-target-libada:

.PHONY: maybe-maintainer-clean-target-libada maintainer-clean-target-libada
maybe-maintainer-clean-target-libada:





.PHONY: configure-target-libgomp maybe-configure-target-libgomp
maybe-configure-target-libgomp:
configure-target-libgomp: stage_current
maybe-configure-target-libgomp: configure-target-libgomp
configure-target-libgomp: 
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	echo "Checking multilib configuration for libgomp..."; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgomp ; \
	$(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/libgomp/multilib.tmp 2> /dev/null ; \
	if test -r $(TARGET_SUBDIR)/libgomp/multilib.out; then \
	  if cmp -s $(TARGET_SUBDIR)/libgomp/multilib.tmp $(TARGET_SUBDIR)/libgomp/multilib.out; then \
	    rm -f $(TARGET_SUBDIR)/libgomp/multilib.tmp; \
	  else \
	    rm -f $(TARGET_SUBDIR)/libgomp/Makefile; \
	    mv $(TARGET_SUBDIR)/libgomp/multilib.tmp $(TARGET_SUBDIR)/libgomp/multilib.out; \
	  fi; \
	else \
	  mv $(TARGET_SUBDIR)/libgomp/multilib.tmp $(TARGET_SUBDIR)/libgomp/multilib.out; \
	fi; \
	test ! -f $(TARGET_SUBDIR)/libgomp/Makefile || exit 0; \
	$(SHELL) $(srcdir)/mkinstalldirs $(TARGET_SUBDIR)/libgomp ; \
	$(NORMAL_TARGET_EXPORTS) \
	echo Configuring in $(TARGET_SUBDIR)/libgomp; \
	cd "$(TARGET_SUBDIR)/libgomp" || exit 1; \
	case $(srcdir) in \
	  /* | [A-Za-z]:[\\/]*) topdir=$(srcdir) ;; \
	  *) topdir=`echo $(TARGET_SUBDIR)/libgomp/ | \
		sed -e 's,\./,,g' -e 's,[^/]*/,../,g' `$(srcdir) ;; \
	esac; \
	srcdiroption="--srcdir=$${topdir}/libgomp"; \
	libsrcdir="$$s/libgomp"; \
	rm -f no-such-file || : ; \
	CONFIG_SITE=no-such-file $(SHELL) $${libsrcdir}/configure \
	  $(TARGET_CONFIGARGS) --build=${build_alias} --host=${target_alias} \
	  --target=${target_alias} $${srcdiroption}  \
	  || exit 1





.PHONY: all-target-libgomp maybe-all-target-libgomp
maybe-all-target-libgomp:
all-target-libgomp: stage_current
TARGET-target-libgomp=all
maybe-all-target-libgomp: all-target-libgomp
all-target-libgomp: configure-target-libgomp
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) $(EXTRA_TARGET_FLAGS)  \
		$(TARGET-target-libgomp))





.PHONY: check-target-libgomp maybe-check-target-libgomp
maybe-check-target-libgomp:
maybe-check-target-libgomp: check-target-libgomp

check-target-libgomp:
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)   check)


.PHONY: install-target-libgomp maybe-install-target-libgomp
maybe-install-target-libgomp:
maybe-install-target-libgomp: install-target-libgomp

install-target-libgomp: installdirs
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(TARGET_FLAGS_TO_PASS)  install)


# Other targets (info, dvi, pdf, etc.)

.PHONY: maybe-info-target-libgomp info-target-libgomp
maybe-info-target-libgomp:
maybe-info-target-libgomp: info-target-libgomp

info-target-libgomp: \
    configure-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing info in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           info) \
	  || exit 1


.PHONY: maybe-dvi-target-libgomp dvi-target-libgomp
maybe-dvi-target-libgomp:
maybe-dvi-target-libgomp: dvi-target-libgomp

dvi-target-libgomp: \
    configure-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing dvi in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           dvi) \
	  || exit 1


.PHONY: maybe-pdf-target-libgomp pdf-target-libgomp
maybe-pdf-target-libgomp:
maybe-pdf-target-libgomp: pdf-target-libgomp

pdf-target-libgomp: \
    configure-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing pdf in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           pdf) \
	  || exit 1


.PHONY: maybe-html-target-libgomp html-target-libgomp
maybe-html-target-libgomp:
maybe-html-target-libgomp: html-target-libgomp

html-target-libgomp: \
    configure-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing html in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           html) \
	  || exit 1


.PHONY: maybe-TAGS-target-libgomp TAGS-target-libgomp
maybe-TAGS-target-libgomp:
maybe-TAGS-target-libgomp: TAGS-target-libgomp

TAGS-target-libgomp: \
    configure-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing TAGS in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           TAGS) \
	  || exit 1


.PHONY: maybe-install-info-target-libgomp install-info-target-libgomp
maybe-install-info-target-libgomp:
maybe-install-info-target-libgomp: install-info-target-libgomp

install-info-target-libgomp: \
    configure-target-libgomp \
    info-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-info in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-info) \
	  || exit 1


.PHONY: maybe-install-pdf-target-libgomp install-pdf-target-libgomp
maybe-install-pdf-target-libgomp:
maybe-install-pdf-target-libgomp: install-pdf-target-libgomp

install-pdf-target-libgomp: \
    configure-target-libgomp \
    pdf-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-pdf in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-pdf) \
	  || exit 1


.PHONY: maybe-install-html-target-libgomp install-html-target-libgomp
maybe-install-html-target-libgomp:
maybe-install-html-target-libgomp: install-html-target-libgomp

install-html-target-libgomp: \
    configure-target-libgomp \
    html-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing install-html in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           install-html) \
	  || exit 1


.PHONY: maybe-installcheck-target-libgomp installcheck-target-libgomp
maybe-installcheck-target-libgomp:
maybe-installcheck-target-libgomp: installcheck-target-libgomp

installcheck-target-libgomp: \
    configure-target-libgomp 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing installcheck in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           installcheck) \
	  || exit 1


.PHONY: maybe-mostlyclean-target-libgomp mostlyclean-target-libgomp
maybe-mostlyclean-target-libgomp:
maybe-mostlyclean-target-libgomp: mostlyclean-target-libgomp

mostlyclean-target-libgomp: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing mostlyclean in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           mostlyclean) \
	  || exit 1


.PHONY: maybe-clean-target-libgomp clean-target-libgomp
maybe-clean-target-libgomp:
maybe-clean-target-libgomp: clean-target-libgomp

clean-target-libgomp: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing clean in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           clean) \
	  || exit 1


.PHONY: maybe-distclean-target-libgomp distclean-target-libgomp
maybe-distclean-target-libgomp:
maybe-distclean-target-libgomp: distclean-target-libgomp

distclean-target-libgomp: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing distclean in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           distclean) \
	  || exit 1


.PHONY: maybe-maintainer-clean-target-libgomp maintainer-clean-target-libgomp
maybe-maintainer-clean-target-libgomp:
maybe-maintainer-clean-target-libgomp: maintainer-clean-target-libgomp

maintainer-clean-target-libgomp: 
	@: $(MAKE); $(unstage)
	@[ -f $(TARGET_SUBDIR)/libgomp/Makefile ] || exit 0 ; \
	r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(NORMAL_TARGET_EXPORTS) \
	echo "Doing maintainer-clean in $(TARGET_SUBDIR)/libgomp" ; \
	for flag in $(EXTRA_TARGET_FLAGS); do \
	  eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'; export \1|"`; \
	done; \
	(cd $(TARGET_SUBDIR)/libgomp && \
	  $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
	          "CC=$${CC}" "CXX=$${CXX}" "LD=$${LD}" "NM=$${NM}" \
	          "RANLIB=$${RANLIB}" \
	          "DLLTOOL=$${DLLTOOL}" "WINDRES=$${WINDRES}" "WINDMC=$${WINDMC}" \
	           maintainer-clean) \
	  || exit 1




# ----------
# GCC module
# ----------


.PHONY: check-gcc-c++
check-gcc-c++:
	@if [ -f ./gcc/Makefile ] ; then \
	  r=`${PWD_COMMAND}`; export r; \
	  s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	  $(HOST_EXPORTS) \
	  (cd gcc && $(MAKE) $(GCC_FLAGS_TO_PASS) check-c++); \
	else \
	  true; \
	fi

.PHONY: check-c++
check-c++: check-target-libstdc++-v3 check-gcc-c++

# Install the gcc headers files, but not the fixed include files,
# which Cygnus is not allowed to distribute.  This rule is very
# dependent on the workings of the gcc Makefile.in.
.PHONY: gcc-no-fixedincludes
gcc-no-fixedincludes:
	@if [ -f ./gcc/Makefile ]; then \
	  rm -rf gcc/tmp-include; \
	  mv gcc/include gcc/tmp-include 2>/dev/null; \
	  mkdir gcc/include; \
	  cp $(srcdir)/gcc/gsyslimits.h gcc/include/syslimits.h; \
	  touch gcc/stmp-fixinc gcc/include/fixed; \
	  rm -f gcc/stmp-headers gcc/stmp-int-hdrs; \
	  r=`${PWD_COMMAND}`; export r; \
	  s=`cd $(srcdir); ${PWD_COMMAND}` ; export s; \
	  $(HOST_EXPORTS) \
	  (cd ./gcc && \
	   $(MAKE) $(GCC_FLAGS_TO_PASS) install); \
	  rm -rf gcc/include; \
	  mv gcc/tmp-include gcc/include 2>/dev/null; \
	else true; fi

# ---------------------
# GCC bootstrap support
# ---------------------

# We track the current stage (the one in 'gcc') in the stage_current file.
# stage_last instead tracks the stage that was built last.  These targets
# are dummy when toplevel bootstrap is not active.

# While making host and target tools, symlinks to the final stage must be
# there, so $(unstage) should be run at various points.  To avoid excessive
# recursive invocations of make, we "inline" them using a variable.  These
# must be referenced as ": $(MAKE) ; $(unstage)" rather than "$(unstage)"
# to avoid warnings from the GNU Make job server.

unstage = :
stage = :
current_stage = ""

unstage = if [ -f stage_last ]; then [ -f stage_current ] || $(MAKE) `cat stage_last`-start || exit 1; else :; fi
stage = if [ -f stage_current ]; then $(MAKE) `cat stage_current`-end || exit 1; else :; fi
current_stage = "`cat stage_current 2> /dev/null`"

.PHONY: unstage stage
unstage:
	@: $(MAKE); $(unstage)
stage:
	@: $(MAKE); $(stage)

# Disable commands for lean bootstrap.
LEAN = false

# We name the build directories for the various stages "stage1-gcc",
# "stage2-gcc","stage3-gcc", etc.

# Since the 'compare' process will fail (on debugging information) if any
# directory names are different, we need to link the gcc directory for
# the previous stage to a constant name ('prev-gcc'), and to make the name of
# the build directories constant as well. For the latter, we use naked names
# like 'gcc', because the scripts in that directory assume it.  We use
# mv on platforms where symlinks to directories do not work or are not
# reliable.

# 'touch' doesn't work right on some platforms.
STAMP = echo timestamp > 

# We only want to compare .o files, so set this!
objext = .o


.PHONY: stage1-start stage1-end

stage1-start::
	@: $(MAKE); $(stage); \
	echo stage1 > stage_current ; \
	echo stage1 > stage_last; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)
	@cd $(HOST_SUBDIR); [ -d stage1-gcc ] || \
	  mkdir stage1-gcc; \
	mv stage1-gcc gcc 
	@cd $(HOST_SUBDIR); [ -d stage1-gmp ] || \
	  mkdir stage1-gmp; \
	mv stage1-gmp gmp 
	@cd $(HOST_SUBDIR); [ -d stage1-mpfr ] || \
	  mkdir stage1-mpfr; \
	mv stage1-mpfr mpfr 
	@cd $(HOST_SUBDIR); [ -d stage1-intl ] || \
	  mkdir stage1-intl; \
	mv stage1-intl intl 
	@cd $(HOST_SUBDIR); [ -d stage1-libcpp ] || \
	  mkdir stage1-libcpp; \
	mv stage1-libcpp libcpp 
	@cd $(HOST_SUBDIR); [ -d stage1-libdecnumber ] || \
	  mkdir stage1-libdecnumber; \
	mv stage1-libdecnumber libdecnumber 
	@cd $(HOST_SUBDIR); [ -d stage1-libiberty ] || \
	  mkdir stage1-libiberty; \
	mv stage1-libiberty libiberty 
	@[ -d stage1-$(TARGET_SUBDIR) ] || \
	  mkdir stage1-$(TARGET_SUBDIR); \
	mv stage1-$(TARGET_SUBDIR) $(TARGET_SUBDIR) 

stage1-end:: 
	@if test -d $(HOST_SUBDIR)/gcc ; then \
	  cd $(HOST_SUBDIR); mv gcc stage1-gcc  ; \
	fi
	@if test -d $(HOST_SUBDIR)/gmp ; then \
	  cd $(HOST_SUBDIR); mv gmp stage1-gmp  ; \
	fi
	@if test -d $(HOST_SUBDIR)/mpfr ; then \
	  cd $(HOST_SUBDIR); mv mpfr stage1-mpfr  ; \
	fi
	@if test -d $(HOST_SUBDIR)/intl ; then \
	  cd $(HOST_SUBDIR); mv intl stage1-intl  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libcpp ; then \
	  cd $(HOST_SUBDIR); mv libcpp stage1-libcpp  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libdecnumber ; then \
	  cd $(HOST_SUBDIR); mv libdecnumber stage1-libdecnumber  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libiberty ; then \
	  cd $(HOST_SUBDIR); mv libiberty stage1-libiberty  ; \
	fi
	@if test -d $(TARGET_SUBDIR) ; then \
	  mv $(TARGET_SUBDIR) stage1-$(TARGET_SUBDIR)  ; \
	fi
	rm -f stage_current

# Bubble a bug fix through all the stages up to stage 1.  They are
# remade, but not reconfigured.  The next stage (if any) will not be
# reconfigured either.
.PHONY: stage1-bubble
stage1-bubble:: 
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stage1-lean  ; then \
	  echo Skipping rebuild of stage1 ; \
	else \
	  $(MAKE) stage1-start; \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-stage1; \
	fi

.PHONY: all-stage1 clean-stage1
do-clean: clean-stage1

# FIXME: Will not need to be conditional when toplevel bootstrap is the
# only possibility, but now it conflicts with no-bootstrap rules




# Rules to wipe a stage and all the following ones, also used for cleanstrap

.PHONY: distclean-stage1
distclean-stage1::
	@: $(MAKE); $(stage)
	@test "`cat stage_last`" != stage1 || rm -f stage_last
	rm -rf stage1-* 




.PHONY: stage2-start stage2-end

stage2-start::
	@: $(MAKE); $(stage); \
	echo stage2 > stage_current ; \
	echo stage2 > stage_last; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)
	@cd $(HOST_SUBDIR); [ -d stage2-gcc ] || \
	  mkdir stage2-gcc; \
	mv stage2-gcc gcc  ; \
	mv stage1-gcc prev-gcc || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stage2-gmp ] || \
	  mkdir stage2-gmp; \
	mv stage2-gmp gmp  ; \
	mv stage1-gmp prev-gmp || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stage2-mpfr ] || \
	  mkdir stage2-mpfr; \
	mv stage2-mpfr mpfr  ; \
	mv stage1-mpfr prev-mpfr || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stage2-intl ] || \
	  mkdir stage2-intl; \
	mv stage2-intl intl  ; \
	mv stage1-intl prev-intl || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stage2-libcpp ] || \
	  mkdir stage2-libcpp; \
	mv stage2-libcpp libcpp  ; \
	mv stage1-libcpp prev-libcpp || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stage2-libdecnumber ] || \
	  mkdir stage2-libdecnumber; \
	mv stage2-libdecnumber libdecnumber  ; \
	mv stage1-libdecnumber prev-libdecnumber || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stage2-libiberty ] || \
	  mkdir stage2-libiberty; \
	mv stage2-libiberty libiberty  ; \
	mv stage1-libiberty prev-libiberty || test -f stage1-lean 
	@[ -d stage2-$(TARGET_SUBDIR) ] || \
	  mkdir stage2-$(TARGET_SUBDIR); \
	mv stage2-$(TARGET_SUBDIR) $(TARGET_SUBDIR)  ; \
	mv stage1-$(TARGET_SUBDIR) prev-$(TARGET_SUBDIR) || test -f stage1-lean 

stage2-end:: 
	@if test -d $(HOST_SUBDIR)/gcc ; then \
	  cd $(HOST_SUBDIR); mv gcc stage2-gcc ; \
	  mv prev-gcc stage1-gcc ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/gmp ; then \
	  cd $(HOST_SUBDIR); mv gmp stage2-gmp ; \
	  mv prev-gmp stage1-gmp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/mpfr ; then \
	  cd $(HOST_SUBDIR); mv mpfr stage2-mpfr ; \
	  mv prev-mpfr stage1-mpfr ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/intl ; then \
	  cd $(HOST_SUBDIR); mv intl stage2-intl ; \
	  mv prev-intl stage1-intl ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libcpp ; then \
	  cd $(HOST_SUBDIR); mv libcpp stage2-libcpp ; \
	  mv prev-libcpp stage1-libcpp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libdecnumber ; then \
	  cd $(HOST_SUBDIR); mv libdecnumber stage2-libdecnumber ; \
	  mv prev-libdecnumber stage1-libdecnumber ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libiberty ; then \
	  cd $(HOST_SUBDIR); mv libiberty stage2-libiberty ; \
	  mv prev-libiberty stage1-libiberty ; :  ; \
	fi
	@if test -d $(TARGET_SUBDIR) ; then \
	  mv $(TARGET_SUBDIR) stage2-$(TARGET_SUBDIR)  ; \
	  mv prev-$(TARGET_SUBDIR) stage1-$(TARGET_SUBDIR) ; :  ; \
	fi
	rm -f stage_current

# Bubble a bug fix through all the stages up to stage 2.  They are
# remade, but not reconfigured.  The next stage (if any) will not be
# reconfigured either.
.PHONY: stage2-bubble
stage2-bubble:: stage1-bubble
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stage2-lean || test -f stage1-lean  ; then \
	  echo Skipping rebuild of stage2 ; \
	else \
	  $(MAKE) stage2-start; \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-stage2; \
	fi

.PHONY: all-stage2 clean-stage2
do-clean: clean-stage2

# FIXME: Will not need to be conditional when toplevel bootstrap is the
# only possibility, but now it conflicts with no-bootstrap rules



.PHONY: bootstrap2 bootstrap2-lean
bootstrap2:
	echo stage2 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stage2-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target

bootstrap2-lean:
	echo stage2 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) LEAN=: stage2-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target


# Rules to wipe a stage and all the following ones, also used for cleanstrap
distclean-stage1:: distclean-stage2 
.PHONY: distclean-stage2
distclean-stage2::
	@: $(MAKE); $(stage)
	@test "`cat stage_last`" != stage2 || rm -f stage_last
	rm -rf stage2-* 




.PHONY: stageb2g0-start stageb2g0-end

stageb2g0-start::
	@: $(MAKE); $(stage); \
	echo stageb2g0 > stage_current ; \
	echo stageb2g0 > stage_last; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)
	@cd $(HOST_SUBDIR); [ -d stageb2g0-gcc ] || \
	  mkdir stageb2g0-gcc; \
	mv stageb2g0-gcc gcc  ; \
	mv stage1-gcc prev-gcc || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageb2g0-gmp ] || \
	  mkdir stageb2g0-gmp; \
	mv stageb2g0-gmp gmp  ; \
	mv stage1-gmp prev-gmp || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageb2g0-mpfr ] || \
	  mkdir stageb2g0-mpfr; \
	mv stageb2g0-mpfr mpfr  ; \
	mv stage1-mpfr prev-mpfr || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageb2g0-intl ] || \
	  mkdir stageb2g0-intl; \
	mv stageb2g0-intl intl  ; \
	mv stage1-intl prev-intl || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageb2g0-libcpp ] || \
	  mkdir stageb2g0-libcpp; \
	mv stageb2g0-libcpp libcpp  ; \
	mv stage1-libcpp prev-libcpp || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageb2g0-libdecnumber ] || \
	  mkdir stageb2g0-libdecnumber; \
	mv stageb2g0-libdecnumber libdecnumber  ; \
	mv stage1-libdecnumber prev-libdecnumber || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageb2g0-libiberty ] || \
	  mkdir stageb2g0-libiberty; \
	mv stageb2g0-libiberty libiberty  ; \
	mv stage1-libiberty prev-libiberty || test -f stage1-lean 
	@[ -d stageb2g0-$(TARGET_SUBDIR) ] || \
	  mkdir stageb2g0-$(TARGET_SUBDIR); \
	mv stageb2g0-$(TARGET_SUBDIR) $(TARGET_SUBDIR)  ; \
	mv stage1-$(TARGET_SUBDIR) prev-$(TARGET_SUBDIR) || test -f stage1-lean 

stageb2g0-end:: 
	@if test -d $(HOST_SUBDIR)/gcc ; then \
	  cd $(HOST_SUBDIR); mv gcc stageb2g0-gcc ; \
	  mv prev-gcc stage1-gcc ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/gmp ; then \
	  cd $(HOST_SUBDIR); mv gmp stageb2g0-gmp ; \
	  mv prev-gmp stage1-gmp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/mpfr ; then \
	  cd $(HOST_SUBDIR); mv mpfr stageb2g0-mpfr ; \
	  mv prev-mpfr stage1-mpfr ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/intl ; then \
	  cd $(HOST_SUBDIR); mv intl stageb2g0-intl ; \
	  mv prev-intl stage1-intl ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libcpp ; then \
	  cd $(HOST_SUBDIR); mv libcpp stageb2g0-libcpp ; \
	  mv prev-libcpp stage1-libcpp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libdecnumber ; then \
	  cd $(HOST_SUBDIR); mv libdecnumber stageb2g0-libdecnumber ; \
	  mv prev-libdecnumber stage1-libdecnumber ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libiberty ; then \
	  cd $(HOST_SUBDIR); mv libiberty stageb2g0-libiberty ; \
	  mv prev-libiberty stage1-libiberty ; :  ; \
	fi
	@if test -d $(TARGET_SUBDIR) ; then \
	  mv $(TARGET_SUBDIR) stageb2g0-$(TARGET_SUBDIR)  ; \
	  mv prev-$(TARGET_SUBDIR) stage1-$(TARGET_SUBDIR) ; :  ; \
	fi
	rm -f stage_current

# Bubble a bug fix through all the stages up to stage b2g0.  They are
# remade, but not reconfigured.  The next stage (if any) will not be
# reconfigured either.
.PHONY: stageb2g0-bubble
stageb2g0-bubble:: stage1-bubble
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stageb2g0-lean || test -f stage1-lean  ; then \
	  echo Skipping rebuild of stageb2g0 ; \
	else \
	  $(MAKE) stageb2g0-start; \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-stageb2g0; \
	fi

.PHONY: all-stageb2g0 clean-stageb2g0
do-clean: clean-stageb2g0

# FIXME: Will not need to be conditional when toplevel bootstrap is the
# only possibility, but now it conflicts with no-bootstrap rules



.PHONY: bootstrap2-debug bootstrap2-debug-lean
bootstrap2-debug:
	echo stageb2g0 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stageb2g0-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target

bootstrap2-debug-lean:
	echo stageb2g0 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) LEAN=: stageb2g0-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target


# Rules to wipe a stage and all the following ones, also used for cleanstrap
distclean-stage1:: distclean-stageb2g0 
.PHONY: distclean-stageb2g0
distclean-stageb2g0::
	@: $(MAKE); $(stage)
	@test "`cat stage_last`" != stageb2g0 || rm -f stage_last
	rm -rf stageb2g0-* 




.PHONY: stage3-start stage3-end

stage3-start::
	@: $(MAKE); $(stage); \
	echo stage3 > stage_current ; \
	echo stage3 > stage_last; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)
	@cd $(HOST_SUBDIR); [ -d stage3-gcc ] || \
	  mkdir stage3-gcc; \
	mv stage3-gcc gcc  ; \
	mv stage2-gcc prev-gcc || test -f stage2-lean 
	@cd $(HOST_SUBDIR); [ -d stage3-gmp ] || \
	  mkdir stage3-gmp; \
	mv stage3-gmp gmp  ; \
	mv stage2-gmp prev-gmp || test -f stage2-lean 
	@cd $(HOST_SUBDIR); [ -d stage3-mpfr ] || \
	  mkdir stage3-mpfr; \
	mv stage3-mpfr mpfr  ; \
	mv stage2-mpfr prev-mpfr || test -f stage2-lean 
	@cd $(HOST_SUBDIR); [ -d stage3-intl ] || \
	  mkdir stage3-intl; \
	mv stage3-intl intl  ; \
	mv stage2-intl prev-intl || test -f stage2-lean 
	@cd $(HOST_SUBDIR); [ -d stage3-libcpp ] || \
	  mkdir stage3-libcpp; \
	mv stage3-libcpp libcpp  ; \
	mv stage2-libcpp prev-libcpp || test -f stage2-lean 
	@cd $(HOST_SUBDIR); [ -d stage3-libdecnumber ] || \
	  mkdir stage3-libdecnumber; \
	mv stage3-libdecnumber libdecnumber  ; \
	mv stage2-libdecnumber prev-libdecnumber || test -f stage2-lean 
	@cd $(HOST_SUBDIR); [ -d stage3-libiberty ] || \
	  mkdir stage3-libiberty; \
	mv stage3-libiberty libiberty  ; \
	mv stage2-libiberty prev-libiberty || test -f stage2-lean 
	@[ -d stage3-$(TARGET_SUBDIR) ] || \
	  mkdir stage3-$(TARGET_SUBDIR); \
	mv stage3-$(TARGET_SUBDIR) $(TARGET_SUBDIR)  ; \
	mv stage2-$(TARGET_SUBDIR) prev-$(TARGET_SUBDIR) || test -f stage2-lean 

stage3-end:: 
	@if test -d $(HOST_SUBDIR)/gcc ; then \
	  cd $(HOST_SUBDIR); mv gcc stage3-gcc ; \
	  mv prev-gcc stage2-gcc ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/gmp ; then \
	  cd $(HOST_SUBDIR); mv gmp stage3-gmp ; \
	  mv prev-gmp stage2-gmp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/mpfr ; then \
	  cd $(HOST_SUBDIR); mv mpfr stage3-mpfr ; \
	  mv prev-mpfr stage2-mpfr ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/intl ; then \
	  cd $(HOST_SUBDIR); mv intl stage3-intl ; \
	  mv prev-intl stage2-intl ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libcpp ; then \
	  cd $(HOST_SUBDIR); mv libcpp stage3-libcpp ; \
	  mv prev-libcpp stage2-libcpp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libdecnumber ; then \
	  cd $(HOST_SUBDIR); mv libdecnumber stage3-libdecnumber ; \
	  mv prev-libdecnumber stage2-libdecnumber ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libiberty ; then \
	  cd $(HOST_SUBDIR); mv libiberty stage3-libiberty ; \
	  mv prev-libiberty stage2-libiberty ; :  ; \
	fi
	@if test -d $(TARGET_SUBDIR) ; then \
	  mv $(TARGET_SUBDIR) stage3-$(TARGET_SUBDIR)  ; \
	  mv prev-$(TARGET_SUBDIR) stage2-$(TARGET_SUBDIR) ; :  ; \
	fi
	rm -f stage_current

# Bubble a bug fix through all the stages up to stage 3.  They are
# remade, but not reconfigured.  The next stage (if any) will not be
# reconfigured either.
.PHONY: stage3-bubble
stage3-bubble:: stage2-bubble
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stage3-lean || test -f stage2-lean  ; then \
	  echo Skipping rebuild of stage3 ; \
	else \
	  $(MAKE) stage3-start; \
	  if $(LEAN); then \
	    rm -rf stage1-* ; \
	    $(STAMP) stage1-lean ; \
	  fi; \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-stage3; \
	fi
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) compare

.PHONY: all-stage3 clean-stage3
do-clean: clean-stage3

# FIXME: Will not need to be conditional when toplevel bootstrap is the
# only possibility, but now it conflicts with no-bootstrap rules

compare:
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stage2-lean; then \
	  echo Cannot compare object files as stage 2 was deleted. ; \
	  exit 0 ; \
	fi; \
	: $(MAKE); $(stage); \
	rm -f .bad_compare ; \
	echo Comparing stages 2 and 3 ; \
	cd stage3-gcc; \
	files=`find . -name "*$(objext)" -print` ; \
	cd .. ; \
	for file in $${files} ; do \
	  f1=$$r/stage2-gcc/$$file; f2=$$r/stage3-gcc/$$file; \
	  $(do-compare) > /dev/null 2>&1; \
	  if test $$? -eq 1; then \
	    case $$file in \
	      ./cc*-checksum$(objext) | ./libgcc/* ) \
	        echo warning: $$file differs ;; \
	      *) \
	        echo $$file differs >> .bad_compare ;; \
	    esac ; \
	  fi ; \
	done ; \
	if [ -f .bad_compare ]; then \
	  echo "Bootstrap comparison failure!"; \
	  cat .bad_compare; \
	  exit 1; \
	else \
	  echo Comparison successful.; \
	fi ; \
	$(STAMP) compare
	if $(LEAN); then \
	  rm -rf stage2-*; \
	  $(STAMP) stage2-lean; \
	fi



.PHONY: bootstrap bootstrap-lean
bootstrap:
	echo stage3 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stage3-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target

bootstrap-lean:
	echo stage3 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) LEAN=: stage3-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target


# Rules to wipe a stage and all the following ones, also used for cleanstrap
distclean-stage2:: distclean-stage3 
.PHONY: distclean-stage3
distclean-stage3::
	@: $(MAKE); $(stage)
	@test "`cat stage_last`" != stage3 || rm -f stage_last
	rm -rf stage3-* compare 


.PHONY: cleanstrap
cleanstrap: do-distclean local-clean
	echo stage3 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stage3-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target



.PHONY: stageb3g2-start stageb3g2-end

stageb3g2-start::
	@: $(MAKE); $(stage); \
	echo stageb3g2 > stage_current ; \
	echo stageb3g2 > stage_last; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)
	@cd $(HOST_SUBDIR); [ -d stageb3g2-gcc ] || \
	  mkdir stageb3g2-gcc; \
	mv stageb3g2-gcc gcc  ; \
	mv stageb2g0-gcc prev-gcc || test -f stageb2g0-lean 
	@cd $(HOST_SUBDIR); [ -d stageb3g2-gmp ] || \
	  mkdir stageb3g2-gmp; \
	mv stageb3g2-gmp gmp  ; \
	mv stageb2g0-gmp prev-gmp || test -f stageb2g0-lean 
	@cd $(HOST_SUBDIR); [ -d stageb3g2-mpfr ] || \
	  mkdir stageb3g2-mpfr; \
	mv stageb3g2-mpfr mpfr  ; \
	mv stageb2g0-mpfr prev-mpfr || test -f stageb2g0-lean 
	@cd $(HOST_SUBDIR); [ -d stageb3g2-intl ] || \
	  mkdir stageb3g2-intl; \
	mv stageb3g2-intl intl  ; \
	mv stageb2g0-intl prev-intl || test -f stageb2g0-lean 
	@cd $(HOST_SUBDIR); [ -d stageb3g2-libcpp ] || \
	  mkdir stageb3g2-libcpp; \
	mv stageb3g2-libcpp libcpp  ; \
	mv stageb2g0-libcpp prev-libcpp || test -f stageb2g0-lean 
	@cd $(HOST_SUBDIR); [ -d stageb3g2-libdecnumber ] || \
	  mkdir stageb3g2-libdecnumber; \
	mv stageb3g2-libdecnumber libdecnumber  ; \
	mv stageb2g0-libdecnumber prev-libdecnumber || test -f stageb2g0-lean 
	@cd $(HOST_SUBDIR); [ -d stageb3g2-libiberty ] || \
	  mkdir stageb3g2-libiberty; \
	mv stageb3g2-libiberty libiberty  ; \
	mv stageb2g0-libiberty prev-libiberty || test -f stageb2g0-lean 
	@[ -d stageb3g2-$(TARGET_SUBDIR) ] || \
	  mkdir stageb3g2-$(TARGET_SUBDIR); \
	mv stageb3g2-$(TARGET_SUBDIR) $(TARGET_SUBDIR)  ; \
	mv stageb2g0-$(TARGET_SUBDIR) prev-$(TARGET_SUBDIR) || test -f stageb2g0-lean 

stageb3g2-end:: 
	@if test -d $(HOST_SUBDIR)/gcc ; then \
	  cd $(HOST_SUBDIR); mv gcc stageb3g2-gcc ; \
	  mv prev-gcc stageb2g0-gcc ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/gmp ; then \
	  cd $(HOST_SUBDIR); mv gmp stageb3g2-gmp ; \
	  mv prev-gmp stageb2g0-gmp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/mpfr ; then \
	  cd $(HOST_SUBDIR); mv mpfr stageb3g2-mpfr ; \
	  mv prev-mpfr stageb2g0-mpfr ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/intl ; then \
	  cd $(HOST_SUBDIR); mv intl stageb3g2-intl ; \
	  mv prev-intl stageb2g0-intl ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libcpp ; then \
	  cd $(HOST_SUBDIR); mv libcpp stageb3g2-libcpp ; \
	  mv prev-libcpp stageb2g0-libcpp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libdecnumber ; then \
	  cd $(HOST_SUBDIR); mv libdecnumber stageb3g2-libdecnumber ; \
	  mv prev-libdecnumber stageb2g0-libdecnumber ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libiberty ; then \
	  cd $(HOST_SUBDIR); mv libiberty stageb3g2-libiberty ; \
	  mv prev-libiberty stageb2g0-libiberty ; :  ; \
	fi
	@if test -d $(TARGET_SUBDIR) ; then \
	  mv $(TARGET_SUBDIR) stageb3g2-$(TARGET_SUBDIR)  ; \
	  mv prev-$(TARGET_SUBDIR) stageb2g0-$(TARGET_SUBDIR) ; :  ; \
	fi
	rm -f stage_current

# Bubble a bug fix through all the stages up to stage b3g2.  They are
# remade, but not reconfigured.  The next stage (if any) will not be
# reconfigured either.
.PHONY: stageb3g2-bubble
stageb3g2-bubble:: stageb2g0-bubble
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stageb3g2-lean || test -f stageb2g0-lean  ; then \
	  echo Skipping rebuild of stageb3g2 ; \
	else \
	  $(MAKE) stageb3g2-start; \
	  if $(LEAN); then \
	    rm -rf stage1-* ; \
	    $(STAMP) stage1-lean ; \
	  fi; \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-stageb3g2; \
	fi
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) compare-debug

.PHONY: all-stageb3g2 clean-stageb3g2
do-clean: clean-stageb3g2

# FIXME: Will not need to be conditional when toplevel bootstrap is the
# only possibility, but now it conflicts with no-bootstrap rules

compare-debug:
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stageb2g0-lean; then \
	  echo Cannot compare object files as stage b2g0 was deleted. ; \
	  exit 0 ; \
	fi; \
	: $(MAKE); $(stage); \
	rm -f .bad_compare ; \
	echo Comparing stages b2g0 and b3g2 ; \
	cd stageb3g2-gcc; \
	files=`find . -name "*$(objext)" -print` ; \
	cd .. ; \
	for file in $${files} ; do \
	  f1=$$r/stageb2g0-gcc/$$file; f2=$$r/stageb3g2-gcc/$$file; \
	  $(do-compare-debug) > /dev/null 2>&1; \
	  if test $$? -eq 1; then \
	    case $$file in \
	      ./cc*-checksum$(objext) | ./libgcc/* ) \
	        echo warning: $$file differs ;; \
	      *) \
	        echo $$file differs >> .bad_compare ;; \
	    esac ; \
	  fi ; \
	done ; \
	if [ -f .bad_compare ]; then \
	  echo "Bootstrap comparison failure!"; \
	  cat .bad_compare; \
	  exit 1; \
	else \
	  echo Comparison successful.; \
	fi ; \
	$(STAMP) compare-debug
	if $(LEAN); then \
	  rm -rf stageb2g0-*; \
	  $(STAMP) stageb2g0-lean; \
	fi



.PHONY: bootstrap-debug bootstrap-debug-lean
bootstrap-debug:
	echo stageb3g2 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stageb3g2-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target

bootstrap-debug-lean:
	echo stageb3g2 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) LEAN=: stageb3g2-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target


# Rules to wipe a stage and all the following ones, also used for cleanstrap
distclean-stageb2g0:: distclean-stageb3g2 
.PHONY: distclean-stageb3g2
distclean-stageb3g2::
	@: $(MAKE); $(stage)
	@test "`cat stage_last`" != stageb3g2 || rm -f stage_last
	rm -rf stageb3g2-* compare-debug 


.PHONY: cleanstrap-debug
cleanstrap-debug: do-distclean local-clean
	echo stageb3g2 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stageb3g2-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target



.PHONY: stage4-start stage4-end

stage4-start::
	@: $(MAKE); $(stage); \
	echo stage4 > stage_current ; \
	echo stage4 > stage_last; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)
	@cd $(HOST_SUBDIR); [ -d stage4-gcc ] || \
	  mkdir stage4-gcc; \
	mv stage4-gcc gcc  ; \
	mv stage3-gcc prev-gcc || test -f stage3-lean 
	@cd $(HOST_SUBDIR); [ -d stage4-gmp ] || \
	  mkdir stage4-gmp; \
	mv stage4-gmp gmp  ; \
	mv stage3-gmp prev-gmp || test -f stage3-lean 
	@cd $(HOST_SUBDIR); [ -d stage4-mpfr ] || \
	  mkdir stage4-mpfr; \
	mv stage4-mpfr mpfr  ; \
	mv stage3-mpfr prev-mpfr || test -f stage3-lean 
	@cd $(HOST_SUBDIR); [ -d stage4-intl ] || \
	  mkdir stage4-intl; \
	mv stage4-intl intl  ; \
	mv stage3-intl prev-intl || test -f stage3-lean 
	@cd $(HOST_SUBDIR); [ -d stage4-libcpp ] || \
	  mkdir stage4-libcpp; \
	mv stage4-libcpp libcpp  ; \
	mv stage3-libcpp prev-libcpp || test -f stage3-lean 
	@cd $(HOST_SUBDIR); [ -d stage4-libdecnumber ] || \
	  mkdir stage4-libdecnumber; \
	mv stage4-libdecnumber libdecnumber  ; \
	mv stage3-libdecnumber prev-libdecnumber || test -f stage3-lean 
	@cd $(HOST_SUBDIR); [ -d stage4-libiberty ] || \
	  mkdir stage4-libiberty; \
	mv stage4-libiberty libiberty  ; \
	mv stage3-libiberty prev-libiberty || test -f stage3-lean 
	@[ -d stage4-$(TARGET_SUBDIR) ] || \
	  mkdir stage4-$(TARGET_SUBDIR); \
	mv stage4-$(TARGET_SUBDIR) $(TARGET_SUBDIR)  ; \
	mv stage3-$(TARGET_SUBDIR) prev-$(TARGET_SUBDIR) || test -f stage3-lean 

stage4-end:: 
	@if test -d $(HOST_SUBDIR)/gcc ; then \
	  cd $(HOST_SUBDIR); mv gcc stage4-gcc ; \
	  mv prev-gcc stage3-gcc ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/gmp ; then \
	  cd $(HOST_SUBDIR); mv gmp stage4-gmp ; \
	  mv prev-gmp stage3-gmp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/mpfr ; then \
	  cd $(HOST_SUBDIR); mv mpfr stage4-mpfr ; \
	  mv prev-mpfr stage3-mpfr ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/intl ; then \
	  cd $(HOST_SUBDIR); mv intl stage4-intl ; \
	  mv prev-intl stage3-intl ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libcpp ; then \
	  cd $(HOST_SUBDIR); mv libcpp stage4-libcpp ; \
	  mv prev-libcpp stage3-libcpp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libdecnumber ; then \
	  cd $(HOST_SUBDIR); mv libdecnumber stage4-libdecnumber ; \
	  mv prev-libdecnumber stage3-libdecnumber ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libiberty ; then \
	  cd $(HOST_SUBDIR); mv libiberty stage4-libiberty ; \
	  mv prev-libiberty stage3-libiberty ; :  ; \
	fi
	@if test -d $(TARGET_SUBDIR) ; then \
	  mv $(TARGET_SUBDIR) stage4-$(TARGET_SUBDIR)  ; \
	  mv prev-$(TARGET_SUBDIR) stage3-$(TARGET_SUBDIR) ; :  ; \
	fi
	rm -f stage_current

# Bubble a bug fix through all the stages up to stage 4.  They are
# remade, but not reconfigured.  The next stage (if any) will not be
# reconfigured either.
.PHONY: stage4-bubble
stage4-bubble:: stage3-bubble
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stage4-lean || test -f stage3-lean  ; then \
	  echo Skipping rebuild of stage4 ; \
	else \
	  $(MAKE) stage4-start; \
	  if $(LEAN); then \
	    rm -rf stage2-* ; \
	    $(STAMP) stage2-lean ; \
	  fi; \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-stage4; \
	fi
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) compare3

.PHONY: all-stage4 clean-stage4
do-clean: clean-stage4

# FIXME: Will not need to be conditional when toplevel bootstrap is the
# only possibility, but now it conflicts with no-bootstrap rules

compare3:
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stage3-lean; then \
	  echo Cannot compare object files as stage 3 was deleted. ; \
	  exit 0 ; \
	fi; \
	: $(MAKE); $(stage); \
	rm -f .bad_compare ; \
	echo Comparing stages 3 and 4 ; \
	cd stage4-gcc; \
	files=`find . -name "*$(objext)" -print` ; \
	cd .. ; \
	for file in $${files} ; do \
	  f1=$$r/stage3-gcc/$$file; f2=$$r/stage4-gcc/$$file; \
	  $(do-compare3) > /dev/null 2>&1; \
	  if test $$? -eq 1; then \
	    case $$file in \
	      ./cc*-checksum$(objext) | ./libgcc/* ) \
	        echo warning: $$file differs ;; \
	      *) \
	        echo $$file differs >> .bad_compare ;; \
	    esac ; \
	  fi ; \
	done ; \
	if [ -f .bad_compare ]; then \
	  echo "Bootstrap comparison failure!"; \
	  cat .bad_compare; \
	  exit 1; \
	else \
	  echo Comparison successful.; \
	fi ; \
	$(STAMP) compare3
	if $(LEAN); then \
	  rm -rf stage3-*; \
	  $(STAMP) stage3-lean; \
	fi



.PHONY: bootstrap4 bootstrap4-lean
bootstrap4:
	echo stage4 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stage4-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target

bootstrap4-lean:
	echo stage4 > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) LEAN=: stage4-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target


# Rules to wipe a stage and all the following ones, also used for cleanstrap
distclean-stage3:: distclean-stage4 
.PHONY: distclean-stage4
distclean-stage4::
	@: $(MAKE); $(stage)
	@test "`cat stage_last`" != stage4 || rm -f stage_last
	rm -rf stage4-* compare3 




.PHONY: stageprofile-start stageprofile-end

stageprofile-start::
	@: $(MAKE); $(stage); \
	echo stageprofile > stage_current ; \
	echo stageprofile > stage_last; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)
	@cd $(HOST_SUBDIR); [ -d stageprofile-gcc ] || \
	  mkdir stageprofile-gcc; \
	mv stageprofile-gcc gcc  ; \
	mv stage1-gcc prev-gcc || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageprofile-gmp ] || \
	  mkdir stageprofile-gmp; \
	mv stageprofile-gmp gmp  ; \
	mv stage1-gmp prev-gmp || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageprofile-mpfr ] || \
	  mkdir stageprofile-mpfr; \
	mv stageprofile-mpfr mpfr  ; \
	mv stage1-mpfr prev-mpfr || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageprofile-intl ] || \
	  mkdir stageprofile-intl; \
	mv stageprofile-intl intl  ; \
	mv stage1-intl prev-intl || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageprofile-libcpp ] || \
	  mkdir stageprofile-libcpp; \
	mv stageprofile-libcpp libcpp  ; \
	mv stage1-libcpp prev-libcpp || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageprofile-libdecnumber ] || \
	  mkdir stageprofile-libdecnumber; \
	mv stageprofile-libdecnumber libdecnumber  ; \
	mv stage1-libdecnumber prev-libdecnumber || test -f stage1-lean 
	@cd $(HOST_SUBDIR); [ -d stageprofile-libiberty ] || \
	  mkdir stageprofile-libiberty; \
	mv stageprofile-libiberty libiberty  ; \
	mv stage1-libiberty prev-libiberty || test -f stage1-lean 
	@[ -d stageprofile-$(TARGET_SUBDIR) ] || \
	  mkdir stageprofile-$(TARGET_SUBDIR); \
	mv stageprofile-$(TARGET_SUBDIR) $(TARGET_SUBDIR)  ; \
	mv stage1-$(TARGET_SUBDIR) prev-$(TARGET_SUBDIR) || test -f stage1-lean 

stageprofile-end:: 
	@if test -d $(HOST_SUBDIR)/gcc ; then \
	  cd $(HOST_SUBDIR); mv gcc stageprofile-gcc ; \
	  mv prev-gcc stage1-gcc ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/gmp ; then \
	  cd $(HOST_SUBDIR); mv gmp stageprofile-gmp ; \
	  mv prev-gmp stage1-gmp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/mpfr ; then \
	  cd $(HOST_SUBDIR); mv mpfr stageprofile-mpfr ; \
	  mv prev-mpfr stage1-mpfr ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/intl ; then \
	  cd $(HOST_SUBDIR); mv intl stageprofile-intl ; \
	  mv prev-intl stage1-intl ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libcpp ; then \
	  cd $(HOST_SUBDIR); mv libcpp stageprofile-libcpp ; \
	  mv prev-libcpp stage1-libcpp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libdecnumber ; then \
	  cd $(HOST_SUBDIR); mv libdecnumber stageprofile-libdecnumber ; \
	  mv prev-libdecnumber stage1-libdecnumber ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libiberty ; then \
	  cd $(HOST_SUBDIR); mv libiberty stageprofile-libiberty ; \
	  mv prev-libiberty stage1-libiberty ; :  ; \
	fi
	@if test -d $(TARGET_SUBDIR) ; then \
	  mv $(TARGET_SUBDIR) stageprofile-$(TARGET_SUBDIR)  ; \
	  mv prev-$(TARGET_SUBDIR) stage1-$(TARGET_SUBDIR) ; :  ; \
	fi
	rm -f stage_current

# Bubble a bug fix through all the stages up to stage profile.  They are
# remade, but not reconfigured.  The next stage (if any) will not be
# reconfigured either.
.PHONY: stageprofile-bubble
stageprofile-bubble:: stage1-bubble
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stageprofile-lean || test -f stage1-lean  ; then \
	  echo Skipping rebuild of stageprofile ; \
	else \
	  $(MAKE) stageprofile-start; \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-stageprofile; \
	fi

.PHONY: all-stageprofile clean-stageprofile
do-clean: clean-stageprofile

# FIXME: Will not need to be conditional when toplevel bootstrap is the
# only possibility, but now it conflicts with no-bootstrap rules




# Rules to wipe a stage and all the following ones, also used for cleanstrap
distclean-stage1:: distclean-stageprofile 
.PHONY: distclean-stageprofile
distclean-stageprofile::
	@: $(MAKE); $(stage)
	@test "`cat stage_last`" != stageprofile || rm -f stage_last
	rm -rf stageprofile-* 




.PHONY: stagefeedback-start stagefeedback-end

stagefeedback-start::
	@: $(MAKE); $(stage); \
	echo stagefeedback > stage_current ; \
	echo stagefeedback > stage_last; \
	$(SHELL) $(srcdir)/mkinstalldirs $(HOST_SUBDIR)
	@cd $(HOST_SUBDIR); [ -d stagefeedback-gcc ] || \
	  mkdir stagefeedback-gcc; \
	mv stagefeedback-gcc gcc  ; \
	mv stageprofile-gcc prev-gcc || test -f stageprofile-lean 
	@cd $(HOST_SUBDIR); [ -d stagefeedback-gmp ] || \
	  mkdir stagefeedback-gmp; \
	mv stagefeedback-gmp gmp  ; \
	mv stageprofile-gmp prev-gmp || test -f stageprofile-lean 
	@cd $(HOST_SUBDIR); [ -d stagefeedback-mpfr ] || \
	  mkdir stagefeedback-mpfr; \
	mv stagefeedback-mpfr mpfr  ; \
	mv stageprofile-mpfr prev-mpfr || test -f stageprofile-lean 
	@cd $(HOST_SUBDIR); [ -d stagefeedback-intl ] || \
	  mkdir stagefeedback-intl; \
	mv stagefeedback-intl intl  ; \
	mv stageprofile-intl prev-intl || test -f stageprofile-lean 
	@cd $(HOST_SUBDIR); [ -d stagefeedback-libcpp ] || \
	  mkdir stagefeedback-libcpp; \
	mv stagefeedback-libcpp libcpp  ; \
	mv stageprofile-libcpp prev-libcpp || test -f stageprofile-lean 
	@cd $(HOST_SUBDIR); [ -d stagefeedback-libdecnumber ] || \
	  mkdir stagefeedback-libdecnumber; \
	mv stagefeedback-libdecnumber libdecnumber  ; \
	mv stageprofile-libdecnumber prev-libdecnumber || test -f stageprofile-lean 
	@cd $(HOST_SUBDIR); [ -d stagefeedback-libiberty ] || \
	  mkdir stagefeedback-libiberty; \
	mv stagefeedback-libiberty libiberty  ; \
	mv stageprofile-libiberty prev-libiberty || test -f stageprofile-lean 
	@[ -d stagefeedback-$(TARGET_SUBDIR) ] || \
	  mkdir stagefeedback-$(TARGET_SUBDIR); \
	mv stagefeedback-$(TARGET_SUBDIR) $(TARGET_SUBDIR)  ; \
	mv stageprofile-$(TARGET_SUBDIR) prev-$(TARGET_SUBDIR) || test -f stageprofile-lean 

stagefeedback-end:: 
	@if test -d $(HOST_SUBDIR)/gcc ; then \
	  cd $(HOST_SUBDIR); mv gcc stagefeedback-gcc ; \
	  mv prev-gcc stageprofile-gcc ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/gmp ; then \
	  cd $(HOST_SUBDIR); mv gmp stagefeedback-gmp ; \
	  mv prev-gmp stageprofile-gmp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/mpfr ; then \
	  cd $(HOST_SUBDIR); mv mpfr stagefeedback-mpfr ; \
	  mv prev-mpfr stageprofile-mpfr ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/intl ; then \
	  cd $(HOST_SUBDIR); mv intl stagefeedback-intl ; \
	  mv prev-intl stageprofile-intl ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libcpp ; then \
	  cd $(HOST_SUBDIR); mv libcpp stagefeedback-libcpp ; \
	  mv prev-libcpp stageprofile-libcpp ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libdecnumber ; then \
	  cd $(HOST_SUBDIR); mv libdecnumber stagefeedback-libdecnumber ; \
	  mv prev-libdecnumber stageprofile-libdecnumber ; :  ; \
	fi
	@if test -d $(HOST_SUBDIR)/libiberty ; then \
	  cd $(HOST_SUBDIR); mv libiberty stagefeedback-libiberty ; \
	  mv prev-libiberty stageprofile-libiberty ; :  ; \
	fi
	@if test -d $(TARGET_SUBDIR) ; then \
	  mv $(TARGET_SUBDIR) stagefeedback-$(TARGET_SUBDIR)  ; \
	  mv prev-$(TARGET_SUBDIR) stageprofile-$(TARGET_SUBDIR) ; :  ; \
	fi
	rm -f stage_current

# Bubble a bug fix through all the stages up to stage feedback.  They are
# remade, but not reconfigured.  The next stage (if any) will not be
# reconfigured either.
.PHONY: stagefeedback-bubble
stagefeedback-bubble:: stageprofile-bubble
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	if test -f stagefeedback-lean || test -f stageprofile-lean  ; then \
	  echo Skipping rebuild of stagefeedback ; \
	else \
	  $(MAKE) stagefeedback-start; \
	  $(MAKE) $(RECURSE_FLAGS_TO_PASS) all-stagefeedback; \
	fi

.PHONY: all-stagefeedback clean-stagefeedback
do-clean: clean-stagefeedback

# FIXME: Will not need to be conditional when toplevel bootstrap is the
# only possibility, but now it conflicts with no-bootstrap rules



.PHONY: profiledbootstrap profiledbootstrap-lean
profiledbootstrap:
	echo stagefeedback > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stagefeedback-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target

profiledbootstrap-lean:
	echo stagefeedback > stage_final
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) LEAN=: stagefeedback-bubble
	@: $(MAKE); $(unstage)
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(TARGET_FLAGS_TO_PASS) all-host all-target


# Rules to wipe a stage and all the following ones, also used for cleanstrap
distclean-stageprofile:: distclean-stagefeedback 
.PHONY: distclean-stagefeedback
distclean-stagefeedback::
	@: $(MAKE); $(stage)
	@test "`cat stage_last`" != stagefeedback || rm -f stage_last
	rm -rf stagefeedback-* 





stageprofile-end::
	$(MAKE) distclean-stagefeedback

stagefeedback-start::
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	for i in prev-*; do \
	  j=`echo $$i | sed s/^prev-//` ; \
	  cd $$r/$$i && \
	  { find . -type d | sort | sed 's,.*,$(SHELL) '"$$s"'/mkinstalldirs "../'$$j'/&",' | $(SHELL) ; } && \
	  { find . -name '*.*da' | sed 's,.*,$(LN) -f "&" "../'$$j'/&",' | $(SHELL) ; } ; \
	done

do-distclean: distclean-stage1

# Provide a GCC build when we're building target libraries.  This does
# not work as a dependency, just as the minimum necessary to avoid errors.
stage_last:
	@r=`${PWD_COMMAND}`; export r; \
	s=`cd $(srcdir); ${PWD_COMMAND}`; export s; \
	$(MAKE) $(RECURSE_FLAGS_TO_PASS) stage1-bubble

# Same as unstage, but not phony and defaulting to stage1-start.  We place
# it in the dependency so that for example `make -j3 all-gcc' works.
stage_current:
	@if test -f stage_last; then $(unstage); else $(MAKE) stage1-start; fi

.PHONY: restrap
restrap::
	@: $(MAKE); $(stage)
	rm -rf stage1-$(TARGET_SUBDIR) stage2-* stageb2g0-* stage3-* stageb3g2-* stage4-* stageprofile-* stagefeedback-* 
restrap:: all

# --------------------------------------
# Dependencies between different modules
# --------------------------------------

# Generic dependencies for target modules on host stuff, especially gcc
configure-target-libstdc++-v3: stage_last
configure-target-libmudflap: stage_last
configure-target-libssp: stage_last
configure-target-newlib: stage_last
configure-stage1-target-libgcc: maybe-all-stage1-gcc
configure-stage2-target-libgcc: maybe-all-stage2-gcc
configure-stageb2g0-target-libgcc: maybe-all-stageb2g0-gcc
configure-stage3-target-libgcc: maybe-all-stage3-gcc
configure-stageb3g2-target-libgcc: maybe-all-stageb3g2-gcc
configure-stage4-target-libgcc: maybe-all-stage4-gcc
configure-stageprofile-target-libgcc: maybe-all-stageprofile-gcc
configure-stagefeedback-target-libgcc: maybe-all-stagefeedback-gcc
configure-target-libgfortran: stage_last
configure-target-libobjc: stage_last
configure-target-libtermcap: stage_last
configure-target-winsup: stage_last
configure-target-libgloss: stage_last
configure-target-libiberty: stage_last
configure-target-gperf: stage_last
configure-target-examples: stage_last
configure-target-libffi: stage_last
configure-target-libjava: stage_last
configure-target-zlib: stage_last
configure-target-boehm-gc: stage_last
configure-target-qthreads: stage_last
configure-target-rda: stage_last
configure-target-libada: stage_last
configure-target-libgomp: stage_last



# There are two types of dependencies here: 'hard' dependencies, where one
# module simply won't build without the other; and 'soft' dependencies, where
# if the depended-on module is missing, the depending module will do without
# or find a substitute somewhere (perhaps installed).  Soft dependencies
# are made here to depend on a 'maybe-' target.  If you're not sure,
# it's safer to use a soft dependency.






# With all the machinery above in place, it is pretty easy to generate
# dependencies.  Host dependencies are a bit more complex because we have
# to check for bootstrap/prebootstrap dependencies.  To resolve
# prebootstrap dependencies, prebootstrap modules are gathered in
# a hash table.
all-build-bison: maybe-all-build-texinfo
all-build-byacc: maybe-all-build-texinfo
all-build-flex: maybe-all-build-texinfo
all-build-flex: maybe-all-build-bison
all-build-flex: maybe-all-build-byacc
all-build-flex: maybe-all-build-m4
all-build-libiberty: maybe-all-build-texinfo
all-build-m4: maybe-all-build-texinfo
all-build-fixincludes: maybe-all-build-libiberty
configure-gcc: maybe-configure-intl

configure-stage1-gcc: maybe-configure-stage1-intl
configure-stage2-gcc: maybe-configure-stage2-intl
configure-stageb2g0-gcc: maybe-configure-stageb2g0-intl
configure-stage3-gcc: maybe-configure-stage3-intl
configure-stageb3g2-gcc: maybe-configure-stageb3g2-intl
configure-stage4-gcc: maybe-configure-stage4-intl
configure-stageprofile-gcc: maybe-configure-stageprofile-intl
configure-stagefeedback-gcc: maybe-configure-stagefeedback-intl
configure-gcc: maybe-all-binutils

configure-stage1-gcc: maybe-all-stage1-binutils
configure-stage2-gcc: maybe-all-stage2-binutils
configure-stageb2g0-gcc: maybe-all-stageb2g0-binutils
configure-stage3-gcc: maybe-all-stage3-binutils
configure-stageb3g2-gcc: maybe-all-stageb3g2-binutils
configure-stage4-gcc: maybe-all-stage4-binutils
configure-stageprofile-gcc: maybe-all-stageprofile-binutils
configure-stagefeedback-gcc: maybe-all-stagefeedback-binutils
configure-gcc: maybe-all-gas

configure-stage1-gcc: maybe-all-stage1-gas
configure-stage2-gcc: maybe-all-stage2-gas
configure-stageb2g0-gcc: maybe-all-stageb2g0-gas
configure-stage3-gcc: maybe-all-stage3-gas
configure-stageb3g2-gcc: maybe-all-stageb3g2-gas
configure-stage4-gcc: maybe-all-stage4-gas
configure-stageprofile-gcc: maybe-all-stageprofile-gas
configure-stagefeedback-gcc: maybe-all-stagefeedback-gas
configure-gcc: maybe-all-ld

configure-stage1-gcc: maybe-all-stage1-ld
configure-stage2-gcc: maybe-all-stage2-ld
configure-stageb2g0-gcc: maybe-all-stageb2g0-ld
configure-stage3-gcc: maybe-all-stage3-ld
configure-stageb3g2-gcc: maybe-all-stageb3g2-ld
configure-stage4-gcc: maybe-all-stage4-ld
configure-stageprofile-gcc: maybe-all-stageprofile-ld
configure-stagefeedback-gcc: maybe-all-stagefeedback-ld
configure-gcc: maybe-all-gold

configure-stage1-gcc: maybe-all-stage1-gold
configure-stage2-gcc: maybe-all-stage2-gold
configure-stageb2g0-gcc: maybe-all-stageb2g0-gold
configure-stage3-gcc: maybe-all-stage3-gold
configure-stageb3g2-gcc: maybe-all-stageb3g2-gold
configure-stage4-gcc: maybe-all-stage4-gold
configure-stageprofile-gcc: maybe-all-stageprofile-gold
configure-stagefeedback-gcc: maybe-all-stagefeedback-gold
all-gcc: all-libiberty

all-stage1-gcc: all-stage1-libiberty
all-stage2-gcc: all-stage2-libiberty
all-stageb2g0-gcc: all-stageb2g0-libiberty
all-stage3-gcc: all-stage3-libiberty
all-stageb3g2-gcc: all-stageb3g2-libiberty
all-stage4-gcc: all-stage4-libiberty
all-stageprofile-gcc: all-stageprofile-libiberty
all-stagefeedback-gcc: all-stagefeedback-libiberty
all-gcc: maybe-all-gmp

all-stage1-gcc: maybe-all-stage1-gmp
all-stage2-gcc: maybe-all-stage2-gmp
all-stageb2g0-gcc: maybe-all-stageb2g0-gmp
all-stage3-gcc: maybe-all-stage3-gmp
all-stageb3g2-gcc: maybe-all-stageb3g2-gmp
all-stage4-gcc: maybe-all-stage4-gmp
all-stageprofile-gcc: maybe-all-stageprofile-gmp
all-stagefeedback-gcc: maybe-all-stagefeedback-gmp
all-gcc: maybe-all-intl

all-stage1-gcc: maybe-all-stage1-intl
all-stage2-gcc: maybe-all-stage2-intl
all-stageb2g0-gcc: maybe-all-stageb2g0-intl
all-stage3-gcc: maybe-all-stage3-intl
all-stageb3g2-gcc: maybe-all-stageb3g2-intl
all-stage4-gcc: maybe-all-stage4-intl
all-stageprofile-gcc: maybe-all-stageprofile-intl
all-stagefeedback-gcc: maybe-all-stagefeedback-intl
all-gcc: maybe-all-mpfr

all-stage1-gcc: maybe-all-stage1-mpfr
all-stage2-gcc: maybe-all-stage2-mpfr
all-stageb2g0-gcc: maybe-all-stageb2g0-mpfr
all-stage3-gcc: maybe-all-stage3-mpfr
all-stageb3g2-gcc: maybe-all-stageb3g2-mpfr
all-stage4-gcc: maybe-all-stage4-mpfr
all-stageprofile-gcc: maybe-all-stageprofile-mpfr
all-stagefeedback-gcc: maybe-all-stagefeedback-mpfr
all-gcc: maybe-all-ppl

all-stage1-gcc: maybe-all-stage1-ppl
all-stage2-gcc: maybe-all-stage2-ppl
all-stageb2g0-gcc: maybe-all-stageb2g0-ppl
all-stage3-gcc: maybe-all-stage3-ppl
all-stageb3g2-gcc: maybe-all-stageb3g2-ppl
all-stage4-gcc: maybe-all-stage4-ppl
all-stageprofile-gcc: maybe-all-stageprofile-ppl
all-stagefeedback-gcc: maybe-all-stagefeedback-ppl
all-gcc: maybe-all-cloog

all-stage1-gcc: maybe-all-stage1-cloog
all-stage2-gcc: maybe-all-stage2-cloog
all-stageb2g0-gcc: maybe-all-stageb2g0-cloog
all-stage3-gcc: maybe-all-stage3-cloog
all-stageb3g2-gcc: maybe-all-stageb3g2-cloog
all-stage4-gcc: maybe-all-stage4-cloog
all-stageprofile-gcc: maybe-all-stageprofile-cloog
all-stagefeedback-gcc: maybe-all-stagefeedback-cloog
all-gcc: maybe-all-build-texinfo

all-stage1-gcc: maybe-all-build-texinfo
all-stage2-gcc: maybe-all-build-texinfo
all-stageb2g0-gcc: maybe-all-build-texinfo
all-stage3-gcc: maybe-all-build-texinfo
all-stageb3g2-gcc: maybe-all-build-texinfo
all-stage4-gcc: maybe-all-build-texinfo
all-stageprofile-gcc: maybe-all-build-texinfo
all-stagefeedback-gcc: maybe-all-build-texinfo
all-gcc: maybe-all-build-bison

all-stage1-gcc: maybe-all-build-bison
all-stage2-gcc: maybe-all-build-bison
all-stageb2g0-gcc: maybe-all-build-bison
all-stage3-gcc: maybe-all-build-bison
all-stageb3g2-gcc: maybe-all-build-bison
all-stage4-gcc: maybe-all-build-bison
all-stageprofile-gcc: maybe-all-build-bison
all-stagefeedback-gcc: maybe-all-build-bison
all-gcc: maybe-all-build-byacc

all-stage1-gcc: maybe-all-build-byacc
all-stage2-gcc: maybe-all-build-byacc
all-stageb2g0-gcc: maybe-all-build-byacc
all-stage3-gcc: maybe-all-build-byacc
all-stageb3g2-gcc: maybe-all-build-byacc
all-stage4-gcc: maybe-all-build-byacc
all-stageprofile-gcc: maybe-all-build-byacc
all-stagefeedback-gcc: maybe-all-build-byacc
all-gcc: maybe-all-build-flex

all-stage1-gcc: maybe-all-build-flex
all-stage2-gcc: maybe-all-build-flex
all-stageb2g0-gcc: maybe-all-build-flex
all-stage3-gcc: maybe-all-build-flex
all-stageb3g2-gcc: maybe-all-build-flex
all-stage4-gcc: maybe-all-build-flex
all-stageprofile-gcc: maybe-all-build-flex
all-stagefeedback-gcc: maybe-all-build-flex
all-gcc: maybe-all-build-libiberty

all-stage1-gcc: maybe-all-build-libiberty
all-stage2-gcc: maybe-all-build-libiberty
all-stageb2g0-gcc: maybe-all-build-libiberty
all-stage3-gcc: maybe-all-build-libiberty
all-stageb3g2-gcc: maybe-all-build-libiberty
all-stage4-gcc: maybe-all-build-libiberty
all-stageprofile-gcc: maybe-all-build-libiberty
all-stagefeedback-gcc: maybe-all-build-libiberty
all-gcc: maybe-all-build-fixincludes

all-stage1-gcc: maybe-all-build-fixincludes
all-stage2-gcc: maybe-all-build-fixincludes
all-stageb2g0-gcc: maybe-all-build-fixincludes
all-stage3-gcc: maybe-all-build-fixincludes
all-stageb3g2-gcc: maybe-all-build-fixincludes
all-stage4-gcc: maybe-all-build-fixincludes
all-stageprofile-gcc: maybe-all-build-fixincludes
all-stagefeedback-gcc: maybe-all-build-fixincludes
all-gcc: maybe-all-zlib

all-stage1-gcc: maybe-all-stage1-zlib
all-stage2-gcc: maybe-all-stage2-zlib
all-stageb2g0-gcc: maybe-all-stageb2g0-zlib
all-stage3-gcc: maybe-all-stage3-zlib
all-stageb3g2-gcc: maybe-all-stageb3g2-zlib
all-stage4-gcc: maybe-all-stage4-zlib
all-stageprofile-gcc: maybe-all-stageprofile-zlib
all-stagefeedback-gcc: maybe-all-stagefeedback-zlib
all-gcc: all-libcpp

all-stage1-gcc: all-stage1-libcpp
all-stage2-gcc: all-stage2-libcpp
all-stageb2g0-gcc: all-stageb2g0-libcpp
all-stage3-gcc: all-stage3-libcpp
all-stageb3g2-gcc: all-stageb3g2-libcpp
all-stage4-gcc: all-stage4-libcpp
all-stageprofile-gcc: all-stageprofile-libcpp
all-stagefeedback-gcc: all-stagefeedback-libcpp
all-gcc: all-libdecnumber

all-stage1-gcc: all-stage1-libdecnumber
all-stage2-gcc: all-stage2-libdecnumber
all-stageb2g0-gcc: all-stageb2g0-libdecnumber
all-stage3-gcc: all-stage3-libdecnumber
all-stageb3g2-gcc: all-stageb3g2-libdecnumber
all-stage4-gcc: all-stage4-libdecnumber
all-stageprofile-gcc: all-stageprofile-libdecnumber
all-stagefeedback-gcc: all-stagefeedback-libdecnumber
all-gcc: maybe-all-libiberty

all-stage1-gcc: maybe-all-stage1-libiberty
all-stage2-gcc: maybe-all-stage2-libiberty
all-stageb2g0-gcc: maybe-all-stageb2g0-libiberty
all-stage3-gcc: maybe-all-stage3-libiberty
all-stageb3g2-gcc: maybe-all-stageb3g2-libiberty
all-stage4-gcc: maybe-all-stage4-libiberty
all-stageprofile-gcc: maybe-all-stageprofile-libiberty
all-stagefeedback-gcc: maybe-all-stagefeedback-libiberty
all-gcc: maybe-all-fixincludes
install-gcc: maybe-install-fixincludes
configure-libcpp: configure-libiberty

configure-stage1-libcpp: configure-stage1-libiberty
configure-stage2-libcpp: configure-stage2-libiberty
configure-stageb2g0-libcpp: configure-stageb2g0-libiberty
configure-stage3-libcpp: configure-stage3-libiberty
configure-stageb3g2-libcpp: configure-stageb3g2-libiberty
configure-stage4-libcpp: configure-stage4-libiberty
configure-stageprofile-libcpp: configure-stageprofile-libiberty
configure-stagefeedback-libcpp: configure-stagefeedback-libiberty
configure-libcpp: maybe-configure-intl

configure-stage1-libcpp: maybe-configure-stage1-intl
configure-stage2-libcpp: maybe-configure-stage2-intl
configure-stageb2g0-libcpp: maybe-configure-stageb2g0-intl
configure-stage3-libcpp: maybe-configure-stage3-intl
configure-stageb3g2-libcpp: maybe-configure-stageb3g2-intl
configure-stage4-libcpp: maybe-configure-stage4-intl
configure-stageprofile-libcpp: maybe-configure-stageprofile-intl
configure-stagefeedback-libcpp: maybe-configure-stagefeedback-intl
all-libcpp: all-libiberty

all-stage1-libcpp: all-stage1-libiberty
all-stage2-libcpp: all-stage2-libiberty
all-stageb2g0-libcpp: all-stageb2g0-libiberty
all-stage3-libcpp: all-stage3-libiberty
all-stageb3g2-libcpp: all-stageb3g2-libiberty
all-stage4-libcpp: all-stage4-libiberty
all-stageprofile-libcpp: all-stageprofile-libiberty
all-stagefeedback-libcpp: all-stagefeedback-libiberty
all-libcpp: maybe-all-intl

all-stage1-libcpp: maybe-all-stage1-intl
all-stage2-libcpp: maybe-all-stage2-intl
all-stageb2g0-libcpp: maybe-all-stageb2g0-intl
all-stage3-libcpp: maybe-all-stage3-intl
all-stageb3g2-libcpp: maybe-all-stageb3g2-intl
all-stage4-libcpp: maybe-all-stage4-intl
all-stageprofile-libcpp: maybe-all-stageprofile-intl
all-stagefeedback-libcpp: maybe-all-stagefeedback-intl
all-fixincludes: maybe-all-libiberty
all-gnattools: maybe-all-target-libada
configure-mpfr: maybe-all-gmp

configure-stage1-mpfr: maybe-all-stage1-gmp
configure-stage2-mpfr: maybe-all-stage2-gmp
configure-stageb2g0-mpfr: maybe-all-stageb2g0-gmp
configure-stage3-mpfr: maybe-all-stage3-gmp
configure-stageb3g2-mpfr: maybe-all-stageb3g2-gmp
configure-stage4-mpfr: maybe-all-stage4-gmp
configure-stageprofile-mpfr: maybe-all-stageprofile-gmp
configure-stagefeedback-mpfr: maybe-all-stagefeedback-gmp
configure-ppl: maybe-all-gmp

configure-stage1-ppl: maybe-all-stage1-gmp
configure-stage2-ppl: maybe-all-stage2-gmp
configure-stageb2g0-ppl: maybe-all-stageb2g0-gmp
configure-stage3-ppl: maybe-all-stage3-gmp
configure-stageb3g2-ppl: maybe-all-stageb3g2-gmp
configure-stage4-ppl: maybe-all-stage4-gmp
configure-stageprofile-ppl: maybe-all-stageprofile-gmp
configure-stagefeedback-ppl: maybe-all-stagefeedback-gmp
configure-ppl: maybe-all-mpfr

configure-stage1-ppl: maybe-all-stage1-mpfr
configure-stage2-ppl: maybe-all-stage2-mpfr
configure-stageb2g0-ppl: maybe-all-stageb2g0-mpfr
configure-stage3-ppl: maybe-all-stage3-mpfr
configure-stageb3g2-ppl: maybe-all-stageb3g2-mpfr
configure-stage4-ppl: maybe-all-stage4-mpfr
configure-stageprofile-ppl: maybe-all-stageprofile-mpfr
configure-stagefeedback-ppl: maybe-all-stagefeedback-mpfr
configure-cloog: maybe-all-ppl

configure-stage1-cloog: maybe-all-stage1-ppl
configure-stage2-cloog: maybe-all-stage2-ppl
configure-stageb2g0-cloog: maybe-all-stageb2g0-ppl
configure-stage3-cloog: maybe-all-stage3-ppl
configure-stageb3g2-cloog: maybe-all-stageb3g2-ppl
configure-stage4-cloog: maybe-all-stage4-ppl
configure-stageprofile-cloog: maybe-all-stageprofile-ppl
configure-stagefeedback-cloog: maybe-all-stagefeedback-ppl
configure-gdb: maybe-all-intl
configure-gdb: maybe-configure-sim
configure-gdb: maybe-all-bfd
configure-gdb: maybe-all-libiconv
all-gdb: maybe-all-libiberty
all-gdb: maybe-all-libiconv
all-gdb: maybe-all-opcodes
all-gdb: maybe-all-readline
all-gdb: maybe-all-build-bison
all-gdb: maybe-all-build-byacc
all-gdb: maybe-all-sim
all-gdb: maybe-all-libdecnumber
configure-libgui: maybe-configure-tcl
configure-libgui: maybe-configure-tk
all-libgui: maybe-all-tcl
all-libgui: maybe-all-tk
all-libgui: maybe-all-itcl
configure-bfd: configure-libiberty

configure-stage1-bfd: configure-stage1-libiberty
configure-stage2-bfd: configure-stage2-libiberty
configure-stageb2g0-bfd: configure-stageb2g0-libiberty
configure-stage3-bfd: configure-stage3-libiberty
configure-stageb3g2-bfd: configure-stageb3g2-libiberty
configure-stage4-bfd: configure-stage4-libiberty
configure-stageprofile-bfd: configure-stageprofile-libiberty
configure-stagefeedback-bfd: configure-stagefeedback-libiberty
configure-bfd: maybe-configure-intl

configure-stage1-bfd: maybe-configure-stage1-intl
configure-stage2-bfd: maybe-configure-stage2-intl
configure-stageb2g0-bfd: maybe-configure-stageb2g0-intl
configure-stage3-bfd: maybe-configure-stage3-intl
configure-stageb3g2-bfd: maybe-configure-stageb3g2-intl
configure-stage4-bfd: maybe-configure-stage4-intl
configure-stageprofile-bfd: maybe-configure-stageprofile-intl
configure-stagefeedback-bfd: maybe-configure-stagefeedback-intl
all-bfd: maybe-all-libiberty

all-stage1-bfd: maybe-all-stage1-libiberty
all-stage2-bfd: maybe-all-stage2-libiberty
all-stageb2g0-bfd: maybe-all-stageb2g0-libiberty
all-stage3-bfd: maybe-all-stage3-libiberty
all-stageb3g2-bfd: maybe-all-stageb3g2-libiberty
all-stage4-bfd: maybe-all-stage4-libiberty
all-stageprofile-bfd: maybe-all-stageprofile-libiberty
all-stagefeedback-bfd: maybe-all-stagefeedback-libiberty
all-bfd: maybe-all-intl

all-stage1-bfd: maybe-all-stage1-intl
all-stage2-bfd: maybe-all-stage2-intl
all-stageb2g0-bfd: maybe-all-stageb2g0-intl
all-stage3-bfd: maybe-all-stage3-intl
all-stageb3g2-bfd: maybe-all-stageb3g2-intl
all-stage4-bfd: maybe-all-stage4-intl
all-stageprofile-bfd: maybe-all-stageprofile-intl
all-stagefeedback-bfd: maybe-all-stagefeedback-intl
configure-opcodes: configure-libiberty

configure-stage1-opcodes: configure-stage1-libiberty
configure-stage2-opcodes: configure-stage2-libiberty
configure-stageb2g0-opcodes: configure-stageb2g0-libiberty
configure-stage3-opcodes: configure-stage3-libiberty
configure-stageb3g2-opcodes: configure-stageb3g2-libiberty
configure-stage4-opcodes: configure-stage4-libiberty
configure-stageprofile-opcodes: configure-stageprofile-libiberty
configure-stagefeedback-opcodes: configure-stagefeedback-libiberty
all-opcodes: maybe-all-libiberty

all-stage1-opcodes: maybe-all-stage1-libiberty
all-stage2-opcodes: maybe-all-stage2-libiberty
all-stageb2g0-opcodes: maybe-all-stageb2g0-libiberty
all-stage3-opcodes: maybe-all-stage3-libiberty
all-stageb3g2-opcodes: maybe-all-stageb3g2-libiberty
all-stage4-opcodes: maybe-all-stage4-libiberty
all-stageprofile-opcodes: maybe-all-stageprofile-libiberty
all-stagefeedback-opcodes: maybe-all-stagefeedback-libiberty
configure-binutils: maybe-configure-intl

configure-stage1-binutils: maybe-configure-stage1-intl
configure-stage2-binutils: maybe-configure-stage2-intl
configure-stageb2g0-binutils: maybe-configure-stageb2g0-intl
configure-stage3-binutils: maybe-configure-stage3-intl
configure-stageb3g2-binutils: maybe-configure-stageb3g2-intl
configure-stage4-binutils: maybe-configure-stage4-intl
configure-stageprofile-binutils: maybe-configure-stageprofile-intl
configure-stagefeedback-binutils: maybe-configure-stagefeedback-intl
all-binutils: maybe-all-libiberty

all-stage1-binutils: maybe-all-stage1-libiberty
all-stage2-binutils: maybe-all-stage2-libiberty
all-stageb2g0-binutils: maybe-all-stageb2g0-libiberty
all-stage3-binutils: maybe-all-stage3-libiberty
all-stageb3g2-binutils: maybe-all-stageb3g2-libiberty
all-stage4-binutils: maybe-all-stage4-libiberty
all-stageprofile-binutils: maybe-all-stageprofile-libiberty
all-stagefeedback-binutils: maybe-all-stagefeedback-libiberty
all-binutils: maybe-all-opcodes

all-stage1-binutils: maybe-all-stage1-opcodes
all-stage2-binutils: maybe-all-stage2-opcodes
all-stageb2g0-binutils: maybe-all-stageb2g0-opcodes
all-stage3-binutils: maybe-all-stage3-opcodes
all-stageb3g2-binutils: maybe-all-stageb3g2-opcodes
all-stage4-binutils: maybe-all-stage4-opcodes
all-stageprofile-binutils: maybe-all-stageprofile-opcodes
all-stagefeedback-binutils: maybe-all-stagefeedback-opcodes
all-binutils: maybe-all-bfd

all-stage1-binutils: maybe-all-stage1-bfd
all-stage2-binutils: maybe-all-stage2-bfd
all-stageb2g0-binutils: maybe-all-stageb2g0-bfd
all-stage3-binutils: maybe-all-stage3-bfd
all-stageb3g2-binutils: maybe-all-stageb3g2-bfd
all-stage4-binutils: maybe-all-stage4-bfd
all-stageprofile-binutils: maybe-all-stageprofile-bfd
all-stagefeedback-binutils: maybe-all-stagefeedback-bfd
all-binutils: maybe-all-build-flex

all-stage1-binutils: maybe-all-build-flex
all-stage2-binutils: maybe-all-build-flex
all-stageb2g0-binutils: maybe-all-build-flex
all-stage3-binutils: maybe-all-build-flex
all-stageb3g2-binutils: maybe-all-build-flex
all-stage4-binutils: maybe-all-build-flex
all-stageprofile-binutils: maybe-all-build-flex
all-stagefeedback-binutils: maybe-all-build-flex
all-binutils: maybe-all-build-bison

all-stage1-binutils: maybe-all-build-bison
all-stage2-binutils: maybe-all-build-bison
all-stageb2g0-binutils: maybe-all-build-bison
all-stage3-binutils: maybe-all-build-bison
all-stageb3g2-binutils: maybe-all-build-bison
all-stage4-binutils: maybe-all-build-bison
all-stageprofile-binutils: maybe-all-build-bison
all-stagefeedback-binutils: maybe-all-build-bison
all-binutils: maybe-all-build-byacc

all-stage1-binutils: maybe-all-build-byacc
all-stage2-binutils: maybe-all-build-byacc
all-stageb2g0-binutils: maybe-all-build-byacc
all-stage3-binutils: maybe-all-build-byacc
all-stageb3g2-binutils: maybe-all-build-byacc
all-stage4-binutils: maybe-all-build-byacc
all-stageprofile-binutils: maybe-all-build-byacc
all-stagefeedback-binutils: maybe-all-build-byacc
all-binutils: maybe-all-intl

all-stage1-binutils: maybe-all-stage1-intl
all-stage2-binutils: maybe-all-stage2-intl
all-stageb2g0-binutils: maybe-all-stageb2g0-intl
all-stage3-binutils: maybe-all-stage3-intl
all-stageb3g2-binutils: maybe-all-stageb3g2-intl
all-stage4-binutils: maybe-all-stage4-intl
all-stageprofile-binutils: maybe-all-stageprofile-intl
all-stagefeedback-binutils: maybe-all-stagefeedback-intl
install-binutils: maybe-install-opcodes
install-opcodes: maybe-install-bfd
configure-gas: maybe-configure-intl

configure-stage1-gas: maybe-configure-stage1-intl
configure-stage2-gas: maybe-configure-stage2-intl
configure-stageb2g0-gas: maybe-configure-stageb2g0-intl
configure-stage3-gas: maybe-configure-stage3-intl
configure-stageb3g2-gas: maybe-configure-stageb3g2-intl
configure-stage4-gas: maybe-configure-stage4-intl
configure-stageprofile-gas: maybe-configure-stageprofile-intl
configure-stagefeedback-gas: maybe-configure-stagefeedback-intl
all-gas: maybe-all-libiberty

all-stage1-gas: maybe-all-stage1-libiberty
all-stage2-gas: maybe-all-stage2-libiberty
all-stageb2g0-gas: maybe-all-stageb2g0-libiberty
all-stage3-gas: maybe-all-stage3-libiberty
all-stageb3g2-gas: maybe-all-stageb3g2-libiberty
all-stage4-gas: maybe-all-stage4-libiberty
all-stageprofile-gas: maybe-all-stageprofile-libiberty
all-stagefeedback-gas: maybe-all-stagefeedback-libiberty
all-gas: maybe-all-opcodes

all-stage1-gas: maybe-all-stage1-opcodes
all-stage2-gas: maybe-all-stage2-opcodes
all-stageb2g0-gas: maybe-all-stageb2g0-opcodes
all-stage3-gas: maybe-all-stage3-opcodes
all-stageb3g2-gas: maybe-all-stageb3g2-opcodes
all-stage4-gas: maybe-all-stage4-opcodes
all-stageprofile-gas: maybe-all-stageprofile-opcodes
all-stagefeedback-gas: maybe-all-stagefeedback-opcodes
all-gas: maybe-all-bfd

all-stage1-gas: maybe-all-stage1-bfd
all-stage2-gas: maybe-all-stage2-bfd
all-stageb2g0-gas: maybe-all-stageb2g0-bfd
all-stage3-gas: maybe-all-stage3-bfd
all-stageb3g2-gas: maybe-all-stageb3g2-bfd
all-stage4-gas: maybe-all-stage4-bfd
all-stageprofile-gas: maybe-all-stageprofile-bfd
all-stagefeedback-gas: maybe-all-stagefeedback-bfd
all-gas: maybe-all-intl

all-stage1-gas: maybe-all-stage1-intl
all-stage2-gas: maybe-all-stage2-intl
all-stageb2g0-gas: maybe-all-stageb2g0-intl
all-stage3-gas: maybe-all-stage3-intl
all-stageb3g2-gas: maybe-all-stageb3g2-intl
all-stage4-gas: maybe-all-stage4-intl
all-stageprofile-gas: maybe-all-stageprofile-intl
all-stagefeedback-gas: maybe-all-stagefeedback-intl
configure-gprof: maybe-configure-intl
all-gprof: maybe-all-libiberty
all-gprof: maybe-all-bfd
all-gprof: maybe-all-opcodes
all-gprof: maybe-all-intl
configure-ld: maybe-configure-intl

configure-stage1-ld: maybe-configure-stage1-intl
configure-stage2-ld: maybe-configure-stage2-intl
configure-stageb2g0-ld: maybe-configure-stageb2g0-intl
configure-stage3-ld: maybe-configure-stage3-intl
configure-stageb3g2-ld: maybe-configure-stageb3g2-intl
configure-stage4-ld: maybe-configure-stage4-intl
configure-stageprofile-ld: maybe-configure-stageprofile-intl
configure-stagefeedback-ld: maybe-configure-stagefeedback-intl
all-ld: maybe-all-libiberty

all-stage1-ld: maybe-all-stage1-libiberty
all-stage2-ld: maybe-all-stage2-libiberty
all-stageb2g0-ld: maybe-all-stageb2g0-libiberty
all-stage3-ld: maybe-all-stage3-libiberty
all-stageb3g2-ld: maybe-all-stageb3g2-libiberty
all-stage4-ld: maybe-all-stage4-libiberty
all-stageprofile-ld: maybe-all-stageprofile-libiberty
all-stagefeedback-ld: maybe-all-stagefeedback-libiberty
all-ld: maybe-all-bfd

all-stage1-ld: maybe-all-stage1-bfd
all-stage2-ld: maybe-all-stage2-bfd
all-stageb2g0-ld: maybe-all-stageb2g0-bfd
all-stage3-ld: maybe-all-stage3-bfd
all-stageb3g2-ld: maybe-all-stageb3g2-bfd
all-stage4-ld: maybe-all-stage4-bfd
all-stageprofile-ld: maybe-all-stageprofile-bfd
all-stagefeedback-ld: maybe-all-stagefeedback-bfd
all-ld: maybe-all-opcodes

all-stage1-ld: maybe-all-stage1-opcodes
all-stage2-ld: maybe-all-stage2-opcodes
all-stageb2g0-ld: maybe-all-stageb2g0-opcodes
all-stage3-ld: maybe-all-stage3-opcodes
all-stageb3g2-ld: maybe-all-stageb3g2-opcodes
all-stage4-ld: maybe-all-stage4-opcodes
all-stageprofile-ld: maybe-all-stageprofile-opcodes
all-stagefeedback-ld: maybe-all-stagefeedback-opcodes
all-ld: maybe-all-build-bison

all-stage1-ld: maybe-all-build-bison
all-stage2-ld: maybe-all-build-bison
all-stageb2g0-ld: maybe-all-build-bison
all-stage3-ld: maybe-all-build-bison
all-stageb3g2-ld: maybe-all-build-bison
all-stage4-ld: maybe-all-build-bison
all-stageprofile-ld: maybe-all-build-bison
all-stagefeedback-ld: maybe-all-build-bison
all-ld: maybe-all-build-byacc

all-stage1-ld: maybe-all-build-byacc
all-stage2-ld: maybe-all-build-byacc
all-stageb2g0-ld: maybe-all-build-byacc
all-stage3-ld: maybe-all-build-byacc
all-stageb3g2-ld: maybe-all-build-byacc
all-stage4-ld: maybe-all-build-byacc
all-stageprofile-ld: maybe-all-build-byacc
all-stagefeedback-ld: maybe-all-build-byacc
all-ld: maybe-all-build-flex

all-stage1-ld: maybe-all-build-flex
all-stage2-ld: maybe-all-build-flex
all-stageb2g0-ld: maybe-all-build-flex
all-stage3-ld: maybe-all-build-flex
all-stageb3g2-ld: maybe-all-build-flex
all-stage4-ld: maybe-all-build-flex
all-stageprofile-ld: maybe-all-build-flex
all-stagefeedback-ld: maybe-all-build-flex
all-ld: maybe-all-intl

all-stage1-ld: maybe-all-stage1-intl
all-stage2-ld: maybe-all-stage2-intl
all-stageb2g0-ld: maybe-all-stageb2g0-intl
all-stage3-ld: maybe-all-stage3-intl
all-stageb3g2-ld: maybe-all-stageb3g2-intl
all-stage4-ld: maybe-all-stage4-intl
all-stageprofile-ld: maybe-all-stageprofile-intl
all-stagefeedback-ld: maybe-all-stagefeedback-intl
configure-gold: maybe-configure-intl

configure-stage1-gold: maybe-configure-stage1-intl
configure-stage2-gold: maybe-configure-stage2-intl
configure-stageb2g0-gold: maybe-configure-stageb2g0-intl
configure-stage3-gold: maybe-configure-stage3-intl
configure-stageb3g2-gold: maybe-configure-stageb3g2-intl
configure-stage4-gold: maybe-configure-stage4-intl
configure-stageprofile-gold: maybe-configure-stageprofile-intl
configure-stagefeedback-gold: maybe-configure-stagefeedback-intl
all-gold: maybe-all-libiberty

all-stage1-gold: maybe-all-stage1-libiberty
all-stage2-gold: maybe-all-stage2-libiberty
all-stageb2g0-gold: maybe-all-stageb2g0-libiberty
all-stage3-gold: maybe-all-stage3-libiberty
all-stageb3g2-gold: maybe-all-stageb3g2-libiberty
all-stage4-gold: maybe-all-stage4-libiberty
all-stageprofile-gold: maybe-all-stageprofile-libiberty
all-stagefeedback-gold: maybe-all-stagefeedback-libiberty
all-gold: maybe-all-intl

all-stage1-gold: maybe-all-stage1-intl
all-stage2-gold: maybe-all-stage2-intl
all-stageb2g0-gold: maybe-all-stageb2g0-intl
all-stage3-gold: maybe-all-stage3-intl
all-stageb3g2-gold: maybe-all-stageb3g2-intl
all-stage4-gold: maybe-all-stage4-intl
all-stageprofile-gold: maybe-all-stageprofile-intl
all-stagefeedback-gold: maybe-all-stagefeedback-intl
all-gold: maybe-all-bfd

all-stage1-gold: maybe-all-stage1-bfd
all-stage2-gold: maybe-all-stage2-bfd
all-stageb2g0-gold: maybe-all-stageb2g0-bfd
all-stage3-gold: maybe-all-stage3-bfd
all-stageb3g2-gold: maybe-all-stageb3g2-bfd
all-stage4-gold: maybe-all-stage4-bfd
all-stageprofile-gold: maybe-all-stageprofile-bfd
all-stagefeedback-gold: maybe-all-stagefeedback-bfd
all-gold: maybe-all-build-bison

all-stage1-gold: maybe-all-build-bison
all-stage2-gold: maybe-all-build-bison
all-stageb2g0-gold: maybe-all-build-bison
all-stage3-gold: maybe-all-build-bison
all-stageb3g2-gold: maybe-all-build-bison
all-stage4-gold: maybe-all-build-bison
all-stageprofile-gold: maybe-all-build-bison
all-stagefeedback-gold: maybe-all-build-bison
all-gold: maybe-all-build-byacc

all-stage1-gold: maybe-all-build-byacc
all-stage2-gold: maybe-all-build-byacc
all-stageb2g0-gold: maybe-all-build-byacc
all-stage3-gold: maybe-all-build-byacc
all-stageb3g2-gold: maybe-all-build-byacc
all-stage4-gold: maybe-all-build-byacc
all-stageprofile-gold: maybe-all-build-byacc
all-stagefeedback-gold: maybe-all-build-byacc
check-gold: maybe-all-binutils

check-stage1-gold: maybe-all-stage1-binutils
check-stage2-gold: maybe-all-stage2-binutils
check-stageb2g0-gold: maybe-all-stageb2g0-binutils
check-stage3-gold: maybe-all-stage3-binutils
check-stageb3g2-gold: maybe-all-stageb3g2-binutils
check-stage4-gold: maybe-all-stage4-binutils
check-stageprofile-gold: maybe-all-stageprofile-binutils
check-stagefeedback-gold: maybe-all-stagefeedback-binutils
configure-opcodes: maybe-configure-intl

configure-stage1-opcodes: maybe-configure-stage1-intl
configure-stage2-opcodes: maybe-configure-stage2-intl
configure-stageb2g0-opcodes: maybe-configure-stageb2g0-intl
configure-stage3-opcodes: maybe-configure-stage3-intl
configure-stageb3g2-opcodes: maybe-configure-stageb3g2-intl
configure-stage4-opcodes: maybe-configure-stage4-intl
configure-stageprofile-opcodes: maybe-configure-stageprofile-intl
configure-stagefeedback-opcodes: maybe-configure-stagefeedback-intl
all-opcodes: maybe-all-bfd

all-stage1-opcodes: maybe-all-stage1-bfd
all-stage2-opcodes: maybe-all-stage2-bfd
all-stageb2g0-opcodes: maybe-all-stageb2g0-bfd
all-stage3-opcodes: maybe-all-stage3-bfd
all-stageb3g2-opcodes: maybe-all-stageb3g2-bfd
all-stage4-opcodes: maybe-all-stage4-bfd
all-stageprofile-opcodes: maybe-all-stageprofile-bfd
all-stagefeedback-opcodes: maybe-all-stagefeedback-bfd
all-opcodes: maybe-all-libiberty

all-stage1-opcodes: maybe-all-stage1-libiberty
all-stage2-opcodes: maybe-all-stage2-libiberty
all-stageb2g0-opcodes: maybe-all-stageb2g0-libiberty
all-stage3-opcodes: maybe-all-stage3-libiberty
all-stageb3g2-opcodes: maybe-all-stageb3g2-libiberty
all-stage4-opcodes: maybe-all-stage4-libiberty
all-stageprofile-opcodes: maybe-all-stageprofile-libiberty
all-stagefeedback-opcodes: maybe-all-stagefeedback-libiberty
all-opcodes: maybe-all-intl

all-stage1-opcodes: maybe-all-stage1-intl
all-stage2-opcodes: maybe-all-stage2-intl
all-stageb2g0-opcodes: maybe-all-stageb2g0-intl
all-stage3-opcodes: maybe-all-stage3-intl
all-stageb3g2-opcodes: maybe-all-stageb3g2-intl
all-stage4-opcodes: maybe-all-stage4-intl
all-stageprofile-opcodes: maybe-all-stageprofile-intl
all-stagefeedback-opcodes: maybe-all-stagefeedback-intl
all-dejagnu: maybe-all-tcl
all-dejagnu: maybe-all-expect
all-dejagnu: maybe-all-tk
configure-expect: maybe-configure-tcl
configure-expect: maybe-configure-tk
all-expect: maybe-all-tcl
all-expect: maybe-all-tk
configure-itcl: maybe-configure-tcl
configure-itcl: maybe-configure-tk
all-itcl: maybe-all-tcl
all-itcl: maybe-all-tk
install-itcl: maybe-install-tcl
configure-tk: maybe-configure-tcl
all-tk: maybe-all-tcl
all-sid: maybe-all-libiberty
all-sid: maybe-all-bfd
all-sid: maybe-all-opcodes
all-sid: maybe-all-tcl
all-sid: maybe-all-tk
install-sid: maybe-install-tcl
install-sid: maybe-install-tk
configure-sim: maybe-configure-intl
all-sim: maybe-all-intl
all-sim: maybe-all-libiberty
all-sim: maybe-all-bfd
all-sim: maybe-all-opcodes
all-sim: maybe-all-readline
all-sim: maybe-configure-gdb
all-fastjar: maybe-all-zlib
all-fastjar: maybe-all-build-texinfo
all-fastjar: maybe-all-libiberty
all-autoconf: maybe-all-m4
all-autoconf: maybe-all-build-texinfo
all-automake: maybe-all-m4
all-automake: maybe-all-build-texinfo
all-automake: maybe-all-autoconf
all-bison: maybe-all-intl
all-bison: maybe-all-build-texinfo
all-diff: maybe-all-intl
all-diff: maybe-all-build-texinfo
all-fileutils: maybe-all-intl
all-fileutils: maybe-all-build-texinfo
all-flex: maybe-all-build-bison
all-flex: maybe-all-build-byacc
all-flex: maybe-all-intl
all-flex: maybe-all-m4
all-flex: maybe-all-build-texinfo
all-gzip: maybe-all-intl
all-gzip: maybe-all-zlib
all-gzip: maybe-all-build-texinfo
all-hello: maybe-all-intl
all-hello: maybe-all-build-texinfo
all-m4: maybe-all-intl
all-m4: maybe-all-build-texinfo
all-make: maybe-all-intl
all-make: maybe-all-build-texinfo
all-patch: maybe-all-build-texinfo
all-make: maybe-all-build-texinfo
all-prms: maybe-all-libiberty
all-recode: maybe-all-build-texinfo
all-sed: maybe-all-build-texinfo
all-send-pr: maybe-all-prms
all-tar: maybe-all-build-texinfo
all-uudecode: maybe-all-build-texinfo
configure-target-boehm-gc: maybe-configure-target-qthreads
configure-target-boehm-gc: maybe-all-target-libstdc++-v3
configure-target-fastjar: maybe-configure-target-zlib
all-target-fastjar: maybe-all-target-zlib
all-target-fastjar: maybe-all-target-libiberty
configure-target-libjava: maybe-configure-target-zlib
configure-target-libjava: maybe-configure-target-boehm-gc
configure-target-libjava: maybe-configure-target-qthreads
configure-target-libjava: maybe-configure-target-libffi
all-target-libjava: maybe-all-fastjar
all-target-libjava: maybe-all-target-zlib
all-target-libjava: maybe-all-target-boehm-gc
all-target-libjava: maybe-all-target-qthreads
all-target-libjava: maybe-all-target-libffi
configure-target-libobjc: maybe-configure-target-boehm-gc
all-target-libobjc: maybe-all-target-libiberty
all-target-libobjc: maybe-all-target-boehm-gc
all-target-libstdc++-v3: maybe-all-target-libiberty
configure-target-libstdc++-v3: maybe-configure-target-libgomp
all-target-libgloss: maybe-all-target-newlib
all-target-winsup: maybe-all-target-libiberty
all-target-winsup: maybe-all-target-libtermcap


# Dependencies for target modules on other target modules are
# described by lang_env_dependencies; the defaults apply to anything
# not mentioned there.





configure-target-libstdc++-v3: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-libmudflap: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-libssp: maybe-all-target-newlib maybe-all-target-libgloss



configure-target-libgfortran: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-libobjc: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-libtermcap: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-winsup: maybe-all-target-newlib maybe-all-target-libgloss



configure-target-gperf: maybe-all-target-newlib maybe-all-target-libgloss
configure-target-gperf: maybe-all-target-libstdc++-v3

configure-target-examples: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-libffi: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-libjava: maybe-all-target-newlib maybe-all-target-libgloss
configure-target-libjava: maybe-all-target-libstdc++-v3

configure-target-zlib: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-boehm-gc: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-qthreads: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-rda: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-libada: maybe-all-target-newlib maybe-all-target-libgloss

configure-target-libgomp: maybe-all-target-newlib maybe-all-target-libgloss


CONFIGURE_GDB_TK = 
GDB_TK = 
INSTALL_GDB_TK = 
configure-gdb: $(CONFIGURE_GDB_TK)
all-gdb: $(gdbnlmrequirements) $(GDB_TK)
install-gdb: $(INSTALL_GDB_TK)

# Serialization dependencies.  Host configures don't work well in parallel to
# each other, due to contention over config.cache.  Target configures and 
# build configures are similar.

# serdep.tmp

# --------------------------------
# Regenerating top level configury
# --------------------------------

# Rebuilding Makefile.in, using autogen.
AUTOGEN = autogen
$(srcdir)/Makefile.in: # $(srcdir)/Makefile.tpl $(srcdir)/Makefile.def
	cd $(srcdir) && $(AUTOGEN) Makefile.def

# Rebuilding Makefile.
Makefile: $(srcdir)/Makefile.in config.status
	CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) ./config.status

config.status: configure
	CONFIG_SHELL="$(SHELL)" $(SHELL) ./config.status --recheck

# Rebuilding configure.
AUTOCONF = autoconf
$(srcdir)/configure: # $(srcdir)/configure.ac $(srcdir)/config/acx.m4 \
	$(srcdir)/config/override.m4 $(srcdir)/config/proginstall.m4
	cd $(srcdir) && $(AUTOCONF)

# ------------------------------
# Special directives to GNU Make
# ------------------------------

# Don't pass command-line variables to submakes.
.NOEXPORT:
MAKEOVERRIDES=

# end of Makefile.in
