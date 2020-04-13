
#include <lighttpd/base.h>

#include <sys/stat.h>
#include <fcntl.h>

GQuark li_chunk_error_quark(void) {
	return g_quark_from_string("li-chunk-error-quark");
}

/******************
 *   chunkfile    *
 ******************/

liChunkFile *li_chunkfile_new(GString *name, int fd, gboolean is_temp) {
	liChunkFile *cf = g_slice_new(liChunkFile);
	cf->refcount = 1;
	if (name) {
		cf->name = g_string_new_len(GSTR_LEN(name));
	} else {
		cf->name = NULL;
	}
	cf->fd = fd;
	cf->is_temp = is_temp;
	return cf;
}

void li_chunkfile_acquire(liChunkFile *cf) {
	LI_FORCE_ASSERT(g_atomic_int_get(&cf->refcount) > 0);
	g_atomic_int_inc(&cf->refcount);
}

void li_chunkfile_release(liChunkFile *cf) {
	if (!cf) return;
	LI_FORCE_ASSERT(g_atomic_int_get(&cf->refcount) > 0);
	if (g_atomic_int_dec_and_test(&cf->refcount)) {
		if (-1 != cf->fd) close(cf->fd);
		cf->fd = -1;
		if (cf->is_temp) unlink(cf->name->str);
		cf->is_temp = FALSE;
		if (cf->name) g_string_free(cf->name, TRUE);
		cf->name = NULL;
		g_slice_free(liChunkFile, cf);
	}
}

/* open the file cf->name if it is not already opened for reading
 * may return HANDLER_GO_ON, HANDLER_ERROR
 */
liHandlerResult li_chunkfile_open(liChunkFile *cf, GError **err) {
	g_return_val_if_fail (err == NULL || *err == NULL, LI_HANDLER_ERROR);

	if (NULL == cf) {
		g_set_error(err, LI_CHUNK_ERROR, 0, "li_chunkfile_open: cf is NULL");
		return LI_HANDLER_ERROR;
	}
	if (-1 != cf->fd) return LI_HANDLER_GO_ON;
	if (NULL == cf->name) {
		g_set_error(err, LI_CHUNK_ERROR, 0, "li_chunkfile_open: Missing filename");
		return LI_HANDLER_ERROR;
	}
	if (-1 == (cf->fd = open(cf->name->str, O_RDONLY))) {
		g_set_error(err, LI_CHUNK_ERROR, 0, "li_chunkfile_open: Couldn't open file '%s': %s", GSTR_SAFE_STR(cf->name), g_strerror(errno));
		return LI_HANDLER_ERROR;
	}
#if defined(HAVE_POSIX_FADVISE) && defined(POSIX_FADV_SEQUENTIAL)
	/* tell the kernel that we want to stream the file */
	if (-1 == posix_fadvise(cf->fd, 0, 0, POSIX_FADV_SEQUENTIAL)) {
		if (ENOSYS != errno) {
			/* g_debug("posix_fadvise failed for '%s': %s (%i)", GSTR_SAFE_STR(cf->name), g_strerror(errno), cf->fd); */
		}
	}
#endif
	return LI_HANDLER_GO_ON;
}

/******************
 * chunk iterator *
 ******************/

/* must be powers of 2 */
#define MAX_MMAP_CHUNK (2*1024*1024)
#define MMAP_CHUNK_ALIGN (4*1024)

/* get the data from a chunk; easy in case of a STRING_CHUNK,
 * but needs to do io in case of FILE_CHUNK; the data is _not_ marked as "done"
 * may return HANDLER_GO_ON, HANDLER_ERROR
 */
