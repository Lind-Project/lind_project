/* Formatted output to strings.
   Copyright (C) 1999, 2002, 2006-2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

int
VSNPRINTF (DCHAR_T *buf, size_t size, const FCHAR_T *format, va_list args)
{
  size_t length;
  DCHAR_T *result;

  if (size == 0)
    buf = NULL;
  else
    length = size;
  result = VASNPRINTF (buf, &length, format, args);
  if (result == NULL)
    return -1;

  if (result != buf)
    {
      if (size != 0)
        {
          /* The result did not fit into the buffer.  Copy the initial segment
             into the buffer, truncating it if necessary.  */
          size_t n = (length < size ? length : size - 1);
          DCHAR_CPY (buf, result, n);
          buf[n] = '\0';
        }
      free (result);
    }

  if (length > INT_MAX)
    {
      errno = EOVERFLOW;
      return -1;
    }

  /* Return the number of resulting units, excluding the trailing NUL.  */
  return length;
}
