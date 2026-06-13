// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT
#include <stdio.h>

typedef struct Artigo artigo; 
typedef struct Data data; 
 
struct Data{ int hora, minuto, dia, mes, ano;}; 
 
struct Artigo{ 
    int cp;   // Código numérico único do artigo 
    int np;   // Quantidade do artigo existente em stock 
    float preco;  // Preço unitário (em euros) 
    data venda;   // Data em que foi realizada a última venda 
};

typedef struct {int mes, ano;} data; 
typedef struct gestor no, *pno; 
 
struct gestor{ 
    int idG; 
    struct emCurso *v1; 
    struct completo *v2; 
    int totV1, totV2; 
    pno prox; 
}; 
 
struct emCurso{ 
    int id;  
    data inicio; 
}; 
 
struct completo{ 
    int id; 
    data final; 
    int duracao; 
};

int main() {

   printf("estudasses!\n");

   return 0;
}

// ex.1 (ficheiros)
float f_vendas (char *f_texto, char *f_binario, data agora) {

   FILE *f_bin = fopen(f_binario, "rb+"); if (!f_bin) return -1;
   FILE *f_txt = fopen(f_texto, "r"); 
   if (!f_txt) {
      fclose(f_bin);
      return -1;
   }

   int n_artigos, codigo_encomenda, quant_encomenda, i;
   artigo atual;
   long pos_artigos;
   float total_vendas = 0;

   fread(&n_artigos, sizeof(int), 1, f_bin);
   // n_artigos vale 5
   pos_artigos = ftell(f_bin);

   while (fscanf(f_txt, " %d %d ", &codigo_encomenda, &quant_encomenda) == 2) {

      fseek(f_bin, pos_artigos, SEEK_SET); // vamos para o primeiro artigo
      i = 0;
      
      do {

         fread(&atual, sizeof(artigo), 1, f_bin);

         i++;

      } while (i < n_artigos && atual.cp != codigo_encomenda);

      if (atual.cp != codigo_encomenda) {
         //o artigo nao existe
         continue;
      }

      // atualizar stock
      if (quant_encomenda <= atual.np) {
         total_vendas += quant_encomenda * atual.preco;
         atual.np -= quant_encomenda;
      } else {
         total_vendas += atual.np * atual.preco;
         atual.np = 0;
      }

      //alterar data
      atual.venda = agora;

      fseek(f_bin, -sizeof(artigo), SEEK_CUR);
      fwrite(&atual, sizeof(artigo), 1, f_bin);
      
   }

   fclose(f_txt);
   fclose(f_bin);

   return total_vendas;
}

// ex.2 (listas ligadas)
// imprimir o estado de um projeto passado por parametro (concluido ou nao concluido)
// e o identificador do gestor
void mostra_projeto (pno gestores, int id_proj) {

   int encontrado = 0, i, j;

   pno atual_gestor = NULL;
   atual_gestor = gestores;

   struct emCurso *atual_emCurso = NULL;
   struct completo *atual_completo = NULL;

   while (atual_gestor != NULL) { // aqui iteramos sobre os gestores

      if (encontrado == 1) break;

      // agora precisamos iterar sobre os emCurso e os completos
      
      // vamos começar pelos emCurso
      if (atual_gestor->v1 != NULL && encontrado == 0) {

         atual_emCurso = atual_gestor->v1;

         for (i = 0; i < atual_gestor->totV1; i++) { // procura no emCurso

            if (atual_emCurso[i].id > id_proj) break; // o id_proj nao esta aqui
            
            if (atual_emCurso[i].id == id_proj) {
               printf("Projeto: %d | Estado: %s | ID do gestor: %d\n", atual_emCurso[i].id, "Em curso", atual_gestor->idG);
               encontrado = 1;
               break;
            }
         }
         
      }

      // agora vamos procurar nos projetos ja finalizados
      if (atual_gestor->v2 != NULL && encontrado == 0) {

         atual_completo = atual_gestor->v2;

         for (i = 0; i < atual_gestor->totV2; i++) {

            if (atual_completo[i].id > id_proj) break; // o id_proj nao esta aqui

            if (atual_completo[i].id == id_proj) {
               printf("Projeto: %d | Estado: %s | ID do gestor: %d\n", atual_completo[i].id, "Concluido", atual_gestor->idG);
               encontrado = 1;
               break;
            }
         }
      }
      atual_gestor = atual_gestor->prox;
   }
   if (encontrado == 0) {
         printf("Inexistente");
   }
} // tudo certo logo na primeira tentativa :)



