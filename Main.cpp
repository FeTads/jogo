#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <locale.h>
#include "comp.h"
#include "seta.h"

typedef struct {
	
	int existe;
	char login[20];
	char senha[20];
	char nome[20];
	int admin;

} User;

User usuario;
User usuario1, usuario2;

typedef struct {
	
	//atributos ensinaveis
	int persuasao;
	int furtividade;
	
	//atributos fixos
	int inteligencia;
	int carisma;
	int forca;
	int sabedoria;
	int destreza;
	int constituicao;
	int parte;
	
} Atributes;

Atributes atrbt;


//copiar funcoes pro codigo principal depois
void aceitar_missao();
void recusar_missao();
void mostrar_atributos();
void ir_poseidon();

void game_reset(){
	
	FILE *atributos = fopen("atributos.bin", "wb");
	
	atrbt.forca = 0;
	atrbt.inteligencia = 0;
	atrbt.destreza = 0;
	atrbt.constituicao = 0;
	atrbt.carisma = 0;
	atrbt.sabedoria = 0;
	atrbt.furtividade = 0;
	atrbt.persuasao = 0;
	atrbt.parte = 0;
	   		
	fwrite(&atrbt, sizeof(Atributes), 1, atributos);
	
	fclose(atributos);
}

//             0    1    2     3    4      5    6       7        8
typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,
	LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;
//       9        10       11         12        13        14     15

static int __BACKGROUND = BLACK;
static int __FOREGROUND = WHITE;

void textcolor (int letra, int fundo){
    __FOREGROUND = letra;
    __BACKGROUND = fundo;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letra + (__BACKGROUND << 4));
}


clock_t tempo = 0;

void fazTudo(int x, int y);
int dificuldade(int dif);
void rank(int opcao, char *nome, int t, int dif);
void placar(int t, char *nome, int dif);
int efetuar_login();
int cadastrar();
void editar();
void reset_ranking();
void menu_admin();
void mudar_login();
void mudar_senha();
void jogar();


int main(void){ 


	//jogar();

	int opcao2, retorno, flag, t, dif, opcao;
	int sair_menu;
	char *nome;
	
	nome = (char*)malloc(20*sizeof(char)); 
			
	system("cls");
 	do{
 	
	 	puts("_____________________________________________");
	 	puts("------------------- LOGIN -------------------");
	 	puts("|     1 - Efetuar Login                     |");
	 	puts("|     2 - Cadastrar                         |");
	 	puts("|     3 - Ranking                           |");
	 	puts("|     4 - Sair                              |");
	    puts("------------------- LOGIN -------------------");
	 	puts("_____________________________________________");
	 	printf("> ");
	 	scanf("%i", &opcao2);
	 	
	 	system("cls");
	 	
	 	if(opcao2 == 1){
	 		
	 		FILE *usuarios = fopen("user.bin","rb");
	 		
	 		if(usuarios == NULL){
	 			printf("\n\n\t\t\t**********************************\n");
	 			printf("\t\t\tERRO!!! NAO EXISTE NENHUM CADASTRO\n");
	 			printf("\t\t\t**********************************\n");
	 			system("\n\n\ntimeout /T 10");
	 			//getch();
	 			system("cls");
	 			fclose(usuarios);
	 			opcao2 = 100;
			}
			
	 		
			else{
				fclose(usuarios);
	 			
			 	puts("_____________________________________________");
				puts("------------------- LOGIN -------------------");
				puts("|    Digite seu Login:                      |");
				printf("| > ");
				setbuf(stdin,NULL);
				fgets(usuario1.login, 20, stdin);
				puts("|    Digite sua senha:                      |");
				printf("| > ");
				setbuf(stdin,NULL);
				fgets(usuario1.senha, 20, stdin);
				puts("------------------- LOGIN -------------------");
				puts("_____________________________________________");
			 		
			 	retorno = efetuar_login();
			 	system("cls");
			 	
			 	if(retorno == 0){
			 		opcao2 = 100;
				}
				
				else{
			 		opcao2 = 1;
			 	}	
		 	}
		}
		 
		if(opcao2 == 2){
							
			puts("__________________________________________________");
			puts("----------------- CADASTRO ----------------------");
			puts("|    Digite seu Login:                           |");
			printf("| > ");
			setbuf(stdin,NULL);
			fgets(usuario2.login, 20, stdin);
			puts("|    Digite sua senha:                     	 |");
			printf("| > ");
			setbuf(stdin,NULL);
			fgets(usuario2.senha, 20, stdin);
			puts("|    Digite seu nome:                     	 |");
			printf("| > ");
			setbuf(stdin,NULL);
			fgets(usuario2.nome, 20, stdin);
			usuario2.admin = 1;
			puts("----------------- CADASTRO ----------------------");
			puts("__________________________________________________");
			 	
			 	
		 	flag = cadastrar();
		 	system("cls");
		 	if(flag == 1){
		 		opcao2 = 100;
			}
	 		
		}
	
		if(opcao2 == 3){
			rank(3, nome, t, dif);
			opcao2 = 100;			
		}	
		
		if(opcao2 == 4){
			exit(1);
		}
		
		if(opcao2 < 1 || opcao2 > 4){
			if(opcao2 != 100){
				system("cls");
				printf("\n\t[OPCAO NAO EXISTENTE]");
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				getch();
				system("cls");
			}
		}
		
	}while(opcao2 < 1 || opcao2 > 4);
	

    return 0;
}

int dificuldade(int dif){
	
	system("cls");
	
	printf("Escolha a Dificuldade: \n");
	printf("1 - Facil\n");
	printf("2 - Medio\n");
	printf("3 - Dificil\n");
	printf("> ");
	scanf("%i", &dif);
	
	return dif;	
}


