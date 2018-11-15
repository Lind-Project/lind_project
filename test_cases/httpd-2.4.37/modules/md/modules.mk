mod_md.la: md_acme.slo md_acme_acct.slo md_acme_authz.slo md_acme_drive.slo md_core.slo md_curl.slo md_crypt.slo md_http.slo md_json.slo md_jws.slo md_log.slo md_reg.slo md_store.slo md_store_fs.slo md_util.slo mod_md.slo mod_md_config.slo mod_md_os.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  md_acme.lo md_acme_acct.lo md_acme_authz.lo md_acme_drive.lo md_core.lo md_curl.lo md_crypt.lo md_http.lo md_json.lo md_jws.lo md_log.lo md_reg.lo md_store.lo md_store_fs.lo md_util.lo mod_md.lo mod_md_config.lo mod_md_os.lo  $(MOD_MD_LDADD)
DISTCLEAN_TARGETS = modules.mk
static = 
shared =  mod_md.la
MOD_LDFLAGS = -lssl -lcrypto    -ljansson -lcurl
