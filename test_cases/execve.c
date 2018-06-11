#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

extern char **environ;

int main(void)
{
	char *args[] = {"/bin/echo", "hi", 0};

	printf("%d\n", getpid());
	puts("executing /bin/echo");
	execve(args[0], args, environ);

	return 0;
}
