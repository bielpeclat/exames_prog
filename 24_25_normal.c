// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT
#include <stdio.h>

typedef struct dados item; 
 
struct dados{ 
    int id;                 // Identificador numérico único 
    char nome[100];         // Nome do item 
    int qtd;                // Quantidade em stock 
    int minstock;           // Quantidade mínima para gerar alerta de stock 
}; 

typedef struct projeto proj, *pproj; 
typedef struct pessoa gestor, *pgest; 
 
struct pessoa{ 
    int id;   // Identificador único do gestor 
    char nome[100];  // Nome do gestor 
    int total;   // Número de projetos que está a gerir 
}; 
 
struct projeto{ 
    int id;     // Identificador único do projeto 
    struct {int dia, mes, ano;} inicio;  // Data de início do projeto 
    pgest p;    // Ponteiro para o gestor deste projeto 
    pproj prox; 
};

int main() {

    printf("estudasses!\n");

    return 0;
}


// ex.1 (ficheiros) - esse exercicio em especifico esta mais propenso para conter erros, pq foi o primeiro que fiz, nao estava sendo muito rigoroso, mas, todos os outros *provavelmente n vao conter nenhum erro
int f_receita(char *f_stock_b, char *f_receita_t) {

    FILE *f_txt = fopen(f_receita_t, "r");
    FILE *f_bin = fopen(f_stock_b, "rb+"); 

    if (f_bin == NULL || f_txt == NULL) {
        if (f_bin) fclose(f_bin);
        if (f_txt) fclose(f_txt);
        return 0;
    } 
    
    item atual, item_lido;
    char comentario[256];

    while (fscanf(f_txt, " %d : %99[^:] : %d : %255[^\n]", &atual.id, atual.nome, &atual.qtd, comentario) == 4) {

        do {

            fread(&item_lido, sizeof(item), 1, f_bin);
        
        } while (item_lido.id != atual.id);
        //aqui o nosso item_lido aponta para o local certo

        item_lido.qtd -= atual.qtd;

        fseek(f_bin, -sizeof(item), SEEK_CUR);
        fwrite(&item_lido, sizeof(item), 1, f_bin);

        if (item_lido.qtd < item_lido.minstock) {
            printf("O ingrediente %s com ID %d tem stock abaixo do mínimo\n", atual.nome, atual.id);
        }

        rewind(f_bin);
        
    }

    fclose(f_txt);
    fclose(f_bin);
    return 1;
}

//ex.2 (listas ligadas)
void projetos_gestor (int id_gestor, pproj projetos, pgest pessoas, int tam) {

    pproj antigo = NULL, recente = NULL;
    pgest gestor_esc = NULL;
    int i, gestor_encontrado = 0, primeiro = 1;

    for (i = 0; i < tam; i++) {

        if (pessoas[i].id == id_gestor) {
            gestor_esc = &pessoas[i];
            gestor_encontrado = 1;
            break;
        }
        
    }
    if (gestor_encontrado == 0 || gestor_esc->total < 2) {
        printf("Não aplicável");
        return;
    }

    // aqui ja estamos no cenario ideal
    pproj atual_lista = NULL;
    atual_lista = projetos;

    while (atual_lista != NULL) {

        if (atual_lista->p != NULL && atual_lista->p->id == gestor_esc->id) {

            if (primeiro == 1) {

                antigo = atual_lista;
                recente = atual_lista;
                primeiro = 0;
                
            } else { // ainda vou alterar isso para por uma funcao de comparacao de datas, mas, não agora... 3 ifs encadeados... xd
                if ((atual_lista->inicio.ano < antigo->inicio.ano) || 
                    (atual_lista->inicio.ano == antigo->inicio.ano && atual_lista->inicio.mes < antigo->inicio.mes) || 
                    (atual_lista->inicio.ano == antigo->inicio.ano && atual_lista->inicio.mes == antigo->inicio.mes && atual_lista->inicio.dia < antigo->inicio.dia)) {

                        antigo = atual_lista;

                    } else if ((atual_lista->inicio.ano > recente->inicio.ano) || 
                                (atual_lista->inicio.ano == recente->inicio.ano && atual_lista->inicio.mes > recente->inicio.mes) || 
                                (atual_lista->inicio.ano == recente->inicio.ano && atual_lista->inicio.mes == recente->inicio.mes && atual_lista->inicio.dia > recente->inicio.dia)) {
                        recente = atual_lista;
                    }
            }
            
        }


        atual_lista = atual_lista->prox;
    }
    
    printf("Data de inicio do projeto mais antigo: %2d/%2d/%4d\n", antigo->inicio.dia,antigo->inicio.mes, antigo->inicio.ano);
    printf("Data de inicio do projeto mais recente: %2d/%2d/%4d\n", recente->inicio.dia,recente->inicio.mes, recente->inicio.ano);
    
}




