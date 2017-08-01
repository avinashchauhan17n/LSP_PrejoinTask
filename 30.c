#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#define handle_error(x) printf(#x"%s",strerror(errno)) 
int count;
char value;

void sighupHandler(int sig); // signal handler function 

int main(int argc, char *argv[]) {
  sigset_t sigmask;
  struct sigaction action;
  int i;

  printf("Process id=%d\n", getpid());

/* Handle SIGINT */
  action.sa_handler = sighupHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;
  sigaction(SIGHUP, &action, NULL);
/* Handle sigmask */
  sigemptyset(&sigmask);
  sigaddset(&sigmask, SIGHUP);
/* executing signal handler function and passing arguement aas 1 which denotes the SIG1 = SIGHUP(re reading your conf file*/
  sighupHandler(1);
  while(1) {
    sleep(1);
    sigprocmask(SIG_BLOCK, &sigmask, NULL);
    for(i=0; i<count; i++) {
      printf("%c", value);
    }
    sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
    printf("\n");
  }
  return EXIT_SUCCESS;
}

void sighupHandler(int sig) {
  FILE *file;
  if(NULL == (file=fopen("reconfigure.conf", "r"))) {
    handle_error("fopen");
  }
  if(fscanf(file, "%c %d\n", &value, &count)) {
    if(ferror(file)) {
      handle_error("fscanf");
    }
  }
  fclose(file);
  return;
}
