#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void gameFunc(){
  
  int gridsize = 30;
  int vidaJon = 100;
  int resultadoLutaJonCersei=0;
  
  
  srand(time(NULL));

  

  char grid[gridsize][gridsize];

  for(int l = 0; l < gridsize; l++){
    for(int c = 0; c<gridsize;c++){
      grid[l][c] = ' ';
    }
  }

  for(int i = 0; i < 20; i++)
  {
      grid[rand()%gridsize][rand()%gridsize] = 'i';
  }
  for(int i = 0; i < 10; i++)
  {
      grid[rand()%gridsize][rand()%gridsize] = 'o';
  }
  for(int i = 0; i < 5; i++)
  {
      grid[rand()%gridsize][rand()%gridsize] = 'p';
  }

  for(int x = gridsize/2-1; x<=gridsize/2+1;x++){
    for(int y = gridsize/2-1; y<=gridsize/2+1;y++){
      grid[x][y] = '*';
    }
  }
  
  for(int x = gridsize-3; x<=gridsize-1;x++){
    for(int y = gridsize-3; y<=gridsize-1;y++){
      grid[x][y] = '*';
    }
  }

  grid[0][0] = 'J';
  grid[gridsize/2][gridsize/2] = 'C';
  grid[gridsize-2][gridsize-2] = 'N';


  int posjon[2]={0,0};


  for(int l = 0; l < gridsize; l++){
    for(int c = 0; c<gridsize;c++){
      printf("%c ", grid[l][c]);
    }
    printf("\n");
  }



  while(1){
  printf("Movimento (W/A/S/D) Vidas: %i: \n", vidaJon);
  
  char move[1];
  fgets(move, 2, stdin);

//===========================================================
// Movimentação

  if(move[0] == 'd' && grid[posjon[0]][posjon[1]+1]!='o'){

    if(grid[posjon[0]][posjon[1]+1] == 'i'){
      vidaJon -= 1;
    }
      if(grid[posjon[0]][posjon[1]+1] == 'p'){
        vidaJon += 5;
      }

    grid[posjon[0]][posjon[1]] = ' ';
    grid[posjon[0]][posjon[1]+1] = 'J';

    posjon[1] += 1;

    } else   if(move[0] == 'w' && grid[posjon[0]-1][posjon[1]]!='o'){
  
      if(grid[posjon[0]-1][posjon[1]] == 'i'){
        vidaJon -= 1;
      }
          if(grid[posjon[0]-1][posjon[1]] == 'p'){
        vidaJon += 5;
      }

      grid[posjon[0]][posjon[1]] = ' ';
      grid[posjon[0]-1][posjon[1]] = 'J';

      posjon[0] -= 1;

    } else   if(move[0] == 'a' && grid[posjon[0]][posjon[1]-1]!='o'){

      
      if(grid[posjon[0]][posjon[1]-1] == 'i'){
        vidaJon -= 1;
      }
      if(grid[posjon[0]][posjon[1]-1] == 'p'){
        vidaJon += 5;
      }

      grid[posjon[0]][posjon[1]] = ' ';
      grid[posjon[0]][posjon[1]-1] = 'J';

      posjon[1] -= 1;

    } else   if(move[0] == 's' && grid[posjon[0]+1][posjon[1]]!='o'){

          
      if(grid[posjon[0]+1][posjon[1]] == 'i'){
        vidaJon -= 1;
      }
      if(grid[posjon[0]+1][posjon[1]] == 'p'){
        vidaJon += 5;
      }

      grid[posjon[0]][posjon[1]] = ' ';
      grid[posjon[0]+1][posjon[1]] = 'J';

      posjon[0] += 1;
    }
//===========================================================

//Chega em Westeros
  int tentVitoria=0;
  if(posjon[0] >= gridsize/2-1 && posjon[0] <= gridsize/2+1 && posjon[1] >= gridsize/2-1 && posjon[1] <= gridsize/2+1 && resultadoLutaJonCersei == 0){
    int resTenta[5];
    

    for(int i =0;i<=5;i++){
      printf("\n%iº tentativa... aperte enter", i);
      getchar();
      resTenta[i] = rand() % 101;
      if(resTenta[i] >=60){
        tentVitoria += 1;
      }
    }

    if(tentVitoria <=2){
      //luta contra Cersei
      //system("cls");
      printf("A negociação não deu certo.\n Westeros declarou guerra!");
      int lutaAcabou=0;
      int vidaCersei=100;
      while(lutaAcabou == 0){
        printf("\n\nJon Snow - Vida = %i\n", vidaJon);
        for(int i=0;i<=vidaJon;i++){
          if(i%10 == 0){
            printf(":");
          } 
        }
        printf("\n");
        printf("\nCersei Lannister - Vida = %i\n", vidaCersei);
        for(int i=0;i<=vidaCersei;i++){
          if(i%10 == 0){
            printf(":");
          }          
        }

        printf("\n");
        
        printf("\nenter para atacar! ");
        getchar();

        int taxaDeAtaque = rand() % 101;

        if(taxaDeAtaque >=50){
          printf("\nAcertou o ataque! Cersei -10\n");
          vidaCersei -= 10;
        } else {
          printf("\nErrou o ataque, vez de Cersei. Jon -10");
          vidaJon -=10;

          int ataqueCersei = rand() %101;

          if(ataqueCersei >= 50){
            printf("\nCersei acertou! Jon -10");
            vidaJon -= 10;
          } else {
            printf("\nCersei errou, sua vez. Cersei -10");
            vidaCersei -= 10;
          }
        }

        //system("cls");




        if(vidaJon<=0){
          exit(0);
          
        } else if(vidaCersei <= 0){
          lutaAcabou = 1;
          resultadoLutaJonCersei = 1;
        }      
      }
    }
  }
  

  //system("cls");

          //Chega ao rei da noite
        if(posjon[0] >= gridsize-3 && posjon[0] <= gridsize-1 && posjon[1] >= gridsize-3 && posjon[1] <= gridsize-1 && resultadoLutaJonCersei == 1){
          printf("Voce chegou ao rei da noite. Começa a Guerra!");
          //batalha contra o rei da noite
          int vidaRei = 200;
          while(1){
            printf("\n\nJon Snow - Vida = %i\n", vidaJon);
        for(int i=0;i<=vidaJon;i++){
          if(i%10 == 0){
            printf(":");
          } 
        }
        printf("\n");
        printf("\nRei da Noite - Vida = %i\n", vidaRei);
        for(int i=0;i<=vidaRei;i++){
          if(i%10 == 0){
            printf(":");
          }          
        }

        printf("\n");
        
        printf("\nenter para atacar! ");
        getchar();

        int taxaDeAtaque = rand() % 101;

        if(taxaDeAtaque >=50){
          printf("\nAcertou o ataque! Rei da Noite -10\n");
          vidaRei -= 10;
        } else {
          printf("\nErrou o ataque, vez do Rei da Noite. Jon -10\n");
          vidaJon -=10;

          int ataqueCersei = rand() %101;

          if(ataqueCersei >= 50){
            printf("\nRei da Noite acertou! Jon -10\n");
            vidaJon -= 5;
            vidaRei += 5;
          } else {
            printf("\nRei da noite errou, sua vez. Rei da noite -10\n");
            vidaRei -= 10;
          }
        }

        if(vidaJon<=0){
          printf("\nVoce foi derrotado. Fim de jogo");
          exit(0);
        }
        if(vidaRei<=0){
          printf("\nVoce venceu a guerra!");
          exit(0);
        }

        //system("cls");
          }
        }
  //imprime o cenario atualizado      
  for(int l = 0; l < gridsize; l++){
    for(int c = 0; c<gridsize;c++){
      printf("%c ", grid[l][c]);
    }
    printf("\n");
  }
      if(tentVitoria>=3){
      printf("\nConseguiu a ajuda de Cersei\n");
      resultadoLutaJonCersei = 1;
      vidaJon += 100;
    }
 }
}


int main(void) {
  gameFunc();
}