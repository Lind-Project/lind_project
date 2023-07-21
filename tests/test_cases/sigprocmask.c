#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void sh1(int sig){
    printf("signal %d received\n", sig);
    fflush(stdout);
}

// void sh2(int sig){
//     printf("signal %d received\n", sig);
//     fflush(stdout);
// }

void* th1(void* arg){
    printf("I am thread01\n");
    fflush(stdout);
    
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    
    struct sigaction sa1;
    sa1.sa_handler = sh1;
    sa1.sa_flags = 0;
    sa1.sa_mask = mask;
    sigaction(SIGUSR1, &sa1, NULL);

    sigprocmask(SIG_BLOCK, &mask, NULL);
    
    return NULL;
}

// void* th2(void* arg){
//     printf("I am thread02\n");
//     fflush(stdout);
    
//     sigset_t mask;
//     sigemptyset(&mask);
//     sigaddset(&mask, SIGUSR2);
    
//     struct sigaction sa2;
//     sa2.sa_handler = sh2;
//     sa2.sa_flags = 0;
//     sa2.sa_mask = mask;
//     sigaction(SIGUSR2, &sa2, NULL);
    

//     sigprocmask(SIG_BLOCK, &mask, NULL);
    
//     return NULL;
// }

// int main(void) {
//     pthread_t thread1, thread2;
    
//     pthread_create(&thread1, NULL, th1, NULL);
//     pthread_create(&thread2, NULL, th2, NULL);
    
//     sleep(2);
    
//     // Send signal to threads
//     if (pthread_kill(thread1, SIGUSR2) != 0){
//         printf("Error of Thread 1 is: %s\n", strerror(errno));
//         fflush(stdout);
//     }
//     if (pthread_kill(thread2, SIGUSR2) != 0){
//         printf("Error of Thread 2 is: %s\n", strerror(errno));
//         fflush(stdout);
//     }
    
// //    // Send signal to main
// //    char buf[512];
// //    printf("My PID is %d\n", getpid());
// //    while (1) {
// //        if (read(STDIN_FILENO, buf, 511) == -1){
// //            printf("Error of Main is: %d\n", errno);
// //            fflush(stdout);
// //        }
// //    }
    
//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);
//     printf("Successful\n");
//     fflush(stdout);
//     return EXIT_SUCCESS;

// }
 
static void sig_usr(int signum){
    if(signum == SIGUSR2){
        printf("SIGUSR2 received\n");
    }else{
        printf("signal %d received\n", signum);
    }
}
 
int main(void){
    char buf[512];
    int n;
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sig_usr;   
    
    sigaction(SIGUSR2, &sa_usr, NULL);
    
    printf("My PID is %d\n", getpid());
    
    while(1){
        if((n = read(STDIN_FILENO, buf, 511)) == -1){
            if(errno == EINTR){
                printf("read is interrupted by signal\n");
                break;
            }
        }
        else{
            buf[n] = '\0';
            printf("%d bytes read: %s\n", n, buf);
        }
    }

    int ret;
    pthread_t thread1;
    ret = pthread_create(&thread1, NULL, th1, NULL);
    if (ret != 0){
        perror("Thread1 failed");
    }
    sleep(1);
    int res;
    res = pthread_kill(thread1, SIGUSR1);
    if (res == EINTR){
        printf("Error of Thread 1 is: %s\n", strerror(errno));
    }
    pthread_join(thread1, NULL);

    printf("End\n");
    return 0;
}
