#include "chamada.h"


lista_chamada *criar_lista_chamada(){
	lista_chamada *lista_chama=(lista_chamada*)malloc(sizeof(lista_chamada));
	lista_chama -> cabeca = NULL;
	return lista_chama;
}


void insere_chamada(lista_chamada *L, char data[], int matricula, char frequencia[], int ausencia) {

    // Aloca memória para o novo nó
    no_chamada *novo = (no_chamada*)malloc(sizeof(no_chamada));
    if (novo == NULL) {
        printf("Erro ao alocar memória para nova chamada.\n");
        exit(1);
    }
    
    // Preenche os dados do novo nó
    strcpy(novo->data, data);
    strcpy(novo->frequencia, frequencia);
    novo->matricula = matricula;
    novo->ausencia = ausencia;
    
    // Faz o novo nó apontar para o antigo primeiro nó
    novo->prox = L->cabeca;

    // Atualiza a cabeça da lista para o novo nó
    L->cabeca = novo;
}

void imprime_chamada(lista_chamada *L) {
    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de chamada vazia.\n");
        return;
    }

    no_chamada *busca = L->cabeca; // Começa da primeira avaliacao real, não da cabeça
    while (busca != NULL) {
        printf("%s %d %s %d\n", busca->data, busca->matricula, busca->frequencia, busca -> ausencia);
        busca = busca->prox;
    }
}

void conta_ausencia(lista_chamada *L, int matricula){
	int cont = 0;

	if (L == NULL || L->cabeca == NULL) {
        printf("Lista de chamada vazia.\n");
        return;
    }

    no_chamada *busca = L->cabeca; // Começa da primeira avaliacao real, não da cabeça
    while (busca != NULL) {
        if(busca->matricula == matricula){
            if(strcmp(busca->frequencia, "ausente") == 0){
                cont++;
            }   
        }
        busca = busca->prox;
    }

    if(cont == 10){
    	printf("Aluno reprovado por infrequência.\n");
    }

    printf("\nausencia: %d\n", cont);

}

void imprime_chamada_nome(lista_chamada *L, int matricula) {
    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de chamada vazia.\n");
        return;
    }

    no_chamada *busca = L->cabeca; // Começa da primeira avaliacao real, não da cabeça
    while (busca != NULL && busca -> matricula == matricula) {
        printf("%s %s\n", busca->data,busca->frequencia);
        busca = busca->prox;
    }
}

void imprime_chamada_data(lista_chamada *L) {
    int cont = 0;
    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de chamada vazia.\n");
        return;
    }

    no_chamada *busca = L->cabeca; // Começa da primeira avaliacao real, não da cabeça
    while (busca != NULL) {
        printf("%s \n", busca->data);
        busca = busca->prox;    
    }
}


int data_existe(lista_chamada *L, char data[]) {
    no_chamada *busca = L->cabeca;
    while (busca != NULL) {
        if (strcmp(busca->data, data) == 0) {
            return 1; // Data já existe
        }
        busca = busca->prox;
    }
    return 0; // Data não existe
}

