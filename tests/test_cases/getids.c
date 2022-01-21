#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <pwd.h>

int main(void)
{
    puts("Gid:");
    printf("%d\n", getgid());
    puts("Uid:");
    printf("%d\n", getuid());
    puts("Egid");
    printf("%d\n", getegid());
    puts("Euid");
    printf("%d\n", geteuid());
}