#!/usr/bin/python2
# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# IMPORTANT NOTE: If you make local mods to this file, you must run:
#   %  pnacl/build.sh driver
# in order for them to take effect in the scons build.  This command
# updates the copy in the toolchain/ tree.
#

from driver_tools import *
from driver_env import env
from driver_log import Log, DriverOpen, TempFiles
import filetype
import platform

EXTRA_ENV = {
  'ALLOW_NATIVE': '0', # Allow LD args which will change the behavior
                       # of native linking. This must be accompanied by
                       # -arch to produce a .nexe.
  'USE_IRT': '1',  # Use stable IRT interfaces.

  'INPUTS'   : '',
  'OUTPUT'   : '',

  'SHARED'   : '0',
  'STATIC'   : '0',
  'PIC'      : '0',
  'STDLIB'   : '1',
  'RELOCATABLE': '0',
  'SONAME'   : '',

  'STRIP_MODE' : 'none',

  'STRIP_FLAGS'      : '${STRIP_FLAGS_%STRIP_MODE%}',
  'STRIP_FLAGS_all'  : '-s',
  'STRIP_FLAGS_debug': '-S',

  'OPT_INLINE_THRESHOLD': '100',
  'OPT_LEVEL': '',  # Default opt is 0, but we need to know if it's explicitly
                    # requested or not, since we don't want to propagate
                    # the value to TRANSLATE_FLAGS if it wasn't explicitly set.
  'OPT_LTO_FLAGS': '-std-link-opts -disable-internalize',
  'OPT_FLAGS': '${#OPT_LEVEL && !OPT_LEVEL == 0 ? ${OPT_LTO_FLAGS}} ${OPT_STRIP_%STRIP_MODE%} ' +
               '-inline-threshold=${OPT_INLINE_THRESHOLD} ',
  'OPT_STRIP_none': '',
  'OPT_STRIP_all': '-disable-opt --strip',
  'OPT_STRIP_debug': '-disable-opt --strip-debug',

  'TRANSLATE_FLAGS': '${PIC ? -fPIC} ${!STDLIB ? -nostdlib} ' +
                     '${STATIC ? -static} ' +
                     '${SHARED ? -shared} ' +
                     '${#SONAME ? -Wl,--soname=${SONAME}} ' +
                     '${#OPT_LEVEL ? -O${OPT_LEVEL}} ' +
                     '--allow-llvm-bitcode-input ' +
                     '${TRANSLATE_FLAGS_USER}',

  # Extra pnacl-translate flags specified by the user using -Wt
  'TRANSLATE_FLAGS_USER': '',

  'GOLD_PLUGIN_ARGS': '-plugin=${GOLD_PLUGIN_SO} ' +
                      '-plugin-opt=emit-llvm',

  'LD_FLAGS'       : '-nostdlib ${@AddPrefix:-L:SEARCH_DIRS} ' +
                     '${SHARED ? -shared} ${STATIC ? -static} ' +
                     '${RELOCATABLE ? -relocatable} ' +
                     '${#SONAME ? --soname=${SONAME}}',

  # Flags for native linking.
  # Only allowed if ALLOW_NATIVE is true.
  'LD_FLAGS_NATIVE': '',

  'SEARCH_DIRS'        : '${SEARCH_DIRS_USER} ${SEARCH_DIRS_BUILTIN}',
  'SEARCH_DIRS_USER'   : '',

  # Standard Library Directories
  'SEARCH_DIRS_BUILTIN': '${STDLIB ? ' +
                         '  ${BASE_USR}/lib/ ' +
                         '  ${BASE_SDK}/lib/ ' +
                         '  ${BASE_LIB}/ ' +
                         '  ${SEARCH_DIRS_NATIVE} ' +
                         '}',

  # HACK-BEGIN
  # Add glibc/lib-<arch>/ to the search path.
  # These are here to let the bitcode link find native objects
  # needed by the GLibC toolchain.
  # TODO(pdox): Remove these when we have bitcode .pso stubs for GlibC.
  'SEARCH_DIRS_NATIVE': '${LIBMODE_GLIBC ? ${LIBS_ARCH}/}',

  'LIBS_ARCH'        : '${LIBS_%ARCH%}',
  'LIBS_ARM'         : '${BASE_GLIBC}/lib-arm',
  'LIBS_X8632'       : '${BASE_GLIBC}/lib-x86-32',
  'LIBS_X8664'       : '${BASE_GLIBC}/lib-x86-64',
  'LIBS_MIPS32'      : '${BASE_GLIBC}/lib-mips32',
  # HACK-END

  'BCLD_OFORMAT'        : '${BCLD_OFORMAT_%ARCH%}',
  'BCLD_OFORMAT_ARM'    : 'elf32-littlearm',
  'BCLD_OFORMAT_X8632'  : 'elf32-i386-nacl',
  'BCLD_OFORMAT_X8664'  : 'elf64-x86-64-nacl',
  'BCLD_OFORMAT_MIPS32' : 'elf32-tradlittlemips',

  'BCLD_ALLOW_UNRESOLVED'  :
    # The following functions are implemented in the native support library.
    # Before a .pexe is produced, they get rewritten to intrinsic calls.
    # However, this rewriting happens after bitcode linking - so gold has
    # to be told that these are allowed to remain unresolved.
    '--allow-unresolved=memcpy '
    '--allow-unresolved=memset '
    '--allow-unresolved=memmove '
    '--allow-unresolved=setjmp '
    '--allow-unresolved=longjmp '
    # For exception-handling enabled tests.
    '${ALLOW_CXX_EXCEPTIONS ? '
      '--allow-unresolved=_Unwind_Backtrace '
      '--allow-unresolved=_Unwind_DeleteException '
      '--allow-unresolved=_Unwind_GetCFA '
      '--allow-unresolved=_Unwind_GetDataRelBase '
      '--allow-unresolved=_Unwind_GetIP '
      '--allow-unresolved=_Unwind_GetIPInfo '
      '--allow-unresolved=_Unwind_GetLanguageSpecificData '
      '--allow-unresolved=_Unwind_GetRegionStart '
      '--allow-unresolved=_Unwind_GetTextRelBase '
      '--allow-unresolved=_Unwind_PNaClSetResult0 '
      '--allow-unresolved=_Unwind_PNaClSetResult1 '
      '--allow-unresolved=_Unwind_RaiseException '
      '--allow-unresolved=_Unwind_Resume '
      '--allow-unresolved=_Unwind_Resume_or_Rethrow '
      '--allow-unresolved=_Unwind_SetIP}',

  'BCLD_FLAGS':
    '--oformat ${BCLD_OFORMAT} -Ttext=0x20000 ' +
    '${!SHARED && !RELOCATABLE ? --undef-sym-check ${BCLD_ALLOW_UNRESOLVED}} ' +
    '${GOLD_PLUGIN_ARGS} ${LD_FLAGS}',
  'RUN_BCLD': ('${LD} ${BCLD_FLAGS} ${inputs} -o ${output}'),

  'ALLOW_CXX_EXCEPTIONS': '0',
  'ALLOW_NEXE_BUILD_ID': '0',
  'DISABLE_ABI_CHECK': '0',
  'LLVM_PASSES_TO_DISABLE': '',
  # Skip dev intrinsic checks in ABI verifier.  Used for pnacl-llc.pexe and
  # gold.pexe, which currently use llvm.nacl.target.arch.
  # TODO(jvoung): find way to stop using llvm.nacl.target.arch.
  'ALLOW_DEV_INTRINSICS': '0',
}

