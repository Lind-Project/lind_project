// #undef _GNU_SOURCE
// #define _GNU_SOURCE

// #include <errno.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/statfs.h>

// #define EXPECTED_TYPE 0x6969

// void test_statfs(const char *file_name){
//   struct statfs buf = {0};

//   if (statfs(file_name, &buf) == -1) {
//     perror("Error in fstatfs");
//     printf("File: %s\n", file_name);
//     return;
//   }

//   printf("Testing file: %s\n", file_name);
//   printf("File system type: %d\n", buf.f_type);
//   printf("Total file system blocks: %ld\n", buf.f_blocks);
//   printf("Free blocks: %ld\n", buf.f_bfree);
//   printf("Total file system inodes: %ld\n", buf.f_files);
//   printf("Free inodes: %ld\n", buf.f_ffree);
//   fflush(stdout);

//   if (buf.f_type != EXPECTED_TYPE) {
//     printf("Unexpected file system type for file %s: expected %d, got %d\n",
//       file_name, EXPECTED_TYPE, buf.f_type);
//   }
  
// }

// int main(int argc, char **argv) {
//   char file_name[100] = "testfiles/statfsfile.txt";

//   if (argc < 2) {
//     fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
//     exit(EXIT_FAILURE);
//   }

//   // statfs
//   // struct statfs buf = {0};
//   // if (statfs(file_name, &buf) == -1) {
//   //   perror("Error in fstatfs\n");
//   //   exit(EXIT_FAILURE);
//   // }
//   // expected output is: NFS_SUPER_MAGIC 0x6969 on native CentOS 7 on CIMS
//   // printf("filesystem type: %d", buf.f_type);
//   // fflush(stdout);
//   for (int i = 1; i < argc; ++i) {
//     test_statfs(argv[i]);
//   }
//   return 0;
// }

#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statfs.h>

int main(int argc, char **argv) {
  char file_name[100] = "testfiles/statfsfile.txt";

  // statfs
  struct statfs buf = {0};
  if (statfs(file_name, &buf) == -1) {
    perror("Error in fstatfs\n");
    exit(EXIT_FAILURE);
  }
  // expected output is: 
  printf("filesystem type: %lx\n", buf.f_type);
  fflush(stdout);
  return 0;
}