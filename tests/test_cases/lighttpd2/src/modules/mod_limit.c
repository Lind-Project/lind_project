/*
 * mod_limit - limit concurrent connections or requests per second
 *
 * Author:
 *     Copyright (c) 2010 Thomas Porzelt
 * License:
 *     MIT, see COPYING file in the lighttpd 2 tree
 */

#include <lighttpd/base.h>
#include <lighttpd/radix.h>

LI_API gboolean mod_limit_init(liModules *mods, liModule *mod);
LI_API gboolean mod_limit_free(liModules *mods, liModule *mod);

typedef enum {
	ML_TYPE_CON,
	ML_TYPE_CON_IP,
	ML_TYPE_REQ,
	ML_TYPE_REQ_IP
} mod_limit_context_type;

struct mod_limit_context {
	mod_limit_context_type type;
	gint limit;
	gint refcount;
	GMutex *mutex;           /* used when type != ML_TYPE_CON */
	liPlugin *plugin;
	liAction *action_limit_reached;

	union {
		gint con;            /* decreased on vr_close */
		liRadixTree *con_ip; /* radix tree contains gint, removed on vr_close */
		struct {
			gint num;
			time_t ts;
		} req;               /* reset when now - ts > 1 */
		liRadixTree *req_ip; /* radix tree contains (mod_limit_req_ip_data*), removed via waitqueue timer */
	} pool;
};
typedef struct mod_limit_context mod_limit_context;

struct mod_limit_req_ip_data {
	gint requests;
	liWaitQueueElem timeout_elem;
	liSocketAddress ip;
	mod_limit_context *ctx;
};
typedef struct mod_limit_req_ip_data mod_limit_req_ip_data;

struct mod_limit_data {
	liWaitQueue *timeout_queues; /* each worker has its own timeout queue */
};
typedef struct mod_limit_data mod_limit_data;


static mod_limit_context* mod_limit_context_new(mod_limit_context_type type, gint limit, liAction *action_limit_reached, liPlugin *plugin) {
	mod_limit_context *ctx = g_slice_new0(mod_limit_context);
	ctx->type = type;
	ctx->limit = limit;
	ctx->action_limit_reached = action_limit_reached;
	ctx->plugin = plugin;
	ctx->refcount = 1;

	switch (type) {
	case ML_TYPE_CON:
		ctx->pool.con = 0;
		break;
	case ML_TYPE_CON_IP:
		ctx->pool.con_ip = li_radixtree_new();
		ctx->mutex = g_mutex_new();
		break;
	case ML_TYPE_REQ:
		ctx->pool.req.num = 0;
		ctx->pool.req.ts = 0;
		break;
	case ML_TYPE_REQ_IP:
		ctx->pool.req_ip = li_radixtree_new();
		ctx->mutex = g_mutex_new();
		break;
	}

	return ctx;
}

static void mod_limit_context_free(liServer *srv, mod_limit_context *ctx) {
	if (ctx->mutex)
		g_mutex_free(ctx->mutex);

	if (ctx->action_limit_reached) {
		li_action_release(srv, ctx->action_limit_reached);
	}

	switch (ctx->type) {
	case ML_TYPE_CON:
		break;
	case ML_TYPE_CON_IP:
		li_radixtree_free(ctx->pool.con_ip, NULL, NULL);
		break;
	case ML_TYPE_REQ:
		break;
	case ML_TYPE_REQ_IP:
		li_radixtree_free(ctx->pool.req_ip, NULL, NULL);
		break;
	}

	g_slice_free(mod_limit_context, ctx);
}

static void mod_limit_timeout_callback(liWaitQueue *wq, gpointer data) {
	liWaitQueueElem *wqe;
	mod_limit_req_ip_data *rid;
	gpointer addr;
	guint32 bits;

	UNUSED(data);

	while ((wqe = li_waitqueue_pop(wq)) != NULL) {
		rid = wqe->data;

		/* IPv4 or IPv6? */
		if (rid->ip.addr->plain.sa_family == AF_INET) {
			addr = &rid->ip.addr->ipv4.sin_addr.s_addr;
			bits = 32;
		} else {
			addr = &rid->ip.addr->ipv6.sin6_addr.s6_addr;
			bits = 128;
		}

		g_mutex_lock(rid->ctx->mutex);
		li_radixtree_remove(rid->ctx->pool.req_ip, addr, bits);
		g_mutex_unlock(rid->ctx->mutex);
		li_sockaddr_clear(&rid->ip);
		g_slice_free(mod_limit_req_ip_data, rid);
	}

	li_waitqueue_update(wq);
}

