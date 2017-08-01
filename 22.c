#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
  int choice;
  char *string[]={"ls", "ps", "date", "goof"}; // goof can be replaced by any shell command
  printf("Which commands to run ? 1 ls\n 2 ps \n3 date\n 4 cat curremt file contents \n");
  scanf("%d",&choice);
  execlp(string[choice-1],string[choice-1],NULL);
  }
