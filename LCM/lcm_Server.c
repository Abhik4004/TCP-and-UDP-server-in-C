#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int lcm (int a, int b) {
  int max = (a > b) ? a : b;
  while(1) {
    if(max % a == 0 && max % b == 0) break;
    ++max;
  }
  return max;
}

int main() {
  int socket_fd, client_fd;
  struct sockaddr_in serveraddr;
  int buffer[2], result;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(2100);

  bind(socket_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

  listen(socket_fd, 5);

  client_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL);
  while(1) {
    recv(client_fd, buffer, sizeof(buffer), 0);
    int num1 = ntohl(buffer[0]);
    int num2 = ntohl(buffer[1]);

    printf("Received %d and %d", num1, num2);

    int num3 = htonl(lcm(num1, num2));
    send(client_fd, &num3, sizeof(num3), 0);
  } 
  return 0;
}