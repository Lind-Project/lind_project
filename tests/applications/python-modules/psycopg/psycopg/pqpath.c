/* pqpath.c - single path into libpq
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

/* IMPORTANT NOTE: no function in this file do its own connection locking
   except for pg_execute and pq_fetch (that are somehow high-level). This means
   that all the other functions should be called while holding a lock to the
   connection.
*/

#define PSYCOPG_MODULE
#include "psycopg/psycopg.h"

#include "psycopg/pqpath.h"
#include "psycopg/connection.h"
#include "psycopg/cursor.h"
#include "psycopg/replication_cursor.h"
#include "psycopg/replication_message.h"
#include "psycopg/green.h"
#include "psycopg/typecast.h"
#include "psycopg/pgtypes.h"
#include "psycopg/error.h"

#include "psycopg/libpq_support.h"
#include "libpq-fe.h"

#ifdef _WIN32
/* select() */
#include <winsock2.h>
/* gettimeofday() */
#include "win32_support.h"
#endif

extern HIDDEN PyObject *psyco_DescriptionType;
extern HIDDEN const char *srv_isolevels[];
extern HIDDEN const char *srv_readonly[];
extern HIDDEN const char *srv_deferrable[];

/* Strip off the severity from a Postgres error message. */
static const char *
strip_severity(const char *msg)
{
    if (!msg)
        return NULL;

    if (strlen(msg) > 8 && (!strncmp(msg, "ERROR:  ", 8) ||
                            !strncmp(msg, "FATAL:  ", 8) ||
                            !strncmp(msg, "PANIC:  ", 8)))
        return &msg[8];
    else
        return msg;
}

/* Returns the Python exception corresponding to an SQLSTATE error
   code.  A list of error codes can be found at:

   http://www.postgresql.org/docs/current/static/errcodes-appendix.html */
BORROWED static PyObject *
exception_from_sqlstate(const char *sqlstate)
{
    switch (sqlstate[0]) {
    case '0':
        switch (sqlstate[1]) {
        case 'A': /* Class 0A - Feature Not Supported */
            return NotSupportedError;
        }
        break;
    case '2':
        switch (sqlstate[1]) {
        case '0': /* Class 20 - Case Not Found */
        case '1': /* Class 21 - Cardinality Violation */
            return ProgrammingError;
        case '2': /* Class 22 - Data Exception */
            return DataError;
        case '3': /* Class 23 - Integrity Constraint Violation */
            return IntegrityError;
        case '4': /* Class 24 - Invalid Cursor State */
        case '5': /* Class 25 - Invalid Transaction State */
            return InternalError;
        case '6': /* Class 26 - Invalid SQL Statement Name */
        case '7': /* Class 27 - Triggered Data Change Violation */
        case '8': /* Class 28 - Invalid Authorization Specification */
            return OperationalError;
        case 'B': /* Class 2B - Dependent Privilege Descriptors Still Exist */
        case 'D': /* Class 2D - Invalid Transaction Termination */
        case 'F': /* Class 2F - SQL Routine Exception */
            return InternalError;
        }
        break;
    case '3':
        switch (sqlstate[1]) {
        case '4': /* Class 34 - Invalid Cursor Name */
            return OperationalError;
        case '8': /* Class 38 - External Routine Exception */
        case '9': /* Class 39 - External Routine Invocation Exception */
        case 'B': /* Class 3B - Savepoint Exception */
            return InternalError;
        case 'D': /* Class 3D - Invalid Catalog Name */
        case 'F': /* Class 3F - Invalid Schema Name */
            return ProgrammingError;
        }
        break;
    case '4':
        switch (sqlstate[1]) {
        case '0': /* Class 40 - Transaction Rollback */
            return TransactionRollbackError;
        case '2': /* Class 42 - Syntax Error or Access Rule Violation */
        case '4': /* Class 44 - WITH CHECK OPTION Violation */
            return ProgrammingError;
        }
        break;
    case '5':
        /* Class 53 - Insufficient Resources
           Class 54 - Program Limit Exceeded
           Class 55 - Object Not In Prerequisite State
           Class 57 - Operator Intervention
           Class 58 - System Error (errors external to PostgreSQL itself) */
        if (!strcmp(sqlstate, "57014"))
            return QueryCanceledError;
        else
            return OperationalError;
    case 'F': /* Class F0 - Configuration File Error */
        return InternalError;
    case 'H': /* Class HV - Foreign Data Wrapper Error (SQL/MED) */
        return OperationalError;
    case 'P': /* Class P0 - PL/pgSQL Error */
        return InternalError;
    case 'X': /* Class XX - Internal Error */
        return InternalError;
    }
    /* return DatabaseError as a fallback */
    return DatabaseError;
}

/* pq_raise - raise a python exception of the right kind

   This function should be called while holding the GIL.

   The function passes the ownership of the pgres to the returned exception,
   where the pgres was the explicit argument or taken from the cursor.
   So, after calling it curs->pgres will be set to null */

RAISES static void
pq_raise(connectionObject *conn, cursorObject *curs, PGresult **pgres)
{
    PyObject *exc = NULL;
    const char *err = NULL;
    const char *err2 = NULL;
    const char *code = NULL;
    PyObject *pyerr = NULL;
    PyObject *pgerror = NULL, *pgcode = NULL;

    if (conn == NULL) {
        PyErr_SetString(DatabaseError,
            "psycopg went psychotic and raised a null error");
        return;
    }

    /* if the connection has somehow been broken, we mark the connection
       object as closed but requiring cleanup */
    if (conn->pgconn != NULL && PQstatus(conn->pgconn) == CONNECTION_BAD)
        conn->closed = 2;

    if (pgres == NULL && curs != NULL)
        pgres = &curs->pgres;

    if (pgres && *pgres) {
        err = PQresultErrorMessage(*pgres);
        if (err != NULL) {
            Dprintf("pq_raise: PQresultErrorMessage: err=%s", err);
            code = PQresultErrorField(*pgres, PG_DIAG_SQLSTATE);
        }
    }
    if (err == NULL) {
        err = PQerrorMessage(conn->pgconn);
        Dprintf("pq_raise: PQerrorMessage: err=%s", err);
    }

    /* if the is no error message we probably called pq_raise without reason:
       we need to set an exception anyway because the caller will probably
       raise and a meaningful message is better than an empty one.
       Note: it can happen without it being our error: see ticket #82 */
    if (err == NULL || err[0] == '\0') {
        PyErr_Format(DatabaseError,
            "error with status %s and no message from the libpq",
            PQresStatus(pgres == NULL ?
                PQstatus(conn->pgconn) : PQresultStatus(*pgres)));
        return;
    }

    /* Analyze the message and try to deduce the right exception kind
       (only if we got the SQLSTATE from the pgres, obviously) */
    if (code != NULL) {
        exc = exception_from_sqlstate(code);
    }
    else {
        /* Fallback if there is no exception code (reported happening e.g.
         * when the connection is closed). */
        exc = DatabaseError;
    }

    /* try to remove the initial "ERROR: " part from the postgresql error */
    err2 = strip_severity(err);
    Dprintf("pq_raise: err2=%s", err2);

    /* decode now the details of the error, because after psyco_set_error
     * decoding will fail.
     */
    if (!(pgerror = conn_text_from_chars(conn, err))) {
        /* we can't really handle an exception while handling this error
         * so just print it. */
        PyErr_Print();
        PyErr_Clear();
    }

    if (!(pgcode = conn_text_from_chars(conn, code))) {
        PyErr_Print();
        PyErr_Clear();
    }

    pyerr = psyco_set_error(exc, curs, err2);

    if (pyerr && PyObject_TypeCheck(pyerr, &errorType)) {
        errorObject *perr = (errorObject *)pyerr;

        Py_CLEAR(perr->pydecoder);
        Py_XINCREF(conn->pydecoder);
        perr->pydecoder = conn->pydecoder;

        Py_CLEAR(perr->pgerror);
        perr->pgerror = pgerror;
        pgerror = NULL;

        Py_CLEAR(perr->pgcode);
        perr->pgcode = pgcode;
        pgcode = NULL;

        CLEARPGRES(perr->pgres);
        if (pgres && *pgres) {
            perr->pgres = *pgres;
            *pgres = NULL;
        }
    }

    Py_XDECREF(pgerror);
    Py_XDECREF(pgcode);
}

