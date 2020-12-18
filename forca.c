#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void) {
  char alfabeto[27] = "qwertyuiopasdfghjklzxcvbnm";

  char palavra[20];
  char jogada[20];
  char campo[20];
  int q_letras = 0;

  printf("palavra: ");
  fgets(palavra, 20, stdin);

  for(int l=0; l < strlen(palavra)-1;l++){
      for(int a = 0; a < strlen(alfabeto);a++){
        if(palavra[l] == alfabeto[a]){
          ++q_letras;
          alfabeto[a] = '1';
        }      
      }
      strcat(campo, "-");
      
    }

  printf("%s", campo);

  int vitoria = 0;
  int vidas = 6;
  int acertos = 0;
  int acertos_g = 0;
  int jajog = 0;

  int palav_len = strlen(palavra);

  char jogados[20];

  while(vitoria == 0){
    acertos = 0;
    printf("\nsua jogada -> ");
    //jogada[0] = getchar();
    fgets(jogada, 20, stdin);

    if (strlen(jogada) > 1){
      if(strcmp(palavra, jogada) == 0){
        printf("vc acertou a palavra e ganhou!");
        break;
      }
    }
    
    //getchar();
    jajog = 0;

    for(int j = 0; j <= strlen(jogados); j++){
      if(jogada[0] == jogados[j]){
        jajog += 1;
      }
    }

    for (int i = 0; i <= palav_len; i++){
      
      if(palavra[i] == jogada[0] && jajog == 0){
        acertos += 1;
        campo[i] = palavra[i];
        strncat(jogados, jogada, 1);
      }
    }
    printf("%s", campo);

    if (acertos > 0){
      acertos_g += 1;
      printf("\nesta letra aparece %i vezes na palavra vc acertou %i", acertos, acertos_g);
    } else if(jajog == 0){
      vidas -= 1;
      printf("\nvoce errou... %i vidas restantes", vidas);
    } else {
      printf("\nVocê já jogou esta letra");
    }

    if (vidas == 0){
      printf("\nvoce perdeu...");
      break;
    }

    if(acertos_g == q_letras) {
      printf("\nvoce ganhou!");
      vitoria = 1;
      break;
    }

  }
  
  return 0;
}