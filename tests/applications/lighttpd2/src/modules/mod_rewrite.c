/*
 * mod_rewrite - modify request path and querystring with support for regular expressions
 *
 * Authors:
 *     Copyright (c) 2009 Thomas Porzelt
 *     Copyright (c) 2010 Stefan Bühler
 * License:
 *     MIT, see COPYING file in the lighttpd 2 tree
 */

#include <lighttpd/base.h>
#include <lighttpd/encoding.h>
#include <lighttpd/pattern.h>
#include <lighttpd/url_parser.h>

LI_API gboolean mod_rewrite_init(liModules *mods, liModule *mod);
LI_API gboolean mod_rewrite_free(liModules *mods, liModule *mod);

typedef struct rewrite_rule rewrite_rule;
struct rewrite_rule {
	liPattern *path, *querystring;
	GRegex *regex;
};

typedef struct rewrite_data rewrite_data;
struct rewrite_data {
	GArray *rules;
	liPlugin *p;
};

static gboolean rewrite_rule_parse(liServer *srv, GString *regex, GString *str, rewrite_rule *rule, gboolean raw) {
	gchar *qs = NULL;

	rule->path = rule->querystring = NULL;
	rule->regex = NULL;

	if (!raw) {
		/* find "not-escaped" ? */
		for (qs = str->str; *qs; qs++) {
			if ('\\' == *qs) {
				qs++;
				if (!*qs) break;
			} else if ('?' == *qs) break;
		}
		if (!*qs) qs = NULL;
	}

	if (NULL != qs) {
		*qs = '\0'; /* restore later */
		rule->querystring = li_pattern_new(srv, qs+1);
		if (NULL == rule->querystring) {
			goto error;
		}
	}

	rule->path = li_pattern_new(srv, str->str);
	if (NULL == rule->path) {
		goto error;
	}

	if (NULL != regex) {
		GError *err = NULL;
		rule->regex = g_regex_new(regex->str, G_REGEX_RAW | G_REGEX_OPTIMIZE, 0, &err);

		if (NULL == rule->regex || NULL != err) {
			ERROR(srv, "rewrite: error compiling regex \"%s\": %s", regex->str, NULL != err ? err->message : "unknown error");
			g_error_free(err);
			goto error;
		}
	}

	if (NULL != qs) {
		*qs = '?';
	}

	return TRUE;

error:
	if (NULL != rule->querystring) {
		li_pattern_free(rule->querystring);
		rule->querystring = NULL;
	}
	if (NULL != rule->path) {
		li_pattern_free(rule->path);
		rule->path = NULL;
	}
	if (NULL != rule->regex) {
		g_regex_unref(rule->regex);
		rule->regex = NULL;
	}

	if (NULL != qs) {
		*qs = '?';
	}

	return FALSE;
}

static gboolean rewrite_internal(liVRequest *vr, GString *dest_path, GString *dest_query, rewrite_rule *rule, gchar *path) {
	GMatchInfo *match_info = NULL;
	GMatchInfo *prev_match_info = NULL;

	if (NULL != rule->regex && !g_regex_match(rule->regex, path, 0, &match_info)) {
		if (NULL != match_info) {
			g_match_info_free(match_info);
		}

		return FALSE;
	}

	if (vr->action_stack.regex_stack->len) {
		GArray *rs = vr->action_stack.regex_stack;
		prev_match_info = g_array_index(rs, liActionRegexStackElement, rs->len - 1).match_info;
	}

	g_string_truncate(dest_path, 0);
	if (NULL != dest_query) g_string_truncate(dest_query, 0);

	li_pattern_eval(vr, dest_path, rule->path, li_pattern_regex_cb, match_info, li_pattern_regex_cb, prev_match_info);
	if (NULL != rule->querystring) {
		LI_FORCE_ASSERT(NULL != dest_query);
		li_pattern_eval(vr, dest_query, rule->querystring, li_pattern_regex_cb, match_info, li_pattern_regex_cb, prev_match_info);
	}

	g_match_info_free(match_info);

	return TRUE;
}

static liHandlerResult rewrite_raw(liVRequest *vr, gpointer param, gpointer *context) {
	guint i;
	rewrite_rule *rule;
	rewrite_data *rd = param;
	gboolean debug = _OPTION(vr, rd->p, 0).boolean;
	gchar *path = vr->request.uri.raw_path->str;
	UNUSED(context);

	for (i = 0; i < rd->rules->len; i++) {
		GString *dest_path = vr->wrk->tmp_str;

		rule = &g_array_index(rd->rules, rewrite_rule, i);

		if (rewrite_internal(vr, dest_path, NULL, rule, path)) {
			/* regex matched */
			if (debug) {
				VR_DEBUG(vr, "rewrite_raw: path \"%s\" => \"%s\"", path, dest_path->str);
			}

			if (!li_parse_raw_path(&vr->request.uri, dest_path)) return LI_HANDLER_ERROR;

			/* stop at first matching regex */
			break;
		}
	}

	return LI_HANDLER_GO_ON;
}



