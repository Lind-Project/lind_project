#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char file_name[100] = "testfiles/chmodfile.txt";
	if(chmod(file_name, S_IRUSR | S_IXUSR) != 0) //change from 700 to 500
	{
		perror("ERROR with CHMOD");
		exit(1);
	}
	struct stat st;
	if (stat(file_name, &st) == -1) //get mode of file using stat()
	{
		perror("ERROR WITH STAT");
		exit(1);
	}
	mode_t file_per = ((S_IRWXU | S_IRWXG | S_IRWXO) & st.st_mode); //isolate file permissions
	if ((file_per & (S_IRUSR | S_IXUSR)) != file_per)
	{
		fprintf(stderr, "Expected %s to have access mode 500 but was %03o\n", file_name, (unsigned int) file_per);
		exit(1);
	}
	if(chmod(file_name, S_IRWXU) != 0) //change file permissions back to original
	{
		perror("COULD NOT CHANGE MODE BACK TO 700");
		exit(1);
	}
	if(stat(file_name, &st) == -1)
	{
		perror("ERROR WITH SECOND STAT CALL");
		exit(1);
	}
	file_per = ((S_IRWXU | S_IRWXG | S_IRWXO) & st.st_mode);
	if((file_per & S_IRWXU) != file_per)
	{
		fprintf(stderr, "Expected %s to have access mode 700 but was %03o\n", file_name, (unsigned int) file_per);
		exit(1);
	}
	printf("Mode changed successfully\n");	
	fflush(stdout);
	return (0);
}

