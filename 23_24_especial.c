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

int main() {

   printf("estudasses!\n");

   return 0;
}

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