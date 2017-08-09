#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define ERROR(msg) printf(#msg"%s\n",strerror(errno));exit(0);

#define PORT 8000

/*MY ROT13 IMPLEMENTATION IN QUE 33 */
void rot13(char *input);

int main(void) {
  int sock, fd, readBytes=0;
  socklen_t clientLen;
  struct sockaddr_in server, client;
  char c;

  /* creating socket */
  if( (sock=socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      ERROR("socket");
  }

  /* Bind Socket to Port 8000 */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(PORT);

  if (bind(sock, (struct sockaddr *)&server, (socklen_t)sizeof(server)) == -1) {
      ERROR("bind");
  }

  /* Setup Listen Queue */
  if (listen(sock, 5) == -1) {
     ERROR("listen");
  }

  printf("listening on port............. %d\n", PORT);

  /* ignoring child generated signal to avoid zombiee */
  signal(SIGCHLD, SIG_IGN);

  while(1) {
    /* Accept Connections, blocks till connection is established */
    clientLen = sizeof(client);
    if( (fd=accept(sock, (struct sockaddr *)&client, (socklen_t *)&clientLen)) == -1) {
        ERROR("accept");
    }
    if (fork() == 0) {
      /* Child process */
      /* Close Socket Descriptor as its unused in child */
      close(sock);
      /* Handle Connection */
      printf("new connection from client: %d\n", client.sin_addr.s_addr);

      do {
       if ( (readBytes = read(fd, &c, 1)) == -1) {
          ERROR("read");
       }

       rot13(&c);

       if (write(fd, &c, readBytes) == -1) {
          ERROR("write");
       }
      } while(readBytes) ;

      printf("connection closed by client\n");

      close(fd);
      exit(EXIT_SUCCESS);
    } else {
      close(fd);
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

