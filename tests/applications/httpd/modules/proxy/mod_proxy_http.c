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

/* HTTP routines for Apache proxy */

#include "mod_proxy.h"
#include "ap_regex.h"

module AP_MODULE_DECLARE_DATA proxy_http_module;

static int (*ap_proxy_clear_connection_fn)(request_rec *r, apr_table_t *headers) =
        NULL;

static apr_status_t ap_proxy_http_cleanup(const char *scheme,
                                          request_rec *r,
                                          proxy_conn_rec *backend);

static apr_status_t ap_proxygetline(apr_bucket_brigade *bb, char *s, int n,
                                    request_rec *r, int flags, int *read);

/*
 * Canonicalise http-like URLs.
 *  scheme is the scheme for the URL
 *  url    is the URL starting with the first '/'
 *  def_port is the default port for this scheme.
 */
static int proxy_http_canon(request_rec *r, char *url)
{
    char *host, *path, sport[7];
    char *search = NULL;
    const char *err;
    const char *scheme;
    apr_port_t port, def_port;

    /* ap_port_of_scheme() */
    if (strncasecmp(url, "http:", 5) == 0) {
        url += 5;
        scheme = "http";
    }
    else if (strncasecmp(url, "https:", 6) == 0) {
        url += 6;
        scheme = "https";
    }
    else {
        return DECLINED;
    }
    port = def_port = ap_proxy_port_of_scheme(scheme);

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  "HTTP: canonicalising URL %s", url);

    /* do syntatic check.
     * We break the URL into host, port, path, search
     */
    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01083)
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }

    /*
     * now parse path/search args, according to rfc1738:
     * process the path.
     *
     * In a reverse proxy, our URL has been processed, so canonicalise
     * unless proxy-nocanon is set to say it's raw
     * In a forward proxy, we have and MUST NOT MANGLE the original.
     */
    switch (r->proxyreq) {
    default: /* wtf are we doing here? */
    case PROXYREQ_REVERSE:
        if (apr_table_get(r->notes, "proxy-nocanon")) {
            path = url;   /* this is the raw path */
        }
        else {
            path = ap_proxy_canonenc(r->pool, url, strlen(url),
                                     enc_path, 0, r->proxyreq);
            search = r->args;
        }
        break;
    case PROXYREQ_PROXY:
        path = url;
        break;
    }

    if (path == NULL)
        return HTTP_BAD_REQUEST;

    if (port != def_port)
        apr_snprintf(sport, sizeof(sport), ":%d", port);
    else
        sport[0] = '\0';

    if (ap_strchr_c(host, ':')) { /* if literal IPv6 address */
        host = apr_pstrcat(r->pool, "[", host, "]", NULL);
    }
    r->filename = apr_pstrcat(r->pool, "proxy:", scheme, "://", host, sport,
            "/", path, (search) ? "?" : "", (search) ? search : "", NULL);
    return OK;
}

/* Clear all connection-based headers from the incoming headers table */
typedef struct header_dptr {
    apr_pool_t *pool;
    apr_table_t *table;
    apr_time_t time;
} header_dptr;
static ap_regex_t *warn_rx;
static int clean_warning_headers(void *data, const char *key, const char *val)
{
    apr_table_t *headers = ((header_dptr*)data)->table;
    apr_pool_t *pool = ((header_dptr*)data)->pool;
    char *warning;
    char *date;
    apr_time_t warn_time;
    const int nmatch = 3;
    ap_regmatch_t pmatch[3];

    if (headers == NULL) {
        ((header_dptr*)data)->table = headers = apr_table_make(pool, 2);
    }
/*
 * Parse this, suckers!
 *
 *    Warning    = "Warning" ":" 1#warning-value
 *
 *    warning-value = warn-code SP warn-agent SP warn-text
 *                                             [SP warn-date]
 *
 *    warn-code  = 3DIGIT
 *    warn-agent = ( host [ ":" port ] ) | pseudonym
 *                    ; the name or pseudonym of the server adding
 *                    ; the Warning header, for use in debugging
 *    warn-text  = quoted-string
 *    warn-date  = <"> HTTP-date <">
 *
 * Buggrit, use a bloomin' regexp!
 * (\d{3}\s+\S+\s+\".*?\"(\s+\"(.*?)\")?)  --> whole in $1, date in $3
 */
    while (!ap_regexec(warn_rx, val, nmatch, pmatch, 0)) {
        warning = apr_pstrndup(pool, val+pmatch[0].rm_so,
                               pmatch[0].rm_eo - pmatch[0].rm_so);
        warn_time = 0;
        if (pmatch[2].rm_eo > pmatch[2].rm_so) {
            /* OK, we have a date here */
            date = apr_pstrndup(pool, val+pmatch[2].rm_so,
                                pmatch[2].rm_eo - pmatch[2].rm_so);
            warn_time = apr_date_parse_http(date);
        }
        if (!warn_time || (warn_time == ((header_dptr*)data)->time)) {
            apr_table_addn(headers, key, warning);
        }
        val += pmatch[0].rm_eo;
    }
    return 1;
}
static apr_table_t *ap_proxy_clean_warnings(apr_pool_t *p, apr_table_t *headers)
{
   header_dptr x;
   x.pool = p;
   x.table = NULL;
   x.time = apr_date_parse_http(apr_table_get(headers, "Date"));
   apr_table_do(clean_warning_headers, &x, headers, "Warning", NULL);
   if (x.table != NULL) {
       apr_table_unset(headers, "Warning");
       return apr_table_overlay(p, headers, x.table);
   }
   else {
        return headers;
   }
}

static void add_te_chunked(apr_pool_t *p,
                           apr_bucket_alloc_t *bucket_alloc,
                           apr_bucket_brigade *header_brigade)
{
    apr_bucket *e;
    char *buf;
    const char te_hdr[] = "Transfer-Encoding: chunked" CRLF;

    buf = apr_pmemdup(p, te_hdr, sizeof(te_hdr)-1);
    ap_xlate_proto_to_ascii(buf, sizeof(te_hdr)-1);

    e = apr_bucket_pool_create(buf, sizeof(te_hdr)-1, p, bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
}

static void add_cl(apr_pool_t *p,
                   apr_bucket_alloc_t *bucket_alloc,
                   apr_bucket_brigade *header_brigade,
                   const char *cl_val)
{
    apr_bucket *e;
    char *buf;

    buf = apr_pstrcat(p, "Content-Length: ",
                      cl_val,
                      CRLF,
                      NULL);
    ap_xlate_proto_to_ascii(buf, strlen(buf));
    e = apr_bucket_pool_create(buf, strlen(buf), p, bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
}

#define ASCII_CRLF  "\015\012"
#define ASCII_ZERO  "\060"

static void terminate_headers(apr_bucket_alloc_t *bucket_alloc,
                              apr_bucket_brigade *header_brigade)
{
    apr_bucket *e;

    /* add empty line at the end of the headers */
    e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
}


#define MAX_MEM_SPOOL 16384

static int stream_reqbody_chunked(apr_pool_t *p,
                                           request_rec *r,
                                           proxy_conn_rec *p_conn,
                                           conn_rec *origin,
                                           apr_bucket_brigade *header_brigade,
                                           apr_bucket_brigade *input_brigade)
{
    int seen_eos = 0, rv = OK;
    apr_size_t hdr_len;
    apr_off_t bytes;
    apr_status_t status;
    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
    apr_bucket_brigade *bb;
    apr_bucket *e;

    add_te_chunked(p, bucket_alloc, header_brigade);
    terminate_headers(bucket_alloc, header_brigade);

    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
    {
        char chunk_hdr[20];  /* must be here due to transient bucket. */

        /* If this brigade contains EOS, either stop or remove it. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
            seen_eos = 1;

            /* We can't pass this EOS to the output_filters. */
            e = APR_BRIGADE_LAST(input_brigade);
            apr_bucket_delete(e);
        }

        apr_brigade_length(input_brigade, 1, &bytes);

        hdr_len = apr_snprintf(chunk_hdr, sizeof(chunk_hdr),
                               "%" APR_UINT64_T_HEX_FMT CRLF,
                               (apr_uint64_t)bytes);

        ap_xlate_proto_to_ascii(chunk_hdr, hdr_len);
        e = apr_bucket_transient_create(chunk_hdr, hdr_len,
                                        bucket_alloc);
        APR_BRIGADE_INSERT_HEAD(input_brigade, e);

        /*
         * Append the end-of-chunk CRLF
         */
        e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(input_brigade, e);

        if (header_brigade) {
            /* we never sent the header brigade, so go ahead and
             * take care of that now
             */
            bb = header_brigade;

            /*
             * Save input_brigade in bb brigade. (At least) in the SSL case
             * input_brigade contains transient buckets whose data would get
             * overwritten during the next call of ap_get_brigade in the loop.
             * ap_save_brigade ensures these buckets to be set aside.
             * Calling ap_save_brigade with NULL as filter is OK, because
             * bb brigade already has been created and does not need to get
             * created by ap_save_brigade.
             */
            status = ap_save_brigade(NULL, &bb, &input_brigade, p);
            if (status != APR_SUCCESS) {
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            header_brigade = NULL;
        }
        else {
            bb = input_brigade;
        }

        /* The request is flushed below this loop with chunk EOS header */
        rv = ap_proxy_pass_brigade(bucket_alloc, r, p_conn, origin, bb, 0);
        if (rv != OK) {
            return rv;
        }

        if (seen_eos) {
            break;
        }

        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            conn_rec *c = r->connection;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02608)
                          "read request body failed to %pI (%s)"
                          " from %s (%s)", p_conn->addr,
                          p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return ap_map_http_request_error(status, HTTP_BAD_REQUEST);
        }
    }

    if (header_brigade) {
        /* we never sent the header brigade because there was no request body;
         * send it now
         */
        bb = header_brigade;
    }
    else {
        if (!APR_BRIGADE_EMPTY(input_brigade)) {
            /* input brigade still has an EOS which we can't pass to the output_filters. */
            e = APR_BRIGADE_LAST(input_brigade);
            AP_DEBUG_ASSERT(APR_BUCKET_IS_EOS(e));
            apr_bucket_delete(e);
        }
        bb = input_brigade;
    }

    e = apr_bucket_immortal_create(ASCII_ZERO ASCII_CRLF
                                   /* <trailers> */
                                   ASCII_CRLF,
                                   5, bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);

    if (apr_table_get(r->subprocess_env, "proxy-sendextracrlf")) {
        e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);
    }

    /* Now we have headers-only, or the chunk EOS mark; flush it */
    rv = ap_proxy_pass_brigade(bucket_alloc, r, p_conn, origin, bb, 1);
    return rv;
}

