#include <stdlib.h>
#include <linux/tcp.h>
#include "net.h"
#include "compat.h"
#include "random.h"
#include "utils.h"	// RAND_ARRAY

static const unsigned int tcp_opts[] = {
	TCP_NODELAY, TCP_MAXSEG, TCP_CORK, TCP_KEEPIDLE,
	TCP_KEEPINTVL, TCP_KEEPCNT, TCP_SYNCNT, TCP_LINGER2,
	TCP_DEFER_ACCEPT, TCP_WINDOW_CLAMP, TCP_INFO, TCP_QUICKACK,
	TCP_CONGESTION, TCP_MD5SIG, TCP_COOKIE_TRANSACTIONS, TCP_THIN_LINEAR_TIMEOUTS,
	TCP_THIN_DUPACK, TCP_USER_TIMEOUT, TCP_REPAIR, TCP_REPAIR_QUEUE,
	TCP_QUEUE_SEQ, TCP_REPAIR_OPTIONS, TCP_FASTOPEN, TCP_TIMESTAMP,
	TCP_NOTSENT_LOWAT, TCP_CC_INFO, TCP_SAVE_SYN, TCP_SAVED_SYN,
	TCP_REPAIR_WINDOW,
};

void tcp_setsockopt(struct sockopt *so, __unused__ struct socket_triplet *triplet)
{
	so->optname = RAND_ARRAY(tcp_opts);
}
