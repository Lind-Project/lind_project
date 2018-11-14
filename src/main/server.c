
#include <lighttpd/base.h>
#include <lighttpd/plugin_core.h>

#ifdef HAVE_SYS_RESOURCE_H
# include <sys/resource.h>
#endif

typedef struct {
	liServerPrepareCallbackCB callback;
	gpointer data;
} liServerPrepareCallbackData;

static void li_server_listen_cb(liEventBase *watcher, int events);
static void li_server_stop(liServer *srv);
static void state_ready_cb(liEventBase *watcher, int events);
static void li_server_1sec_timer(liEventBase *watcher, int events);

static liServerSocket* server_socket_new(liServer *srv, int fd) {
	liServerSocket *sock = g_slice_new0(liServerSocket);

	sock->local_addr = li_sockaddr_local_from_socket(fd);
	sock->refcount = 1;
	li_fd_no_block(fd);
	li_event_io_init(&srv->main_worker->loop, "server socket", &sock->watcher, li_server_listen_cb, fd, LI_EV_READ);
	return sock;
}

void li_server_socket_release(liServerSocket* sock) {
	if (!sock) return;
	LI_FORCE_ASSERT(g_atomic_int_get(&sock->refcount) > 0);
	if (g_atomic_int_dec_and_test(&sock->refcount)) {
		if (sock->release_cb) sock->release_cb(sock);

		/* loop is already destroyed */
		li_sockaddr_clear(&sock->local_addr);

		g_slice_free(liServerSocket, sock);
	}
}

void li_server_socket_acquire(liServerSocket* sock) {
	LI_FORCE_ASSERT(g_atomic_int_get(&sock->refcount) > 0);
	g_atomic_int_inc(&sock->refcount);
}

static void server_fetch_db_free(gpointer db) {
	li_fetch_database_release((liFetchDatabase*) db);
}

static void sigint_cb(liEventBase *watcher, int events) {
	liEventSignal *sig = li_event_signal_from(watcher);
	liEventLoop *loop = li_event_get_loop(sig);
	liServer *srv = LI_CONTAINER_OF(loop, liWorker, loop)->srv;
	UNUSED(events);

	if (g_atomic_int_get(&srv->dest_state) != LI_SERVER_DOWN) {
		INFO(srv, "%s", "Got signal, shutdown");
		li_server_goto_state(srv, LI_SERVER_DOWN);
	} else {
		INFO(srv, "%s", "Got second signal, force shutdown");
		abort();
	}
}

static void sigpipe_cb(liEventBase *watcher, int events) {
	/* ignore */
	UNUSED(watcher); UNUSED(events);
}

liServer* li_server_new(const gchar *module_dir, gboolean module_resident) {
	liServer* srv = g_slice_new0(liServer);

	srv->magic = LIGHTTPD_SERVER_MAGIC;
	srv->state = LI_SERVER_INIT;
	srv->dest_state = LI_SERVER_RUNNING;

	srv->statelock = g_mutex_new();
	g_queue_init(&srv->state_wait_queue);
	srv->state_wait_for = srv->state;

	li_lua_init(&srv->LL, srv, NULL);

	srv->workers = g_array_new(FALSE, TRUE, sizeof(liWorker*));
	srv->worker_count = 0;

	srv->sockets = g_ptr_array_new();

	srv->modules = li_modules_new(srv, module_dir, module_resident);

	li_server_plugins_init(srv);

	srv->prepare_callbacks = g_array_new(FALSE, TRUE, sizeof(liServerPrepareCallbackData));

	srv->mainaction = NULL;
	srv->config_global_vars = li_value_new_hashtable();

	srv->action_mutex = g_mutex_new();

	srv->fetch_backends = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, server_fetch_db_free);
	srv->fetch_backends_mutex = g_mutex_new();

	srv->exiting = FALSE;

	srv->ts_formats = g_array_new(FALSE, TRUE, sizeof(GString*));
	/* error log ts format */
	li_server_ts_format_add(srv, g_string_new("%a, %d %b %Y %H:%M:%S %Z"));
	/* http header ts format */
	li_server_ts_format_add(srv, g_string_new("%a, %d %b %Y %H:%M:%S GMT"));

	srv->connection_load = 0;
	srv->max_connections = 256; /* assume max-fds = 1024 */
	srv->connection_limit_hit = FALSE;
