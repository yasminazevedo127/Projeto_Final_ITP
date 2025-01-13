#include <stdlib.h>
#include <stdio.h>
#include "codigo_bin.h"

int cont_L = INICIO_L;
int cont_R = INICIO_R;

#include <stdio.h>

// Constantes para os padrões de código L e R
const int L_CODE[10][7] = {
    {0, 0, 0, 1, 1, 0, 1}, // 0
    {0, 0, 1, 1, 0, 0, 1}, // 1
    {0, 0, 1, 0, 0, 1, 1}, // 2
    {0, 1, 1, 1, 1, 0, 0}, // 3
    {0, 1, 0, 0, 0, 1, 1}, // 4
    {0, 1, 1, 0, 0, 0, 1}, // 5
    {0, 1, 0, 1, 1, 1, 1}, // 6
    {0, 1, 1, 1, 0, 1, 1}, // 7
    {0, 1, 1, 0, 1, 1, 1}, // 8
    {0, 0, 0, 1, 0, 1, 1}  // 9
};

const int R_CODE[10][7] = {
    {1, 1, 1, 0, 0, 1, 0}, // 0
    {1, 1, 0, 0, 1, 1, 0}, // 1
    {1, 1, 0, 1, 1, 0, 0}, // 2
    {1, 0, 0, 0, 0, 1, 1}, // 3
    {1, 0, 1, 1, 1, 0, 0}, // 4
    {1, 0, 0, 1, 1, 1, 0}, // 5
    {1, 0, 1, 0, 0, 0, 0}, // 6
    {1, 0, 0, 0, 1, 0, 0}, // 7
    {1, 0, 0, 1, 0, 0, 0}, // 8
    {1, 1, 1, 0, 1, 0, 0}  // 9
};

// Função para preencher bits padrão
void bits_padrao(int *vetor) {
    vetor[0] = 1;
    vetor[1] = 0;
    vetor[2] = 1;
    vetor[31] = 0;
    vetor[32] = 1;
    vetor[33] = 0;
    vetor[34] = 1;
    vetor[35] = 0;
    vetor[64] = 1;
    vetor[65] = 0;
    vetor[66] = 1;
}

// Função genérica para preencher o código
void preencherCodigo(int *codigo, int *contador, const int padrao[7]) {
    for (int i = 0; i < 7; i++) {
        codigo[*contador + i] = padrao[i];
    }
    *contador += 7;
}

// Função para o L-Code
void conversor_L_code(int *codigo, int num, int *cont_L) {
    if (num >= 0 && num <= 9) {
        preencherCodigo(codigo, cont_L, L_CODE[num]);
    }
}

// Função para o R-Code
void conversor_R_code(int *codigo, int num, int *cont_R) {
    if (num >= 0 && num <= 9) {
        preencherCodigo(codigo, cont_R, R_CODE[num]);
    }
}


//convertendo de binario ean-8 para base10:


int* converter_binario_base10(char** matriz_recebida){

    int *numerocb = (int*)malloc(8 * sizeof(int));

    char* matriz_base[] = {
        "0001101", //0L
        "0011001", //1L
        "0010011", //2L
        "0111101", //3L
        "0100011", //4L
        "0110001", //5L
        "0101111", //6L
        "0111011", //7L
        "0110111", //8L
        "0001011", //9L
        "1110010", //0R
        "1100110", //1R
        "1101100", //2R
        "1000010", //3R
        "1011100", //4R
        "1001110", //5R
        "1010000", //6R
        "1000100", //7R
        "1001000", //8R
        "1110100" //9R
    };

    for(int i = 0;i<4;i++){ //converte os primeiros 4 digitos

        matriz_recebida[i][strcspn(matriz_recebida[i], "\n")] = '\0';
        for(int j = 0; j<10;j++){
            if(strcmp(matriz_recebida[i], matriz_base[j])==0){
                numerocb[i] = j;
            }
        }
    }

    for(int i = 4;i<8;i++){ //converte os ultimos 4 digitos

    matriz_recebida[i][strcspn(matriz_recebida[i], "\n")] = '\0';
        for(int j = 10; j<20;j++){
            if(strcmp(matriz_recebida[i], matriz_base[j])==0){
                numerocb[i] = j-10;
            }
        }
    }
    
    return numerocb;

}