/* pq_set_critical, pq_resolve_critical - manage critical errors

   this function is invoked when a PQexec() call returns NULL, meaning a
   critical condition like out of memory or lost connection. it save the error
   message and mark the connection as 'wanting cleanup'.

   both functions do not call any Py_*_ALLOW_THREADS macros.
   pq_resolve_critical should be called while holding the GIL. */

void
pq_set_critical(connectionObject *conn, const char *msg)
{
    if (msg == NULL)
        msg = PQerrorMessage(conn->pgconn);
    if (conn->critical) free(conn->critical);
    Dprintf("pq_set_critical: setting %s", msg);
    if (msg && msg[0] != '\0') conn->critical = strdup(msg);
    else conn->critical = NULL;
}

static void
pq_clear_critical(connectionObject *conn)
{
    /* sometimes we know that the notice analizer set a critical that
       was not really as such (like when raising an error for a delayed
       contraint violation. it would be better to analyze the notice
       or avoid the set-error-on-notice stuff at all but given that we
       can't, some functions at least clear the critical status after
       operations they know would result in a wrong critical to be set */
    Dprintf("pq_clear_critical: clearing %s", conn->critical);
    if (conn->critical) {
        free(conn->critical);
        conn->critical = NULL;
    }
}

/* return -1 if the exception is set (i.e. if conn->critical is set),
 * else 0 */
RAISES_NEG static int
pq_resolve_critical(connectionObject *conn, int close)
{
    Dprintf("pq_resolve_critical: resolving %s", conn->critical);

    if (conn->critical) {
        char *msg = &(conn->critical[6]);
        Dprintf("pq_resolve_critical: error = %s", msg);
        /* we can't use pq_raise because the error has already been cleared
           from the connection, so we just raise an OperationalError with the
           critical message */
        PyErr_SetString(OperationalError, msg);

        /* we don't want to destroy this connection but just close it */
        if (close == 1) conn_close(conn);

        /* remember to clear the critical! */
        pq_clear_critical(conn);

        return -1;
    }
    return 0;
}

/* pq_clear_async - clear the effects of a previous async query

   note that this function does block because it needs to wait for the full
   result sets of the previous query to clear them.

   this function does not call any Py_*_ALLOW_THREADS macros */

void
pq_clear_async(connectionObject *conn)
{
    PGresult *pgres;

    /* this will get all pending results (if the submitted query consisted of
       many parts, i.e. "select 1; select 2", there will be many) and also
       finalize asynchronous processing so the connection will be ready to
       accept another query */

    while ((pgres = PQgetResult(conn->pgconn)) != NULL) {
        Dprintf("pq_clear_async: clearing PGresult at %p", pgres);
        CLEARPGRES(pgres);
    }
    Py_CLEAR(conn->async_cursor);
}


/* pq_set_non_blocking - set the nonblocking status on a connection.

   Accepted arg values are 1 (nonblocking) and 0 (blocking).

   Return 0 if everything ok, else < 0 and set an exception.
 */
RAISES_NEG int
pq_set_non_blocking(connectionObject *conn, int arg)
{
    int ret = PQsetnonblocking(conn->pgconn, arg);
    if (0 != ret) {
        Dprintf("PQsetnonblocking(%d) FAILED", arg);
        PyErr_SetString(OperationalError, "PQsetnonblocking() failed");
        ret = -1;
    }
    return ret;
}


/* pg_execute_command_locked - execute a no-result query on a locked connection.

   This function should only be called on a locked connection without
   holding the global interpreter lock.

   On error, -1 is returned, and the pgres argument will hold the
   relevant result structure.

   The tstate parameter should be the pointer of the _save variable created by
   Py_BEGIN_ALLOW_THREADS: this enables the function to acquire and release
   again the GIL if needed, i.e. if a Python wait callback must be invoked.
 */
int
pq_execute_command_locked(connectionObject *conn, const char *query,
                          PGresult **pgres, char **error,
                          PyThreadState **tstate)
{
    int pgstatus, retvalue = -1;

    Dprintf("pq_execute_command_locked: pgconn = %p, query = %s",
            conn->pgconn, query);
    *error = NULL;

    if (!psyco_green()) {
        *pgres = PQexec(conn->pgconn, query);
    } else {
        PyEval_RestoreThread(*tstate);
        *pgres = psyco_exec_green(conn, query);
        *tstate = PyEval_SaveThread();
    }
    if (*pgres == NULL) {
        Dprintf("pq_execute_command_locked: PQexec returned NULL");
        PyEval_RestoreThread(*tstate);
        if (!PyErr_Occurred()) {
            const char *msg;
            msg = PQerrorMessage(conn->pgconn);
            if (msg && *msg) { *error = strdup(msg); }
        }
        *tstate = PyEval_SaveThread();
        goto cleanup;
    }

    pgstatus = PQresultStatus(*pgres);
    if (pgstatus != PGRES_COMMAND_OK ) {
        Dprintf("pq_execute_command_locked: result was not COMMAND_OK (%d)",
                pgstatus);
        goto cleanup;
    }

    retvalue = 0;
    CLEARPGRES(*pgres);

cleanup:
    return retvalue;
}

/* pq_complete_error: handle an error from pq_execute_command_locked()

   If pq_execute_command_locked() returns -1, this function should be
   called to convert the result to a Python exception.

   This function should be called while holding the global interpreter
   lock.
 */
RAISES void
pq_complete_error(connectionObject *conn, PGresult **pgres, char **error)
{
    Dprintf("pq_complete_error: pgconn = %p, pgres = %p, error = %s",
            conn->pgconn, *pgres, *error ? *error : "(null)");
    if (*pgres != NULL) {
        pq_raise(conn, NULL, pgres);
        /* now *pgres is null */
    }
    else {
        if (*error != NULL) {
            PyErr_SetString(OperationalError, *error);
        } else {
            PyErr_SetString(OperationalError, "unknown error");
        }
        /* Trivia: with a broken socket connection PQexec returns NULL, so we
         * end up here. With a TCP connection we get a pgres with an error
         * instead, and the connection gets closed in the pq_raise call above
         * (see ticket #196)
         */
        if (CONNECTION_BAD == PQstatus(conn->pgconn)) {
            conn->closed = 2;
        }
    }

    if (*error) {
        free(*error);
        *error = NULL;
    }
}


/* pq_begin_locked - begin a transaction, if necessary

   This function should only be called on a locked connection without
   holding the global interpreter lock.

   On error, -1 is returned, and the pgres argument will hold the
   relevant result structure.
 */
int
pq_begin_locked(connectionObject *conn, PGresult **pgres, char **error,
                PyThreadState **tstate)
{
    const size_t bufsize = 256;
    char buf[256];  /* buf size must be same as bufsize */
    int result;

    Dprintf("pq_begin_locked: pgconn = %p, autocommit = %d, status = %d",
            conn->pgconn, conn->autocommit, conn->status);

    if (conn->autocommit || conn->status != CONN_STATUS_READY) {
        Dprintf("pq_begin_locked: transaction in progress");
        return 0;
    }

    if (conn->isolevel == ISOLATION_LEVEL_DEFAULT
            && conn->readonly == STATE_DEFAULT
            && conn->deferrable == STATE_DEFAULT) {
        strcpy(buf, "BEGIN");
    }
    else {
        snprintf(buf, bufsize,
            conn->server_version >= 80000 ?
                "BEGIN%s%s%s%s" : "BEGIN;SET TRANSACTION%s%s%s%s",
            (conn->isolevel >= 1 && conn->isolevel <= 4)
                ? " ISOLATION LEVEL " : "",
            (conn->isolevel >= 1 && conn->isolevel <= 4)
                ? srv_isolevels[conn->isolevel] : "",
            srv_readonly[conn->readonly],
            srv_deferrable[conn->deferrable]);
    }

    result = pq_execute_command_locked(conn, buf, pgres, error, tstate);
    if (result == 0)
        conn->status = CONN_STATUS_BEGIN;

    return result;
}

