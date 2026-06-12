// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {int h, m;} tempo; 
typedef struct Voo voo; 

struct Voo{ 
   char codigo[6];         // código do voo   
   char destino[4];        // código do destino 
   int emTerra;            // sim = 1; não = 0; 
   tempo t;                // hora de partida  
};

int main() {

   printf("estudasses!\n");

   return 0;
}

voo *f_aeroporto (char *f_binario, tempo hora_atual, char dest[4], int *tam) {

   FILE *f_bin = fopen(f_binario, "rb+"); if (!f_bin) return NULL;

   int i;
   voo atual;
   *tam = 0;

   while (fread(&atual, sizeof(voo), 1, f_bin) == 1 ) {

      if (strcmp(atual.destino, dest) == 0) (*tam)++;

      if (atual.emTerra == 0) continue;
      
      /*if (atual.t.h < hora_atual.h) {
         atual.emTerra = 0;
      } else if (atual.t.h == hora_atual.h) {
         if (atual.t.m < hora_atual.m) {
            atual.emTerra = 0;
         } else {
            continue;
         }
      } else {
         continue;
      }*/
      
      if (atual.t.h < hora_atual.h || (atual.t.h == hora_atual.h && atual.t.m < hora_atual.m)) {
         atual.emTerra = 0;
      } else {
         continue;
      }
      
      // só chega no fseek, se ele de facto ja tiver decolado
      fseek(f_bin, -sizeof(voo), SEEK_CUR);
      fwrite(&atual, sizeof(voo), 1, f_bin);
      fseek(f_bin, 0, SEEK_CUR);
   }

   // fim do ponto i)

   // inicio do ponto ii)
   // vamos criar um array dinamico

   if (*tam == 0) {
      fclose(f_bin);
      return NULL;
   }

   voo *vetor = malloc((*tam) * sizeof(voo)); 
   if (!vetor) {
      fclose(f_bin);
      return NULL;
   }

   rewind(f_bin);

   i = 0;

   while (fread(&atual, sizeof(voo), 1, f_bin) == 1) {

      if (strcmp (atual.destino, dest) == 0) {
         vetor[i] = atual;
         i++;
      }
   }
   
   
   
   fclose(f_bin);
   return vetor; // vamos meter aqui o array dinamico
}



