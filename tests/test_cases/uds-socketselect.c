#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

pthread_barrier_t closebarrier;
pthread_barrier_t syncbarrier;

#define SERVER_PATH "unix_sock.server"

void *client(void *v)
{
    int sock = 0, valread;
    struct sockaddr_un serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    long opt = 1;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SERVER_PATH);

    pthread_barrier_wait(&syncbarrier);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    sleep(0.1);
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    fflush(stdout);
    close(sock);
    pthread_barrier_wait(&closebarrier);
    return NULL;
}

void *server(void *v)
{
    int i, len, rc, on = 1;
    int listen_sd, max_sd, new_sd;
    int desc_ready, end_server = FALSE;
    int close_conn;
    char buffer[80];
    struct sockaddr_un server_sockaddr;
    struct timeval timeout;
    fd_set master_set, working_set;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));

    pthread_barrier_init(&closebarrier, NULL, 2);

    /* Create an AF_UNIX stream socket to receive incoming      */
    /* connections on                                            */

    listen_sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listen_sd < 0)
    {
        perror("socket() failed");
        exit(-1);
    }

    rc = ioctl(listen_sd, FIONBIO, (char *)&on);
    if (rc < 0)
    {
        perror("ioctl() failed");
        close(listen_sd);
        exit(-1);
    }

    /* Bind the socket                                           */
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
    unlink(SERVER_PATH);
    int addrlen = sizeof(server_sockaddr);

    rc = bind(listen_sd, (struct sockaddr *)&server_sockaddr, addrlen);
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

    /* Initialize the master fd_set                              */

    FD_ZERO(&master_set);
    max_sd = listen_sd;
    FD_SET(listen_sd, &master_set);

    /* Initialize the timeval struct to 2 seconds.  If no        */
    /* activity after 2 second this program will end.           */

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    pthread_barrier_wait(&syncbarrier);

    /* Loop waiting for incoming connects or for incoming data   */
    /* on any of the connected sockets.                          */

    do
    {
        /* Copy the master fd_set over to the working fd_set.     */
        memcpy(&working_set, &master_set, sizeof(master_set));

        /* Call select() and wait for it to complete.   */
        printf("Waiting on select()...\n");
        fflush(stdout);
        rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);

        /* Check to see if the select call failed.                */
        if (rc < 0)
        {
            perror("  select() failed");
            break;
        }

        /* Check to see if the time out expired.         */
        if (rc == 0)
        {
            printf("  select() timed out. End program.\n");
            break;
        }

        /* One or more descriptors are readable.  Need to         */
        /* determine which ones they are.                         */
        desc_ready = rc;
        for (i = 0; i <= max_sd && desc_ready > 0; ++i)
        {
            /* Check to see if this descriptor is ready            */
            if (FD_ISSET(i, &working_set))
            {

                /* A descriptor was found that was readable - one   */
                /* less has to be looked for.  This is being done   */
                /* so that we can stop looking at the working set   */
                /* once we have found all of the descriptors that   */
                /* were ready.                                      */

                desc_ready -= 1;

                /* Check to see if this is the listening socket     */

                if (i == listen_sd)
                {
                    printf("  Listening socket is readable\n");
                    fflush(stdout);

                    /* Accept all incoming connections that are      */
                    /* queued up on the listening socket before we   */
                    /* loop back and call select again.              */

                    do
                    {

                        /* Accept each incoming connection.  If       */
                        /* accept fails with EWOULDBLOCK, then we     */
                        /* have accepted all of them.  Any other      */
                        /* failure on accept will cause us to end the */
                        /* server.                                    */

                        new_sd = accept(listen_sd, NULL, NULL);
                        if (new_sd < 0)
                        {
                            if (errno != EWOULDBLOCK)
                            {
                                perror("  accept() failed");
                                end_server = TRUE;
                            }
                            break;
                        }

                        /* Add the new incoming connection to the     */
                        /* master read set                            */

                        printf("  New incoming connection - %d\n", new_sd);
                        fflush(stdout);
                        FD_SET(new_sd, &master_set);
                        if (new_sd > max_sd)
                            max_sd = new_sd;

                        /* Loop back up and accept another incoming   */
                        /* connection                                 */

                    } while (new_sd != -1);
                }

                /* This is not the listening socket, therefore an   */
                /* existing connection must be readable             */

                else
                {
                    printf("  Descriptor %d is readable\n", i);
                    fflush(stdout);
                    close_conn = FALSE;

                    /* Receive all incoming data on this socket      */
                    /* before we loop back and call select again.    */

                    do
                    {

                        /* Receive data on this connection until the  */
                        /* recv fails with EWOULDBLOCK.  If any other */
                        /* failure occurs, we will close the          */
                        /* connection.                                */

                        rc = recv(i, buffer, sizeof(buffer), 0);
                        if (rc < 0)
                        {
                            if (errno != EWOULDBLOCK)
                            {
                                perror("  recv() failed");
                                close_conn = TRUE;
                            }
                            break;
                        }

                        /* Check to see if the connection has been    */
                        /* closed by the client                       */

                        if (rc == 0)
                        {
                            printf("  Connection closed\n");
                            close_conn = TRUE;
                            break;
                        }

                        /* Data was received                          */

                        len = rc;
                        printf("  %d bytes received\n", len);
                        fflush(stdout);

                        /* Echo the data back to the client           */

                        rc = send(i, buffer, len, 0);
                        if (rc < 0)
                        {
                            perror("  send() failed");
                            close_conn = TRUE;
                            break;
                        }
                        pthread_barrier_wait(&closebarrier);

                    } while (TRUE);

                    /* If the close_conn flag was turned on, we need */
                    /* to clean up this active connection.  This     */
                    /* clean up process includes removing the        */
                    /* descriptor from the master set and            */
                    /* determining the new maximum descriptor value  */
                    /* based on the bits that are still turned on in */
                    /* the master set.                               */

                    if (close_conn)
                    {
                        close(i);
                        FD_CLR(i, &master_set);
                        if (i == max_sd)
                        {
                            while (FD_ISSET(max_sd, &master_set) == FALSE)
                                max_sd -= 1;
                        }
                    }
                } /* End of existing connection is readable */
            }     /* End of if (FD_ISSET(i, &working_set)) */
        }         /* End of loop through selectable descriptors */

    } while (end_server == FALSE);

    /* Clean up all of the sockets that are open                 */

    for (i = 0; i <= max_sd; ++i)
    {
        if (FD_ISSET(i, &master_set))
            close(i);
    }
}

int main()
{
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