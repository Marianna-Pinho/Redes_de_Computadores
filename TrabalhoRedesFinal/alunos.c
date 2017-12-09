#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matricula;

typedef struct{
	int idMatricula;
	char nome[100];
	float ap1;
	float ap2;
}Aluno;

void menu(){
	// A funcao menu ira mostrar as opcoes que o usuario tem em nosso sistema
	printf("\t\t Digite:\n");
	printf("\t 1 - Para cadastrar Aluno \n");
	printf("\t 2 - Para pesquisar Aluno \n");
	printf("\t 3 - Para editar Aluno \n");
	printf("\t 4 - Para excluir Aluno \n");
	printf("\t 5 - Para calcular media do Aluno \n");
	printf("\t 6 - Para calcular media da turma \n");
	printf("\t 7 - Para sair \n");
}

void receber(Aluno *p){
	// A funcao recerber tem como parametro um ponteiro de aluno, onde o iremos salvar os dados de um novo aluno no endereco mandado na funcao main
	printf("Digite o nome do aluno: ");
	scanf("%s",p->nome);
	printf("Digite a nota da ap1 do aluno: ");
	scanf("%f",&(p->ap1));
	printf("Digite a nota da ap2 do aluno: ");
	scanf("%f",&(p->ap2));
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

void editar(Aluno lista[], int tamanho, int idAux){
	// vai percorrer toda a lista de alunos e procurar onde tem o id que usou pra busca
	int i;
	for(i=0;i<tamanho;i++){
		if(lista[i].idMatricula == idAux){
			receber(&lista[i]);
			// quando achar ele ira recber novamente os dados desse aluno
			i = tamanho;
		}
	}
}

void excluir(Aluno lista[], int tamanho, int idAux){
	// vai percorrer toda a lista de alunos e procurar onde tem o id que usou pra busca
	int i;
	for(i=0;i<tamanho;i++){
		if(lista[i].idMatricula == idAux){
			lista[i].idMatricula = -1;
			// quando achar esse id ele ira modificar o idMatricula do aluno para -1 (ele ira excluir o aluno)
			i = tamanho;
		}
	}
}

void calcular(Aluno lista[], int tamanho, int idAux){
	// vai percorrer toda a lista de alunos e procurar onde tem o id que usou pra busca
	int i;
	for(i=0;i<tamanho;i++){
		if(lista[i].idMatricula == idAux){
			printf("A media do aluno eh: %f \n",((lista[i].ap1 + lista[i].ap2)/2.0));
			// quando achar ele ira calcular e mostrar a media
			i = tamanho;
		}
	}
}

void calcularMediaTurma(Aluno lista[], int tamanho){
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
		printf("A media da turma eh: %f \n",acumulador);
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
	}
}

int main(){
	matricula = 0;
	
	printf("\t Bem-vindo ao sistema de controle escolar!\n");
	
	int tam, opc = 0;
	char aux;
	printf("Digite o tamanho maximo da classe: ");
	scanf("%d",&tam);
	
	// ponteiro recebe malloc para guardar o espaço igual ao que for recebido no tamanho
	
	Aluno *vetor = malloc(sizeof(Aluno)*tam);
	
	inicializar(vetor,tam);
	
	while(opc != 7){
		menu();
		scanf("%d",&opc);
		while(opc<1||opc>7){
			printf("Opcao invalida!\n");
			menu();
			scanf("%d",&opc);
		}
		Aluno a;
		int retorno;
		if(opc == 1){
			receber(&a);
			retorno = cadastrar(vetor,a,tam);
			if(retorno == 1) printf("Aluno cadastrado com sucesso!\n");
			else printf("Aluno nao cadastrado com sucesso!\n");
		}else if(opc == 2){
			int opc1 = 0;
			while(opc1<1||opc1>2){
				printf("\t Digite:\n");
				printf("\t 1 - Para pesquisar por matricula \n");
				printf("\t 2 - Para pesquisar por nome \n");
				scanf("%d",&opc1);
				if(opc1<1||opc1>2) printf("Opcao invalida! ");
			}
			if(opc1 == 1){
				int idaux;
				printf("Digite a matricula do aluno que deseja buscar: ");
				scanf("%d",&idaux);
				retorno = buscaPorID(idaux,vetor,tam,&a);
				if(retorno == 1) imprimirAluno(a);
				else printf("Aluno nao encontrado! \n");
			}
			else{
				char nomeaux[100];
				printf("Digite o nome do aluno que deseja buscar: ");
				scanf("%s",nomeaux);
				retorno = buscaPorNome(nomeaux,vetor,tam,&a);
				if(retorno == 1) imprimirAluno(a);
				else printf("Aluno nao encontrado! \n");
			}
		}else if(opc == 3){
			int idaux;
			printf("Digite a matricula do aluno que deseja editar: ");
			scanf("%d",&idaux);
			retorno = buscaPorID(idaux,vetor,tam,&a);
			if(retorno == 1){ 
				editar(vetor,tam,idaux);
				printf("Aluno editado com sucesso!\n");
			}
			else printf("Aluno nao encontrado! \n");
		}else if(opc == 4){
			int idaux;
			printf("Digite a matricula do aluno que deseja excluir: ");
			scanf("%d",&idaux);
			retorno = buscaPorID(idaux,vetor,tam,&a);
			if(retorno == 1){ 
				excluir(vetor,tam,idaux);
				printf("Aluno excluido com sucesso!\n");
			}
			else printf("Aluno nao encontrado! \n");
		}else if(opc == 5){
			int idaux;
			printf("Digite a matricula do aluno que deseja calcular media: ");
			scanf("%d",&idaux);
			retorno = buscaPorID(idaux,vetor,tam,&a);
			if(retorno == 1){ 
				calcular(vetor,tam,idaux);
			}
			else printf("Aluno nao encontrado! \n");
		}else if(opc == 6){
			calcularMediaTurma(vetor,tam);
		}else if(opc == 7){
        // quando o usuario sair do progrma o espaço reservado precisa ser liberado		
			free(vetor);
		}
		// serve guardar o \n 
		// se nao tivesse no scanf ele nao pausaria para receber o char
		getchar();
		printf("Aperte ENTER para limpar sua tela...");
		scanf("%c",&aux);
        // system é alguma coisa que vc pede para o programa fazer nesse caso limpar 
		system("clear");
	}
	
	printf("Voce saiu! :( \n");
	
	return 0;
}
