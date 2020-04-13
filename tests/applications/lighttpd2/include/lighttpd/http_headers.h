#ifndef _LIGHTTPD_HTTP_HEADERS_H_
#define _LIGHTTPD_HTTP_HEADERS_H_

#ifndef _LIGHTTPD_BASE_H_
#error Please include <lighttpd/base.h> instead of this file
#endif

#define LI_HEADER_VALUE(h) \
	(&(h)->data->str[(h)->keylen + 2])

#define LI_HEADER_VALUE_LEN(h) \
	(&(h)->data->str[(h)->keylen + 2]), ((h)->data->len - ((h)->keylen + 2))

#define LI_HEADER_KEY_LEN(h) \
	((h)->data->str), ((h)->keylen)

struct liHttpHeader {
	guint keylen;     /** length of "headername" in data */
	GString *data;    /** "headername: value" */
};

struct liHttpHeaders {
	GQueue entries;
};

typedef struct liHttpHeaderTokenizer liHttpHeaderTokenizer;
struct liHttpHeaderTokenizer {
	GList *cur;
	guint pos;
};

/* strings always get copied, so you should free key and value yourself */

LI_API liHttpHeaders* li_http_headers_new(void);
LI_API void li_http_headers_reset(liHttpHeaders* headers);
LI_API void li_http_headers_free(liHttpHeaders* headers);

/** If header does not exist, just insert normal header. If it exists, append (", %s", value) */
LI_API void li_http_header_append(liHttpHeaders *headers, const gchar *key, size_t keylen, const gchar *val, size_t valuelen);

/** Add new entry to list ("%s: %s", key, value) */
LI_API void li_http_header_insert(liHttpHeaders *headers, const gchar *key, size_t keylen, const gchar *val, size_t valuelen);

/** If header does not exist, just insert normal header. If it exists, overwrite the value */
LI_API void li_http_header_overwrite(liHttpHeaders *headers, const gchar *key, size_t keylen, const gchar *val, size_t valuelen);

/** Remove all header entries with specified key */
LI_API gboolean li_http_header_remove(liHttpHeaders *headers, const gchar *key, size_t keylen);

LI_API void li_http_header_remove_link(liHttpHeaders *headers, GList *l);

LI_API liHttpHeader* li_http_header_lookup(liHttpHeaders *headers, const gchar *key, size_t keylen);

LI_API GList* li_http_header_find_first(liHttpHeaders *headers, const gchar *key, size_t keylen);
LI_API GList* li_http_header_find_next(GList *l, const gchar *key, size_t keylen);
LI_API GList* li_http_header_find_last(liHttpHeaders *headers, const gchar *key, size_t keylen);

/** Use lowercase keys! values are compared case-insensitive */
LI_API gboolean li_http_header_is(liHttpHeaders *headers, const gchar *key, size_t keylen, const gchar *val, size_t valuelen);

/** concats all headers with key with ', ' - empty if no header exists */
LI_API void li_http_header_get_all(GString *dest, liHttpHeaders *headers, const gchar *key, size_t keylen);

INLINE gboolean li_http_header_key_is(liHttpHeader *h, const gchar *key, size_t keylen) {
	return (h->keylen == keylen && 0 == g_ascii_strncasecmp(key, h->data->str, keylen));
}

/* very simple tokenizer. splits at ' ' and ',', unquotes \\ escapes and "..." tokens */
LI_API void li_http_header_tokenizer_start(liHttpHeaderTokenizer *tokenizer, liHttpHeaders *headers, const gchar *key, size_t keylen);
LI_API gboolean li_http_header_tokenizer_next(liHttpHeaderTokenizer *tokenizer, GString *token);


#endif
