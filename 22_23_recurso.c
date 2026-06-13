// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT
#include <stdio.h>

typedef struct Artigo{ 
    char ref[10]; 
    int qtd; 
    float preco; 
} artigo;

int main() {

    printf("estudasses!\n");

    return 0;
}

int f_armazem (char *f_texto, char *f_binario, int limite) {

    FILE *f_bin = fopen(f_binario, "rb+"); if (!f_bin) return -1;

    float media_inicio;
    artigo atual;
    int n_produtos = 0;

    fread(&media_inicio, sizeof(float), 1, f_bin);
    media_inicio *= 1.1;

    fseek(f_bin, 0, SEEK_SET);
    fwrite(&media_inicio, sizeof(float), 1, f_bin);
    fseek(f_bin, 0, SEEK_CUR);
    //aqui ja atualizamos a media

    while (fread(&atual, sizeof(artigo), 1, f_bin) == 1) {
        atual.preco *= 1.1;
        fseek(f_bin, -sizeof(artigo), SEEK_CUR);
        fwrite(&atual, sizeof(artigo), 1, f_bin);
        fseek(f_bin, 0, SEEK_CUR);
    }

    // fim do ponto i) do enunciado

    // inicio do ponto ii)

    FILE *f_txt = fopen(f_texto, "w"); 
    if (!f_txt) {
        fclose(f_bin);
        return -1;
    }

    rewind(f_bin); // voltamos o pointer do f_bin para o inicio

    fread(&media_inicio, sizeof(float), 1, f_bin);

    while (fread(&atual, sizeof(artigo), 1, f_bin) == 1) {
        
        if (atual.qtd < limite) {
            fprintf(f_txt, "%s %d\n", atual.ref, atual.qtd);
            n_produtos++;
        }
        
    }

    fclose(f_txt);
    fclose(f_bin);
    return n_produtos;
}