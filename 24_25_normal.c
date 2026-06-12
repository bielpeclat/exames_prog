#include <stdio.h>

typedef struct dados item; 
 
struct dados{ 
    int id;                 // Identificador numérico único 
    char nome[100];         // Nome do item 
    int qtd;                // Quantidade em stock 
    int minstock;           // Quantidade mínima para gerar alerta de stock 
}; 

int main () {
    printf("gabriel peclat\n");
    return 0;
}

// primeiro exercicio dos ficheiros
int f_receita(char *f_stock_b, char *f_receita_t) {

    FILE *f_txt = fopen(f_receita_t, "r");
    FILE *f_bin = fopen(f_stock_b, "rb+"); 

    if (f_bin == NULL || f_txt == NULL) {
        if (f_bin) fclose(f_bin);
        if (f_txt) fclose(f_txt);
    } return 0;
    
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







