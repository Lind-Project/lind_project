// Taken from http://osr507doc.sco.com/en/netguide/dusockD.socketpairs_codetext.html and modified

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
    int sockets[2], child;
    char buf[1024];


    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) {
        perror("opening stream socket pair");
        exit(1);
    }
    
    printf("Done!");

    return 0;
}