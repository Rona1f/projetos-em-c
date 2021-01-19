#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GRIDSIZE 26
#define DEFAULTCHAR ' '

#define CLEAR "clear"

char grid[GRIDSIZE][GRIDSIZE];

// Estrutura do personagem
typedef struct Rick{
  int vida; 
  int balas;
  int posL; //posição (linha)
  int posC; //posição (coluna)
  char skin;
} Rick;

typedef struct Zumbi {
  int posL; //posição (linha)
  int posC; //posição (coluna)
  int active; //vida do zumbi: 1 para vivo/0 para morto
  char skin;
} Zumbi;

Rick rick;
Zumbi zumbi[15];

int gameover = 0;
int fim = 0; // resultado do jogo: 1 para vitoria/2 para derrota

void initGame(){ //função que inicia o jogo

  //define o tabuleiro
  for(int l=0;l<GRIDSIZE;l++){
    for(int c=0;c<GRIDSIZE;c++){
      grid[l][c] = DEFAULTCHAR;
    }
  }

  //define os atributos do personagem
  rick.vida = 10;
  rick.balas = 0;
  rick.posL = rand() % GRIDSIZE;
  rick.posC = rand() % GRIDSIZE;
  rick.skin = 'R';

  grid[rick.posL][rick.posC] = rick.skin; //posição inicial do personagem

  

  for(int b=0;b<4;b++){
    grid[rand()%GRIDSIZE][rand()%GRIDSIZE] = 'b';
  }
  for(int z=0;z<=15;z++){
    zumbi[z].posL = rand()%GRIDSIZE;
    zumbi[z].posC = rand()%GRIDSIZE;
    zumbi[z].skin = 'z';
    zumbi[z].active = 1;
    grid[zumbi[z].posL][zumbi[z].posC] = zumbi[z].skin;
  }
  for(int c=0;c<=4;c++){
    grid[rand()%GRIDSIZE][rand()%GRIDSIZE] = 'c';
  }
  for(int a=0;a<=7;a++){
    grid[rand()%GRIDSIZE][rand()%GRIDSIZE] = 'a';
  }
  for(int p=0;p<=8;p++){
    grid[rand()%GRIDSIZE][rand()%GRIDSIZE] = 'p';
  }
    //posição da saída
      grid[rand() % GRIDSIZE][rand() % GRIDSIZE] = 'S';
  for(int l=0;l<GRIDSIZE;l++){
    for(int c=0;c<GRIDSIZE;c++){
      printf("%c ", grid[l][c]);
    }
    printf("\n");
  }

}

void update(){ //atualiza a interface
  system(CLEAR);
  
  for(int l=0;l<GRIDSIZE;l++){
    for(int c=0;c<GRIDSIZE;c++){
      printf("%c ", grid[l][c]);
    }
    printf("\n");
  }
  printf("\nBalas = %i\n", rick.balas);
}

