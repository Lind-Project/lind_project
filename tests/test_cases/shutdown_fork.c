/* Test if shutdown() would take longer to run in a multi-process program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	int server_fd, new_socket, client_fd; 
	int opt = 1, opt2 = 1;
	int dummy = 0;
	clock_t t;
	struct sockaddr_in address, serv_addr;
	int addrlen = sizeof(address);
	char buffer[32];

	int parent_to_child[2];
	
	// Open a pipe for syncing between parent and child process
	if (pipe(parent_to_child) < 0)
	{
		printf("Failed to initialize parent to child pipe: %n\n", strerror(errno));
		fflush(stdout);
		exit(EXIT_FAILURE);
	}

	// Create server socket, which we use to test shutdown
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("server socket failed: %s\n", strerror(errno));
		fflush(stdout);
		exit(EXIT_FAILURE);
	}


	if (fork() == 0) { // Child process
		close(parent_to_child[1]);

		// Create a client socket
		if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			printf("client socket failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Set client socket options
		if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &opt2, sizeof(opt2))) {
			printf("client setsockopt failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(5000);

		// Set the server address
		if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
			printf("client inet_pton failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Connect to server
		if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
			printf("client connection failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Blocking read pipe that continues when parent is about to read socket
		read(parent_to_child[0], &dummy, sizeof(dummy));
		
		// Wait for parent to start read socket
		sleep(1);

		/* shutdown */
		t = clock();
		shutdown(server_fd, SHUT_RDWR);
		t = clock() - t;
		printf("%lf\n", ((double)t) / CLOCKS_PER_SEC);
		fflush(stdout);
		/* shutdown */

		// Send something to let parent process continue
		send(client_fd, buffer, strlen(buffer), 0);

		close(server_fd);
		close(client_fd);
		close(parent_to_child[0]);

		exit(0);
	} else { // Parent process
		close(parent_to_child[0]);

		// Set server socket option
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
			printf("server setsockopt failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(5000);

		// Bind server socket to the address
		if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
			printf("server bind failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Start listening
		if (listen(server_fd, 3) < 0) {
			printf("server listen failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Receiving a new connection from child process
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
			printf("server accept failed: %s\n", strerror(errno));
			fflush(stdout);
			exit(EXIT_FAILURE);
		}

		// Tell child we'll call read() in the next step
		write(parent_to_child[1], &dummy, sizeof(dummy));

		/* The blocking read */
		read(new_socket, buffer, 32);

		close(server_fd);
		close(new_socket);
		close(parent_to_child[1]);

		wait(0);
		exit(0);
	}
}
