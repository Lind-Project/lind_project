#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    pid_t pid1, pid2;
    char *fileset = "/usr/local/pgsql/data/base/pgsql_tmp/pgsql_tmp15.0.sharedfileset";
    char *file_0_0 = "/usr/local/pgsql/data/base/pgsql_tmp/pgsql_tmp15.0.sharedfileset/0.0";
    char *file_0_1 = "/usr/local/pgsql/data/base/pgsql_tmp/pgsql_tmp15.0.sharedfileset/0.1";
    char *file_1_0 = "/usr/local/pgsql/data/base/pgsql_tmp/pgsql_tmp15.0.sharedfileset/1.0";
    char *file_1_1 = "/usr/local/pgsql/data/base/pgsql_tmp/pgsql_tmp15.0.sharedfileset/1.1";

    // Create the first child process
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid1 == 0)
    {
        int counter = 0;
        while (counter++ < 1000)
        {
            // Child process 1
            struct stat st;
            if (stat(file_0_1, &st) == 0)
            {
                printf("Child 1: stat successful on %s\n", file_0_1);
                fflush(stdout);
            }
            else
            {
                perror("Child 1: stat failed");
            }

            int fd = open(file_0_0, O_RDWR | O_CREAT | O_TRUNC);
            if (fd != -1)
            {
                printf("Child 1: open successful on %s\n", file_0_0);
                fflush(stdout);
                close(fd);
            }
            else
            {
                perror("Child 1: open failed");
            }

            if (mkdir(fileset, 0777) == 0)
            {
                printf("Child 1: mkdir successful on %s\n", fileset);
                fflush(stdout);
            }
            else
            {
                perror("Child 1: mkdir failed");
            }

            fd = open(file_0_0, O_RDWR | O_CREAT | O_TRUNC);
            if (fd != -1)
            {
                printf("Child 1: open successful on %s\n", file_0_0);
                fflush(stdout);
                close(fd);
            }
            else
            {
                perror("Child 1: open failed");
                exit(1);
            }

            if (stat(fileset, &st) == 0)
            {
                printf("Child 1: stat successful on %s\n", fileset);
                fflush(stdout);
            }
            else
            {
                perror("Child 1: stat failed");
            }

            if (remove(file_0_0) == 0)
            {
                printf("Child 1: remove successful on %s\n", file_0_0);
                fflush(stdout);
            }
            else
            {
                perror("Failed to remove directory");
            }

            if (rmdir(fileset) == 0)
            {
                printf("Child 1: rmdir successful on %s\n", fileset);
                fflush(stdout);
            }
            else
            {
                perror("Failed to remove directory");
            }
        }
        exit(0);
    }

    // // Create the second child process
    // pid2 = fork();
    // if (pid2 < 0)
    // {
    //     perror("Fork failed");
    //     exit(1);
    // }
    // else if (pid2 == 0)
    // {
    //     int counter = 0;
    //     while (counter++ < 1000)
    //     {
    //         // Child process 2
    //         struct stat st;
    //         if (stat(file_1_1, &st) == 0)
    //         {
    //             printf("Child 2: stat successful on %s\n", file_1_1);
    //             fflush(stdout);
    //         }
    //         else
    //         {
    //             perror("Child 2: stat failed");
    //         }

    //         int fd = open(file_1_0, O_RDWR | O_CREAT | O_TRUNC);
    //         if (fd != -1)
    //         {
    //             printf("Child 2: open successful on %s\n", file_1_0);
    //             fflush(stdout);
    //             close(fd);
    //         }
    //         else
    //         {
    //             perror("Child 2: open failed");
    //         }

    //         if (mkdir(fileset, 0777) == 0)
    //         {
    //             printf("Child 2: mkdir successful on %s\n", fileset);
    //             fflush(stdout);
    //         }
    //         else
    //         {
    //             perror("Child 2: mkdir failed");
    //         }

    //         fd = open(file_1_0, O_RDWR | O_CREAT | O_TRUNC);
    //         if (fd != -1)
    //         {
    //             printf("Child 2: open successful on %s\n", file_1_0);
    //             fflush(stdout);
    //             close(fd);
    //         }
    //         else
    //         {
    //             perror("Child 2: open failed");
    //             exit(1);
    //         }

    //         if (stat(fileset, &st) == 0)
    //         {
    //             printf("Child 2: stat successful on %s\n", fileset);
    //             fflush(stdout);
    //         }
    //         else
    //         {
    //             perror("Child 2: stat failed");
    //         }

    //         if (remove(file_1_0) == 0)
    //         {
    //             printf("Child 2: remove successful on %s\n", file_1_0);
    //             fflush(stdout);
    //         }
    //         else
    //         {
    //             perror("Failed to remove directory");
    //         }

    //         if (rmdir(fileset) == 0)
    //         {
    //             printf("Child 2: rmdir successful on %s\n", fileset);
    //             fflush(stdout);
    //         }
    //         else
    //         {
    //             perror("Failed to remove directory");
    //         }
    //     }
    //     exit(0);
    // }

    // // Wait for both child processes to complete
    // waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
