/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file  core_filters.c
 * @brief Core input/output network filters.
 */

#include "apr.h"
#include "apr_strings.h"
#include "apr_lib.h"
#include "apr_fnmatch.h"
#include "apr_hash.h"
#include "apr_thread_proc.h"    /* for RLIMIT stuff */

#define APR_WANT_IOVEC
#define APR_WANT_STRFUNC
#define APR_WANT_MEMFUNC
#include "apr_want.h"

#include "ap_config.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_protocol.h" /* For index_of_response().  Grump. */
#include "http_request.h"
#include "http_vhost.h"
#include "http_main.h"     /* For the default_handler below... */
#include "http_log.h"
#include "util_md5.h"
#include "http_connection.h"
#include "apr_buckets.h"
#include "util_filter.h"
#include "util_ebcdic.h"
#include "mpm_common.h"
#include "scoreboard.h"
#include "mod_core.h"
#include "ap_listen.h"

#include "mod_so.h" /* for ap_find_loaded_module_symbol */

#define AP_MIN_SENDFILE_BYTES           (256)

/**
 * Remove all zero length buckets from the brigade.
 */
#define BRIGADE_NORMALIZE(b) \
do { \
    apr_bucket *e = APR_BRIGADE_FIRST(b); \
    do {  \
        if (e->length == 0 && !APR_BUCKET_IS_METADATA(e)) { \
            apr_bucket *d; \
            d = APR_BUCKET_NEXT(e); \
            apr_bucket_delete(e); \
            e = d; \
        } \
        else { \
            e = APR_BUCKET_NEXT(e); \
        } \
    } while (!APR_BRIGADE_EMPTY(b) && (e != APR_BRIGADE_SENTINEL(b))); \
} while (0)

/* we know core's module_index is 0 */
#undef APLOG_MODULE_INDEX
#define APLOG_MODULE_INDEX AP_CORE_MODULE_INDEX

struct core_output_filter_ctx {
    apr_bucket_brigade *buffered_bb;
    apr_bucket_brigade *tmp_flush_bb;
    apr_pool_t *deferred_write_pool;
    apr_size_t bytes_written;
};

struct core_filter_ctx {
    apr_bucket_brigade *b;
    apr_bucket_brigade *tmpbb;
};


