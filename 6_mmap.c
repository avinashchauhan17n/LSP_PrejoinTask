/* program 6 copy contents of one file to other using memory mapped I/O  */

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>

#define PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH           // Permission for RW-R-R
#define SOURCE "foo.txt"
#define WMODE O_CREAT | O_RDWR | O_TRUNC

int main(void) {

  int fdRead, fdWrite, fileSize;
  char *read, *write;
/*opening the read file and creating write file to copy the contents */
  fdRead=open(SOURCE, O_RDONLY);
  if(-1 == fdRead) {
    printf("open Error:%s\n",strerror(errno));
    return EXIT_FAILURE;
  }
  fdWrite = open("bar", WMODE, PERM);
  if(-1 == fdWrite) {
    printf("Write Error:%s\n",strerror(errno));
    return EXIT_FAILURE;
    }

	/*Retriving Input file size and adjusting output file size in accordance with Input file size*/
  fileSize = lseek(fdRead, 0, SEEK_END);
	if(-1 == ftruncate(fdWrite, fileSize)) {
    printf("Ftruncate Error:%s\n",strerror(errno));
    return EXIT_FAILURE;
	}

	/* Create a memory map for the read and write files */
	read = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fdRead, 0);
  write = mmap(NULL, fileSize, PROT_WRITE | PROT_READ, MAP_SHARED, fdWrite, 0);

	if( (MAP_FAILED == read) || (MAP_FAILED == write ) )  {
    printf("MMAP Error:%s\n",strerror(errno));
    return EXIT_FAILURE;
	}

	/* Copying contents */
	memcpy(write, read, fileSize);

	/* writing to file from memory t*/
	if(-1 == msync(write, fileSize, MS_SYNC) ) {
    printf("msync Error:%s\n",strerror(errno));
    return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
