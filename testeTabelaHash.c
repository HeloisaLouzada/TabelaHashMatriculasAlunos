#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Tad_TabHash.h"

// MANIPULAÇÃO DE ARQUIVO
FILE * abrirArquivo(char *nomeArq, char *modo) {
    FILE *arq = fopen(nomeArq, modo);
    if (arq == NULL) {
        printf("ERRO ao abrir o arquivo.\n");
    } else {
        printf("Arquivo aberto\n");
    }
    return arq;
}

int quantidadeElementos(char *nomeArq) {
    FILE *arq = abrirArquivo(nomeArq, "rt");
    int numeroMatricula, quantidade = 0;

    if (arq == NULL) {
        return 0;
    }

    while (fscanf(arq, "%d", &numeroMatricula) == 1) {
        quantidade++;
    }

    fclose(arq);
    return quantidade;
}

void inicializa(TLista *Lista) {
    Lista->inicio = NULL;
    Lista->fim = NULL;
    Lista->total = 0;
}

// VETOR
float menuTamanhoVetor() {
    int opcao;
    float tamanho = 0;

    printf("\n\nTAMANHOS DO VETOR\n\n");
    printf("1 - 100\n");
    printf("2 - 120\n");
    printf("3 - 150\n");
    printf("0 - Sair\n\n");

    do {
        printf("Escolha sua opção: ");
        scanf("%d", &opcao);
        if (opcao < 0 || opcao > 3) {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao < 0 || opcao > 3);

    switch (opcao) {
        case 0:
            printf("Saindo...\n");
            return 0;

        case 1:
            tamanho = 1.0;  // Tamanho 100%
            printf("Tamanho 100\n");
            break;
        case 2:
            tamanho = 1.2;  // 120% do valor original
            printf("Tamanho 120\n");
            break;
        case 3:
            tamanho = 1.5;  // 150% do valor original
            printf("Tamanho 150\n");
            break;

        default:
            printf("\n\nOpção inválida!\n\n");
            break;
    }

    return tamanho;
}

// MENU
int menu() {
    int op;
    printf("\n\nSISTEMA PEDIDOS\n\n");
    printf("1 - Escolher Tamanho do Vetor Hash\n");
    printf("2 - Inserir Nova Matrícula\n");
    printf("3 - Cancelar Matrícula (ou Remover Matrícula)\n");
    printf("4 - Pesquisar matrícula\n");
    printf("5 - Total de matrículas\n");
    printf("6 - Exibir matrículas\n");
    printf("0 - Sair\n\n");

    do {
        printf("Escolha sua opção: ");
        scanf("%d", &op);
        if (op < 0 || op > 6) {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (op < 0 || op > 6);

    return op;
}

// FUNÇÃO PRINCIPAL
int main() {
    SetConsoleOutputCP(65001);
    FILE *arquivo = NULL;
    int op, numero = 0;
    float tamanhoVet = 0;
    float resultado=0;
    TLista lista;

    do {
        op = menu();
        switch (op) {
            case 0:
                break;

            case 1:
                arquivo = abrirArquivo("nomes_matriculas.txt", "rt");
                if (arquivo == NULL) {
                    printf("Não foi possível criar o arquivo.\n");
                    break;
                }
                numero = quantidadeElementos("nomes_matriculas.txt");
                fclose(arquivo);
                printf("Número de elementos: %d\n", &numero);

                // LISTA
                inicializa(&lista);
                tamanhoVet = menuTamanhoVetor();
                printf("Esse é o tamanho do vetor: %.2f\n", tamanhoVet);
                // Multiplica o tamanho pelo número de elementos
                resultado = tamanhoVet*numero;

                // Corrige a impressão do valor float
                printf("Esse é o tamanho do vetor: %.2f\n", resultado);

                
                break;

            default:
                printf("\n\nOpção inválida!\n\n");
                break;
        }
    } while (op != 0);

    return 0;
}
