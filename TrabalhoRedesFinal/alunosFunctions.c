#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alunosFunctions.h"

int matricula = 0;
void menu(){
	// A funcao menu ira mostrar as opcoes que o usuario tem em nosso sistema
	printf("\t\t Digite:\n");
	printf("\t TAMCLASSE,_tamanho\n");
	printf("\t ADDALUNO,_nome,_nota1,_nota2\n");
	printf("\t SEARCHN,_nome\n");
	printf("\t SEARCHM,_mat\n");
	printf("\t EDITALUNO,_mat,_nome,_nota1,_nota2\n");
	printf("\t DELALUNO,_mat\n");
	printf("\t MEDIAALUNO,_mat\n");
	printf("\t MEDIATURMA\n");
	printf("\t FIM\n");
}


void receber(Aluno *p){
	// A funcao recerber tem como parametro um ponteiro de aluno, onde o iremos salvar os dados de um novo aluno no endereco mandado na funcao main
	printf("Digite o nome do aluno, nota 1 e nota 2: ");

	scanf("%s %f %f",p->nome, &(p->ap1), &(p->ap2));
}

int cadastrar(Aluno lista[], Aluno novoAluno, int tamanho){
	// cadastrar recebe a lista de alunos e um novo aluno que quer inserir
	int flag = 0, i = 0;
	for(i=0;i<tamanho;i++){
	// ele vai percorrer todo esse for e aonde matricula for -1 (onde tiver posicao vazia) lista[i] recebe esse novo aluno	
		if(lista[i].idMatricula == -1){
			lista[i] = novoAluno;
			lista[i].idMatricula = matricula;
			matricula++;
			flag = 1;
			i = tamanho;
		}
	}
	// se foi encontrado alguma matricula -1 ele ira retorna 1 senao ira retornar 0
	return flag;
}

void editar(Aluno lista[], int idM, int tamanho, Aluno aluno){
	// vai percorrer toda a lista de alunos e procurar onde tem o id que usou pra busca
	int i = 0;
	for(i=0;i<tamanho;i++){
	// ele vai percorrer todo esse for e aonde matricula for -1 (onde tiver posicao vazia) lista[i] recebe esse novo aluno	
		if(lista[i].idMatricula == idM){
			lista[i] = aluno;
		}
	}
}

void excluir(Aluno lista[], int tamanho, int idAux){
	// vai percorrer toda a lista de alunos e procurar onde tem o id que usou pra busca
	int i;
	for(i=0;i<tamanho;i++){
		if(lista[i].idMatricula == idAux){
			lista[i].idMatricula = -1;
			strcpy(lista[i].nome,"");
			lista[i].ap1 = 0;
			lista[i].ap2 = 0;
			// quando achar esse id ele ira modificar o idMatricula do aluno para -1 (ele ira excluir o aluno)
			i = tamanho;
		}
	}
}

float calcular(Aluno lista[], int tamanho, int idAux){
	// vai percorrer toda a lista de alunos e procurar onde tem o id que usou pra busca
	int i;
	for(i=0;i<tamanho;i++){
		if(lista[i].idMatricula == idAux){
			printf("A media do aluno eh: %f \n",((lista[i].ap1 + lista[i].ap2)/2.0));
			// quando achar ele ira calcular e mostrar a media
			//i = tamanho;
			return (lista[i].ap1 + lista[i].ap2)/2.0;
		}
	}
}

float calcularMediaTurma(Aluno lista[], int tamanho){
	int i, qtd = 0;
	float acumulador = 0;
	for(i=0;i<tamanho;i++){
		if(lista[i].idMatricula != -1){
			acumulador += ((lista[i].ap1 + lista[i].ap2)/2.0);
			// ele vai procurar onde id for -1, e se for ele ira acumulando a media de cada aluno e incrementando a quantidade
			qtd++;
		}
	}
	// se qtd == 0 nao tera nenhum aluno na lista de alunos
	if(qtd == 0) printf("Lista de alunos vazia! \n");
	else{
	// se qtd != 0, ele ira pegar as medias acumuladas e dividir pela qtd de alunos da lista
		acumulador /= qtd;
		//printf("A media da turma eh: %f \n",acumulador);
		return acumulador;
	}
}

void imprimirAluno(Aluno a){
	// ele ira receber um aluno e ira mostrar todos os dados desse aluno
	printf("Matricula: %d \n",a.idMatricula);
	printf("Nome: %s \n",a.nome);
	printf("Ap1: %f \n",a.ap1);
	printf("Ap2: %f \n",a.ap2);
}

int buscaPorID(int idM, Aluno lista[], int tamanho, Aluno *n){
	// recebemos um id que devemos buscar na lista de Alunos
	int i, flag = 0;
	for(i=0;i<tamanho;i++){
		if(lista[i].idMatricula == idM){
			flag = 1;
			*n = lista[i];
			i = tamanho;
		}
		// se ele achar o id ele ira armazenar o aluno no ponteiro n e retornar 1
	}
	return flag;
}

int buscaPorNome(char nomeAux[], Aluno lista[], int tamanho, Aluno *n){
	// recebemos um nome que devemos buscar na lista de Alunos
	int i, flag = 0;
	for(i=0;i<tamanho;i++){
		if((strcmp(lista[i].nome,nomeAux)) == 0){
			flag = 1;
			*n = lista[i];
			i = tamanho;
		}
		// se ele achar o nome ele ira armazenar o aluno no ponteiro n e retornar 1
	}
	return flag;
}

void inicializar (Aluno *p, int tamanho){
	// precisamos iniciar os ids com -1 para indicar onde esses ids forem -1 eh como se essas posicoes na lista aluno tivessem vazias
	int i;
	for(i=0;i<tamanho;i++){
		p[i].idMatricula = -1;
		p[i].nome[0] = '\0';
		p[i].ap1 = 0.0;
		p[i].ap2 = 0.0;
	}
}

int qtdAlunos(Aluno *alunos, int tam){
	int count  = 0, i = 0;
	//printf("Tam: %d\n", tam );
	for(i = 0; i < tam; i++){
		if(alunos[i].idMatricula != -1){
			count++;
		}
	}
	return count;
}
