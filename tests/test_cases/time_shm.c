#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

/*--------Timing functions--------*/
long long execution_time = 0;

long long gettimens(void) {
  struct timespec tp;

  if( clock_gettime(CLOCK_MONOTONIC, &tp) == -1 ) {
    perror( "clock gettime" );
    exit( EXIT_FAILURE );
  }

  return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}
// long long gettimems(void) {
//     struct timespec tp;

//     if(clock_gettime(CLOCK_MONOTONIC, &tp) == -1) {
//         perror("clock gettime");
//         exit(EXIT_FAILURE);
//     }

//     return (tp.tv_sec * 1000) + (tp.tv_nsec / 1000000);
// }
/*--------Shared Memory--------*/
int shmid;

typedef struct {
    int a[2];
} SharedMemory;

SharedMemory *shared_memory;

// Initialize shared memo
void init_shared_memory() {
    int *array;
    int count = 5;
    int i = 0;
    // Create
    shmid = shmget(31337, count*sizeof(int), IPC_CREAT | 0666);
    if(shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Connect
    shared_memory = (SharedMemory *)shmat(shmid, NULL, 0);
    if((intptr_t)shared_memory == -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    shared_memory->a[0] = 0;
    shared_memory->a[1] = 0;
}

void destroy_shared_memory() {
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);
}

/*--------Thread functions--------*/
void* thread1() {
    long long count = 0;
    while(count <= 2000000000) {
        shared_memory->a[0] = shared_memory->a[1] + 1;
        count++;
    }
    return NULL;
}

void* thread2() {
    long long count = 0;
    while(count <= 2000000000) {
        shared_memory->a[1] = shared_memory->a[0];
        count++;
    }
    return NULL;
}

/*--------Main functions--------*/
int main(int argc, char *argv[]) {
    // destroy_shared_memory();
    init_shared_memory();
    
    pthread_t t1, t2;

    long long start_time = gettimens();

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    long long average_time = total_time/2000000000;
    printf("start: %lld\nend: %lld\n", start_time, end_time);
    printf("%d shared memory calls, average time %lld ms\n", 2000000000, average_time);
    fflush(NULL);

    destroy_shared_memory();
    
    return 0;
}