def AddToBCLinkFlags(*args):
  env.append('LD_FLAGS', *args)

def AddToNativeFlags(*args):
  env.append('LD_FLAGS_NATIVE', *args)

def AddToBothFlags(*args):
  env.append('LD_FLAGS', *args)
  env.append('LD_FLAGS_NATIVE', *args)

def AddAllowCXXExceptions(*args):
  env.set('ALLOW_CXX_EXCEPTIONS', '1')
  env.append('TRANSLATE_FLAGS', *args)

def SetLibTarget(*args):
  arch = ParseTriple(args[0])
  if arch != 'le32':
    env.set('BCLIB_ARCH', arch)

LDPatterns = [
  ( '--pnacl-allow-native', "env.set('ALLOW_NATIVE', '1')"),
  ( '--noirt',              "env.set('USE_IRT', '0')"),
  ( '(--pnacl-allow-exceptions)', AddAllowCXXExceptions),
  ( '(--pnacl-allow-nexe-build-id)', "env.set('ALLOW_NEXE_BUILD_ID', '1')"),
  ( '--pnacl-disable-abi-check', "env.set('DISABLE_ABI_CHECK', '1')"),
  # "--pnacl-disable-pass" allows an ABI simplification pass to be
  # disabled if it is causing problems.  These passes are generally
  # required for ABI-stable pexes but can be omitted when the PNaCl
  # toolchain is used for producing native nexes.
  ( '--pnacl-disable-pass=(.+)', "env.append('LLVM_PASSES_TO_DISABLE', $0)"),
  ( '--pnacl-allow-dev-intrinsics', "env.set('ALLOW_DEV_INTRINSICS', '1')"),
  ( ('-target', '(.+)'), SetLibTarget),
  ( ('--target=(.+)'), SetLibTarget),

  ( '-o(.+)',          "env.set('OUTPUT', pathtools.normalize($0))"),
  ( ('-o', '(.+)'),    "env.set('OUTPUT', pathtools.normalize($0))"),

  ( '-shared',         "env.set('SHARED', '1')"),
  ( '-static',         "env.set('STATIC', '1')"),
  ( '-nostdlib',       "env.set('STDLIB', '0')"),
  ( '-r',              "env.set('RELOCATABLE', '1')"),
  ( '-relocatable',    "env.set('RELOCATABLE', '1')"),

  ( ('-L', '(.+)'),
    "env.append('SEARCH_DIRS_USER', pathtools.normalize($0))\n"),
  ( '-L(.+)',
    "env.append('SEARCH_DIRS_USER', pathtools.normalize($0))\n"),
  ( ('--library-path', '(.+)'),
    "env.append('SEARCH_DIRS_USER', pathtools.normalize($0))\n"),

  # We just ignore undefined symbols in shared objects, so
  # -rpath-link should not be necessary.
  #
  # However, libsrpc.so still needs to be linked in directly (in non-IRT mode)
  # or it malfunctions. This is the only way that -rpath-link is still used.
  # There's a corresponding hack in pnacl-translate to recognize libsrpc.so
  # and link it in directly.
  # TODO(pdox): Investigate this situation.
  ( ('(-rpath)','(.*)'), ""),
  ( ('(-rpath)=(.*)'), ""),
  ( ('(-rpath-link)','(.*)'),
    "env.append('TRANSLATE_FLAGS', $0+'='+pathtools.normalize($1))"),
  ( ('(-rpath-link)=(.*)'),
    "env.append('TRANSLATE_FLAGS', $0+'='+pathtools.normalize($1))"),

  # This overrides the builtin linker script.
  ( ('(-T)', '(.*)'),    AddToNativeFlags),

  # TODO(pdox): Allow setting an alternative _start symbol in bitcode
  ( ('(-e)','(.*)'),     AddToBothFlags),

  # TODO(pdox): Support GNU versioning.
  ( '(--version-script=.*)', ""),

  # Flags to pass to the native linker.
  ( '-Wn,(.*)', "env.append('LD_FLAGS_NATIVE', *($0.split(',')))"),
  ( ('(-Ttext-segment=.*)'), AddToNativeFlags),
  ( ('(-Trodata-segment=.*)'), AddToNativeFlags),
  ( ('(--section-start)', '(.+)'), AddToNativeFlags),
  ( ('(--build-id)'), AddToNativeFlags),

  # Flags to pass to translate
  ( '-Wt,(.*)', "env.append('TRANSLATE_FLAGS_USER', *($0.split(',')))"),

  # NOTE: -export-dynamic doesn't actually do anything to the bitcode link
  # right now.  This is just in case we do want to record that in metadata
  # eventually, and have that influence the native linker flags.
  ( '(-export-dynamic)', AddToBCLinkFlags),

  ( '-?-soname=(.*)',             "env.set('SONAME', $0)"),
  ( ('-?-soname', '(.*)'),        "env.set('SONAME', $0)"),

  ( '(-M)',                       AddToBCLinkFlags),
  ( '(-t)',                       AddToBCLinkFlags),
  ( ('(-y)','(.*)'),              AddToBCLinkFlags),
  ( ('(-defsym)','(.*)'),         AddToBCLinkFlags),

  ( '-melf_nacl',            "env.set('ARCH', 'X8632')"),
  ( ('-m','elf_nacl'),       "env.set('ARCH', 'X8632')"),
  ( '-melf64_nacl',          "env.set('ARCH', 'X8664')"),
  ( ('-m','elf64_nacl'),     "env.set('ARCH', 'X8664')"),
  ( '-marmelf_nacl',         "env.set('ARCH', 'ARM')"),
  ( ('-m','armelf_nacl'),    "env.set('ARCH', 'ARM')"),
  ( '-mmipselelf_nacl',      "env.set('ARCH', 'MIPS32')"),
  ( ('-m','mipselelf_nacl'), "env.set('ARCH', 'MIPS32')"),

  ( ('(-?-wrap)', '(.+)'), AddToBCLinkFlags),
  ( ('(-?-wrap=.+)'),      AddToBCLinkFlags),

  # NOTE: For scons tests, the code generation fPIC flag is used with pnacl-ld.
  ( '-fPIC',               "env.set('PIC', '1')"),

  # This controls LTO optimization.
  # opt does not support -Os but internally it is identical to -O2
  # opt also does not support -O4 but -O4 is how you ask clang for LTO, so we
  # can support it as well
  ( '-Os',                 "env.set('OPT_LEVEL', '2')"),
  ( '-O([0-3])',           "env.set('OPT_LEVEL', $0)"),
  ( '-O([0-9]+)',          "env.set('OPT_LEVEL', '3')"),

  ( '(-translate-fast)',   "env.append('TRANSLATE_FLAGS', $0)"),

  ( '-s',                  "env.set('STRIP_MODE', 'all')"),
  ( '--strip-all',         "env.set('STRIP_MODE', 'all')"),
  ( '-S',                  "env.set('STRIP_MODE', 'debug')"),
  ( '--strip-debug',       "env.set('STRIP_MODE', 'debug')"),

  ( '-g', ""),

  # Inputs and options that need to be kept in order
  ( '(-l.*)',              "env.append('INPUTS', $0)"),
  ( ('(-l)','(.*)'),       "env.append('INPUTS', $0+$1)"),
  ( '(--no-as-needed)',    "env.append('INPUTS', $0)"),
  ( '(--as-needed)',       "env.append('INPUTS', $0)"),
  ( '(--start-group)',     "env.append('INPUTS', $0)"),
  ( '(--end-group)',       "env.append('INPUTS', $0)"),
  ( '(-Bstatic)',          "env.append('INPUTS', $0)"),
  ( '(-Bdynamic)',          "env.append('INPUTS', $0)"),
  ( '(--(no-)?whole-archive)', "env.append('INPUTS', $0)"),
  ( '(--undefined=.*)',    "env.append('INPUTS', $0)"),
  ( '(-.*)',               UnrecognizedOption),
  ( '(.*)',                "env.append('INPUTS', pathtools.normalize($0))"),
]

