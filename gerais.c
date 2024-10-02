#include "gerais.h"
#include "menus.h"

int le_escolha(int escolha){
	printf("Digite o número da opção para escolher:");
	scanf("%d", &escolha);
	return escolha;
}

void limpa_tela(){
	system("clear||cls");
}

void espera(){
	printf("aperte enter para continuar");
	getchar();
	getchar();
}

int prepara_menu(int escolha_menu_principal){
	int escolha_sub_menu;
	limpa_tela();
    sub_menus(escolha_menu_principal);
    escolha_sub_menu = le_escolha(escolha_sub_menu);
    return escolha_sub_menu;
}

int gerarMatriculaAleatoria() {
    return rand() % 10000;  // Gera um número de 0 a 9999
}
void remover_nova_linha(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}