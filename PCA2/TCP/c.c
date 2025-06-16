#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int sock_fd;
    struct sockaddr_in serverAddr;
    int buffer[4];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(3000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(sock_fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    printf("[+] Connection established....\n");

    while (1) {
        printf("Enter 2 numbers:\n");
        for (int i = 0; i < 2; i++) {
            printf("Number %d: ", i + 1);
            scanf("%d", &buffer[i]);
        }

        // Zero out remaining buffer elements (optional)
        buffer[2] = 0;
        buffer[3] = 0;

        for (int i = 0; i < 4; i++) buffer[i] = htonl(buffer[i]);

        send(sock_fd, buffer, sizeof(buffer), 0);

        recv(sock_fd, buffer, sizeof(buffer), 0);

        printf("Results:\n");
        for (int i = 0; i < 4; i++) {
            printf("%d\t", ntohl(buffer[i]));
        }
        printf("\n");
    }

    close(sock_fd);
    return 0;
}
