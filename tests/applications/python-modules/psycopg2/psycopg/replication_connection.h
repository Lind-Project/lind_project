/* replication_connection.h - definition for the psycopg replication connection type
 *
 * Copyright (C) 2015 Daniele Varrazzo <daniele.varrazzo@gmail.com>
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

#ifndef PSYCOPG_REPLICATION_CONNECTION_H
#define PSYCOPG_REPLICATION_CONNECTION_H 1

#include "psycopg/connection.h"

#ifdef __cplusplus
extern "C" {
#endif

extern HIDDEN PyTypeObject replicationConnectionType;

typedef struct replicationConnectionObject {
    connectionObject conn;

    long int type;
} replicationConnectionObject;

/* The funny constant values should help to avoid mixups with some
   commonly used numbers like 1 and 2. */
#define REPLICATION_PHYSICAL 12345678
#define REPLICATION_LOGICAL  87654321

extern HIDDEN PyObject *replicationPhysicalConst;
extern HIDDEN PyObject *replicationLogicalConst;

#ifdef __cplusplus
}
#endif

#endif /* !defined(PSYCOPG_REPLICATION_CONNECTION_H) */