#ifdef HAVE_GETRLIMIT
	{
		struct rlimit rlim;
		rlim_t max_fds = 1024;
		if (0 != getrlimit(RLIMIT_NOFILE, &rlim)) {
			ERROR(srv, "couldn't get 'max filedescriptors': %s", g_strerror(errno));
		} else {
			max_fds = rlim.rlim_cur;
			if (RLIM_INFINITY == rlim.rlim_max) {
				/* don't set RLIM_INFINITY as rlim_cur - doesn't work */
				rlim.rlim_max = 4096;
			}
			if (rlim.rlim_cur < rlim.rlim_max) {
				/* go for maximum */
				rlim.rlim_cur = rlim.rlim_max;
				if (0 != setrlimit(RLIMIT_NOFILE, &rlim)) {
					ERROR(srv, "couldn't set 'max filedescriptors': %s", g_strerror(errno));
				} else {
					max_fds = rlim.rlim_cur;
				}
			}
		}
		if (max_fds / 4 > G_MAXUINT32) {
			srv->max_connections = G_MAXUINT32;
		} else {
			srv->max_connections = max_fds / 4;
		}
	}
#endif

	srv->io_timeout = 300; /* default I/O timeout */
	srv->keep_alive_queue_timeout = 5;
	srv->stat_cache_ttl = 10.0; /* default stat cache ttl */
	srv->tasklet_pool_threads = 4; /* default per-worker tasklet_pool threads */

	return srv;
}

void li_server_free(liServer* srv) {
	if (!srv) return;

	li_server_stop(srv);
	g_atomic_int_set(&srv->exiting, TRUE);

	/* join all workers */
	{
		guint i;
		for (i = 1; i < srv->workers->len; i++) {
			liWorker *wrk;
			wrk = g_array_index(srv->workers, liWorker*, i);
			li_worker_exit(srv->main_worker, wrk);
			g_thread_join(wrk->thread);
		}
	}

	li_action_release(srv, srv->mainaction);
	srv->mainaction = NULL;
	g_hash_table_destroy(srv->config_global_vars);
	srv->config_global_vars = NULL;

	li_event_clear(&srv->state_ready_watcher);
	g_mutex_free(srv->statelock);

	li_lua_clear(&srv->LL);

	if (srv->acon) {
		li_angel_connection_free(srv->acon);
		srv->acon = NULL;
	}

	li_event_clear(&srv->srv_1sec_timer);

	li_event_clear(&srv->sig_w_INT);
	li_event_clear(&srv->sig_w_TERM);
	li_event_clear(&srv->sig_w_PIPE);

	/* free all workers */
	{
		guint i;
		for (i = 0; i < srv->workers->len; i++) {
			liWorker *wrk;
			struct ev_loop *loop;
			wrk = g_array_index(srv->workers, liWorker*, i);
			loop = li_worker_free(wrk);
			if (i == 0) {
				ev_default_destroy();
			} else {
				ev_loop_destroy(loop);
			}
		}
		g_array_free(srv->workers, TRUE);
	}

	{
		guint i; for (i = 0; i < srv->sockets->len; i++) {
			liServerSocket *sock = g_ptr_array_index(srv->sockets, i);
			close(li_event_io_fd(&sock->watcher));
			li_event_clear(&sock->watcher);
			li_server_socket_release(sock);
		}
		g_ptr_array_free(srv->sockets, TRUE);
	}

	g_hash_table_remove_all(srv->fetch_backends);

	/* release modules */
	li_modules_free(srv->modules);

	li_plugin_free(srv, srv->core_plugin);

	li_log_cleanup(srv);

	{
		guint i;
		for (i = 0; i < srv->ts_formats->len; i++)
			g_string_free(g_array_index(srv->ts_formats, GString*, i), TRUE);
		g_array_free(srv->ts_formats, TRUE);
	}

	li_server_plugins_free(srv);

	if (NULL != srv->prepare_callbacks) {
		guint i, len;
		for (i = 0, len = srv->prepare_callbacks->len; i < len; ++i) {
			liServerPrepareCallbackData *cbd = &g_array_index(srv->prepare_callbacks, liServerPrepareCallbackData, i);
			cbd->callback(srv, cbd->data, TRUE);
		}
		g_array_free(srv->prepare_callbacks, TRUE);
		srv->prepare_callbacks = NULL;
	}

	g_hash_table_destroy(srv->fetch_backends);
	g_mutex_free(srv->fetch_backends_mutex);

	g_mutex_free(srv->action_mutex);

#ifdef LIGHTY_OS_LINUX
	li_value_free(srv->workers_cpu_affinity);
#endif

	if (srv->started_str)
		g_string_free(srv->started_str, TRUE);

	g_slice_free(liServer, srv);
}

