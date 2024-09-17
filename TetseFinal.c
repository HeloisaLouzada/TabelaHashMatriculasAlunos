//Heloísa Louzada Borchardt Gomes - V06

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <time.h>
#include "Tad_TabHash.h"

#define A 0.6180339887  // Utilizei a razão aurea como constante, vi em alguns trabalhos
#define MAX_NOME 100

long metodoMultiplicacao(long long int matricula, long tamanho){
    double val = matricula * A;  
    val = val - (long long int)val;      
    return (long)(tamanho * val); 
}


long metodoDivisao(long long int matricula, long tamanho){
    return matricula % tamanho; 
}


long hash(long long int matricula, long tamanho, int metodo){
    if (metodo == 1) {
        return metodoMultiplicacao(matricula, tamanho);
    } else {
        return metodoDivisao(matricula, tamanho);
    }
}


TabelaHash* criarTabelaHash(long tamanho){
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabela->tamanho = tamanho;
    tabela->tabelaAluno = (Aluno**)malloc(tamanho * sizeof(Aluno*));

    int i = 0;
    for (i = 0; i < tamanho; i++) {
        tabela->tabelaAluno[i] = NULL;
    }
    return tabela;
}


void inserir(TabelaHash* tabela, char* nome, long long int matricula, int metodo){
    long index = hash(matricula, tabela->tamanho, metodo);
    Aluno* novoAluno = (Aluno*)malloc(sizeof(Aluno));
    strcpy(novoAluno->nome, nome);
    novoAluno->matricula = matricula;
    novoAluno->prox = tabela->tabelaAluno[index];
    tabela->tabelaAluno[index] = novoAluno;
}


