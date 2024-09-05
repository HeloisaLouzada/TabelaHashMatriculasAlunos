typedef struct tipoAluno{
     int matricula;
     char nome[50];
     struct tipoAluno *prox;
}TAluno;

typedef struct tipoLista{
    TAluno *inicio;
    TAluno *fim;
    int total;
}TLista;

FILE * abrirArquivo(char * nomeArq, char * modo);

int quantidadeElementos(char *nomeArq);

void leituraArquivo(TLista *Lista, char *nomeArq);

void gravarArquivo(FILE *arquivo, TLista *Lista);

TLista * tamanhoVetor(TLista * lista, int qntd); 