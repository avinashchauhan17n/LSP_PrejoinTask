/* 3. 	 Write	a	file	copy	program	that	copies	contents	from	foo	to	bar	using	standard	C	file	I/O	ensure	proper	error	checking	is	in	place*/

#include<stdio.h>
#include<stdlib.h>

#define sourcefile "source.txt"
#define destfile "destination.txt"   

int main(void)
{
	FILE *source,*dest;
	int ch;
	if((source=fopen(sourcefile,"r"))==NULL)
	{
		printf("Error in opening source file\n");
		exit(1);
	}
	if((dest=fopen(destfile,"w"))==NULL)
        {
                printf("Error in opening destination file\n");
                exit(1);
        }

	while((ch=fgetc(source))!=EOF)
	fputc(ch,dest);

	fclose(source);
	fclose(dest);
	return 0;
}
