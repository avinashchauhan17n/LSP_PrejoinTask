//14. Write	a	program	that	prints	out	the	entire	environment	for	the	process..

#define _GNU_SOURCE   
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
 

extern char **environ;   // The variable environ points to an array of pointers to strings called the "environment"

int main(int argc, char *argv[]) {
  char **p;
  for(p=environ; *p != NULL; p++) {
    printf("%s\n", *p);
  }
  return EXIT_SUCCESS;
}
