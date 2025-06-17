#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(clientaddr);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(2100);

    bind(server_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(server_fd, 5);

    printf("[+] Server listening on port 2100...\n");

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&clientaddr, &addrlen);

        // Print connected client info
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientaddr.sin_addr), clientIP, INET_ADDRSTRLEN);
        int clientPort = ntohs(clientaddr.sin_port);
        printf("[+] Client connected: IP %s, Port %d\n", clientIP, clientPort);

        if (fork() == 0) {  // Child process
            close(server_fd);  // Child closes listening socket

            while (1) {
                int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
                if (n <= 0) break;  // Client disconnected or error

                buffer[n] = '\0';  // Null-terminate received string
                printf("Client (%s:%d) says: %s", clientIP, clientPort, buffer);

                // Echo message back to client
                send(client_fd, buffer, n, 0);
            }

            close(client_fd);
            printf("[+] Client disconnected: IP %s, Port %d\n", clientIP, clientPort);
            exit(0);  // Terminate child process
        }

        close(client_fd);  // Parent closes client socket
    }

    close(server_fd);
    return 0;
}
