#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char old_name[] = "testfiles/renamefile.txt";
    struct stat st;
    int ret_stat;
    
    ret_stat = stat(old_name, &st);
    if(ret_stat < 0) {
        printf("ERROR: %d\n", errno);
        perror("stat");
        fflush(NULL);
        printf("Return: %d\n", ret_stat);
        exit(1);
    }

    printf("Return: %d\n", ret_stat);
    return 0;
}
