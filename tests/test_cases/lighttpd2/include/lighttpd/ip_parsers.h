#ifndef _LIGHTTPD_IP_PARSERS_H_
#define _LIGHTTPD_IP_PARSERS_H_

#include <lighttpd/settings.h>

/** optional parameters are set to default values (netmask all bits, port 0) */
/** parse an IPv4 (if netmask is not NULL with optional cidr netmask, if port is not NULL with optional port) */
LI_API gboolean li_parse_ipv4(const char *str, guint32 *ip, guint32 *netmask, guint16 *port);
/** parse an IPv6 (if network is not NULL with optional cidr network, if port is not NULL with optional port if the ip/cidr part is in [...]) */
LI_API gboolean li_parse_ipv6(const char *str, guint8 *ip, guint *network, guint16 *port);
/** print the ip into dest, return dest */
LI_API GString* li_ipv6_tostring(GString *dest, const guint8 ip[16]);

#endif
