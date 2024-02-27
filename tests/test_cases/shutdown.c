/* A multithreaded testcase for shutdown() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

pthread_barrier_t barrier;

const int NUM_OF_PINGER = 2;
const int NUM_OF_PINGPONG = 10;
const int BUFFER_SIZE = 32;

void clear_buffer(char *buffer, int length) {
	for (int i = 0; i < length; ++i) {
		buffer[i] = 0;
	}
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
		printf("ponger socket failed: %s\n", strerror(errno));
		fflush(stdout);
		exit(EXIT_FAILURE);
	}

	// Set server socket option
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		printf("ponger setsockopt failed: %s\n", strerror(errno));
		fflush(stdout);
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(5000);

	// Bind server socket to the address
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
			printf(strerror(errno));
		printf("ponger bind failed: %s\n", strerror(errno));
		fflush(stdout);
		exit(EXIT_FAILURE);
	}

	// Start listening
	if (listen(server_fd, 3) < 0) {
		printf("ponger listen failed: %s\n", strerror(errno));
		fflush(stdout);
		exit(EXIT_FAILURE);
	}

	pthread_barrier_wait(&barrier);

	// Bounce and increment numbers between pingers
	for (int i = 0; i < NUM_OF_PINGER * NUM_OF_PINGPONG; ++i) {
		// Establish a new connection
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
			printf("ponger accept failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Receive a value from a pinger
		clear_buffer(buffer, BUFFER_SIZE);
		valread = read(new_socket, buffer, BUFFER_SIZE);
		printf("ponger receive: %s\n", buffer);
		fflush(stdout);

		// Increment the value by 1 and send it back
		sprintf(buffer, "%d", atoi(buffer)+1);
		send(new_socket, buffer, strlen(buffer), 0);
		printf("ponger send: %s\n", buffer);
		fflush(stdout);

		close(new_socket);
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
			printf("pinger socket failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}
		
		// Set pinger socket options
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
			printf("pinger setsockopt failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(5000);

		// Set the address
		if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
			printf("pinger inet_pton failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Connect to ponger
		if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
			printf("pinger connection failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Increment the current number by 1 and send it to ponger
		clear_buffer(buffer, BUFFER_SIZE);
		sprintf(buffer, "%d", ++counter);
		printf("client %d send: %s\n", pinger_id, buffer);
		fflush(stdout);
		send(sock, buffer, strlen(buffer), 0);

		// Call shutdown(). Not the way it's supposed to be used, but good enough for testing purpose
		shutdown(sock, SHUT_WR);

		// Read the incremented number from ponger
		clear_buffer(buffer, BUFFER_SIZE);
		valread = read(sock, buffer, BUFFER_SIZE);
		counter = atoi(buffer);
		printf("client %d receive: %s\n", pinger_id, buffer);
		fflush(stdout);

		close(sock);
	}
}

int main( int argc, char *argv[] ) {
	pthread_t ponger_id, pinger_id[NUM_OF_PINGER];
	int pinger_id_natural[NUM_OF_PINGER];
	for (int i = 0; i < NUM_OF_PINGER; ++i) {
		pinger_id_natural[i] = i;
	}

	pthread_barrier_init(&barrier, NULL, NUM_OF_PINGER+1);
	
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
