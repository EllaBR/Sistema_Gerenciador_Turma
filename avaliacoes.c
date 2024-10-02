//#include "avaliacoes.h"
#include "alunos.h"


lista_avaliacoes *criar_lista_avaliacoes(){
	lista_avaliacoes *lista_aval=(lista_avaliacoes*)malloc(sizeof(lista_avaliacoes));
	lista_aval -> cabeca = NULL;
	return lista_aval;
}


void insere_avaliacao(lista_avaliacoes *L, char nome_avaliacao[], float valor_total, int matricula_aluno, float nota_aluno) {

    no_avaliacao *novo = (no_avaliacao*)malloc(sizeof(no_avaliacao));
    if (novo == NULL) {
        printf("Erro ao alocar memória para nova avaliação.\n");
        exit(1);
    }
 
    strcpy(novo->nome_avaliacao, nome_avaliacao);
    novo->valor_total = valor_total;
    novo->matricula_aluno = matricula_aluno;
    novo-> nota_aluno = nota_aluno;
 
    novo->prox = NULL; 

    if (L->cabeca == NULL) {
        L->cabeca = novo;
    } else {  
        no_avaliacao *atual = L->cabeca;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}



void imprime_avaliacao(lista_avaliacoes *L, char nome_avaliacao[]) {
    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de avaliações vazia.\n");
        return;
    }

    no_avaliacao *busca = L->cabeca;
    while (busca != NULL) {
        if (strcmp(busca->nome_avaliacao, nome_avaliacao) == 0) {
            printf("%s %f %d %f\n", busca->nome_avaliacao, busca->valor_total, busca->matricula_aluno, busca->nota_aluno);
        }
        busca = busca->prox;
    }
}




float nota_max(lista_avaliacoes *L, char nome_avaliacao[]) {
    float maior = 0;

    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de avaliações vazia.\n");
        return maior;
    }

    no_avaliacao *busca = L->cabeca;
    while (busca != NULL) {
        if (strcmp(busca->nome_avaliacao, nome_avaliacao) == 0) {
            if (busca->nota_aluno > maior) {
                maior = busca->nota_aluno;
            }
        }
        busca = busca->prox;
    }
    return maior;
}



float nota_min(lista_avaliacoes *L, char nome_avaliacao[]) {
    float min = 10;

    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de avaliações vazia.\n");
        return min;
    }

    no_avaliacao *busca = L->cabeca;
    while (busca != NULL) {
        if (strcmp(busca->nome_avaliacao, nome_avaliacao) == 0) {
            if (busca->nota_aluno < min) {
                min = busca->nota_aluno;
            }
        }
        busca = busca->prox;
    }
    return min;
}

float nota_med(lista_avaliacoes *L, char nome_avaliacao[]) {
    float soma = 0;
    int cont = 0;

    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de avaliações vazia.\n");
        return 0;
    }

    no_avaliacao *busca = L->cabeca;
    while (busca != NULL) {
        if (strcmp(busca->nome_avaliacao, nome_avaliacao) == 0) {
            soma += busca->nota_aluno;
            cont++;
        }
        busca = busca->prox;
    }

    if (cont == 0) return 0;

    return soma / cont;
}

float soma_todas_as_notas(lista_avaliacoes *lista, int matricula){
    no_avaliacao *busca = lista->cabeca;
    float soma_nota = 0;
    if(busca == NULL){
        return soma_nota;
    }
    while(busca!=NULL){
        if(matricula = busca -> matricula_aluno){
            soma_nota = soma_nota + busca ->nota_aluno;
        }
        busca = busca->prox;
    }
    return soma_nota;
}

void ordenar_notas_descrescente(lista_avaliacoes *L, const char *nome_avaliacao) {
    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de avaliações vazia ou não inicializada.\n");
        return;
    }

    // Converte a lista filtrada em um array de ponteiros para facilitar a ordenação
    int n = 0;
    no_avaliacao *current = L->cabeca;
    while (current != NULL) {
        if (strcmp(current->nome_avaliacao, nome_avaliacao) == 0) {
            n++;
        }
        current = current->prox;
    }

    if (n == 0) {
        printf("Nenhuma avaliação encontrada para o nome fornecido.\n");
        return;
    }

    no_avaliacao **array = (no_avaliacao**)malloc(n * sizeof(no_avaliacao*));
    if (array == NULL) {
        printf("Erro ao alocar memória para array de ponteiros.\n");
        exit(1);
    }

    current = L->cabeca;
    int idx = 0;
    while (current != NULL) {
        if (strcmp(current->nome_avaliacao, nome_avaliacao) == 0) {
            array[idx++] = current;
        }
        current = current->prox;
    }

    // Selection Sort
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j]->nota_aluno > array[max_idx]->nota_aluno) {
                max_idx = j;
            }
        }

        // Troca o ponteiro do nó
        no_avaliacao *temp = array[i];
        array[i] = array[max_idx];
        array[max_idx] = temp;
    }

    // Reconstrua a lista original com a ordem corrigida
    no_avaliacao *nova_cabeca = array[0];
    current = nova_cabeca;
    for (int i = 1; i < n; i++) {
        current->prox = array[i];
        current = current->prox;
    }
    current->prox = NULL;

    // Atualiza a lista original com a nova cabeça
    // Note: Ensure L->cabeca is updated if you're managing a single list.
    L->cabeca = nova_cabeca;

    free(array);
}


void imprime_avaliacoes_ordenadas(lista_avaliacoes *L, const char *nome_avaliacao) {
    if (L == NULL || L->cabeca == NULL) {
        printf("Lista de avaliações vazia.\n");
        return;
    }

    no_avaliacao *busca = L->cabeca;
    while (busca != NULL) {
        if (strcmp(busca->nome_avaliacao, nome_avaliacao) == 0) {
            printf("Valor Total:%f Matrícula:%d Nota:%f\n", busca->valor_total, busca->matricula_aluno, busca->nota_aluno);
        }
        busca = busca->prox;
    }
}


void imprime_avaliacoes(lista_avaliacoes* L) {
    no_avaliacao* atual = L->cabeca;
    
    if (atual == NULL) {
        printf("Nenhuma avaliação registrada.\n");
        return;
    }

    while (atual != NULL) {
        printf("Nome da Avaliação: %s\n", atual->nome_avaliacao);
        printf("Valor Total: %.2f\n", atual->valor_total);
        printf("Matrícula do Aluno: %d\n", atual->matricula_aluno);
        printf("Nota do Aluno: %.2f\n", atual->nota_aluno);
        printf("---------------------------\n");
        atual = atual->prox;
    }
}