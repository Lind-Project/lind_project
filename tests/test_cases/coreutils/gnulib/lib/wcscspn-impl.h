/* Search a wide string for any of a set of wide characters.
   Copyright (C) 1999, 2011-2018 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 1999.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

size_t
wcscspn (const wchar_t *wcs, const wchar_t *reject)
{
  /* Optimize two cases.  */
  if (reject[0] == (wchar_t)'\0')
    return wcslen (wcs);

  if (reject[1] == (wchar_t)'\0')
    {
      wchar_t wc = reject[0];
      const wchar_t *ptr = wcs;
      for (; *ptr != (wchar_t)'\0'; ptr++)
        {
          if (*ptr == wc)
            break;
        }
      return ptr - wcs;
    }

  /* General case.  */
  {
    const wchar_t *ptr = wcs;
    for (; *ptr != (wchar_t)'\0'; ptr++)
      {
        if (wcschr (reject, *ptr))
          break;
      }
    return ptr - wcs;
  }
}
