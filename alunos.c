#include "alunos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função hash para calcular o índice na tabela
int funcaoHash(int matricula) {
    return matricula % TABLE_SIZE;
}

// Inicializa a tabela hash
void inicializarTabelaHash(hash_table* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->tabela[i] = NULL;
    }
}

// Cria uma nova lista de alunos
lista_aluno* criar_lista_aluno() {
    lista_aluno* lista_a = (lista_aluno*)malloc(sizeof(lista_aluno));
    lista_a->cabeca = NULL;
    return lista_a;
}

// Insere um aluno na tabela hash e na lista encadeada
void insere_aluno(lista_aluno* lista, char nome[], char curso[], char ano_entrada[], int matricula) {
    no_aluno* novo = (no_aluno*)malloc(sizeof(no_aluno));
    if (novo == NULL) {
        printf("Erro ao alocar memória para novo aluno.\n");
        exit(1);
    }

    // Preenche os dados do novo aluno
    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    strcpy(novo->curso, curso);
    strcpy(novo->ano_entrada, ano_entrada);
    novo -> soma_notas = 0;

    // Insere na lista encadeada
    novo->prox = lista->cabeca;
    lista->cabeca = novo;
}

// Insere na tabela hash o endereço de um nó da lista encadeada de alunos
void insere_hash(hash_table *ht, no_aluno* aluno) {
    // Calcula o índice da tabela hash com base na matrícula do aluno
    int indice = funcaoHash(aluno->matricula);
    
    // Cria um novo nó na tabela hash para armazenar o endereço do nó da lista de alunos
    no_hash* novo_no_hash = (no_hash*)malloc(sizeof(no_hash));
    if (novo_no_hash == NULL) {
        printf("Erro ao alocar memória para novo nó na tabela hash.\n");
        exit(1);
    }

    // Armazena o ponteiro para o nó da lista encadeada de alunos
    novo_no_hash->aluno = aluno;

    // Insere no início da lista encadeada na posição da tabela hash
    novo_no_hash->prox = ht->tabela[indice];  // Corrigido: ht->tabela contém no_hash*
    ht->tabela[indice] = novo_no_hash;  // Corrigido: agora armazena no_hash*, não no_aluno*
}



// Imprime todos os alunos na lista encadeada
void imprime_alunos(lista_aluno* lista) {
    no_aluno* atual = lista->cabeca;
    if (atual == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    while (atual) {
        printf("%s %s %s %d\n", atual->nome, atual->curso, atual->ano_entrada, atual->matricula);
        atual = atual->prox;
    }
}


// Busca um aluno na lista encadeada
no_aluno* buscarAluno(lista_aluno* lista, int matricula) {
    no_aluno* atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->matricula == matricula) {
            return atual;
        }
        atual = atual->prox;
    }
    printf("Aluno não encontrado.\n");
    return NULL;
}

// Busca um aluno na tabela hash
no_aluno* busca_hash(hash_table* ht, int matricula) {
    int indice = funcaoHash(matricula);
    no_hash* atual = ht->tabela[indice];

    // Percorre a lista de colisões na tabela hash
    while (atual != NULL) {
        if (atual->aluno->matricula == matricula) {
            return atual->aluno;  // Retorna o nó do aluno
        }
        atual = atual->prox;
    }

    printf("Aluno não encontrado.\n");
    return NULL;
}


// Imprime a tabela hash
void imprime_tabela(hash_table* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->tabela[i] != NULL) {
            no_hash* atual = ht->tabela[i];
            printf("Índice %d:\n", i);

            // Percorre a lista de colisões na tabela hash
            while (atual != NULL) {
                // Acessa os dados do aluno através do ponteiro armazenado no nó da tabela hash
                printf("  Nome: %s, Matrícula: %d\n", atual->aluno->nome, atual->aluno->matricula);
                atual = atual->prox;
            }
        } else {
            printf("Índice %d: Vazio\n", i);
        }
    }
}


int comparaNomes(const void* a, const void* b) {
    no_aluno* aluno1 = *(no_aluno**)a;
    no_aluno* aluno2 = *(no_aluno**)b;
    return strcmp(aluno1->nome, aluno2->nome);
}






int particao(no_aluno* alunos[], int baixo, int alto) {
    no_aluno* pivo = alunos[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (strcmp(alunos[j]->nome, pivo->nome) < 0) {
            i++;
            no_aluno* temp = alunos[i];
            alunos[i] = alunos[j];
            alunos[j] = temp;
        }
    }

    no_aluno* temp = alunos[i + 1];
    alunos[i + 1] = alunos[alto];
    alunos[alto] = temp;

    return i + 1;
}

// Função de Quick Sort
void quickSort(no_aluno* alunos[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particao(alunos, baixo, alto);
        quickSort(alunos, baixo, pi - 1);
        quickSort(alunos, pi + 1, alto);
    }
}


