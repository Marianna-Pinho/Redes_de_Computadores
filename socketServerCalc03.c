//http://www.linuxhowtos.org/C_C++/socket.htm
//https://stackoverflow.com/questions/23187496/what-is-the-meaning-of-sin-addr-s-addr-and-inet-addr

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//headers para sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTA 2000
#define LEN 4096

struct sockaddr_in server; //server
struct sockaddr_in client; //client

typedef struct Operand{
	float x;
	float y;
	char o;
}Operando;


float operacao(Operando op){
	if(op.o == '+'){
		return op.x + op.y;
	}

	if(op.o == '-'){
		return op.x - op.y;
	}

	if(op.o == '*'){
		return op.x * op.y;
	}

	if(op.o == '/'){
		return op.x / op.y;
	}
}

int main(){
	int sockfd = 0, newsock = 0, clientLen = 0;
	char buffer[LEN];
	Operando op;
	float resultado = 0.0;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Socket not created!");
		exit(1);
	}else{
		printf("Socket successfully created!\n");
	}

	server.sin_family = AF_INET;
	server.sin_port	  = htons(PORTA);
	//server.sin_addr.s_addr = inet_addr("192.168.1.7");
	memset(server.sin_zero, 0x0, 8);

	if(bind(sockfd, (struct sockaddr*)& server, sizeof(server)) == -1){
		perror("Bind not established!");
		exit(1);
	}

	if(listen(sockfd, 1) == -1){
		perror("Listen not established!");
		exit(1);
	}

	clientLen = sizeof(client);
	if((newsock = accept(sockfd, (struct sockaddr *)& client, &clientLen)) == -1){
		perror("Connection not accepted!");
		exit(1);
	}

	strcpy(buffer, "Welcome!\n\0");
	if(send(newsock, buffer, strlen(buffer), 0)){
		printf("Waiting client's answer...\n");
	}

	while(1){
		//memset(buffer, 0x0, LEN);
		if(recv(newsock, &op, sizeof(op), 0) > 0){
			//buffer[strlen(buffer)-1] = '\0';

			printf("Received Message: %f %f \n", op.x, op.y);
			resultado = operacao(op);
			printf("Resultado: %.2f\n", resultado);

			//memset(buffer, 0x0, LEN);
			//fgets(buffer, LEN, stdin);
			send(newsock, &resultado, sizeof(resultado), 0);
		}
	}

	close(newsock);
	close(sockfd);
	printf("Server Closed!\n");	
}
