/* Write	a	program	to	use	ctime()	and	strfmtime()  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/inotify.h>
#include <time.h>
#include <string.h>

int main (void) {

  time_t dateTime; 
  struct tm *info;
  char buffer[1000];

  dateTime=time(NULL);
  if(!dateTime) {
    printf("date time error %s \n",strerror(errno));
  }
  info = localtime(&dateTime);
/*custom formating date and time returned by system format */
  strftime(buffer,1000,"%R %A %e %B", info); 
  printf("ctime: %s\n",ctime(&dateTime)); 
  printf("Formatted date & time: %s\n", buffer );

  return EXIT_SUCCESS;
}
