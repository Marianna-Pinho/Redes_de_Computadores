typedef struct{
	int idMatricula;
	char nome[100];
	float ap1;
	float ap2;
}Aluno;


void menu();
void receber(Aluno *p);
int cadastrar(Aluno lista[], Aluno novoAluno, int tamanho);
void editar(Aluno lista[], int idM, int tamanho, Aluno aluno);
void excluir(Aluno lista[], int tamanho, int idAux);
float calcular(Aluno lista[], int tamanho, int idAux);
float calcularMediaTurma(Aluno lista[], int tamanho);
void imprimirAluno(Aluno a);
int buscaPorID(int idM, Aluno lista[], int tamanho, Aluno *n);
int buscaPorNome(char nomeAux[], Aluno lista[], int tamanho, Aluno *n);
void inicializar (Aluno *p, int tamanho);
int qtdAlunos(Aluno *alunos, int tam);
int verClasse(Aluno *alunos, int tam);