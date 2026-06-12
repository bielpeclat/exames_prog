// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT
#include <stdio.h>

typedef struct a autor;
struct a{ 
    char nome[100]; // Nome do autor 
    int idA;  // Identificador numérico do autor 
    int nLivros;  // Número de títulos no catálogo da livraria 
};

int main() {

   printf("estudasses!\n");

   return 0;
}

// 1. (questão sobre ficheiros)
/*

int f_livraria (char *f_texto, char *f_binario) {

   FILE *f_bin = fopen(f_binario, "rb+"); // ler o id e depois alterar nLivros
   if (!f_bin) return 0;

   FILE *f_txt = fopen(f_texto, "r"); // ler os dados no f_texto
   if (!f_txt) {
      fclose(f_bin);
      return 0;
   }

   char nome_livro_txt[100];
   int id_txt;
   float preco_txt;

   int n_autores, i, n_livros_local;
   autor atual;



   fread(&n_autores, sizeof(int), 1, f_bin);

   for (i = 0; i < n_autores; i++) {

      fread(&atual, sizeof(autor), 1, f_bin);
      // aqui, vamos iterar sobre cada um dos autores do f_bin

      n_livros_local = 0; // entrar no while com a quant de livros a 0

      rewind(f_txt); // começar a ler os livros no inicio do ficheiro
      
      while (fscanf(f_txt, " %99[^#]# %d # %f ", nome_livro_txt, &id_txt, &preco_txt) == 3) {
         if (atual.idA == id_txt) {
            n_livros_local++;
         }

         //rewind(f_txt); aqui esta errado!
         
      } // aqui temos n_livros_local com o valor correto da quant de livros para por no f_bin

      if (n_livros_local != atual.nLivros) { // so vamos alterar se o valor estiver errado

         atual.nLivros = n_livros_local;
         
         fseek(f_bin, -sizeof(autor), SEEK_CUR);
         fwrite(&atual, sizeof(autor), 1, f_bin);
         fflush(f_bin);
      }

   }

   fclose(f_txt);
   fclose(f_bin);
   return 1;
}

*/



