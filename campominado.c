#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// define variavel de altura e largura do tabuleiro
int lxc;
//variavel de chance de ocorrer bombas, o que define a dificuldade do jogo
int facil;

void init(){
    
  // função que pede ao jogador o tamanho do tabuleiro e a facilidade do jogo  
  
  int tamTab=0;
  do{
      printf("tamanho do tabuleiro (max: 26): ");
      scanf("%i", &tamTab);
      getchar();
      lxc = tamTab + 1;
  }while(tamTab>26);

  do{
  printf("Nivel de facilidade (quanto maior menos bombas) (max: 9): ");
  int facilc;
  scanf("%i", &facilc);
  facil = facilc + 1;
  getchar();
  } while (facil > 10);
}

void drawGrid(){
  //------------------------------------
  // contrói o tabuleiro e inicia o jogo 
  //------------------------------------
  
  srand(time(NULL));
  
  int posicionaBomba; // guarda um valor aleatorio entre 0 e a facilidade escolhida pelo jogador

  char grid[lxc][lxc]; // tabuleiro
  int bomb[lxc][lxc]; // tabuleiro de bombas, invisivel ao jogador

  // define as posições das bombas
  for(int i=0; i<lxc;i++){
    for(int j=0; j<lxc;j++){
      posicionaBomba = rand() % facil;
      bomb[i][j] = posicionaBomba;
      //printf("%i ", bomb[i][j]);
    }
    //printf("\n");
  }
  //=============================================================================
  
  
//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
 // contrói as laterais do tabuleiro, com as coordenadas
  for(int i=0;i<=lxc;i++){
    char j = 'a'+i-1;
    grid[0][i] = j;
  }
  for(int i=1;i<=lxc;i++){
    grid[i][0] = 'a'+i-1;
  }
//- - - - - - - - - - - - - - - - - - - - - - - - - - - -

//- - - - - - - - - - - - - - - - - - - -
// controi o tabuleiro e imprime na tela
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
  //- - - - - - - - - - - - - - - - - - - -

//------------------------------------------------
    // loop update do jogo
//------------------------------------------------
  while(1){
     
    //reinicia as jogadas e os contadores
    char linha = '.', coluna = '.';
    int poslin = 999, poscol = 999;

    //pede a jogada
    printf("sua jogada [linha]x[coluna] ");
    scanf("%cx%c", &linha, &coluna);
    getchar();

    //navega pelas linhas e colunas e registra a posição no tabuleiro atacada
    for(int i = 0; i<=lxc;i++){

      if (grid[i][0] == linha){
        
        poslin = i;
      }
      if (grid[0][i] == coluna){
        poscol = i;
      }
      if(poscol!=999 && poslin!=999){
        i=lxc+1;
      }
    }
    
    // checa no tabuleiro de bombas se na posição atacada há uma bomba
    if(bomb[poslin][poscol] == 0){
        
      // se sim,imprime a derrota e revela as posições das bombas no tabuleiro visivel
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
        
      /* se não, checa se a posição ainda não foi atacada, se sim, abre uma area vazia, 
      revela a bombas dentro da area e informa quantas bombas estão nas proximidades das bordas
      */
      
      int contBombRaio = 0;
      int contadorArea = 0;
      int subdesc = 0;
      for(int pl=poslin-4;pl<=poslin+4;pl++){
        for (int pc=poscol-contadorArea;pc<=poscol+contadorArea;pc++){
          
          /* confere no tabuleiro de bombas se na posição na area atacada é uma bomba,
          se sim atualiza ela no tabuleiro de jogo, se não, atualiza para um espaço vazio
          */
          if(pl >0 && pc > 0 && pl<lxc && pc<lxc){
            if(bomb[pl][pc]!=0){
              grid[pl][pc]=' ';
            } else {
              grid[pl][pc]='#';
            }
              
          }
          
          // conta as bombas proxima da borda e atualiza a quantidade
          if (pc == poscol-contadorArea){
            
            for(int i=pl-1;i<=pl+1;i++){
              for(int j=pc-1;j<=pc+1;j++){
                if(bomb[i][j]==0){
                  
                  contBombRaio += 1;
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
                }
              }
            }
            if(contBombRaio>0 && bomb[pl][pc] != 0 && pc > 0 && pl > 0){
              grid[pl][pc] = '0'+contBombRaio;
            }
            contBombRaio = 0;
          }
          

        // contador para construção do losango (area atacada)
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
    
    // imprime o tabuleiro atualizado
    for(int i=0;i<=lxc-1;i++){
      for(int j=0;j<=lxc-1;j++){
        
        printf("%c ", grid[i][j]);
    }
    printf("\n");
  }


  // checa se o jogo acabou, se sim informa a vitoria e encerra o jogo
  int bombFalta=0;
  for(int i=1;i<=lxc;i++){
    for(int j=1;j<=lxc;j++){
      if(grid[i][j] == '-' && bomb[i][j] == 0){
        bombFalta += 1;
      }
    }
  }
  printf("\n%i bombas faltando\n", bombFalta);

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
