#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main(){
  int fd = open("test.txt", O_RDWR | O_CREAT, 0777);
  char buf[] = "This is a test of the wonderful fork call in lind.";
  write(fd, buf, sizeof(buf));
  close(fd);
  fd = open("test.txt", O_RDWR);
  switch(fork()){
    case -1:
      puts("fork failed");
      break;
    case 0:
      close(fd);
      break;
    default:
      sleep(1);
      char newbuf[100];
      int numread = read(fd, newbuf, 100);
      printf("%s\n",newbuf);
      printf("read %d chars\n",numread);
      unlink("test.txt");
      close(fd);
      break;
  }
  return 0;
}