static int stream_reqbody_cl(apr_pool_t *p,
                                      request_rec *r,
                                      proxy_conn_rec *p_conn,
                                      conn_rec *origin,
                                      apr_bucket_brigade *header_brigade,
                                      apr_bucket_brigade *input_brigade,
                                      char *old_cl_val)
{
    int seen_eos = 0, rv = 0;
    apr_status_t status = APR_SUCCESS;
    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
    apr_bucket_brigade *bb;
    apr_bucket *e;
    apr_off_t cl_val = 0;
    apr_off_t bytes;
    apr_off_t bytes_streamed = 0;

    if (old_cl_val) {
        char *endstr;

        add_cl(p, bucket_alloc, header_brigade, old_cl_val);
        status = apr_strtoff(&cl_val, old_cl_val, &endstr, 10);

        if (status || *endstr || endstr == old_cl_val || cl_val < 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01085)
                          "could not parse request Content-Length (%s)",
                          old_cl_val);
            return HTTP_BAD_REQUEST;
        }
    }
    terminate_headers(bucket_alloc, header_brigade);

    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
    {
        apr_brigade_length(input_brigade, 1, &bytes);
        bytes_streamed += bytes;

        /* If this brigade contains EOS, either stop or remove it. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
            seen_eos = 1;

            /* We can't pass this EOS to the output_filters. */
            e = APR_BRIGADE_LAST(input_brigade);
            apr_bucket_delete(e);

            if (apr_table_get(r->subprocess_env, "proxy-sendextracrlf")) {
                e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(input_brigade, e);
            }
        }

        /* C-L < bytes streamed?!?
         * We will error out after the body is completely
         * consumed, but we can't stream more bytes at the
         * back end since they would in part be interpreted
         * as another request!  If nothing is sent, then
         * just send nothing.
         *
         * Prevents HTTP Response Splitting.
         */
        if (bytes_streamed > cl_val) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01086)
                          "read more bytes of request body than expected "
                          "(got %" APR_OFF_T_FMT ", expected %" APR_OFF_T_FMT ")",
                          bytes_streamed, cl_val);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        if (header_brigade) {
            /* we never sent the header brigade, so go ahead and
             * take care of that now
             */
            bb = header_brigade;

            /*
             * Save input_brigade in bb brigade. (At least) in the SSL case
             * input_brigade contains transient buckets whose data would get
             * overwritten during the next call of ap_get_brigade in the loop.
             * ap_save_brigade ensures these buckets to be set aside.
             * Calling ap_save_brigade with NULL as filter is OK, because
             * bb brigade already has been created and does not need to get
             * created by ap_save_brigade.
             */
            status = ap_save_brigade(NULL, &bb, &input_brigade, p);
            if (status != APR_SUCCESS) {
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            header_brigade = NULL;
        }
        else {
            bb = input_brigade;
        }

        /* Once we hit EOS, we are ready to flush. */
        rv = ap_proxy_pass_brigade(bucket_alloc, r, p_conn, origin, bb, seen_eos);
        if (rv != OK) {
            return rv ;
        }

        if (seen_eos) {
            break;
        }

        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            conn_rec *c = r->connection;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02609)
                          "read request body failed to %pI (%s)"
                          " from %s (%s)", p_conn->addr,
                          p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return ap_map_http_request_error(status, HTTP_BAD_REQUEST);
        }
    }

    if (bytes_streamed != cl_val) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01087)
                      "client %s given Content-Length did not match"
                      " number of body bytes read", r->connection->client_ip);
        return HTTP_BAD_REQUEST;
    }

    if (header_brigade) {
        /* we never sent the header brigade since there was no request
         * body; send it now with the flush flag
         */
        bb = header_brigade;
        return(ap_proxy_pass_brigade(bucket_alloc, r, p_conn, origin, bb, 1));
    }

    return OK;
}

static int spool_reqbody_cl(apr_pool_t *p,
                                     request_rec *r,
                                     proxy_conn_rec *p_conn,
                                     conn_rec *origin,
                                     apr_bucket_brigade *header_brigade,
                                     apr_bucket_brigade *input_brigade,
                                     int force_cl)
{
    int seen_eos = 0;
    apr_status_t status;
    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
    apr_bucket_brigade *body_brigade;
    apr_bucket *e;
    apr_off_t bytes, bytes_spooled = 0, fsize = 0;
    apr_file_t *tmpfile = NULL;
    apr_off_t limit;

    body_brigade = apr_brigade_create(p, bucket_alloc);

    limit = ap_get_limit_req_body(r);

    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
    {
        /* If this brigade contains EOS, either stop or remove it. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
            seen_eos = 1;

            /* We can't pass this EOS to the output_filters. */
            e = APR_BRIGADE_LAST(input_brigade);
            apr_bucket_delete(e);
        }

        apr_brigade_length(input_brigade, 1, &bytes);

        if (bytes_spooled + bytes > MAX_MEM_SPOOL) {
            /*
             * LimitRequestBody does not affect Proxy requests (Should it?).
             * Let it take effect if we decide to store the body in a
             * temporary file on disk.
             */
            if (limit && (bytes_spooled + bytes > limit)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01088)
                              "Request body is larger than the configured "
                              "limit of %" APR_OFF_T_FMT, limit);
                return HTTP_REQUEST_ENTITY_TOO_LARGE;
            }
            /* can't spool any more in memory; write latest brigade to disk */
            if (tmpfile == NULL) {
                const char *temp_dir;
                char *template;

                status = apr_temp_dir_get(&temp_dir, p);
                if (status != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01089)
                                  "search for temporary directory failed");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                apr_filepath_merge(&template, temp_dir,
                                   "modproxy.tmp.XXXXXX",
                                   APR_FILEPATH_NATIVE, p);
                status = apr_file_mktemp(&tmpfile, template, 0, p);
                if (status != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01090)
                                  "creation of temporary file in directory "
                                  "%s failed", temp_dir);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
            }
            for (e = APR_BRIGADE_FIRST(input_brigade);
                 e != APR_BRIGADE_SENTINEL(input_brigade);
                 e = APR_BUCKET_NEXT(e)) {
                const char *data;
                apr_size_t bytes_read, bytes_written;

                apr_bucket_read(e, &data, &bytes_read, APR_BLOCK_READ);
                status = apr_file_write_full(tmpfile, data, bytes_read, &bytes_written);
                if (status != APR_SUCCESS) {
                    const char *tmpfile_name;

                    if (apr_file_name_get(&tmpfile_name, tmpfile) != APR_SUCCESS) {
                        tmpfile_name = "(unknown)";
                    }
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01091)
                                  "write to temporary file %s failed",
                                  tmpfile_name);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                AP_DEBUG_ASSERT(bytes_read == bytes_written);
                fsize += bytes_written;
            }
            apr_brigade_cleanup(input_brigade);
        }
        else {

            /*
             * Save input_brigade in body_brigade. (At least) in the SSL case
             * input_brigade contains transient buckets whose data would get
             * overwritten during the next call of ap_get_brigade in the loop.
             * ap_save_brigade ensures these buckets to be set aside.
             * Calling ap_save_brigade with NULL as filter is OK, because
             * body_brigade already has been created and does not need to get
             * created by ap_save_brigade.
             */
            status = ap_save_brigade(NULL, &body_brigade, &input_brigade, p);
            if (status != APR_SUCCESS) {
                return HTTP_INTERNAL_SERVER_ERROR;
            }

        }

        bytes_spooled += bytes;

        if (seen_eos) {
            break;
        }

        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            conn_rec *c = r->connection;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02610)
                          "read request body failed to %pI (%s)"
                          " from %s (%s)", p_conn->addr,
                          p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return ap_map_http_request_error(status, HTTP_BAD_REQUEST);
        }
    }

    if (bytes_spooled || force_cl) {
        add_cl(p, bucket_alloc, header_brigade, apr_off_t_toa(p, bytes_spooled));
    }
    terminate_headers(bucket_alloc, header_brigade);
    APR_BRIGADE_CONCAT(header_brigade, body_brigade);
    if (tmpfile) {
        apr_brigade_insert_file(header_brigade, tmpfile, 0, fsize, p);
    }
    if (apr_table_get(r->subprocess_env, "proxy-sendextracrlf")) {
        e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
    }
    /* This is all a single brigade, pass with flush flagged */
    return(ap_proxy_pass_brigade(bucket_alloc, r, p_conn, origin, header_brigade, 1));
}