def main(argv):
  env.update(EXTRA_ENV)
  ParseArgs(argv, LDPatterns)
  # If the user passed -arch, then they want native output.
  arch_flag_given = GetArch() is not None

  # Both LD_FLAGS_NATIVE and TRANSLATE_FLAGS_USER affect
  # the translation process. If they are non-empty,
  # then --pnacl-allow-native must be given.
  allow_native = env.getbool('ALLOW_NATIVE')
  native_flags = env.get('LD_FLAGS_NATIVE') + env.get('TRANSLATE_FLAGS_USER')
  if len(native_flags) > 0:
    if not allow_native:
      flagstr = ' '.join(native_flags)
      Log.Fatal('"%s" affects translation. '
                'To allow, specify --pnacl-allow-native' % flagstr)

  if env.getbool('ALLOW_NATIVE') and not arch_flag_given:
      Log.Fatal("--pnacl-allow-native given, but translation "
                "is not happening (missing -arch?)")

  # Overriding the lib target uses native-flavored bitcode libs rather than the
  # portable bitcode libs. It is currently only tested/supported for
  # building the IRT.
  if env.getone('BCLIB_ARCH') != '':
    env.set('BASE_USR', "${BASE_USR_ARCH}")
    env.set('BASE_LIB', "${BASE_LIB_ARCH}")

  if env.getbool('RELOCATABLE'):
    if env.getbool('SHARED'):
      Log.Fatal("-r and -shared may not be used together")
    env.set('STATIC', '0')

  inputs = env.get('INPUTS')
  output = env.getone('OUTPUT')

  if output == '':
    output = pathtools.normalize('a.out')

  if not arch_flag_given:
    # If -arch is not given, assume X86-32.
    # This is because gold requires an arch (even for bitcode linking).
    SetArch('X8632')
  assert(GetArch() is not None)

  # Expand all parameters
  # This resolves -lfoo into actual filenames,
  # and expands linker scripts into command-line arguments.
  inputs = ldtools.ExpandInputs(inputs,
                                env.get('SEARCH_DIRS'),
                                env.getbool('STATIC'),
                                # Once all glibc bitcode link is purely
                                # bitcode (e.g., even libc_nonshared.a)
                                # we may be able to restrict this more.
                                # This is also currently used by
                                # pnacl_generate_pexe=0 with glibc,
                                # for user libraries.
                                ldtools.LibraryTypes.ANY)

  # Make sure the inputs have matching arch.
  CheckInputsArch(inputs)

  regular_inputs, native_objects = SplitLinkLine(inputs)

  if not env.getbool('USE_IRT'):
    inputs = UsePrivateLibraries(inputs)

  # Filter out object files which are currently used in the bitcode link.
  # These don't actually need to be treated separately, since the
  # translator includes them automatically. Eventually, these will
  # be compiled to bitcode or replaced by bitcode stubs, and this list
  # can go away.
  if env.getbool('STDLIB'):
    native_objects = RemoveNativeStdLibs(native_objects)

  if env.getbool('SHARED'):
    bitcode_type = 'pso'
    native_type = 'so'
  elif env.getbool('RELOCATABLE'):
    bitcode_type = 'po'
    native_type = 'o'
  else:
    bitcode_type = 'pexe'
    native_type = 'nexe'

  if native_objects and not allow_native:
    argstr = ' '.join(native_objects)
    Log.Fatal("Native objects '%s' detected in the link. "
              "To allow, specify --pnacl-allow-native" % argstr)

  tng = TempNameGen([], output)

  # Do the bitcode link.
  if HasBitcodeInputs(inputs):
    chain = DriverChain(inputs, output, tng)
    chain.add(LinkBC, 'pre_opt.' + bitcode_type)

    # Some ABI simplification passes assume the whole program is
    # available (e.g. -expand-varargs, -nacl-expand-ctors and
    # -nacl-expand-tls).  While we could try running a subset of
    # simplification passes when linking native objects or enabling
    # C++ exception handling, we don't do this because it complicates
    # testing.  For example, it requires '-expand-constant-expr' to be
    # able to handle 'landingpad' instructions.
    abi_simplify = (env.getbool('STATIC') and
                    len(native_objects) == 0 and
                    not env.getbool('ALLOW_CXX_EXCEPTIONS') and
                    not env.getbool('ALLOW_NEXE_BUILD_ID') and
                    env.getone('BCLIB_ARCH') == '')

    preopt_passes = []
    if abi_simplify:
      preopt_passes += ['-pnacl-abi-simplify-preopt']
    elif not env.getbool('ALLOW_CXX_EXCEPTIONS'):
      # '-lowerinvoke' prevents use of C++ exception handling, which
      # is not yet supported in the PNaCl ABI.  '-simplifycfg' removes
      # landingpad blocks made unreachable by '-lowerinvoke'.
      #
      # We run this in order to remove 'resume' instructions,
      # otherwise these are translated to calls to _Unwind_Resume(),
      # which will not be available at native link time.
      preopt_passes += ['-lowerinvoke', '-simplifycfg']
    if len(preopt_passes) != 0:
      chain.add(DoLLVMPasses(preopt_passes), 'simplify_preopt.' + bitcode_type)

    if env.getone('OPT_LEVEL') != '' and env.getone('OPT_LEVEL') != '0':
      chain.add(DoLTO, 'opt.' + bitcode_type)
    elif env.getone('STRIP_MODE') != 'none':
      chain.add(DoStrip, 'stripped.' + bitcode_type)

    if abi_simplify:
      postopt_passes = ['-pnacl-abi-simplify-postopt']
      if not env.getbool('DISABLE_ABI_CHECK'):
        postopt_passes += [
            '-verify-pnaclabi-module',
            '-verify-pnaclabi-functions',
            # A flag for the above -verify-pnaclabi-* passes.
            '-pnaclabi-allow-debug-metadata']
        if env.getbool('ALLOW_DEV_INTRINSICS'):
          # A flag for the above -verify-pnaclabi-* passes.
          postopt_passes += ['-pnaclabi-allow-dev-intrinsics']
      chain.add(DoLLVMPasses(postopt_passes),
                'simplify_postopt.' + bitcode_type)
  else:
    chain = DriverChain('', output, tng)

  # If -arch is also specified, invoke pnacl-translate afterwards.
  if arch_flag_given:
    env.set('NATIVE_OBJECTS', *native_objects)
    chain.add(DoTranslate, native_type)

  chain.run()

  if bitcode_type == 'pexe' and not arch_flag_given:
    # Mark .pexe files as executable.
    # Some versions of 'configure' expect this.
    SetExecutableMode(output)
  return 0

