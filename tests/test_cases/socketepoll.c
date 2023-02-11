#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <pthread.h> 

#define PORT 9994

#define TRUE             1
#define FALSE            0

pthread_barrier_t closebarrier;
pthread_barrier_t syncbarrier;

void* client(void* v) { 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client\n"; 
    char *followup = "Did you get my message?\n";
    char buffer[1024] = {0}; 
    long opt = 1;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
      perror("setsockopt"); 
      exit(EXIT_FAILURE); 
    }

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    pthread_barrier_wait(&syncbarrier);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sock , hello , strlen(hello) , 0 );
    printf("CLIENT: Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    write(1,buffer, valread); 
    fflush(stdout);
    printf("CLIENT: sending followup\n");
    send(sock,followup, strlen(followup),0);
    close(sock);
    printf("CLIENT: Closed connection\n");
    fflush(stdout);
    pthread_barrier_wait(&closebarrier);
    return NULL; 
} 

void* server(void* v) {
   char* response = "Message Received\n";
   int    i, len, rc, on = 1;
   int    listen_sd, max_sd, new_sd;
   int    desc_ready, end_server = FALSE;
   int    close_conn;
   int    epfd, nfds, connfd;
   char   buffer[80];
   socklen_t clilen;
   struct sockaddr_in   addr;
   //struct sockaddr_in   serv_addr;
   //struct timeval       timeout;
   struct epoll_event ev, events[20]; // ev is used to register events, and the array is used to return events to be processed
   int connected, num_fd = 0; // connected is set to 1 when the server makes the first connection, num_fd is a counter of open fd monitored by epoll

   pthread_barrier_init(&closebarrier, NULL, 2);
   
   /* Create an AF_INET6 stream socket to receive incoming      */
   /* connections on                                            */
   
   listen_sd = socket(AF_INET, SOCK_STREAM, 0);
   if (listen_sd < 0)
   {
      perror("socket() failed");
      exit(-1);
   }
   
   /* Allow socket descriptor to be reuseable                   */
   
   rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on));
   if (rc < 0)
   {
      perror("setsockopt() failed");
      close(listen_sd);
      exit(-1);
   }

   
   /* Set socket to be nonblocking. All of the sockets for      */
   /* the incoming connections will also be nonblocking since   */
   /* they will inherit that state from the listening socket.   */
   
   rc = ioctl(listen_sd, FIONBIO, (char *)&on);
   if (rc < 0)
   {
      perror("ioctl() failed");
      close(listen_sd);
      exit(-1);
   }
   
   /* Bind the socket                                           */
   addr.sin_family = AF_INET; 
   addr.sin_addr.s_addr = INADDR_ANY; 
   addr.sin_port = htons( PORT ); 
   
   rc = bind(listen_sd,
             (struct sockaddr *)&addr, sizeof(addr));
   if (rc < 0)
   {
      perror("bind() failed");
      close(listen_sd);
      exit(-1);
   }

   /* Set the listen back log                                   */
   
   rc = listen(listen_sd, 1);
   if (rc < 0)
   {
      perror("listen() failed");
      close(listen_sd);
      exit(-1);
   }
   fprintf(stdout, "SERVER: New socket bound and listen\n");
   fflush(stdout);
    
   epfd = epoll_create(256);
   if(epfd == -1) 
   {
      perror("epoll_create error");
      exit(-1);

   }
   
   ev.data.fd = listen_sd;
   ev.events = EPOLLIN|EPOLLET;
   if (epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sd, &ev) != 0) {
      perror("epoll_ctl error");
      exit(-1);
   }

   pthread_barrier_wait(&syncbarrier);

   while(1) 
   {
      int n, i;
      n = epoll_wait(epfd, events, 20, 5); // epoll_wait() populates events array, n is the number of events that occurred
      if(n < 0) 
      {
	  perror("epoll_wait\n");
	  exit(-1);
      }
      if (connected == 1 && n == 0 && num_fd == 0) 
      {
         pthread_barrier_wait(&closebarrier);
	 return NULL;
      }
      for (i = 0; i < n; ++i) 
      {
	 if((events[i].events & EPOLLERR) ||
            (events[i].events & EPOLLHUP) || 
	    (!(events[i].events & EPOLLIN)))
         {
            /* Error with file descriptor or socket is not ready for reading. */
            fprintf(stderr, "epoll error\n");
	    fflush(stderr);
            if(close(events[i].data.fd) == -1) 
            {
	        perror("Error closing\n");
		exit(-1);
	    }
	    continue;
         }
         /* There is notification from listening socket. */
         else if (listen_sd == events[i].data.fd) 
         {
            fprintf(stdout, "SERVER: NEW CONNECTION\n");
	    fflush(stdout);
            num_fd++;
            connected = 1;
            while(1)
            {
               new_sd = accept(listen_sd,NULL,NULL);

	       if (new_sd < 0)
               {
                  if((errno != EWOULDBLOCK) || (errno != EAGAIN))
                  {
                     perror("accept error");
                     exit(-1);
                  }
               }
               ev.data.fd = new_sd;
               ev.events = EPOLLIN | EPOLLET;
               /* Add new_sd onto array of file descriptors that should be monitored. */
               if (epoll_ctl(epfd, EPOLL_CTL_ADD, new_sd, &ev) != 0) 
               {
                  perror("epoll_ctl error");
                  exit(-1);
               }
               break;
            }
         }
              
         else 
         {
            int done = 0;
            while (1)
            {
               /* There is data on the file descriptor that is waiting to be read. */
               ssize_t count;
               char buf[512];
               count = read (events[i].data.fd, buf, sizeof(buf));
               if (count == -1)
               {
                  /* If errno == EAGAIN, that means we have read all
                     data. So go back to the main loop. */
                  if (errno != EAGAIN)
                  {
                     perror ("read error");
                     done = 1;
                  }
                  break;
               }
               else if (count == 0)
               {
                  /* End of file. The remote has closed the
                     connection. */
                  done = 1;
                  break;
               }
               /* Write the buffer to standard output */
               if (write(1, buf, count) < 0)
               {
                  perror ("error with write");
                  exit(-1);
               }
               else 
               {
                  send(events[i].data.fd, response, strlen(response),0);
               }
            }

            if (done)
            {
               printf ("Closed connection on descriptor %d\n", events[i].data.fd);

               /* Closing the descriptor will make epoll remove it
                  from the set of descriptors which are monitored. */
               close (events[i].data.fd);
               num_fd--;
            }
         }
      }
   }
}


int main() {
    pthread_t serverthread, clientthread1;
    
    pthread_barrier_init(&syncbarrier, NULL, 2);
    pthread_create(&serverthread, NULL, server, NULL);
    pthread_create(&clientthread1, NULL, client, NULL);
    pthread_join(clientthread1, NULL);
    pthread_join(serverthread, NULL);
    pthread_barrier_destroy(&syncbarrier);
    pthread_barrier_destroy(&closebarrier);
    return 0;
}
