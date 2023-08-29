#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define DIR "lis/testfolder"

int main() {
    mode_t dir_per = (S_IRUSR | S_IWUSR);
    int ret_mk1, ret_mk2, ret_rm1, ret_rm2;

    ret_mk1 = mkdir(DIR, dir_per);
    printf("First mkdir return: %d\n", ret_mk1);
    fflush(NULL);
    ret_mk2 = mkdir(DIR, dir_per);
    if(ret_mk2 < 0) {
        printf("ERROR: %d\n", errno);
        perror("mkdir");
        fflush(NULL);
        printf("Second mkdir return: %d\n", ret_mk2);
    }

    ret_rm1 = rmdir(DIR);
    printf("First rmdir return: %d\n", ret_rm1);
    fflush(NULL);
    ret_rm2 = rmdir(DIR);
    if(ret_rm2 < 0) {
        printf("ERROR: %d\n", errno);
        perror("rmdir");
        fflush(NULL);
        printf("Second rmdir return: %d\n", ret_rm2);
        exit(1);
    }    

    return 0;

}