void rank(int opcao, char *nome, int t, int dif){
	
	char c;
	
	FILE *arquivo = fopen("ranking.bin","a+b");
			
	if(opcao != 3 && opcao != 2){
		fprintf(arquivo,"\nNome ------------: %s", usuario.nome);
		if(dif == 1){
			fprintf(arquivo,"Pontos ----------: %d\n", (t - 1) * 2);
		}
		else if(dif == 2){
			fprintf(arquivo,"Pontos ----------: %d\n", (t - 1) * 4);
		}
		else if(dif == 3){
			fprintf(arquivo,"Pontos ----------: %d\n", (t - 1) * 7);
		}
		
				
					
		if((float)(tempo/CLOCKS_PER_SEC) >= 60){
				   	
			int j = 0;                              //                 
			int i = (tempo/CLOCKS_PER_SEC);         // i = 105
				do{
					if((float)(tempo/CLOCKS_PER_SEC) >= 60){
					    j++;									//j = 1
					    i = i - 60;								//i = 45
					}
				}while(i >= 60);
									
		fprintf(arquivo, "Tempo -----------: %i Mins. e %i segundos\n", j, i);
				    				    	
		}
		
		else{
			fprintf(arquivo, "Tempo -----------: %.2f Seg.\n",((float)tempo/CLOCKS_PER_SEC));
		}
				
				
		if(dif == 1){
			fprintf(arquivo, "Dificuldade -----: Facil\n");
		}
		
		else if(dif == 2){
			fprintf(arquivo, "Dificuldade -----: Medio\n");
		}
		
		else if(dif == 3){
			fprintf(arquivo, "Dificuldade -----: Dificil\n");
		}
				
		fprintf(arquivo,"---------------------------------------------------------------------\n");
				
			fclose(arquivo);
	}
	
				
	system("cls");
				
	puts(" ____________________________________________________________________");
	puts("|  ****************************************************************  |");
	puts("|  *************************    RANKING    ************************  |");
	puts("|  ****************************************************************  |");
				    
				
	arquivo = fopen("ranking.bin", "r");
	while( !feof(arquivo) ){                         //enquanto não atingir o final do arquivo
		c = getc(arquivo);                           //captura cada caractere
		printf("%c",c);                              // e imprime ele
	}
		 	
	fclose(arquivo); 
				
	puts("\n\nPressione ENTER para voltar ao menu");
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	getch();
				
	system("cls");
			
}  

void placar(int t, char *nome, int dif){
	
	
		system("cls");
		system("mode con:cols=120 lines=30");
		
		printf("   PLACAR \n");
		printf("\njogador ----------: %s", usuario.nome);
		if(dif == 1){
			printf("Pontos -----------: %d\n", (t - 1) * 2);
		}
		else if(dif == 2){
			printf("Pontos -----------: %d\n", (t - 1) * 4);
		}
		else if(dif == 3){
			printf("Pontos -----------: %d\n", (t - 1) * 7);
		}
	
		if((float)(tempo/CLOCKS_PER_SEC) >= 60){
			   	
			int j = 0;                              //                 
			int i = (tempo/CLOCKS_PER_SEC);         // i = 105
				do{
					if((float)(tempo/CLOCKS_PER_SEC) >= 60){
					    j++;									//j = 1
					    i = i - 60;								//i = 45
					}
				}while(i >= 60);
								
			printf("Tempo ------------: %i Mins. e %i segundos\n", j, i);
				    				    	
		}
		else{
			printf("Tempo ------------: %.2f Seg.\n",((float)tempo/CLOCKS_PER_SEC));
		}
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch();
}

int efetuar_login(){
	
	FILE *usuarios = fopen("user.bin","rb");
	
	int flag = 0;
	
	rewind(usuarios);

	while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
	
		if(strcmp(usuario1.login, usuario.login) == 0 && strcmp(usuario1.senha, usuario.senha) == 0){
			
			if(usuario.admin == 1){
				flag = 1;
			}
			
			else{
				flag  = 2;
			}	
		}	
	}
	
	if(flag == 0){
		printf("_____________________________________________\n");
		printf("\n\n\tUSUARIO INCORRETO\n");
		printf("_____________________________________________\n");
		system("\n\n\ntimeout /T 10");
		fclose(usuarios);
	}
	
	else if(flag == 1){
		printf("_____________________________________________\n");
		printf("\n\n\tADMINISTRADOR AUTENTICADO\n");
		printf("_____________________________________________\n");
		system("\n\n\ntimeout /T 10");
		fclose(usuarios);
		menu_admin();
		
	}
	
	

	fclose(usuarios);
	
	return 0;
}

int cadastrar(){
	
	int flag = 0;
	
		FILE *usuarios = fopen("user.bin","a+b");
		
		rewind(usuarios);
	
		do{
			if(strcmp(usuario2.login, usuario.login) == 0){
				fclose(usuarios);
				printf("[ERRO] JA EXISTE UM USUARIO COM ESSE LOGIN");
				system("\n\n\ntimeout /T 10");
				return 1;
			}
			
			if(usuario2.admin == 1 && usuario.existe == 1){
				fclose(usuarios);
				printf("__________________________________________________\n");
				printf("\n[ERRO] JA EXISTE UM ADMINISTRADOR AUTENTICADO\n");
				printf("__________________________________________________\n");
				system("\n\n\ntimeout /T 10");
				return 1;
			}
			
		}while( fread(&usuario, sizeof(User), 1, usuarios) == 1);
		
		usuario.admin = usuario2.admin;
		strcpy(usuario.login, usuario2.login);
		strcpy(usuario.senha, usuario2.senha);
		strcpy(usuario.nome, usuario2.nome);
					
		if(usuario.admin == 1){
			printf("__________________________________________________\n");
			printf("\n\n\tADMINISTRADOR CADASTRADO\n");
			printf("__________________________________________________\n");
			system("\n\n\ntimeout /T 10");
			usuario.existe = 1;
			fwrite(&usuario, sizeof(User), 1, usuarios);
			fclose(usuarios);
			menu_admin();	
		}
		
		
		fclose(usuarios);
	return 1;
}


