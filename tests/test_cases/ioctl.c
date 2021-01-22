#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <sys/ioctl.h> 
#define PORT 10000 

int main()
{

    int server_fd, val; 
    int opt = 1; 
    int not_blocking;
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    printf("[For 0 = False and <any_other_int> = True]\n");
    printf("[The answers should be F, T, F]\n\n");

    if ( (val = fcntl(server_fd, F_GETFL)) < 0) { 
    /* Something's wrong here, check errno to find out why   */
        printf("Error: fcntl(F_GETFL) < 0, fcntl(F_GETFL)= %d", val); 
    } else { 
        not_blocking = val & O_NONBLOCK; 
        printf("(0) Is the socket set for non-blocking I/O?: %d\n", not_blocking);
    } 

    printf("[Setting socket for non_blocking I/O]\n");
    ioctl(server_fd, FIONBIO, &opt);

    if ( (val = fcntl(server_fd, F_GETFL)) < 0) { 
    /* Something's wrong here, check errno to find out why */ 
        printf("Error: fcntl(F_GETFL) < 0, fcntl(F_GETFL)= %d", val);
    } else { 
        not_blocking = val & O_NONBLOCK; 
        printf("(1) Is the socket set for non-blocking I/O?: %d\n", not_blocking);
    } 

    opt = 0;
    printf("[Clearing socket for non-blocking I/O]\n");
    ioctl(server_fd, FIONBIO, &opt);
    opt = 1;

    if ( (val = fcntl(server_fd, F_GETFL)) < 0) { 
    /* Something's wrong here, check errno to find out why  */
        printf("Error: fcntl(F_GETFL) < 0, fcntl(F_GETFL)= %d", val); 
    } else { 
        not_blocking = val & O_NONBLOCK; 
        printf("(2) Is the socket set for non-blocking I/O?: %d\n", not_blocking);
    } 
    
    return 0;
}
