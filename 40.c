#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define error(msg) \
        printf(#msg"%s\n",strerror(errno))

#define PORT 8000

int read_write(char * c, int fd);
void rot13(char *input);

int main()
{
  int sock,fd;
  fd_set fullclientlist, activeclientlist;
  socklen_t clientlen;
  struct sockaddr_in server, client;
  int i;
  char c;

  FD_ZERO(&activeclientlist);
  FD_ZERO(&fullclientlist);

  /*  creating a socket */
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    error("socket");
  }
  /* setting parameters for binding */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(PORT);

  /* binding the socket */
  if( (bind(sock, (struct sockaddr *)&server, sizeof(server))) == -1) {
    error("binding error");
  }
  /* listening */
  if (listen(sock, 5) == -1) {
    printf("Waiting to connect.................\n");
  }

  FD_SET(sock, &fullclientlist);

  while(1) {
    /* duplicate the full client list as select will overwrite it */
    memcpy(&activeclientlist, &fullclientlist, sizeof(fullclientlist));
    /* blocks till any connection is ready OR established */
    select(FD_SETSIZE, &activeclientlist, NULL, NULL, NULL);
    /* First check sock descriptor, and accept the connection */
    if (FD_ISSET(sock, &activeclientlist)) {
      clientlen = sizeof(client);
      if( (fd=accept(sock, (struct sockaddr *)&client, (socklen_t *)&clientlen)) == -1) {
        error("accept");
      }
        /* Add fd to the fullClientList to keep listening on it */
    FD_SET(fd, &fullclientlist);
    printf("Got new connection from client: %d\n", client.sin_addr.s_addr);

    }
    /* Handle All Other Client Connections */
    /* ignore stdin, stdout, stderr and sock */
    for(i=3; i<FD_SETSIZE; i++) {
      if(i != sock) {
        if(FD_ISSET(i, &activeclientlist)) {
          if(read_write(&c,i) == -1) {
            /* connection closed OR error so stop monitoring this */
            /* Very important to close file descriptors */
            printf("Client closed connection\n");
            close(i);
            FD_CLR(i, &fullclientlist);
          }
        }
      }
    }
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

int read_write(char *c , int fd) {

  int readBytes=0;

  if ( (readBytes = read(fd, c, 1)) < 1) {
    printf("Client closed connection, so server closing connection\n");
    return -1;
  }
  rot13(c);
  if (write(fd, c, readBytes) < 1) {
    return -1;
  }
  return 0;
}
