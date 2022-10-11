#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

extern char **environ;

const char* FILENAME = "testfiles/fstatfile.txt";

int main(int argc, char **argv)
{
	FILE *fp = stdout;
	int fd;

	/*
	* struct stat {
	*         dev_t     st_dev;         [> ID of device containing file <]
	*         ino_t     st_ino;         [> Inode number <]
	*         mode_t    st_mode;        [> File type and mode <]
	*         nlink_t   st_nlink;       [> Number of hard links <]
	*         uid_t     st_uid;         [> User ID of owner <]
	*         gid_t     st_gid;         [> Group ID of owner <]
	*         dev_t     st_rdev;        [> Device ID (if special file) <]
	*         off_t     st_size;        [> Total size, in bytes <]
	*         blksize_t st_blksize;     [> Block size for filesystem I/O <]
	*         blkcnt_t  st_blocks;      [> Number of 512B blocks allocated <]
	*
	*         [> Since Linux 2.6, the kernel supports nanosecond
	*           precision for the following timestamp fields.
	*           For the details before Linux 2.6, see NOTES. <]
	*
	*         struct timespec st_atim;  [> Time of last access <]
	*         struct timespec st_mtim;  [> Time of last modification <]
	*         struct timespec st_ctim;  [> Time of last status change <]
	*
	* #define st_atime st_atim.tv_sec      [> Backward compatibility <]
	* #define st_mtime st_mtim.tv_sec
	* #define st_ctime st_ctim.tv_sec
	* };
	*/

	if (argc < 2) {
		struct stat st = {0};
		//printf("usage: %s <files>\n", argv[0]); //-causes a silly error on dettest - 
		//usage: /automated_tests/fstat.NEXE <files> and usage: ./automated_tests/fstat <files> do not match.
		printf("running fstat(\"%s\")\n", FILENAME); //argv[0] to specify any file
		fd = open(FILENAME, O_RDONLY);
		if (fstat(fd, &st) < 0) {
			perror("fstat");
			printf("errno: %d\n", errno);
			exit(1);
		}
		printf("size: %jd\n", st.st_size);
		exit(0);
	}

	// The files would have to be copied to lindfs beforehand
	for (int i = 1; i < argc; i++) {
		struct stat st = {0};
		printf("running fstat(\"%s\")\n", argv[i]);
		fd = open(argv[i], O_RDONLY);
		if (fstat(fd, &st) < 0) {
			perror("fstat");
			printf("errno: %d\n", errno);
			exit(1);
		}
		printf("size: %jd\n", st.st_size);
	}

	return 0;
}