void movement(char move){ //função de movimento do jogador
  grid[rick.posL][rick.posC]=DEFAULTCHAR;
  if(move=='w' && (grid[rick.posL-1][rick.posC]==DEFAULTCHAR || grid[rick.posL-1][rick.posC]=='b' || grid[rick.posL-1][rick.posC]=='z' || grid[rick.posL-1][rick.posC]=='S')){

    rick.posL-=1;

    if(grid[rick.posL][rick.posC]=='b') rick.balas+=1;
    if(grid[rick.posL][rick.posC]=='S') {
      fim = 1;
      gameover=1;
      }
    if(grid[rick.posL][rick.posC]=='z'){
      if(rick.balas==0) {
        gameover=1;
        fim = 2;
      } else {
        rick.balas-=1;
      }
    }
  }
  if(move=='a' && (grid[rick.posL][rick.posC-1]==DEFAULTCHAR ||grid[rick.posL][rick.posC-1]=='b' || grid[rick.posL][rick.posC-1]=='z' || grid[rick.posL][rick.posC-1]=='S')){
    rick.posC-=1;

    if(grid[rick.posL][rick.posC]=='b') rick.balas+=1;
    if(grid[rick.posL][rick.posC]=='S') {
      fim = 1;
      gameover=1;
      }
    if(grid[rick.posL][rick.posC]=='z'){
      if(rick.balas==0) {
        gameover=1;
        fim = 2;
      } else {
        rick.balas-=1;
      }
    }
  }
  if(move=='s' && (grid[rick.posL+1][rick.posC]==DEFAULTCHAR || grid[rick.posL+1][rick.posC]=='b' || grid[rick.posL+1][rick.posC]=='z' || grid[rick.posL+1][rick.posC]=='S')){
    rick.posL+=1;

    if(grid[rick.posL][rick.posC]=='b') rick.balas+=1;
    if(grid[rick.posL][rick.posC]=='S') {
      fim = 1;
      gameover=1;
      }
    if(grid[rick.posL][rick.posC]=='z'){
      if(rick.balas==0) {
        gameover=1;
        fim = 2;
      } else {
        rick.balas-=1;
      }
    }
  }
  if(move=='d' && (grid[rick.posL][rick.posC+1]==DEFAULTCHAR|| grid[rick.posL][rick.posC+1]=='b' || grid[rick.posL][rick.posC+1]=='z' || grid[rick.posL][rick.posC+1]=='S')){
    rick.posC+=1;

    if(grid[rick.posL][rick.posC]=='b') rick.balas+=1;
    if(grid[rick.posL][rick.posC]=='S') {
      fim = 1;
      gameover=1;
      }
    if(grid[rick.posL][rick.posC]=='z'){
      if(rick.balas==0) {
        gameover=1;
        fim = 2;
      } else {
        rick.balas-=1;
      }
    }
  }
  grid[rick.posL][rick.posC] = rick.skin;

  update();
}

int main(void) { 
  srand(time(NULL));

  initGame();
  

  while(gameover==0){
    
    update();
    printf("\nMovimento [WASD]: ");
    char move;
    scanf("%c", &move);
    getchar();
    


    for(int i=0; i<15;i++){
      if(zumbi[i].posL==rick.posL && zumbi[i].posC==rick.posC) zumbi[i].skin = DEFAULTCHAR;
      if(abs(zumbi[i].posL-rick.posL)<=3 && abs(zumbi[i].posC-rick.posC)<=3){
        grid[zumbi[i].posL][zumbi[i].posC]=DEFAULTCHAR;
        if(zumbi[i].posL > rick.posL){
          if(grid[zumbi[i].posL-1][zumbi[i].posC]==DEFAULTCHAR) zumbi[i].posL -=1;     
          goto stop;
        }
        if(zumbi[i].posL < rick.posL){
          if(grid[zumbi[i].posL+1][zumbi[i].posC]==DEFAULTCHAR) zumbi[i].posL +=1;
          goto stop;
        }
        if(zumbi[i].posC > rick.posC){
          if(grid[zumbi[i].posL][zumbi[i].posC-1]==DEFAULTCHAR) zumbi[i].posC -=1;
          goto stop;
        }
        if(zumbi[i].posC < rick.posC){
          if(grid[zumbi[i].posL][zumbi[i].posC+1]==DEFAULTCHAR) zumbi[i].posC +=1;
          goto stop;
        }
        stop:;
        grid[zumbi[i].posL][zumbi[i].posC] = zumbi[i].skin;
      }
      
    }
      movement(move);
  }
  system(CLEAR);
  if(fim == 2){
    printf("==================\n");
    printf("Rick esta morto...\n");
    printf("==================\n");
  }
  if(fim == 1){
    printf("===============\n");
    printf("RICK ESCAPOU!!!\n");
    printf("===============\n");
  }
  
  printf("Enter para encerrar...");
  getchar();
  return 0;
}
