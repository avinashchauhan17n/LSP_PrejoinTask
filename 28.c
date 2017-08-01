/* Write a program where you register a	signal	handler	using	the	signalaction()	
with	sa_flags=0	and	perform	a	read	operation	on	a	pipe.	Show	that	receiving	a	
signal,	stops	the	pipe	read	mid-way	and	is	unable	to	resume	it */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

void myhandler(int sigint); // handler function for signal

int main(void) {

/* mandatory steps used in handling signals */
  struct sigaction action;
  char buffer[1000];
  int bytesRead;
  int p[2];
  printf("Process id %d \n",getpid());
/*Handle SIGINT */
  action.sa_handler=myhandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags=0;
  sigaction(SIGINT,&action,NULL);
/*creating pipe */
  if(-1 == pipe(p)) {
    printf("Pipe errror %s \n",strerror(errno));  
  }
  while(1) {
/* blocking read as ther is no writer to pipe */
    if(-1 == (bytesRead=read(p[0],buffer,1000))) {
      printf("error read %s\n",strerror(errno));
    }
    printf("%d bytes, read input =%s\n",bytesRead,buffer);
  }
  return EXIT_SUCCESS;
}

void myhandler(int sigint)
{
printf("Interrupt is Handled using Handler\n");
}
