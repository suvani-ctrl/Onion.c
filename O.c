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
}
