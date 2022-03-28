/* error.h - definition for the psycopg base Error type
 *
 * Copyright (C) 2013  Daniele Varrazzo <daniele.varrazzo@gmail.com>
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

#ifndef PSYCOPG_ERROR_H
#define PSYCOPG_ERROR_H 1

extern HIDDEN PyTypeObject errorType;

typedef struct {
    PyBaseExceptionObject exc;

    PyObject *pgerror;
    PyObject *pgcode;
    cursorObject *cursor;
    PyObject *pydecoder;
    PGresult *pgres;
} errorObject;

HIDDEN PyObject *error_text_from_chars(errorObject *self, const char *str);

#endif /* PSYCOPG_ERROR_H */
