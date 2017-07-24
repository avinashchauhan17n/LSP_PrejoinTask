#include <stdio.h>
#include <stdlib.h>
#define SOURCE "file.txt"

int main(void){

/***************local variables declaration start here****************************************************/

	FILE *filetowriteDATA;
	int block_size,block_count;
	int retVALUE;
	char *buffer;

/***************local variables declaration ends here*****************************************************/

/***************User Inputs for block_size and block count starts*****************************************/
	printf("Enter the Block size\n");
    scanf("%d",&block_size);
	printf("Enter the Block Count\n");
    scanf("%d",&block_count);

    if ( (buffer = (char *)malloc(block_size*sizeof(char))) == NULL){
        printf("Error in Allocating desired buffer size\n");
        EXIT_FAILURE;
    }
/***************User Inputs for block_size and block count ends******************************************/

	if ((filetowriteDATA=fopen(SOURCE,"w"))==NULL){
		printf("Error in opening file.txt\n");
		EXIT_FAILURE;
        }
/***************Writing buffer with size Blocksize given by user for Bockcount number of times**********/
	while (block_count>0){
           if ((retVALUE=(fwrite(buffer,sizeof(buffer),1,filetowriteDATA))) == 0){
               printf("FIle Write Error\n");
               EXIT_FAILURE;
              }

	       block_count--;
          }
	EXIT_SUCCESS;
}