static void mod_limit_vrclose(liVRequest *vr, liPlugin *p) {
	GPtrArray *arr = g_ptr_array_index(vr->plugin_ctx, p->id);
	mod_limit_context *ctx;
	guint i;
	gint cons;
	liSocketAddress *remote_addr = &vr->coninfo->remote_addr;
	gpointer addr;
	guint32 bits;

	if (!arr)
		return;

	for (i = 0; i < arr->len; i++) {
		ctx = g_ptr_array_index(arr, i);

		switch (ctx->type) {
		case ML_TYPE_CON:
			g_atomic_int_add(&ctx->pool.con, -1);
			break;
		case ML_TYPE_CON_IP:
			/* IPv4 or IPv6? */
			if (remote_addr->addr->plain.sa_family == AF_INET) {
				addr = &remote_addr->addr->ipv4.sin_addr.s_addr;
				bits = 32;
			} else {
				addr = &remote_addr->addr->ipv6.sin6_addr.s6_addr;
				bits = 128;
			}

			g_mutex_lock(ctx->mutex);
			cons = GPOINTER_TO_INT(li_radixtree_lookup_exact(ctx->pool.con_ip, addr, bits));
			cons--;
			if (!cons) {
				li_radixtree_remove(ctx->pool.con_ip, addr, bits);
			} else {
				li_radixtree_insert(ctx->pool.con_ip, addr, bits, GINT_TO_POINTER(cons));
			}
			g_mutex_unlock(ctx->mutex);
			break;
		default:
			break;
		}

		if (g_atomic_int_dec_and_test(&ctx->refcount)) {
			mod_limit_context_free(vr->wrk->srv, ctx);
		}
	}

	g_ptr_array_free(arr, TRUE);
}

