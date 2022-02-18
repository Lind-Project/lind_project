/*
 * Routines to get randomness.
 */
#include <syslog.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include "arch.h"
#include "pids.h"
#include "random.h"
#include "sanitise.h"	// interesting_numbers
#include "types.h"
#include "utils.h"

void generate_rand_bytes(unsigned char *ptr, unsigned int len)
{
	unsigned int i;
	unsigned int startoffset = 0, remain;
	unsigned char separators[] = { ':', ',', '.', ' ', '-', '\0', };
	unsigned char separator;

	switch (rand() % 3) {
	case 0:
		/* Complete garbage. */
		for (i = 0; i < len; i++)
			ptr[i] = RAND_BYTE();
		break;
	case 1:
		/* printable text strings. */
		for (i = 0; i < len; i++)
			ptr[i] = 32 + rand() % (0x7f - 32);
		break;
	case 2:
		/* numbers (for now, decimal only) */

		separator = separators[rand() % sizeof(separators)];

		remain = len;

		while (remain > 0) {
			unsigned int runlen;

			/* Sometimes make the numbers be negative. */
			if (RAND_BOOL()) {
				ptr[startoffset++] = '-';
				remain--;
				if (remain == 0)
					break;
			}

			/* At most make this run 10 chars. */
			runlen = min(remain, (unsigned int) rand() % 10);

			for (i = startoffset; i < startoffset + runlen; i++)
				ptr[i] = '0' + rand() % 10;

			startoffset += runlen;
			remain -= runlen;

			/* insert commas and/or spaces */
			if (remain > 0) {
				ptr[i++] = separator;
				startoffset++;
				remain--;
			}
		}
		break;
	}
}

/*
 * OR a random number of bits into a mask.
 * Used by ARG_LIST generation, and get_o_flags()
 */
unsigned long set_rand_bitmask(unsigned int num, const unsigned long *values)
{
	unsigned long i;
	unsigned long mask = 0;
	unsigned int bits;

	bits = RAND_RANGE(0, num);      /* num of bits to OR */
	if (bits == 0)
		return mask;

	for (i = 0; i < bits; i++)
		mask |= values[rand() % num];

	return mask;
}

/*
 * Pick a random power of two between 2^0 and 2^(__WORDSIZE-1)
 */
unsigned long rand_single_bit(unsigned char size)
{
	if (size > __WORDSIZE)
		size = __WORDSIZE;

	return (1UL << (rand() % size));
}

/*
 * set N bits, where N= rand(0 - WORDSIZE/2)
 */
static unsigned long randbits(int limit)
{
	unsigned int num = rand() % (limit / 2);
	unsigned int i;
	unsigned long r = 0;

	for (i = 0; i < num; i++)
		r |= (1UL << (rand() % (limit - 1)));

	return r;
}

/*
 * Pick 1 random byte, and repeat it through a long.
 */
static unsigned long rept_byte(void)
{
	unsigned long r = RAND_BYTE();

	r = (r << 8) | r;
	r = (r << 16) | r;
#if __WORDSIZE == 64
	r = (r << 32) | r;
#endif
	return r;
}

/*
 * Generate, and munge a 32bit number.
 */
unsigned int rand32(void)
{
	unsigned long r = 0;

	switch (rand() % 5) {
	case 0: r = rand_single_bit(32);
		break;
	case 1:	r = randbits(32);
		break;
	case 2: r = RAND_32();
		break;
	case 3:	r = rept_byte();
		break;
	case 4:	return get_interesting_value();
	}

	/* Sometimes deduct it from INT_MAX */
	if (ONE_IN(25))
		r = INT_MAX - r;

	/* Sometimes flip sign */
	if (ONE_IN(25))
		r = ~r + 1;

	/* we might get lucky if something is counting ints/longs etc. */
	if (ONE_IN(4)) {
		int _div = 1 << RAND_RANGE(1, 4);	/* 2,4,8 or 16 */
		r /= _div;
	}

	/* limit the size */
	switch (rand() % 5) {
	case 0: r &= 0xff;
		break;
	case 1: r &= 0xffff;
		break;
	case 2: r &= PAGE_MASK;
		break;
	case 3: r &= 0xffffff;
		break;
	case 4:	// do nothing
		break;
	}

	return r;
}

/*
 * Generate and munge a 64bit number.
 */
u64 rand64(void)
{
	unsigned long r = 0;

	if (RAND_BOOL()) {
		/* 32-bit ranges. */
		r = rand32();

	} else {
		/* 33:64-bit ranges. */
		switch (rand() % 5) {
		case 0:	r = rand_single_bit(64);
			break;
		case 1:	r = randbits(64);
			break;
		case 2:	r = RAND_64();
			break;
		case 3:	r = rept_byte();
			break;
		/* Sometimes pick a not-so-random number. */
		case 4:	return get_interesting_value();
		}

		/* limit the size */
		switch (rand() % 4) {
		case 0: r &= 0x000000ffffffffffULL;
			break;
		case 1: r &= 0x0000ffffffffffffULL;
			break;
		case 2: r &= 0x00ffffffffffffffULL;
			break;
		default: /* no limiting. */
			break;
		}
	}

	/* Sometimes invert the generated number. */
	if (ONE_IN(25))
		r = ~r;

	/* increase distribution in MSB */
	if (ONE_IN(10)) {
		unsigned int i;
		unsigned int rounds;

		rounds = rand() % 4;
		for (i = 0; i < rounds; i++)
			r |= (1UL << ((__WORDSIZE - 1) - (rand() % 8)));
	}

	/* Sometimes flip sign */
	if (ONE_IN(25))
		r = ~r + 1;

	return r;
}
