typedef char string[40];

typedef struct tipoAluno{
     long matricula;
     string nome;
     struct tipoAluno *prox;
}TAluno;

typedef struct tipoLista{
    TAluno *inicio;
    TAluno *fim;
    int total;
}TLista;


FILE * abrirArquivo(char * nomeArq, char * modo);

long quantidadeElementos(char *nomeArq);

void inicializa (TLista *Lista);

long menuTamanhoVetor();

int ehPrimo(int num);

int sortearNumeroPrimo(int min, int max);

long calculoHash(long matriculas, long vetor, int k);

/*void leituraArquivo(TLista *tabela, char *nomeArq);

void gravarArquivo(FILE *arquivo, TLista *Lista);

TLista * tamanhoVetor(TLista * lista, int qntd); 

int buscar(TLista *lista, int matricula);*/