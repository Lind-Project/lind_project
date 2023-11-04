#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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

/*--------Shared Memory--------*/
int shmid;

typedef struct {
    int a[2];
} SharedMemory;

SharedMemory *shared_memory;

// Initialize shared memo
void init_shared_memory() {
    // Create
    shmid = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
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
}

void destroy_shared_memory() {
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);
}

/*--------Thread functions--------*/
void* thread1(int i) {
    int count = 0;
    long long start_time = gettimens();
    while(count <= i) {
        shared_memory->a[0] = shared_memory->a[1] + 1;
        count++;
    }
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    // Average
    long long average_time = total_time/count;
    printf("[thread 1] %d shared memory calls, average time %lld ns\n", i, average_time);
    fflush(NULL);

    return NULL;
}

void* thread2(int i) {
    int count = 0;
    long long start_time = gettimens();
    while(count <= i) {
        shared_memory->a[1] = shared_memory->a[0];
        count++;
    }
    long long end_time = gettimens();
    long long total_time = end_time - start_time;
    // Average
    long long average_time = total_time/count;
    printf("[thread 2] %d shared memory calls, average time %lld ns\n", i, average_time);
    fflush(NULL);

    return NULL;
}

/*--------Main functions--------*/
int main(int argc, char *argv[]) {
    int i = atoi(argv[1]);
    printf("%d\n", 1);
    fflush(NULL);
    init_shared_memory();
    printf("%d\n", 2);
    fflush(NULL);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1(i), NULL);
    sleep(100);
    pthread_create(&t2, NULL, thread2(i), NULL);
    printf("%d\n", 3);
    fflush(NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("%d\n", 4);
    fflush(NULL);
    destroy_shared_memory();
    printf("%d\n", 5);
    fflush(NULL);
    return 0;
}

