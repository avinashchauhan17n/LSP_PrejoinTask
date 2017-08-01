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

#define handle_error(x) printf(#x"%s\n",strerror(errno))

int  main(void) {
  FILE *file;
  int notifyHandle;
  int i=0;

  /* Linux specified max filename is: NAME_MAX */
  char line[NAME_MAX+1]; 

  /* Handle 100 events at one go      */
  int watchHandles[100];
  char eventBuffer[100*sizeof(struct inotify_event) + NAME_MAX+1];
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

  /* create individual watchHandles and add it to notifyHandle*/
  while(fgets(line, NAME_MAX+1, file) != NULL) {
    /* Remove \n from the line read */
    line[strlen(line)-1] = '\0';
    if( (watchHandles[i++] = inotify_add_watch(notifyHandle, line, IN_DELETE_SELF | IN_MODIFY)) == -1) {
      handle_error(line);
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
