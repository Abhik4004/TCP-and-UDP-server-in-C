#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
  int sock_fd, comm_fd;
  struct sockaddr_in server_addr;
  char buffer[100];

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(2100);

  bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  listen(sock_fd, 5);
  printf("[+] Server is running on port 2100....");
  comm_fd = accept(sock_fd, (struct sockaddr *)NULL, NULL);

  while(1) {
    recv(comm_fd, buffer, 100, 0);
    printf("[+] client msg : %s", buffer);

    // if (strcmp(buffer, "EXIT") == 0) break;

    bzero(buffer, 0);

    printf("[+] Enter server response: ");
    fgets(buffer, 100, stdin);
    send(comm_fd, buffer, 100, 0);
  }

  close(sock_fd);
  close(comm_fd);
  return 0;

}