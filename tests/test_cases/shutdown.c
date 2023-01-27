#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Adapted from https://www.geeksforgeeks.org/socket-programming-cc/
void *ponger(void *vargp) {
	int server_fd, new_socket, valread, finished;
	int opt = 1;
	int counter;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[1024];

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket failed\n");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		printf("setsockopt\n");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(5000);

	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		printf("bind failed\n");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		printf("listen\n");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
		printf("accept\n");
		exit(EXIT_FAILURE);
	}

	valread = read(new_socket, buffer, 1024);
	printf("ponger: %s\n", buffer);
	sprintf(buffer, "%d", atoi(buffer)+1);

	send(new_socket, buffer, strlen(buffer), 0);
	printf("ponger: %s\n", buffer);

	close(new_socket);
	shutdown(server_fd, SHUT_RDWR);
}

void *pinger(void *vargp) {
	int sock = 0, valread, client_fd;
	int counter = 0;
	struct sockaddr_in serv_addr;
	char buffer[1024];

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	    printf("client socket creation error\n");
	    exit(EXIT_FAILURE);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
	    printf("Invalid address/ Address not supported\n");
	    exit(EXIT_FAILURE);
	}

	if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
	    printf("Connection Failed\n");
	    exit(EXIT_FAILURE);
	}

	sprintf(buffer, "%d", ++counter);
	printf("client: %s\n", buffer);

	send(sock, buffer, strlen(buffer), 0);
	valread = read(sock, buffer, 1024);

	counter = atoi(buffer);
	printf("client: %s\n", buffer);

	close(client_fd);
}

int main( int argc, char *argv[] ) {
	pthread_t ponger_id, pinger_id;
	
	printf("Threads start\n");

	pthread_create(&ponger_id, NULL, ponger, NULL);
	pthread_create(&pinger_id, NULL, pinger, NULL);

	pthread_join(ponger_id, NULL);
	pthread_join(pinger_id, NULL);

	printf("Threads end\n");

	return 0;
}