def RemoveNativeStdLibs(objs):
  # For newlib, all standard libraries are already bitcode.
  if env.getbool('LIBMODE_NEWLIB'):
    return objs

  # GLibC standard libraries
  defaultlibs = ['libc_nonshared.a', 'libpthread_nonshared.a',
                 'libc.a', 'libstdc++.a', 'libgcc.a', 'libgcc_eh.a',
                 'libm.a']
  return [f for f in objs if pathtools.split(f)[1] not in defaultlibs]

def UsePrivateLibraries(libs):
  """ Place libnacl_sys_private.a before libnacl.a
  Replace libpthread.a with libpthread_private.a
  Replace libnacl_dyncode.a with libnacl_dyncode_private.a
  This assumes that the private libs can be found at the same directory
  as the public libs.
  """
  result_libs = []
  for l in libs:
    base = pathtools.basename(l)
    dname = pathtools.dirname(l)
    if base == 'libnacl.a':
      Log.Info('Not using IRT -- injecting libnacl_sys_private.a to link line')
      result_libs.append(pathtools.join(dname, 'libnacl_sys_private.a'))
      result_libs.append(l)
    elif base == 'libpthread.a':
      Log.Info('Not using IRT -- swapping private lib for libpthread')
      result_libs.append(pathtools.join(dname, 'libpthread_private.a'))
    elif base == 'libnacl_dyncode.a':
      Log.Info('Not using IRT -- swapping private lib for libnacl_dyncode')
      result_libs.append(pathtools.join(dname, 'libnacl_dyncode_private.a'))
    else:
      result_libs.append(l)
  return result_libs

