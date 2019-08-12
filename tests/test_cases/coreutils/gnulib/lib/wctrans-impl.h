/* Get descriptor for a wide character case conversion.
   Copyright (C) 2011-2018 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2011.

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

wctrans_t
wctrans (const char *name)
{
  if (name[0] == 't'
      && name[1] == 'o')
    switch (name[2])
      {
      case 'l':
        if (strcmp (name + 3, "ower") == 0)
          return (wctrans_t) towlower;
        break;
      case 'u':
        if (strcmp (name + 3, "pper") == 0)
          return (wctrans_t) towupper;
        break;
      default:
        break;
      }
  return NULL;
}
