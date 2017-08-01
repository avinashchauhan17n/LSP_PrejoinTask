#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
 
void sigintHandler(int sig);

int main(void) {
  struct sigaction action;
  int bytesRead;
  char buffer[10000];
  int p[2];

  printf("Pid=%d\n", getpid());

  /* Handle SIGINT */
  action.sa_handler = sigintHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;
  /*action.sa_flags = 0;*/
  sigaction(SIGINT, &action, NULL);
  
  if(pipe(p) == -1) {
    printf("pipe error %s\n",strerror(errno));
  }
  while(1) {
    /* Blocking read as there is no writer to the pipe */
    if( (bytesRead=read(p[0], buffer, 1000)) == -1) {
      /*handle_error("read");*/
      /* ignore error for demo */
    }
    printf("got %d number of bytes, read input = %s\n", bytesRead, buffer);
  }
  return EXIT_SUCCESS;
}

void sigintHandler(int sig) {
  printf("test message \n"); // always put \n handle interrupt with care 
}

