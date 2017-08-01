/* program	to	measure	the	time	taken	by	a	process	using	sysconf(),	times()	and	clock() */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void) {

  pid_t parent,child;
/* creating child process by fork command */
  if(-1 == (child=fork())) {
    printf("error %s \n",strerror(errno));
  }
/*checking for parent process */
  if(child) {
    parent=getpid();
    printf("In parent %d",parent);
  }
  else {               // child process
    child = getpid();
    printf("In child %d\n",child);
  }

  return EXIT_SUCCESS;
}
