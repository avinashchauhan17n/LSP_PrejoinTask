#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#define HANDLEERROR(msg) printf(#msg"%s",strerror(errno))

int main(void) {
  DIR *d;
  struct dirent *info;
  struct stat sb;
  long total =0;
/* descriptor to open  all dir in current directory */
  if(NULL==(d=opendir("."))) {
    HANDLEERROR("dir open error");
  }
/* reading all dir and their respective sizes iterating the end of file in directory */
  while((info=readdir(d))!=NULL) {
    if(-1 == stat(info->d_name,&sb)) {
      HANDLEERROR("stat error");
    }
/* calculating toatl size of each directory */
  total +=sb.st_size;
  }
  closedir(d);
  printf("Total size is %lu \n",total);

}
