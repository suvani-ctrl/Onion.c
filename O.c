#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PROXY "127.0.0.1"
#define PROXYPORT 1234
#define USERNAME "onion"
#define reqsize sizeof(struct Proxy_Request)
#define ressize sizeof(struct Proxy_Response)

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct Proxy_Request {
    int8 vn;
    int8 CD;
    int16 Destination_Port;
    int32 Destination_IP;
    unsigned char userid[8]; 
};

struct Proxy_Response {
    int8 vn;
    int8 CD;
    int16 _;  
    int32 __;  
};

struct Proxy_Request *request(const char *dstip, const int dstport) {
    struct Proxy_Request *req = malloc(reqsize);
    if (req == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }

    req->vn = 4;
    req->CD = 1;
    req->Destination_Port = htons(dstport);
    req->Destination_IP = inet_addr(dstip);
    strncpy((char *)req->userid, USERNAME, 8);

    return req;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return -1;
    }

    char *host = argv[1];
    int port = atoi(argv[2]);

    int SocketFd;
    struct sockaddr_in sock;

    SocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketFd < 0) {
        perror("Socket Error!");
        return -1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(host);

    if (connect(SocketFd, (struct sockaddr *)&sock, sizeof(sock)) < 0) {
        perror("Connect Error");
        close(SocketFd);
        return -1;
    }

    printf("Connected to the Proxy\n");

    struct Proxy_Request *req = request(PROXY, PROXYPORT);
    if (req != NULL) {
        if (write(SocketFd, req, reqsize) < 0) {
            perror("Write Error");
            free(req);
            close(SocketFd);
            return -1;
        }
        free(req);
    }

    char buf[ressize];
    memset(buf, 0, ressize);

    if (read(SocketFd, buf, ressize) < 1) {
        perror("Read Error");
        close(SocketFd);
        return -1;
    }

    struct Proxy_Response *res = (struct Proxy_Response *)buf;

    int success = (res->CD == 90);
    if (!success) {
        fprintf(stderr, "Unable to traverse the proxy, error code: %d\n", res->CD);
        close(SocketFd);
        return -1;
    }

    printf("Successfully connected to the Proxy!\n");

    close(SocketFd);

    return 0;
}