void editar(){
	
	system("cls");
	
	int op;
	
	do{
		puts("========================= Editar =========================");
		printf("||\t1 - Editar Login\t\t\t\t||\n");
		printf("||\t2 - Editar Senha\t\t\t\t||\n");
		printf("||\t3 - Sair\t\t\t\t\t||\n");
		puts("======================== Editar ==========================");
		printf("> ");
		scanf("%i", &op);
		
		if(op == 1){
			mudar_login();
		}
		
		if(op == 2){
			mudar_senha();
		}
		
		if(op == 3){
			break;
		}
		
		else if(op < 1 || op > 3){
			system("cls");
			printf("\n\t[OPCAO NAO EXISTENTE]");
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			getch();
			system("cls");
		}
		
	
	}while(op < 1 || op > 3);
	
}

void reset_ranking(){
	system("cls");
	FILE *arquivo = fopen("ranking.bin","wb");
	
	if(arquivo == NULL){
		printf("\n\n");
		printf("\t\t[ERRO] Não há Ranking para ser removido");
		system("\n\n\ntimeout /T 5");
	}
	else{
		remove("ranking.bin");
		printf("\n\n");
		printf("\t\t[OK] Ranking resetado com sucesso");
		system("\n\n\ntimeout /T 5");
	}
	
	fclose(arquivo);
	
}

void menu_admin(){
	
	int opcao;
	int op_menu_admin, t, dif;
	char *nome;
	
	
	do{
		system("cls");
		puts("=================== MENU ADMININASTRO ====================");
		printf("||\t1 - Jogar  \t\t\t\t\t||\n");
		printf("||\t2 - Ranking\t\t\t\t\t||\n");
		printf("||\t3 - Editar \t\t\t\t\t||\n");
		printf("||\t4 - Resetar Ranking \t\t\t\t||\n");
		printf("||\t5 - Sair     \t\t\t\t\t||\n");                       
		puts("=================== MENU ADMININASTRO ====================");
		printf("> ");
		scanf("%i", &op_menu_admin);
		
		
		if(op_menu_admin == 1){
			jogar();
		}
		else if(op_menu_admin == 2){
			rank(2, nome, t, dif);
		}	
		else if(op_menu_admin == 3){
			editar();
		}
		else if(op_menu_admin == 4){
			reset_ranking();
		}
		
		else if(op_menu_admin < 1 || op_menu_admin > 5){
			system("cls");
			printf("\n\t[OPCAO NAO EXISTENTE]");
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			getch();
			system("cls");
		}
		
	}while(op_menu_admin != 5);
	
}


void mudar_login(){
	
	
	int flag, flag1, flag2 = 2;
	char login[20], novologin[20], novologin2[20], senha[20];
	
	system("cls");
	
	FILE *usuarios, *usuarios2;
	
	usuarios = fopen("user.bin","rb");
	usuarios2 = fopen("user2.bin","wb");
	
	puts("==================== MUDAR LOGIN =====================");
	printf("Digite o Login: ");
	printf("\n> ");
	setbuf(stdin,NULL);
	fgets(login, 50, stdin);
	printf("Digite a senha: ");
	printf("\n> ");
	setbuf(stdin,NULL);
	fgets(senha, 50, stdin);
	
	rewind(usuarios);
	
	while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
		if(strcmp(senha, usuario.senha) == 0 && strcmp(login, usuario.login) == 0){
			flag = 1;
			break;
		}
		else{
			flag = -1;
		}
	}
	if(flag == -1){
		printf("\n\n\t[ERRO] Login ou Senha nao corresponde");
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch();
	}
	
	if(flag == 1){
		
		printf("\nDigite novo Login: ");
		printf("\n> ");
		setbuf(stdin,NULL);
		fgets(novologin, 20, stdin);
		
		rewind(usuarios);
		while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
			if(strcmp(novologin,usuario.login) == 0){
				printf("[ERRO] JA EXISTE UM USUARIO COM ESSE LOGIN");
				flag2 = 1;
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				getch();
				break;
			}
		}
		
		if(flag2 != 1){
			printf("\nConfirme o Login: ");
			printf("\n> ");
			setbuf(stdin,NULL);
			fgets(novologin2, 20,stdin);
			
		puts("================= MUDAR LOGIN E SENHA ==================");
		
			if(strcmp(novologin, novologin2) != 0){
				printf("\n\n\t[ERRO] os Logins nao sao iguais");
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				getch();
			}
			
			else{
				printf("\n\n\tLogin alterado com sucesso!!!");
				flag1 = 10;
				printf("\n\n\t[APERTE ENTER]");
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				getch();
			}	
		}
	}
	else{
		printf("\n\n\t[ERRO] NAO existe usuario com esse Login ou essa senha");
	}

	
	rewind(usuarios);
	
	if(flag1 == 10){
		while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
	       	if(strcmp(login, usuario.login) != 0){
	       	    fwrite(&usuario, sizeof(User), 1, usuarios2);
	       	}
	       	else{
	       		if(usuario.admin == 1){
	       			usuario.admin = 1;
	       			usuario.existe = 1;
				}
				else{
					usuario.admin = 2;
					usuario.existe = 2;
				}
	     		strcpy(usuario.login, novologin);
	     		strcpy(usuario.senha, senha);
	    
	     		fwrite(&usuario, sizeof(User), 1, usuarios2);
			}
		}
	}
	else{
		while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
			fwrite(&usuario, sizeof(User), 1, usuarios2);
		}
	}

	fclose(usuarios);
   	fclose(usuarios2);
   	
    remove("user.bin");
    rename("user2.bin","user.bin");
	
	
	printf("\n\n\t[APERTE ENTER]");
	
	
	
}

