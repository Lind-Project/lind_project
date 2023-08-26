#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char old_name[] = "";
    // char new_name[] = "testfiles/renamefile.txt";
    // int fd = open(new_name, O_RDONLY);
    struct stat st;
    int ret_stat, ret_fstat, ret_lstat;
    
    ret_stat = stat(old_name, &st);
    if(ret_stat < 0) {
        printf("ERROR: %d\n", errno);
        perror("stat");
        fflush(NULL);
        printf("Return: %d\n", ret_stat);
    }

    // ret_fstat = fstat(fd, &st);
    //     if(ret_fstat < 0) {
    //     printf("ERROR: %d\n", errno);
    //     perror("fstat");
    //     fflush(NULL);
    //     printf("Return: %d\n", ret_fstat);
    // }

    return 0;
}
