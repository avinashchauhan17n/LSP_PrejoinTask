#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

struct data {
int id;
char name[80];
};

int main(void) {
  struct data *records;
  int fd;
  size_t fileSize;

/* open a file */
  if(-1 == (fd=open("dat",O_RDWR))) {
    printf("open error %s\n",strerror(errno));
    return EXIT_FAILURE;
  }

/* finding size of file */
  if(-1 == (fileSize=lseek(fd,0,SEEK_END))) {
  printf("size error %s\n",strerror(errno));
  return EXIT_FAILURE;
 }

/* copying a block of memory lets say 2nd record */
  records=(struct data*)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if(MAP_FAILED == records) {
    printf("mmap error %s\n",strerror(errno));
    return EXIT_FAILURE;
  }
  records[1].id=7;
  if (msync(records, fileSize, MS_SYNC) == -1) {
    printf("mmap errorgdfg %s\n",strerror(errno));
    return EXIT_FAILURE;
  }


}