/* pq_commit - send an END, if necessary

   This function should be called while holding the global interpreter
   lock.
*/

int
pq_commit(connectionObject *conn)
{
    int retvalue = -1;
    PGresult *pgres = NULL;
    char *error = NULL;

    Py_BEGIN_ALLOW_THREADS;
    pthread_mutex_lock(&conn->lock);

    Dprintf("pq_commit: pgconn = %p, autocommit = %d, status = %d",
            conn->pgconn, conn->autocommit, conn->status);

    if (conn->autocommit || conn->status != CONN_STATUS_BEGIN) {
        Dprintf("pq_commit: no transaction to commit");
        retvalue = 0;
    }
    else {
        conn->mark += 1;
        retvalue = pq_execute_command_locked(conn, "COMMIT", &pgres, &error, &_save);
    }

    Py_BLOCK_THREADS;
    conn_notice_process(conn);
    Py_UNBLOCK_THREADS;

    /* Even if an error occurred, the connection will be rolled back,
       so we unconditionally set the connection status here. */
    conn->status = CONN_STATUS_READY;

    pthread_mutex_unlock(&conn->lock);
    Py_END_ALLOW_THREADS;

    if (retvalue < 0)
        pq_complete_error(conn, &pgres, &error);

    return retvalue;
}

RAISES_NEG int
pq_abort_locked(connectionObject *conn, PGresult **pgres, char **error,
                PyThreadState **tstate)
{
    int retvalue = -1;

    Dprintf("pq_abort_locked: pgconn = %p, autocommit = %d, status = %d",
            conn->pgconn, conn->autocommit, conn->status);

    if (conn->autocommit || conn->status != CONN_STATUS_BEGIN) {
        Dprintf("pq_abort_locked: no transaction to abort");
        return 0;
    }

    conn->mark += 1;
    retvalue = pq_execute_command_locked(conn, "ROLLBACK", pgres, error, tstate);
    if (retvalue == 0)
        conn->status = CONN_STATUS_READY;

    return retvalue;
}

/* pq_abort - send an ABORT, if necessary

   This function should be called while holding the global interpreter
   lock. */

RAISES_NEG int
pq_abort(connectionObject *conn)
{
    int retvalue = -1;
    PGresult *pgres = NULL;
    char *error = NULL;

    Dprintf("pq_abort: pgconn = %p, autocommit = %d, status = %d",
            conn->pgconn, conn->autocommit, conn->status);

    Py_BEGIN_ALLOW_THREADS;
    pthread_mutex_lock(&conn->lock);

    retvalue = pq_abort_locked(conn, &pgres, &error, &_save);

    Py_BLOCK_THREADS;
    conn_notice_process(conn);
    Py_UNBLOCK_THREADS;

    pthread_mutex_unlock(&conn->lock);
    Py_END_ALLOW_THREADS;

    if (retvalue < 0)
        pq_complete_error(conn, &pgres, &error);

    return retvalue;
}

/* pq_reset - reset the connection

   This function should be called while holding the global interpreter
   lock.

   The _locked version of this function should be called on a locked
   connection without holding the global interpreter lock.
*/

RAISES_NEG int
pq_reset_locked(connectionObject *conn, PGresult **pgres, char **error,
                PyThreadState **tstate)
{
    int retvalue = -1;

    Dprintf("pq_reset_locked: pgconn = %p, autocommit = %d, status = %d",
            conn->pgconn, conn->autocommit, conn->status);

    conn->mark += 1;

    if (!conn->autocommit && conn->status == CONN_STATUS_BEGIN) {
        retvalue = pq_execute_command_locked(conn, "ABORT", pgres, error, tstate);
        if (retvalue != 0) return retvalue;
    }

    if (conn->server_version >= 80300) {
        retvalue = pq_execute_command_locked(conn, "DISCARD ALL", pgres, error, tstate);
        if (retvalue != 0) return retvalue;
    }
    else {
        retvalue = pq_execute_command_locked(conn, "RESET ALL", pgres, error, tstate);
        if (retvalue != 0) return retvalue;

        retvalue = pq_execute_command_locked(conn,
            "SET SESSION AUTHORIZATION DEFAULT", pgres, error, tstate);
        if (retvalue != 0) return retvalue;
    }

    /* should set the tpc xid to null: postponed until we get the GIL again */
    conn->status = CONN_STATUS_READY;

    return retvalue;
}

int
pq_reset(connectionObject *conn)
{
    int retvalue = -1;
    PGresult *pgres = NULL;
    char *error = NULL;

    Dprintf("pq_reset: pgconn = %p, autocommit = %d, status = %d",
            conn->pgconn, conn->autocommit, conn->status);

    Py_BEGIN_ALLOW_THREADS;
    pthread_mutex_lock(&conn->lock);

    retvalue = pq_reset_locked(conn, &pgres, &error, &_save);

    Py_BLOCK_THREADS;
    conn_notice_process(conn);
    Py_UNBLOCK_THREADS;

    pthread_mutex_unlock(&conn->lock);
    Py_END_ALLOW_THREADS;

    if (retvalue < 0) {
        pq_complete_error(conn, &pgres, &error);
    }
    else {
        Py_CLEAR(conn->tpc_xid);
    }
    return retvalue;
}


/* Get a session parameter.
 *
 * The function should be called on a locked connection without
 * holding the GIL.
 *
 * The result is a new string allocated with malloc.
 */

char *
pq_get_guc_locked(
    connectionObject *conn, const char *param,
    PGresult **pgres, char **error, PyThreadState **tstate)
{
    char query[256];
    int size;
    char *rv = NULL;

    Dprintf("pq_get_guc_locked: reading %s", param);

    size = PyOS_snprintf(query, sizeof(query), "SHOW %s", param);
    if (size < 0 || (size_t)size >= sizeof(query)) {
        *error = strdup("SHOW: query too large");
        goto cleanup;
    }

    Dprintf("pq_get_guc_locked: pgconn = %p, query = %s", conn->pgconn, query);

    *error = NULL;
    if (!psyco_green()) {
        *pgres = PQexec(conn->pgconn, query);
    } else {
        PyEval_RestoreThread(*tstate);
        *pgres = psyco_exec_green(conn, query);
        *tstate = PyEval_SaveThread();
    }

    if (*pgres == NULL) {
        Dprintf("pq_get_guc_locked: PQexec returned NULL");
        PyEval_RestoreThread(*tstate);
        if (!PyErr_Occurred()) {
            const char *msg;
            msg = PQerrorMessage(conn->pgconn);
            if (msg && *msg) { *error = strdup(msg); }
        }
        *tstate = PyEval_SaveThread();
        goto cleanup;
    }
    if (PQresultStatus(*pgres) != PGRES_TUPLES_OK) {
        Dprintf("pq_get_guc_locked: result was not TUPLES_OK (%d)",
                PQresultStatus(*pgres));
        goto cleanup;
    }

    rv = strdup(PQgetvalue(*pgres, 0, 0));
    CLEARPGRES(*pgres);

cleanup:
    return rv;
}

/* Set a session parameter.
 *
 * The function should be called on a locked connection without
 * holding the GIL
 */

