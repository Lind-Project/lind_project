#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char str[] = "write succeeded\n";

    int backup = dup(STDOUT_FILENO);   // make backup of stdout

    write(backup, str, sizeof str - 1);
 
    return 0;
}

