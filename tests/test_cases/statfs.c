#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

int main(int argc, char **argv) {
  // char FILENAME[100] = "/dev/urandom";
  char FILENAME[100] = "testfiles/statfsfile.txt";
  
  // statfs
  struct statfs buf = {0};
  if (statfs(FILENAME, &buf) == -1) {
    perror("Error in statfs\n");
    exit(EXIT_FAILURE);
  }
  // system file info
  if (buf.f_type != 0xBEEFC0DE)
  {
    fprintf(stderr, "Expected statfsfile.txt to have file type beefc0de but was  %lx\n", buf.f_type);
		exit(EXIT_FAILURE);
  }
  if (buf.f_blocks != 4096)
  {
    fprintf(stderr, "Expected statfsfile.txt to have total block 4096 but was  %ld\n", buf.f_blocks);
		exit(EXIT_FAILURE);
  }
  if (buf.f_bavail != 1073741824)
  {
    fprintf(stderr, "Expected statfsfile.txt to have available blocks (non-root) 1073741824 but was  %ld\n", buf.f_bavail);
		exit(EXIT_FAILURE);
  }
  fprintf(stdout, "Getting file info successfully\n");
  fflush(stdout);
  return 0;
}
