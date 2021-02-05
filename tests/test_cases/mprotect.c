#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

int main() {
  char* text = "Mprotect write test text";
  char* readonlydata;
  if(!(readonlydata = mmap(NULL, 4096, PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0))) {
    perror("Failed to mmap page\n");
  }
  if(mprotect(readonlydata, 4096, PROT_READ | PROT_WRITE)) {
    perror("Failed to mprotect page\n");
  }
  memcpy(readonlydata, text, strlen(text) + 1);
  puts(readonlydata);
  if(munmap(readonlydata, 4096)) {
    perror("Failed to munmap page\n");
  }
}
