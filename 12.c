#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#define EVENTMAX 100
#define FILESIZE NAME_MAX+1
#define handle_error(x) printf(#x"%s\n",strerror(errno))

int  main(void) {
  FILE *file;
  int notifyHandle;
  int i=0;
  char buffer[FILESIZE]; 
  
  /* creating watch handles to watch number of events */
  int watchHandles[EVENTMAX];
  char eventBuffer[EVENTMAX*sizeof(struct inotify_event) + FILESIZE];
  char *p;
  struct inotify_event *eventPtr;

  /* notifyHandle for watching file system events */
  if(-1 ==  (notifyHandle = inotify_init())) {
    handle_error("inotify_init()");
  }
  /* Open monitor.conf file */
  if(NULL == (file = fopen("monitor.conf", "r"))) {
    handle_error("monitor.conf fopen");
  }
	i=0;
  /* create individual watchHandles and add it to notifyHandle*/
  while(NULL != fgets(buffer, FILESIZE, file)) {
    /* Remove \n from the line read */
    buffer[strlen(buffer)-1] = '\0';
    if(-1 == (watchHandles[i++] = inotify_add_watch(notifyHandle, buffer, IN_DELETE_SELF | IN_MODIFY))) {
      handle_error(buffer);
    }
  }
  
  while(1) {
    if(-1 == (i = read(notifyHandle, eventBuffer, sizeof(eventBuffer)))) {
      handle_error("read notifyHandle");
    }    
    p = eventBuffer;
    while(p < eventBuffer+i) {
      eventPtr = (struct inotify_event *)p;
      if(eventPtr->mask & IN_MODIFY) {
        printf("Got modify event on filehandle: %d\n", eventPtr->wd);
      }
      if(eventPtr->mask & IN_DELETE_SELF) {
        printf("Got delete event on filehandle: %d\n", eventPtr->wd);
      }
      p += sizeof(struct inotify_event) + eventPtr->len;
    }
  }

  return EXIT_SUCCESS;
}
