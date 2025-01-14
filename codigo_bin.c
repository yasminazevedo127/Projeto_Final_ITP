#include <stdlib.h>
#include <stdio.h>
#include "codigo_bin.h"

// Variáveis globais para controle dos índices de leitura do código de barras L e R
int cont_L = INICIO_L;
int cont_R = INICIO_R;

// Constantes para os padrões de código de barras L e R (representando os padrões binários para os dígitos 0 a 9)
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

// Função para preencher os bits padrão do código de barras (L/R), com valores fixos.
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

// Função genérica para preencher o código com os valores dos padrões L ou R.
// Recebe o vetor de código, o contador de posição e o padrão a ser copiado.
void preencherCodigo(int *code, int *count, const int padrao[7]) {
    for (int i = 0; i < 7; i++) {
        code[*count + i] = padrao[i]; // Preenche a posição do código com o valor do padrão.
    }
    *count += 7; // Atualiza o contador para a próxima posição.
}

// Função para preencher o código de barras utilizando o padrão L (para os 4 primeiros dígitos).
void conversor_L_code(int *code, int num, int *cont_L) {
    if (num >= 0 && num <= 9) {
        preencherCodigo(code, cont_L, L_CODE[num]); // Preenche com o padrão L correspondente.
    }
}

// Função para preencher o código de barras utilizando o padrão R (para os 4 últimos dígitos).
void conversor_R_code(int *code, int num, int *cont_R) {
    if (num >= 0 && num <= 9) {
        preencherCodigo(code, cont_R, R_CODE[num]); // Preenche com o padrão R correspondente.
    }
}

// Função para converter os valores binários do código de barras EAN-8 para base 10.
// Recebe a matriz de strings com os dígitos binários e retorna um vetor com os valores decimais correspondentes.
int* converter_binario_base10(char** matriz_recebida) {

    int *digitos_codigo_barras = (int*)malloc(8 * sizeof(int));

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
        "1110100"  //9R
    };

    for(int i = 0; i < 4; i++) { // converte os primeiros 4 dígitos
        matriz_recebida[i][strcspn(matriz_recebida[i], "\n")] = '\0';
        for(int j = 0; j < 10; j++) {
            if(strcmp(matriz_recebida[i], matriz_base[j]) == 0) {
                digitos_codigo_barras[i] = j;
            }
        }
    }

    for(int i = 4; i < 8; i++) { // converte os últimos 4 dígitos
        matriz_recebida[i][strcspn(matriz_recebida[i], "\n")] = '\0';
        for(int j = 10; j < 20; j++) {
            if(strcmp(matriz_recebida[i], matriz_base[j]) == 0) {
                digitos_codigo_barras[i] = j - 10;
            }
        }
    }

    return digitos_codigo_barras;
}