apr_status_t ap_core_input_filter(ap_filter_t *f, apr_bucket_brigade *b,
                                  ap_input_mode_t mode, apr_read_type_e block,
                                  apr_off_t readbytes)
{
    apr_status_t rv;
    core_net_rec *net = f->ctx;
    core_ctx_t *ctx = net->in_ctx;
    const char *str;
    apr_size_t len;

    if (mode == AP_MODE_INIT) {
        /*
         * this mode is for filters that might need to 'initialize'
         * a connection before reading request data from a client.
         * NNTP over SSL for example needs to handshake before the
         * server sends the welcome message.
         * such filters would have changed the mode before this point
         * is reached.  however, protocol modules such as NNTP should
         * not need to know anything about SSL.  given the example, if
         * SSL is not in the filter chain, AP_MODE_INIT is a noop.
         */
        return APR_SUCCESS;
    }

    if (!ctx)
    {
        net->in_ctx = ctx = apr_palloc(f->c->pool, sizeof(*ctx));
        ctx->b = apr_brigade_create(f->c->pool, f->c->bucket_alloc);
        ctx->tmpbb = apr_brigade_create(f->c->pool, f->c->bucket_alloc);
        /* seed the brigade with the client socket. */
        rv = ap_run_insert_network_bucket(f->c, ctx->b, net->client_socket);
        if (rv != APR_SUCCESS)
            return rv;
    }
    else if (APR_BRIGADE_EMPTY(ctx->b)) {
        return APR_EOF;
    }

    /* ### This is bad. */
    BRIGADE_NORMALIZE(ctx->b);

    /* check for empty brigade again *AFTER* BRIGADE_NORMALIZE()
     * If we have lost our socket bucket (see above), we are EOF.
     *
     * Ideally, this should be returning SUCCESS with EOS bucket, but
     * some higher-up APIs (spec. read_request_line via ap_rgetline)
     * want an error code. */
    if (APR_BRIGADE_EMPTY(ctx->b)) {
        return APR_EOF;
    }

    if (mode == AP_MODE_GETLINE) {
        /* we are reading a single LF line, e.g. the HTTP headers */
        rv = apr_brigade_split_line(b, ctx->b, block, HUGE_STRING_LEN);
        /* We should treat EAGAIN here the same as we do for EOF (brigade is
         * empty).  We do this by returning whatever we have read.  This may
         * or may not be bogus, but is consistent (for now) with EOF logic.
         */
        if (APR_STATUS_IS_EAGAIN(rv) && block == APR_NONBLOCK_READ) {
            rv = APR_SUCCESS;
        }
        return rv;
    }

    /* ### AP_MODE_PEEK is a horrific name for this mode because we also
     * eat any CRLFs that we see.  That's not the obvious intention of
     * this mode.  Determine whether anyone actually uses this or not. */
    if (mode == AP_MODE_EATCRLF) {
        apr_bucket *e;
        const char *c;

        /* The purpose of this loop is to ignore any CRLF (or LF) at the end
         * of a request.  Many browsers send extra lines at the end of POST
         * requests.  We use the PEEK method to determine if there is more
         * data on the socket, so that we know if we should delay sending the
         * end of one request until we have served the second request in a
         * pipelined situation.  We don't want to actually delay sending a
         * response if the server finds a CRLF (or LF), becuause that doesn't
         * mean that there is another request, just a blank line.
         */
        while (1) {
            if (APR_BRIGADE_EMPTY(ctx->b))
                return APR_EOF;

            e = APR_BRIGADE_FIRST(ctx->b);

            rv = apr_bucket_read(e, &str, &len, APR_NONBLOCK_READ);

            if (rv != APR_SUCCESS)
                return rv;

            c = str;
            while (c < str + len) {
                if (*c == APR_ASCII_LF)
                    c++;
                else if (*c == APR_ASCII_CR && *(c + 1) == APR_ASCII_LF)
                    c += 2;
                else
                    return APR_SUCCESS;
            }

            /* If we reach here, we were a bucket just full of CRLFs, so
             * just toss the bucket. */
            /* FIXME: Is this the right thing to do in the core? */
            apr_bucket_delete(e);
        }
        return APR_SUCCESS;
    }

    /* If mode is EXHAUSTIVE, we want to just read everything until the end
     * of the brigade, which in this case means the end of the socket.
     * To do this, we attach the brigade that has currently been setaside to
     * the brigade that was passed down, and send that brigade back.
     *
     * NOTE:  This is VERY dangerous to use, and should only be done with
     * extreme caution.  FWLIW, this would be needed by an MPM like Perchild;
     * such an MPM can easily request the socket and all data that has been
     * read, which means that it can pass it to the correct child process.
     */
    if (mode == AP_MODE_EXHAUSTIVE) {
        apr_bucket *e;

        /* Tack on any buckets that were set aside. */
        APR_BRIGADE_CONCAT(b, ctx->b);

        /* Since we've just added all potential buckets (which will most
         * likely simply be the socket bucket) we know this is the end,
         * so tack on an EOS too. */
        /* We have read until the brigade was empty, so we know that we
         * must be EOS. */
        e = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(b, e);
        return APR_SUCCESS;
    }

    /* read up to the amount they specified. */
    if (mode == AP_MODE_READBYTES || mode == AP_MODE_SPECULATIVE) {
        apr_bucket *e;

        AP_DEBUG_ASSERT(readbytes > 0);

        e = APR_BRIGADE_FIRST(ctx->b);
        rv = apr_bucket_read(e, &str, &len, block);

        if (APR_STATUS_IS_EAGAIN(rv) && block == APR_NONBLOCK_READ) {
            /* getting EAGAIN for a blocking read is an error; for a
             * non-blocking read, return an empty brigade. */
            return APR_SUCCESS;
        }
        else if (rv != APR_SUCCESS) {
            return rv;
        }
        else if (block == APR_BLOCK_READ && len == 0) {
            /* We wanted to read some bytes in blocking mode.  We read
             * 0 bytes.  Hence, we now assume we are EOS.
             *
             * When we are in normal mode, return an EOS bucket to the
             * caller.
             * When we are in speculative mode, leave ctx->b empty, so
             * that the next call returns an EOS bucket.
             */
            apr_bucket_delete(e);

            if (mode == AP_MODE_READBYTES) {
                e = apr_bucket_eos_create(f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(b, e);
            }
            return APR_SUCCESS;
        }

        /* Have we read as much data as we wanted (be greedy)? */
        if (len < readbytes) {
            apr_size_t bucket_len;

            rv = APR_SUCCESS;
            /* We already registered the data in e in len */
            e = APR_BUCKET_NEXT(e);
            while ((len < readbytes) && (rv == APR_SUCCESS)
                   && (e != APR_BRIGADE_SENTINEL(ctx->b))) {
                /* Check for the availability of buckets with known length */
                if (e->length != -1) {
                    len += e->length;
                    e = APR_BUCKET_NEXT(e);
                }
                else {
                    /*
                     * Read from bucket, but non blocking. If there isn't any
                     * more data, well than this is fine as well, we will
                     * not wait for more since we already got some and we are
                     * only checking if there isn't more.
                     */
                    rv = apr_bucket_read(e, &str, &bucket_len,
                                         APR_NONBLOCK_READ);
                    if (rv == APR_SUCCESS) {
                        len += bucket_len;
                        e = APR_BUCKET_NEXT(e);
                    }
                }
            }
        }

        /* We can only return at most what we read. */
        if (len < readbytes) {
            readbytes = len;
        }

        rv = apr_brigade_partition(ctx->b, readbytes, &e);
        if (rv != APR_SUCCESS) {
            return rv;
        }

        /* Must do move before CONCAT */
        ctx->tmpbb = apr_brigade_split_ex(ctx->b, e, ctx->tmpbb);

        if (mode == AP_MODE_READBYTES) {
            APR_BRIGADE_CONCAT(b, ctx->b);
        }
        else if (mode == AP_MODE_SPECULATIVE) {
            apr_bucket *copy_bucket;

            for (e = APR_BRIGADE_FIRST(ctx->b);
                 e != APR_BRIGADE_SENTINEL(ctx->b);
                 e = APR_BUCKET_NEXT(e))
            {
                rv = apr_bucket_copy(e, &copy_bucket);
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                APR_BRIGADE_INSERT_TAIL(b, copy_bucket);
            }
        }

        /* Take what was originally there and place it back on ctx->b */
        APR_BRIGADE_CONCAT(ctx->b, ctx->tmpbb);
    }
    return APR_SUCCESS;
}

static void setaside_remaining_output(ap_filter_t *f,
                                      core_output_filter_ctx_t *ctx,
                                      apr_bucket_brigade *bb,
                                      conn_rec *c);

static apr_status_t send_brigade_nonblocking(apr_socket_t *s,
                                             apr_bucket_brigade *bb,
                                             apr_size_t *bytes_written,
                                             conn_rec *c);

static void remove_empty_buckets(apr_bucket_brigade *bb);

static apr_status_t send_brigade_blocking(apr_socket_t *s,
                                          apr_bucket_brigade *bb,
                                          apr_size_t *bytes_written,
                                          conn_rec *c);

static apr_status_t writev_nonblocking(apr_socket_t *s,
                                       struct iovec *vec, apr_size_t nvec,
                                       apr_bucket_brigade *bb,
                                       apr_size_t *cumulative_bytes_written,
                                       conn_rec *c);

#if APR_HAS_SENDFILE
static apr_status_t sendfile_nonblocking(apr_socket_t *s,
                                         apr_bucket *bucket,
                                         apr_size_t *cumulative_bytes_written,
                                         conn_rec *c);
#endif

/* XXX: Should these be configurable parameters? */
#define THRESHOLD_MIN_WRITE 4096
#define THRESHOLD_MAX_BUFFER 65536
#define MAX_REQUESTS_IN_PIPELINE 5

/* Optional function coming from mod_logio, used for logging of output
 * traffic
 */
extern APR_OPTIONAL_FN_TYPE(ap_logio_add_bytes_out) *ap__logio_add_bytes_out;

apr_status_t ap_core_output_filter(ap_filter_t *f, apr_bucket_brigade *new_bb)
{
    conn_rec *c = f->c;
    core_net_rec *net = f->ctx;
    core_output_filter_ctx_t *ctx = net->out_ctx;
    apr_bucket_brigade *bb = NULL;
    apr_bucket *bucket, *next, *flush_upto = NULL;
    apr_size_t bytes_in_brigade, non_file_bytes_in_brigade;
    int eor_buckets_in_brigade, morphing_bucket_in_brigade;
    apr_status_t rv;
    int loglevel = ap_get_conn_module_loglevel(c, APLOG_MODULE_INDEX);

    /* Fail quickly if the connection has already been aborted. */
    if (c->aborted) {
        if (new_bb != NULL) {
            apr_brigade_cleanup(new_bb);
        }
        return APR_ECONNABORTED;
    }

    if (ctx == NULL) {
        ctx = apr_pcalloc(c->pool, sizeof(*ctx));
        net->out_ctx = (core_output_filter_ctx_t *)ctx;
        /*
         * Need to create tmp brigade with correct lifetime. Passing
         * NULL to apr_brigade_split_ex would result in a brigade
         * allocated from bb->pool which might be wrong.
         */
        ctx->tmp_flush_bb = apr_brigade_create(c->pool, c->bucket_alloc);
        /* same for buffered_bb and ap_save_brigade */
        ctx->buffered_bb = apr_brigade_create(c->pool, c->bucket_alloc);
    }

    if (new_bb != NULL)
        bb = new_bb;

    if ((ctx->buffered_bb != NULL) &&
        !APR_BRIGADE_EMPTY(ctx->buffered_bb)) {
        if (new_bb != NULL) {
            APR_BRIGADE_PREPEND(bb, ctx->buffered_bb);
        }
        else {
            bb = ctx->buffered_bb;
        }
        c->data_in_output_filters = 0;
    }
    else if (new_bb == NULL) {
        return APR_SUCCESS;
    }

    /* Scan through the brigade and decide whether to attempt a write,
     * and how much to write, based on the following rules:
     *
     *  1) The new_bb is null: Do a nonblocking write of as much as
     *     possible: do a nonblocking write of as much data as possible,
     *     then save the rest in ctx->buffered_bb.  (If new_bb == NULL,
     *     it probably means that the MPM is doing asynchronous write
     *     completion and has just determined that this connection
     *     is writable.)
     *
     *  2) Determine if and up to which bucket we need to do a blocking
     *     write:
     *
     *  a) The brigade contains a flush bucket: Do a blocking write
     *     of everything up that point.
     *
     *  b) The request is in CONN_STATE_HANDLER state, and the brigade
     *     contains at least THRESHOLD_MAX_BUFFER bytes in non-file
     *     buckets: Do blocking writes until the amount of data in the
     *     buffer is less than THRESHOLD_MAX_BUFFER.  (The point of this
     *     rule is to provide flow control, in case a handler is
     *     streaming out lots of data faster than the data can be
     *     sent to the client.)
     *
     *  c) The request is in CONN_STATE_HANDLER state, and the brigade
     *     contains at least MAX_REQUESTS_IN_PIPELINE EOR buckets:
     *     Do blocking writes until less than MAX_REQUESTS_IN_PIPELINE EOR
     *     buckets are left. (The point of this rule is to prevent too many
     *     FDs being kept open by pipelined requests, possibly allowing a
     *     DoS).
     *
     *  d) The brigade contains a morphing bucket: If there was no other
     *     reason to do a blocking write yet, try reading the bucket. If its
     *     contents fit into memory before THRESHOLD_MAX_BUFFER is reached,
     *     everything is fine. Otherwise we need to do a blocking write the
     *     up to and including the morphing bucket, because ap_save_brigade()
     *     would read the whole bucket into memory later on.
     *
     *  3) Actually do the blocking write up to the last bucket determined
     *     by rules 2a-d. The point of doing only one flush is to make as
     *     few calls to writev() as possible.
     *
     *  4) If the brigade contains at least THRESHOLD_MIN_WRITE
     *     bytes: Do a nonblocking write of as much data as possible,
     *     then save the rest in ctx->buffered_bb.
     */

    if (new_bb == NULL) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(rv)) {
            /* The client has aborted the connection */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
            apr_brigade_cleanup(bb);
            c->aborted = 1;
            return rv;
        }
        setaside_remaining_output(f, ctx, bb, c);
        return APR_SUCCESS;
    }

    bytes_in_brigade = 0;
    non_file_bytes_in_brigade = 0;
    eor_buckets_in_brigade = 0;
    morphing_bucket_in_brigade = 0;

    for (bucket = APR_BRIGADE_FIRST(bb); bucket != APR_BRIGADE_SENTINEL(bb);
         bucket = next) {
        next = APR_BUCKET_NEXT(bucket);

        if (!APR_BUCKET_IS_METADATA(bucket)) {
            if (bucket->length == (apr_size_t)-1) {
                /*
                 * A setaside of morphing buckets would read everything into
                 * memory. Instead, we will flush everything up to and
                 * including this bucket.
                 */
                morphing_bucket_in_brigade = 1;
            }
            else {
                bytes_in_brigade += bucket->length;
                if (!APR_BUCKET_IS_FILE(bucket))
                    non_file_bytes_in_brigade += bucket->length;
            }
        }
        else if (AP_BUCKET_IS_EOR(bucket)) {
            eor_buckets_in_brigade++;
        }

        if (APR_BUCKET_IS_FLUSH(bucket)
            || non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER
            || morphing_bucket_in_brigade
            || eor_buckets_in_brigade > MAX_REQUESTS_IN_PIPELINE) {
            /* this segment of the brigade MUST be sent before returning. */

            if (loglevel >= APLOG_TRACE6) {
                char *reason = APR_BUCKET_IS_FLUSH(bucket) ?
                               "FLUSH bucket" :
                               (non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER) ?
                               "THRESHOLD_MAX_BUFFER" :
                               morphing_bucket_in_brigade ? "morphing bucket" :
                               "MAX_REQUESTS_IN_PIPELINE";
                ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, c,
                              "will flush because of %s", reason);
                ap_log_cerror(APLOG_MARK, APLOG_TRACE8, 0, c,
                              "seen in brigade%s: bytes: %" APR_SIZE_T_FMT
                              ", non-file bytes: %" APR_SIZE_T_FMT ", eor "
                              "buckets: %d, morphing buckets: %d",
                              flush_upto == NULL ? " so far"
                                                 : " since last flush point",
                              bytes_in_brigade,
                              non_file_bytes_in_brigade,
                              eor_buckets_in_brigade,
                              morphing_bucket_in_brigade);
            }
            /*
             * Defer the actual blocking write to avoid doing many writes.
             */
            flush_upto = next;

            bytes_in_brigade = 0;
            non_file_bytes_in_brigade = 0;
            eor_buckets_in_brigade = 0;
            morphing_bucket_in_brigade = 0;
        }
    }

    if (flush_upto != NULL) {
        ctx->tmp_flush_bb = apr_brigade_split_ex(bb, flush_upto,
                                                 ctx->tmp_flush_bb);
        if (loglevel >= APLOG_TRACE8) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE8, 0, c,
                              "flushing now");
        }
        rv = send_brigade_blocking(net->client_socket, bb,
                                   &(ctx->bytes_written), c);
        if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
            apr_brigade_cleanup(bb);
            c->aborted = 1;
            return rv;
        }
        if (loglevel >= APLOG_TRACE8) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE8, 0, c,
                              "total bytes written: %" APR_SIZE_T_FMT,
                              ctx->bytes_written);
        }
        APR_BRIGADE_CONCAT(bb, ctx->tmp_flush_bb);
    }

    if (loglevel >= APLOG_TRACE8) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE8, 0, c,
                      "brigade contains: bytes: %" APR_SIZE_T_FMT
                      ", non-file bytes: %" APR_SIZE_T_FMT
                      ", eor buckets: %d, morphing buckets: %d",
                      bytes_in_brigade, non_file_bytes_in_brigade,
                      eor_buckets_in_brigade, morphing_bucket_in_brigade);
    }

    if (bytes_in_brigade >= THRESHOLD_MIN_WRITE) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if ((rv != APR_SUCCESS) && (!APR_STATUS_IS_EAGAIN(rv))) {
            /* The client has aborted the connection */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
            apr_brigade_cleanup(bb);
            c->aborted = 1;
            return rv;
        }
        if (loglevel >= APLOG_TRACE8) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE8, 0, c,
                              "tried nonblocking write, total bytes "
                              "written: %" APR_SIZE_T_FMT,
                              ctx->bytes_written);
        }
    }

    setaside_remaining_output(f, ctx, bb, c);
    return APR_SUCCESS;
}