liHandlerResult li_chunkiter_read(liChunkIter iter, off_t start, off_t length, char **data_start, off_t *data_len, GError **err) {
	liChunk *c = li_chunkiter_chunk(iter);
	off_t we_have, our_start;
	liHandlerResult res = LI_HANDLER_GO_ON;

	g_return_val_if_fail (err == NULL || *err == NULL, LI_HANDLER_ERROR);

	if (!c) return LI_HANDLER_ERROR;
	if (!data_start || !data_len) return LI_HANDLER_ERROR;

	we_have = li_chunk_length(c) - start;
	if (length > we_have) length = we_have;
	if (length <= 0) return LI_HANDLER_ERROR;

	switch (c->type) {
	case UNUSED_CHUNK: return LI_HANDLER_ERROR;
	case STRING_CHUNK:
		*data_start = c->data.str->str + c->offset + start;
		*data_len = length;
		break;
	case MEM_CHUNK:
		*data_start = (char*) c->mem->data + c->offset + start;
		*data_len = length;
		break;
	case FILE_CHUNK:
		if (LI_HANDLER_GO_ON != (res = li_chunkfile_open(c->data.file.file, err))) return res;

		if (length > MAX_MMAP_CHUNK) length = MAX_MMAP_CHUNK;

		if (!c->mem) {
			c->mem = g_byte_array_sized_new(length);
		} else {
			g_byte_array_set_size(c->mem, length);
		}

		our_start = start + c->offset + c->data.file.start;

read_chunk:
		if (-1 == (we_have = pread(c->data.file.file->fd, c->mem->data, length, our_start))) {
			if (EINTR == errno) goto read_chunk;
			g_set_error(err, LI_CHUNK_ERROR, 0, "li_chunkiter_read: pread failed for '%s' (fd = %i): %s",
				GSTR_SAFE_STR(c->data.file.file->name), c->data.file.file->fd,
				g_strerror(errno));
			g_byte_array_free(c->mem, TRUE);
			c->mem = NULL;
			return LI_HANDLER_ERROR;
		} else if (we_have != length) {
			/* may return less than requested bytes due to signals */
			/* CON_TRACE(srv, "read return unexpected number of bytes"); */
			if (we_have == 0) {
				g_set_error(err, LI_CHUNK_ERROR, 0, "li_chunkiter_read: pread returned 0 bytes for '%s' (fd = %i): unexpected end of file?",
					GSTR_SAFE_STR(c->data.file.file->name), c->data.file.file->fd);
				g_byte_array_free(c->mem, TRUE);
				c->mem = NULL;
				return LI_HANDLER_ERROR;
			}
			length = we_have;
			g_byte_array_set_size(c->mem, length);
		}
		*data_start = (char*) c->mem->data;
		*data_len = length;
		break;
	case BUFFER_CHUNK:
		*data_start = (char*) c->data.buffer.buffer->addr + c->data.buffer.offset + c->offset + start;
		*data_len = length;
		break;
	}
	return LI_HANDLER_GO_ON;
}

/* same as li_chunkiter_read, but tries mmap() first and falls back to pread();
 * as accessing mmap()-ed areas may result in SIGBUS, you have to handle that signal somehow.
 */