def SplitLinkLine(inputs):
  """ Pull native objects (.o, .a) out of the input list.
      These need special handling since they cannot be
      encoded in the bitcode file.
      (NOTE: native .so files do not need special handling,
       because they can be encoded as dependencies in the bitcode)
  """
  normal = []
  native = []
  for f in inputs:
    if ldtools.IsFlag(f):
      normal.append(f)
    elif filetype.IsNativeArchive(f) or filetype.IsNativeObject(f):
      native.append(f)
    else:
      normal.append(f)
  return (normal, native)

def HasBitcodeInputs(inputs):
  for f in inputs:
    if ldtools.IsFlag(f):
      continue
    elif filetype.IsBitcodeObject(f) or filetype.IsBitcodeArchive(f):
      return True
  return False

def CheckInputsArch(inputs):
  count = 0
  for f in inputs:
    if ldtools.IsFlag(f):
      continue
    elif (filetype.IsBitcodeObject(f) or filetype.IsBitcodeDSO(f) or
          filetype.IsBitcodeArchive(f)):
      pass
    elif filetype.IsNative(f):
      ArchMerge(f, True)
    else:
      Log.Fatal("%s: Unexpected type of file for linking (%s)",
                pathtools.touser(f), FileType(f))
    count += 1

  if count == 0:
    Log.Fatal("no input files")

