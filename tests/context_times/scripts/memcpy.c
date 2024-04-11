#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ITERS 4098

long long gettimens(void)
{
    struct timespec tp;

    if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1)
    {
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }

    return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

int main(int argc, char *argv[])
{

    int i = atoi(argv[1]);

    unsigned long long size = 1UL << i;

    char *src = (char *)malloc(sizeof(char) * size);
    char *dest = (char *)malloc(sizeof(char) * size);

    long long start_time = gettimens();

    for (int i = 0; i < ITERS; i++)
    {
        memcpy(dest, src, size);
    }

    long long end_time = gettimens();

    long long total_time = (end_time - start_time);
    double time_per_iter = (double)total_time / ITERS;
    double bpns = size / time_per_iter;
    double gbps = bpns / 0.931; // gbps conversion factor of 1000000000/1,073,741,824

    printf("average time %f \n", gbps);

    free(src);
    free(dest);

    return (0);
}
