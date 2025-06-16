#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int client_fd, server_fd;
    struct sockaddr_in serverAddr;
    int buffer[4];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(3000);

    bind(server_fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(server_fd, 5);

    client_fd = accept(server_fd, NULL, NULL);
    printf("[+] Client Connected\n");

    while (1) {
        recv(client_fd, buffer, sizeof(buffer), 0);

        for (int i = 0; i < 4; i++) {
            buffer[i] = ntohl(buffer[i]);
            printf("%d\t", buffer[i]);
        }
        printf("\n");

        int a = buffer[0];
        int b = buffer[1];

        buffer[0] = a + b;
        buffer[1] = a - b;
        buffer[2] = (b != 0) ? (a / b) : 0;  // Avoid division by zero
        buffer[3] = a * b;

        for (int i = 0; i < 4; i++) buffer[i] = htonl(buffer[i]);

        send(client_fd, buffer, sizeof(buffer), 0);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
