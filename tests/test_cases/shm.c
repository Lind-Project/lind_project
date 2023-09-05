#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
 
#define SHM_SIZE 128
 
// union semun
// {
// 	int val;
// 	struct semid_ds *buf;
// 	unsigned short *arry;
// };
 
static int sem_id = 0;
int real_i = 0;
 
static int set_semvalue();
static void del_semvalue();
static int semaphore_p();
static int semaphore_v();
 
int main(int argc, char *argv[]) {
	int shm_id = 0;
	char message = 'X';
	char *share;
	int i = 0;
 
	// Create semahore
	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);
	
	// 1. Create shared memory
    shm_id = shmget((key_t)1234, SHM_SIZE, IPC_CREAT|0666);
    if(shm_id == -1){
        perror("shmget()");
    }
	// 2.Link shared memory with 
    share = shmat(shm_id, NULL, 0);
 
	if(argc > 1)
	{
		// Initialize semaphore when first time
		if(!set_semvalue())
		{
			fprintf(stderr, "Failed to initialize semaphore\n");
			exit(EXIT_FAILURE);
		}
		message = argv[1][0];
		sleep(2);
	}
	for(i = 0; i < 10; ++i)
	{
		// Enter the critical section
		if(!semaphore_p())
			exit(EXIT_FAILURE);
		printf("%c", message);
		fflush(stdout);
		sprintf(share+strlen(share), "%c", message);
		real_i += 1;
		sleep(rand() % 3);
		sprintf(share+strlen(share), "%c", message);
		real_i += 1;
		// Leave critical section and sleep random time
		printf("%c", message);
		fflush(stdout);
		if(!semaphore_v())
			exit(EXIT_FAILURE);
		sleep(rand() % 2);
	}
 
	sleep(10);
	printf("\n %s - finished\n", share);
 
	if(argc > 1)
	{
		//If the program is called for the first time, delete the semaphore before exiting
		sleep(3);
		del_semvalue();
	}
	
	// 3. Detach shared memory from current process
    shmdt(share);
	// 4. Delete shared memory
    shmctl(shm_id, IPC_RMID, 0);
	
	return 0;
}
 
static int set_semvalue() {
	// Initialize
	union semun sem_union;
 
	sem_union.val = 1;
	if(semctl(sem_id, 0, SETVAL, sem_union) == -1)
		return 0;
	return 1;
}
 
static void del_semvalue() {
	// Delete semahore
	union semun sem_union;
 
	if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
		fprintf(stderr, "Failed to delete semaphore\n");
}
 
static int semaphore_p() {
	// -1
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;//P()
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		fprintf(stderr, "semaphore_p failed\n");
		return 0;
	}
	return 1;
}
 
static int semaphore_v(){
	//这是一个释放操作，它使信号量变为可用，即发送信号V（sv）
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;//V()
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		fprintf(stderr, "semaphore_v failed\n");
		return 0;
	}
	return 1;
}
