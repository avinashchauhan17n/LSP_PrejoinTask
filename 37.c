#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netdb.h>

#define TFTP_OPCODE_RRQ    1
#define TFTP_OPCODE_WRQ    2
#define TFTP_OPCODE_DATA   3
#define TFTP_OPCODE_ACK    4
#define TFTP_OPCODE_ERROR  5
#define TFTP_TRANSFER_MODE "octet"

#define ERROR(msg) printf(#msg"%s\n",strerror(errno));exit(0)


void tftp_read(int sock, struct sockaddr *server, socklen_t serverlen, char *filename);

int main(void) {

  int sock, retValue;
  struct addrinfo hints;
  struct addrinfo *results ,*rp, *server;

  /*clearing all members of structure with zeros*/
  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;

  /* getaddrinfo combines the functinality for gethostbyname() and getservbyname() without IPv4/V6 dependenies */
  if( (retValue = getaddrinfo("127.0.0.1", "tftp", &hints, &results)) != 0) {  // 127.0.0.1 is localhost for loopback
      ERROR("TFTP Service assigning error");
  }

  server = NULL;
  rp=results;

  /* traversing through */
  while(rp != NULL) {
    if( (sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) != -1) {
         server = rp;
         rp = NULL;
    } else {
        printf("Socket creation failed moving\n");
        rp = rp->ai_next;
      }
  }

  if(server == NULL) {
    ERROR("Server error");
  }

  tftp_read( sock, server->ai_addr, server->ai_addrlen, "foo"); // file save in local tftpboot folder
  freeaddrinfo(results);
  close(sock);
  return EXIT_SUCCESS;
}

void tftp_read(int sock, struct sockaddr *server, socklen_t serverlen, char * filename) {

  char buffer[516];
  char *framePointer = buffer;
  int payloadLength;
  int count;
  struct sockaddr_in servRespAddr;
  socklen_t servRespAddrLen;
  short opcode;
  short blockNumber;

  /* First Generate a Payload for Read Request */

  opcode = htons(TFTP_OPCODE_RRQ);
  memcpy(framePointer, &opcode, sizeof(short));

  framePointer += 2;
  framePointer = strcpy(framePointer, filename);
  framePointer += strlen(filename) + 1;
  framePointer = strcpy(framePointer, TFTP_TRANSFER_MODE);
  framePointer += strlen(TFTP_TRANSFER_MODE) + 1;
  payloadLength = framePointer - buffer;  // actual frame orig - ( data + 2(payload) + 2(blocksize)

  /* Send the Read Request */
  if(sendto(sock, buffer, payloadLength, 0, server, serverlen) == -1) {
     ERROR("sendto");
  }

  /* Fall into the loop to handle DATA and ERROR till end of transmission*/
  do {
    servRespAddrLen = sizeof(struct sockaddr_in);
    /* Read Data OR Error */

    if( (count = recvfrom(sock, buffer, 512, 0, (struct sockaddr*)&servRespAddr, &servRespAddrLen)) == -1) {
         ERROR("recvfrom");
    }
    memcpy(&opcode, buffer, sizeof(short));
    memcpy(&blockNumber, buffer+2, sizeof(short));
    opcode = ntohs(opcode);
    blockNumber = ntohs(blockNumber);

    switch(opcode) {
    case TFTP_OPCODE_ERROR:
      fprintf(stderr, "TFTP server error code %d: %s\n", blockNumber, buffer+4);
      exit(EXIT_FAILURE);
      break;
    case TFTP_OPCODE_DATA:
      /* Stream data to stdout */
      if (write(1, buffer+4, count-4) == -1) {
          ERROR("write");
      }
      /* Send the ACK Request */
      /* Copy only ACK Opcode as Block Number is already in place */
      opcode = htons(TFTP_OPCODE_ACK);
      memcpy(buffer, &opcode, sizeof(short));
      payloadLength = 4;
      if (sendto(sock, buffer, payloadLength, 0, (struct sockaddr *)&servRespAddr, sizeof(struct sockaddr_in)) == -1) {
          ERROR("sendto");
      }
      break;
      default:
      ERROR("Unknown opcode from the server");
      break;
    }
  } while(count == 516);

return;

}



