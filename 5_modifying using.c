#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define DATA "database.txt"
#define MODE O_CREAT|O_RDWR
#define DEBUG // comment it if do not want to print the data from database

struct record {
  unsigned int id;
  char name[80];
};

int main(void){
/* local variables used for data file generation part of code, Required once to generate a demo database*/
  struct record r1[4] = {
  {1,"avinash"},
  {2,"kiran"},
  {3,"omkar"},
  {4,"chandu"}
  };
  char buffer[sizeof(r1)];
  int fdWrite, retValue1;
/* local variables used for data file generation part of code*/
  int fdReadWrite, retValue2,recordSize;
  struct record newModification;
  recordSize = sizeof(newModification);
/*Datafile creation part1/2 of the main program */
  memcpy(&buffer[0*84], &r1[0], 84);
  memcpy(&buffer[1*84], &r1[1], 84);
  memcpy(&buffer[2*84], &r1[2], 84);
  memcpy(&buffer[3*84], &r1[3], 84);

  if(-1 == (fdWrite = open("database.txt", O_CREAT| O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))) {
    printf("Error:open %s\n",strerror(errno));
    return EXIT_FAILURE;
  }
  if(-1 == (retValue1 = write(fdWrite, buffer, 84*4))) {
    printf("Error:write %s\n",strerror(errno));
    return EXIT_FAILURE;
  }
  close(fdWrite);
/* Modification of the database part2/2 of the program */
  if(-1 == (fdReadWrite = open("database.txt", O_RDWR))) {
    printf("Error:open %s\n",strerror(errno));
    return EXIT_FAILURE;
  }

  if(-1 == (retValue2 = lseek(fdReadWrite, recordSize, SEEK_SET))) {
    printf("Error:readwrite %s\n",strerror(errno));
    return EXIT_FAILURE;
  }
  #ifdef DEBUG
  printf("before reading : %d %s\n",newModification.id,newModification.name);
  #endif

  if(-1 == (retValue2 = read(fdReadWrite, &newModification, recordSize))) {
    printf("read error with errno = %d\n", errno);
    perror("datafile");
    exit(1);
  }
  #ifdef DEBUG
    printf("Before modification value: %d, %s\n", newModification.id, newModification.name);
  #endif

  newModification.id = 5;

  #ifdef DEBUG
  printf("After modification value: %d, %s\n", newModification.id, newModification.name);
  #endif

/* updating the record in correct position after reading operation */
  if(-1 == (retValue2 = lseek(fdReadWrite, -1*recordSize, SEEK_CUR))) {
    printf("Error:readwrite %s\n",strerror(errno));
    return EXIT_FAILURE;
  }


return EXIT_SUCCESS;
}

