// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT

// 1. (pergunta sobre ficheiros)
/*

#include <stdio.h>
typedef struct drone dr;
struct drone { 
    char id[20];      // identificador alfanumérico do drone 
    int entregas;     // número de entregas realizadas 
    float km;         // quilómetros percorridos 
    char eficiente;   // 'S' se eficiente, 'N' caso contrário 
}; 

int main() {

   printf("gabriel peclat\n2025140643, isec, pt");

   return 0;
}

int f_drones(char *f_texto, char *f_binario) {

   FILE *f_txt = fopen(f_texto, "r"); if (!f_txt) return 0;
   int n_drones = 0, n_entregas = 0;
   float km_global = 0, media;
   dr atual;

   while (fscanf(f_txt, " %19s %d %f ", atual.id, &atual.entregas, &atual.km) == 3) {
      n_drones++;
      n_entregas += atual.entregas;
      km_global += atual.km;
   } // chegamos aqui com os dados para calcular a eficiencia média


   if (n_entregas == 0) {
         fclose(f_txt);
         return 0;
      }

   media = km_global / n_entregas;

   rewind(f_txt); // voltamos o cursos de texto para o inicio do ficheiro de texto

   FILE *f_bin = fopen(f_binario, "wb");
   if (!f_bin) {
      fclose(f_txt);
      return 0;
   }
   
   float media_local;

   fwrite(&n_drones, sizeof(int), 1, f_bin);

   while (fscanf(f_txt, " %19s %d %f ", atual.id, &atual.entregas, &atual.km) == 3) {

      if (atual.entregas == 0) { // evitar divisao por 0
         fclose(f_txt);
         fclose(f_bin);
         return 0;
      }

      media_local = atual.km / atual.entregas;

      if (media_local < media) {
         atual.eficiente = 'S';
      } else {
         atual.eficiente = 'N';
      }

      fwrite(&atual, sizeof(dr), 1, f_bin);
   }
   fclose(f_txt);
   fclose(f_bin);
   return 1;
}

*/



