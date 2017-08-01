#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  if(argc <2) {
    printf("Insufficient arguements\n");
  }
  if(argc==2) {
    execlp(argv[1],argv[1],NULL);
  }
  if(argc == 3) {
    printf("ashish >");
    execlp(argv[1],argv[1],argv[2],NULL);
  }

}
