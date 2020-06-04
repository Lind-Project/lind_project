#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int fd;
	char *p;
	char const str[] = "hello pototo";

	puts("main()");

	if ((fd = open("/dev/zero",  O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1)
		perror("open()");

	//getchar();
	puts("open()");

	if ((p = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
		perror("mmap()");

	memcpy(p, str, sizeof str);
	puts(p);
	//getchar();
	puts("mmap()");

	if (mprotect(p, 4096, PROT_READ|PROT_EXEC))
		perror("mprotect()");

	puts(p);
	puts("mprotect()");
	//getchar();

	if (munmap(p, 4096))
		perror("munmap()");

	puts("munmap()");
	//getchar();

	if (close(fd) == -1)
		perror("close()");

	puts("close()");
	//getchar();

	return 0;
}
