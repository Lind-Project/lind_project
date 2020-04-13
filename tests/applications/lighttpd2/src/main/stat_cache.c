#include <lighttpd/base.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <lighttpd/plugin_core.h>

static void stat_cache_delete_cb(liWaitQueue *wq, gpointer daa);

static void stat_cache_entry_release(liStatCacheEntry *sce);
static void stat_cache_entry_acquire(liStatCacheEntry *sce);

liStatCache* li_stat_cache_new(liWorker *wrk, gdouble ttl) {
	liStatCache *sc;

	if (ttl < 0) {
		/* fall back to default if not sane */
		ttl = 10.0;
	} else if (ttl == 0) {
		/* ttl means disabled stat cache */
		return NULL;
	}

	sc = g_slice_new0(liStatCache);
	sc->ttl = ttl;
	sc->entries = g_hash_table_new_full((GHashFunc)g_string_hash, (GEqualFunc)g_string_equal, NULL, NULL);
	sc->dirlists = g_hash_table_new_full((GHashFunc)g_string_hash, (GEqualFunc)g_string_equal, NULL, NULL);

	li_waitqueue_init(&sc->delete_queue, &wrk->loop, "stat cache delete queue", stat_cache_delete_cb, ttl, sc);

	return sc;
}

static void stat_cache_remove_from_cache(liStatCache *sc, liStatCacheEntry *sce) {
	if (sce->cached) {
		if (sce->type == STAT_CACHE_ENTRY_SINGLE) {
			g_hash_table_remove(sc->entries, sce->data.path);
		} else {
			g_hash_table_remove(sc->dirlists, sce->data.path);
		}
		sce->cached = FALSE;
	}
	sce->sc = NULL;
	stat_cache_entry_release(sce);
}

void li_stat_cache_free(liStatCache *sc) {
	liWaitQueueElem *wqe;

	/* check if stat cache was enabled */
	if (!sc)
		return;

	li_waitqueue_stop(&sc->delete_queue);

	while (NULL != (wqe = li_waitqueue_pop_force(&sc->delete_queue))) {
		liStatCacheEntry *sce = wqe->data;
		stat_cache_remove_from_cache(sc, sce);
	}

	g_hash_table_destroy(sc->entries);
	g_hash_table_destroy(sc->dirlists);
	g_slice_free(liStatCache, sc);
}

static void stat_cache_delete_cb(liWaitQueue *wq, gpointer data) {
	liStatCache *sc = data;
	liWaitQueueElem *wqe;

	while ((wqe = li_waitqueue_pop(wq)) != NULL) {
		liStatCacheEntry *sce = wqe->data;

		/* stat cache entry TTL over */
		stat_cache_remove_from_cache(sc, sce);
	}

	li_waitqueue_update(wq);
}

static void stat_cache_finished(gpointer data) {
	liStatCacheEntry *sce = data;
	guint i;
	liVRequest *vr;

	if (sce->data.failed) {
		if (NULL != sce->sc) sce->sc->errors++;
	}

	/* queue pending vrequests */
	for (i = 0; i < sce->vrequests->len; i++) {
		vr = g_ptr_array_index(sce->vrequests, i);
		li_vrequest_joblist_append(vr);
	}

	/* release tasklet reference */
	stat_cache_entry_release(sce);
}