liHandlerResult li_chunkiter_read_mmap(liChunkIter iter, off_t start, off_t length, char **data_start, off_t *data_len, GError **err) {
	liChunk *c = li_chunkiter_chunk(iter);
	off_t we_want, we_have, our_start, our_offset;
	liHandlerResult res = LI_HANDLER_GO_ON;
	int mmap_errno = 0;

	g_return_val_if_fail (err == NULL || *err == NULL, LI_HANDLER_ERROR);

	if (!c) return LI_HANDLER_ERROR;
	if (!data_start || !data_len) return LI_HANDLER_ERROR;

	we_have = li_chunk_length(c) - start;
	if (length > we_have) length = we_have;
	if (length <= 0) return LI_HANDLER_ERROR;

	switch (c->type) {
	case UNUSED_CHUNK: return LI_HANDLER_ERROR;
	case STRING_CHUNK:
		*data_start = c->data.str->str + c->offset + start;
		*data_len = length;
		break;
	case MEM_CHUNK:
		*data_start = (char*) c->mem->data + c->offset + start;
		*data_len = length;
		break;
	case FILE_CHUNK:
		if (LI_HANDLER_GO_ON != (res = li_chunkfile_open(c->data.file.file, err))) return res;

		if (length > MAX_MMAP_CHUNK) length = MAX_MMAP_CHUNK;

		if ( !(c->data.file.mmap.data != MAP_FAILED || c->mem) /* no data present */
			|| !( /* or in the wrong range */
				(start + c->offset + c->data.file.start >= c->data.file.mmap.offset)
				&& (start + c->offset + c->data.file.start + length <= c->data.file.mmap.offset + (ssize_t) c->data.file.mmap.length)) ) {
			/* then find new range */
			our_start = start + c->offset + c->data.file.start;  /* "start" maps to this offset in the file */
			our_offset = our_start % MMAP_CHUNK_ALIGN;      /* offset for "start" in new mmap block */
			our_start -= our_offset;                 /* file offset for mmap */

			we_want = length + MAX_MMAP_CHUNK;
			if (we_want > we_have) we_want = we_have;
			we_want += our_offset;

			if (MAP_FAILED != c->data.file.mmap.data) {
				munmap(c->data.file.mmap.data, c->data.file.mmap.length);
				c->data.file.mmap.data = MAP_FAILED;
			}
			c->data.file.mmap.offset = our_start;
			c->data.file.mmap.length = we_want;
			if (!c->mem) { /* mmap did not fail till now */
				c->data.file.mmap.data = mmap(0, we_want, PROT_READ, MAP_SHARED, c->data.file.file->fd, our_start);
				mmap_errno = errno;
			}
			if (MAP_FAILED == c->data.file.mmap.data) {
				/* fallback to pread(...) */
				if (!c->mem) {
					c->mem = g_byte_array_sized_new(we_want);
				} else {
					g_byte_array_set_size(c->mem, we_want);
				}
read_chunk:
				if (-1 == (we_have = pread(c->data.file.file->fd, c->mem->data, we_want, our_start))) {
					if (EINTR == errno) goto read_chunk;
					/* prefer the error of the first syscall */
					if (0 != mmap_errno) {
						g_set_error(err, LI_CHUNK_ERROR, 0, "li_chunkiter_read_mmap: mmap failed for '%s' (fd = %i): %s",
							GSTR_SAFE_STR(c->data.file.file->name), c->data.file.file->fd,
							g_strerror(mmap_errno));
					} else {
						g_set_error(err, LI_CHUNK_ERROR, 0, "li_chunkiter_read_mmap: pread failed for '%s' (fd = %i): %s",
							GSTR_SAFE_STR(c->data.file.file->name), c->data.file.file->fd,
							g_strerror(errno));
					}
					g_byte_array_free(c->mem, TRUE);
					c->mem = NULL;
					return LI_HANDLER_ERROR;
				} else if (we_have != we_want) {
					/* may return less than requested bytes due to signals */
					/* CON_TRACE(srv, "read return unexpected number of bytes"); */
					we_want = we_have;
					if (length > we_have) length = we_have;
					c->data.file.mmap.length = we_want;
					g_byte_array_set_size(c->mem, we_want);
				}
			} else {
#ifdef HAVE_MADVISE
				/* don't advise files < 64Kb */
				if (c->data.file.mmap.length > (64*1024) &&
					0 != madvise(c->data.file.mmap.data, c->data.file.mmap.length, MADV_WILLNEED)) {
					/*
					g_debug("madvise failed for '%s' (fd = %i): %s",
						GSTR_SAFE_STR(c->data.file.file->name), c->data.file.file->fd,
						g_strerror(errno));
					*/
				}
#endif
			}
		}
		*data_start = (c->mem ? (char*) c->mem->data : c->data.file.mmap.data) + start + c->offset + c->data.file.start - c->data.file.mmap.offset;
		*data_len = length;
		break;
	case BUFFER_CHUNK:
		*data_start = (char*) c->data.buffer.buffer->addr + c->data.buffer.offset + c->offset + start;
		*data_len = length;
		break;
	}
	return LI_HANDLER_GO_ON;
}

/******************
 *     chunk      *
 ******************/

static liChunk* chunk_new(void) {
	liChunk *c = g_slice_new0(liChunk);
	c->data.file.mmap.data = MAP_FAILED;
	c->cq_link.data = c;
	return c;
}

static void chunk_free(liChunkQueue *cq, liChunk *c) {
	if (!c) return;
	if (cq) {
		g_queue_unlink(&cq->queue, &c->cq_link);
	}
	switch (c->type) {
	case UNUSED_CHUNK:
		break;
	case STRING_CHUNK:
		g_string_free(c->data.str, TRUE);
		c->data.str = NULL;
		break;
	case MEM_CHUNK:
		/* mem is handled extra below */
		break;
	case FILE_CHUNK:
		if (c->data.file.file) {
			li_chunkfile_release(c->data.file.file);
			c->data.file.file = NULL;
		}
		if (c->data.file.mmap.data != MAP_FAILED) {
			munmap(c->data.file.mmap.data, c->data.file.mmap.length);
			c->data.file.mmap.data = MAP_FAILED;
		}
		break;
	case BUFFER_CHUNK:
		li_buffer_release(c->data.buffer.buffer);
		break;
	}
	c->type = UNUSED_CHUNK;
	if (c->mem) {
		g_byte_array_free(c->mem, TRUE);
		c->mem = NULL;
	}
	g_slice_free(liChunk, c);
}

