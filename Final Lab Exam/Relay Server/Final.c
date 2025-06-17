// final_server.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9002);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sockfd, 1);

    int client = accept(sockfd, NULL, NULL);

    char buffer[1024];
    int n = read(client, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';

    printf("Server C received: %s\n", buffer);

    close(client);
    close(sockfd);
    return 0;
}