static void stat_cache_run(gpointer data) {
	liStatCacheEntry *sce = data;

	if (stat(sce->data.path->str, &sce->data.st) == -1) {
		sce->data.failed = TRUE;
		sce->data.err = errno;
	} else {
		sce->data.failed = FALSE;
	}

	if (!sce->data.failed && sce->type == STAT_CACHE_ENTRY_DIR) {
		/* dirlisting */
		DIR *dirp;
		struct dirent *result;
		liStatCacheEntryData sced;
		GString *str;

		dirp = opendir(sce->data.path->str);
		if (dirp == NULL) {
			sce->data.failed = TRUE;
			sce->data.err = errno;
		} else {
			sce->dirlist = g_array_sized_new(FALSE, FALSE, sizeof(liStatCacheEntryData), 32);

			str = g_string_sized_new(sce->data.path->len + 64);
			g_string_append_len(str, GSTR_LEN(sce->data.path));

			/* glibc claims modern readdir are thread-safe, and
			 * readdir_r has issues. no way to check readdir is actually
			 * safe, hope for the best.
			 */
			for (;;) {
				errno = 0; /* readdir may not reset errno */
				if (NULL == (result = readdir(dirp))) break;

				/* hide "." and ".." */
				if (result->d_name[0] == '.' && (result->d_name[1] == '\0' ||
					(result->d_name[1] == '.' && result->d_name[2] == '\0'))) {
					continue;
				}

				sced.path = g_string_sized_new(63);
				g_string_assign(sced.path, result->d_name);

				g_string_truncate(str, sce->data.path->len);
				/* make sure the path ends with / (or whatever) */
				if (!sce->data.path->len || sce->data.path->str[sce->data.path->len-1] != G_DIR_SEPARATOR)
					g_string_append_c(str, G_DIR_SEPARATOR);
				g_string_append_len(str, GSTR_LEN(sced.path));

				if (stat(str->str, &sced.st) == -1) {
					sced.failed = TRUE;
					sced.err = errno;
				} else {
					sced.failed = FALSE;
				}

				g_array_append_val(sce->dirlist, sced);
			}

			if (errno) {
				sce->data.failed = TRUE;
				sce->data.err = errno;
			}

			g_string_free(str, TRUE);
			closedir(dirp);
		}
	}

	g_atomic_int_set(&sce->state, STAT_CACHE_ENTRY_FINISHED);
}

static liStatCacheEntry *stat_cache_entry_new(liStatCache *sc, GString *path) {
	liStatCacheEntry *sce;

	sce = g_slice_new0(liStatCacheEntry);
	sce->sc = sc;
	sce->data.path = g_string_new_len(GSTR_LEN(path));
	sce->vrequests = g_ptr_array_sized_new(8);
	sce->state = STAT_CACHE_ENTRY_WAITING;
	sce->queue_elem.data = sce;
	sce->refcount = 1;
	sce->cached = TRUE;

	return sce;
}

static void stat_cache_entry_free(liStatCacheEntry *sce) {
	guint i;

	LI_FORCE_ASSERT(sce->vrequests->len == 0);

	g_string_free(sce->data.path, TRUE);
	g_ptr_array_free(sce->vrequests, TRUE);

	if (NULL != sce->dirlist) {
		for (i = 0; i < sce->dirlist->len; i++) {
			g_string_free(g_array_index(sce->dirlist, liStatCacheEntryData, i).path, TRUE);
		}

		g_array_free(sce->dirlist, TRUE);
	}

	g_slice_free(liStatCacheEntry, sce);
}

static void stat_cache_entry_release(liStatCacheEntry *sce) {
	if (0 == --sce->refcount) stat_cache_entry_free(sce);
}

static void stat_cache_entry_acquire(liStatCacheEntry *sce) {
	++sce->refcount;
}

void li_stat_cache_entry_acquire(liVRequest *vr, liStatCacheEntry *sce) {
	stat_cache_entry_acquire(sce);
	g_ptr_array_add(vr->stat_cache_entries, sce);
	g_ptr_array_add(sce->vrequests, vr);
}

void li_stat_cache_entry_release(liVRequest *vr, liStatCacheEntry *sce) {
	g_ptr_array_remove_fast(sce->vrequests, vr);
	g_ptr_array_remove_fast(vr->stat_cache_entries, sce);
	stat_cache_entry_release(sce);
}

