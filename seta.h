void gotoxy(int x,int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int seta(int linha, int qtd_opcoes){
	
		int tecla, linha_ini = linha;
	
	gotoxy(4,linha);
    	printf("%c", 16);
	    gotoxy(79,24);
	    
	    do{
	    	tecla = 0;
	        if(kbhit()){
	            tecla = getch();
	            gotoxy(4,linha);
	            printf("  ");
	            if(tecla==224){
	                tecla = getch();
	                if(tecla == 72){ //tecla pra cima
	                    linha--;
	                }
	                else{
	                    if(tecla == 80){  //tecla pra baixo
	                        linha++;
	                    }
	                }
	                if(linha > (linha_ini + qtd_opcoes) - 1 ){  //se apertar a seta pra baixo demais
	                    linha = linha_ini;                      // ela volta a ser a primeira opcao
	                }
	                else{
	                    if(linha < linha_ini){                     //se apertar demais pra cima
	                        linha = (linha_ini + qtd_opcoes) - 1;  //ela vai pra ultima opcao
	                    }
	                }
	                gotoxy(4,linha);
	                printf("%c", 16);
	                gotoxy(79,24);
	            }
	        }
	    }while(tecla != 13);
	return linha - (linha_ini - 1);
}