void remover(TabelaHash* tabela, long long int matricula, int metodo){
    long index = hash(matricula, tabela->tamanho, metodo);
    Aluno* atual = tabela->tabelaAluno[index];
    Aluno* anterior = NULL;

    while (atual != NULL && atual->matricula != matricula){
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL){
        printf("Matrícula não encontrada.\n");
        return;
    }

    if (anterior == NULL){
        tabela->tabelaAluno[index] = atual->prox;
    } else{
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Matrícula removida com sucesso.\n");
}


Aluno* pesquisar(TabelaHash* tabela, long long int matricula, int metodo){
    long index = hash(matricula, tabela->tamanho, metodo);
    Aluno* atual = tabela->tabelaAluno[index];

    while (atual != NULL){
        if (atual->matricula == matricula) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
}


void imprimir(TabelaHash* tabela){
    int i = 0;
    for (i = 0; i < tabela->tamanho; i++){
        Aluno* atual = tabela->tabelaAluno[i];
        
        while (atual != NULL) {
            printf("Posição %d-> ", i);
            printf("Nome: %s, Matrícula: %I64d\n", atual->nome, atual->matricula);
            atual = atual->prox;
        }
    }
}


long contarTotal(TabelaHash* tabela){
    int total = 0, i = 0;
    for (i = 0; i < tabela->tamanho; i++){
        Aluno* atual = tabela->tabelaAluno[i];
        while (atual != NULL) {
            total++;
            atual = atual->prox;
        }
    }
    return total;
}


void gravarArquivo(TabelaHash* tabela, char* nomeArquivo, char *modo){
    FILE* arq = fopen(nomeArquivo, modo);
    if (arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i = 0;
    for (i = 0; i < tabela->tamanho; i++){
        Aluno* atual = tabela->tabelaAluno[i];
        while (atual != NULL) {
            fprintf(arq, "%s\n", atual->nome);
            fprintf(arq, "%I64d\n", atual->matricula);
            atual = atual->prox;
        }
    }

    fclose(arq);
}


void carregarArquivo(TabelaHash* tabela, char* nomeArquivo, char *modo, int metodoEscolhido){
    FILE* arq = fopen(nomeArquivo, modo);
    if (arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    string nome;
    long long int matricula;

    while (fgets(nome, sizeof(nome), arq) != NULL){
        nome[strcspn(nome, "\n")] = '\0';  
        
        if (fscanf(arq, "%I64d\n", &matricula) == 1){  
            Aluno* aluno = pesquisar(tabela, matricula, metodoEscolhido);
            if (aluno == NULL) { 
                inserir(tabela, nome, matricula, metodoEscolhido);  
            }
        }    
    }

    fclose(arq);
}

//FUNÇÕES
long quantidadeElementos(char *nomeArq){
    FILE *arq = fopen(nomeArq, "rt"); 
    if (arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return -1;  
    }
        
    string nome;
    long long int matricula;    
    long quantidade = 0;   

    
    while (fgets(nome, sizeof(nome), arq) != NULL){  
        if (fscanf(arq, "%I64d\n", &matricula) == 1){  
            quantidade++;  
        }
    }

    fclose(arq);  
    printf("\t\tA quantidade de alunos é:%ld\n", quantidade);

    return quantidade;
}

int escolherTamanho(int baseDados){
    int opcao;
    printf("Escolha o tamanho do vetor Hash:\n");
    printf("1. 100%% do tamanho da base de dados\n");
    printf("2. 120%% do tamanho da base de dados\n");
    printf("3. 150%% do tamanho da base de dados\n");
    scanf("%d", &opcao);

    int tamanho;
    switch (opcao){
        case 1:
            tamanho = baseDados;
            break;
        case 2:
            tamanho = (baseDados * 120) / 100;
            break;
        case 3:
            tamanho = (baseDados * 150) / 100;
            break;
        default:
            printf("Opção inválida, usando 100%% por padrão.\n");
            tamanho = baseDados;
    }
    
    int i = 0;
    for (i = tamanho;; i++){
        int primo = 1;
        int j = 0;
        for (j = 2; j * j <= i; j++){
            if (i % j == 0) {
                primo = 0;
                break;
            }
        }
        if (primo){
            return i;
        }
    }
}

int escolherMetodo(){
    int opcao;
    printf("\nEscolha o método de dispersão:\n");
    printf("1. Multiplicação\n");
    printf("2. Divisão\n");
    scanf("%d", &opcao);

    if (opcao != 1 && opcao != 2){
        printf("Opção inválida. Seguindo com o método da multiplicação por padrão.\n");
        opcao = 1;
    }

    return opcao;
}


// FUNÇÃO PRINCIPAL
int main(){
    long baseDados = quantidadeElementos("nomes_matriculas.txt");
    int metodo = escolherMetodo();
    long tamanho = escolherTamanho(baseDados);

    clock_t inicio, fim;

    inicio = clock();
    TabelaHash* tabela = criarTabelaHash(tamanho);
    carregarArquivo(tabela, "nomes_matriculas.txt", "rt", metodo);
    fim = clock();
    printf("\t\t\t ->Tempo de inserção: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    int opcao;
    char nome[MAX_NOME];
    long long int matricula;

    

    do{
        printf("\nMenu:\n");
        printf("1. Inserir nova matrícula\n");
        printf("2. Cancelar matrícula\n");
        printf("3. Pesquisar matrícula\n");
        printf("4. Total de matrículas\n");
        printf("5. Imprimir matrículas\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                printf("Digite o nome do aluno: ");
                scanf("%s", nome);
               
                printf("Digite a matrícula: ");
                
                fflush(stdin);
            
                while (scanf("%I64d", &matricula) < 0){
                    printf("Entrada inválida. Digite a matrícula novamente: ");
                    fflush(stdin);
                }

                inserir(tabela, nome, matricula, metodo);
                break;

            case 2:
                printf("Digite a matrícula a ser removida: ");
                scanf("%I64d", &matricula);
                remover(tabela, matricula, metodo);
                fim = clock();
                printf("Tempo de remoção: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
                break;
                
            case 3:
                printf("Digite a matrícula para pesquisar: ");
                scanf("%I64d", &matricula);
                inicio = clock();
                Aluno* aluno = pesquisar(tabela, matricula, metodo);
                fim = clock();
                if (aluno != NULL){
                    printf("Aluno encontrado: %s, Matrícula: %I64d\n", aluno->nome, aluno->matricula);
                } else{
                    printf("Aluno não encontrado.\n");
                }
                printf("Tempo de pesquisa: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
                break;
                
            case 4:
                printf("Total de matrículas: \n\t\t%ld\n", contarTotal(tabela));
                break;
                
            case 5:
                imprimir(tabela);
                break;
                
            case 6:
                gravarArquivo(tabela, "nomes_matriculas.txt", "wt");
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 6);

    return 0;
}