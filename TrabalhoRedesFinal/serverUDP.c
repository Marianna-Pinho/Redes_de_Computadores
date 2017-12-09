#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include "alunosFunctions.h"
#include <time.h>

#define PORT 5000
#define MSGLEN 500
#define CHAVE 7

struct sockaddr_in server, client;

int decodificar(char *message){
	char *token = NULL;
	char operacao[20];
	char msg[100];
	strcpy(msg, message);
	msg[strlen(msg)] = '\0';

	token = strtok(msg, ",");
	strcpy(operacao, token);
	operacao[strlen(operacao)] = '\0';

	if(strcmp(operacao, "TAMCLASSE") == 0){
		return 1;
	}else if(strcmp(operacao, "ADDALUNO") == 0){
		return 2;
	}else if(strcmp(operacao, "SEARCHN") == 0){
		return 3;
	}else if(strcmp(operacao, "SEARCHM") == 0){
		return 4;
	}else if(strcmp(operacao, "EDITALUNO") == 0){
		return 5;
	}else if(strcmp(operacao, "DELALUNO") == 0){
		return 6;
	}else if(strcmp(operacao, "MEDIAALUNO") == 0){
		return 7;
	}else if(strcmp(operacao, "MEDIATURMA") == 0){
		return 8;
	}else if(strcmp(operacao, "FIM") == 0){
		return 9;
	}else{
		return 0;
	}
}

