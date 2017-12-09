#include <stdio_ext.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include "alunosFunctions.h"


#define PORT 5000
#define MSGLEN 100
#define SERVER_ADDRESS "192.168.1.16"
#define MAX_RETRANSMISSION	5

struct sockaddr_in server;
//192.168.1.16
int main(){
	int sockfd = 0, ctimeout = 0, serverLen = sizeof(server);
	char message[MSGLEN], result[MSGLEN];
	struct timeval timeout={0,1};


	if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		perror("Socket not created!");
		exit(1);
	}
	printf("Socket successfully created!\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	memset(server.sin_zero, 0x0, 8);


	if (inet_aton(SERVER_ADDRESS , &server.sin_addr) == 0){
        fprintf(stderr, "inet_aton() failed\n");
        perror("Invalid server address!");
        exit(1);
    }
    
    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    while(1){
    	memset(message, 0x0, MSGLEN);
    	memset(result, 0x0, MSGLEN);
    	menu();
    	scanf(" %[^\n]", message);
       	
    
    	while(1){
		    if(sendto(sockfd, message, strlen(message),0, (struct sockaddr*)&server, serverLen) == -1){
		        perror("Send message failed!");
		        exit(1);
		    }
		   	
		   	int recvlen = 0;
		   	setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));

		   	if(strcmp(message, "FIM") == 0){
	    		close(sockfd);
   				printf("Client is closed...\n");
   				return 0;
	    	}

		    if((recvlen = recvfrom(sockfd, result, MSGLEN, 0, (struct sockaddr *)&server, &serverLen)) == -1){
		        perror("TIMEOUT");
		        ctimeout++;
		        usleep(500000);
		        continue;
		       	
		    }

		    
			printf("MESSAGE: %s\n",result);
		    //ctimeout = MAX_RETRANSMISSION;
		    break;
	    }
	    
	}

}