// Gabriel Peclat dos Reis Costa, Eng. Informática
// 2025140643, ISEC - PT
#include <stdio.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} data;

int comparar(data d1, data d2);

int main() {

    data gabriel = {11, 5, 2005};
    data outro = {11, 5, 2005};

    int res = comparar(gabriel, outro);

    if (res < 0) {
        printf("gabriel é mais velho!\n");
    } else if (res > 0) {
        printf("gabriel é mais novo!\n");
    } else {
        printf("nasceram no mesmo dia!\n");
    }

    return 0;
}

int comparar(data d1, data d2) {

    if (d1.ano != d2. ano) return d1.ano - d2.ano;
    if (d1.mes != d2. mes) return d1.mes - d2.mes;
    return d1.dia - d2.dia;
}