int
pq_set_guc_locked(
    connectionObject *conn, const char *param, const char *value,
    PGresult **pgres, char **error, PyThreadState **tstate)
{
    char query[256];
    int size;
    int rv = -1;

    Dprintf("pq_set_guc_locked: setting %s to %s", param, value);

    if (0 == strcmp(value, "default")) {
        size = PyOS_snprintf(query, sizeof(query),
            "SET %s TO DEFAULT", param);
    }
    else {
        size = PyOS_snprintf(query, sizeof(query),
            "SET %s TO '%s'", param, value);
    }
    if (size < 0 || (size_t)size >= sizeof(query)) {
        *error = strdup("SET: query too large");
    }

    rv = pq_execute_command_locked(conn, query, pgres, error, tstate);

    return rv;
}

/* Call one of the PostgreSQL tpc-related commands.
 *
 * This function should only be called on a locked connection without
 * holding the global interpreter lock. */

int
pq_tpc_command_locked(connectionObject *conn, const char *cmd, const char *tid,
                  PGresult **pgres, char **error, PyThreadState **tstate)
{
    int rv = -1;
    char *etid = NULL, *buf = NULL;
    Py_ssize_t buflen;

    Dprintf("_pq_tpc_command: pgconn = %p, command = %s",
            conn->pgconn, cmd);

    conn->mark += 1;

    PyEval_RestoreThread(*tstate);

    /* convert the xid into the postgres transaction_id and quote it. */
    if (!(etid = psycopg_escape_string(conn, tid, -1, NULL, NULL)))
    { goto exit; }

    /* prepare the command to the server */
    buflen = 2 + strlen(cmd) + strlen(etid); /* add space, zero */
    if (!(buf = PyMem_Malloc(buflen))) {
        PyErr_NoMemory();
        goto exit;
    }
    if (0 > PyOS_snprintf(buf, buflen, "%s %s", cmd, etid)) { goto exit; }

    /* run the command and let it handle the error cases */
    *tstate = PyEval_SaveThread();
    rv = pq_execute_command_locked(conn, buf, pgres, error, tstate);
    PyEval_RestoreThread(*tstate);

exit:
    PyMem_Free(buf);
    PyMem_Free(etid);

    *tstate = PyEval_SaveThread();
    return rv;
}


/* pq_is_busy - consume input and return connection status

   a status of 1 means that a call to pq_fetch will block, while a status of 0
   means that there is data available to be collected. -1 means an error, the
   exception will be set accordingly.

   this function locks the connection object
   this function call Py_*_ALLOW_THREADS macros */

int
pq_is_busy(connectionObject *conn)
{
    int res;
    Dprintf("pq_is_busy: consuming input");

    Py_BEGIN_ALLOW_THREADS;
    pthread_mutex_lock(&(conn->lock));

    if (PQconsumeInput(conn->pgconn) == 0) {
        Dprintf("pq_is_busy: PQconsumeInput() failed");
        pthread_mutex_unlock(&(conn->lock));
        Py_BLOCK_THREADS;

        /* if the libpq says pgconn is lost, close the py conn */
        if (CONNECTION_BAD == PQstatus(conn->pgconn)) {
            conn->closed = 2;
        }

        PyErr_SetString(OperationalError, PQerrorMessage(conn->pgconn));
        return -1;
    }

    res = PQisBusy(conn->pgconn);

    Py_BLOCK_THREADS;
    conn_notifies_process(conn);
    conn_notice_process(conn);
    Py_UNBLOCK_THREADS;

    pthread_mutex_unlock(&(conn->lock));
    Py_END_ALLOW_THREADS;

    return res;
}

/* pq_is_busy_locked - equivalent to pq_is_busy but we already have the lock
 *
 * The function should be called with the lock and holding the GIL.
 */

int
pq_is_busy_locked(connectionObject *conn)
{
    Dprintf("pq_is_busy_locked: consuming input");

    if (PQconsumeInput(conn->pgconn) == 0) {
        Dprintf("pq_is_busy_locked: PQconsumeInput() failed");

        /* if the libpq says pgconn is lost, close the py conn */
        if (CONNECTION_BAD == PQstatus(conn->pgconn)) {
            conn->closed = 2;
        }

        PyErr_SetString(OperationalError, PQerrorMessage(conn->pgconn));
        return -1;
    }

    /* notices and notifies will be processed at the end of the loop we are in
     * (async reading) by pq_fetch. */

    return PQisBusy(conn->pgconn);
}

/* pq_flush - flush output and return connection status

   a status of 1 means that a some data is still pending to be flushed, while a
   status of 0 means that there is no data waiting to be sent. -1 means an
   error and an exception will be set accordingly.

   this function locks the connection object
   this function call Py_*_ALLOW_THREADS macros */

int
pq_flush(connectionObject *conn)
{
    int res;

    Dprintf("pq_flush: flushing output");

    Py_BEGIN_ALLOW_THREADS;
    pthread_mutex_lock(&(conn->lock));
    res = PQflush(conn->pgconn);
    pthread_mutex_unlock(&(conn->lock));
    Py_END_ALLOW_THREADS;

    return res;
}

/* pq_execute - execute a query, possibly asynchronously
 *
 * With no_result an eventual query result is discarded.
 * Currently only used to implement cursor.executemany().
 *
 * This function locks the connection object
 * This function call Py_*_ALLOW_THREADS macros
*/

RAISES_NEG int
pq_execute(cursorObject *curs, const char *query, int async, int no_result, int no_begin)
{
    PGresult *pgres = NULL;
    char *error = NULL;
    int async_status = ASYNC_WRITE;

    /* if the status of the connection is critical raise an exception and
       definitely close the connection */
    if (curs->conn->critical) {
        return pq_resolve_critical(curs->conn, 1);
    }

    /* check status of connection, raise error if not OK */
    if (PQstatus(curs->conn->pgconn) != CONNECTION_OK) {
        Dprintf("pq_execute: connection NOT OK");
        PyErr_SetString(OperationalError, PQerrorMessage(curs->conn->pgconn));
        return -1;
    }
    Dprintf("pq_execute: pg connection at %p OK", curs->conn->pgconn);

    Py_BEGIN_ALLOW_THREADS;
    pthread_mutex_lock(&(curs->conn->lock));

    if (!no_begin && pq_begin_locked(curs->conn, &pgres, &error, &_save) < 0) {
        pthread_mutex_unlock(&(curs->conn->lock));
        Py_BLOCK_THREADS;
        pq_complete_error(curs->conn, &pgres, &error);
        return -1;
    }

    if (async == 0) {
        CLEARPGRES(curs->pgres);
        Dprintf("pq_execute: executing SYNC query: pgconn = %p", curs->conn->pgconn);
        Dprintf("    %-.200s", query);
        if (!psyco_green()) {
            curs->pgres = PQexec(curs->conn->pgconn, query);
        }
        else {
            Py_BLOCK_THREADS;
            curs->pgres = psyco_exec_green(curs->conn, query);
            Py_UNBLOCK_THREADS;
        }

        /* don't let pgres = NULL go to pq_fetch() */
        if (curs->pgres == NULL) {
            pthread_mutex_unlock(&(curs->conn->lock));
            Py_BLOCK_THREADS;
            if (!PyErr_Occurred()) {
                PyErr_SetString(OperationalError,
                                PQerrorMessage(curs->conn->pgconn));
            }
            return -1;
        }

        /* Process notifies here instead of when fetching the tuple as we are
         * into the same critical section that received the data. Without this
         * care, reading notifies may disrupt other thread communications.
         * (as in ticket #55). */
        Py_BLOCK_THREADS;
        conn_notifies_process(curs->conn);
        conn_notice_process(curs->conn);
        Py_UNBLOCK_THREADS;
    }

    else if (async == 1) {
        int ret;

        Dprintf("pq_execute: executing ASYNC query: pgconn = %p", curs->conn->pgconn);
        Dprintf("    %-.200s", query);

        CLEARPGRES(curs->pgres);
        if (PQsendQuery(curs->conn->pgconn, query) == 0) {
            pthread_mutex_unlock(&(curs->conn->lock));
            Py_BLOCK_THREADS;
            PyErr_SetString(OperationalError,
                            PQerrorMessage(curs->conn->pgconn));
            return -1;
        }
        Dprintf("pq_execute: async query sent to backend");

        ret = PQflush(curs->conn->pgconn);
        if (ret == 0) {
            /* the query got fully sent to the server */
            Dprintf("pq_execute: query got flushed immediately");
            /* the async status will be ASYNC_READ */
            async_status = ASYNC_READ;
        }
        else if (ret == 1) {
            /* not all of the query got sent to the server */
            async_status = ASYNC_WRITE;
        }
        else {
            /* there was an error */
            pthread_mutex_unlock(&(curs->conn->lock));
            Py_BLOCK_THREADS;
            PyErr_SetString(OperationalError,
                            PQerrorMessage(curs->conn->pgconn));
            return -1;
        }
    }

    pthread_mutex_unlock(&(curs->conn->lock));
    Py_END_ALLOW_THREADS;

    /* if the execute was sync, we call pq_fetch() immediately,
       to respect the old DBAPI-2.0 compatible behaviour */
    if (async == 0) {
        Dprintf("pq_execute: entering synchronous DBAPI compatibility mode");
        if (pq_fetch(curs, no_result) < 0) return -1;
    }
    else {
        PyObject *tmp;
        curs->conn->async_status = async_status;
        curs->conn->async_cursor = tmp = PyWeakref_NewRef((PyObject *)curs, NULL);
        if (!tmp) {
            /* weakref creation failed */
            return -1;
        }
    }

    return 1-async;
}

