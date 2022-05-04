#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main()
{
    key_t key = 31337;
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  
    // shmat to attach to shared memory
    char *shm = (char*) shmat(shmid, (void*)0, 0);
    char str[8] = "Hello!";
    
    memcpy(shm, str, 8); 
  
    printf("Data written in memory: %s\n", str);
      
    //detach from shared memory 
    shmdt(str);
  
    return 0;
}