static
int ap_proxy_http_request(apr_pool_t *p, request_rec *r,
                                   proxy_conn_rec *p_conn, proxy_worker *worker,
                                   proxy_server_conf *conf,
                                   apr_uri_t *uri,
                                   char *url, char *server_portstr)
{
    conn_rec *c = r->connection;
    apr_bucket_alloc_t *bucket_alloc = c->bucket_alloc;
    apr_bucket_brigade *header_brigade;
    apr_bucket_brigade *input_brigade;
    apr_bucket_brigade *temp_brigade;
    apr_bucket *e;
    char *buf;
    apr_status_t status;
    enum rb_methods {RB_INIT, RB_STREAM_CL, RB_STREAM_CHUNKED, RB_SPOOL_CL};
    enum rb_methods rb_method = RB_INIT;
    char *old_cl_val = NULL;
    char *old_te_val = NULL;
    apr_off_t bytes_read = 0;
    apr_off_t bytes;
    int force10, rv;
    conn_rec *origin = p_conn->connection;

    if (apr_table_get(r->subprocess_env, "force-proxy-request-1.0")) {
        if (r->expecting_100) {
            return HTTP_EXPECTATION_FAILED;
        }
        force10 = 1;
    } else {
        force10 = 0;
    }

    header_brigade = apr_brigade_create(p, bucket_alloc);
    rv = ap_proxy_create_hdrbrgd(p, header_brigade, r, p_conn,
                                 worker, conf, uri, url, server_portstr,
                                 &old_cl_val, &old_te_val);
    if (rv != OK) {
        return rv;
    }

    /* We have headers, let's figure out our request body... */
    input_brigade = apr_brigade_create(p, bucket_alloc);

    /* sub-requests never use keepalives, and mustn't pass request bodies.
     * Because the new logic looks at input_brigade, we will self-terminate
     * input_brigade and jump past all of the request body logic...
     * Reading anything with ap_get_brigade is likely to consume the
     * main request's body or read beyond EOS - which would be unplesant.
     *
     * An exception: when a kept_body is present, then subrequest CAN use
     * pass request bodies, and we DONT skip the body.
     */
    if (!r->kept_body && r->main) {
        /* XXX: Why DON'T sub-requests use keepalives? */
        p_conn->close = 1;
        old_cl_val = NULL;
        old_te_val = NULL;
        rb_method = RB_STREAM_CL;
        e = apr_bucket_eos_create(input_brigade->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(input_brigade, e);
        goto skip_body;
    }

    /* WE only understand chunked.  Other modules might inject
     * (and therefore, decode) other flavors but we don't know
     * that the can and have done so unless they remove
     * their decoding from the headers_in T-E list.
     * XXX: Make this extensible, but in doing so, presume the
     * encoding has been done by the extensions' handler, and
     * do not modify add_te_chunked's logic
     */
    if (old_te_val && strcasecmp(old_te_val, "chunked") != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01093)
                      "%s Transfer-Encoding is not supported", old_te_val);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (old_cl_val && old_te_val) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01094)
                      "client %s (%s) requested Transfer-Encoding "
                      "chunked body with Content-Length (C-L ignored)",
                      c->client_ip, c->remote_host ? c->remote_host: "");
        old_cl_val = NULL;
        origin->keepalive = AP_CONN_CLOSE;
        p_conn->close = 1;
    }

    /* Prefetch MAX_MEM_SPOOL bytes
     *
     * This helps us avoid any election of C-L v.s. T-E
     * request bodies, since we are willing to keep in
     * memory this much data, in any case.  This gives
     * us an instant C-L election if the body is of some
     * reasonable size.
     */
    temp_brigade = apr_brigade_create(p, bucket_alloc);
    do {
        status = ap_get_brigade(r->input_filters, temp_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                MAX_MEM_SPOOL - bytes_read);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01095)
                          "prefetch request body failed to %pI (%s)"
                          " from %s (%s)",
                          p_conn->addr, p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return ap_map_http_request_error(status, HTTP_BAD_REQUEST);
        }

        apr_brigade_length(temp_brigade, 1, &bytes);
        bytes_read += bytes;

        /*
         * Save temp_brigade in input_brigade. (At least) in the SSL case
         * temp_brigade contains transient buckets whose data would get
         * overwritten during the next call of ap_get_brigade in the loop.
         * ap_save_brigade ensures these buckets to be set aside.
         * Calling ap_save_brigade with NULL as filter is OK, because
         * input_brigade already has been created and does not need to get
         * created by ap_save_brigade.
         */
        status = ap_save_brigade(NULL, &input_brigade, &temp_brigade, p);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01096)
                          "processing prefetched request body failed"
                          " to %pI (%s) from %s (%s)",
                          p_conn->addr, p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return HTTP_INTERNAL_SERVER_ERROR;
        }

    /* Ensure we don't hit a wall where we have a buffer too small
     * for ap_get_brigade's filters to fetch us another bucket,
     * surrender once we hit 80 bytes less than MAX_MEM_SPOOL
     * (an arbitrary value.)
     */
    } while ((bytes_read < MAX_MEM_SPOOL - 80)
              && !APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade)));

    /* Use chunked request body encoding or send a content-length body?
     *
     * Prefer C-L when:
     *
     *   We have no request body (handled by RB_STREAM_CL)
     *
     *   We have a request body length <= MAX_MEM_SPOOL
     *
     *   The administrator has setenv force-proxy-request-1.0
     *
     *   The client sent a C-L body, and the administrator has
     *   not setenv proxy-sendchunked or has set setenv proxy-sendcl
     *
     *   The client sent a T-E body, and the administrator has
     *   setenv proxy-sendcl, and not setenv proxy-sendchunked
     *
     * If both proxy-sendcl and proxy-sendchunked are set, the
     * behavior is the same as if neither were set, large bodies
     * that can't be read will be forwarded in their original
     * form of C-L, or T-E.
     *
     * To ensure maximum compatibility, setenv proxy-sendcl
     * To reduce server resource use,   setenv proxy-sendchunked
     *
     * Then address specific servers with conditional setenv
     * options to restore the default behavior where desireable.
     *
     * We have to compute content length by reading the entire request
     * body; if request body is not small, we'll spool the remaining
     * input to a temporary file.  Chunked is always preferable.
     *
     * We can only trust the client-provided C-L if the T-E header
     * is absent, and the filters are unchanged (the body won't
     * be resized by another content filter).
     */
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
        /* The whole thing fit, so our decision is trivial, use
         * the filtered bytes read from the client for the request
         * body Content-Length.
         *
         * If we expected no body, and read no body, do not set
         * the Content-Length.
         */
        if (old_cl_val || old_te_val || bytes_read) {
            old_cl_val = apr_off_t_toa(r->pool, bytes_read);
        }
        rb_method = RB_STREAM_CL;
    }
    else if (old_te_val) {
        if (force10
             || (apr_table_get(r->subprocess_env, "proxy-sendcl")
                  && !apr_table_get(r->subprocess_env, "proxy-sendchunks")
                  && !apr_table_get(r->subprocess_env, "proxy-sendchunked"))) {
            rb_method = RB_SPOOL_CL;
        }
        else {
            rb_method = RB_STREAM_CHUNKED;
        }
    }
    else if (old_cl_val) {
        if (r->input_filters == r->proto_input_filters) {
            rb_method = RB_STREAM_CL;
        }
        else if (!force10
                  && (apr_table_get(r->subprocess_env, "proxy-sendchunks")
                      || apr_table_get(r->subprocess_env, "proxy-sendchunked"))
                  && !apr_table_get(r->subprocess_env, "proxy-sendcl")) {
            rb_method = RB_STREAM_CHUNKED;
        }
        else {
            rb_method = RB_SPOOL_CL;
        }
    }
    else {
        /* This is an appropriate default; very efficient for no-body
         * requests, and has the behavior that it will not add any C-L
         * when the old_cl_val is NULL.
         */
        rb_method = RB_SPOOL_CL;
    }