static liHandlerResult rewrite(liVRequest *vr, gpointer param, gpointer *context) {
	guint i;
	rewrite_rule *rule;
	rewrite_data *rd = param;
	gboolean debug = _OPTION(vr, rd->p, 0).boolean;
	GString *dest_query = g_string_sized_new(31);
	gchar *path = vr->request.uri.path->str;
	UNUSED(context);

	for (i = 0; i < rd->rules->len; i++) {
		GString *dest_path = vr->wrk->tmp_str;

		rule = &g_array_index(rd->rules, rewrite_rule, i);

		if (rewrite_internal(vr, dest_path, dest_query, rule, path)) {
			/* regex matched */
			if (debug) {
				if (NULL != rule->querystring) {
					VR_DEBUG(vr, "rewrite: path \"%s\" => \"%s\", query \"%s\" => \"%s\"",
						path, dest_path->str,
						vr->request.uri.query->str, dest_query->str
					);
				} else {
					VR_DEBUG(vr, "rewrite: path \"%s\" => \"%s\"",
						path, dest_path->str
					);
				}
			}

			/* change request query */
			if (NULL != rule->querystring) {
				g_string_truncate(vr->request.uri.query, 0);
				g_string_append_len(vr->request.uri.query, GSTR_LEN(dest_query));
			}

			/* change request path */
			g_string_truncate(vr->request.uri.path, 0);
			g_string_append_len(vr->request.uri.path, GSTR_LEN(dest_path));
			li_path_simplify(vr->request.uri.path);

			/* rebuild raw_path */
			li_string_encode(vr->request.uri.path->str, vr->request.uri.raw_path, LI_ENCODING_URI);
			if (vr->request.uri.query->len > 0) {
				g_string_append_len(vr->request.uri.raw_path, CONST_STR_LEN("?"));
				g_string_append_len(vr->request.uri.raw_path, GSTR_LEN(vr->request.uri.query));
			}

			/* stop at first matching regex */
			break;
		}
	}

	g_string_free(dest_query, TRUE);
	return LI_HANDLER_GO_ON;
}

static void rewrite_free(liServer *srv, gpointer param) {
	guint i;
	rewrite_data *rd = param;

	UNUSED(srv);

	for (i = 0; i < rd->rules->len; i++) {
		rewrite_rule *rule = &g_array_index(rd->rules, rewrite_rule, i);

		li_pattern_free(rule->path);
		li_pattern_free(rule->querystring);

		if (rule->regex) {
			g_regex_unref(rule->regex);
		}
	}

	g_array_free(rd->rules, TRUE);
	g_slice_free(rewrite_data, rd);
}

static liAction* rewrite_create(liServer *srv, liWorker *wrk, liPlugin* p, liValue *val, gpointer userdata) {
	rewrite_data *rd;
	gboolean raw = GPOINTER_TO_INT(userdata);
	UNUSED(wrk);

	val = li_value_get_single_argument(val);

	if (LI_VALUE_STRING != li_value_type(val) && LI_VALUE_LIST != li_value_type(val)) {
		ERROR(srv, "%s", "rewrite expects a either a string, a tuple of strings or a list of string tuples");
		return NULL;
	}

	rd = g_slice_new(rewrite_data);
	rd->p = p;
	rd->rules = g_array_new(FALSE, FALSE, sizeof(rewrite_rule));

	if (LI_VALUE_STRING == li_value_type(val)) {
		/* rewrite "/foo/bar"; */
		rewrite_rule rule = { NULL, NULL, NULL };

		if (!rewrite_rule_parse(srv, NULL, val->data.string, &rule, raw)) {
			rewrite_free(NULL, rd);
			ERROR(srv, "rewrite: error parsing rule \"%s\"", val->data.string->str);
			return NULL;
		}

		g_array_append_val(rd->rules, rule);
	} else if (li_value_list_has_len(val, 2) && LI_VALUE_STRING == li_value_list_type_at(val, 0) && LI_VALUE_STRING == li_value_list_type_at(val, 1)) {
		/* only one rule */
		rewrite_rule rule = { NULL, NULL, NULL };

		if (!rewrite_rule_parse(srv, li_value_list_at(val, 0)->data.string, li_value_list_at(val, 1)->data.string, &rule, raw)) {
			rewrite_free(NULL, rd);
			return NULL;
		}

		g_array_append_val(rd->rules, rule);
	} else {
		/* probably multiple rules */
		LI_VALUE_FOREACH(v, val)
			rewrite_rule rule = { NULL, NULL, NULL };

			if (!li_value_list_has_len(v, 2)
					|| LI_VALUE_STRING != li_value_list_type_at(v, 0) || LI_VALUE_STRING != li_value_list_type_at(v, 1)) {
				rewrite_free(NULL, rd);
				ERROR(srv, "%s", "rewrite expects a either a tuple of strings or a list of those");
				return NULL;
			}

			if (!rewrite_rule_parse(srv, li_value_list_at(v, 0)->data.string, li_value_list_at(v, 1)->data.string, &rule, raw)) {
				rewrite_free(NULL, rd);
				return NULL;
			}

			g_array_append_val(rd->rules, rule);
		LI_VALUE_END_FOREACH()
	}

	return li_action_new_function(raw ? rewrite_raw : rewrite, NULL, rewrite_free, rd);
}



static const liPluginOption options[] = {
	{ "rewrite.debug", LI_VALUE_BOOLEAN, FALSE, NULL },

	{ NULL, 0, 0, NULL }
};

static const liPluginAction actions[] = {
	{ "rewrite", rewrite_create, GINT_TO_POINTER(FALSE) },
	{ "rewrite_raw", rewrite_create, GINT_TO_POINTER(TRUE) },

	{ NULL, NULL, NULL }
};

static const liPluginSetup setups[] = {
	{ NULL, NULL, NULL }
};


static void plugin_rewrite_init(liServer *srv, liPlugin *p, gpointer userdata) {
	UNUSED(srv); UNUSED(userdata);

	p->options = options;
	p->actions = actions;
	p->setups = setups;
}


gboolean mod_rewrite_init(liModules *mods, liModule *mod) {
	UNUSED(mod);

	MODULE_VERSION_CHECK(mods);

	mod->config = li_plugin_register(mods->main, "mod_rewrite", plugin_rewrite_init, NULL);

	return mod->config != NULL;
}

gboolean mod_rewrite_free(liModules *mods, liModule *mod) {
	if (mod->config)
		li_plugin_free(mods->main, mod->config);

	return TRUE;
}
