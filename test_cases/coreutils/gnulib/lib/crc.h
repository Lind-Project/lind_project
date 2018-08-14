/* crc.h -- cyclic redundancy checks
   Copyright (C) 2005, 2009-2018 Free Software Foundation, Inc.

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

/* Written by Simon Josefsson.  */

#ifndef CRC_H
# define CRC_H 1

#include <stddef.h>
#include <stdint.h>

/* Compute CRC-32 value of LEN bytes long BUF, and return it. */
extern uint32_t crc32 (const char *buf, size_t len);

/* Incrementally update CRC-32 value CRC using LEN bytes long BUF.  In
   the first call, use 0 as the value for CRC.  Return the updated
   CRC-32 value.  */
extern uint32_t crc32_update (uint32_t crc, const char *buf, size_t len);

/* Compute modified-CRC-32 value of LEN bytes long BUF, and return it.
   The "modification" is to avoid the initial and final XOR operation.
   Due to historic implementation errors, this variant is sometimes
   used (i.e., in RFC 3961). */
extern uint32_t crc32_no_xor (const char *buf, size_t len);

/* Incrementally update modified-CRC-32 value CRC using LEN bytes long
   BUF.  In the first call, use 0 as the value for CRC.  Return the
   updated modified-CRC-32 value.  The "modification" is to avoid the
   initial and final XOR operation.  Due to historic implementation
   errors, this variant is sometimes used (i.e., in RFC 3961).  */
extern uint32_t
crc32_update_no_xor (uint32_t crc, const char *buf, size_t len);

#endif /* CRC_H */