static liHandlerResult mod_limit_action_handle(liVRequest *vr, gpointer param, gpointer *context) {
	gboolean limit_reached = FALSE;
	mod_limit_context *ctx = (mod_limit_context*) param;
	GPtrArray *arr = g_ptr_array_index(vr->plugin_ctx, ctx->plugin->id);
	gint cons;
	mod_limit_req_ip_data *rid;
	liSocketAddress *remote_addr = &vr->coninfo->remote_addr;
	gpointer addr;
	guint32 bits;

	UNUSED(context);

	if (li_vrequest_is_handled(vr)) {
		VR_DEBUG(vr, "%s", "mod_limit: already have a content handler - ignoring limits. Put limit.* before content handlers such as 'static', 'fastcgi' or 'proxy'");
		return LI_HANDLER_GO_ON;
	}

	/* IPv4 or IPv6? */
	switch (remote_addr->addr->plain.sa_family) {
	case AF_INET:
		addr = &remote_addr->addr->ipv4.sin_addr.s_addr;
		bits = 32;
		break;
	case AF_INET6:
		addr = &remote_addr->addr->ipv6.sin6_addr.s6_addr;
		bits = 128;
		break;
	default:
		if (ctx->type == ML_TYPE_CON_IP || ctx->type == ML_TYPE_REQ_IP) {
			VR_DEBUG(vr, "%s", "mod_limit only supports ipv4 or ipv6 clients");
			return LI_HANDLER_ERROR;
		}
		addr = NULL;
		bits = 0;
	}

	if (!arr) {
		/* request is not in any context yet, create new array */
		arr = g_ptr_array_sized_new(2);
		g_ptr_array_index(vr->plugin_ctx, ctx->plugin->id) = arr;
	}

	switch (ctx->type) {
	case ML_TYPE_CON:
#ifdef GLIB_VERSION_2_30
		/* since 2.30 g_atomic_int_add does the same as g_atomic_int_exchange_and_add,
		 * before it didn't return the old value. this fixes the deprecation warning. */
		if (g_atomic_int_add(&ctx->pool.con, 1) > ctx->limit) {
			g_atomic_int_add(&ctx->pool.con, -1);
			limit_reached = TRUE;
			VR_DEBUG(vr, "limit.con: limit reached (%d active connections)", ctx->limit);
		}
#else
		if (g_atomic_int_exchange_and_add(&ctx->pool.con, 1) > ctx->limit) {
			g_atomic_int_add(&ctx->pool.con, -1);
			limit_reached = TRUE;
			VR_DEBUG(vr, "limit.con: limit reached (%d active connections)", ctx->limit);
		}
#endif
		break;
	case ML_TYPE_CON_IP:
		g_mutex_lock(ctx->mutex);
		cons = GPOINTER_TO_INT(li_radixtree_lookup_exact(ctx->pool.con_ip, addr, bits));
		if (cons < ctx->limit) {
			li_radixtree_insert(ctx->pool.con_ip, addr, bits, GINT_TO_POINTER(cons+1));
		} else {
			limit_reached = TRUE;
			VR_DEBUG(vr, "limit.con_ip: limit reached (%d active connections)", ctx->limit);
		}
		g_mutex_unlock(ctx->mutex);
		break;
	case ML_TYPE_REQ:
		g_mutex_lock(ctx->mutex);
		if (li_cur_ts(vr->wrk) - ctx->pool.req.ts > 1.0) {
			/* reset pool */
			ctx->pool.req.ts = li_cur_ts(vr->wrk);
			ctx->pool.req.num = 1;
		} else {
			ctx->pool.req.num++;
			if (ctx->pool.req.num > ctx->limit) {
				limit_reached = TRUE;
				VR_DEBUG(vr, "limit.req: limit reached (%d req/s)", ctx->limit);
			}
		}
		g_mutex_unlock(ctx->mutex);
		break;
	case ML_TYPE_REQ_IP:
		g_mutex_lock(ctx->mutex);
		rid = li_radixtree_lookup_exact(ctx->pool.req_ip, addr, bits);
		if (!rid) {
			/* IP not known */
			rid = g_slice_new0(mod_limit_req_ip_data);
			rid->requests = 1;
			rid->ip = li_sockaddr_dup(*remote_addr);
			rid->ctx = ctx;
			rid->timeout_elem.data = rid;
			li_radixtree_insert(ctx->pool.req_ip, addr, bits, rid);
			li_waitqueue_push(&(((mod_limit_data*)ctx->plugin->data)->timeout_queues[vr->wrk->ndx]), &rid->timeout_elem);
		} else if (rid->requests < ctx->limit) {
			rid->requests++;
		} else {
			limit_reached = TRUE;
			VR_DEBUG(vr, "limit.req_ip: limit reached (%d req/s)", ctx->limit);
		}
		g_mutex_unlock(ctx->mutex);
		break;
	}

	if (limit_reached) {
		/* limit reached, we either execute the defined action or return a 503 error page */
		if (ctx->action_limit_reached) {
			/* execute action */
			li_action_enter(vr, ctx->action_limit_reached);
		} else {
			/* return 503 error page */
			if (!li_vrequest_handle_direct(vr)) {
				return LI_HANDLER_ERROR;
			}

			vr->response.http_status = 503;
		}
	} else {
		g_ptr_array_add(arr, ctx);
		g_atomic_int_inc(&ctx->refcount);
	}

	return LI_HANDLER_GO_ON;
}

static void mod_limit_action_free(liServer *srv, gpointer param) {
	mod_limit_context *ctx = param;

	if (g_atomic_int_dec_and_test(&ctx->refcount)) {
		mod_limit_context_free(srv, ctx);
	}
}

static liAction* mod_limit_action_create(liServer *srv, liPlugin *p, mod_limit_context_type type, liValue *val) {
	const char* act_names[] = { "limit.con", "limit.con_ip", "limit.req", "limit.req_ip" };
	mod_limit_context *ctx;
	gint limit = 0;
	liAction *action_limit_reached = NULL;

	val = li_value_get_single_argument(val);
	val = li_value_get_single_argument(val);

	if (LI_VALUE_NUMBER == li_value_type(val) && val->data.number > 0) {
		/* limit.* N; */
		limit = val->data.number;
		action_limit_reached = NULL;
	} else if (LI_VALUE_LIST == li_value_type(val)
			&& li_value_list_has_len(val, 2)
			&& LI_VALUE_NUMBER == li_value_list_type_at(val, 0)
			&& li_value_list_at(val, 0)->data.number > 0
			&& LI_VALUE_ACTION == li_value_list_type_at(val, 1)) {

		limit = li_value_list_at(val, 0)->data.number;
		action_limit_reached = li_value_extract_action(li_value_list_at(val, 1));
	} else {
		ERROR(srv, "%s expects either an integer > 0 as parameter, or a list of (int > 0,action)", act_names[type]);
		return NULL;
	}

	ctx = mod_limit_context_new(type, limit, action_limit_reached, p);

	return li_action_new_function(mod_limit_action_handle, NULL, mod_limit_action_free, ctx);
}

