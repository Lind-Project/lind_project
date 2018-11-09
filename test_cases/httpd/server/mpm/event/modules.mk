libevent.la: event.lo
	$(MOD_LINK) event.lo
DISTCLEAN_TARGETS = modules.mk
static = libevent.la
shared =