/******************
 *    cqlimit     *
 ******************/
liCQLimit* li_cqlimit_new(void) {
	liCQLimit *cql = g_slice_new0(liCQLimit);
	cql->refcount = 1;
	cql->limit = -1;
	return cql;
}

void li_cqlimit_reset(liCQLimit *cql) {
	LI_FORCE_ASSERT(cql->current == 0);
	LI_FORCE_ASSERT(cql->io_watcher == NULL);
	LI_FORCE_ASSERT(cql->notify == NULL);
	cql->current = 0;
	cql->limit = -1;
	cql->io_watcher = NULL;
	cql->notify = NULL;
}

void li_cqlimit_acquire(liCQLimit *cql) {
	LI_FORCE_ASSERT(g_atomic_int_get(&cql->refcount) > 0);
	g_atomic_int_inc(&cql->refcount);
}

void li_cqlimit_release(liCQLimit *cql) {
	if (!cql) return;
	LI_FORCE_ASSERT(g_atomic_int_get(&cql->refcount) > 0);
	if (g_atomic_int_dec_and_test(&cql->refcount)) {
		g_slice_free(liCQLimit, cql);
	}
}

static void cqlimit_lock(liCQLimit *cql) {
	cql->locked = TRUE;
	if (NULL != cql->io_watcher) {
		li_event_io_rem_events(cql->io_watcher, LI_EV_READ);
	}
	if (cql->notify) {
		cql->notify(cql->context, cql->locked);
	}
}

static void cqlimit_unlock(liCQLimit *cql) {
	cql->locked = FALSE;
	if (NULL != cql->io_watcher) {
		li_event_io_add_events(cql->io_watcher, LI_EV_READ);
	}
	if (cql->notify) {
		cql->notify(cql->context, cql->locked);
	}
}

static void cqlimit_update(liChunkQueue *cq, goffset d) {
	liCQLimit *cql;

	if (!cq) return;
	cq->mem_usage += d;
	LI_FORCE_ASSERT(cq->mem_usage >= 0);
	cql = cq->limit;
	/* g_printerr("cqlimit_update: cq->mem_usage: %"LI_GOFFSET_FORMAT"\n", cq->mem_usage); */

	if (!cql) return;
	cql->current += d;
	LI_FORCE_ASSERT(cql->current >= 0);
	/* g_printerr("cqlimit_update: cql->current: %"LI_GOFFSET_FORMAT", cql->limit: %"LI_GOFFSET_FORMAT"\n", cql->current, cql->limit); */
	if (cql->locked) {
		if (cql->limit <= 0 || cql->current < cql->limit) {
			cqlimit_unlock(cql);
		}
	} else {
		if (cql->limit > 0 && cql->current >= cql->limit) {
			cqlimit_lock(cql);
		}
	}
}

void li_cqlimit_set_limit(liCQLimit *cql, goffset limit) {
	if (!cql) return;

	cql->limit = limit;
	if (cql->locked) {
		if (cql->limit <= 0 || cql->current < cql->limit) {
			cqlimit_unlock(cql);
		}
	} else {
		if (cql->limit > 0 && cql->current >= cql->limit) {
			cqlimit_lock(cql);
		}
	}
}


/******************
 *   chunkqueue   *
 ******************/

liChunkQueue* li_chunkqueue_new(void) {
	liChunkQueue *cq = g_slice_new0(liChunkQueue);
	g_queue_init(&cq->queue);
	return cq;
}

static void __chunk_free(gpointer _c, gpointer userdata) {
	liChunk *c = (liChunk *)_c;
	liChunkQueue *cq = (liChunkQueue*) userdata;
	if (c->type == STRING_CHUNK) cqlimit_update(cq, - (goffset)c->data.str->len);
	else if (c->type == MEM_CHUNK) cqlimit_update(cq, - (goffset)c->mem->len);
	else if (c->type == BUFFER_CHUNK) cqlimit_update(cq, - (goffset)c->data.buffer.length);
	chunk_free(cq, c);
}

void li_chunkqueue_reset(liChunkQueue *cq) {
	if (!cq) return;
	cq->is_closed = FALSE;
	cq->bytes_in = cq->bytes_out = cq->length = 0;
	g_queue_foreach(&cq->queue, __chunk_free, cq);
	LI_FORCE_ASSERT(cq->mem_usage == 0);
	cq->mem_usage = 0;
	g_queue_init(&cq->queue); /* should be empty now */
}