void mudar_senha(){
	
	int flag;
	char login[50], senha[50], novasenha[50], novasenha2[50];
	system("cls");
	
	FILE *usuarios, *usuarios2;
	
	usuarios = fopen("user.bin","rb");
	usuarios2 = fopen("user2.bin","wb");
	
	puts("===================== MUDAR SENHA ====================");
	printf("Digite seu Login: ");
	printf("\n> ");
	setbuf(stdin,NULL);
	fgets(login, 50, stdin);
	printf("Digite sua senha: ");
	printf("\n> ");
	setbuf(stdin,NULL);
	fgets(senha, 50, stdin);
	while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
		if(strcmp(senha, usuario.senha) == 0 && strcmp(login, usuario.login) == 0){
			flag = 1;
			break;
		}
	}
	if(flag == 1){
		printf("\nDigite nova senha: ");
		printf("\n> ");
		setbuf(stdin,NULL);
		fgets(novasenha, 50, stdin);
		printf("\nConfirme a senha: ");
		printf("\n> ");
		setbuf(stdin,NULL);
		fgets(novasenha2, 50, stdin);
		
		puts("\n===================== MUDAR SENHA ====================");
		
		if(strcmp(novasenha, novasenha2) == 0){
			printf("\n\n\tSenha alterada com sucesso!!!");
			flag = 10;
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			getch();
		}
		else{
			printf("\n\n\t[ERRO] as senhas nao coincidem");
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			getch();
		}
	}
	else{
		printf("\n\n\t[ERRO] NAO existe usuario com essa senha");
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch();
	}

	
	rewind(usuarios);
	
	while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
		if(flag == 10){
        	if(strcmp(login, usuario.login) != 0){
        	    fwrite(&usuario, sizeof(User), 1, usuarios2);
       	 	}
       	 	else{
       	 		
       	 		if(usuario.admin == 1){
       	 			usuario.admin = 1;
					usuario.existe = 1;	
				}
				else{
					usuario.admin = 2;
					usuario.existe = 2;
				}
       	 		
       	 		strcpy(usuario.login, login);
       	 		strcpy(usuario.senha, novasenha);
    	
       	 		fwrite(&usuario, sizeof(User), 1, usuarios2);
			}
		}
		else{
			fwrite(&usuario, sizeof(User), 1, usuarios2);
		}
	}

	fclose(usuarios);
   	fclose(usuarios2);
   	
    remove("user.bin");
    rename("user2.bin","user.bin");
	
	
	printf("\n\n\t[APERTE ENTER]");
		
}


