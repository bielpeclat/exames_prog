// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT

#include <stdio.h>
#include <string.h>

typedef struct drone dr;
struct drone { 
    char id[20];      // identificador alfanumérico do drone 
    int entregas;     // número de entregas realizadas 
    float km;         // quilómetros percorridos 
    char eficiente;   // 'S' se eficiente, 'N' caso contrário 
}; 

typedef struct disciplina no, *pno; 
typedef struct pessoa aluno, *pAluno; 
 
struct pessoa{ 
    char nome[100];     // Nome do aluno 
    int num;            // Número do aluno    
    pno v[3];           // Ponteiros para as disciplinas a que está inscrito 
}; 
 
struct disciplina{ 
    char nome[100];     // Nome da disciplina 
    int id, conta;      // ID da disciplina e contador de alunos inscritos 
    pno prox; 
};

int main() {

   printf("estudasses!\n");

   return 0;
}

// ex. 1 (ficheiros)
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

// ex.2 (listas ligadas)
void mostra_alunos (pno cadeiras, pAluno alunos, int tam) {

   if (cadeiras == NULL || cadeiras->prox == NULL) {
      printf("Não aplicável");
      return;
   } 

   // aqui, a lista tem obrigatoriamente dois ou mais nós

   int i, j;

   pno penultimo = NULL;
   penultimo = cadeiras;

   while (penultimo->prox->prox != NULL) {
      penultimo = penultimo->prox;
   } // aqui ja temos um ponteiro para o penultimo nó/ disciplina

   // vamos iterar sobre os alunos

   for (i = 0; i < tam; i++) {

      for (j = 0; j < 3; j++) {

         if (alunos[i].v[j] == NULL) continue;

         if (alunos[i].v[j] == penultimo) {
            printf("Aluno: %s | Nº aluno: %d\n", alunos[i].nome, alunos[i].num);
         }
         
      }
      
   }
   
}

// ex. 3 (listas ligadas)
pno add_disciplina (char *nome, int id, pno lista, pAluno alunos, int tam) {

   // primeiro, vamos add uma nova disciplina a lista (insercao ordenada)
   pno atual_lista = lista;
   int i, j, n_disc_local;

   pno no_novo = malloc(sizeof(no)); // alocando memoria para 1 disciplina
   if (!no_novo) return lista;

   // atribuicao dos campos da nova disciplina
   strcpy(no_novo->nome, nome);        // nome
   no_novo->id = id;                   // id
   no_novo->conta = 0;                 // nenhum aluno ainda

   // insercao no (inicio) vs (meio ou fim)

   // vamos comecar com insercao no inicio ou em lista vazia
   if (lista == NULL || id < atual_lista->id) {
      no_novo->prox = atual_lista;
      lista = no_novo;
   } 
   
   // insercao no meio ou fim
   else {

      if (id == atual_lista->id) {
         free(no_novo);
         return lista;
      }

      while (atual_lista->prox != NULL && atual_lista->prox->id < id) {
         atual_lista = atual_lista->prox;
      } 
      // aqui estamos na posicao correta

      if (atual_lista->prox != NULL && atual_lista->prox->id == id) {
         free(no_novo);
         return lista;
      }

      no_novo->prox = atual_lista->prox;
      atual_lista->prox = no_novo;
   } // aqui ja inserimos a disciplina

   // agora precisamos inserir os alunos com n_disc < 2 para a nova disciplina
   for (i = 0; i < tam; i++) {                  // iterar sobre os alunos

      n_disc_local = 0;
      for(j = 0; j < 3; j++) {                  // iterar sobre as disciplinas

         if (alunos[i].v[j] != NULL) {
            n_disc_local++;
         }
         
      }
      
      if (n_disc_local < 2) {
         alunos[i].v[n_disc_local] = no_novo;
         no_novo->conta++;
      }
      
   }
   
   return lista;
}

// 4. recursividade
// resposta: 2366