void li_chunkqueue_free(liChunkQueue *cq) {
	if (!cq) return;
	g_queue_foreach(&cq->queue, __chunk_free, cq);
	li_cqlimit_release(cq->limit);
	cq->limit = NULL;
	LI_FORCE_ASSERT(cq->mem_usage == 0);
	cq->mem_usage = 0;
	g_slice_free(liChunkQueue, cq);
}

void li_chunkqueue_use_limit(liChunkQueue *cq, goffset limit) {
	if (!cq->limit) cq->limit = li_cqlimit_new();
	li_cqlimit_set_limit(cq->limit, limit);
}

void li_chunkqueue_set_limit(liChunkQueue *cq, liCQLimit* cql) {
	goffset memusage = cq->mem_usage;

	if (cql == cq->limit) return;

	if (cql) li_cqlimit_acquire(cql);
	cqlimit_update(cq, -memusage);
	li_cqlimit_release(cq->limit);
	cq->limit = cql;
	cqlimit_update(cq, memusage);
}

/* return -1 for unlimited, 0 for full and n > 0 for n bytes free */
goffset li_chunkqueue_limit_available(liChunkQueue *cq) {
	liCQLimit *cql = cq->limit;
	goffset avail;
	if (!cql) return -1;
	if (cql->limit <= 0) return -1;
	avail = cql->limit - cql->current;
	if (avail < 0) return 0;
	return avail;
}

 /* pass ownership of str to chunkqueue, do not free/modify it afterwards
  * you may modify the data (not the length) if you are sure it isn't sent before.
  * if the length is NULL, str is destroyed immediately
  */
void li_chunkqueue_append_string(liChunkQueue *cq, GString *str) {
	liChunk *c;
	if (!str->len) {
		g_string_free(str, TRUE);
		return;
	}
	c = chunk_new();
	c->type = STRING_CHUNK;
	c->data.str = str;
	g_queue_push_tail_link(&cq->queue, &c->cq_link);
	cq->length += str->len;
	cq->bytes_in += str->len;
	cqlimit_update(cq, str->len);
}

 /* pass ownership of mem to chunkqueue, do not free/modify it afterwards
  * you may modify the data (not the length) if you are sure it isn't sent before.
  * if the length is NULL, mem is destroyed immediately
  */
void li_chunkqueue_append_bytearr(liChunkQueue *cq, GByteArray *mem) {
	liChunk *c;
	if (!mem->len) {
		g_byte_array_free(mem, TRUE);
		return;
	}
	c = chunk_new();
	c->type = MEM_CHUNK;
	c->mem = mem;
	g_queue_push_tail_link(&cq->queue, &c->cq_link);
	cq->length += mem->len;
	cq->bytes_in += mem->len;
	cqlimit_update(cq, mem->len);
}

 /* pass ownership of one buffer reference to chunkqueue
  * if the length is NULL, reference is released immediately
  */
void li_chunkqueue_append_buffer(liChunkQueue *cq, liBuffer *buffer) {
	liChunk *c;
	if (!buffer->used) {
		li_buffer_release(buffer);
		return;
	}
	c = chunk_new();
	c->type = BUFFER_CHUNK;
	c->data.buffer.buffer = buffer;
	c->data.buffer.offset = 0;
	c->data.buffer.length = buffer->used;
	g_queue_push_tail_link(&cq->queue, &c->cq_link);
	cq->length += buffer->used;
	cq->bytes_in += buffer->used;
	cqlimit_update(cq, buffer->used);
}

void li_chunkqueue_append_buffer2(liChunkQueue *cq, liBuffer *buffer, gsize offset, gsize length) {
	liChunk *c;
	if (length == 0) {
		li_buffer_release(buffer);
		return;
	}
	LI_FORCE_ASSERT(offset + length <= buffer->used);
	c = chunk_new();
	c->type = BUFFER_CHUNK;
	c->data.buffer.buffer = buffer;
	c->data.buffer.offset = offset;
	c->data.buffer.length = length;
	g_queue_push_tail_link(&cq->queue, &c->cq_link);
	cq->length += length;
	cq->bytes_in += length;
	cqlimit_update(cq, length);
}

