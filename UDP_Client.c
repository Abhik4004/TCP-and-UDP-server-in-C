#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
  int sock_fd;
  struct sockaddr_in server_Addr;
  char buffer[100];
  socklen_t addrlen = sizeof(server_Addr);

  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

  server_Addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_Addr.sin_family = AF_INET;
  server_Addr.sin_port = htons(2100);

  while(1) {
    printf("[+] Enter your message: ");
    fgets(buffer, 100, stdin);

    sendto(sock_fd, buffer, 100, 0,(struct sockaddr *)&server_Addr, addrlen );
    bzero(buffer, 100);
    int n = recvfrom(sock_fd, buffer, 100, 0,(struct sockaddr *)&server_Addr, &addrlen );
    buffer[n] = '\0';
    printf("[+] Server: %s", buffer);
  }
  close(sock_fd);
  return 0;
}