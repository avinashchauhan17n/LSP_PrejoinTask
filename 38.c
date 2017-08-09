#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

#define ERROR(msg) printf(#msg"%s\n",strerror(errno));exit(0);

#define BPORT  8008  /* port for bradcasting */

int main(void) {

  int sock, count;
  struct sockaddr_in server, client;
  socklen_t clientAddrLen;
  int flag=1;
  char buff[1024];
  
/* create a socket */
  if( (sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
       ERROR("socket creation");
  }

/* setup socket to broadcast*/
  if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&flag, sizeof(flag)) == -1) {
      ERROR("setting socket failed\n");
  }
 /* setup socket to reuse port so that multiple process can bind */
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (char *)&flag, sizeof(flag)) == -1) {
      ERROR("socket setup for multiple reuse port failed");
  }
  /* Bind socket to UDP Broadcast Host Addr and Port */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(BPORT);

  if (bind(sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
      ERROR("bind");
  }

  /*forking a child process here to listen broadcast message*/
  if (fork() == 0) { /* child */
      while(1) {
      /* Receive Broadcast Messages */
        clientAddrLen = sizeof(struct sockaddr_in);
        if( (count = recvfrom(sock, buff, 1024, 0, (struct sockaddr*)&client, &clientAddrLen)) == -1) {
            ERROR("recvfrom");
        }
      /* Print them on the stdout */
        if (write(1, buff, count) == -1) {
            ERROR("write");
        }
      }
  } else {
    /* Parent */
    while(1) {
      /* Scan data from stdin */
      if( (count = read(0, buff, 1024)) == -1) {
           ERROR("read");
      }
      /* Broadcast the data */
      server.sin_family = AF_INET;
      server.sin_port = htons(BPORT);
      server.sin_addr.s_addr = 0xFFFFFFFF;
      if(sendto(sock, buff, count, 0, (struct sockaddr*)&server, sizeof(server)) == -1) {
         ERROR("sendto");
      }
    }
  }
  return EXIT_SUCCESS;
}
