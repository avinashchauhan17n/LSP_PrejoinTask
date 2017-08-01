/*Write	a	program	that	takes	‘c’,	‘v’,	as	Boolean	options,	‘b’	as	a	numeric	option,	‘f’	as	a	
text	option	and	remaining	non-option	arguments	and	prints	out	all	the	options	that	were	set	
along	with	non-option	arguments.	Test	the	program	to	work	with	various	ordering	of	all	the	
options,	combining	options,	etc. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <getopt.h>

  extern char *optarg;
  extern int optind, opterr, optopt;

int main(int argc,char *argv[]) {
  int c=0,v=0,b=0,f=0;
  char opt;
  int bOpt=0;
  char *fOpt=NULL;
  int i=0,j=0;

  while(-1 != (opt=getopt(argc, argv, "cvb:f:"))) {
    switch(opt) {
      case 'c': c=1; break;
      case 'v': v=1; break; 
      case 'b': b=1; bOpt=atoi(optarg); break;
      case 'f': f=1; if(NULL == (fOpt=(char*)malloc(strlen(optarg)*sizeof(char)))) {
		       printf("Malloc not alloted %s\n",strerror(errno));
	             }
		     strcpy(fOpt,optarg); break;
      default: return EXIT_FAILURE;		
    }  
  }
  if(c) { printf("Found option c\n"); }
  if(v) { printf("Found option v\n"); }
  if(b) { printf("Found option b with value: %d\n", bOpt); }
  if(f) { printf("Found option f with value: %s\n", fOpt); }

  /* printing all non-option arguments */
  i=optind;             /*the index of non-option arguments */
  j=argc-optind;        /*number of non-option arguments */

  while(j) {
    printf("Found non-option argument: %s\n", argv[i]);
    i++; j--;
  }

  free(fOpt);
  return EXIT_SUCCESS;
}	