static liAction* mod_limit_action_con_create(liServer *srv, liWorker *wrk, liPlugin *p, liValue *val, gpointer userdata) {
	UNUSED(wrk); UNUSED(userdata);

	return mod_limit_action_create(srv, p, ML_TYPE_CON, val);
}

static liAction* mod_limit_action_con_ip_create(liServer *srv, liWorker *wrk, liPlugin* p, liValue *val, gpointer userdata) {
	UNUSED(wrk); UNUSED(userdata);

	return mod_limit_action_create(srv, p, ML_TYPE_CON_IP, val);
}

static liAction* mod_limit_action_req_create(liServer *srv, liWorker *wrk, liPlugin* p, liValue *val, gpointer userdata) {
	UNUSED(wrk); UNUSED(userdata);

	return mod_limit_action_create(srv, p, ML_TYPE_REQ, val);
}

static liAction* mod_limit_action_req_ip_create(liServer *srv, liWorker *wrk, liPlugin* p, liValue *val, gpointer userdata) {
	UNUSED(wrk); UNUSED(userdata);

	return mod_limit_action_create(srv, p, ML_TYPE_REQ_IP, val);
}


static const liPluginOption options[] = {
	{ NULL, 0, 0, NULL }
};

static const liPluginOptionPtr optionptrs[] = {
	{ NULL, 0, NULL, NULL, NULL }
};

static const liPluginAction actions[] = {
	{ "limit.con", mod_limit_action_con_create, NULL },
	{ "limit.con_ip", mod_limit_action_con_ip_create, NULL },
	{ "limit.req", mod_limit_action_req_create, NULL },
	{ "limit.req_ip", mod_limit_action_req_ip_create, NULL },

	{ NULL, NULL, NULL }
};

static const liPluginSetup setups[] = {
	{ NULL, NULL, NULL }
};

static void mod_limit_prepare_worker(liServer *srv, liPlugin *p, liWorker *wrk) {
	static gint once = 0;
	mod_limit_data *mld;

	/* initialize once */
	if (g_atomic_int_compare_and_exchange(&once, 0, 1)) {
		mld = g_slice_new(mod_limit_data);
		p->data = mld;
		mld->timeout_queues = g_new0(liWaitQueue, srv->worker_count);
		g_atomic_int_set(&once, 2);
	} else {
		while (g_atomic_int_get(&once) != 2) { }
		mld = p->data;
	}

	li_waitqueue_init(&(mld->timeout_queues[wrk->ndx]), &wrk->loop, "mod_limit timeout queue", mod_limit_timeout_callback, 1.0, NULL);
}

static void plugin_limit_free(liServer *srv, liPlugin *p) {
	mod_limit_data *mld = p->data;

	UNUSED(srv); UNUSED(p);

	if (mld) {
		g_free(mld->timeout_queues);
		g_slice_free(mod_limit_data, mld);
	}
}

static void plugin_limit_init(liServer *srv, liPlugin *p, gpointer userdata) {
	UNUSED(srv); UNUSED(userdata);

	p->options = options;
	p->optionptrs = optionptrs;
	p->actions = actions;
	p->setups = setups;

	p->free = plugin_limit_free;
	p->handle_vrclose = mod_limit_vrclose;
	p->handle_prepare_worker = mod_limit_prepare_worker;
}


gboolean mod_limit_init(liModules *mods, liModule *mod) {
	UNUSED(mod);

	MODULE_VERSION_CHECK(mods);

	mod->config = li_plugin_register(mods->main, "mod_limit", plugin_limit_init, NULL);

	return mod->config != NULL;
}

gboolean mod_limit_free(liModules *mods, liModule *mod) {
	if (mod->config)
		li_plugin_free(mods->main, mod->config);

	return TRUE;
}
