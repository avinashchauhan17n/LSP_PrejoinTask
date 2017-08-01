#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/times.h>
#include <fcntl.h>


/* child process gets its own copy of the stack and data segments at the time of the fork(), and it is able to modify variables in
these segments without affecting the parent. */
void Create_Process() {
  int i,retValue;	
  int fd;
/* opening a file */
  if(-1==(fd=open("abc.txt",O_CREAT|O_TRUNC|O_RDWR, 0666))) {
    printf("open error %s",strerror(errno));
  }
  for(i=0;i<10000000;i++) {
    if(-1 ==(retValue=write(fd,"hi hello",15))) {
      printf("write error %s ",strerror(errno));
    }
  }
  close(fd);
}

int main(void) {
  struct tms timeStatistics;
  clock_t startTime=clock();
  clock_t endTime;

  printf("Sysconf: %ld \n",sysconf(_SC_CLK_TCK));
  printf("Clock per second %ld \n",CLOCKS_PER_SEC);
  Create_Process();
  times(&timeStatistics);
/* printing all statistics as similar to time command in shell */

  printf("user time %ld\n",timeStatistics.tms_utime);
  printf("system time %ld\n",timeStatistics.tms_stime);
  printf("child user time %ld\n",timeStatistics.tms_cutime);
  printf("child system time %ld\n",timeStatistics.tms_cstime);
  endTime=clock();
  printf("Elapsed time %ld sec\n",(endTime-startTime)/CLOCKS_PER_SEC);
  printf("Time in CLOCKs PER SEC %ld\n",clock()/CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}
