#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define crsize 9
#define udsize 26


int main(void) {
  srand(time(NULL));
  system("cls");

  char classroom[crsize][crsize];
  char upsidedown[udsize][udsize];
  char demodogsgrid[udsize][udsize];

  char bgchar = '`';

  int endgame = 0;
  int state = 1;
  int encontrou=0;

  int vidaEleven = 100;

  int posEleven[2] = {1,1};
  int posWill[2] = {rand()%udsize, rand()%udsize};

  //inicializa a sala de aula
  for(int l=0;l<crsize;l++){
    for(int c=0;c<crsize;c++){
      classroom[l][c] = bgchar;
    }
  }
  classroom[1][1] = 'E';
  for(int l=0;l<crsize;l++){
    for(int c=0;c<crsize;c++){
      printf("%c ",classroom[l][c]);
    }
    printf("\n");
  }

  //inicializa o mundo invertido
  for(int l=0;l<udsize;l++){
    for(int c=0;c<udsize;c++){
      upsidedown[l][c] = bgchar;
    }
  }
  for(int l=0;l<udsize;l++){
    for(int c=0;c<udsize;c++){
      demodogsgrid[l][c] = bgchar;
    }
  }
  
  for(int i=0;i<10;i++){
    upsidedown[rand()%udsize][rand()%udsize] = 't';
  }
  for(int i=0;i<5;i++){
    upsidedown[rand()%udsize][rand()%udsize] = 'c';
  }
  for(int i=0;i<5;i++){
    upsidedown[rand()%udsize][rand()%udsize] = 'a';
  }
  for(int i=0;i<4;i++){
    demodogsgrid[rand()%udsize][rand()%udsize] = 'd';
  }
  for(int i=0;i<10;i++){
    upsidedown[rand()%udsize][rand()%udsize] = 'p';
  }
  upsidedown[1][1] = 'E';
  upsidedown[posWill[0]][posWill[1]] = 'W';
  upsidedown[rand()%udsize][rand()%udsize] = '*';


while(endgame == 0){
  switch(state){
    
    case 1: //sala de aula (abrindo o portal) 
      printf("\nVida: %i \nEnter para tentar abrir o portal ", vidaEleven);
      getchar();

      if(rand()%101 >= 60){
        state = 2;
        classroom[rand()%crsize][rand()%crsize] = '*';
      } else{
        vidaEleven -= 20;
      }
      break;

    case 2: //sala de aula (portal aberto)
    system("cls");
    for(int l=0;l<crsize;l++){
      for(int c=0;c<crsize;c++){
        printf("%c ",classroom[l][c]);
      }
    printf("\n");
    }
    printf("\nVida: %i\nMovimento[wasd]: \n", vidaEleven);

    char move[2];
    fgets(move, 2, stdin);


    //movimento
    if(move[0] == 'w'){
      
      classroom[posEleven[0]][posEleven[1]] = bgchar;
      if(classroom[posEleven[0]-1][posEleven[1]]=='*') {
        state = 3;
        posEleven[0] = 1;
        posEleven[1] = 1;
        break;
        }
        posEleven[0] -= 1;
      classroom[posEleven[0]][posEleven[1]] = 'E';
      
    }
    if(move[0] == 'a'){
      
      classroom[posEleven[0]][posEleven[1]] = bgchar;
      if(classroom[posEleven[0]][posEleven[1]-1]=='*') {
        state = 3;
        posEleven[0] = 1;
        posEleven[1] = 1;
        break;
        }
        posEleven[1] -= 1;
      classroom[posEleven[0]][posEleven[1]] = 'E';
      
    }
    if(move[0] == 's'){
      
      classroom[posEleven[0]][posEleven[1]] = bgchar;
      if(classroom[posEleven[0]+1][posEleven[1]]=='*') {
        state = 3;
        posEleven[0] = 1;
        posEleven[1] = 1;
        break;
        }
        posEleven[0] += 1;
      classroom[posEleven[0]][posEleven[1]] = 'E';
      
    }
    if(move[0] == 'd'){
      
      classroom[posEleven[0]][posEleven[1]] = bgchar;
      if(classroom[posEleven[0]][posEleven[1]+1]=='*') {
        state = 3;
        posEleven[0] = 1;
        posEleven[1] = 1;
        break;
        }
        posEleven[1] += 1;
      classroom[posEleven[0]][posEleven[1]] = 'E';
      
    }

    break;

    case 3: // mundo invertido
      system("cls");
      for(int l=0;l<udsize;l++){
        for(int c=0;c<udsize;c++){
          printf("%c ",upsidedown[l][c]);
        }
      printf("\n");
      }
      
      printf("\nVida: %i\nMovimento[wasd]: \n", vidaEleven);

    fgets(move, 2, stdin);

    //movimento
    if(move[0] == 'w' && (upsidedown[posEleven[0]-1][posEleven[1]]==bgchar || upsidedown[posEleven[0]-1][posEleven[1]] == 'p' || upsidedown[posEleven[0]-1][posEleven[1]] == '*')){
      
      upsidedown[posEleven[0]][posEleven[1]] = bgchar;
      posEleven[0] -= 1;
      if(upsidedown[posEleven[0]][posEleven[1]]=='*' && encontrou==10) state = 4;
      if(upsidedown[posEleven[0]][posEleven[1]]=='p') if(vidaEleven<100) vidaEleven+=10;
      if(demodogsgrid[posEleven[0]][posEleven[1]]=='d') vidaEleven-=10; demodogsgrid[posEleven[0]][posEleven[1]]=bgchar;
      upsidedown[posEleven[0]][posEleven[1]] = 'E';
    }
    if(move[0] == 'a' && (upsidedown[posEleven[0]][posEleven[1]-1]==bgchar || upsidedown[posEleven[0]][posEleven[1]-1] == 'p' || upsidedown[posEleven[0]][posEleven[1]-1] == '*')){
      
      upsidedown[posEleven[0]][posEleven[1]] = bgchar;
      posEleven[1] -= 1;
      if(upsidedown[posEleven[0]][posEleven[1]]=='*' && encontrou==10) state = 4;
      if(upsidedown[posEleven[0]][posEleven[1]]=='p') if(vidaEleven<100) vidaEleven+=10;
      if(demodogsgrid[posEleven[0]][posEleven[1]]=='d') vidaEleven-=10; demodogsgrid[posEleven[0]][posEleven[1]]=bgchar;
      upsidedown[posEleven[0]][posEleven[1]] = 'E';
    }
    if(move[0] == 's' && (upsidedown[posEleven[0]+1][posEleven[1]]==bgchar || upsidedown[posEleven[0]+1][posEleven[1]] == 'p' || upsidedown[posEleven[0]+1][posEleven[1]] == '*')){

      upsidedown[posEleven[0]][posEleven[1]] = bgchar;
      posEleven[0] += 1;
      if(upsidedown[posEleven[0]][posEleven[1]]=='*' && encontrou==10) state = 4;
      if(upsidedown[posEleven[0]][posEleven[1]]=='p') if(vidaEleven<100) vidaEleven+=10;
      if(demodogsgrid[posEleven[0]][posEleven[1]]=='d') vidaEleven-=10; demodogsgrid[posEleven[0]][posEleven[1]]=bgchar;
      upsidedown[posEleven[0]][posEleven[1]] = 'E';
    }
    if(move[0] == 'd' && (upsidedown[posEleven[0]][posEleven[1]+1]==bgchar || upsidedown[posEleven[0]][posEleven[1]+1] == 'p' || upsidedown[posEleven[0]][posEleven[1]+1] == '*')){

      upsidedown[posEleven[0]][posEleven[1]] = bgchar;
      posEleven[1] += 1;
      if(upsidedown[posEleven[0]][posEleven[1]]=='*' && encontrou==10) state = 4;
      if(upsidedown[posEleven[0]][posEleven[1]]=='p') if(vidaEleven<100) vidaEleven+=10;
      if(demodogsgrid[posEleven[0]][posEleven[1]]=='d') vidaEleven-=10; demodogsgrid[posEleven[0]][posEleven[1]]=bgchar;
      upsidedown[posEleven[0]][posEleven[1]] = 'E';
    }

    
    // will
    switch(rand()%4+encontrou){
      case 0: //will move para cima
        if(upsidedown[posWill[0]-1][posWill[1]]==bgchar) {
          upsidedown[posWill[0]][posWill[1]] = bgchar;
          posWill[0]-=1;
          upsidedown[posWill[0]][posWill[1]] = 'W';
        }
        break;
      case 1: // will move para esquerda
      if(upsidedown[posWill[0]][posWill[1]-1]==bgchar) {
          upsidedown[posWill[0]][posWill[1]] = bgchar;
          posWill[1]-=1;
          upsidedown[posWill[0]][posWill[1]] = 'W';
        }
      break;
      case 2: //will move para baixo
      if(upsidedown[posWill[0]+1][posWill[1]]==bgchar) {
          upsidedown[posWill[0]][posWill[1]] = bgchar;
          posWill[0]+=1;
          upsidedown[posWill[0]][posWill[1]] = 'W';
        }
      break;
      case 3: //will move para a direita
      if(upsidedown[posWill[0]][posWill[1]+1]==bgchar) {
          upsidedown[posWill[0]][posWill[1]] = bgchar;
          posWill[1]+=1;
          upsidedown[posWill[0]][posWill[1]] = 'W';
        }
      break;
      default:
      upsidedown[posWill[0]][posWill[1]] = bgchar;
        posWill[0] = posEleven[0]+1;
        posWill[1] = posEleven[1]+1;
        upsidedown[posWill[0]][posWill[1]] = 'W';
    }

    if(posEleven[0]-posWill[0]>=-3 && posEleven[0]-posWill[0]<=3 && posEleven[1]-posWill[1]>=-3 && posEleven[1]-posWill[1]<=3 && encontrou == 0) {
      encontrou = 10;
      for(int i=0;i<3;i++)
      {
        demodogsgrid[rand()%(posEleven[0]+4)+(posEleven[0]-4)][rand()%(posEleven[0]+4)+(posEleven[0]-4)] = 'd';
        }
      }

    break;
    case 4:
    system("cls");
    printf("\nVidas: %i\nVoce salvou Will!\n\nEnter para encerrar...", vidaEleven);
    getchar();
    getchar();
    endgame=1;
    break;
  }
  if(vidaEleven <= 0) {printf("Eleven morreu...\nEnter para encerrar...");
  getchar();
  getchar();
  endgame=1;
  } 
 }
}
