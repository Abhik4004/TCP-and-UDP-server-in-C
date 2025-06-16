#include "common.h"

int main() {
    int sock_fd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrlen = sizeof(clientAddr);

    int buffer[4];

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(3000);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock_fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    while(1) {
        recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &addrlen);

        for(int i = 0; i < 4; i++) {
            buffer[i] = ntohl(buffer[i]);
            printf("%d\t", buffer[i]);
        }
        printf("\n");

        int a = buffer[0];
        int b = buffer[1];

        buffer[1] = a + b;
        buffer[0] = a - b;
        buffer[2] = (b != 0) ? a/b : 0;
        buffer[3] = a * b;

        for(int i = 0; i < 4; i++) buffer[i] = htonl(buffer[i]);
        sendto(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, addrlen);
        printf("\n");
    }
    
    return 0;
}