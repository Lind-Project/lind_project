/* Test of log2*() function family.
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

  /* Negative arguments.  */
  ASSERT (ISNAN (LOG2 (- L_(0.00001))));
  ASSERT (ISNAN (LOG2 (- L_(1.0))));
  ASSERT (ISNAN (LOG2 (- L_(1000000.0))));
  ASSERT (ISNAN (LOG2 (- INFINITY)));

  /* NaN.  */
  ASSERT (ISNAN (LOG2 (NAN)));

  /* Only rational value.  */
  {
    DOUBLE z = LOG2 (L_(1.0));
    ASSERT (z == L_(0.0));
    ASSERT (!signbit (z));
  }

  /* Infinity.  */
  ASSERT (LOG2 (INFINITY) == INFINITY);
}
