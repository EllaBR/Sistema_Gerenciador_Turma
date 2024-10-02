#include "menus.h"
#include "gerais.h"
#include "alunos.h"



void menu_principal(){
	printf("------------- MENU -------------\n");
	printf("[1] Cadastrar aluno\n");
	printf("[2] Cadastrar avaliação\n");
	printf("[3] Realizar chamada\n");
	printf("[4] Relatório de alunos\n");
	printf("[5] Relatório de notas\n");
	printf("[6] Sair do sistema\n");

}


void sub_menus(int escolha){

	switch(escolha){
	case 1:
		printf("------------- CADASTRO DE ALUNOS -------------\n");
		printf("[1] Nome\n");
		printf("[2] Curso\n");
		printf("[3] Ano de entrada\n");
		printf("[4] Voltar\n");
		break;
	case 2:
		printf("------------- CADASTRO DE AVALIAÇÕES -------------\n");
		printf("[1] Nome da avaliação\n");
		printf("[2] Valor total\n");
		printf("[3] Voltar\n");
		//solicita nota de cada aluno após
		break;
	case 3:
		printf("------------- CHAMADA -------------\n");
		printf("[1] Informar a data (dd/mm/aaaa)\n");
		printf("[2] Voltar\n");
		//le a data e depois pergunta se cada aluno da lista está ou não presente, se bater 10 faltas imprime aviso falando que foi reprovado
		break;
	case 4:
		printf("------------- RELATÓRIO DE ALUNOS -------------\n");
		printf("Opções de ordenação:\n");
		printf("[1] Por matrícula\n");
		printf("[2] Por nome\n");
		printf("[3] Por soma de todas as notas\n");
		printf("[4] Por número de faltas\n");
		printf("[5] Voltar\n");
		//imprime o relatório após
		break;
	case 5:
		printf("------------- RELATÓRIO DE NOTAS -------------\n");
		printf("[1] Informar o nome da avaliação\n");
		printf("[2] Voltar\n");
		//após isso imprime nota max, min e media e após isso todas as notas em ordem descrescente sem indicar os nomes dos alunos
		break;
	}

}


void menus_especificos(int escolha){
	int escolha_sub_menu = 0;
	switch(escolha){
	case 1:
	
					
		break;
	case 2:
		while(escolha_sub_menu != 3){
			escolha_sub_menu = le_escolha(escolha_sub_menu);
			switch(escolha_sub_menu){
			case 1:
				printf("Informe o nome da avaliação:\n");
				break;
			case 2:
				printf("Informe o valor total da avaliação:\n");
				break;
			}
	     }
		break;
	case 3:
		while(escolha_sub_menu != 2){
			escolha_sub_menu = le_escolha(escolha_sub_menu);
			switch(escolha_sub_menu){
			case 1:
				
				break;
			}
	     }
		break;	
	case 4:
		while(escolha_sub_menu != 5){
			escolha_sub_menu = le_escolha(escolha_sub_menu);
			switch(escolha_sub_menu){
			case 1:
				//ordenação
				break;
			}
	     }
		break;
	case 5:
		while(escolha_sub_menu != 2){
			escolha_sub_menu = le_escolha(escolha_sub_menu);
			switch(escolha_sub_menu){
			case 1:
				printf("Informe o nome da avaliação:\n");
				// mostra as informações dps
				break;
			}
	     }
		break;
	}
}
