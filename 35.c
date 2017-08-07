/*Modify	the	program	#34	that	connects	to	the	rot13	server by using	the	modern
way	of	populating	the	server	details	using	the	getaddinfo()	system	call.	Make
sure	the	code	is	completely	protocol	agnostic	such	that	if	the	rot13	server
changes	from	IPv4	to	IPv6,	the	client	is	able	to	connect	to	it. */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netdb.h>

#define ERROR(msg) printf(#msg"%s\n",strerror(errno));exit(0)
#define BUF_SIZE 1024

int main(void) {
  int sock;
  struct addrinfo hints;
  struct addrinfo *results, *rp;
  int count, retval, flag=0;
  char c;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC; /*validate both IPv4 and IPv6 */
  hints.ai_socktype = SOCK_STREAM; 

  if( (retval = getaddrinfo("localhost", "rot13", &hints, &results)) != 0) {
       ERROR("addres error");
  }

  rp = results;

  while (rp != NULL) {
    /* first create socket */
    if( (sock=socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) != -1) {
      /* if Success, then connect */
      if (connect(sock, (struct sockaddr *)rp->ai_addr, rp->ai_addrlen) != -1) {
          printf("....................connected to rot13:TCP.................");
          flag = 1;
          rp = NULL;
      }
      else {
        /* Unable to connect, close the socket connection */
          printf("Unable to connect, move to the next\n");
          rp = rp->ai_next;
          close(sock);
      }
    } else {
      /* Unable to create socket, move to next connection */
      printf("Unable to create socket, move to the next\n");
      rp = rp->ai_next;
      }
  }

  if (flag == 0) {
      ERROR("fail connect");
  }
  /* Free the results */
  freeaddrinfo(results);

  /* Handle Connection: */
  /* read from stdin, tx to server, rx from server, print to stdout */
  while(1) {
    if( (count = read(0, &c, 1)) == -1) {
      ERROR("read");
    }
    
    if (write(sock, &c, 1) == -1) {
        ERROR("write");
    }
    
    if( (count = read(sock, &c, 1)) == -1) {
        ERROR("read");
    }
    
    if (write(1, &c, 1) == -1) {
        ERROR("write");
    }
  }
  return EXIT_SUCCESS;
}