/* Yes I hate gotos.  This is the subrequest shortcut */
skip_body:
    /*
     * Handle Connection: header if we do HTTP/1.1 request:
     * If we plan to close the backend connection sent Connection: close
     * otherwise sent Connection: Keep-Alive.
     */
    if (!force10) {
        if (!ap_proxy_connection_reusable(p_conn)) {
            buf = apr_pstrdup(p, "Connection: close" CRLF);
        }
        else {
            buf = apr_pstrdup(p, "Connection: Keep-Alive" CRLF);
        }
        ap_xlate_proto_to_ascii(buf, strlen(buf));
        e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
    }

    /* send the request body, if any. */
    switch(rb_method) {
    case RB_STREAM_CHUNKED:
        rv = stream_reqbody_chunked(p, r, p_conn, origin, header_brigade,
                                        input_brigade);
        break;
    case RB_STREAM_CL:
        rv = stream_reqbody_cl(p, r, p_conn, origin, header_brigade,
                                   input_brigade, old_cl_val);
        break;
    case RB_SPOOL_CL:
        rv = spool_reqbody_cl(p, r, p_conn, origin, header_brigade,
                                  input_brigade, (old_cl_val != NULL)
                                              || (old_te_val != NULL)
                                              || (bytes_read > 0));
        break;
    default:
        /* shouldn't be possible */
        rv = HTTP_INTERNAL_SERVER_ERROR;
        break;
    }

    if (rv != OK) {
        /* apr_status_t value has been logged in lower level method */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01097)
                      "pass request body failed to %pI (%s) from %s (%s)",
                      p_conn->addr, p_conn->hostname ? p_conn->hostname: "",
                      c->client_ip, c->remote_host ? c->remote_host: "");
        return rv;
    }

    return OK;
}

/*
 * If the date is a valid RFC 850 date or asctime() date, then it
 * is converted to the RFC 1123 format.
 */
static const char *date_canon(apr_pool_t *p, const char *date)
{
    apr_status_t rv;
    char* ndate;

    apr_time_t time = apr_date_parse_http(date);
    if (!time) {
        return date;
    }

    ndate = apr_palloc(p, APR_RFC822_DATE_LEN);
    rv = apr_rfc822_date(ndate, time);
    if (rv != APR_SUCCESS) {
        return date;
    }

    return ndate;
}

static request_rec *make_fake_req(conn_rec *c, request_rec *r)
{
    apr_pool_t *pool;
    request_rec *rp;

    apr_pool_create(&pool, c->pool);

    rp = apr_pcalloc(pool, sizeof(*r));

    rp->pool            = pool;
    rp->status          = HTTP_OK;

    rp->headers_in      = apr_table_make(pool, 50);
    rp->trailers_in     = apr_table_make(pool, 5);

    rp->subprocess_env  = apr_table_make(pool, 50);
    rp->headers_out     = apr_table_make(pool, 12);
    rp->trailers_out    = apr_table_make(pool, 5);
    rp->err_headers_out = apr_table_make(pool, 5);
    rp->notes           = apr_table_make(pool, 5);

    rp->server = r->server;
    rp->log = r->log;
    rp->proxyreq = r->proxyreq;
    rp->request_time = r->request_time;
    rp->connection      = c;
    rp->output_filters  = c->output_filters;
    rp->input_filters   = c->input_filters;
    rp->proto_output_filters  = c->output_filters;
    rp->proto_input_filters   = c->input_filters;
    rp->useragent_ip = c->client_ip;
    rp->useragent_addr = c->client_addr;

    rp->request_config  = ap_create_request_config(pool);
    proxy_run_create_req(r, rp);

    return rp;
}

static void process_proxy_header(request_rec *r, proxy_dir_conf *c,
                                 const char *key, const char *value)
{
    static const char *date_hdrs[]
        = { "Date", "Expires", "Last-Modified", NULL };
    static const struct {
        const char *name;
        ap_proxy_header_reverse_map_fn func;
    } transform_hdrs[] = {
        { "Location", ap_proxy_location_reverse_map },
        { "Content-Location", ap_proxy_location_reverse_map },
        { "URI", ap_proxy_location_reverse_map },
        { "Destination", ap_proxy_location_reverse_map },
        { "Set-Cookie", ap_proxy_cookie_reverse_map },
        { NULL, NULL }
    };
    int i;
    for (i = 0; date_hdrs[i]; ++i) {
        if (!strcasecmp(date_hdrs[i], key)) {
            apr_table_add(r->headers_out, key,
                          date_canon(r->pool, value));
            return;
        }
    }
    for (i = 0; transform_hdrs[i].name; ++i) {
        if (!strcasecmp(transform_hdrs[i].name, key)) {
            apr_table_add(r->headers_out, key,
                          (*transform_hdrs[i].func)(r, c, value));
            return;
       }
    }
    apr_table_add(r->headers_out, key, value);
}

/*
 * Note: pread_len is the length of the response that we've  mistakenly
 * read (assuming that we don't consider that an  error via
 * ProxyBadHeader StartBody). This depends on buffer actually being
 * local storage to the calling code in order for pread_len to make
 * any sense at all, since we depend on buffer still containing
 * what was read by ap_getline() upon return.
 */