static gpointer server_worker_cb(gpointer data) {
	liWorker *wrk = (liWorker*) data;
	li_plugins_prepare_worker(wrk);
	li_worker_run(wrk);
	return NULL;
}

void li_server_loop_init(liServer *srv) {
	struct ev_loop *evloop;
	liEventLoop *loop;

	/* disable usage if signalfd for libev 3.8, it breaks signal handling. 3.9+ have it disabled by default */
#if EV_VERSION_MAJOR == 3 && EV_VERSION_MINOR == 8
	if (ev_version_major() == 3 && ev_version_minor() == 8) {
			srv->loop_flags |= EVFLAG_NOSIGFD;
	}
#endif

	evloop = ev_default_loop(srv->loop_flags);

	if (NULL == evloop) {
		LI_FATAL("could not initialise libev, bad $LIBEV_FLAGS in environment?");
		return;
	}

	srv->main_worker = li_worker_new(srv, evloop);
	srv->main_worker->ndx = 0;

	loop = &srv->main_worker->loop;

	li_event_async_init(loop, "server state ready", &srv->state_ready_watcher, state_ready_cb);

	li_event_timer_init(loop, "server 1sec", &srv->srv_1sec_timer, li_server_1sec_timer);
	li_event_set_keep_loop_alive(&srv->srv_1sec_timer, FALSE);
	li_event_timer_once(&srv->srv_1sec_timer, 1);

	li_event_signal_init(loop, "server SIGINT", &srv->sig_w_INT, sigint_cb, SIGINT);
	li_event_signal_init(loop, "server SIGTERM", &srv->sig_w_TERM, sigint_cb, SIGTERM);
	li_event_signal_init(loop, "server SIGPIPE", &srv->sig_w_PIPE, sigpipe_cb, SIGPIPE);

	li_log_init(srv);
}

static void li_server_1sec_timer(liEventBase *watcher, int events) {
	liServer *srv = LI_CONTAINER_OF(li_event_timer_from(watcher), liServer, srv_1sec_timer);
	UNUSED(events);

	if (srv->connection_limit_hit) {
		guint srv_cur_load = g_atomic_int_get(&srv->connection_load);
		guint srv_max_load = g_atomic_int_get(&srv->max_connections);
		if (srv_cur_load <= (srv_max_load - srv_max_load/8)) { /* cur_load <= 7/8 * max_load */
			guint i;

			for (i = 0; i < srv->sockets->len; i++) {
				liServerSocket *sock = g_ptr_array_index(srv->sockets, i);
				li_event_start(&sock->watcher);
			}
			srv->connection_limit_hit = FALSE;
		}
	}
}

static gboolean li_server_worker_init(liServer *srv) {
	guint i;

	li_plugins_init_lua(&srv->LL, srv, NULL);
	li_plugins_init_lua(&srv->main_worker->LL, srv, srv->main_worker);

	if (srv->worker_count < 1) srv->worker_count = 1;
	g_array_set_size(srv->workers, srv->worker_count);
	g_array_index(srv->workers, liWorker*, 0) = srv->main_worker;

	for (i = 1; i < srv->worker_count; i++) {
		liWorker *wrk;
		struct ev_loop *loop;

		if (NULL == (loop = ev_loop_new(srv->loop_flags))) {
			LI_FATAL("could not create extra libev loops");
			return FALSE;
		}
		wrk = g_array_index(srv->workers, liWorker*, i) = li_worker_new(srv, loop);
		wrk->ndx = i;

		li_plugins_init_lua(&wrk->LL, srv, wrk);
	}

	return TRUE;
}

