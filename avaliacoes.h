#ifndef AVALIACOES_H
#define AVALIACOES_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Avaliacoes{
	char nome_avaliacao[50];
	float valor_total;
	int matricula_aluno;
	float nota_aluno;
	struct Avaliacoes *prox;
}no_avaliacao;

typedef struct Lista_aval{
	no_avaliacao *cabeca;
}lista_avaliacoes;

lista_avaliacoes *criar_lista_avaliacoes();

//void insere_avaliacao(lista_avaliacoes *L, char nome_avaliacao[], float valor_total, int matricula_aluno, float nota_aluno);

void imprime_avaliacao(lista_avaliacoes *L, char nome_avaliacao[]);

float nota_max(lista_avaliacoes *L, char nome_avaliacao[]);

float nota_min(lista_avaliacoes *L, char nome_avaliacao[]);

float nota_med(lista_avaliacoes *L, char nome_avaliacao[]);

float soma_todas_as_notas(lista_avaliacoes *lista, int matricula);

void ordenar_notas_descrescente(lista_avaliacoes *L, const char *nome_avaliacao);

void imprime_avaliacoes_ordenadas(lista_avaliacoes *L, const char *nome_avaliacao);

void imprime_avaliacoes(lista_avaliacoes* L);

#endif