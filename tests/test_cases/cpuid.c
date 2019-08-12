#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdint.h>
#include <stdio.h>

int main(void) {
	volatile uint32_t reg[4];

	__asm__ volatile ( "cpuid" : "=a"(reg[3]), "=b"(reg[0]), "=c"(reg[2]), "=d"(reg[1]) : "a"(0) : "cc");
	puts((char *)reg);

	return 0;
}