liHandlerResult li_stat_cache_get_dirlist(liVRequest *vr, GString *path, liStatCacheEntry **result) {
	liStatCache *sc;
	liStatCacheEntry *sce;
	guint i;

	sc = vr->wrk->stat_cache;
	sce = g_hash_table_lookup(sc->dirlists, path);

	if (sce) {
		/* cache hit, check state */
		if (g_atomic_int_get(&sce->state) == STAT_CACHE_ENTRY_WAITING) {
			/* already waiting for it? */
			for (i = 0; i < vr->stat_cache_entries->len; i++) {
				if (g_ptr_array_index(vr->stat_cache_entries, i) == sce)
					return LI_HANDLER_WAIT_FOR_EVENT;
			}
			li_stat_cache_entry_acquire(vr, sce); /* assign sce to vr */
			return LI_HANDLER_WAIT_FOR_EVENT;
		}

		sc->hits++;
		*result = sce;
		for (i = 0; i < vr->stat_cache_entries->len; i++) {
			if (g_ptr_array_index(vr->stat_cache_entries, i) == sce)
				return LI_HANDLER_GO_ON;
		}
		li_stat_cache_entry_acquire(vr, sce); /* assign sce to vr */
		return LI_HANDLER_GO_ON;
	} else {
		/* cache miss, allocate new entry */
		sce = stat_cache_entry_new(sc, path);
		sce->type = STAT_CACHE_ENTRY_DIR;

		li_stat_cache_entry_acquire(vr, sce); /* assign sce to vr */

		/* uses initial reference of sce */
		li_waitqueue_push(&sc->delete_queue, &sce->queue_elem);
		g_hash_table_insert(sc->dirlists, sce->data.path, sce);

		sce->refcount++;
		li_tasklet_push(vr->wrk->tasklets, stat_cache_run, stat_cache_finished, sce);

		sc->misses++;
		return LI_HANDLER_WAIT_FOR_EVENT;
	}
}

static liHandlerResult stat_cache_get(liVRequest *vr, GString *path, struct stat *st, int *err, int *fd, gboolean async) {
	liStatCache *sc;
	liStatCacheEntry *sce;
	guint i;

	/* force blocking call if we are not in a vrequest context or stat cache is disabled */
	if (!vr || !(sc = vr->wrk->stat_cache) || !CORE_OPTION(LI_CORE_OPTION_ASYNC_STAT).boolean)
		async = FALSE;

	if (async) {
		sce = g_hash_table_lookup(sc->entries, path);

		if (sce) {
			/* cache hit, check state */
			if (g_atomic_int_get(&sce->state) == STAT_CACHE_ENTRY_WAITING) {
				/* already waiting for it? */
				for (i = 0; i < vr->stat_cache_entries->len; i++) {
					if (g_ptr_array_index(vr->stat_cache_entries, i) == sce) {
						return LI_HANDLER_WAIT_FOR_EVENT;
					}
				}
				li_stat_cache_entry_acquire(vr, sce); /* assign sce to vr */
				return LI_HANDLER_WAIT_FOR_EVENT;
			}

			sc->hits++;
		} else {
			/* cache miss, allocate new entry */
			sce = stat_cache_entry_new(sc, path);
			sce->type = STAT_CACHE_ENTRY_SINGLE;

			li_stat_cache_entry_acquire(vr, sce); /* assign sce to vr */

			/* uses initial reference of sce */
			li_waitqueue_push(&sc->delete_queue, &sce->queue_elem);
			g_hash_table_insert(sc->entries, sce->data.path, sce);

			sce->refcount++;
			li_tasklet_push(vr->wrk->tasklets, stat_cache_run, stat_cache_finished, sce);

			sc->misses++;
			return LI_HANDLER_WAIT_FOR_EVENT;
		}
	}

	if (fd) {
		/* open + fstat */
		while (-1 == (*fd = open(path->str, O_RDONLY))) {
			if (errno == EINTR)
				continue;

			*err = errno;
			return LI_HANDLER_ERROR;
		}
		if (-1 == fstat(*fd, st)) {
			*err = errno;
			close(*fd);
			*fd = -1;
			return LI_HANDLER_ERROR;
		}
	} else {
		/* stat */
		if (-1 == stat(path->str, st)) {
			*err = errno;
			return LI_HANDLER_ERROR;
		}
	}

	return LI_HANDLER_GO_ON;
}

liHandlerResult li_stat_cache_get(liVRequest *vr, GString *path, struct stat *st, int *err, int *fd) {
	return stat_cache_get(vr, path, st, err, fd, TRUE);
}

/* doesn't return HANDLER_WAIT_FOR_EVENT, blocks instead of async lookup */
liHandlerResult li_stat_cache_get_sync(liVRequest *vr, GString *path, struct stat *st, int *err, int *fd) {
	return stat_cache_get(vr, path, st, err, fd, FALSE);
}
