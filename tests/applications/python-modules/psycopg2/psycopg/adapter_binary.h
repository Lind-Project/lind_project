/* adapter_binary.h - definition for the Binary type
 *
 * Copyright (C) 2003-2010 Federico Di Gregorio <fog@debian.org>
 *
 * This file is part of psycopg.
 *
 * psycopg2 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link this program with the OpenSSL library (or with
 * modified versions of OpenSSL that use the same license as OpenSSL),
 * and distribute linked combinations including the two.
 *
 * You must obey the GNU Lesser General Public License in all respects for
 * all of the code used other than OpenSSL.
 *
 * psycopg2 is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 */

#ifndef PSYCOPG_BINARY_H
#define PSYCOPG_BINARY_H 1

#ifdef __cplusplus
extern "C" {
#endif

extern HIDDEN PyTypeObject binaryType;

typedef struct {
    PyObject_HEAD

    PyObject *wrapped;
    PyObject *buffer;
    PyObject *conn;
} binaryObject;

#ifdef __cplusplus
}
#endif

#endif /* !defined(PSYCOPG_BINARY_H) */
