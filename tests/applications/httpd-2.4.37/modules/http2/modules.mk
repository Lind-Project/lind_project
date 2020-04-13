mod_http2.la: mod_http2.slo h2_alt_svc.slo h2_bucket_beam.slo h2_bucket_eos.slo h2_config.slo h2_conn.slo h2_conn_io.slo h2_ctx.slo h2_filter.slo h2_from_h1.slo h2_h2.slo h2_headers.slo h2_mplx.slo h2_ngn_shed.slo h2_push.slo h2_request.slo h2_session.slo h2_stream.slo h2_switch.slo h2_task.slo h2_util.slo h2_workers.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_http2.lo h2_alt_svc.lo h2_bucket_beam.lo h2_bucket_eos.lo h2_config.lo h2_conn.lo h2_conn_io.lo h2_ctx.lo h2_filter.lo h2_from_h1.lo h2_h2.lo h2_headers.lo h2_mplx.lo h2_ngn_shed.lo h2_push.lo h2_request.lo h2_session.lo h2_stream.lo h2_switch.lo h2_task.lo h2_util.lo h2_workers.lo  $(MOD_HTTP2_LDADD)
DISTCLEAN_TARGETS = modules.mk
static = 
shared =  mod_http2.la
MOD_CPPFLAGS = -DH2_OPENSSL -DH2_NG2_CHANGE_PRIO -DH2_NG2_INVALID_HEADER_CB -DH2_NG2_LOCAL_WIN_SIZE
MOD_LDFLAGS = -lssl -lcrypto    -lnghttp2
