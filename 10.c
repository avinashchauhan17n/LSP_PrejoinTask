/* output as ls-l on a directory */

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

void list_File(char *);

int main(void) {
	DIR *d;
	struct dirent *info;
	if(NULL == (d=opendir("."))) {
	HANDLEERROR("dir open error");
	}

	while((info=readdir(d))!=NULL) {
	list_File(info->d_name);
}

return EXIT_SUCCESS;
}

void list_File(char *name) {
	struct stat sb;
	char *modtime;
	char r;

	if(stat(name,&sb)<0){
	perror(name);
	exit(EXIT_FAILURE);
	}
  if(S_ISREG(sb.st_mode)) { r = '-'; }
  if(S_ISDIR(sb.st_mode)) { r = 'd'; }
  if(S_ISCHR(sb.st_mode)) { r = 'c'; }
  if(S_ISBLK(sb.st_mode)) { r = 'b'; }
  if(S_ISFIFO(sb.st_mode)) { r = 'p'; }
  if(S_ISLNK(sb.st_mode)) { r = 'l'; }
  if(S_ISSOCK(sb.st_mode)) { r = 's'; }

printf("%c%c%c%c%c%c%c%c%c%c", r,
         (sb.st_mode & S_IRUSR)? 'r' : '-',
         (sb.st_mode & S_IWUSR)? 'w' : '-',
         (sb.st_mode & S_IXUSR)? 'x' : '-',
         (sb.st_mode & S_IRGRP)? 'r' : '-',
         (sb.st_mode & S_IWGRP)? 'w' : '-',
         (sb.st_mode & S_IXGRP)? 'x' : '-',
         (sb.st_mode & S_IROTH)? 'r' : '-',
         (sb.st_mode & S_IWOTH)? 'w' : '-',
         (sb.st_mode & S_IXOTH)? 'x' : '-');

	printf(" %8ld",sb.st_size);
  	modtime = ctime(&sb.st_mtime);
  	/* remove the '\n' at the end of modtime */
  	modtime[strlen(modtime) -1] = '\0';

	printf(" %s", modtime);
	printf(" %s\n", name);
}


