#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct chamada{
	char data[10];
	int matricula;
	char frequencia[15];
	int ausencia;
	struct chamada *prox;
}no_chamada;

typedef struct Lista_chamada{
	no_chamada *cabeca;
}lista_chamada;

void insere_chamada(lista_chamada *L, char data[], int matricula, char frequencia[], int ausencia);

lista_chamada *criar_lista_chamada();

void imprime_chamada(lista_chamada *L);

void conta_ausencia(lista_chamada *L, int matricula);

void imprime_chamada_nome(lista_chamada *L, int matricula);

void imprime_chamada_data(lista_chamada *L);

int data_existe(lista_chamada *L, char data[]);