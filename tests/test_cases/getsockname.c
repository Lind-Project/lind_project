/* A multithreaded testcase for shutdown() and socket functions */

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

pthread_barrier_t barrier;

const int NUM_OF_PINGER = 2;
const int NUM_OF_PINGPONG = 10;
const int BUFFER_SIZE = 32;

void clear_buffer(char *buffer, int length) {
  for (int i = 0; i < length; ++i) {
    buffer[i] = 0;
  }
}

void test_getpeername(int socket_fd) {
  struct sockaddr_storage addr;
  socklen_t addr_len = sizeof(addr);
  char ipstr[INET6_ADDRSTRLEN];

  if (getpeername(socket_fd, (struct sockaddr *)&addr, &addr_len) == -1) {
    perror("getpeername");
    exit(EXIT_FAILURE);
  }

  if (addr.ss_family == AF_INET) {
    struct sockaddr_in *s = (struct sockaddr_in *)&addr;
    inet_ntop(AF_INET, &(s->sin_addr), ipstr, INET_ADDRSTRLEN);
    printf("getpeername: IPv4 address: %s\n", ipstr);
  } else { // AF_INET6
    struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
    inet_ntop(AF_INET6, &(s->sin6_addr), ipstr, INET6_ADDRSTRLEN);
    printf("getpeername: IPv6 address: %s\n", ipstr);
  }
}

void test_getsockname(int socket_fd) {
  struct sockaddr_storage addr;
  socklen_t addr_len = sizeof(addr);
  char ipstr[INET6_ADDRSTRLEN];

  if (getsockname(socket_fd, (struct sockaddr *)&addr, &addr_len) == -1) {
    perror("getsockname");
    exit(EXIT_FAILURE);
  }

  if (addr.ss_family == AF_INET) {
    struct sockaddr_in *s = (struct sockaddr_in *)&addr;
    inet_ntop(AF_INET, &(s->sin_addr), ipstr, INET_ADDRSTRLEN);
    printf("getsockname: IPv4 address: %s\n", ipstr);
  } else { // AF_INET6
    struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
    inet_ntop(AF_INET6, &(s->sin6_addr), ipstr, INET6_ADDRSTRLEN);
    printf("getsockname: IPv6 address: %s\n", ipstr);
  }
}

void test_getsockopt(int socket_fd) {
  int option_value;
  socklen_t option_len = sizeof(option_value);

  if (getsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &option_value,
                 &option_len) == -1) {
    perror("getsockopt");
    exit(EXIT_FAILURE);
  }

  printf("getsockopt: Socket reuse addr flag: %d\n", option_value);
}

// Adapted from https://www.geeksforgeeks.org/socket-programming-cc/
void *ponger(void *vargp) {
  int server_fd, new_socket, valread, finished;
  int opt = 1;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE];

  // Create server socket
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("ponger socket failed");
    exit(EXIT_FAILURE);
  }

  // Set server socket option
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("ponger setsockopt failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(5000);

  // Bind server socket to the address
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("ponger bind failed");
    exit(EXIT_FAILURE);
  }

  // Start listening
  if (listen(server_fd, 3) < 0) {
    perror("ponger listen failed");
    exit(EXIT_FAILURE);
  }

  pthread_barrier_wait(&barrier);

  // Bounce and increment numbers between pingers
  for (int i = 0; i < NUM_OF_PINGER * NUM_OF_PINGPONG; ++i) {
    // Establish a new connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      perror("ponger accept failed");
      exit(EXIT_FAILURE);
    }

    // Receive a value from a pinger
    clear_buffer(buffer, BUFFER_SIZE);
    valread = read(new_socket, buffer, BUFFER_SIZE);
    printf("ponger receive: %s, valread: %d\n", buffer, valread);
    fflush(stdout);

    // Increment the value by 1 and send it back
    sprintf(buffer, "%d", atoi(buffer) + 1);
    printf("ponger send: %s\n", buffer);
    send(new_socket, buffer, strlen(buffer), 0);
    fflush(stdout);

    // Test functions
    // test_getpeername(new_socket);
    // test_getsockname(new_socket);
    test_getsockopt(new_socket);

    // Close the socket after sending the response
    shutdown(new_socket, SHUT_WR); 
  }

  shutdown(server_fd, SHUT_RDWR);
  close(server_fd);
}

void *pinger(void *vargp) {
  int pinger_id = *((int *)vargp);
  int sock = 0, valread, client_fd;
  int opt = 1;
  int counter = 0;
  struct sockaddr_in serv_addr;
  char buffer[BUFFER_SIZE];

  pthread_barrier_wait(&barrier);

  // Loop a few times to try trigger race conditions
  for (int i = 0; i < NUM_OF_PINGPONG; ++i) {
    // Create a pinger socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("pinger socket failed");
      exit(EXIT_FAILURE);
    }

    // Set pinger socket options
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
      perror("pinger setsockopt failed");
      exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    // Set the address
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
      perror("pinger inet_pton failed");
      exit(EXIT_FAILURE);
    }

    // Connect to ponger
    if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr,
                             sizeof(serv_addr))) < 0) {
      perror("pinger connection failed");
      exit(EXIT_FAILURE);
    }

    // Increment the current number by 1 and send it to ponger
    clear_buffer(buffer, BUFFER_SIZE);
    sprintf(buffer, "%d", ++counter);
    printf("client %d send: %s\n", pinger_id, buffer);
    fflush(stdout);
    send(sock, buffer, strlen(buffer), 0);

    // Read the incremented number from ponger
    clear_buffer(buffer, BUFFER_SIZE);
    valread = read(sock, buffer, BUFFER_SIZE);
    counter = atoi(buffer);
    printf("client %d receive: %s, valread: %d\n", pinger_id, buffer, valread);
    fflush(stdout);

    close(sock);
  }
}

int main(int argc, char *argv[]) {
  pthread_t ponger_id, pinger_id[NUM_OF_PINGER];
  int pinger_id_natural[NUM_OF_PINGER];
  for (int i = 0; i < NUM_OF_PINGER; ++i) {
    pinger_id_natural[i] = i;
  }

  pthread_barrier_init(&barrier, NULL, NUM_OF_PINGER + 1);

  printf("Starting Ponger\n");
  fflush(stdout);
  pthread_create(&ponger_id, NULL, ponger, NULL);

  for (int i = 0; i < NUM_OF_PINGER; ++i) {
    printf("Starting Pinger %d\n", i);
    fflush(stdout);
    pthread_create(&pinger_id[i], NULL, pinger, (void *)&pinger_id_natural[i]);
  }

  pthread_join(ponger_id, NULL);
  for (int i = 0; i < NUM_OF_PINGER; ++i) {
    pthread_join(pinger_id[i], NULL);
  }

  printf("Threads end\n");
  fflush(stdout);

  pthread_barrier_destroy(&barrier);

  return 0;
}
