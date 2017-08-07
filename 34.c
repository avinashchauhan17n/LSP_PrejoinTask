/* Write	a	client	program	that	connects	to	the	rot13	server	(update	/etc/services
file	so	that	the	getservbyname()	can	be	called)	and	open	two	instances	of	the
client	to	fiddle	with	concurrent	connections.	You	should	see	that	one	client	is
blocked	until	one	client	terminates	its	connection. */


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>

#define ERROR(msg) printf(#msg"%s\n",strerror(errno))

int main(void) {

  /* local variables declaration */
  int sock,count;
  struct servent *serviceInfo;
  struct hostent *hostInfo;
  struct sockaddr_in server;
  char c;

  /*Get server Information */
  serviceInfo = getservbyname("rot13", "tcp");
  hostInfo = gethostbyname("localhost");

  /* setting sockaddr for connect */
  server.sin_family = AF_INET;
  memcpy(&server.sin_addr, hostInfo->h_addr, hostInfo->h_length);
  server.sin_port = serviceInfo->s_port;

  /* socket creation */
  if( (sock=socket(AF_INET,SOCK_STREAM,0)) == -1) {
      ERROR("socket creation error");
  }

  /* connect to server */
  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
      ERROR("connect");
  }

  /* handle connection */
  while(1) {

    if( (count = read(0, &c, 1)) == -1 ) {
        ERROR("read");
    }

    if (write(sock, &c, 1) == -1 ) {
        ERROR("write");
    }

    if( (count = read(sock, &c, 1)) == -1) {
        ERROR("read");
    }

    if (write(1, &c, count) == -1) {
        ERROR("write");
    }

  }

return EXIT_SUCCESS;

}
