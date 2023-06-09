#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char **argv){

    if (argc < 2) {
		//printf("usage: %s <files>\n", argv[0]); //-causes a silly error on dettest - 
		//usage: /automated_tests/stat.NEXE <files> and usage: ./automated_tests/stat <files> do not match.
		printf("running access(\"testfile.txt\")\n"); //argv[0] to specify any file
		if (access("testfile.txt", F_OK) < 0) {
			perror("can't access");
			printf("errno: %d\n", errno);
			exit(1);
		}
		printf("file exist\n");

        if (access("testfile.txt", R_OK) < 0) {
			perror("R not okay");
			printf("errno: %d\n", errno);
		}

        if (access("testfile.txt", W_OK) < 0) {
			perror("W not okay");
			printf("errno: %d\n", errno);
		}

        if (access("testfile.txt", X_OK) < 0) {
			perror("X not okay");
			printf("errno: %d\n", errno);
		}
		exit(0);
	}

    printf("Of course you know I didn't implement this part\n");

    return 0;
}