#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(void) {

  pid_t parent,child;
  int status;

/* parent process */
  parent = getpid();
  if(-1 == (child=fork())) {
    printf("Child fork error %s\n",strerror(errno));
  }
  if(child) {
    printf("parent pid: %d \n",parent);
/* wait for child to complete */
    wait(&status);
    if(WIFEXITED(status)) {
      printf("child exited due to signal %d\n",WEXITSTATUS(status)); 
    }
    if(WIFSIGNALED(status)) {
      printf("exited due to signal %d\n",WTERMSIG(status));
    }
  }
  else {
    child=getpid();
    printf("Running chld pid status : %d \n",child);
    sleep(15);
    exit(3);
  }
  return 0;
}
