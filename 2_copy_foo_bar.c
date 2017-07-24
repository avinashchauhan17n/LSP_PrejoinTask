/*Write a       file    copy    program that    copies  contents        from    foo     to      bar     using   low     level   I/O     – ensure
proper  error   checking        is      in      place
*/


#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#define foo_mode O_RDONLY
#define bar_mode O_CREAT|O_TRUNC|O_RDWR
#define perm 777

#define foo "foo.txt"                // enter file name with path or name if it is in current dir
#define bar "bar.txt"

int main()
{
int fd,fd_new;
char c;

        fd=open(foo,foo_mode);                                  // opeing  foo.txt file

        if(fd==-1)
        {
                printf("error: %d \n",errno);
                perror("foo_create");
                exit(1);
        }

        printf("%d\n",fd);
        fd_new=open(bar,bar_mode,perm);                    // creating bar.txt file to copy contents into it from foo.txt

        if(fd_new==-1)
        {
                printf("error: %d \n",errno);
                perror("foo_write");
                exit(1);        
        }

	while(read(fd,&c,1)==1) 			//reading character by character
		write(fd_new,&c,1);
	
	exit(0);
}
