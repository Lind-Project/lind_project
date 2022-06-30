#include <stdio.h>
//note: requires coreutils to be loaded in
int main() {
  FILE *pfile = popen("/bin/cat", "w");
  fprintf(pfile, "This is a test of popen in lind\n");
  pclose(pfile);
}