int main(){
	int sockfd = 0, recvLen = 0, clientLen = sizeof(client);
	char message[MSGLEN];
	Aluno *alunos = NULL;
	int op = 0,tam = 0, idM = 0;
	char *token = NULL, nome[100];
	Aluno aluno;
	srand( (unsigned)time(NULL) );


////////////////////////////////REDES///////////////////////////////////////////////////////////////////////////////
	if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		perror("Socket not created!");
		exit(1);
	}
	printf("Socket successfully created!\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	//server.sin_addr.s_addr = inet_addr("172.18.104.164");
	memset(server.sin_zero, 0x0, 8);
	
	if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1){
		perror("Bind not established!");
		exit(1);
    }
    printf("Bind established!\n");

    while(1){
    	printf("Waiting for client data...");
    	fflush(stdout);
    	memset(message, 0x0, MSGLEN);
    	int chave = rand() % 10;

			if((recvLen = recvfrom(sockfd, message, MSGLEN, 0, (struct sockaddr*)&client, &clientLen)) == -1){
    			perror("Receive message failed!");
    			exit(1);
    			   		
    		}

    	message[strlen(message)] = '\0';
  		
  		printf("MESSAGE: %s\n", message);
    	op = decodificar(message);
    	//tam = 0;
    
///////////////////////////////////////////////////////APLICACAO////////////////////////////////////////////////////////////
    	switch(op){
    		case 1:								//CRIA ou ALTERA tamanho da classe
    			token = strtok(message, ",");
    			token = strtok(NULL, ",");
				tam = atoi(token);
				if(tam > 0){
						alunos =(Aluno*)malloc(sizeof(Aluno)*tam);
						inicializar (alunos, tam);
						strcpy(message, "Classe criada!");	
					
				}else{
					strcpy(message, "Tamanho da classe não é permitido!");
				}
			break;	
			case 2:

				token = strtok(message, ",");
				
				token = strtok(NULL, ",");
				strcpy(aluno.nome, token);
				aluno.nome[strlen(aluno.nome)] = '\0';

				token = strtok(NULL, ",");
				aluno.ap1 = atof(token);

				token = strtok(NULL, ",");
				aluno.ap2 = atof(token);

				if(alunos != NULL){
					cadastrar(alunos, aluno, tam);	
					//printf("nome: %s\nmat: %d\nap1: %.2f\nap2: %.2f", alunos[0].nome, alunos[0].idMatricula, alunos[0].ap1, alunos[0].ap2);	
					strcpy(message, "Aluno cadastrado com sucesso!");
				}else{
					strcpy(message, "Falha ao cadastrar aluno!");
				}
			break;
			case 3:
				token = strtok(message, ",");
				token = strtok(NULL, ",");

				strcpy(nome, token);
				nome[strlen(nome)] = '\0';
				if(buscaPorNome(nome,alunos,tam,&aluno) == 1){
					//printf("nome: %s\nmat: %d\nap1: %.2f\nap2: %.2f", aluno.nome, aluno.idMatricula, aluno.ap1, aluno.ap2);	
					sprintf(message,"nome: %s\nmat: %d\nap1: %.2f\nap2: %.2f", aluno.nome, aluno.idMatricula, aluno.ap1, aluno.ap2);
					printf("M: %s\n", message );
				}else{
					strcpy(message, "Aluno não encontrado!");
				}
			break;
			case 4:
				token = strtok(message, ",");
				token = strtok(NULL, ",");

				idM = atoi(token);

				if(buscaPorID(idM, alunos,tam , &aluno)==1){
					sprintf(message,"nome: %s\nmat: %d\nap1: %.2f\nap2: %.2f", aluno.nome, aluno.idMatricula, aluno.ap1, aluno.ap2);
				}else{
					strcpy(message, "Aluno não encontrado!");
				}
				break;
			case 5:
				token = strtok(message, ",");
				token = strtok(NULL, ",");

				idM = atoi(token);
				
				if(buscaPorID(idM,alunos,tam,&aluno) == 1){ 
					token = strtok(NULL, ",");
					strcpy(aluno.nome, token);
					aluno.nome[strlen(aluno.nome)] = '\0';

					token = strtok(NULL, ",");
					aluno.ap1 = atof(token);

					token = strtok(NULL, ",");
					aluno.ap2 = atof(token);

					aluno.idMatricula = idM;

					editar(alunos,idM,tam,aluno);
					//printf("nome: %s\nmat: %d\nap1: %.2f\nap2: %.2f", alunos[idM].nome, alunos[idM].idMatricula, alunos[idM].ap1, alunos[idM].ap2);	
					strcpy(message, "Aluno editado com sucesso!");
				}else{
					//strcpy(message, "Aluno não encontrado!");			
				}
			break;
			case 6:
				token = strtok(message, ",");
				token = strtok(NULL, ",");

				idM = atoi(token);
				
				if(buscaPorID(idM,alunos,tam,&aluno) == 1){
					excluir(alunos, tam, idM);
					//printf("Aluno excluido\n");
					strcpy(message, "Aluno excluido com sucesso!");
				}else{
					strcpy(message, "Aluno não encontrado!");
				}
			break;
			case 7:
				token = strtok(message, ",");
				token = strtok(NULL, ",");

				idM = atoi(token);
				
				if(buscaPorID(idM,alunos,tam,&aluno) == 1){
					sprintf(message, "A media do aluno eh %.2f\n", calcular(alunos, tam, idM));
					
				}else
					strcpy(message, "Aluno não encontrado!");
			break;
			case 8:
				if(qtdAlunos(alunos,tam) != 0 ){
					sprintf(message, "A media da turma eh %.2f\n", calcularMediaTurma(alunos, tam));	
				}else{
					strcpy(message, "Não há alunos na turma!");
				}
			break;
			case 9:
				strcpy(message, "FIM");
			break;

			default:
				strcpy(message, "Comando não encontrado!");
    	}
	    
////////////////////////////////////////REDES///////////////////////////////////////////////////////////////////////////////
    	message[strlen(message)] = '\0';
    	if(chave == CHAVE){

    		if(sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&client, clientLen) == -1){
    			perror("Send message failed!");
    			exit(1);
    		}

    	}

    	if(strcmp(message, "FIM") == 0){
    		break;
    	}
    	
    	
    }

    close(sockfd);
    printf("Server is closed...\n");
    return 0;
}