/*
 * This function assumes that either ctx->buffered_bb == NULL, or
 * ctx->buffered_bb is empty, or ctx->buffered_bb == bb
 */
static void setaside_remaining_output(ap_filter_t *f,
                                      core_output_filter_ctx_t *ctx,
                                      apr_bucket_brigade *bb,
                                      conn_rec *c)
{
    if (bb == NULL) {
        return;
    }
    remove_empty_buckets(bb);
    if (!APR_BRIGADE_EMPTY(bb)) {
        c->data_in_output_filters = 1;
        if (bb != ctx->buffered_bb) {
            if (!ctx->deferred_write_pool) {
                apr_pool_create(&ctx->deferred_write_pool, c->pool);
                apr_pool_tag(ctx->deferred_write_pool, "deferred_write");
            }
            ap_save_brigade(f, &(ctx->buffered_bb), &bb,
                            ctx->deferred_write_pool);
        }
    }
    else if (ctx->deferred_write_pool) {
        /*
         * There are no more requests in the pipeline. We can just clear the
         * pool.
         */
        apr_pool_clear(ctx->deferred_write_pool);
    }
}

#ifndef APR_MAX_IOVEC_SIZE
#define MAX_IOVEC_TO_WRITE 16
#else
#if APR_MAX_IOVEC_SIZE > 16
#define MAX_IOVEC_TO_WRITE 16
#else
#define MAX_IOVEC_TO_WRITE APR_MAX_IOVEC_SIZE
#endif
#endif

