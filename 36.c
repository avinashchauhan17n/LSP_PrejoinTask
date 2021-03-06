/* Rewrite	program	#33	to	work	with	IPv6,	and	test	program	35	is	working	with
IPv6	version	of	the	server. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define ERROR(msg) printf(#msg"%s\n",strerror(errno));exit(0)

#define PORT 8000
#define BUF_SIZE 1024

void rot13(char *);
void connectionHandler(int fd);

int main(void) {

  int sock, fd;
  socklen_t clientLen;
  struct sockaddr_in client;
  struct sockaddr_in6 server6;
  char c;
  int readBytes;

  /* Creating a socket */
  if( (sock = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
       ERROR("socket");
  }

  /* Binding Socket to Port 8000 */
  server6.sin6_family = AF_INET6;        // IPV6 family
  server6.sin6_addr = in6addr_any;
  server6.sin6_port = htons(PORT);

  if (bind(sock, (struct sockaddr *)&server6, (socklen_t)sizeof(server6)) == -1) {
     ERROR("bind");
  }

  /* Setup Listen Queue */
  if (listen(sock, 5) == -1) {
     ERROR("listen");
  }
  printf("listening on port........ %d\n", PORT);

  while(1) {

    /* Accept Connections, blocks till connection is established */
    clientLen = sizeof(client);
    if( (fd = accept(sock, (struct sockaddr *)&client, (socklen_t *)&clientLen)) == -1) {
         ERROR("accept");
    }

    /* Handling Connection */
    printf("New connection from client*****: %d\n", client.sin_addr.s_addr);
    do {

       if ( (readBytes = read(fd, &c, 1)) == -1) {
          ERROR("read");
       }
       rot13(&c);
       if (write(fd, &c, readBytes) == -1) {
          ERROR("write");
      }
    } while(readBytes) ;

    /* Very important to close file descriptors */
    printf("Client closed connection, so server closing connection\n");
    close(fd);
  }

  return EXIT_SUCCESS;
}

void rot13(char *input) {

  char token[3] = {' ', '\r', '\n'};
  /* sending back CR and NL */
  if (*input == token[0]) {
      *input = token[0];
  }

  else if (*input == token[1]) {
          *input = token[1];
  }

  else if (*input == token[2]) {
          *input = token[2];
  /* rotating alphabets both smaal and upper case */
  } else {
	if ( (*input <= 'm') && (*input >= 'a')) {
        *input = *input+13;
        } else {
          *input = *input-13;
          }
    }
}