/* send an async query to the backend.
 *
 * Return 1 if command succeeded, else 0.
 *
 * The function should be called helding the connection lock and the GIL.
 */
int
pq_send_query(connectionObject *conn, const char *query)
{
    int rv;

    Dprintf("pq_send_query: sending ASYNC query:");
    Dprintf("    %-.200s", query);

    if (0 == (rv = PQsendQuery(conn->pgconn, query))) {
        Dprintf("pq_send_query: error: %s", PQerrorMessage(conn->pgconn));
    }

    return rv;
}

/* Return the last result available on the connection.
 *
 * The function will block only if a command is active and the
 * necessary response data has not yet been read by PQconsumeInput.
 *
 * The result should be disposed using PQclear()
 */
PGresult *
pq_get_last_result(connectionObject *conn)
{
    PGresult *result = NULL, *res;

    /* Read until PQgetResult gives a NULL */
    while (NULL != (res = PQgetResult(conn->pgconn))) {
        if (result) {
            /* TODO too bad: we are discarding results from all the queries
             * except the last. We could have populated `nextset()` with it
             * but it would be an incompatible change (apps currently issue
             * groups of queries expecting to receive the last result: they
             * would start receiving the first instead). */
            PQclear(result);
        }
        result = res;

        /* After entering copy both mode, libpq will make a phony
         * PGresult for us every time we query for it, so we need to
         * break out of this endless loop. */
        if (PQresultStatus(result) == PGRES_COPY_BOTH) {
            break;
        }
    }

    return result;
}

/* pq_fetch - fetch data after a query

   this function locks the connection object
   this function call Py_*_ALLOW_THREADS macros

   return value:
     -1 - some error occurred while calling libpq
      0 - no result from the backend but no libpq errors
      1 - result from backend (possibly data is ready)
*/

RAISES_NEG static int
_pq_fetch_tuples(cursorObject *curs)
{
    int i, *dsize = NULL;
    int pgnfields;
    int pgbintuples;
    int rv = -1;
    PyObject *description = NULL;
    PyObject *casts = NULL;

    Py_BEGIN_ALLOW_THREADS;
    pthread_mutex_lock(&(curs->conn->lock));
    Py_END_ALLOW_THREADS;

    pgnfields = PQnfields(curs->pgres);
    pgbintuples = PQbinaryTuples(curs->pgres);

    curs->notuples = 0;

    /* create the tuple for description and typecasting */
    Py_CLEAR(curs->description);
    Py_CLEAR(curs->casts);
    if (!(description = PyTuple_New(pgnfields))) { goto exit; }
    if (!(casts = PyTuple_New(pgnfields))) { goto exit; }
    curs->columns = pgnfields;

    /* calculate the display size for each column (cpu intensive, can be
       switched off at configuration time) */
#ifdef PSYCOPG_DISPLAY_SIZE
    if (!(dsize = PyMem_New(int, pgnfields))) {
        PyErr_NoMemory();
        goto exit;
    }
    Py_BEGIN_ALLOW_THREADS;
    if (dsize != NULL) {
        int j, len;
        for (i=0; i < pgnfields; i++) {
            dsize[i] = -1;
        }
        for (j = 0; j < curs->rowcount; j++) {
            for (i = 0; i < pgnfields; i++) {
                len = PQgetlength(curs->pgres, j, i);
                if (len > dsize[i]) dsize[i] = len;
            }
        }
    }
    Py_END_ALLOW_THREADS;
#endif

    /* calculate various parameters and typecasters */
    for (i = 0; i < pgnfields; i++) {
        Oid ftype = PQftype(curs->pgres, i);
        int fsize = PQfsize(curs->pgres, i);
        int fmod =  PQfmod(curs->pgres, i);

        PyObject *dtitem = NULL;
        PyObject *type = NULL;
        PyObject *cast = NULL;

        if (!(dtitem = PyTuple_New(7))) { goto exit; }

        /* fill the right cast function by accessing three different dictionaries:
           - the per-cursor dictionary, if available (can be NULL or None)
           - the per-connection dictionary (always exists but can be null)
           - the global dictionary (at module level)
           if we get no defined cast use the default one */

        if (!(type = PyInt_FromLong(ftype))) {
            goto err_for;
        }
        Dprintf("_pq_fetch_tuples: looking for cast %d:", ftype);
        cast = curs_get_cast(curs, type);

        /* else if we got binary tuples and if we got a field that
           is binary use the default cast
           FIXME: what the hell am I trying to do here? This just can't work..
        */
        if (pgbintuples && cast == psyco_default_binary_cast) {
            Dprintf("_pq_fetch_tuples: Binary cursor and "
                    "binary field: %i using default cast",
                    PQftype(curs->pgres,i));
            cast = psyco_default_cast;
        }

        Dprintf("_pq_fetch_tuples: using cast at %p for type %d",
                cast, PQftype(curs->pgres,i));
        Py_INCREF(cast);
        PyTuple_SET_ITEM(casts, i, cast);

        /* 1/ fill the other fields */
        {
            PyObject *tmp;
            if (!(tmp = conn_text_from_chars(
                    curs->conn, PQfname(curs->pgres, i)))) {
                goto err_for;
            }
            PyTuple_SET_ITEM(dtitem, 0, tmp);
        }
        PyTuple_SET_ITEM(dtitem, 1, type);
        type = NULL;

        /* 2/ display size is the maximum size of this field result tuples. */
        if (dsize && dsize[i] >= 0) {
            PyObject *tmp;
            if (!(tmp = PyInt_FromLong(dsize[i]))) { goto err_for; }
            PyTuple_SET_ITEM(dtitem, 2, tmp);
        }
        else {
            Py_INCREF(Py_None);
            PyTuple_SET_ITEM(dtitem, 2, Py_None);
        }

        /* 3/ size on the backend */
        if (fmod > 0) fmod = fmod - sizeof(int);
        if (fsize == -1) {
            if (ftype == NUMERICOID) {
                PyObject *tmp;
                if (!(tmp = PyInt_FromLong((fmod >> 16)))) { goto err_for; }
                PyTuple_SET_ITEM(dtitem, 3, tmp);
            }
            else { /* If variable length record, return maximum size */
                PyObject *tmp;
                if (!(tmp = PyInt_FromLong(fmod))) { goto err_for; }
                PyTuple_SET_ITEM(dtitem, 3, tmp);
            }
        }
        else {
            PyObject *tmp;
            if (!(tmp = PyInt_FromLong(fsize))) { goto err_for; }
            PyTuple_SET_ITEM(dtitem, 3, tmp);
        }

        /* 4,5/ scale and precision */
        if (ftype == NUMERICOID) {
            PyObject *tmp;

            if (!(tmp = PyInt_FromLong((fmod >> 16) & 0xFFFF))) {
                goto err_for;
            }
            PyTuple_SET_ITEM(dtitem, 4, tmp);

            if (!(tmp = PyInt_FromLong(fmod & 0xFFFF))) {
                PyTuple_SET_ITEM(dtitem, 5, tmp);
            }
            PyTuple_SET_ITEM(dtitem, 5, tmp);
        }
        else {
            Py_INCREF(Py_None);
            PyTuple_SET_ITEM(dtitem, 4, Py_None);
            Py_INCREF(Py_None);
            PyTuple_SET_ITEM(dtitem, 5, Py_None);
        }

        /* 6/ FIXME: null_ok??? */
        Py_INCREF(Py_None);
        PyTuple_SET_ITEM(dtitem, 6, Py_None);

        /* Convert into a namedtuple if available */
        if (Py_None != psyco_DescriptionType) {
            PyObject *tmp = dtitem;
            dtitem = PyObject_CallObject(psyco_DescriptionType, tmp);
            Py_DECREF(tmp);
            if (NULL == dtitem) { goto err_for; }
        }

        PyTuple_SET_ITEM(description, i, dtitem);
        dtitem = NULL;

        continue;

err_for:
        Py_XDECREF(type);
        Py_XDECREF(dtitem);
        goto exit;
    }

    curs->description = description; description = NULL;
    curs->casts = casts; casts = NULL;
    rv = 0;

exit:
    PyMem_Free(dsize);
    Py_XDECREF(description);
    Py_XDECREF(casts);

    Py_BEGIN_ALLOW_THREADS;
    pthread_mutex_unlock(&(curs->conn->lock));
    Py_END_ALLOW_THREADS;

    return rv;
}

