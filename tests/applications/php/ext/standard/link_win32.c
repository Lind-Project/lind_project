/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2018 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Pierre A. Joye <pierre@php.net>                              |
   +----------------------------------------------------------------------+
 */

#ifdef PHP_WIN32

#include "php.h"
#include "php_filestat.h"
#include "php_globals.h"

#include <WinBase.h>

#include <stdlib.h>

#include <string.h>
#if HAVE_PWD_H
#include "win32/pwd.h"
#endif

#if HAVE_GRP_H
#include "win32/grp.h"
#endif

#include <errno.h>
#include <ctype.h>

#include "php_link.h"
#include "php_string.h"

/*
TODO:
- Create php_readlink (done), php_link (done) and php_symlink (done) in win32/link.c
- Expose them (PHPAPI) so extensions developers can use them
- define link/readlink/symlink to their php_ equivalent and use them in ext/standard/link.c
- this file is then useless and we have a portable link API
*/

#ifndef VOLUME_NAME_NT
#define VOLUME_NAME_NT 0x2
#endif

#ifndef VOLUME_NAME_DOS
#define VOLUME_NAME_DOS 0x0
#endif

/* {{{ proto string readlink(string filename)
   Return the target of a symbolic link */
PHP_FUNCTION(readlink)
{
	char *link;
	ssize_t link_len;
	char target[MAXPATHLEN];

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "p", &link, &link_len) == FAILURE) {
		return;
	}

	if (OPENBASEDIR_CHECKPATH(link)) {
		RETURN_FALSE;
	}

	link_len = php_sys_readlink(link, target, MAXPATHLEN);
	if (link_len == -1) {
		php_error_docref(NULL, E_WARNING, "readlink failed to read the symbolic link (%s), error %d)", link, GetLastError());
		RETURN_FALSE;
	}
	RETURN_STRING(target);
}
/* }}} */

/* {{{ proto int linkinfo(string filename)
   Returns the st_dev field of the UNIX C stat structure describing the link */
PHP_FUNCTION(linkinfo)
{
	char *link;
	char *dirname;
	size_t link_len;
	zend_stat_t sb;
	int ret;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "p", &link, &link_len) == FAILURE) {
		return;
	}

	dirname = estrndup(link, link_len);
	php_dirname(dirname, link_len);

	if (php_check_open_basedir(dirname)) {
		efree(dirname);
		RETURN_FALSE;
	}

	ret = VCWD_STAT(link, &sb);
	if (ret == -1) {
		php_error_docref(NULL, E_WARNING, "%s", strerror(errno));
		efree(dirname);
		RETURN_LONG(Z_L(-1));
	}

	efree(dirname);
	RETURN_LONG((zend_long) sb.st_dev);
}
/* }}} */

/* {{{ proto int symlink(string target, string link)
   Create a symbolic link */
PHP_FUNCTION(symlink)
{
	char *topath, *frompath;
	size_t topath_len, frompath_len;
	int ret;
	char source_p[MAXPATHLEN];
	char dest_p[MAXPATHLEN];
	char dirname[MAXPATHLEN];
	size_t len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "pp", &topath, &topath_len, &frompath, &frompath_len) == FAILURE) {
		return;
	}

	if (!expand_filepath(frompath, source_p)) {
		php_error_docref(NULL, E_WARNING, "No such file or directory");
		RETURN_FALSE;
	}

	memcpy(dirname, source_p, sizeof(source_p));
	len = php_dirname(dirname, strlen(dirname));

	if (!expand_filepath_ex(topath, dest_p, dirname, len)) {
		php_error_docref(NULL, E_WARNING, "No such file or directory");
		RETURN_FALSE;
	}

	if (php_stream_locate_url_wrapper(source_p, NULL, STREAM_LOCATE_WRAPPERS_ONLY) ||
		php_stream_locate_url_wrapper(dest_p, NULL, STREAM_LOCATE_WRAPPERS_ONLY) )
	{
		php_error_docref(NULL, E_WARNING, "Unable to symlink to a URL");
		RETURN_FALSE;
	}

	if (OPENBASEDIR_CHECKPATH(dest_p)) {
		RETURN_FALSE;
	}

	if (OPENBASEDIR_CHECKPATH(source_p)) {
		RETURN_FALSE;
	}

	/* For the source, an expanded path must be used (in ZTS an other thread could have changed the CWD).
	 * For the target the exact string given by the user must be used, relative or not, existing or not.
	 * The target is relative to the link itself, not to the CWD. */
	ret = php_sys_symlink(topath, source_p);

	if (ret == -1) {
		php_error_docref(NULL, E_WARNING, "%s", strerror(errno));
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int link(string target, string link)
   Create a hard link */
PHP_FUNCTION(link)
{
	char *topath, *frompath;
	size_t topath_len, frompath_len;
	int ret;
	char source_p[MAXPATHLEN];
	char dest_p[MAXPATHLEN];

	/*First argument to link function is the target and hence should go to frompath
	  Second argument to link function is the link itself and hence should go to topath */
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &frompath, &frompath_len, &topath, &topath_len) == FAILURE) {
		return;
	}

	if (!expand_filepath(frompath, source_p) || !expand_filepath(topath, dest_p)) {
		php_error_docref(NULL, E_WARNING, "No such file or directory");
		RETURN_FALSE;
	}

	if (php_stream_locate_url_wrapper(source_p, NULL, STREAM_LOCATE_WRAPPERS_ONLY) ||
		php_stream_locate_url_wrapper(dest_p, NULL, STREAM_LOCATE_WRAPPERS_ONLY) )
	{
		php_error_docref(NULL, E_WARNING, "Unable to link to a URL");
		RETURN_FALSE;
	}

	if (OPENBASEDIR_CHECKPATH(source_p)) {
		RETURN_FALSE;
	}

	if (OPENBASEDIR_CHECKPATH(dest_p)) {
		RETURN_FALSE;
	}

#ifndef ZTS
	ret = php_sys_link(topath, frompath);
#else
	ret = php_sys_link(dest_p, source_p);
#endif
	if (ret == -1) {
		php_error_docref(NULL, E_WARNING, "%s", strerror(errno));
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
