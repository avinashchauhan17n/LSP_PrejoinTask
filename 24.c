#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(void) {

  pid_t child;
  child=fork();
  int p[2];
/* creating pipe */
  if(-1 == pipe(p)) {
    printf("Pipe creation error \n");
  }
/* printing error if child process not created */
  if(child<0) {
    printf("fork error %s \n",strerror(errno));
  }
/* child process */
  else if(child==0) {
    printf("Hello I am the child process and pid is %d\n",getpid());
/*enabling standard o/p that is write to pipe */
    if(-1 == dup2(p[1],1)) {
      printf("child process pipe creation error stdin %s \n",strerror(errno));
    }
/* closing input side of pipe */
    close(p[0]);
    execlp("sort","sort","-r",NULL);
  }
/*parent process*/

  else {        
    printf("I m the parent process and my pid is %d\n",getpid());
/*connect p[0] to std in and close p[1] */
    if(-1 == dup2(p[0],0)) {
      printf("parent process pipe creation error stdin %s \n",strerror(errno));
    }
/* closing o/p of pipe */
  close(p[1]);
  execlp("ls","ls",NULL); 
  }
} 
