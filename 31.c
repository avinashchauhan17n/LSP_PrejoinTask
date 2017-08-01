#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
 
#define handle_error(x) printf(#x"%s\n",strerror(errno))

int count;
char val;

void sigalrmHandler(int sig);

int main(void) {
  struct sigaction action;
  int retValue;
  char buffer[200];
  printf("Process id=%d\n", getpid());

  /* Handle SIGINT */
  action.sa_handler = sigalrmHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0; /* To ensure the blocking read times out */
  sigaction(SIGALRM, &action, NULL);

  /* user input taken continous simultaneosly monitoring signalalarm */
  while(1) {
    printf("Write no. ");
    fflush(stdout); // displaying to terminal */
    alarm(10); /* timeout */
    retValue = read(0, &buffer, 200);
    alarm(0); /* clear the timeout */
    if(-1 == retValue) {
      printf("timed out!\n");
    } 
    else {
      printf("Number is = %d\n", atoi(buffer));
    }
  }
  return EXIT_SUCCESS;
}
void sigalrmHandler(int sig) {
  /* Do nothing */
  printf("\nMy test message\n");
}
