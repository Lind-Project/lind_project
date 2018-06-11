#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	char str[] = "write succeeded\n";

	puts("\nattempting to write to STDOUT_FILENO\n");
	/* fflush(0); */
	write(STDOUT_FILENO, str, sizeof str);
	/* fflush(0); */

	return 0;
}
