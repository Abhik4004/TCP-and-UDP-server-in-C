#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int socket_fd;
  struct sockaddr_in serveraddr;
  int buffer[2], result;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(2100);

  connect(socket_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  while(1) {
    printf("Enter Num1 : ");
    scanf("%d", &buffer[0]);
    printf("Enter Num2 : ");
    scanf("%d", &buffer[1]);
    buffer[0] = htonl(buffer[0]);
    buffer[1] = htonl(buffer[1]);
    send(socket_fd, buffer, sizeof(buffer), 0);

    int result;
    recv(socket_fd, &result, sizeof(result), 0);
    printf("Received %d ", ntohl(result));  
  } 
  return 0;
}