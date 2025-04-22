#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
  int sock_fd;
  struct sockaddr_in server_addr;
  char buffer[100];

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(2100);

  connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  printf("[+] Connection established \n");

  while(1) {
    printf("Enter your message: \n");
    fgets(buffer, 100, stdin);

    send(sock_fd, buffer, 100, 0);
    bzero(buffer, 0);
    recv(sock_fd, buffer, 100, 0);
    printf("Recieved from Server: %s", buffer);
    bzero(buffer, 0);

    // if(strcmp(buffer, "EXIT") == 0) break;
  }
  close(sock_fd);
  return 0;
}