static void li_server_worker_run(liServer *srv) {
	guint i, len;

	for (i = 0, len = srv->prepare_callbacks->len; i < len; ++i) {
		liServerPrepareCallbackData *cbd = &g_array_index(srv->prepare_callbacks, liServerPrepareCallbackData, i);
		cbd->callback(srv, cbd->data, FALSE);
	}
	g_array_free(srv->prepare_callbacks, TRUE);
	srv->prepare_callbacks = NULL;
	li_plugins_prepare_worker(srv->main_worker);

	for (i = 1; i < srv->worker_count; i++) {
		GError *error = NULL;
		liWorker *wrk  = g_array_index(srv->workers, liWorker*, i);
		if (NULL == (wrk->thread = g_thread_create(server_worker_cb, wrk, TRUE, &error))) {
			g_error ( "g_thread_create failed: %s", error->message );
		}
	}
}

static void server_connection_limit_hit(liServer *srv) {
	guint i;

	for (i = 0; i < srv->sockets->len; i++) {
		liServerSocket *sock = g_ptr_array_index(srv->sockets, i);
		li_event_stop(&sock->watcher);
	}

	srv->connection_limit_hit = TRUE;
}

static void li_server_listen_cb(liEventBase *watcher, int events) {
	liServerSocket *sock = LI_CONTAINER_OF(li_event_io_from(watcher), liServerSocket, watcher);
	liServer *srv = sock->srv;
	int s;
	liSocketAddress remote_addr;
	liSockAddr sa;
	socklen_t l;
	int fd = li_event_io_fd(li_event_io_from(watcher));
	UNUSED(events);

	for ( ;; ) {
		liWorker *wrk;
		guint i, min_load, srv_cur_load, srv_max_load;

		srv_cur_load = g_atomic_int_get(&srv->connection_load);
		srv_max_load = g_atomic_int_get(&srv->max_connections);
		if (srv_cur_load >= srv_max_load) {
			server_connection_limit_hit(srv);
			return;
		}

		l = sizeof(sa);

#ifdef HAVE_ACCEPT4
		if (-1 == (s = accept4(fd, &sa.plain, &l, SOCK_NONBLOCK))) {
			if (ENOSYS != errno) break;

			/* fallback */
			if (-1 == (s = accept(fd, &sa.plain, &l))) break;
			li_fd_no_block(s); /* we don't fork, don't care about FD_CLOEXEC */
		}
#else
		if (-1 == (s = accept(fd, &sa.plain, &l))) break;
		li_fd_no_block(s); /* we don't fork, don't care about FD_CLOEXEC */
#endif

		wrk = srv->main_worker;
		min_load = g_atomic_int_get(&wrk->connection_load);

		if (l <= sizeof(sa)) {
			remote_addr.addr = g_slice_alloc(l);
			remote_addr.len = l;
			memcpy(remote_addr.addr, &sa, l);
		} else {
			remote_addr = li_sockaddr_remote_from_socket(s);
		}

		for (i = 1; i < srv->worker_count; i++) {
			liWorker *wt = g_array_index(srv->workers, liWorker*, i);
			guint load = g_atomic_int_get(&wt->connection_load);
			if (load < min_load) {
				wrk = wt;
				min_load = load;
			}
		}

		g_atomic_int_inc((gint*) &wrk->connection_load);
		g_atomic_int_inc((gint*) &srv->connection_load);
		li_server_socket_acquire(sock);
		li_worker_new_con(srv->main_worker, wrk, remote_addr, s, sock);
	}

#ifdef _WIN32
	errno = WSAGetLastError();
#endif

	switch (errno) {
	case EAGAIN:
#if EWOULDBLOCK != EAGAIN
	case EWOULDBLOCK:
#endif
	case EINTR:
		/* we were stopped _before_ we had a connection */
	case ECONNABORTED: /* this is a FreeBSD thingy */
		/* we were stopped _after_ we had a connection */
		break;

	case EMFILE: /* we are out of FDs */
		li_server_out_of_fds(srv);
		/* TODO: disable accept callbacks? */
		break;
	default:
		ERROR(srv, "accept failed on fd=%d with error: %s", fd, g_strerror(errno));
		break;
	}
}

