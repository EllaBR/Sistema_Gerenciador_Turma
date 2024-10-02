#ifndef ALUNOS_H
#define ALUNOS_H

#include "avaliacoes.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 49




typedef struct Aluno {
    int matricula;
    char nome[50];
    char curso[50];
    char ano_entrada[11];
    no_avaliacao* avaliacoes;
    float soma_notas; 
    struct Aluno *prox;
} no_aluno;

typedef struct Lista {
    no_aluno *cabeca;
} lista_aluno;

typedef struct no_hash {
    no_aluno* aluno;  // Ponteiro para o nó da lista de alunos
    struct no_hash* prox;  // Próximo nó na tabela hash (colisões)
} no_hash;

typedef struct {
    no_hash* tabela[TABLE_SIZE];  // Tabela hash de ponteiros para nós do tipo no_hash
} hash_table;

void insere_aluno(lista_aluno* lista, char nome[], char curso[], char ano_entrada[], int matricula);
void imprime_alunos(lista_aluno *lista);
no_aluno* buscarAluno(lista_aluno *lista, int matricula);
no_aluno* busca_hash(hash_table* ht, int matricula);
void imprime_tabela(hash_table* ht);
void inicializarTabelaHash(hash_table* ht);
void ordenar_lista_por_nome(hash_table* ht, lista_aluno* lista);
void ordenar_lista_por_matricula(hash_table* ht, lista_aluno* lista);
lista_aluno* criar_lista_aluno();
void insere_hash(hash_table *ht, no_aluno* aluno);
void ordenarTabelaPorNome(hash_table* ht);

void QuickSort_matricula(int *vet, int p, int r);

void ordenarEImprimir(hash_table* ht);
void ordenarEImprimirPorMatricula(hash_table* ht); 

void insere_avaliacao(lista_avaliacoes *L, char nome_avaliacao[], float valor_total, int matricula_aluno, float nota_aluno);
void calcularSomaNotas(no_aluno* aluno);


void atualizarSomaNotasAluno(no_aluno *aluno, lista_avaliacoes *avaliacoes);
void ordenarEImprimirPorSomaNotas(hash_table* ht);

#endif // ALUNOS_H