void
_read_rowcount(cursorObject *curs)
{
    const char *rowcount;

    rowcount = PQcmdTuples(curs->pgres);
    Dprintf("_read_rowcount: PQcmdTuples = %s", rowcount);
    if (!rowcount || !rowcount[0]) {
        curs->rowcount = -1;
    } else {
        curs->rowcount = atol(rowcount);
    }
}

static int
_pq_copy_in_v3(cursorObject *curs)
{
    /* COPY FROM implementation when protocol 3 is available: this function
       uses the new PQputCopyData() and can detect errors and set the correct
       exception */
    PyObject *o, *func = NULL, *size = NULL;
    Py_ssize_t length = 0;
    int res, error = 0;

    if (!curs->copyfile) {
        PyErr_SetString(ProgrammingError,
            "can't execute COPY FROM: use the copy_from() method instead");
        error = 1;
        goto exit;
    }

    if (!(func = PyObject_GetAttrString(curs->copyfile, "read"))) {
        Dprintf("_pq_copy_in_v3: can't get o.read");
        error = 1;
        goto exit;
    }
    if (!(size = PyInt_FromSsize_t(curs->copysize))) {
        Dprintf("_pq_copy_in_v3: can't get int from copysize");
        error = 1;
        goto exit;
    }

    while (1) {
        if (!(o = PyObject_CallFunctionObjArgs(func, size, NULL))) {
            Dprintf("_pq_copy_in_v3: read() failed");
            error = 1;
            break;
        }

        /* a file may return unicode if implements io.TextIOBase */
        if (PyUnicode_Check(o)) {
            PyObject *tmp;
            if (!(tmp = conn_encode(curs->conn, o))) {
                Dprintf("_pq_copy_in_v3: encoding() failed");
                error = 1;
                break;
            }
            Py_DECREF(o);
            o = tmp;
        }

        if (!Bytes_Check(o)) {
            Dprintf("_pq_copy_in_v3: got %s instead of bytes",
                Py_TYPE(o)->tp_name);
            error = 1;
            break;
        }

        if (0 == (length = Bytes_GET_SIZE(o))) {
            break;
        }
        if (length > INT_MAX) {
            Dprintf("_pq_copy_in_v3: bad length: " FORMAT_CODE_PY_SSIZE_T,
                length);
            error = 1;
            break;
        }

        Py_BEGIN_ALLOW_THREADS;
        res = PQputCopyData(curs->conn->pgconn, Bytes_AS_STRING(o),
            /* Py_ssize_t->int cast was validated above */
            (int) length);
        Dprintf("_pq_copy_in_v3: sent " FORMAT_CODE_PY_SSIZE_T " bytes of data; res = %d",
            length, res);

        if (res == 0) {
            /* FIXME: in theory this should not happen but adding a check
               here would be a nice idea */
        }
        else if (res == -1) {
            Dprintf("_pq_copy_in_v3: PQerrorMessage = %s",
                PQerrorMessage(curs->conn->pgconn));
            error = 2;
        }
        Py_END_ALLOW_THREADS;

        if (error == 2) break;

        Py_DECREF(o);
    }

    Py_XDECREF(o);

    Dprintf("_pq_copy_in_v3: error = %d", error);

    /* 0 means that the copy went well, 2 that there was an error on the
       backend: in both cases we'll get the error message from the PQresult */
    if (error == 0)
        res = PQputCopyEnd(curs->conn->pgconn, NULL);
    else if (error == 2)
        res = PQputCopyEnd(curs->conn->pgconn, "error in PQputCopyData() call");
    else {
        char buf[1024];
        strcpy(buf, "error in .read() call");
        if (PyErr_Occurred()) {
            PyObject *t, *ex, *tb;
            PyErr_Fetch(&t, &ex, &tb);
            if (ex) {
                PyObject *str;
                str = PyObject_Str(ex);
                str = psycopg_ensure_bytes(str);
                if (str) {
                    PyOS_snprintf(buf, sizeof(buf),
                        "error in .read() call: %s %s",
                        ((PyTypeObject *)t)->tp_name, Bytes_AsString(str));
                    Py_DECREF(str);
                }
            }
            /* Clear the Py exception: it will be re-raised from the libpq */
            Py_XDECREF(t);
            Py_XDECREF(ex);
            Py_XDECREF(tb);
            PyErr_Clear();
        }
        res = PQputCopyEnd(curs->conn->pgconn, buf);
    }

    CLEARPGRES(curs->pgres);

    Dprintf("_pq_copy_in_v3: copy ended; res = %d", res);

    /* if the result is -1 we should not even try to get a result from the
       because that will lock the current thread forever */
    if (res == -1) {
        pq_raise(curs->conn, curs, NULL);
        /* FIXME: pq_raise check the connection but for some reason even
           if the error message says "server closed the connection unexpectedly"
           the status returned by PQstatus is CONNECTION_OK! */
        curs->conn->closed = 2;
    }
    else {
        /* and finally we grab the operation result from the backend */
        for (;;) {
            Py_BEGIN_ALLOW_THREADS;
            curs->pgres = PQgetResult(curs->conn->pgconn);
            Py_END_ALLOW_THREADS;

            if (NULL == curs->pgres)
                break;
            _read_rowcount(curs);
            if (PQresultStatus(curs->pgres) == PGRES_FATAL_ERROR)
                pq_raise(curs->conn, curs, NULL);
            CLEARPGRES(curs->pgres);
        }
    }

exit:
    Py_XDECREF(func);
    Py_XDECREF(size);
    return (error == 0 ? 1 : -1);
}

