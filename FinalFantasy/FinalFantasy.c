#include <stdio.h> 
#include <time.h> 
#include <stdlib.h>

#define TAMTIME 4

//estrutura dos times
typedef struct Times {
  int id;
  char nome[20];
  float vida;
  int ataque;
  int defesa;
} Times;

//funções
void iniciarTimes();
int definirTimequeComeca();
void atacar(Times* jogadorqueataca,int id_ataque, Times* jogadorquedefende, int id_defesa);
void atualizarVida(Times* jogadorqueataca, int id_ataque, Times* jogadorquedefende, int id_defesa);
float calcularPrecisao(Times* jogadorqueataca);
void jogar();
void atualizarTela(Times* time_1, Times* time_2);

  
Times time1[TAMTIME];
Times time2[TAMTIME];

int gameover=0;
int timedavez;

void delay(float seconds){
    float milliseconds = seconds*1000;
    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

void carregando(float seconds, int pontos){
  for(int i=0; i<pontos; i++){
    printf(".");
    delay(seconds);
  }
  printf("\n");
}

// Driver code to test above function 
int main() 
{srand(time(NULL)); 

	iniciarTimes();
  int timequecomeca = definirTimequeComeca();
  timedavez = timequecomeca;
  printf("definindo time que inicia");
  carregando(0.3, 5);
  printf("O time %i inicia atacando", timequecomeca);
  carregando(0.2,10);
  delay(3);
  
  jogar(time1, time2);
	return 0; 
} 

void iniciarTimes(){

  for(int i=0;i<TAMTIME;i++){
    time1[i].id = i;
      
    printf("Time 1 - Nome do lutador: ");
    scanf("%s", time1[i].nome);
    //fgets(time1[i].nome, 20, stdin);

    time1[i].vida = 100;
    time1[i].ataque = rand() % 11;
    time1[i].defesa = rand() % 11;
    printf("\n");
  }
  for(int i=0;i<TAMTIME;i++){
    time2[i].id = i;
      
    printf("Time 2 - Nome do lutador: ");
    scanf("%s", time2[i].nome);
    //fgets(time2[i].nome, 20, stdin);

    time2[i].vida = 100;
    time2[i].ataque = rand() % 11;
    time2[i].defesa = rand() % 11;
    printf("\n");
  }
  printf("Times definidos\n");
  carregando(0.1, 15);
  system("cls");

}

int definirTimequeComeca(){
  return (rand() % 2) + 1;
}


void jogar(){
    while(gameover==0){
        system("cls");
        atualizarTela(time1, time2);
        printf("\n\nVez do time %i", timedavez);
        if(timedavez==1){
            int jogataca;
            printf("\nQuem ataca? ");
            scanf("%i", &jogataca);
            getchar();
            int jogdefende;
            printf("\nQuem defende? ");
            scanf("%i", &jogdefende);
            getchar();
            
            atacar(time1, jogataca, time2, jogdefende);
            timedavez = 2;
        } else {
            int jogataca;
            printf("\nQuem ataca? ");
            scanf("%i", &jogataca);
            getchar();
            
            int jogdefende;
            printf("\nQuem defende? ");
            scanf("%i", &jogdefende);
            getchar();
            
            atacar(time2, jogataca, time1, jogdefende);
            timedavez = 1;
        }
    }
}


void atacar(Times* jogadorqueataca, int id_ataque, Times* jogadorquedefende, int id_defesa){
    
    float precisao = 100 - (jogadorqueataca[id_ataque].ataque*jogadorqueataca[id_ataque].defesa);
    if(rand()%101 > precisao){
        printf("\nAcertou o ataque!");
        carregando(0.4,3);
        int vidaatual = jogadorquedefende[id_defesa].vida;
        atualizarVida(jogadorqueataca, id_ataque, jogadorquedefende, id_defesa);
        printf("-%.0f\n", vidaatual-jogadorquedefende[id_defesa].vida);
        carregando(0.3, 10);
    } else {
        printf("\nErrou o ataque");
        carregando(0.4,3);
    }
}

void atualizarVida(Times* jogadorqueataca, int id_ataque, Times* jogadorquedefende, int id_defesa){
    jogadorquedefende[id_defesa].vida = jogadorquedefende[id_defesa].vida - jogadorqueataca[id_ataque].ataque/jogadorquedefende[id_defesa].defesa;
}

void atualizarTela(Times* time_1, Times* time_2){
    for(int i = 0; i<TAMTIME;i++){
        
       printf("\n%i:  %s  hp-%.0f  atq-%i  def-%i      --x--      %i:  %s  hp-%.0f  atq-%i  def-%i\n", time_1[i].id,time_1[i].nome,time_1[i].vida,time_1[i].ataque,time_1[i].defesa, time_2[i].id,time_2[i].nome,time_2[i].vida,time_2[i].ataque,time_2[i].defesa);
       printf("\n");    
    
    }
}




















