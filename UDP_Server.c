#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
  int sock_fd;
  struct sockaddr_in server_Addr, client_Addr;
  socklen_t addrlen = sizeof(client_Addr);
  char buffer[100];

  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

  server_Addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_Addr.sin_family = AF_INET;
  server_Addr.sin_port = htons(2100);

  bind(sock_fd, (struct sockaddr *)&server_Addr, sizeof(server_Addr));
  printf("[+] Server running on port 2100.....");

  while(1) {
    int n = recvfrom(sock_fd, buffer, 100, 0, (struct sockaddr *)&client_Addr, &addrlen);
    printf("[+] Client Msg: %s", buffer);
    buffer[n] = '\0';
    bzero(buffer, 0);

    printf("Enter your message: ");
    fgets(buffer, 100, stdin);
    sendto(sock_fd, buffer, 100, 0, (struct sockaddr *)&client_Addr, addrlen);
  }

  close(sock_fd);
  return 0;
};