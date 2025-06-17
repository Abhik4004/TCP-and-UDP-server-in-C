// relay_server.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9001);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listenfd, 1);

    int clientfd = accept(listenfd, NULL, NULL);

    char buffer[1024];
    int n = read(clientfd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';

    // Connect to final server C
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverC;
    serverC.sin_family = AF_INET;
    serverC.sin_port = htons(9002);
    inet_pton(AF_INET, "127.0.0.1", &serverC.sin_addr);

    connect(sockfd, (struct sockaddr*)&serverC, sizeof(serverC));

    // Forward data to C
    write(sockfd, buffer, n);

    close(sockfd);
    close(clientfd);
    close(listenfd);
    return 0;
}
