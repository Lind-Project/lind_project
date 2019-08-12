/* Copy wide character array.
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

wchar_t *
wmemmove (wchar_t *dest, const wchar_t *src, size_t n)
{
  if (dest < src)
    {
      wchar_t *destptr = dest;
      const wchar_t *srcptr = src;
      for (; n > 0; n--)
        *destptr++ = *srcptr++;
    }
  else if (dest > src)
    {
      wchar_t *destptr = dest + n - 1;
      const wchar_t *srcptr = src + n - 1;
      for (; n > 0; n--)
        *destptr-- = *srcptr--;
    }
  return dest;
}
