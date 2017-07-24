#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define FILETOWRITE "data.txt"
#define MODE O_CREAT|O_WRONLY
#define PERMISSION 644
int main(void) {
        int fdWRITE,retVALUE;
        char *buffer;
        int blockSIZE, blockCOUNT;

        /***************User Inputs for block_size and block count starts*****************************************/
        printf("Enter the Block size\n");
        scanf("%d",&blockSIZE);
        printf("Enter the Block Count\n");
        scanf("%d",&blockCOUNT);

        if ( (buffer = (char *)malloc(blockSIZE*sizeof(char))) == NULL){
                printf("Error in Allocating desired buffer size\n");
                EXIT_FAILURE;
        }
        /***************User Inputs for block_size and block count ends******************************************/

        if( (buffer  = calloc(blockSIZE,(sizeof(char)))) == NULL) {
                printf("Memory not Allocated:error");
                EXIT_FAILURE;
        }

        if( (fdWRITE = open(FILETOWRITE,MODE,PERMISSION)) == -1) {
                printf("Open Error= %d\n", errno);
                perror("FILETOWRITE");
                EXIT_FAILURE;
        }

        while( blockCOUNT > 0) {
                if( (retVALUE = write(fdWRITE, buffer, blockSIZE)) == -1) {
                        printf("Error:Write = %d\n", errno);
                        perror(FILETOWRITE);
                        EXIT_FAILURE;
                }
                blockCOUNT--;
        }

        EXIT_SUCCESS;
}