/* main worker only */
liServerSocket* li_server_listen(liServer *srv, int fd) {
	liServerSocket *sock = server_socket_new(srv, fd);

	sock->srv = srv;
	g_ptr_array_add(srv->sockets, sock);

	if (LI_SERVER_RUNNING == srv->state || LI_SERVER_WARMUP == srv->state) li_event_start(&sock->watcher);

	return sock;
}

static void li_server_start_listen(liServer *srv) {
	guint i;

	for (i = 0; i < srv->sockets->len; i++) {
		liServerSocket *sock = g_ptr_array_index(srv->sockets, i);
		li_event_start(&sock->watcher);
	}
}

static void li_server_stop_listen(liServer *srv) {
	guint i;

	for (i = 0; i < srv->sockets->len; i++) {
		liServerSocket *sock = g_ptr_array_index(srv->sockets, i);
		li_event_stop(&sock->watcher);
	}
	srv->connection_limit_hit = FALSE; /* reset flag */

	/* suspend all workers (close keep-alive connections) */
	for (i = 0; i < srv->worker_count; i++) {
		liWorker *wrk;
		wrk = g_array_index(srv->workers, liWorker*, i);
		li_worker_suspend(srv->main_worker, wrk);
	}
}

static void li_server_stop(liServer *srv) {
	guint i;

	for (i = 0; i < srv->sockets->len; i++) {
		liServerSocket *sock = g_ptr_array_index(srv->sockets, i);
		li_event_stop(&sock->watcher);
	}
	srv->connection_limit_hit = FALSE; /* reset flag */

	/* stop all workers */
	for (i = 0; i < srv->worker_count; i++) {
		liWorker *wrk;
		wrk = g_array_index(srv->workers, liWorker*, i);
		li_worker_stop(srv->main_worker, wrk);
	}
}

void li_server_exit(liServer *srv) {
	li_server_stop(srv);

	g_atomic_int_set(&srv->exiting, TRUE);
	g_atomic_int_set(&srv->state, LI_SERVER_DOWN);
	g_atomic_int_set(&srv->dest_state, LI_SERVER_DOWN);

	/* exit all workers */
	{
		guint i;
		for (i = 0; i < srv->worker_count; i++) {
			liWorker *wrk;
			wrk = g_array_index(srv->workers, liWorker*, i);
			li_worker_exit(srv->main_worker, wrk);
		}
	}
}

/* cache timestamp */
GString *li_server_current_timestamp(void) {
	static GStaticPrivate last_ts_key = G_STATIC_PRIVATE_INIT;
	static GStaticPrivate ts_str_key = G_STATIC_PRIVATE_INIT;

	time_t *last_ts = g_static_private_get(&last_ts_key);
	GString *ts_str = g_static_private_get(&ts_str_key);

	time_t cur_ts = time(NULL);

	if (last_ts == NULL) {
		last_ts = g_new0(time_t, 1);
		g_static_private_set(&last_ts_key, last_ts, g_free);
	}
	if (ts_str == NULL) {
		ts_str = g_string_sized_new(255);
		g_static_private_set(&ts_str_key, ts_str, (GDestroyNotify)li_string_destroy_notify);
	}

	if (cur_ts != *last_ts) {
		gsize s;
#ifdef HAVE_GMTIME_R
		struct tm tm;
#endif

		g_string_set_size(ts_str, 255);
#ifdef HAVE_GMTIME_R
		s = strftime(ts_str->str, ts_str->allocated_len,
				"%a, %d %b %Y %H:%M:%S GMT", gmtime_r(&cur_ts, &tm));
#else
		s = strftime(ts_str->str, ts_str->allocated_len,
				"%a, %d %b %Y %H:%M:%S GMT", gmtime(&cur_ts));
#endif
		g_string_set_size(ts_str, s);
		*last_ts = cur_ts;
	}

	return ts_str;
}

