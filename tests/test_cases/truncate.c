#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

const char *FILENAME = "testfile.txt";
const off_t OFFSET = 123;

void check_filesize(off_t target_size)
{
	struct stat st;
	stat(FILENAME, &st);
	if (st.st_size != target_size)
	{
		fprintf(
			stderr,
			"ERROR: EXPECT FILESIZE TO BE %d BUT GOT %d\n",
			target_size,
			st.st_size
		);
		exit(1);
	}
	printf("Success\n");
}

void check_success(int r)
{
	if (r == -1)
	{
		perror("ERROR WHEN TRUNCATING FILE");
		exit(1);
	}
}


int main(int argc, char **argv)
{
	int fd;

	struct stat st;
	stat(FILENAME, &st);
	off_t filesize = st.st_size;
	off_t filesize_inc = filesize + OFFSET;
	

	printf("Test truncate(const char *, off_t)\n");

	printf("Truncating %s from %d to %d\n", FILENAME, filesize, filesize_inc); 
	check_success(truncate(FILENAME, filesize_inc));
	check_filesize(filesize_inc);

	printf("Truncating %s from %d to %d\n", FILENAME, filesize_inc, filesize);
	check_success(truncate(FILENAME, filesize));
	check_filesize(filesize);


	printf("Test ftruncate(int, off_t)\n");
	fd = open(FILENAME, O_WRONLY);

	printf("Truncating %s from %d to %d\n", FILENAME, filesize, filesize_inc); 
	check_success(ftruncate(fd, filesize_inc));
	check_filesize(filesize_inc);

	printf("Truncating %s from %d to %d\n", FILENAME, filesize_inc, filesize); 
	check_success(ftruncate(fd, filesize));
	check_filesize(filesize);

	close(fd);

	return 0;
}
