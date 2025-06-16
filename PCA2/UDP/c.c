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

    while(1) {

        for(int i = 0; i < 2; i++) {
            printf("For %d:\t", i+1);
            scanf("%d", &buffer[i]);
            buffer[i] = htonl(buffer[i]);
        }

        buffer[2] = htonl(0);
        buffer[3] = htonl(0);

        sendto(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        printf("\n");

        recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddr, &addrlen);
        for(int i = 0; i < 4; i++) {
            buffer[i] = ntohl(buffer[i]);
            printf("%d\t", buffer[i]);
        }
    }
    
    return 0;
}