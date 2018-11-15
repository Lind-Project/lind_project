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

#include "apr_strings.h"
#include "apr_md5.h"            /* for apr_password_validate */

#include "ap_config.h"
#include "ap_provider.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_request.h"

#include "mod_auth.h"

typedef struct {
    char *pwfile;
} authn_file_config_rec;

static APR_OPTIONAL_FN_TYPE(ap_authn_cache_store) *authn_cache_store = NULL;
#define AUTHN_CACHE_STORE(r,user,realm,data) \
    if (authn_cache_store != NULL) \
        authn_cache_store((r), "file", (user), (realm), (data))

static void *create_authn_file_dir_config(apr_pool_t *p, char *d)
{
    authn_file_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->pwfile = NULL;     /* just to illustrate the default really */
    return conf;
}

static const command_rec authn_file_cmds[] =
{
    AP_INIT_TAKE1("AuthUserFile", ap_set_file_slot,
                  (void *)APR_OFFSETOF(authn_file_config_rec, pwfile),
                  OR_AUTHCFG, "text file containing user IDs and passwords"),
    {NULL}
};

module AP_MODULE_DECLARE_DATA authn_file_module;

static authn_status check_password(request_rec *r, const char *user,
                                   const char *password)
{
    authn_file_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &authn_file_module);
    ap_configfile_t *f;
    char l[MAX_STRING_LEN];
    apr_status_t status;
    char *file_password = NULL;

    if (!conf->pwfile) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01619)
                      "AuthUserFile not specified in the configuration");
        return AUTH_GENERAL_ERROR;
    }

    status = ap_pcfg_openfile(&f, r->pool, conf->pwfile);

    if (status != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01620)
                      "Could not open password file: %s", conf->pwfile);
        return AUTH_GENERAL_ERROR;
    }

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
        const char *rpw, *w;

        /* Skip # or blank lines. */
        if ((l[0] == '#') || (!l[0])) {
            continue;
        }

        rpw = l;
        w = ap_getword(r->pool, &rpw, ':');

        if (!strcmp(user, w)) {
            file_password = ap_getword(r->pool, &rpw, ':');
            break;
        }
    }
    ap_cfg_closefile(f);

    if (!file_password) {
        return AUTH_USER_NOT_FOUND;
    }
    AUTHN_CACHE_STORE(r, user, NULL, file_password);

    status = apr_password_validate(password, file_password);
    if (status != APR_SUCCESS) {
        return AUTH_DENIED;
    }

    return AUTH_GRANTED;
}

static authn_status get_realm_hash(request_rec *r, const char *user,
                                   const char *realm, char **rethash)
{
    authn_file_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &authn_file_module);
    ap_configfile_t *f;
    char l[MAX_STRING_LEN];
    apr_status_t status;
    char *file_hash = NULL;

    if (!conf->pwfile) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01621)
                      "AuthUserFile not specified in the configuration");
        return AUTH_GENERAL_ERROR;
    }

    status = ap_pcfg_openfile(&f, r->pool, conf->pwfile);

    if (status != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01622)
                      "Could not open password file: %s", conf->pwfile);
        return AUTH_GENERAL_ERROR;
    }

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
        const char *rpw, *w, *x;

        /* Skip # or blank lines. */
        if ((l[0] == '#') || (!l[0])) {
            continue;
        }

        rpw = l;
        w = ap_getword(r->pool, &rpw, ':');
        x = ap_getword(r->pool, &rpw, ':');

        if (x && w && !strcmp(user, w) && !strcmp(realm, x)) {
            /* Remember that this is a md5 hash of user:realm:password.  */
            file_hash = ap_getword(r->pool, &rpw, ':');
            break;
        }
    }
    ap_cfg_closefile(f);

    if (!file_hash) {
        return AUTH_USER_NOT_FOUND;
    }

    *rethash = file_hash;
    AUTHN_CACHE_STORE(r, user, realm, file_hash);

    return AUTH_USER_FOUND;
}

static const authn_provider authn_file_provider =
{
    &check_password,
    &get_realm_hash,
};

static void opt_retr(void)
{
    authn_cache_store = APR_RETRIEVE_OPTIONAL_FN(ap_authn_cache_store);
}
static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHN_PROVIDER_GROUP, "file",
                              AUTHN_PROVIDER_VERSION,
                              &authn_file_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_optional_fn_retrieve(opt_retr, NULL, NULL, APR_HOOK_MIDDLE);
}

AP_DECLARE_MODULE(authn_file) =
{
    STANDARD20_MODULE_STUFF,
    create_authn_file_dir_config,    /* dir config creater */
    NULL,                            /* dir merger --- default is to override */
    NULL,                            /* server config */
    NULL,                            /* merge server config */
    authn_file_cmds,                 /* command apr_table_t */
    register_hooks                   /* register hooks */
};
