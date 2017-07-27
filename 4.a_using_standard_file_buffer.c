#include <stdio.h>
#include <stdlib.h>
#define SOURCE "file.txt"

int main(void){

/***************local variables declaration start here****************************************************/
  FILE *FileToWriteData;
  int block_size,block_count;
  int retValue;
  char *buffer;
  double TimeDifference;
  clock_t start;
  clock_t end;
/***************local variables declaration ends here*****************************************************/

/***************User Inputs for block_size and block count starts*****************************************/
  printf("Enter the Block size\n");
  scanf("%d",&block_size);
  printf("Enter the Block Count\n");
  scanf("%d",&block_count);

  if( (buffer = (char *)malloc(block_size*sizeof(char))) == NULL){
       printf("Error in Allocating desired buffer size\n");
       return EXIT_FAILURE;
  }
/***************User Inputs for block_size and block count ends******************************************/
  if( (FileToWriteData=fopen(SOURCE,"w"))==NULL) {
 	printf("Error in opening file.txt\n");
	return EXIT_FAILURE;
  }
/***************Writing buffer with size Blocksize given by user for Bockcount number of times**********/
  start = clock();                    // clock event start 
  while (block_count>0) {
    if( (retValue=(fwrite(buffer,1,block_size,FileToWriteData))) == 0) {
         printf("FIle Write Error\n");
         EXIT_FAILURE;
    }
    block_count--;
  }
  end = clock();                    // clock event ends
/***********************************write buffer operation complete***********************************/
  TimeDifference = (double)(end-start);
  printf("Write Operation time taken %lf \n",TimeDifference/CLOCKS_PER_SEC);
	       
  return EXIT_SUCCESS;
}
