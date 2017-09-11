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

struct sockaddr_in server;
typedef struct Operand{
	float x;
	float y;
	char o;
}Operando;

void show_operacoes(){
	printf("Digite uma das seguintes operações:\n [+] [-] [*] [/] \n escolha: ");
}
int main(){
	int sockfd = 0;
	char buffer[LEN];
	float resultado = 0.0;
	Operando op;
	op.x = 1;
	op.y = 2;


	printf("Hello, I am the Client...\n");

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Socket not created!");
		exit(1);
	}else{
		printf("Socket successfully created!\n");
	}

	server.sin_family = AF_INET;
	server.sin_port	  = htons(PORTA);
	//server.sin_addr.s_addr = inet("192.168.1.7");
	memset(server.sin_zero, 0x0, 8);

	if((connect(sockfd, (struct sockaddr *)& server, sizeof(server))) == -1){
		perror("Connection not established!");
		exit(1);
	}


	if(recv(sockfd, buffer, LEN, 0) > 0){
		buffer[strlen(buffer)-1] = '\0';
		printf("From server: %s\n", buffer);
		memset(buffer, 0x0, LEN);
	}

	while(1){
		printf("Digite o primeiro operando: \n");
		scanf("%f", &(op.x));
		show_operacoes();
		scanf(" %c", &(op.o));
		printf("Digite o segundo operando: \n");
		scanf("%f", &(op.y));	

		//fgets(buffer, LEN, stdin);
		send(sockfd, &op, sizeof(op), 0);	
		if(recv(sockfd, &resultado, sizeof(resultado), 0) > 0){
			printf("From server: %f\n", resultado);
		}
	}

	close(sockfd);
	printf("Client closed\n");
	return 0;
}