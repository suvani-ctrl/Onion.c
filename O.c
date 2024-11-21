#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    char *host;
    int port;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return -1;
    }

    host = argv[1];
    port = atoi(argv[2]);

    typedef unsigned char int8;
    typedef unsigned short int int16;
    typedef unsigned int int32;

    struct Proxy_Request
    {
        int8 vn;
        int8 CD;
        int16 Destination_Port;
        int32 Destination_IP;
        unsigned char userid[8];
    };

    struct Proxy_Response
    {
        int8 vn;
        int8 CD;
        int16 _;  
        int32 __; 
    };

    typedef struct Proxy_Request Req;
    typedef struct Proxy_Response Resp;

    int SocketFd;
    struct sockaddr_in sock;

    SocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketFd < 0)
    {
        perror("Socket Error!");
        return -1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(host);

    if (connect(SocketFd, (struct sockaddr *)&sock, sizeof(sock)) < 0)
    {
        perror("connect");
        return -1;
    }
    printf("Connected To The Proxy\n");
    close(SocketFd);

//chech here pls 
    Req *request(const char *dstip, const int dstport)
    {
        Req *req;
        req = malloc(reqsize);
        req -> vn = 4; // -> is basically same as . format but when were using pointe rto a struct we use it !
        req -> cd = 1;
        req -> Destination_Port = htons(1);
        req -> Destination_IP = inet_addr(Destination_IP);

    }
//here 

    return 0;
}
