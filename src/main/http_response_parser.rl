
#include <lighttpd/base.h>
#include <lighttpd/http_response_parser.h>

/** Machine **/



#define _getString(M, FPC) (li_chunk_extract(ctx->M, LI_GETMARK(FPC), NULL))
#define getString(FPC) _getString(mark, FPC)

#define _getStringTo(M, FPC, s) (li_chunk_extract_to(ctx->M, LI_GETMARK(FPC), s, NULL))
#define getStringTo(FPC, s) _getStringTo(mark, FPC, s)


%%{
	machine li_http_response_parser;
	variable cs ctx->chunk_ctx.cs;

	action mark { ctx->mark = LI_GETMARK(fpc); }
	action done { fbreak; }

	action status {
		getStringTo(fpc, ctx->h_value);
		ctx->response->http_status = atoi(ctx->h_value->str);
		switch (ctx->response->http_status) {
		case 100: /* Continue */
		case 102: /* Processing */
			ctx->drop_header = TRUE;
			break;
			/* don't ignore 101 Switching Protocols */
		default:
			break;
		}
	}

	action header_key {
		getStringTo(fpc, ctx->h_key);
		g_string_truncate(ctx->h_value, 0);
	}
	action header_value {
		guint i;
		/* strip whitespace */
		getStringTo(fpc, ctx->h_value);
		for (i = ctx->h_value->len; i-- > 0; ) {
			switch (ctx->h_value->str[i]) {
			case '\r':
			case '\n':
			case ' ':
				continue;
			}
			break;
		}
		g_string_truncate(ctx->h_value, i+1);
	}
	action header {
		if (ctx->accept_cgi && li_strncase_equal(ctx->h_key, CONST_STR_LEN("Status"))) {
			ctx->response->http_status = atoi(ctx->h_value->str);
		} else if (!ctx->drop_header) {
			li_http_header_insert(ctx->response->headers, GSTR_LEN(ctx->h_key), GSTR_LEN(ctx->h_value));
		}
	}

# RFC 2616
	OCTET = any;
	CHAR = ascii;
	UPALPHA = upper;
	LOALPHA = lower;
	ALPHA = alpha;
	DIGIT = digit;
	CTL = ( 0 .. 31 | 127 );
	CR = '\r';
	LF = '\n';
	SP = ' ';
	HT = '\t';
	DQUOTE = '"';

	# RFC 2616 requires CRLF = CR LF; but many backends only send us LF (especially cgi)
	CRLF = (CR LF | LF);
	LWS = CRLF? (SP | HT)+; # linear white space
	TEXT = (OCTET - CTL) | LWS;
	HEX = [a-fA-F0-9];

	Separators = [()<>@,;:\\\"/\[\]?={}] | SP | HT;
	Token = (OCTET - Separators - CTL)+;

	# original definition
	# Comment = "(" ( CText | Quoted_Pair | Comment )* ")";
	# CText   = TEXT - [()];

	# we don't allow escaping control chars (the RFC does)
	Quoted_Pair    = "\\" (CHAR - CTL);
	Comment        = ( TEXT | Quoted_Pair )*;
	QDText         = TEXT -- (DQUOTE | "\\");
	Quoted_String   = DQUOTE ( QDText | Quoted_Pair )* DQUOTE;

	HTTP_Version = (
		  "HTTP/1.0"  %{ ctx->response->http_version = LI_HTTP_VERSION_1_0; }
		| "HTTP/1.1"  %{ ctx->response->http_version = LI_HTTP_VERSION_1_1; }
		| "HTTP" "/" DIGIT+ "." DIGIT+ ) >{ ctx->response->http_version = LI_HTTP_VERSION_UNSET; };
	#HTTP_URL = "http:" "//" Host ( ":" Port )? ( abs_path ( "?" query )? )?;

	Status = (digit digit digit) >mark %status;
	Response_Line = "HTTP/" digit+ "." digit+ SP Status SP (any - CTL - CR - LF)* CRLF;

	# Field_Content = ( TEXT+ | ( Token | Separators | Quoted_String )+ );
	Field_Content = ( (OCTET - CTL - DQUOTE) | SP | HT | Quoted_String )+;
	Field_Value = (SP | HT)* <: ( ( Field_Content | LWS )* CRLF ) >mark %header_value;
	Message_Header = Token >mark %header_key ":" Field_Value % header;

	main := Response_Line? (Message_Header)* CRLF @ done;
}%%

%% write data;

static int li_http_response_parser_has_error(liHttpResponseCtx *ctx) {
	return ctx->chunk_ctx.cs == li_http_response_parser_error;
}

static int li_http_response_parser_is_finished(liHttpResponseCtx *ctx) {
	return ctx->chunk_ctx.cs >= li_http_response_parser_first_final;
}

void li_http_response_parser_init(liHttpResponseCtx* ctx, liResponse *req, liChunkQueue *cq, gboolean accept_cgi, gboolean accept_nph) {
	li_chunk_parser_init(&ctx->chunk_ctx, cq);
	ctx->response = req;
	ctx->accept_cgi = accept_cgi;
	ctx->accept_nph = accept_nph;
	ctx->drop_header = FALSE;
	ctx->h_key = g_string_sized_new(0);
	ctx->h_value = g_string_sized_new(0);

	(void) li_http_response_parser_en_main;
	%% write init;
}

void li_http_response_parser_reset(liHttpResponseCtx* ctx) {
	li_chunk_parser_reset(&ctx->chunk_ctx);
	g_string_truncate(ctx->h_key, 0);
	g_string_truncate(ctx->h_value, 0);
	ctx->drop_header = FALSE;

	%% write init;
}

void li_http_response_parser_clear(liHttpResponseCtx *ctx) {
	g_string_free(ctx->h_key, TRUE);
	g_string_free(ctx->h_value, TRUE);
}

static gboolean li_http_response_handle_finished(liHttpResponseCtx *ctx) {
	if (!li_http_response_parser_is_finished(ctx)) return FALSE;

	li_chunkqueue_skip(ctx->chunk_ctx.cq, ctx->chunk_ctx.bytes_in);
	if (ctx->drop_header) {
		li_http_response_parser_reset(ctx);
		return FALSE;
	} else {
		if (ctx->response->http_status == 0) ctx->response->http_status = 200;
		return TRUE;
	}
}

liHandlerResult li_http_response_parse(liVRequest *vr, liHttpResponseCtx *ctx) {
	liHandlerResult res;

	if (li_http_response_handle_finished(ctx)) return LI_HANDLER_GO_ON;

	if (LI_HANDLER_GO_ON != (res = li_chunk_parser_prepare(&ctx->chunk_ctx))) return res;

	while (!li_http_response_parser_has_error(ctx)) {
		char *p, *pe;
		GError *err = NULL;

		if (LI_HANDLER_GO_ON != (res = li_chunk_parser_next(&ctx->chunk_ctx, &p, &pe, &err))) {
			if (NULL != err) {
				VR_ERROR(vr, "%s", err->message);
				g_error_free(err);
			}
			return res;
		}

		%% write exec;

		li_chunk_parser_done(&ctx->chunk_ctx, p - ctx->chunk_ctx.buf);

		if (li_http_response_handle_finished(ctx)) return LI_HANDLER_GO_ON;
	}

	return LI_HANDLER_ERROR;
}
