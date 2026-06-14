// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT
#include <stdio.h>
#include <string.h>

typedef struct { 
   int d, m, a; 
} data;

typedef struct Farmaco { 
    int id; 
    char designacao[100]; 
    char nome[100]; 
    data terminouProducao; 
} farmaco;

typedef struct sala no, *pno; 
struct sala{ 
    char id[10]; 
    int total; 
    pno prox; 
}; 
 
typedef struct pessoa{ 
    char nome[100], num[20]; 
    pno p; 
} aluno;

int main() {

   printf("estudasses!\n");

   return 0;
}

// o ficheiro de texto tem os medicamentos produzidos pela empresa
// passar para o f_bin os farmacos que deixaram de ser produzidos

// ex. 1 (ficheiros)
int f_farmacos (char *f_texto, char *f_binario, data hoje) {

   FILE *f_txt = fopen(f_texto, "r"); if (!f_txt) return -1;
   FILE *f_bin = fopen(f_binario, "wb");
   if (!f_bin) {
      fclose(f_txt);
      return -1;
   }
   FILE *f_aux = fopen("f_auxiliar.txt", "w");
   if (!f_aux) {
      fclose(f_txt);
      fclose(f_bin);
      return -1;
   }

   farmaco atual;
   char em_prod[10];
   int n_transferidos = 0;

   while (fscanf(f_txt, " %*[^:]: %99[^\n]"
                        " %*[^:]: %99[^\n]"
                        " %*[^:]: %d"
                        " %*[^:]: %9s",
         atual.designacao, atual.nome, &atual.id, em_prod) == 4) {

            if (strcmp(em_prod, "nao") == 0) {
               atual.terminouProducao = hoje;
               fwrite(&atual, sizeof(farmaco), 1, f_bin);
               n_transferidos++;
            }  else if (strcmp(em_prod, "sim") == 0){
               fprintf(f_aux, "Designação: %s\nNome comercial: %s\nId: %d\nEm produção: %s\n\n", atual.designacao, atual.nome, atual.id, em_prod);
            }

            
   }

   fclose(f_aux);
   fclose(f_txt);
   fclose(f_bin);

   remove(f_texto);
   rename("f_auxiliar.txt", f_texto);
   
   return n_transferidos; // vamos mudar isso no futuro
}

// ex. 2 (listas ligadas) 
int trocar_alunos (char *aluno1, char *aluno2, pno salas, aluno *vetor, int tam) {

   aluno *pAluno1 = NULL;
   aluno *pAluno2 = NULL;
   pno aux = NULL;

   int i;

   for (i = 0; i < tam; i++) { // iterar sobre todos os alunos

      if (strcmp(vetor[i].nome, aluno1) == 0) {
         pAluno1 = &vetor[i];

      } else if (strcmp(vetor[i].nome, aluno2) == 0) {
         pAluno2 = &vetor[i];
      }

      if (pAluno1 && pAluno2) break; // early exit
      
   }

   // vamos verificar se conseguimos encontrar ambos
   if (!pAluno1 || !pAluno2) {
      return -1;
   }

   aux = pAluno1->p;
   pAluno1->p = pAluno2->p;
   pAluno2->p = aux;

   return 1;
} // mais um que acertei tudo de primeira :)

// ex. 3 (listas ligadas 2)


