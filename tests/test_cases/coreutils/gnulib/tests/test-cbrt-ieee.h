/* Test of cbrt*() function family.
   Copyright (C) 2012-2018 Free Software Foundation, Inc.

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

static void
test_function (void)
{
  /* [MX] shaded specification in POSIX.  */

  /* NaN.  */
  ASSERT (ISNAN (CBRT (NAN)));

  /* Signed zero.  */
  {
    DOUBLE y = CBRT (L_(0.0));
    ASSERT (y == L_(0.0));
    ASSERT (!signbit (y));
  }
  {
    DOUBLE y = CBRT (MINUS_ZERO);
    ASSERT (y == L_(0.0));
    ASSERT (!!signbit (y) == !!signbit (MINUS_ZERO));
  }

  /* Infinity.  */
  ASSERT (CBRT (INFINITY) == INFINITY);
  ASSERT (CBRT (- INFINITY) == - INFINITY);
}