void li_server_out_of_fds(liServer *srv) {
	ERROR(srv, "%s", "Too many open files. Either raise your fd limit or use a lower connection limit.");
}

guint li_server_ts_format_add(liServer *srv, GString* format) {
	/* check if not already registered */
	guint i;

	g_mutex_lock(srv->action_mutex);

	for (i = 0; i < srv->ts_formats->len; i++) {
		if (g_string_equal(g_array_index(srv->ts_formats, GString*, i), format)) {
			g_mutex_unlock(srv->action_mutex);
			return i;
		}
	}

	g_array_append_val(srv->ts_formats, format);

	g_mutex_unlock(srv->action_mutex);

	return i;
}

/* state machine: call this functions only in the main worker context */
/* Note: main worker doesn't need atomic read for state */

#if 0
	case LI_SERVER_INIT:
	case LI_SERVER_LOADING:
	case LI_SERVER_SUSPENDED:
	case LI_SERVER_WARMUP:
	case LI_SERVER_RUNNING:
	case LI_SERVER_SUSPENDING:
	case LI_SERVER_STOPPING:
	case LI_SERVER_DOWN:
#endif

static const gchar* li_server_state_string(liServerState state) {
	switch (state) {
	case LI_SERVER_INIT: return "init";
	case LI_SERVER_LOADING: return "loading";
	case LI_SERVER_SUSPENDED: return "suspended";
	case LI_SERVER_WARMUP: return "warmup";
	case LI_SERVER_RUNNING: return "running";
	case LI_SERVER_SUSPENDING: return "suspending";
	case LI_SERVER_STOPPING: return "stopping";
	case LI_SERVER_DOWN: return "down";
	}

	return "<unkown>";
}

/* next state in the machine we want to reach to reach */
static liServerState li_server_next_state(liServer *srv) {
	switch (srv->state) {
	case LI_SERVER_INIT:
		return LI_SERVER_LOADING;
	case LI_SERVER_LOADING:
		if (LI_SERVER_DOWN == srv->dest_state) return LI_SERVER_STOPPING;
		return LI_SERVER_SUSPENDED;
	case LI_SERVER_SUSPENDED:
		switch (srv->dest_state) {
		case LI_SERVER_INIT:
		case LI_SERVER_LOADING:
		case LI_SERVER_SUSPENDED:
			return LI_SERVER_SUSPENDED;
		case LI_SERVER_WARMUP:
		case LI_SERVER_RUNNING:
		case LI_SERVER_SUSPENDING:
			return LI_SERVER_WARMUP;
		case LI_SERVER_STOPPING:
		case LI_SERVER_DOWN:
			return LI_SERVER_STOPPING;
		}
		return LI_SERVER_DOWN;
	case LI_SERVER_WARMUP:
		if (LI_SERVER_WARMUP == srv->dest_state) return LI_SERVER_WARMUP;
		return LI_SERVER_RUNNING;
	case LI_SERVER_RUNNING:
		if (LI_SERVER_RUNNING == srv->dest_state) return LI_SERVER_RUNNING;
		return LI_SERVER_SUSPENDING;
	case LI_SERVER_SUSPENDING:
		if (LI_SERVER_RUNNING == srv->dest_state) return LI_SERVER_RUNNING;
		if (LI_SERVER_SUSPENDING == srv->dest_state) return LI_SERVER_SUSPENDING;
		return LI_SERVER_SUSPENDED;
	case LI_SERVER_STOPPING:
	case LI_SERVER_DOWN:
		return LI_SERVER_DOWN;
	}
	return LI_SERVER_DOWN;
}