static void ap_proxy_read_headers(request_rec *r, request_rec *rr,
                                  char *buffer, int size,
                                  conn_rec *c, int *pread_len)
{
    int len;
    char *value, *end;
    int saw_headers = 0;
    void *sconf = r->server->module_config;
    proxy_server_conf *psc;
    proxy_dir_conf *dconf;
    apr_status_t rc;
    apr_bucket_brigade *tmp_bb;

    dconf = ap_get_module_config(r->per_dir_config, &proxy_module);
    psc = (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    r->headers_out = apr_table_make(r->pool, 20);
    r->trailers_out = apr_table_make(r->pool, 5);
    *pread_len = 0;

    /*
     * Read header lines until we get the empty separator line, a read error,
     * the connection closes (EOF), or we timeout.
     */
    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                  "Headers received from backend:");

    tmp_bb = apr_brigade_create(r->pool, c->bucket_alloc);
    while (1) {
        rc = ap_proxygetline(tmp_bb, buffer, size, rr,
                             AP_GETLINE_FOLD | AP_GETLINE_NOSPC_EOL, &len);

        if (len <= 0)
            break;

        if (APR_STATUS_IS_ENOSPC(rc)) {
            /* The header could not fit in the provided buffer, warn.
             * XXX: falls through with the truncated header, 5xx instead?
             */
            int trunc = (len > 128 ? 128 : len) / 2;
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rc, r, APLOGNO(10124)
                    "header size is over the limit allowed by "
                    "ResponseFieldSize (%d bytes). "
                    "Bad response header: '%.*s[...]%s'",
                    size, trunc, buffer, buffer + len - trunc);
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r, "%s", buffer);
        }

        if (!(value = strchr(buffer, ':'))) {     /* Find the colon separator */

            /* We may encounter invalid headers, usually from buggy
             * MS IIS servers, so we need to determine just how to handle
             * them. We can either ignore them, assume that they mark the
             * start-of-body (eg: a missing CRLF) or (the default) mark
             * the headers as totally bogus and return a 500. The sole
             * exception is an extra "HTTP/1.0 200, OK" line sprinkled
             * in between the usual MIME headers, which is a favorite
             * IIS bug.
             */
             /* XXX: The mask check is buggy if we ever see an HTTP/1.10 */

            if (!apr_date_checkmask(buffer, "HTTP/#.# ###*")) {
                if (psc->badopt == bad_error) {
                    /* Nope, it wasn't even an extra HTTP header. Give up. */
                    r->headers_out = NULL;
                    return;
                }
                else if (psc->badopt == bad_body) {
                    /* if we've already started loading headers_out, then
                     * return what we've accumulated so far, in the hopes
                     * that they are useful; also note that we likely pre-read
                     * the first line of the response.
                     */
                    if (saw_headers) {
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01098)
                                      "Starting body due to bogus non-header "
                                      "in headers returned by %s (%s)",
                                      r->uri, r->method);
                        *pread_len = len;
                        return;
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01099)
                                      "No HTTP headers returned by %s (%s)",
                                      r->uri, r->method);
                        return;
                    }
                }
            }
            /* this is the psc->badopt == bad_ignore case */
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01100)
                          "Ignoring bogus HTTP header returned by %s (%s)",
                          r->uri, r->method);
            continue;
        }

        *value = '\0';
        ++value;
        /* XXX: RFC2068 defines only SP and HT as whitespace, this test is
         * wrong... and so are many others probably.
         */
        while (apr_isspace(*value))
            ++value;            /* Skip to start of value   */

        /* should strip trailing whitespace as well */
        for (end = &value[strlen(value)-1]; end > value && apr_isspace(*end); --end)
            *end = '\0';

        /* make sure we add so as not to destroy duplicated headers
         * Modify headers requiring canonicalisation and/or affected
         * by ProxyPassReverse and family with process_proxy_header
         */
        process_proxy_header(r, dconf, buffer, value);
        saw_headers = 1;
    }
}



static int addit_dammit(void *v, const char *key, const char *val)
{
    apr_table_addn(v, key, val);
    return 1;
}

static apr_status_t ap_proxygetline(apr_bucket_brigade *bb, char *s, int n,
                                    request_rec *r, int flags, int *read)
{
    apr_status_t rv;
    apr_size_t len;

    rv = ap_rgetline(&s, n, &len, r, flags, bb);
    apr_brigade_cleanup(bb);

    if (rv == APR_SUCCESS || APR_STATUS_IS_ENOSPC(rv)) {
        *read = (int)len;
    } else {
        *read = -1;
    }

    return rv;
}

/*
 * Limit the number of interim responses we sent back to the client. Otherwise
 * we suffer from a memory build up. Besides there is NO sense in sending back
 * an unlimited number of interim responses to the client. Thus if we cross
 * this limit send back a 502 (Bad Gateway).
 */
#ifndef AP_MAX_INTERIM_RESPONSES
#define AP_MAX_INTERIM_RESPONSES 10
#endif

static int add_trailers(void *data, const char *key, const char *val)
{
    if (val) {
        apr_table_add((apr_table_t*)data, key, val);
    }
    return 1;
}

