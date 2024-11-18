#include "common.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int sockfd, client_sockfd, port;
  struct sockaddr_in server_addr, client_addr;
  socklen_t socklen;

  if (argc < 2) {
    char err_msg[256];
    snprintf(err_msg, sizeof(err_msg), "Usage: %s <port>\n", argv[0]);
    error(err_msg);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("Error opening socket");

  bzero((char *)&server_addr, sizeof(server_addr));
  port = atoi(argv[1]);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    error("Error binding socket");

  listen(sockfd, 5);

  socklen = sizeof(client_addr);
  client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &socklen);
  if (client_sockfd < 0)
    error("Error accepting connection");

  char buf[256];
  int n = read(client_sockfd, buf, 255);
  if (n < 0)
    error("Error reading from socket");

  buf[n] = '\0';
  printf("Client: %s\n", buf);

  char *msg = "Message received\n";
  if (write(client_sockfd, msg, strlen(msg)) < 0)
    error("Error writing to socket");

  close(client_sockfd);
  close(sockfd);
  return 0;
}
