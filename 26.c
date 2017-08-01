#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
int main(void) {
  int i;

  for(i=0; i<32; i++) {
    printf("%d.%s\n", i, strsignal(i));
  }
  return EXIT_SUCCESS;
}