static
apr_status_t ap_proxy_http_process_response(apr_pool_t * p, request_rec *r,
                                            proxy_conn_rec **backend_ptr,
                                            proxy_worker *worker,
                                            proxy_server_conf *conf,
                                            char *server_portstr) {
    conn_rec *c = r->connection;
    char *buffer;
    char fixed_buffer[HUGE_STRING_LEN];
    const char *buf;
    char keepchar;
    apr_bucket *e;
    apr_bucket_brigade *bb;
    apr_bucket_brigade *pass_bb;
    int len, backasswards;
    int interim_response = 0; /* non-zero whilst interim 1xx responses
                               * are being read. */
    apr_size_t response_field_size = 0;
    int pread_len = 0;
    apr_table_t *save_table;
    int backend_broke = 0;
    static const char *hop_by_hop_hdrs[] =
        {"Keep-Alive", "Proxy-Authenticate", "TE", "Trailer", "Upgrade", NULL};
    int i;
    const char *te = NULL;
    int original_status = r->status;
    int proxy_status = OK;
    const char *original_status_line = r->status_line;
    const char *proxy_status_line = NULL;
    proxy_conn_rec *backend = *backend_ptr;
    conn_rec *origin = backend->connection;
    apr_interval_time_t old_timeout = 0;
    proxy_dir_conf *dconf;
    int do_100_continue;

    dconf = ap_get_module_config(r->per_dir_config, &proxy_module);

    do_100_continue = (worker->s->ping_timeout_set
                       && ap_request_has_body(r)
                       && (PROXYREQ_REVERSE == r->proxyreq)
                       && !(apr_table_get(r->subprocess_env, "force-proxy-request-1.0")));

    bb = apr_brigade_create(p, c->bucket_alloc);
    pass_bb = apr_brigade_create(p, c->bucket_alloc);

    /* Only use dynamically sized buffer if user specifies ResponseFieldSize */
    if(backend->worker->s->response_field_size_set) {
        response_field_size = backend->worker->s->response_field_size;

        if (response_field_size != HUGE_STRING_LEN)
            buffer = apr_pcalloc(p, response_field_size);
        else
            buffer = fixed_buffer;
    }
    else {
        response_field_size = HUGE_STRING_LEN;
        buffer = fixed_buffer;
    }

    /* Setup for 100-Continue timeout if appropriate */
    if (do_100_continue) {
        apr_socket_timeout_get(backend->sock, &old_timeout);
        if (worker->s->ping_timeout != old_timeout) {
            apr_status_t rc;
            rc = apr_socket_timeout_set(backend->sock, worker->s->ping_timeout);
            if (rc != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(01101)
                              "could not set 100-Continue timeout");
            }
        }
    }

    /* Get response from the remote server, and pass it up the
     * filter chain
     */

    backend->r = make_fake_req(origin, r);
    /* In case anyone needs to know, this is a fake request that is really a
     * response.
     */
    backend->r->proxyreq = PROXYREQ_RESPONSE;
    apr_table_setn(r->notes, "proxy-source-port", apr_psprintf(r->pool, "%hu",
                   origin->local_addr->port));
    do {
        apr_status_t rc;

        apr_brigade_cleanup(bb);

        rc = ap_proxygetline(backend->tmp_bb, buffer, response_field_size,
                             backend->r, 0, &len);
        if (len == 0) {
            /* handle one potential stray CRLF */
            rc = ap_proxygetline(backend->tmp_bb, buffer, response_field_size,
                                 backend->r, 0, &len);
        }
        if (len <= 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(01102)
                          "error reading status line from remote "
                          "server %s:%d", backend->hostname, backend->port);
            if (APR_STATUS_IS_TIMEUP(rc)) {
                apr_table_setn(r->notes, "proxy_timedout", "1");
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01103) "read timeout");
                if (do_100_continue) {
                    return ap_proxyerror(r, HTTP_SERVICE_UNAVAILABLE, "Timeout on 100-Continue");
                }
            }
            /*
             * If we are a reverse proxy request shutdown the connection
             * WITHOUT ANY response to trigger a retry by the client
             * if allowed (as for idempotent requests).
             * BUT currently we should not do this if the request is the
             * first request on a keepalive connection as browsers like
             * seamonkey only display an empty page in this case and do
             * not do a retry. We should also not do this on a
             * connection which times out; instead handle as
             * we normally would handle timeouts
             */
            if (r->proxyreq == PROXYREQ_REVERSE && c->keepalives &&
                !APR_STATUS_IS_TIMEUP(rc)) {
                apr_bucket *eos;

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01104)
                              "Closing connection to client because"
                              " reading from backend server %s:%d failed."
                              " Number of keepalives %i", backend->hostname,
                              backend->port, c->keepalives);
                ap_proxy_backend_broke(r, bb);
                /*
                 * Add an EOC bucket to signal the ap_http_header_filter
                 * that it should get out of our way, BUT ensure that the
                 * EOC bucket is inserted BEFORE an EOS bucket in bb as
                 * some resource filters like mod_deflate pass everything
                 * up to the EOS down the chain immediately and sent the
                 * remainder of the brigade later (or even never). But in
                 * this case the ap_http_header_filter does not get out of
                 * our way soon enough.
                 */
                e = ap_bucket_eoc_create(c->bucket_alloc);
                eos = APR_BRIGADE_LAST(bb);
                while ((APR_BRIGADE_SENTINEL(bb) != eos)
                       && !APR_BUCKET_IS_EOS(eos)) {
                    eos = APR_BUCKET_PREV(eos);
                }
                if (eos == APR_BRIGADE_SENTINEL(bb)) {
                    APR_BRIGADE_INSERT_TAIL(bb, e);
                }
                else {
                    APR_BUCKET_INSERT_BEFORE(eos, e);
                }
                ap_pass_brigade(r->output_filters, bb);
                /* Mark the backend connection for closing */
                backend->close = 1;
                /* Need to return OK to avoid sending an error message */
                return OK;
            }
            else if (!c->keepalives) {
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01105)
                                   "NOT Closing connection to client"
                                   " although reading from backend server %s:%d"
                                   " failed.",
                                   backend->hostname, backend->port);
            }
            return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                 "Error reading from remote server");
        }
        /* XXX: Is this a real headers length send from remote? */
        backend->worker->s->read += len;

        /* Is it an HTTP/1 response?
         * This is buggy if we ever see an HTTP/1.10
         */
        if (apr_date_checkmask(buffer, "HTTP/#.# ###*")) {
            int major, minor;
            int toclose;

            major = buffer[5] - '0';
            minor = buffer[7] - '0';

            /* If not an HTTP/1 message or
             * if the status line was > 8192 bytes
             */
            if ((major != 1) || (len >= response_field_size - 1)) {
                return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                apr_pstrcat(p, "Corrupt status line returned by remote "
                            "server: ", buffer, NULL));
            }
            backasswards = 0;

            keepchar = buffer[12];
            buffer[12] = '\0';
            proxy_status = atoi(&buffer[9]);
            apr_table_setn(r->notes, "proxy-status",
                           apr_pstrdup(r->pool, &buffer[9]));

            if (keepchar != '\0') {
                buffer[12] = keepchar;
            } else {
                /* 2616 requires the space in Status-Line; the origin
                 * server may have sent one but ap_rgetline_core will
                 * have stripped it. */
                buffer[12] = ' ';
                buffer[13] = '\0';
            }
            proxy_status_line = apr_pstrdup(p, &buffer[9]);

            /* The status out of the front is the same as the status coming in
             * from the back, until further notice.
             */
            r->status = proxy_status;
            r->status_line = proxy_status_line;

            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                          "Status from backend: %d", proxy_status);

            /* read the headers. */
            /* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers*/
            /* Also, take care with headers with multiple occurences. */

            /* First, tuck away all already existing cookies */
            save_table = apr_table_make(r->pool, 2);
            apr_table_do(addit_dammit, save_table, r->headers_out,
                         "Set-Cookie", NULL);

            /* shove the headers direct into r->headers_out */
            ap_proxy_read_headers(r, backend->r, buffer, response_field_size, origin,
                                  &pread_len);

            if (r->headers_out == NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01106)
                              "bad HTTP/%d.%d header returned by %s (%s)",
                              major, minor, r->uri, r->method);
                backend->close = 1;
                /*
                 * ap_send_error relies on a headers_out to be present. we
                 * are in a bad position here.. so force everything we send out
                 * to have nothing to do with the incoming packet
                 */
                r->headers_out = apr_table_make(r->pool,1);
                r->status = HTTP_BAD_GATEWAY;
                r->status_line = "bad gateway";
                return r->status;
            }

            /* Now, add in the just read cookies */
            apr_table_do(addit_dammit, save_table, r->headers_out,
                         "Set-Cookie", NULL);

            /* and now load 'em all in */
            if (!apr_is_empty_table(save_table)) {
                apr_table_unset(r->headers_out, "Set-Cookie");
                r->headers_out = apr_table_overlay(r->pool,
                                                   r->headers_out,
                                                   save_table);
            }

            /* can't have both Content-Length and Transfer-Encoding */
            if (apr_table_get(r->headers_out, "Transfer-Encoding")
                    && apr_table_get(r->headers_out, "Content-Length")) {
                /*
                 * 2616 section 4.4, point 3: "if both Transfer-Encoding
                 * and Content-Length are received, the latter MUST be
                 * ignored";
                 *
                 * To help mitigate HTTP Splitting, unset Content-Length
                 * and shut down the backend server connection
                 * XXX: We aught to treat such a response as uncachable
                 */
                apr_table_unset(r->headers_out, "Content-Length");
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01107)
                              "server %s:%d returned Transfer-Encoding"
                              " and Content-Length",
                              backend->hostname, backend->port);
                backend->close = 1;
            }

            /*
             * Save a possible Transfer-Encoding header as we need it later for
             * ap_http_filter to know where to end.
             */
            te = apr_table_get(r->headers_out, "Transfer-Encoding");

            /* strip connection listed hop-by-hop headers from response */
            toclose = ap_proxy_clear_connection_fn(r, r->headers_out);
            if (toclose) {
                backend->close = 1;
            }

            if ((buf = apr_table_get(r->headers_out, "Content-Type"))) {
                ap_set_content_type(r, apr_pstrdup(p, buf));
            }
            if (!ap_is_HTTP_INFO(proxy_status)) {
                ap_proxy_pre_http_request(origin, backend->r);
            }

            /* Clear hop-by-hop headers */
            for (i=0; hop_by_hop_hdrs[i]; ++i) {
                apr_table_unset(r->headers_out, hop_by_hop_hdrs[i]);
            }

            /* Delete warnings with wrong date */
            r->headers_out = ap_proxy_clean_warnings(p, r->headers_out);

            /* handle Via header in response */
            if (conf->viaopt != via_off && conf->viaopt != via_block) {
                const char *server_name = ap_get_server_name(r);
                /* If USE_CANONICAL_NAME_OFF was configured for the proxy virtual host,
                 * then the server name returned by ap_get_server_name() is the
                 * origin server name (which does make too much sense with Via: headers)
                 * so we use the proxy vhost's name instead.
                 */
                if (server_name == r->hostname)
                    server_name = r->server->server_hostname;
                /* create a "Via:" response header entry and merge it */
                apr_table_addn(r->headers_out, "Via",
                               (conf->viaopt == via_full)
                                     ? apr_psprintf(p, "%d.%d %s%s (%s)",
                                           HTTP_VERSION_MAJOR(r->proto_num),
                                           HTTP_VERSION_MINOR(r->proto_num),
                                           server_name,
                                           server_portstr,
                                           AP_SERVER_BASEVERSION)
                                     : apr_psprintf(p, "%d.%d %s%s",
                                           HTTP_VERSION_MAJOR(r->proto_num),
                                           HTTP_VERSION_MINOR(r->proto_num),
                                           server_name,
                                           server_portstr)
                );
            }

            /* cancel keepalive if HTTP/1.0 or less */
            if ((major < 1) || (minor < 1)) {
                backend->close = 1;
                origin->keepalive = AP_CONN_CLOSE;
            }
        } else {
            /* an http/0.9 response */
            backasswards = 1;
            r->status = 200;
            r->status_line = "200 OK";
            backend->close = 1;
        }

        if (ap_is_HTTP_INFO(proxy_status)) {
            interim_response++;
            /* Reset to old timeout iff we've adjusted it */
            if (do_100_continue
                && (r->status == HTTP_CONTINUE)
                && (worker->s->ping_timeout != old_timeout)) {
                    apr_socket_timeout_set(backend->sock, old_timeout);
            }
        }
        else {
            interim_response = 0;
        }
        if (interim_response) {
            /* RFC2616 tells us to forward this.
             *
             * OTOH, an interim response here may mean the backend
             * is playing sillybuggers.  The Client didn't ask for
             * it within the defined HTTP/1.1 mechanisms, and if
             * it's an extension, it may also be unsupported by us.
             *
             * There's also the possibility that changing existing
             * behaviour here might break something.
             *
             * So let's make it configurable.
             *
             * We need to set "r->expecting_100 = 1" otherwise origin
             * server behaviour will apply.
             */
            const char *policy = apr_table_get(r->subprocess_env,
                                               "proxy-interim-response");
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "HTTP: received interim %d response", r->status);
            if (!policy
                    || (!strcasecmp(policy, "RFC") && ((r->expecting_100 = 1)))) {
                ap_send_interim_response(r, 1);
            }
            /* FIXME: refine this to be able to specify per-response-status
             * policies and maybe also add option to bail out with 502
             */
            else if (strcasecmp(policy, "Suppress")) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01108)
                              "undefined proxy interim response policy");
            }
        }
        /* Moved the fixups of Date headers and those affected by
         * ProxyPassReverse/etc from here to ap_proxy_read_headers
         */

        if ((proxy_status == 401) && (dconf->error_override)) {
            const char *buf;
            const char *wa = "WWW-Authenticate";
            if ((buf = apr_table_get(r->headers_out, wa))) {
                apr_table_set(r->err_headers_out, wa, buf);
            } else {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01109)
                              "origin server sent 401 without "
                              "WWW-Authenticate header");
            }
        }

        r->sent_bodyct = 1;
        /*
         * Is it an HTTP/0.9 response or did we maybe preread the 1st line of
         * the response? If so, load the extra data. These are 2 mutually
         * exclusive possibilities, that just happen to require very
         * similar behavior.
         */
        if (backasswards || pread_len) {
            apr_ssize_t cntr = (apr_ssize_t)pread_len;
            if (backasswards) {
                /*@@@FIXME:
                 * At this point in response processing of a 0.9 response,
                 * we don't know yet whether data is binary or not.
                 * mod_charset_lite will get control later on, so it cannot
                 * decide on the conversion of this buffer full of data.
                 * However, chances are that we are not really talking to an
                 * HTTP/0.9 server, but to some different protocol, therefore
                 * the best guess IMHO is to always treat the buffer as "text/x":
                 */
                ap_xlate_proto_to_ascii(buffer, len);
                cntr = (apr_ssize_t)len;
            }
            e = apr_bucket_heap_create(buffer, cntr, NULL, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
        }
        /* PR 41646: get HEAD right with ProxyErrorOverride */
        if (ap_is_HTTP_ERROR(r->status) && dconf->error_override) {
            /* clear r->status for override error, otherwise ErrorDocument
             * thinks that this is a recursive error, and doesn't find the
             * custom error page
             */
            r->status = HTTP_OK;
            /* Discard body, if one is expected */
        if (!r->header_only && !AP_STATUS_IS_HEADER_ONLY(proxy_status)) {
                const char *tmp;
                /* Add minimal headers needed to allow http_in filter
                 * detecting end of body without waiting for a timeout. */
                if ((tmp = apr_table_get(r->headers_out, "Transfer-Encoding"))) {
                    apr_table_set(backend->r->headers_in, "Transfer-Encoding", tmp);
                }
                else if ((tmp = apr_table_get(r->headers_out, "Content-Length"))) {
                    apr_table_set(backend->r->headers_in, "Content-Length", tmp);
                }
                else if (te) {
                    apr_table_set(backend->r->headers_in, "Transfer-Encoding", te);
                }
                ap_discard_request_body(backend->r);
            }
            /*
             * prevent proxy_handler() from treating this as an
             * internal error.
             */
            apr_table_setn(r->notes, "proxy-error-override", "1");
            return proxy_status;
        }

        /* send body - but only if a body is expected */
        if ((!r->header_only) &&                   /* not HEAD request */
            !interim_response &&                   /* not any 1xx response */
            (proxy_status != HTTP_NO_CONTENT) &&      /* not 204 */
            (proxy_status != HTTP_NOT_MODIFIED)) {    /* not 304 */

            /* We need to copy the output headers and treat them as input
             * headers as well.  BUT, we need to do this before we remove
             * TE, so that they are preserved accordingly for
             * ap_http_filter to know where to end.
             */
            backend->r->headers_in = apr_table_clone(backend->r->pool, r->headers_out);
            /*
             * Restore Transfer-Encoding header from response if we saved
             * one before and there is none left. We need it for the
             * ap_http_filter. See above.
             */
            if (te && !apr_table_get(backend->r->headers_in, "Transfer-Encoding")) {
                apr_table_add(backend->r->headers_in, "Transfer-Encoding", te);
            }

            apr_table_unset(r->headers_out,"Transfer-Encoding");

            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "start body send");

            /*
             * if we are overriding the errors, we can't put the content
             * of the page into the brigade
             */
            if (!dconf->error_override || !ap_is_HTTP_ERROR(proxy_status)) {
                /* read the body, pass it to the output filters */
                apr_read_type_e mode = APR_NONBLOCK_READ;
                int finish = FALSE;

                /* Handle the case where the error document is itself reverse
                 * proxied and was successful. We must maintain any previous
                 * error status so that an underlying error (eg HTTP_NOT_FOUND)
                 * doesn't become an HTTP_OK.
                 */
                if (dconf->error_override && !ap_is_HTTP_ERROR(proxy_status)
                        && ap_is_HTTP_ERROR(original_status)) {
                    r->status = original_status;
                    r->status_line = original_status_line;
                }

                do {
                    apr_off_t readbytes;
                    apr_status_t rv;

                    rv = ap_get_brigade(backend->r->input_filters, bb,
                                        AP_MODE_READBYTES, mode,
                                        conf->io_buffer_size);

                    /* ap_get_brigade will return success with an empty brigade
                     * for a non-blocking read which would block: */
                    if (mode == APR_NONBLOCK_READ
                        && (APR_STATUS_IS_EAGAIN(rv)
                            || (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)))) {
                        /* flush to the client and switch to blocking mode */
                        e = apr_bucket_flush_create(c->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(bb, e);
                        if (ap_pass_brigade(r->output_filters, bb)
                            || c->aborted) {
                            backend->close = 1;
                            break;
                        }
                        apr_brigade_cleanup(bb);
                        mode = APR_BLOCK_READ;
                        continue;
                    }
                    else if (rv == APR_EOF) {
                        backend->close = 1;
                        break;
                    }
                    else if (rv != APR_SUCCESS) {
                        /* In this case, we are in real trouble because
                         * our backend bailed on us. Pass along a 502 error
                         * error bucket
                         */
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01110)
                                      "error reading response");
                        ap_proxy_backend_broke(r, bb);
                        ap_pass_brigade(r->output_filters, bb);
                        backend_broke = 1;
                        backend->close = 1;
                        break;
                    }
                    /* next time try a non-blocking read */
                    mode = APR_NONBLOCK_READ;

                    if (!apr_is_empty_table(backend->r->trailers_in)) {
                        apr_table_do(add_trailers, r->trailers_out,
                                backend->r->trailers_in, NULL);
                        apr_table_clear(backend->r->trailers_in);
                    }

                    apr_brigade_length(bb, 0, &readbytes);
                    backend->worker->s->read += readbytes;
#if DEBUGGING
                    {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01111)
                                  "readbytes: %#x", readbytes);
                    }
