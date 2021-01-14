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
    struct sockaddr_in address; 
    int opt = 1; 
    int not_blocking;
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    // Forcefully attaching socket to the port 10000 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) 
    { 
        perror("setsockopt failed"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 10000  
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    printf("[For 0 = False and <any_other_int> = True]\n");
    printf("[The answers should be F, T, F]\n\n");

    if ( (val = fcntl(server_fd, F_GETFL, 0)) < 0) { 
    /* Something's wrong here, check errno to find out why */ 
        val = -val;
        not_blocking = val & O_NONBLOCK; 
        printf("(0) Is the socket set for non-blocking I/O?: %d\n", not_blocking);
    } else { 
        not_blocking = val & O_NONBLOCK; 
        printf("(0) Is the socket set for non-blocking I/O?: %d\n", not_blocking);
    } 

    printf("[Setting socket for non_blocking I/O]\n");
    ioctl(server_fd, FIONBIO, &opt);

    if ( (val = fcntl(server_fd, F_GETFL, 0)) < 0) { 
    /* Something's wrong here, check errno to find out why */
        val = -val;
        not_blocking = val & O_NONBLOCK; 
        printf("(1) Is the socket set for non-blocking I/O?: %d\n", not_blocking); 
    } else { 
        not_blocking = val & O_NONBLOCK; 
        printf("(1) Is the socket set for non-blocking I/O?: %d\n", not_blocking);
    } 

    opt = 0;
    printf("[Clearing socket for non-blocking I/O]\n");
    ioctl(server_fd, FIONBIO, &opt);
    opt = 1;

    if ( (val = fcntl(server_fd, F_GETFL, 0)) < 0) { 
    /* Something's wrong here, check errno to find out why */ 
        val = -val;
        not_blocking = val & O_NONBLOCK; 
        printf("(2) Is the socket set for non-blocking I/O?: %d\n", not_blocking);
    } else { 
        not_blocking = val & O_NONBLOCK; 
        printf("(2) Is the socket set for non-blocking I/O?: %d\n", not_blocking);
    } 

    return 0;
}
