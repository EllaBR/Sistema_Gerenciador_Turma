#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Lê a opção escolhida pelo usuário
int le_escolha(int escolha);

void limpa_tela();

void espera();

int prepara_menu(int escolha_menu_principal);

int gerarMatriculaAleatoria();

void remover_nova_linha(char* str);