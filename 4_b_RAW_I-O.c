#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#define FILETOWRITE "data.txt"
#define MODE O_CREAT|O_WRONLY
#define PERMISSION 644          //rw-r-r
int main(void) {
        /***************local variables declaration ends here*****************************************************/
        int fdWrite,retValue;
        char *buffer;
        int blockSize, blockCount;
	double TimeDifference;
	clock_t start;
	clock_t end;
        /***************local variables declaration ends here*****************************************************/
        
        /***************User Inputs for block_size and block count starts*****************************************/
        printf("Enter the Block size\n");
        scanf("%d",&blockSize);
        printf("Enter the Block Count\n");
        scanf("%d",&blockCount);

        if ( (buffer = (char *)malloc(blockSize*sizeof(char))) == NULL){
               	printf("Error in Allocating desired buffer size\n");
                EXIT_FAILURE;
        }
        /***************User Inputs for block_size and block count ends******************************************/

        if( (buffer  = calloc(blockSize,(sizeof(char)))) == NULL) {
                printf("Memory not Allocated:error\n");
                EXIT_FAILURE;
        }
        
        if( (fdWrite = open(FILETOWRITE,MODE,PERMISSION)) == -1) {
                printf("Error %s",strerror(errno));
                EXIT_FAILURE;
        }
        /***************Writing buffer with size Blocksize given by user for Bockcount number of times**********/
        start= clock();                  // starting the clock call to count the event
        while( blockCount > 0) {
                if( (retValue = write(fdWrite, buffer, blockSize)) == -1) {
                     printf("Error:Write = %s\n",strerror(errno)); 
                     EXIT_FAILURE;
                }
        	blockCount--;
        }
	end=clock();                   //clock event ends here
	/***************Writing buffer operation ends here*****************************************************/

        timeDiff=(double)(end-start);   
        timeDiff/=CLOCKS_PER_SEC;              // taking diff of operation for buff write in terms of clocks/sec
        printf("Time taken for write cycle: %lf\n",timeDiff);
        EXIT_SUCCESS;
}
