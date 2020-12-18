#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int lxc;
int facil;

void init(){

  int tamTab=0;
  do{
      printf("tamanho do tabuleiro (max: 26): ");
      scanf("%i", &tamTab);
      getchar();
      lxc = tamTab + 1;
  }while(tamTab>26);

  printf("Nivel de facilidade (quanto maior menos bombas): ");
  int facilc;
  scanf("%i", &facilc);
  facil = facilc + 1;
  getchar();
}

void drawGrid(){
  srand(time(NULL));
  
  int posicionaBomba;

  char grid[lxc][lxc];
  int bomb[lxc][lxc];

  for(int i=0; i<lxc;i++){
    for(int j=0; j<lxc;j++){
      posicionaBomba = rand() % 4;
      bomb[i][j] = posicionaBomba;
      //printf("%i ", bomb[i][j]);
    }
    //printf("\n");
  }

  for(int i=0;i<=lxc;i++){
    char j = 'a'+i-1;
    grid[0][i] = j;
  }
  for(int i=1;i<=lxc;i++){
    grid[i][0] = 'a'+i-1;
  }

  for(int i=1;i<=lxc-1;i++){
    for(int j=1;j<=lxc-1;j++){
      grid[i][j] = '-';
    }
  }
  grid[0][0] = '+';
  for(int i=0;i<=lxc-1;i++){
    for(int j=0;j<=lxc-1;j++){
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }


  while(1){
    char linha = '.', coluna = '.';
    int poslin = 999, poscol = 999;


    printf("sua jogada [linha]x[coluna] ");
    scanf("%cx%c", &linha, &coluna);
    getchar();

    for(int i = 0; i<=lxc;i++){

      if (grid[i][0] == linha){
        
        poslin = i;
        //printf("\n%c poslin-%i", grid[i][0], poslin);
      }
      if (grid[0][i] == coluna){
        poscol = i;
        //printf("\n%c poscol-%i\n", grid[0][i], poscol);
      }
      if(poscol!=999 && poslin!=999){
        i=lxc+1;
      }
    }
    //printf("%ix%i = %i\n",poslin, poscol, bomb[poslin][poscol]);

    if(bomb[poslin][poscol] == 0){
      printf("\nexplodiu\n");
      system("cls");
      for(int e=1;e<lxc;e++){
        for(int x=1;x<lxc;x++){
          if(bomb[e][x] == 0){
            grid[e][x] = 'X';
          }
        }
      }
          for(int i=0;i<=lxc-1;i++){
      for(int j=0;j<=lxc-1;j++){
        printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
      printf("\nVoce perdeu");
      break;
      }
    else if (grid[poslin][poscol] == '-'){
      int contBombRaio = 0;
      int contadorArea = 0;
      int subdesc = 0;
      for(int pl=poslin-4;pl<=poslin+4;pl++){
        for (int pc=poscol-contadorArea;pc<=poscol+contadorArea;pc++){
          
          if(pl >0 && pc > 0 && pl<lxc && pc<lxc){
            if(bomb[pl][pc]!=0){
              grid[pl][pc]=' ';
            } else {
              grid[pl][pc]='#';
            }
              
          }
          
          if (pc == poscol-contadorArea){
            
            for(int i=pl-1;i<=pl+1;i++){
              for(int j=pc-1;j<=pc+1;j++){
                //printf("\n%ix%i", i, j);
                if(bomb[i][j]==0){
                  
                  contBombRaio += 1;
                  //printf("\n%ix%i - %i", pl, pc, contBombRaio);
                }
              }
            }
            if(contBombRaio>0 && bomb[pl][pc] != 0 && pc > 0 && pl > 0){
              grid[pl][pc] = '0'+contBombRaio;
            }
            contBombRaio = 0;
          }
          if (pc == poscol+contadorArea){

            for(int i=pl-1;i<=pl+1;i++){
              for(int j=pc-1;j<=pc+1;j++){
                if(bomb[i][j]==0){
                  contBombRaio += 1;
                  //printf("\n%ix%i", pl, pc);
                }
              }
            }
            if(contBombRaio>0 && bomb[pl][pc] != 0 && pc > 0 && pl > 0){
              grid[pl][pc] = '0'+contBombRaio;
            }
            contBombRaio = 0;
          }
          

        }
        if(contadorArea == 4){
          subdesc = 1;
        }
        if(subdesc == 0){
          contadorArea += 1;
        } else {
          contadorArea -=1;
        }
      }
    }
    system("cls");

    for(int i=0;i<=lxc-1;i++){
      for(int j=0;j<=lxc-1;j++){
        
        printf("%c ", grid[i][j]);
    }
    printf("\n");
  }

  int bombFalta=0;
  for(int i=0;i<=lxc;i++){
    for(int j=0;j<=lxc;j++){
      if(grid[i][j] != '-' && bomb[i][j] == 0){
        bombFalta += 1;
      }
    }
  }

  if(bombFalta == 0){
    printf("Voce ganhou");
    break;
  }

  }

  //system("clear");
}

int main() {
  system("cls");
  init();
  drawGrid();
    
  printf("\n\n enter para encerrar, s para jogar de novo");
  char op;
  scanf("%c", &op);
  
  if(op == 's'){
     getchar();
    system("cls");
    drawGrid();
  }
  
  return 0;
}