static int
_pq_copy_out_v3(cursorObject *curs)
{
    PyObject *tmp = NULL;
    PyObject *func = NULL;
    PyObject *obj = NULL;
    int ret = -1;
    int is_text;

    char *buffer;
    Py_ssize_t len;

    if (!curs->copyfile) {
        PyErr_SetString(ProgrammingError,
            "can't execute COPY TO: use the copy_to() method instead");
        goto exit;
    }

    if (!(func = PyObject_GetAttrString(curs->copyfile, "write"))) {
        Dprintf("_pq_copy_out_v3: can't get o.write");
        goto exit;
    }

    /* if the file is text we must pass it unicode. */
    if (-1 == (is_text = psycopg_is_text_file(curs->copyfile))) {
        goto exit;
    }

    while (1) {
        Py_BEGIN_ALLOW_THREADS;
        len = PQgetCopyData(curs->conn->pgconn, &buffer, 0);
        Py_END_ALLOW_THREADS;

        if (len > 0 && buffer) {
            if (is_text) {
                obj = conn_decode(curs->conn, buffer, len);
            } else {
                obj = Bytes_FromStringAndSize(buffer, len);
            }

            PQfreemem(buffer);
            if (!obj) { goto exit; }
            tmp = PyObject_CallFunctionObjArgs(func, obj, NULL);
            Py_DECREF(obj);

            if (tmp == NULL) {
                goto exit;
            } else {
                Py_DECREF(tmp);
            }
        }
        /* we break on len == 0 but note that that should *not* happen,
           because we are not doing an async call (if it happens blame
           postgresql authors :/) */
        else if (len <= 0) break;
    }

    if (len == -2) {
        pq_raise(curs->conn, curs, NULL);
        goto exit;
    }

    /* and finally we grab the operation result from the backend */
    CLEARPGRES(curs->pgres);
    for (;;) {
        Py_BEGIN_ALLOW_THREADS;
        curs->pgres = PQgetResult(curs->conn->pgconn);
        Py_END_ALLOW_THREADS;

        if (NULL == curs->pgres)
            break;
        _read_rowcount(curs);
        if (PQresultStatus(curs->pgres) == PGRES_FATAL_ERROR)
            pq_raise(curs->conn, curs, NULL);
        CLEARPGRES(curs->pgres);
    }
    ret = 1;

exit:
    Py_XDECREF(func);
    return ret;
}

/* Tries to read the next message from the replication stream, without
   blocking, in both sync and async connection modes.  If no message
   is ready in the CopyData buffer, tries to read from the server,
   again without blocking.  If that doesn't help, returns Py_None.
   The caller is then supposed to block on the socket(s) and call this
   function again.

   Any keepalive messages from the server are silently consumed and
   are never returned to the caller.
 */
int
pq_read_replication_message(replicationCursorObject *repl, replicationMessageObject **msg)
{
    cursorObject *curs = &repl->cur;
    connectionObject *conn = curs->conn;
    PGconn *pgconn = conn->pgconn;
    char *buffer = NULL;
    int len, data_size, consumed, hdr, reply;
    XLogRecPtr data_start, wal_end;
    int64_t send_time;
    PyObject *str = NULL, *result = NULL;
    int ret = -1;

    Dprintf("pq_read_replication_message");

    *msg = NULL;
    consumed = 0;

retry:
    len = PQgetCopyData(pgconn, &buffer, 1 /* async */);

    if (len == 0) {
        /* If we've tried reading some data, but there was none, bail out. */
        if (consumed) {
            ret = 0;
            goto exit;
        }
        /* We should only try reading more data when there is nothing
           available at the moment.  Otherwise, with a really highly loaded
           server we might be reading a number of messages for every single
           one we process, thus overgrowing the internal buffer until the
           client system runs out of memory. */
        if (!PQconsumeInput(pgconn)) {
            pq_raise(conn, curs, NULL);
            goto exit;
        }
        /* But PQconsumeInput() doesn't tell us if it has actually read
           anything into the internal buffer and there is no (supported) way
           to ask libpq about this directly.  The way we check is setting the
           flag and re-trying PQgetCopyData(): if that returns 0 again,
           there's no more data available in the buffer, so we return None. */
        consumed = 1;
        goto retry;
    }

    if (len == -2) {
        /* serious error */
        pq_raise(conn, curs, NULL);
        goto exit;
    }
    if (len == -1) {
        /* EOF */
        curs->pgres = PQgetResult(pgconn);

        if (curs->pgres && PQresultStatus(curs->pgres) == PGRES_FATAL_ERROR) {
            pq_raise(conn, curs, NULL);
            goto exit;
        }

        CLEARPGRES(curs->pgres);
        ret = 0;
        goto exit;
    }

    /* It also makes sense to set this flag here to make us return early in
       case of retry due to keepalive message.  Any pending data on the socket
       will trigger read condition in select() in the calling code anyway. */
    consumed = 1;

    /* ok, we did really read something: update the io timestamp */
    gettimeofday(&repl->last_io, NULL);

    Dprintf("pq_read_replication_message: msg=%c, len=%d", buffer[0], len);
    if (buffer[0] == 'w') {
        /* XLogData: msgtype(1), dataStart(8), walEnd(8), sendTime(8) */
        hdr = 1 + 8 + 8 + 8;
        if (len < hdr + 1) {
            psyco_set_error(OperationalError, curs, "data message header too small");
            goto exit;
        }

        data_size  = len - hdr;
        data_start = fe_recvint64(buffer + 1);
        wal_end    = fe_recvint64(buffer + 1 + 8);
        send_time  = fe_recvint64(buffer + 1 + 8 + 8);

        Dprintf("pq_read_replication_message: data_start="XLOGFMTSTR", wal_end="XLOGFMTSTR,
                XLOGFMTARGS(data_start), XLOGFMTARGS(wal_end));

        Dprintf("pq_read_replication_message: >>%.*s<<", data_size, buffer + hdr);

        if (repl->decode) {
            str = conn_decode(conn, buffer + hdr, data_size);
        } else {
            str = Bytes_FromStringAndSize(buffer + hdr, data_size);
        }
        if (!str) { goto exit; }

        result = PyObject_CallFunctionObjArgs((PyObject *)&replicationMessageType,
                                              curs, str, NULL);
        Py_DECREF(str);
        if (!result) { goto exit; }

        *msg = (replicationMessageObject *)result;
        (*msg)->data_size  = data_size;
        (*msg)->data_start = data_start;
        (*msg)->wal_end    = wal_end;
        (*msg)->send_time  = send_time;
    }
    else if (buffer[0] == 'k') {
        /* Primary keepalive message: msgtype(1), walEnd(8), sendTime(8), reply(1) */
        hdr = 1 + 8 + 8;
        if (len < hdr + 1) {
            psyco_set_error(OperationalError, curs, "keepalive message header too small");
            goto exit;
        }

        reply = buffer[hdr];
        if (reply && pq_send_replication_feedback(repl, 0) < 0) {
            goto exit;
        }

        PQfreemem(buffer);
        buffer = NULL;
        goto retry;
    }
    else {
        psyco_set_error(OperationalError, curs, "unrecognized replication message type");
        goto exit;
    }

    ret = 0;

exit:
    if (buffer) {
        PQfreemem(buffer);
    }

    return ret;
}