/* memory gets copied */
void li_chunkqueue_append_mem(liChunkQueue *cq, const void *mem, gssize len) {
	liChunk *c;
	if (!len) return;
	c = chunk_new();
	c->type = MEM_CHUNK;
	c->mem = g_byte_array_sized_new(len);
	g_byte_array_append(c->mem, mem, len);
	g_queue_push_tail_link(&cq->queue, &c->cq_link);
	cq->length += c->mem->len;
	cq->bytes_in += c->mem->len;
	cqlimit_update(cq, c->mem->len);
}

/* increases reference for cf (if length > 0) */
void li_chunkqueue_append_chunkfile(liChunkQueue *cq, liChunkFile *cf, off_t start, off_t length) {
	if (length) {
		liChunk *c = chunk_new();
		li_chunkfile_acquire(cf);

		c->type = FILE_CHUNK;
		c->data.file.file = cf;
		c->data.file.start = start;
		c->data.file.length = length;

		g_queue_push_tail_link(&cq->queue, &c->cq_link);
		cq->length += length;
		cq->bytes_in += length;
	}
}

static void __chunkqueue_append_file(liChunkQueue *cq, GString *filename, off_t start, off_t length, int fd, gboolean is_temp) {
	liChunk *c = chunk_new();
	c->type = FILE_CHUNK;
	c->data.file.file = li_chunkfile_new(filename, fd, is_temp);
	c->data.file.start = start;
	c->data.file.length = length;

	g_queue_push_tail_link(&cq->queue, &c->cq_link);
	cq->length += length;
	cq->bytes_in += length;
}
/* pass ownership of filename, do not free it */
void li_chunkqueue_append_file(liChunkQueue *cq, GString *filename, off_t start, off_t length) {
	if (length)
		__chunkqueue_append_file(cq, filename, start, length, -1, FALSE);
}

/* if you already opened the file, you can pass the fd here - do not close it */
void li_chunkqueue_append_file_fd(liChunkQueue *cq, GString *filename, off_t start, off_t length, int fd) {
	if (length) {
		__chunkqueue_append_file(cq, filename, start, length, fd, FALSE);
	} else {
		if (-1 != fd) close(fd);
	}
}

/* temp files get deleted after usage */
/* pass ownership of filename, do not free it */
void li_chunkqueue_append_tempfile(liChunkQueue *cq, GString *filename, off_t start, off_t length) {
	if (length)
		__chunkqueue_append_file(cq, filename, start, length, -1, TRUE);
}

/* if you already opened the file, you can pass the fd here - do not close it */
void li_chunkqueue_append_tempfile_fd(liChunkQueue *cq, GString *filename, off_t start, off_t length, int fd) {
	if (length)
		__chunkqueue_append_file(cq, filename, start, length, fd, TRUE);
	else {
		if (-1 != fd) close(fd);
		unlink(filename->str);
	}
}

/* steal up to length bytes from in and put them into out, return number of bytes stolen */
goffset li_chunkqueue_steal_len(liChunkQueue *out, liChunkQueue *in, goffset length) {
	liChunk *c, *cnew;
	GList* l;
	goffset bytes = 0, meminbytes = 0, memoutbytes = 0;
	goffset we_have;

	while ( (NULL != (c = li_chunkqueue_first_chunk(in))) && length > 0 ) {
		we_have = li_chunk_length(c);
		if (!we_have) { /* remove empty chunks */
			if (c->type == STRING_CHUNK) meminbytes -= c->data.str->len;
			else if (c->type == MEM_CHUNK) meminbytes -= c->mem->len;
			else if (c->type == BUFFER_CHUNK) meminbytes -= c->data.buffer.length;
			chunk_free(in, c);
			continue;
		}
		if (we_have <= length) { /* move complete chunk */
			l = g_queue_pop_head_link(&in->queue);
			g_queue_push_tail_link(&out->queue, l);
			bytes += we_have;
			if (c->type == STRING_CHUNK) {
				meminbytes -= c->data.str->len;
				memoutbytes += c->data.str->len;
			} else if (c->type == MEM_CHUNK) {
				meminbytes -= c->mem->len;
				memoutbytes += c->mem->len;
			} else if (c->type == BUFFER_CHUNK) {
				meminbytes -= c->data.buffer.length;
				memoutbytes += c->data.buffer.length;
			}
			length -= we_have;
		} else { /* copy first part of a chunk */
			cnew = chunk_new();
			switch (c->type) {
			case UNUSED_CHUNK: /* impossible, has length 0 */
				/* remove "empty" chunks */
				chunk_free(in, c);
				chunk_free(NULL, cnew);
				continue;
			case STRING_CHUNK: /* change type to MEM_CHUNK, as we copy it anyway */
				cnew->type = MEM_CHUNK;
				cnew->mem = g_byte_array_sized_new(length);
				g_byte_array_append(cnew->mem, (guint8*) c->data.str->str + c->offset, length);
				memoutbytes += length;
				break;
			case MEM_CHUNK:
				cnew->type = MEM_CHUNK;
				cnew->mem = g_byte_array_sized_new(length);
				g_byte_array_append(cnew->mem, (guint8*) c->mem->data + c->offset, length);
				memoutbytes += length;
				break;
			case FILE_CHUNK:
				cnew->type = FILE_CHUNK;
				li_chunkfile_acquire(c->data.file.file);
				cnew->data.file.file = c->data.file.file;
				cnew->data.file.start = c->data.file.start + c->offset;
				cnew->data.file.length = length;
				break;
			case BUFFER_CHUNK:
				cnew->type = BUFFER_CHUNK;
				li_buffer_acquire(c->data.buffer.buffer);
				cnew->data.buffer.buffer = c->data.buffer.buffer;
				cnew->data.buffer.offset = c->data.buffer.offset + c->offset;
				cnew->data.buffer.length = length;
				memoutbytes += length;
				break;
			}
			c->offset += length;
			bytes += length;
			length = 0;
			g_queue_push_tail_link(&out->queue, &cnew->cq_link);
		}
	}

	in->bytes_out += bytes;
	in->length -= bytes;
	out->bytes_in += bytes;
	out->length += bytes;
	cqlimit_update(out, memoutbytes);
	cqlimit_update(in, meminbytes);

	return bytes;
}

