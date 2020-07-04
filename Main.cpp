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

char c[10];

typedef struct {
	
	int existe;
	char login[20];
	char senha[20];
	char nome[20];
	int admin;

} User;

typedef struct {
	
	int inteligencia;
	int forca;
	int persuasao;
	int carisma ;
	
	
} Atributes;

Atributes atrbt;

User usuario;
User usuario1, usuario2;

void flush(){
    char c;
    while((c = getch()) != '\n' && c != EOF);
}

//copiar funcoes pro codigo principal depois
void aceitar_missao();
void recusar_missao();
void mostrar_atributos();
void ir_poseidon();


typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;

static int __BACKGROUND = BLACK;
static int __FOREGROUND = WHITE;

void textcolor (int letra, int fundo){
    __FOREGROUND = letra;
    __BACKGROUND = fundo;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letra + (__BACKGROUND << 4));
}



int main(){
	
	setlocale(LC_ALL, "Portuguese");
	FILE *usuarios, *atributos;
	int flag = 0;
	int flag2 = 0;
	int linha = 1,tecla;
	int aceitou_missao = 0, recusou_missao = 0;
	
	char nome[10] = "Felipe";  //apagar depois pra nao setar o nome
	
	char op_missao[10];
	char aceitar[10] = "aceitar";
	char aceitar1[10] = "1";
	char recusar[10] = "recusar";
	char recusar1[10] = "2";
	
	usuarios = fopen("user.bin","rb");
	atributos = fopen("atributos.bin", "a+b");
	rewind(usuarios);
	rewind(atributos);
	
/*	while(fread(&usuario, sizeof(User), 1, usuarios) == 1){
		strcpy(nome, usuario.nome);
		break;
	}
	
	for(int i = 1; i < strlen(nome); i++){
		if(nome[i] == '\n'){
			nome[i] = '\0';
			break;
		}
	}*/
	//fclose(usuarios);
	
	system("cls");
	printf("\n\n");
	Sleep(1000);
	printf("\t\t ola %s\n \ttudo bem com você? espero que sim\n", nome);
	Sleep(500);
	printf("\tMe chamo Jonas, e estou aqui pra nossa primeira missão juntos :)\n");
	Sleep(500);
	setbuf(stdin,NULL);
	printf("\t[APERTE ENTER PRA CONTINUAR]");
	getch();
	setbuf(stdin,NULL);
	do{
		setbuf(stdin,NULL);
		flag = 0;
		flag2 = 0;
		system("cls");
		printf("\n\t%svocê aceita ir nessa missão com o Jonas?", nome);
	    setbuf(stdin,NULL);
		printf("\n\t1(aceitar) ou 2(recusar)");
		printf("\n\tDica: você pode digitar a palavra aceitar/recusar ou digitar 1 / 2");
		printf("\n\t> ");
		setbuf(stdin,NULL);
		gets(op_missao);
		
		if(comps (aceitar, op_missao) == 0 || comps(op_missao, aceitar1) == 0){
			//printf("\t você aceitou :) ");
			system("timeout /T 5");
			aceitou_missao++;
		}
		else if(comps(recusar, op_missao) == 0 || comps(op_missao, recusar1) == 0){
			//printf("\t você recusou :( ");
			system("timeout 5");
			recusou_missao++;
		}		
		
		if(comps(op_missao, aceitar1) != 0 && comps(op_missao, recusar1) != 0){
			flag = 1;
		}
		if(comps(op_missao, aceitar) != 0 && comps(op_missao, recusar) != 0){
			flag2 = 1;
		}
	}while(flag == 1 && flag2 == 1);
	
	system("cls");
	printf("\n\tMas antes, vou contar um pouquinho sobre você, e o que está havendo...");
	Sleep(3000);
	system("cls");
	printf("\n\n\t\t6 MESES ATRÁS...");
	Sleep(2000);
	system("cls");
	printf("\n  Eu sou Poseidon, o Rei do mar e tudo o que nele habita.");
	Sleep(1000);
	printf("\n  Você é filho de Zeus, como já diziam, ele realmente não sabe segurar o ziper fechado...");
	Sleep(1000);
	printf("\n  Quando os deuses tem seus filhos, eles tomam parte do poder para si, não é hereditário.");
	printf("\n  E assim que vocês morrem, os poderes retornam para o verdadeiro dono.");
	Sleep(1200);
	printf("\n  Mas vou do começo, assim que você nasceu...");
	setbuf(stdin,NULL);
	printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
	setbuf(stdin,NULL);
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
	setbuf(stdin,NULL);
	printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
	getch(); 
	setbuf(stdin,NULL);
	system("cls");
	textcolor(12,0);
	printf("\n\t  E porque você quer me ajudar?");
	printf("\n\t  E o que eu devo fazer?");
	linha = seta(1, 2);
	setbuf(stdin,NULL);
	
	//decisao do que fazer
	
	
    if(linha == 1){
    	system("cls");
    	textcolor(15,0);
    	printf("\n\t%s: E porque você quer me ajudar?", nome);
    	printf("\n\tPoseidon: Por que eu quero te ajudar? só você pode conter essa fúria de Zeus isso se for bem treinado");
    	Sleep(1000);
    	printf("\n\tPoseidon: E então o que você me diz?");
    	ir_poseidon();
    	
	}
	else if(linha == 2){
		system("cls");
		textcolor(15,0);
		printf("\n\t%s: E o que eu devo fazer?", nome);
		printf("\n\tPoseidon: você precisa vir comigo");
		printf("\n\tposso te proteger e te treinar contra Zeus");
		ir_poseidon();
	}
	
	if(aceitou_missao == 1){
		aceitar_missao();
	}
	if(recusou_missao == 1){
		recusar_missao();
	}
	
	
	fclose(usuarios);
	fclose(atributos);
}

