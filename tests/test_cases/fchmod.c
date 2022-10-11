#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

const char* FILENAME = "testfiles/fchmodfile.txt";

int main(int argc, char **argv)
{
	int fd = open(FILENAME, O_RDONLY);
	if(fchmod(fd, S_IRUSR | S_IXUSR) != 0) //change from 700 to 500
	{
		perror("ERROR with FCHMOD");
		exit(1);
	}
	struct stat st;
	if (fstat(fd, &st) == -1) //get mode of file using stat()
	{
		perror("ERROR WITH FSTAT");
		exit(1);
	}
	mode_t file_per = ((S_IRWXU | S_IRWXG | S_IRWXO) & st.st_mode); //isolate file permissions
	if ((file_per & (S_IRUSR | S_IXUSR)) != file_per)
	{
		fprintf (stderr, "Expected %s to have access mode 500 but was %03o\n", FILENAME, (unsigned int) file_per);
		exit(1);
	}
	if(fchmod(fd, S_IRWXU) != 0) //change file permissions back to original
	{
		perror("COULD NOT CHANGE MODE BACK TO 700");
		exit(1);
	}
	if(fstat(fd, &st) == -1)
	{
		perror("ERROR WITH SECOND FSTAT CALL");
		exit(1);
	}
	file_per = ((S_IRWXU | S_IRWXG | S_IRWXO) & st.st_mode);
	if((file_per & S_IRWXU) != file_per)
	{
		fprintf(stderr, "Expected %s to have access mode 700 but was %03o\n", FILENAME, (unsigned int) file_per);
		exit(1);
	}
	fprintf(stdout, "Mode changed successfully\n");	
	fflush(stdout);
	return (0);
}