static void li_server_start_transition(liServer *srv, liServerState state) {
	guint i;
	liServerStateWait sw_dummy;

	DEBUG(srv, "Try reaching state: %s (dest: %s)", li_server_state_string(state), li_server_state_string(srv->dest_state));

	srv->state_wait_for = state;
	memset(&sw_dummy, 0, sizeof(sw_dummy));
	li_server_state_wait(srv, &sw_dummy);

	switch (state) {
	case LI_SERVER_INIT:
	case LI_SERVER_LOADING:
		li_server_reached_state(srv, state);
		break;
	case LI_SERVER_SUSPENDED:
		if (srv->state == LI_SERVER_LOADING) {
			li_plugins_prepare(srv);
		}
		break;
	case LI_SERVER_WARMUP:
		li_server_start_listen(srv);
		li_plugins_start_listen(srv);
		break;
	case LI_SERVER_RUNNING:
		if (LI_SERVER_WARMUP == srv->state) {
			li_plugins_start_log(srv);
		} else if (LI_SERVER_SUSPENDING == srv->state) {
			li_server_start_listen(srv);
			li_plugins_start_listen(srv);
		}
		break;
	case LI_SERVER_SUSPENDING:
		li_server_stop_listen(srv);
		li_plugins_stop_listen(srv);
		/* wait for closed connections and plugins */
		break;
	case LI_SERVER_STOPPING:
		{
			liAction* mainaction = srv->mainaction;
			srv->mainaction = NULL;
			li_action_release(srv, mainaction);
		}
		/* stop all workers */
		for (i = 0; i < srv->worker_count; i++) {
			liWorker *wrk;
			wrk = g_array_index(srv->workers, liWorker*, i);
			li_worker_stopping(srv->main_worker, wrk);
		}
		break;
	case LI_SERVER_DOWN:
		/* wait */
		break;
	}

	li_server_state_ready(srv, &sw_dummy);
}

void li_server_goto_state(liServer *srv, liServerState state) {
	if (srv->dest_state == LI_SERVER_DOWN || srv->dest_state == state) return; /* cannot undo this */

	switch (state) {
	case LI_SERVER_INIT:
	case LI_SERVER_LOADING:
	case LI_SERVER_SUSPENDING:
	case LI_SERVER_STOPPING:
		return; /* invalid dest states */
	case LI_SERVER_WARMUP:
	case LI_SERVER_RUNNING:
	case LI_SERVER_SUSPENDED:
	case LI_SERVER_DOWN:
		break;
	}

	g_atomic_int_set(&srv->dest_state, state);

	if (srv->dest_state != srv->state) {
		liServerState want_state = li_server_next_state(srv);
		li_server_start_transition(srv, want_state);
	}
}

void li_server_reached_state(liServer *srv, liServerState state) {
	liServerState want_state = li_server_next_state(srv);
	liServerState old_state = srv->state;
	GList *swlink;
	guint i;

	if (state != want_state) return;
	if (state == srv->state) return;

	g_atomic_int_set(&srv->state, state);
	DEBUG(srv, "Reached state: %s (dest: %s)", li_server_state_string(state), li_server_state_string(srv->dest_state));

	/* cleanup state_wait_queue */
	g_mutex_lock(srv->statelock);

	while (NULL != (swlink = g_queue_pop_head_link(&srv->state_wait_queue))) {
		liServerStateWait *sw = swlink->data;
		sw->active = FALSE;
		if (sw->cancel_cb) {
			sw->cancel_cb(srv, sw);
		}
	}
	g_mutex_unlock(srv->statelock);

	switch (srv->state) {
	case LI_SERVER_INIT:
		break;
	case LI_SERVER_LOADING:
		li_plugins_prepare_callbacks(srv);
		li_server_worker_init(srv);

		{
			GString *str = li_worker_current_timestamp(srv->main_worker, LI_LOCALTIME, LI_TS_FORMAT_DEFAULT);
			srv->started = li_cur_ts(srv->main_worker);
			srv->started_str = g_string_new_len(GSTR_LEN(str));
		}

		li_log_thread_start(srv);
		break;
	case LI_SERVER_SUSPENDED:
		if (LI_SERVER_SUSPENDING == old_state) {
			li_plugins_stop_log(srv);
		} else if (LI_SERVER_LOADING == old_state) {
			li_server_worker_run(srv);
		}
		break;
	case LI_SERVER_WARMUP:
	case LI_SERVER_RUNNING:
		break;
	case LI_SERVER_SUSPENDING:
		break;
	case LI_SERVER_STOPPING:
		/* stop all workers */
		for (i = 0; i < srv->worker_count; i++) {
			liWorker *wrk;
			wrk = g_array_index(srv->workers, liWorker*, i);
			li_worker_stop(srv->main_worker, wrk);
		}

		li_log_thread_wakeup(srv);
		break;
	case LI_SERVER_DOWN:
		/* li_server_exit(srv); */
		return;
	}

	if (srv->acon) {
		GString *data = g_string_new(li_server_state_string(srv->state));
		GError *err = NULL;

		if (!li_angel_send_simple_call(srv->acon, CONST_STR_LEN("core"), CONST_STR_LEN("reached-state"), data, &err)) {
			GERROR(srv, err, "%s", "couldn't send state update to angel");
			g_error_free(err);
		}
	}

	if (srv->dest_state != srv->state) {
		want_state = li_server_next_state(srv);
		li_server_start_transition(srv, want_state);
	}
}

