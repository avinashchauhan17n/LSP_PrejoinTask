#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>

#define mode O_CREAT|O_RDWR|O_TRUNC   
#define permission 777                 //permissions  ugo --> rw-rw-rw

int main()
{
	int fd,w;
	char filename[]="avinash.txt";

	fd=open(filename,mode,permission);

	if(fd==-1)
	{
		printf("Error:%d\n",errno);
		perror("hello.txt creation\n");
		exit(1);
	}
	printf("%d\n",fd);	

	w=write(fd,"Hello! world\n",15);

	if(w==-1)
        {
                printf("Error:%d\n",errno);
                perror("hello.txt write error\n");
		exit(1);
        }

return 0;

}