void ir_poseidon(){
	
	
	int linha;
	
	textcolor(12,0);
    	printf("\n\t[ir com Poseidon]");
    	printf("\n\t[não ir com Poseidon]");
    	textcolor(15,0);
    	linha = seta(4, 2);
    	setbuf(stdin,NULL);
    	printf(" %i ", linha);
    	if(linha == 1){
    		
    		system("cls");
    		
    		printf("\n\tVocê escolheu ir com Poseidon, seu treinamento de 6 meses começa agora...");
    		Sleep(2000);
    		printf("\n\t");
    		setbuf(stdin,NULL);
    		printf(" 20%%");
    		Sleep(1500);
    		system("cls");
    		
    		printf("\n\tVocê escolheu ir com Poseidon, seu treinamento de 6 meses começa agora...");
    		printf("\n\t");
    		setbuf(stdin,NULL);
    		printf(" 50%%");
    		Sleep(1500);
    		system("cls");
    		
    		printf("\n\tVocê escolheu ir com Poseidon, seu treinamento de 6 meses começa agora...");
    		printf("\n\t");
    		setbuf(stdin,NULL);
    		printf(" 80%%");
    		Sleep(1500);
    		system("cls");
    		
    		printf("\n\tVocê escolheu ir com Poseidon, seu treinamento de 6 meses começa agora...");
    		printf("\n\t");
    		setbuf(stdin,NULL);
    		printf(" 100%%");
    		Sleep(2000);
    		
    		textcolor(1,15);
    		printf("\n\n\tSeu treinamento com Poseidon foi concluido com sucesso");
    		textcolor(15,0);
    		
    		atrbt.forca += 2;
    		atrbt.inteligencia += 1;
    		
    		setbuf(stdin,NULL);
    		printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
			getch(); 
			setbuf(stdin,NULL);
    		
		}
		
		else if(linha == 2){
			system("cls");
			printf("\n\tVocê escolheu [NÃO] ir com Poseidon, ele acreditou no seu pontencial e não insistiu porque você é carismático...");
			
			atrbt.persuasao += 1;
			atrbt.carisma += 2;
			
			setbuf(stdin,NULL);
			printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
			getch(); 
			setbuf(stdin,NULL);
		}
		
		mostrar_atributos();
}

void mostrar_atributos(){
	
	FILE *atributos;
	
	atributos = fopen("atributos.bin", "r+b");
	
	system("cls");
	printf("\n\n\t[SEUS ATRIBUTOS SÃO]:");
	printf("\n  persuasão ----: %i ", atrbt.persuasao);
	printf("\n  carisma ------: %i ", atrbt.carisma);
	printf("\n  força --------: %i ", atrbt.forca);
	printf("\n  inteligencia -: %i ", atrbt.inteligencia);
	
	setbuf(stdin,NULL);
	printf("\n\n\t[APERTE ENTER PRA CONTINUAR]");
	getch(); 
	setbuf(stdin,NULL);
	
	fclose(atributos);
}

void aceitar_missao(){
	system("cls");
	
	int flag = 0, flag1 = 0;
	char op_conversar[4];
	char sim[4] = "sim";
	char sim1[4] = "1";
	char nao[4] = "nao";
	char nao1[4] = "2";
	
	do{
		flag = 0;
		flag1 = 0;
		system("cls");
		printf("\n\n\tvocê aceitou a missão com Jonas");
		printf("\n  você quer conversar com ele?");
		printf("\n  1(sim) ou 2(nao)");
		printf("\n\n  Dica: [NÃO] use acento nas respostas");
		printf("\n\t> ");
		setbuf(stdin,NULL);
		gets(op_conversar);
		
		if(comps (op_conversar, sim) == 0 || comps(op_conversar, sim1) == 0){
			printf("\t você aceitou :) ");
			system("timeout /T 5");
			
		}
		else if(strcmp(op_conversar, nao) == 0 ||comps(op_conversar, nao1) == 0){
			printf("\t você recusou :( ");
			system("timeout 5");
		
		}		
		
		if(comps(op_conversar, sim1) != 0 && comps(op_conversar, nao1) != 0){
			flag = 1;
		}
		if(comps(op_conversar, sim) != 0 && comps(op_conversar, nao) != 0){
			flag1 = 1;
		}
	}while(flag == 1 && flag1 == 1);
	
}

void recusar_missao(){
	system("cls");
	
}









