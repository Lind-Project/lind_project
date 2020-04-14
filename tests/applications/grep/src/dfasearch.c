/* dfasearch.c - searching subroutines using dfa and regex for grep.
   Copyright 1992, 1998, 2000, 2007, 2009-2017 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

/* Written August 1992 by Mike Haertel. */

#include <config.h>
#include "intprops.h"
#include "search.h"
#include "die.h"
#include <error.h>

struct dfa_comp
{
  /* KWset compiled pattern.  For Ecompile and Gcompile, we compile
     a list of strings, at least one of which is known to occur in
     any string matching the regexp. */
  kwset_t kwset;

  /* DFA compiled regexp. */
  struct dfa *dfa;

  /* Regex compiled regexps. */
  struct re_pattern_buffer* patterns;
  size_t pcount;
  struct re_registers regs;

  /* Number of compiled fixed strings known to exactly match the regexp.
     If kwsexec returns < kwset_exact_matches, then we don't need to
     call the regexp matcher at all. */
  ptrdiff_t kwset_exact_matches;

  bool begline;
};

void
dfaerror (char const *mesg)
{
  die (EXIT_TROUBLE, 0, "%s", mesg);
}

/* For now, the sole dfawarn-eliciting condition (use of a regexp
   like '[:lower:]') is unequivocally an error, so treat it as such,
   when possible.  */
void
dfawarn (char const *mesg)
{
  if (!getenv ("POSIXLY_CORRECT"))
    dfaerror (mesg);
}

/* If the DFA turns out to have some set of fixed strings one of
   which must occur in the match, then we build a kwset matcher
   to find those strings, and thus quickly filter out impossible
   matches. */
static void
kwsmusts (struct dfa_comp *dc)
{
  struct dfamust *dm = dfamust (dc->dfa);
  if (!dm)
    return;
  dc->kwset = kwsinit (false);
  if (dm->exact)
    {
      /* Prepare a substring whose presence implies a match.
         The kwset matcher will return the index of the matching
         string that it chooses. */
      ++dc->kwset_exact_matches;
      ptrdiff_t old_len = strlen (dm->must);
      ptrdiff_t new_len = old_len + dm->begline + dm->endline;
      char *must = xmalloc (new_len);
      char *mp = must;
      *mp = eolbyte;
      mp += dm->begline;
      dc->begline |= dm->begline;
      memcpy (mp, dm->must, old_len);
      if (dm->endline)
        mp[old_len] = eolbyte;
      kwsincr (dc->kwset, must, new_len);
      free (must);
    }
  else
    {
      /* Otherwise, filtering with this substring should help reduce the
         search space, but we'll still have to use the regexp matcher.  */
      kwsincr (dc->kwset, dm->must, strlen (dm->must));
    }
  kwsprep (dc->kwset);
  dfamustfree (dm);
}

void *
GEAcompile (char *pattern, size_t size, reg_syntax_t syntax_bits)
{
  char *motif;
  struct dfa_comp *dc = xcalloc (1, sizeof (*dc));

  dc->dfa = dfaalloc ();

  if (match_icase)
    syntax_bits |= RE_ICASE;
  re_set_syntax (syntax_bits);
  int dfaopts = eolbyte ? 0 : DFA_EOL_NUL;
  dfasyntax (dc->dfa, &localeinfo, syntax_bits, dfaopts);

  /* For GNU regex, pass the patterns separately to detect errors like
     "[\nallo\n]\n", where the patterns are "[", "allo" and "]", and
     this should be a syntax error.  The same for backref, where the
     backref should be local to each pattern.  */
  char const *p = pattern;
  char const *patlim = pattern + size;
  bool compilation_failed = false;
  size_t palloc = 0;

  do
    {
      size_t len;
      char const *sep = memchr (p, '\n', patlim - p);
      if (sep)
        {
          len = sep - p;
          sep++;
        }
      else
        len = patlim - p;

      if (palloc <= dc->pcount)
        dc->patterns = x2nrealloc (dc->patterns, &palloc, sizeof *dc->patterns);
      struct re_pattern_buffer *pat = &dc->patterns[dc->pcount];
      pat->buffer = NULL;
      pat->allocated = 0;

      /* Do not use a fastmap with -i, to work around glibc Bug#20381.  */
      pat->fastmap = match_icase ? NULL : xmalloc (UCHAR_MAX + 1);

      pat->translate = NULL;

      char const *err = re_compile_pattern (p, len, pat);
      if (err)
        {
          /* With patterns specified only on the command line, emit the bare
             diagnostic.  Otherwise, include a filename:lineno: prefix.  */
          size_t lineno;
          char const *pat_filename = pattern_file_name (dc->pcount + 1,
                                                        &lineno);
          if (*pat_filename == '\0')
            error (0, 0, "%s", err);
          else
            error (0, 0, "%s:%zu: %s", pat_filename, lineno, err);
          compilation_failed = true;
        }
      dc->pcount++;
      p = sep;
    }
  while (p);

  if (compilation_failed)
    exit (EXIT_TROUBLE);

  /* In the match_words and match_lines cases, we use a different pattern
     for the DFA matcher that will quickly throw out cases that won't work.
     Then if DFA succeeds we do some hairy stuff using the regex matcher
     to decide whether the match should really count. */
  if (match_words || match_lines)
    {
      static char const line_beg_no_bk[] = "^(";
      static char const line_end_no_bk[] = ")$";
      static char const word_beg_no_bk[] = "(^|[^[:alnum:]_])(";
      static char const word_end_no_bk[] = ")([^[:alnum:]_]|$)";
      static char const line_beg_bk[] = "^\\(";
      static char const line_end_bk[] = "\\)$";
      static char const word_beg_bk[] = "\\(^\\|[^[:alnum:]_]\\)\\(";
      static char const word_end_bk[] = "\\)\\([^[:alnum:]_]\\|$\\)";
      int bk = !(syntax_bits & RE_NO_BK_PARENS);
      char *n = xmalloc (sizeof word_beg_bk - 1 + size + sizeof word_end_bk);

      strcpy (n, match_lines ? (bk ? line_beg_bk : line_beg_no_bk)
                             : (bk ? word_beg_bk : word_beg_no_bk));
      size_t total = strlen (n);
      memcpy (n + total, pattern, size);
      total += size;
      strcpy (n + total, match_lines ? (bk ? line_end_bk : line_end_no_bk)
                                     : (bk ? word_end_bk : word_end_no_bk));
      total += strlen (n + total);
      pattern = motif = n;
      size = total;
    }
  else
    motif = NULL;

  dfacomp (pattern, size, dc->dfa, 1);
  kwsmusts (dc);

  free (motif);

  return dc;
}