#endif
                    /* sanity check */
                    if (APR_BRIGADE_EMPTY(bb)) {
                        break;
                    }

                    /* Switch the allocator lifetime of the buckets */
                    ap_proxy_buckets_lifetime_transform(r, bb, pass_bb);

                    /* found the last brigade? */
                    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(pass_bb))) {

                        /* signal that we must leave */
                        finish = TRUE;

                        /* the brigade may contain transient buckets that contain
                         * data that lives only as long as the backend connection.
                         * Force a setaside so these transient buckets become heap
                         * buckets that live as long as the request.
                         */
                        for (e = APR_BRIGADE_FIRST(pass_bb); e
                                != APR_BRIGADE_SENTINEL(pass_bb); e
                                = APR_BUCKET_NEXT(e)) {
                            apr_bucket_setaside(e, r->pool);
                        }

                        /* finally it is safe to clean up the brigade from the
                         * connection pool, as we have forced a setaside on all
                         * buckets.
                         */
                        apr_brigade_cleanup(bb);

                        /* make sure we release the backend connection as soon
                         * as we know we are done, so that the backend isn't
                         * left waiting for a slow client to eventually
                         * acknowledge the data.
                         */
                        ap_proxy_release_connection(backend->worker->s->scheme,
                                backend, r->server);
                        /* Ensure that the backend is not reused */
                        *backend_ptr = NULL;

                    }

                    /* try send what we read */
                    if (ap_pass_brigade(r->output_filters, pass_bb) != APR_SUCCESS
                        || c->aborted) {
                        /* Ack! Phbtt! Die! User aborted! */
                        /* Only close backend if we haven't got all from the
                         * backend. Furthermore if *backend_ptr is NULL it is no
                         * longer safe to fiddle around with backend as it might
                         * be already in use by another thread.
                         */
                        if (*backend_ptr) {
                            backend->close = 1;  /* this causes socket close below */
                        }
                        finish = TRUE;
                    }

                    /* make sure we always clean up after ourselves */
                    apr_brigade_cleanup(pass_bb);
                    apr_brigade_cleanup(bb);

                } while (!finish);
            }
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "end body send");
        }
        else if (!interim_response) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "header only");

            /* make sure we release the backend connection as soon
             * as we know we are done, so that the backend isn't
             * left waiting for a slow client to eventually
             * acknowledge the data.
             */
            ap_proxy_release_connection(backend->worker->s->scheme,
                    backend, r->server);
            *backend_ptr = NULL;

            /* Pass EOS bucket down the filter chain. */
            e = apr_bucket_eos_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            ap_pass_brigade(r->output_filters, bb);

            apr_brigade_cleanup(bb);
        }
    } while (interim_response && (interim_response < AP_MAX_INTERIM_RESPONSES));

    /* We have to cleanup bb brigade, because buckets inserted to it could be
     * created from scpool and this pool can be freed before this brigade. */
    apr_brigade_cleanup(bb);

    /* See define of AP_MAX_INTERIM_RESPONSES for why */
    if (interim_response >= AP_MAX_INTERIM_RESPONSES) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             apr_psprintf(p,
                             "Too many (%d) interim responses from origin server",
                             interim_response));
    }

    /* If our connection with the client is to be aborted, return DONE. */
    if (c->aborted || backend_broke) {
        return DONE;
    }

    return OK;
}

