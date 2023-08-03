#include <windows.h>//Biblioteca que permite acesso as funções API( Interface de programação de aplicação) do windows.
#include <conio.h> // Biblioteca de manipulação de caracteres.
#include <stdio.h>// Biblioteca de entrada e saída de dados.
//#include <locale.h> //Biblioteca para acentuação, que se usada neste código irá causar danos na interface gráfica.

#define LINHA 20
#define COLUNA 31

int x = 1;
int y = 1;
int ant_x = 1; 
int ant_y = 2;
int i = 0;
int j = 0;


enum DOS_COLORS{ //Esta função identifica as cores.

 preto, azul, verde, CYAN, vermelho, MAGENTA, castanho,
 cizento_claro, cizento_escuro, azul_claro, verde_claro, CYAN_claro,
 vermelho_claro, MAGENTA_claro, amarelo, branco
};

void textcolor(int iColor){ 	// Esta função permite a utilização das cores.

 HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
 BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
 bufferInfo.wAttributes &= 0x00F0;		
 SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}
void gotoxy(int x, int y){	//A função gotoxy permite o programador pré-determinar a posição de caracteres :)
	  COORD coord;
	  coord.X = x;
	  coord.Y = y;
	  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void desenha_mapa(char matriz[20][31]){ //Essa função desenha o mapa 
										//Desenha uma matriz do tipo "char" de 20 linhas e 31 colunas chamada matriz
    int c,l;	// l = linha, c = coluna
    gotoxy(0,0); //Esta linha de código fixa o mapa na janela de execução
               
    for(l=0;l<LINHA;l++)
    {
    	printf("\n\t");
        for(c=0;c<COLUNA;c++)
        {
            switch(matriz[l][c])
            {
                case 0:textcolor(branco); printf("%c",250); textcolor(1); //Desenha as comidinhas (250 = comidinha)
					break;
                case 1: printf("%c", 219); //Desenha os obstáculos de cor azul
					break;
				case 2: printf("%c", 187); //Desenha o canto superior direito do mapa
					break;
				case 3: printf("%c", 201); //Desenha o canto superior esquerdo do mapa
					break;
				case 4: printf("%c", 200); //Desenha o canto inferior esquerdo do mapa
					break;
				case 5: printf("%c", 188); //Desenha o canto inferior direito do mapa
					break;
				case 6: printf("%c", 186); //Desenha as paredes verticais do mapa
					break;
				case 7: printf("%c", 205); //Desenha as paredes horizontais do mapa
					break;
				case 8: textcolor(amarelo); printf("%c", 184); textcolor(1); // Desenha o personagem 	
					break;
				case 9: textcolor(vermelho); printf("%c", 219); textcolor(1); //Desenha os obstáculos de cor vermelha
					break;
				case 10:textcolor(verde); printf("%c", 219); textcolor(1); //Desenha os obstáculos de cor verde
					break;
				case 11:printf(" "); //Não desenha nada. O 11 representa o caminho que o personagem irá percorrer durante o jogo
					break;	
			
            }
        }
        
    }
}

void desenhar_jogador(char matriz[LINHA][COLUNA]){	// Jogador é desenhado no mapa (matriz[20][31])
		
		printf("%c",matriz[x][y]);
		if(matriz[x][y]!= 0 && matriz[x][y]!= 11){ 	//Se não for um caminho(0) nem comidinha(11)
        	x = ant_x;        
        	y = ant_y; 
        	//Este escopo serve para fazer com que o personagem continue na mesma posição caso ele encontre algum obstáculo 
			//(que não seja a comidinha, obviamente). Na função roda_jogo, ant_x = x e ant_y = y, o que vai fazer 
			//com que haja uma troca infinita de valores entre as variáveis e o personagem não irá prosseguir, impedindo
			//que ele simplesmente atravesse os obstáculos.
    	}else{
    		if(matriz[x][y] == 0){ //Se personagem toca na comidinha
				i++; //A variável k recebe mais 1 sempre que o jogador come uma comidinha
				j = i; //O contador recebe o valor de comidinhas comidas :)
				textcolor(branco); printf("\n\tPontos: %d /315",j); textcolor(1); //Exibe a quantidade de comidinhas comidas pelo jogador	
			}
    		matriz[x][y] = 8; 		//Se for um caminho
    						 	   // Desenha personagem na posição x = 1 e y = 1 
						          //         	||(ou)
							     // Se o personagem toca na comida
    					    	// Desenha personagem na posição da comida(personagem ocupa lugar da comidinha)
    		matriz[ant_x][ant_y] = 11;
    		//posição x = 1 e y = 2 recebe espaço vazio (11) 
    	   //as variáveis ant_x e ant_y são apenas úteis quando o personagem encontra um obstáculo  	   
		}	
		
}

void roda_jogo(){ // Essa função roda o jogo, desenhando o mapa, as comidinhas e determinando os movimentos do personagem
 	
 	 char matriz[LINHA][COLUNA]={  		//O mapa é desenhado usando os cases anteriormente definidos
	 	{3,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2},
		{6,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
		{6,0,11,11,1,11,0,0,0,0,0,0,11,1,1,11,0,0,0,0,0,0,0,0,0,11,1,1,11,0,6},
		{6,0,1,1,1,11,0,0,11,9,9,11,0,11,0,11,10,10,10,10,10,11,0,0,0,11,1,1,11,0,6},
		{6,0,11,11,1,11,0,0,0,0,0,0,0,11,0,11,10,10,11,0,0,0,0,0,0,0,0,0,0,0,6},
		{6,0,0,0,0,0,0,0,11,10,10,11,0,11,0,11,10,10,10,10,10,11,0,0,0,11,1,1,11,0,6},
		{6,0,0,0,0,0,0,0,11,10,10,11,0,11,0,11,10,10,11,0,0,0,0,0,0,11,1,1,11,0,6},
		{6,0,11,1,11,0,11,0,11,10,10,11,0,11,0,11,10,10,11,0,0,0,0,0,0,0,0,0,0,0,6},
		{6,0,11,1,11,0,11,0,11,10,10,11,0,11,0,11,10,10,11,0,0,0,0,11,1,1,11,0,0,0,6},
		{6,0,11,1,11,0,11,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,11,1,1,11,0,0,0,6},
		{6,0,11,1,11,0,11,0,0,0,0,0,0,0,11,0,0,0,0,0,0,0,0,11,1,1,11,0,0,0,6},
		{6,0,0,0,0,11,10,10,10,10,10,10,11,0,11,9,9,9,9,9,11,0,0,0,0,0,0,0,0,0,6},
		{6,0,0,0,0,0,0,11,10,10,11,0,0,0,11,9,9,11,0,0,0,0,0,0,0,0,0,0,0,0,6},
		{6,0,11,1,1,11,0,11,10,10,11,0,0,0,11,9,9,11,0,0,0,0,0,11,1,1,1,1,11,0,6},
		{6,0,11,1,1,11,0,11,10,10,11,0,0,0,11,9,9,11,0,0,0,0,0,11,1,1,1,1,11,0,6},
		{6,0,0,0,0,0,0,11,10,10,11,1,11,0,11,9,9,9,9,9,11,1,11,0,0,0,0,0,0,0,6},
		{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
		{6,0,0,11,1,1,1,1,1,11,0,0,0,0,0,0,0,0,0,0,11,1,1,1,1,11,0,0,0,0,6},
		{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
		{4,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,5}
	};

	int tecla; 		//Declara a variável tecla
 	char nome[20];  //Declara um vetor do tipo char que irá armazenar o nome do usuário			
		
	system("color 03"); //Define a cor da janela e da fonte
	printf("Digite seu nome: ");
	scanf("%s", nome);
	system("cls"); //Limpa a tela
		
	do{  
			
	    tecla = 0; //atribui um valor à variavel
		desenha_mapa(matriz); //Chama a função desenha_mapa ("matriz" é o nome da matriz que desenha/representa o mapa)
	    if(kbhit())//o kbhit() testa se alguma tecla foi pressionada
			tecla = getch(); // getch() lê um caracter do teclado
			desenhar_jogador(matriz); //Chama/executa a função desenhar_jogador
			ant_x = x; //troca infinita de valores entre as variáveis x e ant_x, como explicado na função desenhar_jogador
			ant_y = y; //troca infinita de valores entre as variáveis y e ant_y, como explicado na função desenhar_jogador
						    
			switch(tecla){
				case 80:							/* 80 = seta para baixo    */
					x++;							/*Personagem desce       */
					break;
				case 72:							/* 72 = seta para cima      */
					x--;							/*Personagem sobe         */
					break;
				case 77:						    /* 77 = seta para direita   */
					y++;								/*Personagem vai para a direita     */
					break;
				case 75:							/* 75 = seta para esquerda  */
					y--;							/*Personagem vai para a esquerda  */
					break;
			}
			if(j == 5){
			system("cls");
			system("color 07");
			gotoxy(0,6);
			
		    textcolor(azul); printf("====================================================="); textcolor(1);
		    textcolor(branco); printf("\n\t\tPARABENS, %s ", nome); textcolor(1);
		    textcolor(branco); printf("\n\t\tOBJETIVO ATINGIDO!!"); textcolor(1);
		    textcolor(azul); printf("\n====================================================="); textcolor(1);


		}				
	}while(tecla != 115 && j < 5); //   115 = tecla s
					
}
		

  
void como_jogar(){
 	
 	int tecla =0 ; //Atribui um valor à variável tecla
 	
 		do{
	 	    if(kbhit())//o kbhit() testa se alguma tecla foi pressionada
			    tecla = getch(); // getch() lê um caracter do teclado
				system("cls"); //Limpa a tela
				printf("Objetivo: coletar todas as comidinhas\n\nComandos:\n %c = vai para a esquerda\n %c = vai para a direita\n %c = vai para cima\n %c = vai para baixo\n S = sair\n",17,16,30,31);
				printf("\n*Warning:\nComandos errados podem causar danos ao jogo.\n\n\tBOM JOGO!!!");
				Sleep(100);	  //Esta função determina a velocidade de execução do código
		}while(tecla != 115 ); //    // 115 = tecla 's'
}

int main(){
	
	int opcao; //Declara a variável "opcao" do tipo inteiro
	int tecla = 0; //Declara e atribui um valor para a variável do tipo inteiro "tecla"
	
	do{
		if(kbhit())//o kbhit() testa se alguma tecla foi pressionada
			tecla = getch(); // getch() lê um caracter do teclado
			system("cls");
			system("mode 55,30");	 //Define o tamanho da janela.
					
			gotoxy(13,2); //pré-determina a posição dos caracteres		
			textcolor(3);printf("Sejam bem vindos ao \n");
			textcolor(7);printf("\n\t\t COME-COME \n");
			textcolor(3);printf("\n\tSelecione 1,2 ou 3: \n\t1-Jogar \n\t2-Como jogar?\n\t3-Sair\n\t");
			scanf("%i", &opcao); //Lê a variável opção
			
		    switch(opcao){
		       	case 1:
		        	//Jogar
		        	system("cls");  //Limpa a tela
					roda_jogo(); //Chama/executa a função roda_jogo
					return  0;				
		        	break;  //Fim do case
		       	case 2:
		        	// Como jogar
		        	como_jogar(); //Chama/executa a função como_jogar
		        	break; //Fim do case
		        case 3:
		        	//Sair
		        	system("cls");
		        	return 0;  //Cessa a execução do programa
		        default:
		        	//caso contrário.
		        	printf("Opcao invalida!");
		        	Sleep(500);
			}
		        	
	}while(opcao != 3); //Enquanto usuário não pressionar 3(sair).
	
}

