#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
int main() {
    //https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/UDPSockets.html
    struct DnsHeader {
        uint16_t xid;
        uint16_t flags;
        uint16_t qdcount;
        uint16_t ancount;
        uint16_t nscount;
        uint16_t arcount;
    };

    /* Structure of the bytes for an IPv4 answer */
    struct DnsRecordAT {
        uint16_t compression;
        uint16_t typ;
        uint16_t clas;
        uint32_t ttl;
        uint16_t length;
        struct in_addr addr;
    } __attribute__((packed));

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("is sockfd valid? %s\n", sockfd >=0 ? "yes" : "no");

    struct DnsHeader dnsh;
    dnsh.xid = htons(0x1234);
    dnsh.flags = htons(0x0100);
    dnsh.qdcount = htons(0x0001);
    dnsh.ancount = 0;
    dnsh.nscount = 0;
    dnsh.arcount = 0;

    //specify payload information for dns request
    char* hostname = "\13engineering\03nyu\03edu\0";//numbers signify how many characters until next dot
    uint16_t dnstype = htons(1);
    uint16_t dnsclass = htons(1);

    //construct packet
    int packetlen = sizeof(struct DnsHeader) + strlen(hostname) + 1 + 2 + 2;
    char packvla[packetlen];
    int packetlenleft = packetlen;

    memcpy(packvla, &dnsh, sizeof(struct DnsHeader));
    packetlenleft -= sizeof(struct DnsHeader);
    memcpy(packvla + packetlen - packetlenleft, hostname, strlen(hostname) + 1);
    packetlenleft -= strlen(hostname) + 1;
    memcpy(packvla + packetlen - packetlenleft, &dnstype, 2);
    packetlenleft -= 2;
    memcpy(packvla + packetlen - packetlenleft, &dnsclass, 2);
    packetlenleft -= 2;
    assert(packetlenleft == 0);

    struct sockaddr_in sad;
    sad.sin_family = AF_INET;
    sad.sin_port = htons(53);
    inet_aton("208.67.222.222", &sad.sin_addr);

    int slen = sendto(sockfd, packvla, packetlen, 0, (struct sockaddr*) &sad, sizeof(sad));
    printf("%d is the length sent\n", slen);

    char dnsresp[512];

    int rlen = recvfrom(sockfd, dnsresp, 512, 0, NULL, NULL);
    printf("%d is the length recieved\n", rlen);

    //extract packet header
    const struct DnsHeader* rdnsh = (struct DnsHeader*) dnsresp;

    assert(!(ntohs(rdnsh->flags) & 0xf));

    //skip over the name
    char* nameptr = sizeof(struct DnsHeader) + dnsresp;

    while(*nameptr != 0) {
        nameptr += *nameptr + 1;
    }

    //next we need to skip the null byte, qtype, and qclass to extract the main response payload
    struct DnsRecordAT* recordptr = (struct DnsRecordAT*) (nameptr + 5);
    char* dnsresponse_addr = inet_ntoa(recordptr->addr);
    printf("the dns lookup yields the ip address: %s\n", dnsresponse_addr);
    return 0;
}

