#include "common.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int sockfd, port;
  struct sockaddr_in server_addr;
  struct hostent *server;
  char buf[256];

  if (argc < 3) {
    char err_msg[256];
    snprintf(err_msg, sizeof(err_msg), "Usage: %s <hostname> <port>\n",
             argv[0]);
    error(err_msg);
  }

  port = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("Error opening socket");

  server = gethostbyname(argv[1]);
  if (server == NULL) {
    error("Error, host not found");
  }

  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr,
        server->h_length);
  server_addr.sin_port = htons(port);

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    error("Error connecting");

  printf("Enter a message: ");
  bzero(buf, 256);
  fgets(buf, 255, stdin);

  if (write(sockfd, buf, strlen(buf)) < 0)
    error("Error writing to socket");

  bzero(buf, 256);
  if (read(sockfd, buf, 255) < 0)
    error("Error reading from socket");

  printf("Server: %s\n", buf);

  close(sockfd);
  return 0;
}
