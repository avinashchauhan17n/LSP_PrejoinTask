/* Write a program to print out	the last modified, last	accessed and last changed attributes of	an input file */
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <time.h>

#define st_atime st_atim.tv_sec      /* Backward compatibility Timestamp in nanoseconds*/
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)

int main(void) {

struct stat sb;  // the stat buffer

if(-1 == stat("foo.txt",&sb)) {
  handle_error("stat error");
}
  printf("%s \n",ctime(&sb.st_atime));
  printf("%s \n",ctime(&sb.st_mtime));
  printf("%s \n",ctime(&sb.st_ctime));

}
