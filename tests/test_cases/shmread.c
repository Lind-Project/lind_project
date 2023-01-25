#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
  
int main()
{
    key_t key = 31337; 
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0);
  
    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid, NULL, 0);
  
    printf("Data read from memory: %s\n",str);
  
    // mark the shared memory for removal
    shmctl(shmid, IPC_RMID, NULL);

    //detach from shared memory 
    shmdt(str);
    
    return 0;
}
