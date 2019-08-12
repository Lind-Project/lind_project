/* include/lighttpd/config.h.  Generated from config.h.in by configure.  */
/* include/lighttpd/config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if you have the `accept4' function. */
/* #undef HAVE_ACCEPT4 */

/* with bzip2 */
/* #undef HAVE_BZIP */

/* Define to 1 if you have the <bzlib.h> header file. */
/* #undef HAVE_BZLIB_H */

/* Define to 1 if you have the `chroot' function. */
#define HAVE_CHROOT 1

/* crypt.h */
#define HAVE_CRYPT_H 1

/* crypt_r */
#define HAVE_CRYPT_R 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <ev.h> header file. */
/* #undef HAVE_EV_H */

/* Define to 1 if you have the <execinfo.h> header file. */
#define HAVE_EXECINFO_H 1

/* Define to 1 if you have the `getrlimit' function. */
/* #undef HAVE_GETRLIMIT */

/* Define to 1 if you have the `gmtime_r' function. */
#define HAVE_GMTIME_R 1

/* Define to 1 if you have the `inet_aton' function. */
#define HAVE_INET_ATON 1

/* Define to 1 if you have the `inet_ntop' function. */
#define HAVE_INET_NTOP 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Whether to enable IPv6 support */
#define HAVE_IPV6 1

/* Have libunwind support */
/* #undef HAVE_LIBUNWIND */

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* liblua */
/* #undef HAVE_LUA */

/* lua.h */
/* #undef HAVE_LUA_H */

/* Define to 1 if you have the `madvise' function. */
#define HAVE_MADVISE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Have openssl */
/* #undef HAVE_OPENSSL */

/* Define to 1 if you have the <openssl/ssl.h> header file. */
/* #undef HAVE_OPENSSL_SSL_H */

/* Define to 1 if you have the `posix_fadvise' function. */
/* #undef HAVE_POSIX_FADVISE */

/* Define to 1 if you have the `sendfile' function. */
/* #undef HAVE_SENDFILE */

/* Define to 1 if you have the `sendfile64' function. */
/* #undef HAVE_SENDFILE64 */

/* Define to 1 if you have the `sendfilev' function. */
/* #undef HAVE_SENDFILEV */

/* Whether we have struct sockaddr_storage */
/* #undef HAVE_SOCKADDR_STORAGE */

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/sendfile.h> header file. */
#define HAVE_SYS_SENDFILE_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `writev' function. */
#define HAVE_WRITEV 1

/* with zlib */
/* #undef HAVE_ZLIB */

/* Define to 1 if you have the <zlib.h> header file. */
/* #undef HAVE_ZLIB_H */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "lighttpd"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "contact@lighttpd.net"

/* Define to the full name of this package. */
#define PACKAGE_NAME "lighttpd"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "lighttpd 2.0.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "lighttpd"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.0.0"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* use sni */
/* #undef USE_SNI */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "2.0.0"

/* profiler */
/* #undef WITH_PROFILER */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */
