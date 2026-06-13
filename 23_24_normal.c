// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT
#include <stdio.h>
#include <string.h>

typedef struct a{ 
    char nome[100]; // Nome do autor 
    int idA;  // Identificador numérico do autor 
    int nLivros;  // Número de títulos no catálogo da livraria 
} autor; 
 
typedef struct b{ 
    char titulo[100], isbn[20]; // Título e isbn do livro 
    int idA;    // Identificador do autor 
    float preco;    // Preço do livro 
} livro;

typedef struct dadosUc   uc, *pUc; 
typedef struct dadosSala sala, *pSala; 
typedef struct {int dia, mes, ano;} data; 
 
struct dadosUc{ 
    char refUc[100];       //  Nome da Unidade Curricular 
    data dataEx;           //  Data do exame 
    pSala lista;           // Ponteiro para a lista de salas 
}; 
 
struct dadosSala{ 
    char refSala[100];     //  Nome da sala 
    int capacidade;        // Capacidade de sala 
    pSala prox; 
};

int main() {

   printf("estudasses!\n");

   return 0;
}

// 1. (ficheiros)
int f_livraria (char *f_texto, char *f_binario, int id_funcao) {

   FILE *f_bin = fopen(f_binario, "rb+"); if (!f_bin) return 0;

   int n_autores, i, j, id_maior_autor = -1, n_livros_maior_autor = -1;
   int n_livros;
   int empate = 0, autor_encontrado = 0;

   autor autor_atual;
   livro livro_atual;

   char autor_escolhido[100] = "";

   long offset_livros;

   fread(&n_autores, sizeof(int), 1, f_bin);

   for (i = 0; i < n_autores; i++) {

      fread(&autor_atual, sizeof(autor), 1, f_bin);

      if (autor_atual.idA == id_funcao && autor_encontrado == 0) {
         strcpy(autor_escolhido, autor_atual.nome);
         autor_encontrado = 1;
      }

      if (autor_atual.nLivros > n_livros_maior_autor) {
         n_livros_maior_autor = autor_atual.nLivros;
         id_maior_autor = autor_atual.idA;
         empate = 0;

      } else if (autor_atual.nLivros == n_livros_maior_autor) {
         empate = 1;
      } // temos o id e a quant de livros do mais famoso

   }

   fread(&n_livros, sizeof(int), 1, f_bin);

   for (j = 0; j < n_livros; j++) {

      fread(&livro_atual, sizeof(livro), 1, f_bin);

      if (livro_atual.idA == id_maior_autor && !empate) {
         livro_atual.preco *= 1.1;
         fseek(f_bin, -sizeof(livro), SEEK_CUR);
         fwrite(&livro_atual, sizeof(livro), 1, f_bin);
         fflush(f_bin);
      }
      
   }

   // aqui é finalizado o ponto i)

   // vamos começar o ponto ii)

   FILE *f_txt = fopen(f_texto, "w");
   if (!f_txt) {
      fclose(f_bin);
      return 0;
   }

   int n_livros_id = 0;

   fseek(f_bin, 0, SEEK_SET); // estamos no começo
   fseek(f_bin, sizeof(int), SEEK_CUR); // estamos no primeiro autor
   fseek(f_bin, sizeof(autor) * n_autores, SEEK_CUR); // estamos no numero de livros
   fseek(f_bin, sizeof(int), SEEK_CUR); // estamos no primeiro livro

   while (fread(&livro_atual, sizeof(livro), 1, f_bin) == 1) {

      if (livro_atual.idA == id_funcao) {

         fprintf(f_txt, "%s - %s, %s\n", livro_atual.isbn, livro_atual.titulo, autor_escolhido);
         n_livros_id++;

      }
      
   }

   if (!autor_encontrado) {
      fprintf(f_txt, "Autor Inexistente");
   }

   fclose(f_txt);
   fclose(f_bin);
   return 1;
}

// 2. (listas ligadas)
void mostrar_uc (pUc cadeiras, int tam, char *nome_sala) {

   pSala atual_sala = NULL;
   int i;

   for (i = 0; i < tam; i++) {

      atual_sala = cadeiras[i].lista;

      while (atual_sala != NULL) {

         if (strcmp(atual_sala->refSala, nome_sala) == 0) {
            printf("%s\n", cadeiras[i].refUc);
            break;
         }

         atual_sala = atual_sala->prox;
      }
      
   }
   
}


