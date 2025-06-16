#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int gcd(int a, int b) {
  if(a == 0 || b == 0) return 0;
  int min = (a < b) ? a : b;

  while(1) {
    if(a % min == 0 && b % min == 0) break;
    min--;
  }
  return min;
}

int main() {
  int socket_fd, client_fd;
  struct sockaddr_in serveraddr;
  socklen_t addrlen = sizeof(serveraddr);
  int buffer[2];

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  printf("[+] Socket_Bind Sucessfull.....\n");

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(2100);

  bind(socket_fd, (struct sockaddr *)&serveraddr, addrlen);
  printf("[+] Bind successfull...\n");

  listen(socket_fd, 5);
  printf("[+] Server is listening on port 2100.....\n");

  client_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL);

  while(1) {
    recv(client_fd, buffer, 100, 0);  
    int num1 = ntohl(buffer[0]);
    int num2 = ntohl(buffer[1]);
    printf("Num 1 -> %d and Num 2 -> %d\n", num1, num2);

    int num3 = gcd(num1, num2);
    printf("LCM is %d\n", num3);
    num3 = htonl(num3);

    send(client_fd, &num3, sizeof(num3), 0);

    if(num1 == 0 && num2 == 0) break;
  } 
  close(socket_fd);
  close(client_fd);
  return 0;
}