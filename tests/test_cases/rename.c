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
	char old_name[] = "testfiles/renamefile.txt";
	char new_name[] = "testfiles/renamed_testfile.txt";
	struct stat st;
	if(stat(old_name, &st) == -1)
	{
		perror("ERROR WITH STAT CALL ON OLD NAME");
		exit(1);
	}
	if(rename(old_name, new_name) != 0)
	{
		perror("ERROR WITH RENAME");
		exit(1);
	}
	struct stat st2;
	if(stat(new_name, &st2) == -1)
	{
		perror("ERROR WITH STAT CALL ON NEW NAME");
		exit(1);
	}
	if(st2.st_ino != st.st_ino)
	{
		perror("ERROR: INODE NOT EQUAL");
		exit(1);
	}
	if(rename(new_name, old_name) != 0)
	{
		perror("ERROR WITH CHANGING NAME BACK");
		exit(1);
	}
	printf("SUCCESS WITH RENAMING\n");
	fflush(stdout);
	return 0;
}
