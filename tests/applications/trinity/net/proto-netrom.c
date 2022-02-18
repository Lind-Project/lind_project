#include "config.h"

#ifdef USE_NETROM
#include <stdlib.h>
#include <netrom/netrom.h>
#include "net.h"
#include "compat.h"
#include "utils.h"	// RAND_ARRAY

static const unsigned int netrom_opts[] = {
	NETROM_T1, NETROM_T2, NETROM_N2, NETROM_T4, NETROM_IDLE
};

void netrom_setsockopt(struct sockopt *so)
{
	so->optname = RAND_ARRAY(netrom_opts);
}
#endif
