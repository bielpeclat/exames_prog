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

struct sala{ 
   char id[10]; 
   int total; 
}; 
 
typedef struct pessoa no, *pno; 
struct pessoa{ 
   char nome[100], num[20]; // Nome e número do aluno 
   struct sala* p; // Ptr. para a sala onde o aluno fará o teste  
   pno prox; 
};

int main() {

   printf("estudasses!\n");

   return 0;
}

// ex.1 (ficheiros)
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
   return vetor; 
}

// ex.2 (listas ligadas) 
void mostra_alunos (pno alunos, struct sala *salas, int tam) {

   struct sala *sala_mais = salas;
   int i, empate = 0;

   for (i = 1; i < tam; i++) {

      if (sala_mais->total < salas[i].total) {
         sala_mais = &salas[i];
         empate = 0;

      } else if (sala_mais->total == salas[i].total) {
         empate = 1;
      }
   }

   if (empate) { // vamos sair caso tenha 2 valores mais altos
      return;
   }

   pno atual_aluno = alunos;

   while (atual_aluno != NULL) {

      if (atual_aluno->p == sala_mais) {
         printf("Nome: %s | Numero de aluno: %s\n", atual_aluno->nome, atual_aluno->num);
      }

      atual_aluno = atual_aluno->prox;
   }

}

