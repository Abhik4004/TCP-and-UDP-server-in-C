// client.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverB;
    serverB.sin_family = AF_INET;
    serverB.sin_port = htons(9001);
    inet_pton(AF_INET, "127.0.0.1", &serverB.sin_addr);

    connect(sockfd, (struct sockaddr*)&serverB, sizeof(serverB));

    char *msg = "Hello from A to B to C!";
    write(sockfd, msg, strlen(msg));

    close(sockfd);
    return 0;
}
