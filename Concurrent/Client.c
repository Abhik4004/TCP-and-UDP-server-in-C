#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  int socket_fd;
  struct sockaddr_in serveraddr;
  socklen_t addrlen = sizeof(serveraddr);
  int buffer[2], result;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  printf("[+] Socket_Bind Sucessfull.....\n");

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(2100);


  connect(socket_fd, (struct sockaddr *)&serveraddr, addrlen);

  while(1) {
    printf("Enter no 1: ");
    scanf("%d", &buffer[0]);

    printf("Enter no 2: ");
    scanf("%d", &buffer[1]);

    buffer[0] = htonl(buffer[0]);
    buffer[1] = htonl(buffer[1]);

    send(socket_fd, &buffer, sizeof(buffer), 0);

    recv(socket_fd, &result, sizeof(result), 0);
    result = ntohl(result);

    printf("GCD is %d\n", result);
  } 
  return 0;
}