int
pq_send_replication_feedback(replicationCursorObject *repl, int reply_requested)
{
    cursorObject *curs = &repl->cur;
    connectionObject *conn = curs->conn;
    PGconn *pgconn = conn->pgconn;
    char replybuf[1 + 8 + 8 + 8 + 8 + 1];
    int len = 0;

    Dprintf("pq_send_replication_feedback: write="XLOGFMTSTR", flush="XLOGFMTSTR", apply="XLOGFMTSTR,
            XLOGFMTARGS(repl->write_lsn),
            XLOGFMTARGS(repl->flush_lsn),
            XLOGFMTARGS(repl->apply_lsn));

    replybuf[len] = 'r'; len += 1;
    fe_sendint64(repl->write_lsn, &replybuf[len]); len += 8;
    fe_sendint64(repl->flush_lsn, &replybuf[len]); len += 8;
    fe_sendint64(repl->apply_lsn, &replybuf[len]); len += 8;
    fe_sendint64(feGetCurrentTimestamp(), &replybuf[len]); len += 8;
    replybuf[len] = reply_requested ? 1 : 0; len += 1;

    if (PQputCopyData(pgconn, replybuf, len) <= 0 || PQflush(pgconn) != 0) {
        pq_raise(conn, curs, NULL);
        return -1;
    }
    gettimeofday(&repl->last_io, NULL);

    return 0;
}

/* Calls pq_read_replication_message in an endless loop, until
   stop_replication is called or a fatal error occurs.  The messages
   are passed to the consumer object.

   When no message is available, blocks on the connection socket, but
   manages to send keepalive messages to the server as needed.
*/
int
pq_copy_both(replicationCursorObject *repl, PyObject *consume, double keepalive_interval)
{
    cursorObject *curs = &repl->cur;
    connectionObject *conn = curs->conn;
    PGconn *pgconn = conn->pgconn;
    replicationMessageObject *msg = NULL;
    PyObject *tmp = NULL;
    int fd, sel, ret = -1;
    fd_set fds;
    struct timeval keep_intr, curr_time, ping_time, timeout;

    if (!PyCallable_Check(consume)) {
        Dprintf("pq_copy_both: expected callable consume object");
        goto exit;
    }

    CLEARPGRES(curs->pgres);

    keep_intr.tv_sec  = (int)keepalive_interval;
    keep_intr.tv_usec = (long)((keepalive_interval - keep_intr.tv_sec)*1.0e6);

    while (1) {
        if (pq_read_replication_message(repl, &msg) < 0) {
            goto exit;
        }
        else if (msg == NULL) {
            fd = PQsocket(pgconn);
            if (fd < 0) {
                pq_raise(conn, curs, NULL);
                goto exit;
            }

            FD_ZERO(&fds);
            FD_SET(fd, &fds);

            /* how long can we wait before we need to send a keepalive? */
            gettimeofday(&curr_time, NULL);

            timeradd(&repl->last_io, &keep_intr, &ping_time);
            timersub(&ping_time, &curr_time, &timeout);

            if (timeout.tv_sec >= 0) {
                Py_BEGIN_ALLOW_THREADS;
                sel = select(fd + 1, &fds, NULL, NULL, &timeout);
                Py_END_ALLOW_THREADS;
            }
            else {
                sel = 0; /* we're past target time, pretend select() timed out */
            }

            if (sel < 0) {
                if (errno != EINTR) {
                    PyErr_SetFromErrno(PyExc_OSError);
                    goto exit;
                }
                if (PyErr_CheckSignals()) {
                    goto exit;
                }
                continue;
            }

            if (sel == 0) {
                if (pq_send_replication_feedback(repl, 0) < 0) {
                    goto exit;
                }
            }
            continue;
        }
        else {
            tmp = PyObject_CallFunctionObjArgs(consume, msg, NULL);
            Py_DECREF(msg);

            if (tmp == NULL) {
                Dprintf("pq_copy_both: consume returned NULL");
                goto exit;
            }
            Py_DECREF(tmp);
        }
    }

    ret = 1;

exit:
    return ret;
}

int
pq_fetch(cursorObject *curs, int no_result)
{
    int pgstatus, ex = -1;

    /* even if we fail, we remove any information about the previous query */
    curs_reset(curs);

    /* check for PGRES_FATAL_ERROR result */
    /* FIXME: I am not sure we need to check for critical error here.
    if (curs->pgres == NULL) {
        Dprintf("pq_fetch: got a NULL pgres, checking for critical");
        pq_set_critical(curs->conn);
        if (curs->conn->critical) {
            return pq_resolve_critical(curs->conn);
        }
        else {
            return 0;
        }
    }
    */

    if (curs->pgres == NULL) return 0;

    pgstatus = PQresultStatus(curs->pgres);
    Dprintf("pq_fetch: pgstatus = %s", PQresStatus(pgstatus));

    /* backend status message */
    Py_XDECREF(curs->pgstatus);
    curs->pgstatus = conn_text_from_chars(curs->conn, PQcmdStatus(curs->pgres));

    switch(pgstatus) {

    case PGRES_COMMAND_OK:
        Dprintf("pq_fetch: command returned OK (no tuples)");
        _read_rowcount(curs);
        curs->lastoid = PQoidValue(curs->pgres);
        CLEARPGRES(curs->pgres);
        ex = 1;
        break;

    case PGRES_COPY_OUT:
        Dprintf("pq_fetch: data from a COPY TO (no tuples)");
        curs->rowcount = -1;
        ex = _pq_copy_out_v3(curs);
        /* error caught by out glorious notice handler */
        if (PyErr_Occurred()) ex = -1;
        CLEARPGRES(curs->pgres);
        break;

    case PGRES_COPY_IN:
        Dprintf("pq_fetch: data from a COPY FROM (no tuples)");
        curs->rowcount = -1;
        ex = _pq_copy_in_v3(curs);
        /* error caught by out glorious notice handler */
        if (PyErr_Occurred()) ex = -1;
        CLEARPGRES(curs->pgres);
        break;

    case PGRES_COPY_BOTH:
        Dprintf("pq_fetch: data from a streaming replication slot (no tuples)");
        curs->rowcount = -1;
        ex = 0;
        /* Nothing to do here: pq_copy_both will be called separately.

           Also don't clear the result status: it's checked in
           consume_stream. */
        /*CLEARPGRES(curs->pgres);*/
        break;

    case PGRES_TUPLES_OK:
        if (!no_result) {
            Dprintf("pq_fetch: got tuples");
            curs->rowcount = PQntuples(curs->pgres);
            if (0 == _pq_fetch_tuples(curs)) { ex = 0; }
            /* don't clear curs->pgres, because it contains the results! */
        }
        else {
            Dprintf("pq_fetch: got tuples, discarding them");
            CLEARPGRES(curs->pgres);
            curs->rowcount = -1;
            ex = 0;
        }
        break;

    case PGRES_EMPTY_QUERY:
        PyErr_SetString(ProgrammingError,
            "can't execute an empty query");
        CLEARPGRES(curs->pgres);
        ex = -1;
        break;

    case PGRES_BAD_RESPONSE:
    case PGRES_NONFATAL_ERROR:
    case PGRES_FATAL_ERROR:
        Dprintf("pq_fetch: uh-oh, something FAILED: status = %d pgconn = %p",
            pgstatus, curs->conn);
        pq_raise(curs->conn, curs, NULL);
        ex = -1;
        break;

    default:
        /* PGRES_SINGLE_TUPLE, future statuses */
        Dprintf("pq_fetch: got unsupported result: status = %d pgconn = %p",
            pgstatus, curs->conn);
        PyErr_Format(NotSupportedError,
            "got server response with unsupported status %s",
            PQresStatus(curs->pgres == NULL ?
                PQstatus(curs->conn->pgconn) : PQresultStatus(curs->pgres)));
        CLEARPGRES(curs->pgres);
        ex = -1;
        break;
    }

    /* error checking, close the connection if necessary (some critical errors
       are not really critical, like a COPY FROM error: if that's the case we
       raise the exception but we avoid to close the connection) */
    Dprintf("pq_fetch: fetching done; check for critical errors");
    if (curs->conn->critical) {
        return pq_resolve_critical(curs->conn, ex == -1 ? 1 : 0);
    }

    return ex;
}