static void state_ready_cb(liEventBase *watcher, int events) {
	liServer *srv = LI_CONTAINER_OF(li_event_async_from(watcher), liServer, state_ready_watcher);

	UNUSED(events);

	g_mutex_lock(srv->statelock);

	if (srv->state_wait_queue.length > 0) {
		/* not ready - ignore event */
		g_mutex_unlock(srv->statelock);
		return;
	}

	g_mutex_unlock(srv->statelock);

	if (srv->state_wait_for != li_server_next_state(srv)) {
		/* not the state we have been waiting for - ignore */
		return;
	}

	/* IMPORTANT: do not call this while statelock is locked  */
	li_server_reached_state(srv, srv->state_wait_for);
}

/** threadsafe */
void li_server_state_ready(liServer *srv, liServerStateWait *sw) {
	g_mutex_lock(srv->statelock);

	if (sw->active) {
		g_queue_unlink(&srv->state_wait_queue, &sw->queue_link);
		sw->active = FALSE;

		if (srv->state_wait_queue.length == 0) {
			li_event_async_send(&srv->state_ready_watcher);
		}
	}

	g_mutex_unlock(srv->statelock);
}

/** only call from server state plugin hooks; push new wait condition to wait queue */
void li_server_state_wait(liServer *srv, liServerStateWait *sw) {
	g_mutex_lock(srv->statelock);

	sw->queue_link.data = sw;
	g_queue_push_tail_link(&srv->state_wait_queue, &sw->queue_link);
	sw->active = TRUE;

	g_mutex_unlock(srv->statelock);
}

void li_server_register_prepare_cb(liServer *srv, liServerPrepareCallbackCB cb, gpointer data) {
	if (g_atomic_int_get(&srv->state) != LI_SERVER_INIT) {
		cb(srv, data, FALSE);
	} else {
		liServerPrepareCallbackData cbd;
		cbd.callback = cb;
		cbd.data = data;
		g_array_append_val(srv->prepare_callbacks, cbd);
	}
}

gboolean li_server_register_fetch_database(liServer *srv, const gchar *name, liFetchDatabase *db) {
	gboolean inserted = FALSE;

	g_mutex_lock(srv->fetch_backends_mutex);
		if (NULL == g_hash_table_lookup(srv->fetch_backends, name)) {
			inserted = TRUE;
			li_fetch_database_acquire(db);
			g_hash_table_insert(srv->fetch_backends, g_strdup(name), db);
		}
	g_mutex_unlock(srv->fetch_backends_mutex);
	return inserted;
}

liFetchDatabase* li_server_get_fetch_database(liServer *srv, const gchar *name) {
	liFetchDatabase *db;

	g_mutex_lock(srv->fetch_backends_mutex);
		if (NULL != (db = g_hash_table_lookup(srv->fetch_backends, name))) {
			li_fetch_database_acquire(db);
		}
	g_mutex_unlock(srv->fetch_backends_mutex);
	return db;
}
