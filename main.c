#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "gerais.h"
#include "alunos.h"
#include "avaliacoes.h"
#include "chamada.h"




int main() {
    lista_aluno *lista_a = criar_lista_aluno();
    lista_avaliacoes *lista_aval = criar_lista_avaliacoes();
    lista_chamada *lista_chama = criar_lista_chamada();
    
    int escolha_menu_principal = 0;
    int escolha_sub_menu, contador;

    char nome[50];
    char curso[50];
    char ano_entrada[11];

    char nome_avaliacao[50];
    float valor_total;
    int matricula_aluno;
    float nota_aluno;

    float nota_maxi, nota_mini, nota_media;

    char data[10];
    char frequencia[15];
    int ausencia = 0;
    char data_exist[10];



    hash_table ht;
    inicializarTabelaHash(&ht);


    while (escolha_menu_principal != 6) {
        limpa_tela();
        menu_principal();
        escolha_menu_principal = le_escolha(escolha_menu_principal);
        limpa_tela();
        
        switch (escolha_menu_principal) {
            case 1:
                escolha_sub_menu = 0; // Reinicializa escolha_sub_menu 
                while (escolha_sub_menu != 4) {
                    escolha_sub_menu = prepara_menu(escolha_menu_principal);

                    if (escolha_sub_menu == 1) {
                        printf("Informe o nome do aluno:\n");
                        getchar(); // Limpa o buffer de entrada
                        fgets(nome, sizeof(nome), stdin);
                       
                
                    } else if (escolha_sub_menu == 2) {
                        printf("Informe o curso do aluno:\n");
                        getchar();
                        fgets(curso, sizeof(curso), stdin);
                       
                    } else if (escolha_sub_menu == 3) {
                        printf("Informe o ano de entrada do aluno:\n");
                        getchar(); 
                        fgets(ano_entrada, sizeof(ano_entrada), stdin);
                    }

                }
                int matricula = rand()%1000;
                insere_aluno(lista_a, nome, curso, ano_entrada, matricula);
                 // Pegar o endereço do novo aluno (primeiro da lista após inserção)
                no_aluno* novo_aluno = lista_a->cabeca;
                insere_hash(&ht, novo_aluno);
                imprime_tabela(&ht);
                imprime_alunos(lista_a);
                espera();
                if(lista_chama->cabeca != NULL){
                    printf("\nHá chamadas anteriores, favor adicionar a presença para os seguintes dias:\n");
                    imprime_chamada_data(lista_chama);
                    no_chamada *busca = lista_chama->cabeca; 
                        while (busca != NULL) {
                                if(strcmp(data_exist, busca->data)!= 0){                                      
                                printf("Informe a presença no dia %s:", busca ->data);
                                scanf("%s", frequencia);
                                if (strcmp(frequencia, "ausente") == 0) {
                                    ausencia = 1;
                                }else{
                                    ausencia = 0;
                                }
                                insere_chamada(lista_chama, busca -> data, matricula, frequencia, ausencia);
                                busca = busca->prox;   
                                }   
                        }
                }
                break;

            case 2:
                escolha_sub_menu = 0;
                contador = 0;
                while(escolha_sub_menu != 3) {
                    escolha_sub_menu = prepara_menu(escolha_menu_principal);

                    if(escolha_sub_menu == 1){
                        printf("Informe o nome da avaliação:\n");
                        getchar();
                        fgets(nome_avaliacao, sizeof(nome_avaliacao), stdin);
                        contador++; // utilizado para verificar se as duas informações foram adicionadas
                    } else if (escolha_sub_menu == 2){
                        printf("Informe o valor total da avaliação:");
                        scanf("%f", &valor_total);
                        contador++;
                    }

                    if (contador == 2){

                        printf("--- ALUNOS ---\n");

                        no_aluno *busca = lista_a->cabeca; 

                        while (busca != NULL) {
                            printf("%s", busca -> nome);
                            matricula_aluno = busca -> matricula;
                            printf("informe a nota do aluno:");
                            scanf("%f", &nota_aluno);

                            insere_avaliacao(lista_aval, nome_avaliacao, valor_total, matricula_aluno, nota_aluno);

                            

                            atualizarSomaNotasAluno(busca, lista_aval);

                             printf("Soma das notas do aluno %s: %.2f\n", busca->nome, busca->soma_notas);
                            busca = busca->prox;
                           
                            


                        }

                        //imprime_avaliacao(lista_aval, nome_avaliacao);

                        imprime_avaliacoes(lista_aval);
                        espera();
                        break;
                    }
                }

                break;

            case 3: // Realizar chamada
                escolha_sub_menu = 0;
                while (escolha_sub_menu != 2) {
                    escolha_sub_menu = prepara_menu(escolha_menu_principal);
                    if (escolha_sub_menu == 1) {
                        char data[20];
                        char frequencia[10];
                        int ausencia;
                        int matricula_aluno;
                        
                        printf("Informe a data (xx/xx/xxxx): ");
                        getchar(); // Para limpar o buffer de entrada
                        fgets(data, sizeof(data), stdin);
                        remover_nova_linha(data);
                   

                        no_aluno *busca = lista_a->cabeca;
                        printf("----- ALUNO -----\n");
                        while (busca != NULL) {
                            ausencia = 0;
                            matricula_aluno = busca->matricula;
                            printf("\n%s\n", busca->nome);
                            printf("Informe a situação do aluno (presente/ausente): ");
                            scanf("%s", frequencia);
                            if (strcmp(frequencia, "ausente") == 0) {
                                ausencia = 1;
                            }

                            insere_chamada(lista_chama, data, matricula_aluno, frequencia, ausencia);
                            printf("\n");
                            imprime_chamada(lista_chama);
                            conta_ausencia(lista_chama, matricula_aluno);
                            busca = busca->prox;
                            
                        }
                        //imprime_chamada(lista_chama);
                        espera(); // Função que espera o usuário antes de continuar
                    }
                }
                break;

                break;

            case 4:
            escolha_sub_menu = 0;
                while(escolha_sub_menu != 5) {
                        escolha_sub_menu = prepara_menu(escolha_menu_principal);
                        if (escolha_sub_menu == 1){
                          ordenarEImprimirPorMatricula(&ht);  
                          espera();                           
                        }else if(escolha_sub_menu == 2){
                            ordenarEImprimir(&ht);
                            espera();
                        } else if(escolha_sub_menu == 3){
                            ordenarEImprimirPorSomaNotas(&ht);
                            espera();
                        }
                }
            break;

            case 5:

                escolha_sub_menu = 0;
                while(escolha_sub_menu != 2) {
                        escolha_sub_menu = prepara_menu(escolha_menu_principal);

                        if(escolha_sub_menu == 1){
                            printf("Informe o nome da avaliação:");
                            getchar();
                            fgets(nome_avaliacao, sizeof(nome_avaliacao), stdin);
                            
                            imprime_avaliacoes(lista_aval);
                            nota_maxi = nota_max(lista_aval, nome_avaliacao);
                            nota_mini = nota_min(lista_aval, nome_avaliacao);
                            nota_media = nota_med(lista_aval, nome_avaliacao);

                            printf("-------- RELATÓRIO DE NOTAS --------\n");
                            printf("nota máxima:%f\n", nota_maxi);
                            printf("nota mínima:%f\n", nota_mini);
                            printf("nota média:%f\n", nota_media);

                            //imprimir notas ordenadas de forma decrescente
                            printf("----- NOTAS EM ORDEM DESCRESCENTE -----\n");
                            //ordenar_notas_descrescente(lista_aval,nome_avaliacao);
                            //imprime_avaliacoes_ordenadas(lista_aval, nome_avaliacao);

                            espera();

                        }
                    }
                  

                break;

                
               
        }
    }


    return 0;
}