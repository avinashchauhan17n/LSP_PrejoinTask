/* wap to print o/p file attributes similar to ls-l on a single file */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define FILENAME "foo.txt" 
#define HANDLEERROR(msg) \
do { perror(msg); exit(EXIT_FAILURE); } while(0)

void file_Info(struct stat *sb);

int main(void) {
  struct stat sb;
  if(stat(FILENAME, &sb) == -1) {
    HANDLEERROR("stat error");
  }
  file_Info(&sb);

  return EXIT_SUCCESS;

}
/*function to display various file attributes*/
void file_Info(struct stat *sb) {
  char r=0;
  printf("File type: ");

/* checking file type */
	
  switch (sb->st_mode & S_IFMT) {
    case S_IFREG: printf("regular file\n"); break;
    case S_IFDIR: printf("directory\n"); break;
    case S_IFCHR: printf("character device\n"); break;
    case S_IFBLK: printf("block device\n"); break;
    case S_IFLNK: printf("symbolic (soft) link\n"); break;
    case S_IFIFO: printf("FIFO or pipe\n"); break;
    case S_IFSOCK: printf("socket\n"); break;
    default: printf("unknown file type?\n"); break;
  }
/*comparing individual flags for file permissions */

  printf("%c%c%c%c%c%c%c%c%c%c", r,
  (sb->st_mode & S_IRUSR)? 'r' : '-',
  (sb->st_mode & S_IWUSR)? 'w' : '-',
  (sb->st_mode & S_IXUSR)? 'x' : '-',
  (sb->st_mode & S_IRGRP)? 'r' : '-',
  (sb->st_mode & S_IWGRP)? 'w' : '-',
  (sb->st_mode & S_IXGRP)? 'x' : '-',
  (sb->st_mode & S_IROTH)? 'r' : '-',
  (sb->st_mode & S_IWOTH)? 'w' : '-',
  (sb->st_mode & S_IXOTH)? 'x' : '-');

/* printing all atrributes of file */
  printf("I-node number: %ld\n", (long) sb->st_ino);
  printf("File size: %lld bytes\n", (long long) sb->st_size);
  printf("Optimal I/O block size: %ld bytes\n", (long) sb->st_blksize);
  printf("512B blocks allocated: %lld\n", (long long) sb->st_blocks);
  printf("Last file access: %s", ctime(&sb->st_atime));
  printf("Last file modification: %s", ctime(&sb->st_mtime));
  printf("Last status change: %s", ctime(&sb->st_ctime));


}