int particaoMatricula(no_aluno* alunos[], int baixo, int alto) {
    no_aluno* pivo = alunos[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (alunos[j]->matricula < pivo->matricula) {
            i++;
            no_aluno* temp = alunos[i];
            alunos[i] = alunos[j];
            alunos[j] = temp;
        }
    }

    no_aluno* temp = alunos[i + 1];
    alunos[i + 1] = alunos[alto];
    alunos[alto] = temp;

    return i + 1;
}

void quickSortMatricula(no_aluno* alunos[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particaoMatricula(alunos, baixo, alto);
        quickSortMatricula(alunos, baixo, pi - 1);
        quickSortMatricula(alunos, pi + 1, alto);
    }
}




void ordenarEImprimir(hash_table* ht) {
    no_aluno* alunos[100];  // Array para armazenar endereços dos alunos
    int contador = 0;

    // Coleta todos os alunos da tabela hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        no_hash* atual = ht->tabela[i];
        while (atual != NULL) {
            alunos[contador++] = atual->aluno;
            atual = atual->prox;
        }
    }

    // Ordena o array de alunos
     quickSort(alunos, 0, contador - 1);

    // Imprime os alunos em ordem
    for (int i = 0; i < contador; i++) {
        printf("Nome: %s, Matrícula: %d, Curso: %s, Ano de Entrada: %s\n",
            alunos[i]->nome, alunos[i]->matricula, alunos[i]->curso, alunos[i]->ano_entrada);
    }
}

int comparaMatriculas(const void *a, const void *b) {
    no_aluno *alunoA = *(no_aluno **)a;
    no_aluno *alunoB = *(no_aluno **)b;
    return alunoA->matricula - alunoB->matricula;
}




void ordenarEImprimirPorMatricula(hash_table* ht) {
    no_aluno* alunos[100];  // Array para armazenar endereços dos alunos
    int contador = 0;

    // Coleta todos os alunos da tabela hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        no_hash* atual = ht->tabela[i];
        while (atual != NULL) {
            alunos[contador++] = atual->aluno;
            atual = atual->prox;
        }
    }

    // Ordena o array de alunos por matrícula
    quickSortMatricula(alunos, 0, contador - 1);

    // Imprime os alunos em ordem de matrícula
    for (int i = 0; i < contador; i++) {
        printf("Nome: %s, Matrícula: %d, Curso: %s, Ano de Entrada: %s\n",
            alunos[i]->nome, alunos[i]->matricula, alunos[i]->curso, alunos[i]->ano_entrada);
    }
}



void calcularSomaNotas(no_aluno* aluno) {
    if (aluno == NULL) {
        printf("Aluno não encontrado.\n");
        return;
    }

    no_avaliacao* atual = aluno->avaliacoes;
    aluno->soma_notas = 0.0;  // Inicializa a soma

    while (atual != NULL) {
        aluno->soma_notas += atual->nota_aluno;  // Soma a nota do aluno
        atual = atual->prox;  // Avança para o próximo nó
    }
}



// Função para ordenar o array de alunos pela soma das notas usando Selection Sort
void selectionSortPorSomaNotas(no_aluno* alunos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Encontra o índice do aluno com a maior soma de notas no subarray não ordenado
        int idx_max = i;
        for (int j = i + 1; j < n; j++) {
            if (alunos[j]->soma_notas > alunos[idx_max]->soma_notas) {
                idx_max = j;
            }
        }
        // Troca o aluno na posição i com o aluno com a maior soma de notas
        if (idx_max != i) {
            no_aluno* temp = alunos[i];
            alunos[i] = alunos[idx_max];
            alunos[idx_max] = temp;
        }
    }
}

void ordenarEImprimirPorSomaNotas(hash_table* ht) {
    no_aluno* alunos[100];  // Array para armazenar endereços dos alunos
    int contador = 0;

    // Coleta todos os alunos da tabela hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        no_hash* atual = ht->tabela[i];
        while (atual != NULL) {
            alunos[contador++] = atual->aluno;
            atual = atual->prox;
        }
    }

    // Ordena o array de alunos pela soma das notas
    selectionSortPorSomaNotas(alunos, contador);

    // Imprime os alunos em ordem de soma das notas
    for (int i = 0; i < contador; i++) {
        printf("Nome: %s, Matrícula: %d, Curso: %s, Ano de Entrada: %s, Soma das Notas: %.2f\n",
            alunos[i]->nome, alunos[i]->matricula, alunos[i]->curso, alunos[i]->ano_entrada, alunos[i]->soma_notas);
    }
}


void atualizarSomaNotasAluno(no_aluno *aluno, lista_avaliacoes *avaliacoes) {
    if (aluno == NULL || avaliacoes == NULL) {
        printf("Aluno ou lista de avaliações não inicializados.\n");
        return;
    }

    // Inicializa a soma de notas
    aluno->soma_notas = 0.0;

    // Percorre a lista de avaliações
    no_avaliacao *atual = avaliacoes->cabeca;
    while (atual != NULL) {
        // Verifica se a matrícula do aluno corresponde à matrícula na avaliação
        if (atual->matricula_aluno == aluno->matricula) {
            aluno->soma_notas += atual->nota_aluno;
        }
        atual = atual->prox;
    }
}


