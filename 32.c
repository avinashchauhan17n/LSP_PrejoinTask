#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ERROR(msg) printf(#msg":%s\n",strerror(errno))
#define PORT 8000
#define BUF_SIZE 1024

int main() {
  /* creating a socket */
  //int socket(int domain, int type, int protocol);
    int sock,fd;
    socklen_t clientLen;
    struct sockaddr_in server, client;
    char buffer[BUF_SIZE];
    int retValue;

    if(-1 == (sock=socket(AF_INET,SOCK_STREAM,0))) {
      ERROR("socket creation");
      return EXIT_FAILURE;
    }

    /* bind socket to PORT 8000*/
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if(-1 == bind(sock, (struct sockaddr *)&server, sizeof(server))) {
      ERROR("bind error");
    }

    /* LISTEN queue */
    if(-1 == (listen(sock ,5))) {
      ERROR("LISTEN ERROR");
    }
    printf("lISTENING ON PORT...... %d\n",PORT);
      /* accepts connection , blocks till connection is established */
      while(1) {
      /* accepting the connection on establishment */
        clientLen = sizeof(client);
        if(-1 == (fd=accept(sock, (struct sockaddr *)&client, (socklen_t *)&clientLen))) {
          ERROR("LIST ERROR");
        }
        /*Handle connection once connection established */
        printf("got new connection from client %d\n",client.sin_addr.s_addr);

        /* reading input from buffer */
        while( (retValue = (read(fd,buffer,BUF_SIZE)))> 0) {
                write(fd,buffer,retValue);
        }
        close(fd);
        printf("Closing connection...............\n");

      }
      return EXIT_SUCCESS;
}
