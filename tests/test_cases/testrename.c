#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
	char old_name[] = "testfiles/renmefile.txt";
	char new_name[] = "testfiles/renamed_testfile.txt";
    
    int ret = rename(old_name, new_name);
    if(ret < 0) {
        printf("ERROR: %d\n", errno);
        perror("send");
        fflush(NULL);
        printf("Return: %d\n", ret);
        exit(1);
    }
	
	printf("SUCCESS WITH RENAMING\n");
	fflush(stdout);
	return 0;
}