static
apr_status_t ap_proxy_http_cleanup(const char *scheme, request_rec *r,
                                   proxy_conn_rec *backend)
{
    ap_proxy_release_connection(scheme, backend, r->server);
    return OK;
}

/*
 * This handles http:// URLs, and other URLs using a remote proxy over http
 * If proxyhost is NULL, then contact the server directly, otherwise
 * go via the proxy.
 * Note that if a proxy is used, then URLs other than http: can be accessed,
 * also, if we have trouble which is clearly specific to the proxy, then
 * we return DECLINED so that we can try another proxy. (Or the direct
 * route.)
 */
static int proxy_http_handler(request_rec *r, proxy_worker *worker,
                              proxy_server_conf *conf,
                              char *url, const char *proxyname,
                              apr_port_t proxyport)
{
    int status;
    char server_portstr[32];
    char *scheme;
    const char *proxy_function;
    const char *u;
    proxy_conn_rec *backend = NULL;
    int is_ssl = 0;
    conn_rec *c = r->connection;
    int retry = 0;
    /*
     * Use a shorter-lived pool to reduce memory usage
     * and avoid a memory leak
     */
    apr_pool_t *p = r->pool;
    apr_uri_t *uri = apr_palloc(p, sizeof(*uri));

    /* find the scheme */
    u = strchr(url, ':');
    if (u == NULL || u[1] != '/' || u[2] != '/' || u[3] == '\0')
       return DECLINED;
    if ((u - url) > 14)
        return HTTP_BAD_REQUEST;
    scheme = apr_pstrmemdup(p, url, u - url);
    /* scheme is lowercase */
    ap_str_tolower(scheme);
    /* is it for us? */
    if (strcmp(scheme, "https") == 0) {
        if (!ap_proxy_ssl_enable(NULL)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01112)
                          "HTTPS: declining URL %s (mod_ssl not configured?)",
                          url);
            return DECLINED;
        }
        is_ssl = 1;
        proxy_function = "HTTPS";
    }
    else if (!(strcmp(scheme, "http") == 0 || (strcmp(scheme, "ftp") == 0 && proxyname))) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01113) "HTTP: declining URL %s",
                      url);
        return DECLINED; /* only interested in HTTP, or FTP via proxy */
    }
    else {
        if (*scheme == 'h')
            proxy_function = "HTTP";
        else
            proxy_function = "FTP";
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "HTTP: serving URL %s", url);


    /* create space for state information */
    if ((status = ap_proxy_acquire_connection(proxy_function, &backend,
                                              worker, r->server)) != OK)
        goto cleanup;

    backend->is_ssl = is_ssl;

    /*
     * In the case that we are handling a reverse proxy connection and this
     * is not a request that is coming over an already kept alive connection
     * with the client, do NOT reuse the connection to the backend, because
     * we cannot forward a failure to the client in this case as the client
     * does NOT expect this in this situation.
     * Yes, this creates a performance penalty.
     */
    if ((r->proxyreq == PROXYREQ_REVERSE) && (!c->keepalives)
        && (apr_table_get(r->subprocess_env, "proxy-initial-not-pooled"))) {
        backend->close = 1;
    }

    while (retry < 2) {
        char *locurl = url;

        /* Step One: Determine Who To Connect To */
        if ((status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                                uri, &locurl, proxyname,
                                                proxyport, server_portstr,
                                                sizeof(server_portstr))) != OK)
            break;

        /* Step Two: Make the Connection */
        if (ap_proxy_check_connection(proxy_function, backend, r->server, 1,
                                      PROXY_CHECK_CONN_EMPTY)
                && ap_proxy_connect_backend(proxy_function, backend, worker,
                                            r->server)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01114)
                          "HTTP: failed to make connection to backend: %s",
                          backend->hostname);
            status = HTTP_SERVICE_UNAVAILABLE;
            break;
        }

        /* Step Three: Create conn_rec */
        if (!backend->connection) {
            if ((status = ap_proxy_connection_create_ex(proxy_function,
                                                        backend, r)) != OK)
                break;
            /*
             * On SSL connections set a note on the connection what CN is
             * requested, such that mod_ssl can check if it is requested to do
             * so.
             */
            if (backend->ssl_hostname) {
                apr_table_setn(backend->connection->notes,
                               "proxy-request-hostname",
                               backend->ssl_hostname);
            }
        }

        /* Step Four: Send the Request
         * On the off-chance that we forced a 100-Continue as a
         * kinda HTTP ping test, allow for retries
         */
        if ((status = ap_proxy_http_request(p, r, backend, worker,
                                        conf, uri, locurl, server_portstr)) != OK) {
            if ((status == HTTP_SERVICE_UNAVAILABLE) && worker->s->ping_timeout_set) {
                backend->close = 1;
                ap_log_rerror(APLOG_MARK, APLOG_INFO, status, r, APLOGNO(01115)
                              "HTTP: 100-Continue failed to %pI (%s)",
                              worker->cp->addr, worker->s->hostname_ex);
                retry++;
                continue;
            } else {
                break;
            }

        }

        /* Step Five: Receive the Response... Fall thru to cleanup */
        status = ap_proxy_http_process_response(p, r, &backend, worker,
                                                conf, server_portstr);

        break;
    }

    /* Step Six: Clean Up */
cleanup:
    if (backend) {
        if (status != OK)
            backend->close = 1;
        ap_proxy_http_cleanup(proxy_function, r, backend);
    }
    return status;
}

/* post_config hook: */
static int proxy_http_post_config(apr_pool_t *pconf, apr_pool_t *plog,
        apr_pool_t *ptemp, server_rec *s)
{

    /* proxy_http_post_config() will be called twice during startup.  So, don't
     * set up the static data the 1st time through. */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }

    ap_proxy_clear_connection_fn =
            APR_RETRIEVE_OPTIONAL_FN(ap_proxy_clear_connection);
    if (!ap_proxy_clear_connection_fn) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02477)
                     "mod_proxy must be loaded for mod_proxy_http");
        return !OK;
    }

    return OK;
}

static void ap_proxy_http_register_hook(apr_pool_t *p)
{
    ap_hook_post_config(proxy_http_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    proxy_hook_scheme_handler(proxy_http_handler, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(proxy_http_canon, NULL, NULL, APR_HOOK_FIRST);
    warn_rx = ap_pregcomp(p, "[0-9]{3}[ \t]+[^ \t]+[ \t]+\"[^\"]*\"([ \t]+\"([^\"]+)\")?", 0);
}

AP_DECLARE_MODULE(proxy_http) = {
    STANDARD20_MODULE_STUFF,
    NULL,              /* create per-directory config structure */
    NULL,              /* merge per-directory config structures */
    NULL,              /* create per-server config structure */
    NULL,              /* merge per-server config structures */
    NULL,              /* command apr_table_t */
    ap_proxy_http_register_hook/* register hooks */
};