size_t
EGexecute (void *vdc, char const *buf, size_t size, size_t *match_size,
           char const *start_ptr)
{
  char const *buflim, *beg, *end, *ptr, *match, *best_match, *mb_start;
  char eol = eolbyte;
  regoff_t start;
  size_t len, best_len;
  struct kwsmatch kwsm;
  size_t i;
  struct dfa_comp *dc = vdc;
  struct dfa *superset = dfasuperset (dc->dfa);
  bool dfafast = dfaisfast (dc->dfa);

  mb_start = buf;
  buflim = buf + size;

  for (beg = end = buf; end < buflim; beg = end)
    {
      end = buflim;

      if (!start_ptr)
        {
          char const *next_beg, *dfa_beg = beg;
          size_t count = 0;
          bool exact_kwset_match = false;
          bool backref = false;

          /* Try matching with KWset, if it's defined.  */
          if (dc->kwset)
            {
              char const *prev_beg;

              /* Find a possible match using the KWset matcher.  */
              ptrdiff_t offset = kwsexec (dc->kwset, beg - dc->begline,
                                          buflim - beg + dc->begline,
                                          &kwsm, true);
              if (offset < 0)
                goto failure;
              match = beg + offset;
              prev_beg = beg;

              /* Narrow down to the line containing the possible match.  */
              beg = memrchr (buf, eol, match - buf);
              beg = beg ? beg + 1 : buf;
              dfa_beg = beg;

              /* Determine the end pointer to give the DFA next.  Typically
                 this is after the first newline after MATCH; but if the KWset
                 match is not exact, the DFA is fast, and the offset from
                 PREV_BEG is less than 64 or (MATCH - PREV_BEG), this is the
                 greater of the latter two values; this temporarily prefers
                 the DFA to KWset.  */
              exact_kwset_match = kwsm.index < dc->kwset_exact_matches;
              end = ((exact_kwset_match || !dfafast
                      || MAX (16, match - beg) < (match - prev_beg) >> 2)
                     ? match
                     : MAX (16, match - beg) < (buflim - prev_beg) >> 2
                     ? prev_beg + 4 * MAX (16, match - beg)
                     : buflim);
              end = memchr (end, eol, buflim - end);
              end = end ? end + 1 : buflim;

              if (exact_kwset_match)
                {
                  if (!localeinfo.multibyte | localeinfo.using_utf8)
                    goto success;
                  if (mb_start < beg)
                    mb_start = beg;
                  if (mb_goback (&mb_start, match, buflim) == 0)
                    goto success;
                  /* The matched line starts in the middle of a multibyte
                     character.  Perform the DFA search starting from the
                     beginning of the next character.  */
                  dfa_beg = mb_start;
                }
            }

          /* Try matching with the superset of DFA, if it's defined.  */
          if (superset && !exact_kwset_match)
            {
              /* Keep using the superset while it reports multiline
                 potential matches; this is more likely to be fast
                 than falling back to KWset would be.  */
              next_beg = dfaexec (superset, dfa_beg, (char *) end, 0,
                                  &count, NULL);
              if (next_beg == NULL || next_beg == end)
                continue;

              /* Narrow down to the line we've found.  */
              if (count != 0)
                {
                  beg = memrchr (buf, eol, next_beg - buf);
                  beg++;
                  dfa_beg = beg;
                }
              end = memchr (next_beg, eol, buflim - next_beg);
              end = end ? end + 1 : buflim;

              count = 0;
            }

          /* Try matching with DFA.  */
          next_beg = dfaexec (dc->dfa, dfa_beg, (char *) end, 0, &count,
                              &backref);

          /* If there's no match, or if we've matched the sentinel,
             we're done.  */
          if (next_beg == NULL || next_beg == end)
            continue;

          /* Narrow down to the line we've found.  */
          if (count != 0)
            {
              beg = memrchr (buf, eol, next_beg - buf);
              beg++;
            }
          end = memchr (next_beg, eol, buflim - next_beg);
          end = end ? end + 1 : buflim;

          /* Successful, no backreferences encountered! */
          if (!backref)
            goto success;
          ptr = beg;
        }
      else
        {
          /* We are looking for the leftmost (then longest) exact match.
             We will go through the outer loop only once.  */
          ptr = start_ptr;
        }

      /* If the "line" is longer than the maximum regexp offset,
         die as if we've run out of memory.  */
      if (TYPE_MAXIMUM (regoff_t) < end - beg - 1)
        xalloc_die ();

      /* Run the possible match through Regex.  */
      best_match = end;
      best_len = 0;
      for (i = 0; i < dc->pcount; i++)
        {
          dc->patterns[i].not_eol = 0;
          dc->patterns[i].newline_anchor = eolbyte == '\n';
          start = re_search (&dc->patterns[i], beg, end - beg - 1,
                             ptr - beg, end - ptr - 1, &dc->regs);
          if (start < -1)
            xalloc_die ();
          else if (0 <= start)
            {
              len = dc->regs.end[0] - start;
              match = beg + start;
              if (match > best_match)
                continue;
              if (start_ptr && !match_words)
                goto assess_pattern_match;
              if ((!match_lines && !match_words)
                  || (match_lines && len == end - ptr - 1))
                {
                  match = ptr;
                  len = end - ptr;
                  goto assess_pattern_match;
                }
              /* If -w and not -x, check whether the match aligns with
                 word boundaries.  Do this iteratively because:
                 (a) the line may contain more than one occurrence of the
                 pattern, and
                 (b) Several alternatives in the pattern might be valid at a
                 given point, and we may need to consider a shorter one to
                 find a word boundary.  */
              if (!match_lines && match_words)
                while (match <= best_match)
                  {
                    regoff_t shorter_len = 0;
                    if (! wordchar_next (match + len, end - 1)
                        && ! wordchar_prev (beg, match, end - 1))
                      goto assess_pattern_match;
                    if (len > 0)
                      {
                        /* Try a shorter length anchored at the same place. */
                        --len;
                        dc->patterns[i].not_eol = 1;
                        shorter_len = re_match (&dc->patterns[i], beg,
                                                match + len - ptr, match - beg,
                                                &dc->regs);
                        if (shorter_len < -1)
                          xalloc_die ();
                      }
                    if (0 < shorter_len)
                      len = shorter_len;
                    else
                      {
                        /* Try looking further on. */
                        if (match == end - 1)
                          break;
                        match++;
                        dc->patterns[i].not_eol = 0;
                        start = re_search (&dc->patterns[i], beg, end - beg - 1,
                                           match - beg, end - match - 1,
                                           &dc->regs);
                        if (start < 0)
                          {
                            if (start < -1)
                              xalloc_die ();
                            break;
                          }
                        len = dc->regs.end[0] - start;
                        match = beg + start;
                      }
                  } /* while (match <= best_match) */
              continue;
            assess_pattern_match:
              if (!start_ptr)
                {
                  /* Good enough for a non-exact match.
                     No need to look at further patterns, if any.  */
                  goto success;
                }
              if (match < best_match || (match == best_match && len > best_len))
                {
                  /* Best exact match:  leftmost, then longest.  */
                  best_match = match;
                  best_len = len;
                }
            } /* if re_search >= 0 */
        } /* for Regex patterns.  */
        if (best_match < end)
          {
            /* We have found an exact match.  We were just
               waiting for the best one (leftmost then longest).  */
            beg = best_match;
            len = best_len;
            goto success_in_len;
          }
    } /* for (beg = end ..) */

 failure:
  return -1;

 success:
  len = end - beg;
 success_in_len:;
  size_t off = beg - buf;
  *match_size = len;
  return off;
}
