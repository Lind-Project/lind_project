#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>


#define WBS_ONE    256
#define WBS_TWO    4096
#define WBS_THREE    65536
#define WBS_FOUR    1048576

void main() {

    clock_t before;
    clock_t difference;
    int usec;

    char bufferone[WBS_ONE]; 
    for (int i = 0; i < WBS_ONE; i++) bufferone[i] = 'A';
    before = clock();
    write(STDOUT_FILENO, bufferone, WBS_ONE);
    difference = clock() - before;
    usec = (difference * 1000000) / CLOCKS_PER_SEC;
    fprintf(stderr, "\nwrite 2^8 usec: %d ms\n", usec);

    char buffertwo[WBS_TWO]; 
    for (int i = 0; i < WBS_TWO; i++) buffertwo[i] = 'A';
    before = clock();
    write(STDOUT_FILENO, buffertwo, WBS_TWO);
    difference = clock() - before;
    usec = (difference * 1000000) / CLOCKS_PER_SEC;
    fprintf(stderr, "\nwrite 2^12 usec: %d ms\n", usec);

    char bufferthree[WBS_THREE]; 
    for (int i = 0; i < WBS_THREE; i++) bufferthree[i] = 'A';
    before = clock();
    write(STDOUT_FILENO, bufferthree, WBS_THREE);
    difference = clock() - before;
    usec = (difference * 1000000) / CLOCKS_PER_SEC;
    fprintf(stderr, "\nwrite 2^16 usec: %d ms\n", usec);


    char bufferfour[WBS_FOUR]; 
    for (int i = 0; i < WBS_FOUR; i++) bufferfour[i] = 'A';
    before = clock();
    write(STDOUT_FILENO, bufferfour, WBS_FOUR);
    difference = clock() - before;
    usec = (difference * 1000000) / CLOCKS_PER_SEC;
    fprintf(stderr, "\nwrite 2^20 usec: %d ms\n", usec);


    close(1);
    close(2);
    
}

