#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock_fd;
    struct sockaddr_in serveraddr;
    char buffer[1024];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2100);
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);

    connect(sock_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("[+] Connected to server\n");

    while (1) {
        printf("You: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) break;

        send(sock_fd, buffer, strlen(buffer), 0);

        int n = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0) break;

        buffer[n] = '\0';
        printf("Server: %s", buffer);
    }

    close(sock_fd);
    return 0;
}