/* steal all chunks from in and put them into out, return number of bytes stolen */
goffset li_chunkqueue_steal_all(liChunkQueue *out, liChunkQueue *in) {
	goffset len;

	/* if in->queue is empty, do nothing */
	if (!in->length) return 0;

	if (in->limit != out->limit) {
		cqlimit_update(out, in->mem_usage);
		cqlimit_update(in, -in->mem_usage);
	} else {
		out->mem_usage += in->mem_usage;
		in->mem_usage = 0;
	}

	li_g_queue_merge(&out->queue, &in->queue);

	/* count bytes in chunkqueues */
	len = in->length;
	in->bytes_out += len;
	in->length = 0;
	out->bytes_in += len;
	out->length += len;

	return len;
}

/* steal the first chunk from in and append it to out, return number of bytes stolen */
goffset li_chunkqueue_steal_chunk(liChunkQueue *out, liChunkQueue *in) {
	liChunk *c;
	goffset length;
	GList *l = g_queue_pop_head_link(&in->queue);
	if (!l) return 0;
	g_queue_push_tail_link(&out->queue, l);

	c = (liChunk*) l->data;
	length = li_chunk_length(c);
	in->bytes_out += length;
	in->length -= length;
	out->bytes_in += length;
	out->length += length;
	if (in->limit != out->limit) {
		if (c->type == STRING_CHUNK) {
			cqlimit_update(out, c->data.str->len);
			cqlimit_update(in, - (goffset)c->data.str->len);
		} else if (c->type == MEM_CHUNK) {
			cqlimit_update(out, c->mem->len);
			cqlimit_update(in, - (goffset)c->mem->len);
		} else if (c->type == BUFFER_CHUNK) {
			cqlimit_update(out, c->data.buffer.length);
			cqlimit_update(in, - (goffset)c->data.buffer.length);
		}
	}
	return length;
}

/* skip up to length bytes in a chunkqueue, return number of bytes skipped */
goffset li_chunkqueue_skip(liChunkQueue *cq, goffset length) {
	liChunk *c;
	goffset bytes = 0;
	goffset we_have;

	while ( (NULL != (c = li_chunkqueue_first_chunk(cq))) && (0 == (we_have = li_chunk_length(c)) || length > 0) ) {
		if (we_have <= length) {
			/* skip (delete) complete chunk */
			if (c->type == STRING_CHUNK) cqlimit_update(cq, - (goffset)c->data.str->len);
			else if (c->type == MEM_CHUNK) cqlimit_update(cq, - (goffset)c->mem->len);
			else if (c->type == BUFFER_CHUNK) cqlimit_update(cq, - (goffset)c->data.buffer.length);
			chunk_free(cq, c);
			bytes += we_have;
			length -= we_have;
		} else { /* skip first part of a chunk */
			c->offset += length;
			bytes += length;
			length = 0;
		}
	}

	cq->bytes_out += bytes;
	cq->length -= bytes;
	return bytes;
}