static apr_status_t send_brigade_nonblocking(apr_socket_t *s,
                                             apr_bucket_brigade *bb,
                                             apr_size_t *bytes_written,
                                             conn_rec *c)
{
    apr_bucket *bucket, *next;
    apr_status_t rv;
    struct iovec vec[MAX_IOVEC_TO_WRITE];
    apr_size_t nvec = 0;

    remove_empty_buckets(bb);

    for (bucket = APR_BRIGADE_FIRST(bb);
         bucket != APR_BRIGADE_SENTINEL(bb);
         bucket = next) {
        next = APR_BUCKET_NEXT(bucket);
#if APR_HAS_SENDFILE
        if (APR_BUCKET_IS_FILE(bucket)) {
            apr_bucket_file *file_bucket = (apr_bucket_file *)(bucket->data);
            apr_file_t *fd = file_bucket->fd;
            /* Use sendfile to send this file unless:
             *   - the platform doesn't support sendfile,
             *   - the file is too small for sendfile to be useful, or
             *   - sendfile is disabled in the httpd config via "EnableSendfile off"
             */

            if ((apr_file_flags_get(fd) & APR_SENDFILE_ENABLED) &&
                (bucket->length >= AP_MIN_SENDFILE_BYTES)) {
                if (nvec > 0) {
                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 1);
                    rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                    if (rv != APR_SUCCESS) {
                        (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
                        return rv;
                    }
                }
                rv = sendfile_nonblocking(s, bucket, bytes_written, c);
                if (nvec > 0) {
                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
                    nvec = 0;
                }
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                break;
            }
        }
#endif /* APR_HAS_SENDFILE */
        /* didn't sendfile */
        if (!APR_BUCKET_IS_METADATA(bucket)) {
            const char *data;
            apr_size_t length;
            
            /* Non-blocking read first, in case this is a morphing
             * bucket type. */
            rv = apr_bucket_read(bucket, &data, &length, APR_NONBLOCK_READ);
            if (APR_STATUS_IS_EAGAIN(rv)) {
                /* Read would block; flush any pending data and retry. */
                if (nvec) {
                    rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                    if (rv) {
                        return rv;
                    }
                    nvec = 0;
                }
                
                rv = apr_bucket_read(bucket, &data, &length, APR_BLOCK_READ);
            }
            if (rv != APR_SUCCESS) {
                return rv;
            }

            /* reading may have split the bucket, so recompute next: */
            next = APR_BUCKET_NEXT(bucket);
            vec[nvec].iov_base = (char *)data;
            vec[nvec].iov_len = length;
            nvec++;
            if (nvec == MAX_IOVEC_TO_WRITE) {
                rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                nvec = 0;
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                break;
            }
        }
    }

    if (nvec > 0) {
        rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    remove_empty_buckets(bb);

    return APR_SUCCESS;
}

static void remove_empty_buckets(apr_bucket_brigade *bb)
{
    apr_bucket *bucket;
    while (((bucket = APR_BRIGADE_FIRST(bb)) != APR_BRIGADE_SENTINEL(bb)) &&
           (APR_BUCKET_IS_METADATA(bucket) || (bucket->length == 0))) {
        apr_bucket_delete(bucket);
    }
}

static apr_status_t send_brigade_blocking(apr_socket_t *s,
                                          apr_bucket_brigade *bb,
                                          apr_size_t *bytes_written,
                                          conn_rec *c)
{
    apr_status_t rv;

    rv = APR_SUCCESS;
    while (!APR_BRIGADE_EMPTY(bb)) {
        rv = send_brigade_nonblocking(s, bb, bytes_written, c);
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EAGAIN(rv)) {
                /* Wait until we can send more data */
                apr_int32_t nsds;
                apr_interval_time_t timeout;
                apr_pollfd_t pollset;

                pollset.p = c->pool;
                pollset.desc_type = APR_POLL_SOCKET;
                pollset.reqevents = APR_POLLOUT;
                pollset.desc.s = s;
                apr_socket_timeout_get(s, &timeout);
                do {
                    rv = apr_poll(&pollset, 1, &nsds, timeout);
                } while (APR_STATUS_IS_EINTR(rv));
                if (rv != APR_SUCCESS) {
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    return rv;
}

static apr_status_t writev_nonblocking(apr_socket_t *s,
                                       struct iovec *vec, apr_size_t nvec,
                                       apr_bucket_brigade *bb,
                                       apr_size_t *cumulative_bytes_written,
                                       conn_rec *c)
{
    apr_status_t rv = APR_SUCCESS, arv;
    apr_size_t bytes_written = 0, bytes_to_write = 0;
    apr_size_t i, offset;
    apr_interval_time_t old_timeout;

    arv = apr_socket_timeout_get(s, &old_timeout);
    if (arv != APR_SUCCESS) {
        return arv;
    }
    arv = apr_socket_timeout_set(s, 0);
    if (arv != APR_SUCCESS) {
        return arv;
    }

    for (i = 0; i < nvec; i++) {
        bytes_to_write += vec[i].iov_len;
    }
    offset = 0;
    while (bytes_written < bytes_to_write) {
        apr_size_t n = 0;
        rv = apr_socket_sendv(s, vec + offset, nvec - offset, &n);
        if (n > 0) {
            bytes_written += n;
            for (i = offset; i < nvec; ) {
                apr_bucket *bucket = APR_BRIGADE_FIRST(bb);
                if (APR_BUCKET_IS_METADATA(bucket)) {
                    apr_bucket_delete(bucket);
                }
                else if (n >= vec[i].iov_len) {
                    apr_bucket_delete(bucket);
                    offset++;
                    n -= vec[i++].iov_len;
                }
                else {
                    apr_bucket_split(bucket, n);
                    apr_bucket_delete(bucket);
                    vec[i].iov_len -= n;
                    vec[i].iov_base = (char *) vec[i].iov_base + n;
                    break;
                }
            }
        }
        if (rv != APR_SUCCESS) {
            break;
        }
    }
    if ((ap__logio_add_bytes_out != NULL) && (bytes_written > 0)) {
        ap__logio_add_bytes_out(c, bytes_written);
    }
    *cumulative_bytes_written += bytes_written;

    arv = apr_socket_timeout_set(s, old_timeout);
    if ((arv != APR_SUCCESS) && (rv == APR_SUCCESS)) {
        return arv;
    }
    else {
        return rv;
    }
}

#if APR_HAS_SENDFILE

static apr_status_t sendfile_nonblocking(apr_socket_t *s,
                                         apr_bucket *bucket,
                                         apr_size_t *cumulative_bytes_written,
                                         conn_rec *c)
{
    apr_status_t rv = APR_SUCCESS;
    apr_bucket_file *file_bucket;
    apr_file_t *fd;
    apr_size_t file_length;
    apr_off_t file_offset;
    apr_size_t bytes_written = 0;

    if (!APR_BUCKET_IS_FILE(bucket)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server, APLOGNO(00006)
                     "core_filter: sendfile_nonblocking: "
                     "this should never happen");
        return APR_EGENERAL;
    }
    file_bucket = (apr_bucket_file *)(bucket->data);
    fd = file_bucket->fd;
    file_length = bucket->length;
    file_offset = bucket->start;

    if (bytes_written < file_length) {
        apr_size_t n = file_length - bytes_written;
        apr_status_t arv;
        apr_interval_time_t old_timeout;

        arv = apr_socket_timeout_get(s, &old_timeout);
        if (arv != APR_SUCCESS) {
            return arv;
        }
        arv = apr_socket_timeout_set(s, 0);
        if (arv != APR_SUCCESS) {
            return arv;
        }
        rv = apr_socket_sendfile(s, fd, NULL, &file_offset, &n, 0);
        if (rv == APR_SUCCESS) {
            bytes_written += n;
            file_offset += n;
        }
        arv = apr_socket_timeout_set(s, old_timeout);
        if ((arv != APR_SUCCESS) && (rv == APR_SUCCESS)) {
            rv = arv;
        }
    }
    if ((ap__logio_add_bytes_out != NULL) && (bytes_written > 0)) {
        ap__logio_add_bytes_out(c, bytes_written);
    }
    *cumulative_bytes_written += bytes_written;
    if ((bytes_written < file_length) && (bytes_written > 0)) {
        apr_bucket_split(bucket, bytes_written);
        apr_bucket_delete(bucket);
    }
    else if (bytes_written == file_length) {
        apr_bucket_delete(bucket);
    }
    return rv;
}

#endif
