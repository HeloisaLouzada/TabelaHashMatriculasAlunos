#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tad_TabHash.h"

// Número primo como divisor
long hash(long long int matricula, long tamanho) {
    return matricula % tamanho;
}

TabelaHash* criarTabelaHash(long tamanho) {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabela->tamanho = tamanho;
    tabela->tabelaAluno = (Aluno**)malloc(tamanho * sizeof(Aluno*));

    int i = 0;
    for (i = 0; i < tamanho; i++) {
        tabela->tabelaAluno[i] = NULL;
    }
    return tabela;
}


void inserir(TabelaHash* tabela, char* nome, long long int matricula) {
    long index = hash(matricula, tabela->tamanho);
    Aluno* novoAluno = (Aluno*)malloc(sizeof(Aluno));
    strcpy(novoAluno->nome, nome);
    novoAluno->matricula = matricula;
    novoAluno->prox = tabela->tabelaAluno[index];
    tabela->tabelaAluno[index] = novoAluno;
}


void remover(TabelaHash* tabela, long long int matricula) {
    long index = hash(matricula, tabela->tamanho);
    Aluno* atual = tabela->tabelaAluno[index];
    Aluno* anterior = NULL;

    while (atual != NULL && atual->matricula != matricula) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Matrícula não encontrada.\n");
        return;
    }

    if (anterior == NULL) {
        tabela->tabelaAluno[index] = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Matrícula removida com sucesso.\n");
}


Aluno* pesquisar(TabelaHash* tabela, long long int matricula) {
    long index = hash(matricula, tabela->tamanho);
    Aluno* atual = tabela->tabelaAluno[index];

    while (atual != NULL) {
        if (atual->matricula == matricula) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
}


void imprimir(TabelaHash* tabela) {
    int i = 0;
    for (i = 0; i < tabela->tamanho; i++) {
        Aluno* atual = tabela->tabelaAluno[i];
        
        while (atual != NULL) {
            printf("Posição %d-> ", i);
            printf("Nome: %s, Matrícula: %I64d\n", atual->nome, atual->matricula);
            atual = atual->prox;
        }
    }
}


long contarTotal(TabelaHash* tabela) {
    int total = 0, i = 0;
    for (i = 0; i < tabela->tamanho; i++) {
        Aluno* atual = tabela->tabelaAluno[i];
        while (atual != NULL) {
            total++;
            atual = atual->prox;
        }
    }
    return total;
}

// Coloca dentro do arquivo de boaaaa
void gravarArquivo(TabelaHash* tabela, char* nomeArquivo, char *modo) {
    FILE* arq = fopen(nomeArquivo, modo);
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i = 0;
    for (i = 0; i < tabela->tamanho; i++) {
        Aluno* atual = tabela->tabelaAluno[i];
        while (atual != NULL) {
            fprintf(arq, "%s\n", atual->nome);
            fprintf(arq, "%I64d\n", atual->matricula);
            atual = atual->prox;
        }
    }

    fclose(arq);
}

void carregarArquivo(TabelaHash* tabela, char* nomeArquivo, char *modo) {
    FILE* arq = fopen(nomeArquivo, modo);
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    string nome;
    long long int matricula;

    while (fgets(nome, sizeof(nome), arq) != NULL) {
        nome[strcspn(nome, "\n")] = '\0';  // Função nova EBAAAAA!! strcspn acha o '\n' e troca '\0'
        
        if (fscanf(arq, "%I64d\n", &matricula) == 1) {  
            Aluno* aluno = pesquisar(tabela, matricula);
            if (aluno == NULL) { // Procura para ver se o aluno já não existe
                inserir(tabela, nome, matricula);  
            }
        }    
    }

    fclose(arq);
}

//FUNÇÕES
long quantidadeElementos(char *nomeArq) {
    FILE *arq = fopen(nomeArq, "rt"); 
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;  
    }
        
    string nome;
    long long int matricula;    
    long quantidade = 0;   

    
    while (fgets(nome, sizeof(nome), arq) != NULL) {  
        if (fscanf(arq, "%I64d\n", &matricula) == 1) {  
            quantidade++;  
        }
    }

    fclose(arq);  
    printf("\t\tA quantidade de alunos é:%ld\n", quantidade);

    return quantidade;
}

int escolherTamanho(int baseDados) {
    int opcao;
    printf("Escolha o tamanho do vetor Hash:\n");
    printf("1. 100%% do tamanho da base de dados\n");
    printf("2. 120%% do tamanho da base de dados\n");
    printf("3. 150%% do tamanho da base de dados\n");
    scanf("%d", &opcao);

    int tamanho;
    switch (opcao) {
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

    // Procurar número primo maior ou igual ao tamanhooooo
    int i = 0;
    for (i = tamanho;; i++) {
        int primo = 1;
        int j = 0;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                primo = 0;
                break;
            }
        }
        if (primo) {
            return i;
        }
    }
}

int escolherMetodo(){
    int opcao = 1;

    printf("Escolha o metodo de dispersão:\n");
    printf("1. Multiplicação\n");
    printf("2. Divisão\n");
    scanf("%d", &opcao);

    int tamanho;
    switch (opcao) {
        case 1:
            opcao = 1;
            break;
        case 2:
            opcao = 2;
            break;
        default:
            printf("Opção inválida. Seguindo com o metodo da multiplicação por padrão.\n");
    }

    return opção;
}

/*long metodos(int escolha){
    if(escolha == 1){
        multiplicação();
    }else{
        divisão();
    }

}
*/
// Função principal (menu)
int main() {
    int metodo = 0;

    long baseDados = quantidadeElementos("nomes_matriculas.txt"); //pega a quantidade de elementos do arquivinho fofo
    //metodo escolherMetodo();
    long tamanho = escolherTamanho(baseDados); //Escolhe o tamanho do vetor e já calcula bemmm bonito

    TabelaHash* tabela = criarTabelaHash(tamanho); //cria a tabelinhaaaa

    carregarArquivo(tabela, "nomes_matriculas.txt", "rt");

    int opcao;
    string nome;
    long long int matricula;
    clock_t inicio, fim;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova matrícula\n");
        printf("2. Cancelar matrícula\n");
        printf("3. Pesquisar matrícula\n");
        printf("4. Total de matrículas\n");
        printf("5. Imprimir matrículas\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do aluno: ");
                scanf("%s", nome);
                printf("Digite a matrícula: ");
                scanf("%I64d", &matricula);
                //metodo = escolherMetodo();
                inicio = clock();
                inserir(tabela, nome, matricula);//Fazer uma função com if e else para dividir os tamanhos
                fim = clock();
                printf("Tempo de inserção: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
                break;
            case 2:
                printf("Digite a matrícula a ser removida: ");
                scanf("%I64d", &matricula);
                inicio = clock();
                remover(tabela, matricula);
                fim = clock();
                printf("Tempo de remoção: %lf segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
                break;
            case 3:
                printf("Digite a matrícula para pesquisar: ");
                scanf("%I64d", &matricula);
                inicio = clock();
                Aluno* aluno = pesquisar(tabela, matricula);
                fim = clock();
                if (aluno != NULL) {
                    printf("Aluno encontrado: %s, Matrícula: %I64d\n", aluno->nome, aluno->matricula);
                } else {
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
                // Salvaaaaar os dados no arquivo antes de sair por favor
                gravarArquivo(tabela, "nomes_matriculas.txt", "wt");
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 6);

    return 0;
}
