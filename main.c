#include <stdio.h>
#include <stdlib.h>
#include "gcofo.h"
#include <stddef.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

  
typedef struct _aluno_ {
    char nome[30];
    int numero;
    float nota;

} Aluno;

typedef struct _gcofo_ {
int numItens;
int maxItens;
int cur;
void **item; // int *item;
} GCofo;



int main() {
    int resposta, cont = 1, maxItens, escolha;
    char nome[30];
    float nota;
    GCofo* cofo = NULL;
    Aluno* aluno;

    do {
        printf("\033[2J \033[H");

        printf("Pergunta:\n");
        printf("1 - Criar um cofo\n");
        printf("2 - Inserir elementos no cofo\n");
        printf("3 - Listar os elementos do cofo\n");
        printf("4 - Consultar um dos elementos do cofo\n");
        printf("5 - Remover algum elemento do cofo\n");
        printf("6 - Esvaziar o cofo\n");
        printf("7 - Destruir o cofo\n");
        resposta = -1;
        scanf("%d", &resposta);
        switch (resposta) { 
            case 1:
                printf("Digite a quantidade de itens pra botar no cofo:\n");
                scanf("%d", &maxItens);

                cofo = gcofCreate(maxItens);

                if (cofo != NULL) {
                    printf("Cofo criado com sucesso!\n");

                } else {
                    printf("Erro ao fazer o cofo\n");
                }
                break;
            
            case 2:
                if (cofo == NULL) {
                    printf("Aloque primeiro o cofo\n");
                    break;
                }

                if (cofo->maxItens <= cofo->numItens) {
                    printf("Cofo já cheio\n");
                    break;
                }

                aluno = (Aluno*)malloc(sizeof(Aluno));

                if (aluno == NULL) {
                    printf("Não pude alocar aluno. Saindo\n");
                    break;
                }
                printf("Digite o nome do aluno: ");
                scanf("%s", aluno->nome);
                while(getchar() != '\n'); // Limpa o stdin caso a pessoa tenha digitado um sobrenome

                printf("Digite o numero do aluno: ");
                scanf("%d", &aluno->numero);

                printf("Digite a nota do aluno: \n");
                scanf("%f", &aluno->nota);

                gcofInsert(cofo, (void*)aluno);

                printf("Aluno %s, com numero %d e nota %.2f inserido com sucesso\n", aluno->nome, aluno->numero, aluno->nota);
                break;

            case 3:
                if (cofo == NULL) {
                    printf("Aloque primeiro o cofo\n");
                    break;
                }

                if (cofo->numItens == 0) {
                    printf("Bote algo no cofo antes!\n");
                    break;
                }

                for (int i = 0; i < cofo->numItens; i++) {
                    aluno = cofo->item[i];
                    printf("Aluno %s, índice %d, numero %d, nota %.2f\n", aluno->nome, i, aluno->numero, aluno->nota);
                }
                
                break;
            
            case 4:
                if (cofo == NULL) {
                    printf("Aloque primeiro o cofo\n");
                    break;
                }

                if (cofo->numItens == 0) {
                    printf("Bote algo no cofo antes!\n");
                    break;
                }

                printf("Você deseja procurar por:\n");
                printf("1 - Nome\n");
                printf("2 - Numero\n");
                printf("3 - Nota\n");
                scanf("%d", &escolha);

                switch (escolha) {
                    case 1:
                        printf("Digite o nome a procurar: ");
                        scanf("%s", nome);
                        aluno = gcofQuery(cofo, (void*)nome, QueryAlunoNome);
                        break;
                    case 2:
                        printf("Digite o numero a procurar: ");
                        scanf("%d", &resposta);
                        aluno = gcofQuery(cofo, (void*)&resposta, QueryAlunoNumero);  
                        break;
                    case 3:
                        printf("Digite a nota a procurar: ");
                        scanf("%f", &nota);
                        aluno = gcofQuery(cofo, (void*)&nota, QueryAlunoNota);
                }
                if (aluno != NULL) {
                    printf("Aluno encontrado: \n");
                    printf("Nome: %s\n", aluno->nome);
                    printf("numero: %d\n", aluno->numero);
                    printf("Nota: %.2f\n", aluno->nota);
                } else {
                    printf("Aluno não encontrado!\n");
                }
                break;

            case 5:
                if (cofo == NULL) {
                    printf("Aloque primeiro o cofo\n");
                    break;
                }

                if (cofo->numItens == 0) {
                    printf("Bote algo no cofo antes!\n");
                    break;
                }

                printf("Você deseja procurar por:\n");
                printf("1 - Nome\n");
                printf("2 - numero\n");
                printf("3 - Nota\n");
                scanf("%d", &escolha);

                switch (escolha) {
                    case 1:
                        printf("Digite o nome a procurar: ");
                        scanf("%s", nome);
                        aluno = gcofQuery(cofo, (void*)nome, QueryAlunoNome);
                        break;
                    case 2:
                        printf("Digite o numero a procurar: ");
                        scanf("%d", &resposta);
                        aluno = gcofQuery(cofo, (void*)&resposta, QueryAlunoNumero);
                        break;
                    case 3:
                        printf("Digite a nota a procurar: ");
                        scanf("%f", &nota);
                        aluno = gcofQuery(cofo, (void*)&nota, QueryAlunoNota);
                }

                if (aluno != NULL) {
                    printf("Você deseja remover esse objeto:\n");
                    printf("Nome: %s\n", aluno->nome);
                    printf("numero: %d", aluno->numero);
                    printf("Nota: %.2f\n", aluno->nota);
                    printf("Digite 1 para apagar e outro número para cancelar\n");

                    scanf("%d", &escolha);
                    switch(escolha) {
                        case 1:
                            gcofRemove(cofo, aluno);
                            break;
                    }
                }
                break;
            case 6:
                if (cofo == NULL) {
                    printf("Aloque primeiro o cofo\n");
                    break;
                }

                if (cofo->numItens == 0) {
                    printf("Bote algo no cofo antes!\n");
                    break;
                }
                gcofEsvaziar(cofo);
                printf("O cofo foi esvaziado!\n");
                break;
            case 7:
                if (cofo == NULL) {
                    printf("Aloque primeiro o cofo\n");
                    break;
                }

                if (cofo->numItens != 0) {
                    printf("O cofo deve estar vazio!\n");
                    break;
                }
                gcofDestroy(cofo);
                cofo = NULL;
                break;
            default:
                printf("Saindo\n");
                cont=0;
        }

        printf("Pressione um botão para continuar\n");
        while(getchar() != '\n'); // Limpa o stdin
        getchar(); // Espera a pessoa digitar ENTER

    }while (cont);

    if (cofo != NULL) {
        gcofEsvaziar(cofo);
    }
}