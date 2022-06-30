/* xid.h - definition for the psycopg Xid type
 *
 * Copyright (C) 2008  James Henstridge <james@jamesh.id.au>
 * Copyright (C) 2010  Daniele Varrazzo <daniele.varrazzo@gmail.com>
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

#ifndef PSYCOPG_XID_H
#define PSYCOPG_XID_H 1

extern HIDDEN PyTypeObject xidType;

typedef struct {
  PyObject_HEAD

  /* the Python-style three-part transaction ID */
  PyObject *format_id;
  PyObject *gtrid;
  PyObject *bqual;

  /* Additional information PostgreSQL exposes about prepared transactions */
  PyObject *prepared;
  PyObject *owner;
  PyObject *database;
} xidObject;

HIDDEN xidObject *xid_ensure(PyObject *oxid);
HIDDEN xidObject *xid_from_string(PyObject *s);
HIDDEN PyObject *xid_get_tid(xidObject *self);
HIDDEN PyObject *xid_recover(PyObject *conn);

#endif /* PSYCOPG_XID_H */