def DoLLVMPasses(pass_list):
  def Func(infile, outfile):
    filtered_list = [pass_option for pass_option in pass_list
                     if pass_option not in env.get('LLVM_PASSES_TO_DISABLE')]
    RunDriver('opt', filtered_list + [infile, '-o', outfile])
  return Func

def DoLTO(infile, outfile):
  opt_flags = env.get('OPT_FLAGS')
  RunDriver('opt', opt_flags + [ infile, '-o', outfile ])

def DoStrip(infile, outfile):
  strip_flags = env.get('STRIP_FLAGS')
  RunDriver('strip', strip_flags + [ infile, '-o', outfile ])

def DoTranslate(infile, outfile):
  args = env.get('TRANSLATE_FLAGS')
  args += ['-Wl,'+s for s in env.get('LD_FLAGS_NATIVE')]
  if infile:
    args += [infile]
  args += [s for s in env.get('NATIVE_OBJECTS')]
  args += ['-o', outfile]
  RunDriver('translate', args)

def LinkBC(inputs, output):
  '''Input: a bunch of bc/o/lib input files
     Output: a combined & optimized bitcode file
  '''
  # Produce combined bitcode file
  RunWithEnv('${RUN_BCLD}',
             inputs=inputs,
             output=output)

def get_help(unused_argv):
  return """Usage: pnacl-ld [options] <input files> -o <output>

Bitcode linker for PNaCl.  Similar to the binutils "ld" tool,
but links bitcode instead of native code.  Supports many of the
"ld" flags.

OPTIONS:

  -o <file>                   Set output file name
  -l LIBNAME                  Search for library LIBNAME
  -L DIRECTORY, --library-path DIRECTORY
                              Add DIRECTORY to library search path

  -r, --relocatable           Generate relocatable output

  -O<opt-level>               Optimize output file
  -M, --print-map             Print map file on standard output
  --whole-archive             Include all objects from following archives
  --no-whole-archive          Turn off --whole-archive
  -s, --strip-all             Strip all symbols
  -S, --strip-debug           Strip debugging symbols
  --undefined SYMBOL          Start with undefined reference to SYMBOL

  -help | -h                  Output this help.
"""
