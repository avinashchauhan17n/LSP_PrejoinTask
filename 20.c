#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
 
int main(void) {
  pid_t parent, child;
  int i;

  /* Parent process */
  parent=getpid();
  if(-1 == (child=fork())) {
    printf("Error %s \n",strerror(errno));
  }
/* parent process */  
  if(child) {
    for(i=0;i<10000;i++) {
      printf("inside parent %d, waitin for child %d\n", parent, child);
    }
  } else {
    /* Child process */
    child=getpid();
    for(i=0;i<10000;i++) {
      printf("inside Child %d, forked from parent %d\n", child, parent);
    }
  }
  return EXIT_SUCCESS;
}

