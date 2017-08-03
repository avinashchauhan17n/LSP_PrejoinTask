#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define ERROR(msg) printf(#msg"%s\n",strerror(errno))

void path_dir_lookup(char *);

int histogram[24];

int main(void) {
  char path[PATH_MAX];
  int i=0;

  getcwd(path,PATH_MAX); // retriving current working path for directory  
  path_dir_lookup(path);

  while(i<24) {
    printf("%d %d\n",i,histogram[i]);
    i++;
  }
}

void path_dir_lookup(char *dname) {

  struct stat sb;
  struct tm *modtime;
  DIR *dirp;
  struct dirent *direntp;
  char path[PATH_MAX];
  
  printf("%s", path);
  if( (dirp=opendir(dname)) == NULL) {
    ERROR("open dir"); 
  }  
  while((direntp=readdir(dirp))!= NULL) {  
    strcpy(path, dname);           // updating the path with directory seprator /        
    strcat(path, "/");
    strcat(path, direntp->d_name);
      if(stat(path, &sb) == -1) {
        ERROR("stat");
      }
      if(S_ISDIR(sb.st_mode)) {
 //     printf("%s\n",path);
      if(path[strlen(path)-1] != '.')  // recursion condition termination
        path_dir_lookup(path);           // recursion
      } else { 
//      printf(" %8ld",sb.st_size);
        modtime = localtime(&sb.st_mtime);
        printf(" %d", modtime->tm_hour);
        printf(" %s\n",direntp->d_name);
        histogram[modtime->tm_hour]++;
        }
  }  
  if(closedir(dirp) == -1) {
    ERROR("closedir");
  }

}

