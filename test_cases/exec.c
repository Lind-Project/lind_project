#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(void)
{
	char *args[] = {"/hello", 0};

	printf("environ = [%p]\n", (void *)environ);
	printf("executing: %s", args[0]);
	for (size_t i = 1; args[i]; i++) {
		putchar(' ');
		printf("%s", args[i]);
	}
	putchar('\n');

	/* execv(args[0], args); */
	execve(args[0], args, environ);

	return 0;
}
