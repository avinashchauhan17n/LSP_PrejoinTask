/* Write a simple program that spawns a thread, prints that it is in the thread, sleeps for 1000seconds and returns exit code 99.
The parent waits for the thread to complete, and prints out the child’s exit code.
Examine the output of ps: ps –eLF | egrep ‘UID|prog41’ – notice the LWP = light weight process and contains the details of the thread.*/
                                
                                /* Note plz compile in gcc using gcc -pthread 41.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#define error(msg) printf(#msg"%s\n",strerror(errno));exit(0)

void *child_thread(void *args);

int main(void) {

  int exitstatus, retValue;
  pthread_t child;
  /* creating a child using pthread */
  if( (retValue = pthread_create(&child, NULL, child_thread, "hello this is program 41")) != 0) {
    error("unable to create pthread");
  }

  printf("I m in parent thread\n");
  pthread_join(child, (void **)&exitstatus);
  printf("child exited with status number %d \n", exitstatus);

  return EXIT_SUCCESS;
}

void *child_thread(void *args) {

  printf("i m in child thread, %s \n ", (char*)args);
  sleep(20);

  return ((void *)10);
}




