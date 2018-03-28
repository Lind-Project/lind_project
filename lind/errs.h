/*
 * errs.h - exception wrappers
 *
 * AUTHOR: Joey Pabalinas <alyptik@protonmail.com>
 * See LICENSE.md file for copyright and license details.
 */

#ifndef ERRS_H
#define ERRS_H 1

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* errno, file, and lineno macros */
#define ESTR		strerror(errno), __FILE__, __LINE__
#define FSTR		__FILE__, __LINE__

/* warning macros */
#define WARN(FMT, ...) \
	do { fprintf(stderr, "`%s`: [%s:%u] " FMT "\n", ESTR, __VA_ARGS__); } while (0)
#define WARNX(FMT, ... ) \
	do { fprintf(stderr, "[%s:%u] " FMT "\n", FSTR, __VA_ARGS__); } while (0)
/* error macros */
#define ERR(FMT, ...) \
	do { fprintf(stderr, "`%s`: [%s:%u] " FMT "\n", ESTR, __VA_ARGS__); exit(EXIT_FAILURE); } while (0)
#define ERRX(FMT, ...) \
	do { fprintf(stderr, "[%s:%u] " FMT "\n", FSTR, __VA_ARGS__); exit(EXIT_FAILURE); } while (0)

#endif