void jogar(){
	
	system("mode con: cols=140 lines=25");
	
	setlocale(LC_ALL, "Portuguese");
	FILE *usuarios;
	FILE *atributos, *atributos1;
	int flag = 0;
	int linha = 0,tecla;
	int aceitou_missao = 0, recusou_missao = 0;
	char op_missao[10], nome[20];
		
		
	
	usuarios = fopen("user.bin","rb");
	rewind(usuarios);
	
	while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
		strcpy(nome, usuario.nome);
		break;
	}
	
	for(int i = 1; i < strlen(nome); i++){
		if(nome[i] == '\n'){
			nome[i] = '\0';
			break;
		}
	}
	fclose(usuarios);
	
	atributos = fopen("atributos.bin", "a+b");
	
	if(fread(&atrbt, sizeof(Atributes), 1, atributos) != 1){
	    game_reset();
	}
	
	fclose(atributos);
	
	atributos = fopen("atributos.bin", "a+b");
	if(fread(&atrbt, sizeof(Atributes), 1, atributos) == 1){
		if(atrbt.parte == 1){
			printf("\n\tVocê ja completou a parte 1 - Prólogo, deseja:");
			textcolor(2 ,0);
			printf("\n\t Continuar para parte 2");
			textcolor(4 ,0);
			printf("\n\t Reiniciar parte 1");
			textcolor(15,0);
			linha = seta(2, 2);
			if(linha == 2){
				fclose(atributos);
				game_reset();
				linha = 0;
			}
			else{
				atrbt.parte = 1;
				
				fclose(atributos);
				linha = 0;
			}
		}
		else if(atrbt.parte == 2){
			printf("\n\tVocê ja completou a parte 2 - Prólogo, deseja:");
			textcolor(2 ,0);
			printf("\n\t Continuar para parte 3");
			textcolor(4 ,0);
			printf("\n\t Reiniciar parte 1");
			textcolor(15,0);
			linha = seta(2, 2);
			
			if(linha == 2){
				fclose(atributos);
				game_reset();
				linha = 0;
			}
			else{
				atrbt.parte = 2;
				fclose(atributos);
				linha = 0;
			}
		}
		fclose(atributos);
	}

	if(atrbt.parte  == 0 || atrbt.parte == 1){
		system("cls");
		printf("\n\n");
		Sleep(1000);
		printf("\t\t ola %s\n \ttudo bem com você? espero que sim", nome);
		Sleep(500);
		printf("\n\tMe chamo Jonas, e estou aqui pra nossa primeira missão juntos :)\n");
		Sleep(500);		
		printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch();
		
		
		do{
			
			flag = 0;
			
			system("cls");
			printf("\n\t%s você aceita saber qual é a missão?", nome);
			textcolor(2,0);
			printf("\n\t1(aceitar)");
			textcolor(15,0);
			printf(" ou");
			textcolor(4,0);
			printf(" 2(recusar)");
			textcolor(15,0);
			printf("\n\tDica: você pode digitar a palavra aceitar/recusar ou digitar 1 / 2");
			printf("\n\t> ");
			setbuf(stdin,NULL);
			gets(op_missao);
			
			if(comps ( "aceitar", op_missao) == 0 || comps(op_missao, "1") == 0){
				printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				getch();
				aceitou_missao++;
			}
			else if(comps("recusar", op_missao) == 0 || comps(op_missao, "2") == 0){
				printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				getch();
				recusou_missao++;
			}		
			
			if(comps(op_missao, "1") != 0 && comps(op_missao, "2") != 0){
				flag++;
			}
			if(comps(op_missao, "aceitar") != 0 && comps(op_missao, "recusar") != 0){
				flag++;
			}
		}while(flag == 2);
	}
		
	if(atrbt.parte == 0){
		
		//historia
		system("cls");
		printf("\n\tMas antes, vou contar um pouquinho sobre você, e o que está havendo...");
		Sleep(3000);
		system("cls");
		printf("\n\n\t\t6 MESES ATRÁS...");
		Sleep(2000);
		system("cls");
		printf("\n\tEu sou Poseidon, o Rei do mar e tudo o que nele habita.");
		Sleep(1000);
		printf("\n  Você é filho de Zeus, como já diziam, ele realmente não sabe segurar o ziper fechado...");
		Sleep(1000);
		printf("\n  Quando os deuses tem seus filhos, eles tomam parte do poder para si, não é hereditário.");
		printf("\n  E assim que vocês morrem, os poderes retornam para o verdadeiro dono.");
		Sleep(1200);
		printf("\n  Mas vou do começo, assim que você nasceu...");
		printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch();
		
		system("cls");
		printf("\n\tVocê nasceu na cidade de Londres, da grande Região de Londres.");
		Sleep(1000);
		printf("\n  Sua mãe era uma bela mulher, era muito inteligente e muito determinada.");
		Sleep(1000);
		printf("\n  Eu até arriscaria dizer que ela tinha o poder da persuasão.");
		Sleep(1000);
		printf("\n  Zeus a conheceu em uma de suas idas ao mundo inferior,");
		Sleep(1000);
		printf("\n  Como todos sabem Zeus nunca foi só de ir e voltar, ele gostava de se exibir,");
		Sleep(1000);
		printf("\n  Ele gostava de passar um tempo com as mulheres daqui.");
		Sleep(1000);
		printf("\n  O que Zeus não sabia é que sua mãe tinha sido amaldiçoada por Cronos.");
		Sleep(1000);
		printf("\n  E o motivo disso? E que Cronos temendo ser destronado por um de seus filhos lançou-os uma maldição,");
		Sleep(1000);
		printf("\n  Aquele que tivesse seu décimo filho com uma humana,");
		printf("\n  Esse com o tempo tomaria o poder total de seu pai após completar os 22 anos.");
		Sleep(1500);
		
		printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch(); 
		
		
		system("cls");
		textcolor(12,0);
		printf("\n\t  E porque você quer me ajudar?");
		printf("\n\t  E o que eu devo fazer?");
		textcolor(15,0);
		linha = seta(1, 2);
		
		//decisao do que fazer
		if(linha == 1){
	    	system("cls");
	    	textcolor(15,0);
	    	printf("\n\t%s: E porque você quer me ajudar?", nome);
	    	printf("\n\tPoseidon: Por que eu quero te ajudar? só você pode conter essa fúria de Zeus isso se for bem treinado");
	    	Sleep(1000);
	    	printf("\n\tPoseidon: E então o que você me diz?");
	    	ir_poseidon();
	    	linha = 0;
		}
		else if(linha == 2){
			system("cls");
			textcolor(15,0);
			printf("\n\t%s: E o que eu devo fazer?", nome);
			printf("\n\tPoseidon: você precisa vir comigo");
			printf("\n\tposso te proteger e te treinar contra Zeus");
			ir_poseidon();
			linha = 0;
		}
	}
		
	if(atrbt.parte == 1){		
		if(aceitou_missao == 1){
			system("cls");
	
			int flag = 0;
			char op_conversar[4];
			
			
			do{
				flag = 0;
		
				system("cls");
				printf("\n\n\tvocê aceitou a missão com Jonas");
				printf("\n  você quer conversar com ele?");
				textcolor(2,0);
				printf("\n  1(sim)");
				textcolor(15,0);
				printf(" ou ");
				textcolor(4,0);
				printf("2(nao)");
				textcolor(15,0);
				printf("\n\n  Dica: [NÃO] use acento nas respostas");
				printf("\n\t> ");
				setbuf(stdin,NULL);
				gets(op_conversar);
				
				if(comps (op_conversar, "sim") == 0 || comps(op_conversar, "1") == 0){
					system("cls");
					printf("\n\t%s: Então, me conte um pouco mais sobre você.", nome);
					printf("\n\tJonas: Eu sou da Escócia, filho de Hades, uma das traições de Hades a Perséfone.");
					printf("\n\tJonas: De começo minha mãe não sabia sobre os deuses");
					textcolor(14,0);
					printf("\n\t[E como você descobriu?]");
					printf("\n\t[E como está sua mãe?]");
					textcolor(15,0);
					printf("\n[DICA]: escolhas que são em amarelo são escolhas que ramificam a história");
					linha = seta(4,2);
					if(linha == 1){
						system("cls");
						printf("\n\t%s: Então, me conte um pouco mais sobre você.", nome);
						printf("\n\tJonas: Eu sou da Escócia, filho de Hades, uma das traições de Hades a Perséfone.");
						printf("\n\tJonas: De começo minha mãe não sabia sobre os deuses.");
						textcolor(9,0);
						printf("\n\t%s: E como você descobriu?", nome);
						textcolor(15,0);
						printf("\n\tJonas: Hades apareceu pra mim, foi um pouco amedrontador...");
						printf("\n\t%s: Hades em pessoa?", nome);
						printf("\n\tJonas: É \"Em pessoa\"... ");
						printf("\n\t%s: Hades é um maniaco.", nome);
						printf("\n\tJonas: Eu não sei se ele achou, que aparecer numa forma demoniaca me ajudaria a entede-lo.");
						printf("\n\t%s: Pelo menos você conheceu seu pai.", nome);
						printf("\n\tJonas: Você é filho de Zeus, não é?");
						textcolor(14,0);
						printf("\n\t[Prefiro não comentar sobre]");
						printf("\n\t[Sim, como sabe?]");
						textcolor(15,0);
						linha = seta(12,2);
						if(linha == 1){
							system("cls");
							textcolor(9,0);
							printf("\n\t%s: Prefiro não comentar sobre...", nome);
							textcolor(15,0);
							printf("\n\tJonas: É eu te entendo, ser filho dos três grandes é um pouco ruim.");
							printf("\n\tJonas: Acho que o pessoal tem um pouco de inveja.");
							printf("\n\t%s: Acho bobagem.", nome);
							printf("\n\tJonas: Por quê?");
							printf("\n\t%s: deuses não são nada além daquilo que nós somente acreditamos,",nome);
							printf("\n\t%s: Nós mesmos nos forçamos a acreditar que eles tem poder sobre nós,", nome);
							printf("\n\t%s: Se eles podem ser derrotados, não devemos adora-los nem ter medo deles.", nome);
							printf("\n\tJonas: Interessante sua ideologia sobre deuses.");
							textcolor(4,0);
							printf("\n\t[E você, o que pensa?]");
							printf("\n\t[Você acha que estou errado?]");
							textcolor(15,0);
							linha = seta(10,2);
							if(linha == 1){
								system("cls");
								textcolor(9,0);
								printf("\n\t%s: E você, o que pensa?", nome);
								textcolor(15,0);
								printf("\n\tJonas: penso que eles são deuses, possuem poderes que facilmente nos mataria.");
								printf("\n\t%s: De certo modo você tem razão.", nome);
								linha = 0;
							}
							else if(linha == 2){
								system("cls");
								textcolor(9,0);
								printf("\n\t%s: Você acha que estou errado?", nome);
								textcolor(15,0);
								printf("\n\tJonas: não exatamente, só penso que eles pensam diferente de nós.");
								linha = 0;
							}	
							linha = 0;						
						}
						else if(linha == 2){
							system("cls");
							textcolor(9,0);
							printf("\n\t%s: Sim, como sabe?", nome);
							textcolor(15,0);
							printf("\n\tJonas: ouvi boatos que o filho de um dos três grandes se juntaria a ordem dos semi-deuses.");
							linha = 0;
						}
						linha = 0;
						printf("\n\tJonas: gostei de saber um pouco mais sobre você, mas chegamos.");
					}
					
					if(linha == 2){
						system("cls");
						printf("\n\t%s: Então, me conte um pouco mais sobre você.", nome);
						printf("\n\tJonas: Eu sou da Escócia, filho de Hades, uma das traições de Hades a Perséfone.");
						printf("\n\tJonas: De começo minha mãe não sabia sobre os deuses.");
						textcolor(9,0);
						printf("\n\t%s: E como está sua mãe?", nome);
						textcolor(15,0);
						printf("\n\tJonas: Bom... minha mãe faleceu há alguns anos.");
						printf("\n\t%s: Meus pesames.", nome);
						printf("\n\tJonas: Tudo bem, acho que já superei.");
						textcolor(4,0);
						printf("\n\t[Quer conversar sobre?]");
						printf("\n\t[Teve algo a ver com Hades?]");
						textcolor(15,0);
						linha = seta(8, 2);
						if(linha == 1){
							system("cls");
							textcolor(9,0);
							printf("\n\t%s: Quer conversar sobre?", nome);
							textcolor(15,0);
							printf("\n\tJonas: Acho que estou bem...");
							linha = 0;
						}
						else if(linha == 2){
							system("cls");
							textcolor(9,0);
							printf("\n\t%s: Teve algo a ver com Hades?", nome);
							textcolor(15,0);
							printf("\n\tJonas: Acho que não quero falar sobre...");
							linha = 0;
						}
						linha = 0;
					}	
				}
				else if(comps(op_conversar, "nao") == 0 ||comps(op_conversar, "2") == 0){
					system("cls");
					printf("\t você recusou :( ");
					
				}		
				
				if(comps(op_conversar, "1") != 0 && comps(op_conversar, "2") != 0){
					flag++;
				}
				if(comps(op_conversar, "sim") != 0 && comps(op_conversar, "nao") != 0){
					flag++;
				}
			}while(flag == 2);
			
			printf("\n\tJonas: Vem comigo, vamos falar com Apolo.");
			printf("\n\t%s: O deus do sol?", nome);
			printf("\n\tJonas: pois é amigo, um dos grandes do Olimpo vive aqui também por ordem de Zeus,");
			printf("\n\tJonas Ele ordenou que Apolo cuidasse dos semi-deuses.");
			printf("\n\t%s: Por quê?", nome);
			printf("\n\tJonas: E vai entender o que Zeus pensa, talvez medo da tal profecia...");
			
			printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			getch();
			
			do{	
				system("cls");
				printf("\n\tApolo: Olá Jonas, e quem é você?");
				printf("\n\t%s: Eu sou %s.", nome, nome);
				printf("\n\tApolo: Semi-deuses não costumam ter os mesmos nomes, de quem você é filho?");
				textcolor(14,0);
				printf("\n\t[Falar a verdade]");
				printf("\n\t[Mentir]");
				textcolor(4,0);
				printf("\n\t[Questionar Apolo]");
				textcolor(15,0);
				linha = seta(4,3);
				
				if(linha == 1){
					system("cls");
					printf("\n\t%s: Sou filho de Zeus.", nome);
					printf("\n\tApolo: Hmm, entendo, Zeus não costuma lembrar que tem filhos.");
					printf("\n\t%s: Com o tempo você se acostuma...", nome);
					
					Sleep(1000);
					printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					getch();
					linha = 0;
				}
				else if(linha == 2){
					system("cls");
					printf("\n\t%s: Sou filho de Hades", nome);
					printf("\n\tApolo: Com Perséfone?");
					printf("\n\t%s: Não, minha mãe é uma humana.", nome);
					printf("\n\tApolo: Dificilmente a Ordem envia irmãos em uma missão juntos.");
					printf("\n\tJonas: vai saber o que se passa na cabeça deles...");
					
					Sleep(1000);
					printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					getch();
					linha = 0;
				}
				else if(linha == 3){
					system("cls");
					printf("\n\t%s: Por que quer saber de quem eu sou filho?", nome);
					printf("\n\tApolo: É só uma pergunta, pra saber com quem eu converso.");
					
					Sleep(1000);
					printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					getch();
					linha = -1;
				}
			}while(linha != 0);
			
			system("cls");
			printf("\n\tJonas: E então, o que devemos fazer?");
			printf("\n\tApolo: A missão de vocês é reunir todos os filhos de Zeus.");
			printf("\n\t%s: Por quê?", nome);
			printf("\n\tApolo: Parece que a Ordem precisa conversar com os filhos do Grande deus");
			textcolor(4,0);
			printf("\n\t[Algum motivo em especial?]");
			printf("\n\t[Tem a ver com a profecia?]");
			textcolor(15,0);
			linha = seta(5,2);
			if(linha == 1){
				textcolor(9,0);
				system("cls");
				printf("\n\t%s: Algum motivo em especial?", nome);
				textcolor(15,0);
				printf("\n\tApolo: Creio que tem a ver com a profecia, talvez queiram protege-los");
				linha = 0;
			}
			else if(linha == 2){
				textcolor(9,0);
				system("cls");
				printf("\n\t%s: Tem a ver com a profecia?", nome);
				textcolor(15,0);
				printf("\n\tApolo: Creio que sim, talvez queiram protege-los");
				linha = 0;
			}
			textcolor(14,0);
			printf("\n\t[Aceitar missão]");
			printf("\n\t[Recursar missão]");
			textcolor(15,0);
			linha = seta(3,2);
			
			if(linha == 1){
				aceitou_missao++;
				system("cls");
				printf("\n\tAqui estão alguns atributos que podem ser uteis pra você.");
				printf("\n\n\t[PARABÉNS VOCÊ DESBLOQUEOU A HABILIDADE DA PERSUASÃO]");
				
				printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				getch();
				
				atributos = fopen("atributos.bin", "a+b");	
				rewind(atributos);
		    	while(fread(&atrbt, sizeof(Atributes), 1, atributos) == 1){
		    		if(atrbt.parte == 1){
		    					    		    			    
			    		atrbt.persuasao++;
						atrbt.sabedoria++;
						atrbt.inteligencia++;
						atrbt.carisma++;
						atrbt.parte++;
			    		
			    		atributos1 = fopen("atributos1.bin", "w+b");
			    		fwrite(&atrbt, sizeof(Atributes), 1, atributos1);
			    		
			    		fclose(atributos);
						fclose(atributos1);
			
						remove("atributos.bin");
						rename("atributos1.bin", "atributos.bin");
						break;
			    	}
			    	else{
			    		fclose(atributos);
			    		break;
					}
			    }
				
				linha = 0;
			}		
			else if(linha == 2){
				recusou_missao = 1;
				system("cls");
				printf("\n\tRecusando a missão você se dedicou ao treinamento por algum tempo...");
				
				printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				getch(); 
				linha = 0;
			}
		}
		if(recusou_missao == 1){
			printf("\n\n\tSeu treinamento com a ordem te rendeu algumas habilidades...");
			printf("\n\n\t[PARABÉNS VOCÊ DESBLOQUEOU A HABILIDADE DA FURTIVIDADE]");
			
			printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			getch();
			
			atributos = fopen("atributos.bin", "a+b");
			rewind(atributos);
	    	while(fread(&atrbt, sizeof(Atributes), 1, atributos) == 1){
	    		if(atrbt.parte == 1){
	    
		    		atrbt.furtividade++;
					atrbt.forca++;
					atrbt.constituicao++;
					atrbt.destreza++;
					atrbt.parte++;
		    		
		    		atributos1 = fopen("atributos1.bin", "w+b");
		    		fwrite(&atrbt, sizeof(Atributes), 1, atributos1);
		    		
		    		fclose(atributos);
					fclose(atributos1);
		
					remove("atributos.bin");
					rename("atributos1.bin", "atributos.bin");
					break;
		    	}
		    	else{
		    		fclose(atributos);
		    		break;
				}
		    }
		}
		
		mostrar_atributos();
	}
	
	if(atrbt.parte == 2){
		system("cls");
		printf("\n\n\tPOR ENQUANTO EH TUDO :( :P");
		
		printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch();
	}
	
	/*fclose(usuarios);
	fclose(atributos);*/
}

