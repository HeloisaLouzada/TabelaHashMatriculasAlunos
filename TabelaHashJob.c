//Heloísa Louzada Borchardt Gomes - V06

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Tad_TabHash.h"

/*
Escolher Tamanho do Vetor Hash
100%
120%
150%
Inserir Nova Matrícula
Cancelar Matrícula (ou Remover Matrícula)
Pesquisar Matrícula
Total de Matrículas
Imprimir Matrículas */

//MANIPULAÇÃO DE ARQUIVO..............................
FILE * abrirArquivo(char * nomeArq, char * modo) {
    FILE * arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
    }

    return arq;
}

void leituraArquivo(TLista *Lista, char *nomeArq) {
    FILE *arq = abrirArquivo(nomeArq, "rt");
    int numeroMatricula;

    while (fscanf(arq, "%d", &numeroMatricula) == 1) {
        if(buscar(Lista,numeroMatricula) == -1){
            inserirLista(Lista, numeroMatricula);
        }
    }
    
    fclose(arq);
}

void gravarArquivo(FILE *arquivo, TLista *Lista) {
    TElemento *atual = Lista->inicio;
        
    while (atual != NULL) {
        fprintf(arquivo, "%d\n", atual->valor);
        atual = atual->prox;
    }
}

//VETOR
void tamanhoVetor(){
  

}

//FUNÇÕES

//MENU.........................................................................
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

        } while(op < 0 || op > 6);
        return op;
    }

//FUNÇÃO PRINCIPAL

int main (){
    SetConsoleOutputCP(65001);
    TAluno listaMatriculas[];
    FILE * arquivo = NULL;
    int op, numero = 0;
    TLista lista;
    inicializa (&lista);

    do {
    op = menu();
    switch (op) {
    case 0:
          
        break;
        
    case 1:
       
        break;

    case 2:
        
        break;

    case 3:
         
        break;

    case 4:
        
        break;

    case 5:
        
        break;

    case 6:
           
        break;  

    default:
        printf("\n\nOpção inválida!\n\n");
        break;
    }
} while (op != 0);
    return 0;
}