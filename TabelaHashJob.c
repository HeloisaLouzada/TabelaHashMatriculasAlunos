#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Tad_TabHash.h"

// MANIPULAÇÃO DE ARQUIVO
FILE *abrirArquivo(char *nomeArq, char *modo) {
    FILE *arq = fopen(nomeArq, modo);
    if (arq == NULL) {
        printf("ERRO ao abrir o arquivo.\n");
    }

    fclose(arq);
    return arq;
}

#include <stdio.h>

long quantidadeElementos(char *nomeArq) {
    FILE *arq = fopen(nomeArq, "rt");  // Abrir o arquivo em modo leitura "rt"
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;  // Retornar -1 para indicar erro
    }

    char nome[100];        // Buffer para o nome do aluno
    char matricula[20];    // Buffer para a matrícula do aluno
    long quantidade = 0;   // Contador de alunos

    // Loop para ler nome e matrícula em pares
    while (fgets(nome, sizeof(nome), arq) != NULL) {  // Lê o nome do aluno
        if (fgets(matricula, sizeof(matricula), arq) != NULL) {  // Lê a matrícula do aluno
            quantidade++;  // Incrementa a quantidade de alunos
        }
    }

    fclose(arq);  // Fecha o arquivo após a leitura
    printf("A quantidade de alunos é: %ld\n", quantidade);

    return quantidade;
}


void inicializa(TLista *Lista) {
    Lista->inicio = NULL;
    Lista->fim = NULL;
    Lista->total = 0;
}


// VETOR

long menuTamanhoVetor(long quantidadeMatricula) {
    int opcao;
    long tamanho = 0;
    
    printf("\n\nTAMANHOS DO VETOR\n\n");
    printf("1 - 100%%\n");
    printf("2 - 120%%\n");
    printf("3 - 150%%\n");
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
            tamanho = (long)(1.0*quantidadeMatricula);  // 100%
            break;
        case 2:
            tamanho = (long)(1.2*quantidadeMatricula);  // 120%
            break;
        case 3:
            tamanho = (long)(1.5*quantidadeMatricula);  // 150%
            break;

        default:
            printf("\n\nOpção inválida!\n\n");
            break;
    }


    printf("Esse é o tamanho selecionado: %ld\n", tamanho);  // Usa %f para float
    
    return tamanho;
}

//FUNÇÕES
    //SORTEAR NUMERO PRIMO
// Função para verificar se um número é primo
int ehPrimo(int num) {
    int i;
    if (num <= 1) return 0;  // Números menores ou iguais a 1 não são primos
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;  // Se for divisível por qualquer número além de 1 e ele mesmo, não é primo
        }
    }
    return 1;  // Se passou por todos os testes, é primo
}

// Função para sortear um número primo dentro de um intervalo
int sortearNumeroPrimo(int min, int max) {
    int num;
    
    // Continuar sorteando números até encontrar um primo
    do {
        num = rand() % (max - min + 1) + min;  // Sorteia um número entre min e max
    } while (!ehPrimo(num));  // Continua até encontrar um número primo
    
    return num;
}

//CALCULO
long calculoHash(long matriculas, long vetor, int k){
    long chave = (long)(vetor % k);
    chave = (long)(chave*matriculas); 

    printf("A chave é: %ld\n", chave);

    return chave;
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
    int op;
    long numero = 0;
    long tamanhoVetor = 0;
    int primo = 0;
    TLista lista;

    do {
        op = menu();
        switch (op) {
        case 0:
            break;

        case 1:
            // Abrir arquivo para contar elementos
            arquivo = abrirArquivo("nomes_matriculas.txt", "rt");
            numero = quantidadeElementos("nomes_matriculas.txt");
            printf("Quantidade de elementos: %ld\n", numero);

            // Escolher tamanho do vetor e calcular
            tamanhoVetor = menuTamanhoVetor(numero);
            printf("Esse é o tamanho do vetor:%ld\n", tamanhoVetor);  
            
            // Inicializar lista
            inicializa(&lista);

            primo = sortearNumeroPrimo(0, 10);
            printf("Número primo sorteado: %d\n", primo);
     
            calculoHash(numero, tamanhoVetor, primo);

            break;

        default:
            printf("\n\nOpção inválida!\n\n");
            break;
        }
    } while (op != 0);

    return 0;
}