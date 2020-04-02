#ifndef _LIGHTTPD_ANGEL_DATA_H_
#define _LIGHTTPD_ANGEL_DATA_H_

/* write/read data from/to a buffer (GString) (binary)
 * this is not meant to be the most performant way to do this,
 * as communication with the angel shouldn't happen to often anyway.
 *
 * Please never send "user" data to the angel (i.e. do not implement
 * something like a mod_cgi via sending the request data to the angel;
 * instead use the angel to spawn a fastcgi backend (or something similar)
 * and send the request via a socket to the backend directly.
 */

/* angel obviously doesn't work across platforms, so we don't need
 * to care about endianess
 */

/* The buffer may be bigger of course, but a single string should not
 * exceed this length: */
#define LI_ANGEL_DATA_MAX_STR_LEN 1024 /* must fit into a gint32 */

/* Needed for reading data */
typedef struct liAngelBuffer liAngelBuffer;
struct liAngelBuffer {
	GString *data;
	gsize pos;
};

/* error handling */
#define LI_ANGEL_DATA_ERROR li_angel_data_error_quark()
LI_API GQuark li_angel_data_error_quark(void);

typedef enum {
	LI_ANGEL_DATA_ERROR_EOF,                    /* not enough data to read value */
	LI_ANGEL_DATA_ERROR_INVALID_STRING_LENGTH,  /* invalid string length read from buffer (< 0 || > max-str-len) */
	LI_ANGEL_DATA_ERROR_STRING_TOO_LONG         /* string too long (len > max-str-len) */
} liAngelDataError;

/* write */
LI_API gboolean li_angel_data_write_int32(GString *buf, gint32 i, GError **err);
LI_API gboolean li_angel_data_write_int64(GString *buf, gint64 i, GError **err);
LI_API gboolean li_angel_data_write_char (GString *buf, gchar c, GError **err);
LI_API gboolean li_angel_data_write_str  (GString *buf, const GString *str, GError **err);
LI_API gboolean li_angel_data_write_cstr (GString *buf, const gchar *str, gsize len, GError **err);

/* read:
 * - if the val pointer is NULL, the data will be discarded
 * - reading strings: if *val != NULL *val will be reused;
 *   otherwise a new GString* will be created
 * - *val will only be modified if no error is returned
 */
LI_API gboolean li_angel_data_read_int32(liAngelBuffer *buf, gint32 *val, GError **err);
LI_API gboolean li_angel_data_read_int64(liAngelBuffer *buf, gint64 *val, GError **err);
LI_API gboolean li_angel_data_read_char (liAngelBuffer *buf, gchar *val, GError **err);
LI_API gboolean li_angel_data_read_str  (liAngelBuffer *buf, GString **val, GError **err);
LI_API gboolean li_angel_data_read_mem  (liAngelBuffer *buf, GString **val, gsize len, GError **err);

#endif