goffset li_chunkqueue_skip_all(liChunkQueue *cq) {
	goffset bytes = cq->length;

	g_queue_foreach(&cq->queue, __chunk_free, cq);
	g_queue_init(&cq->queue);

	cq->bytes_out += bytes;
	cq->length = 0;

	return bytes;
}

gboolean li_chunkqueue_extract_to(liChunkQueue *cq, goffset len, GString *dest, GError **err) {
	liChunkIter ci;
	goffset coff, clen;

	g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

	g_string_set_size(dest, 0);
	if (len > cq->length) return FALSE;

	ci = li_chunkqueue_iter(cq);

	while (len > 0) {
		coff = 0;
		clen = li_chunkiter_length(ci);
		while (coff < clen) {
			gchar *buf;
			off_t we_have;
			if (LI_HANDLER_GO_ON != li_chunkiter_read(ci, coff, len, &buf, &we_have, err)) goto error;
			g_string_append_len(dest, buf, we_have);
			coff += we_have;
			len -= we_have;
			if (len <= 0) return TRUE;
		}
		li_chunkiter_next(&ci);
	}

	return TRUE;

error:
	g_string_assign(dest, "");
	return FALSE;
}

gboolean li_chunkqueue_extract_to_memory(liChunkQueue *cq, goffset len, void *dest, GError **err) {
	liChunkIter ci;
	goffset coff, clen;
	unsigned char *cdest = (unsigned char*) dest;

	g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

	if (len > cq->length) return FALSE;

	ci = li_chunkqueue_iter(cq);

	while (len > 0) {
		coff = 0;
		clen = li_chunkiter_length(ci);
		while (coff < clen) {
			gchar *buf;
			off_t we_have;
			if (LI_HANDLER_GO_ON != li_chunkiter_read(ci, coff, len, &buf, &we_have, err)) goto error;
			memcpy(cdest, buf, we_have);
			cdest += we_have;
			coff += we_have;
			len -= we_have;
			if (len <= 0) return TRUE;
		}
		li_chunkiter_next(&ci);
	}

	return TRUE;

error:
	g_byte_array_set_size(dest, 0);
	return FALSE;
}

gboolean li_chunkqueue_extract_to_bytearr(liChunkQueue *cq, goffset len, GByteArray *dest, GError **err) {
	g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

	if (len > cq->length) return FALSE;

	g_byte_array_set_size(dest, len);

	if (!li_chunkqueue_extract_to_memory(cq, len, dest->data, err)) {
		g_byte_array_set_size(dest, 0);
		return FALSE;
	}

	return TRUE;
}

/* helper functions to append to the last BUFFER_CHUNK of a chunkqueue */

/* returns the liBuffer from the last chunk in cq, if the chunk has type BUFFER_CHUNK,
 * and the buffer has at least min_space bytes free and refcount == 1 (NULL otherwise) */
liBuffer* li_chunkqueue_get_last_buffer(liChunkQueue *cq, guint min_space) {
	liChunk *c = g_queue_peek_tail(&cq->queue);
	liBuffer *buf;

	if (!c || c->type != BUFFER_CHUNK) return NULL;
	buf = c->data.buffer.buffer;
	if (g_atomic_int_get(&buf->refcount) != 1 || (buf->alloc_size - buf->used) < min_space) return NULL;
	/* truncate buf->used - we are the only reference, so that is no problem;
	 * but we need to append directly after the current data block
	 */
	buf->used = c->data.buffer.offset + c->data.buffer.length;
	return buf;
}

/* only call this if li_chunkqueue_get_last_buffer returned a buffer; don't modify the chunkqueue
 * between the two calls
 * updates the buffer and the cq data
 */
LI_API void li_chunkqueue_update_last_buffer_size(liChunkQueue *cq, goffset add_length) {
	liChunk *c = g_queue_peek_tail(&cq->queue);
	liBuffer *buf;

	LI_FORCE_ASSERT(c && c->type == BUFFER_CHUNK);
	buf = c->data.buffer.buffer;
	buf->used += add_length;
	c->data.buffer.length += add_length;

	cq->length += add_length;
	cq->bytes_in += add_length;
	cqlimit_update(cq, add_length);
}