void ir_poseidon(){
	
	FILE *atributos, *atributos1;
	atributos = fopen("atributos.bin", "a+b");
	
	
	int linha;
	
	textcolor(12,0);
    printf("\n\t[ir com Poseidon]");
    printf("\n\t[não ir com Poseidon]");
    textcolor(15,0);
    linha = seta(4, 2);
    
    
    if(linha == 1){
    		
    	system("cls");
    		
    	printf("\n\tVocê escolheu ir com Poseidon, seu treinamento de 6 meses começa agora...");
    	Sleep(2000);
    	printf("\n\t");
    	for(int i = 0; i <= 10; i++){
    		printf("%c", 22);
		}
    	printf(" 20%%");
    	Sleep(1500);
    	system("cls");
    		
    	printf("\n\tVocê escolheu ir com Poseidon, seu treinamento de 6 meses começa agora...");
    	printf("\n\t");
    	for(int i = 0; i <= 25; i++){
    		printf("%c", 22);
		}
    	printf(" 50%%");
    	Sleep(1500);
    	system("cls");
    		
    	printf("\n\tVocê escolheu ir com Poseidon, seu treinamento de 6 meses começa agora...");
    	printf("\n\t");
    	for(int i = 0; i <= 40; i++){
    		printf("%c", 22);
		}
    	printf(" 80%%");
    	Sleep(1500);
    	system("cls");
    		
    	printf("\n\tVocê escolheu ir com Poseidon, seu treinamento de 6 meses começa agora...");
    	printf("\n\t");
    	for(int i = 0; i <= 50; i++){
    		printf("%c", 22);
		}
    	printf(" 100%%");
    	Sleep(2000);
    		
    	textcolor(1,15);
    	printf("\n\n\tSeu treinamento com Poseidon foi concluido com sucesso");
    	textcolor(15,0);
    	
    	rewind(atributos);
    	while(fread(&atrbt, sizeof(Atributes), 1, atributos) == 1){
    		if(atrbt.parte == 0){
    		    			    
	    		atrbt.forca += 2;
	    		atrbt.inteligencia += 1;
	    		atrbt.destreza += 2;
	    		atrbt.constituicao += 1;
	    		atrbt.parte++;
	    		
	    		atributos1 = fopen("atributos1.bin", "w+b");
	    		fwrite(&atrbt, sizeof(Atributes), 1, atributos1);
	    		
	    		fclose(atributos);
				fclose(atributos1);
	
				remove("atributos.bin");
				rename("atributos1.bin", "atributos.bin");
				break;
	    	}
	    	else{
	    		fclose(atributos);
	    		break;
			}
	    }
    	
    	printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch();
		linha = 0;
	}
		
	else if(linha == 2){
		system("cls");
		printf("\n\tVocê escolheu [NÃO] ir com Poseidon.");
		printf("\n\tele acreditou no seu pontencial e não insistiu porque você é carismático...");
		
		rewind(atributos);
		while(fread(&atrbt, sizeof(Atributes), 1, atributos) == 1){
			if(atrbt.parte == 0){
				
				atrbt.sabedoria += 2;
				atrbt.carisma += 2;
				atrbt.inteligencia += 1;
				atrbt.forca += 1;
				atrbt.parte++;
				
				atributos1 = fopen("atributos1.bin", "w+b");
	    		fwrite(&atrbt, sizeof(Atributes), 1, atributos1);
	    		
	    		fclose(atributos);
				fclose(atributos1);
	
				remove("atributos.bin");
				rename("atributos1.bin", "atributos.bin");
				break;
	    	}
	    	else{
				fclose(atributos);
				break;
			}
		}
			
		printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
		
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getch(); 	
		linha = 0;
	}
	
	
	mostrar_atributos();
	
}

void mostrar_atributos(){
	
	FILE *atributos;
	
	atributos = fopen("atributos.bin", "rb");
	
	
	while(fread(&atrbt, sizeof(Atributes), 1, atributos) == 1){
		system("cls");
		printf("\n\n\t[SEUS ATRIBUTOS SÃO]:");
		printf("\n\n  Saberdoria ----: %i ", atrbt.sabedoria);
		printf("\n  Carisma -------: %i ", atrbt.carisma);
		printf("\n  Força ---------: %i ", atrbt.forca);
		printf("\n  Inteligencia --: %i ", atrbt.inteligencia);
		printf("\n  Constituição --: %i ", atrbt.constituicao);
		printf("\n  Destreza ------: %i ", atrbt.destreza);
		if(atrbt.persuasao == 1){
			printf("\n  Persuasão -----: Aprendeu");
		}
		else if(atrbt.persuasao == 0){
			printf("\n  Persuasão -----: Não aprendeu");
		}
		if(atrbt.furtividade == 1){
		printf("\n  Furtividade ---: Aprendeu");
		}
		else if(atrbt.furtividade == 0){
			printf("\n  Furtividade ---: Não aprendeu");
		}
		
	}
	
	fclose(atributos);
	
	printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	getch(); 
	
}
