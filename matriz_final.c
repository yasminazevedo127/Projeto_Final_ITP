#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "matriz_final.h"
#include "validar_codigo.h"

int** dimensionar(int linhas, int colunas){
    int**m;
    m = calloc(linhas, sizeof(int*));

    for(int i = 0; i < linhas; ++i){
        m[i] = calloc(colunas, sizeof(int));
    }

    return m;
}

//função para montar a matriz ajustada de acordo com a largura de cada área e baseada no vetor_ean
void montarMatriz(int** matriz, int* vetor, int borda, int largura_area, int linhas, int colunas){

    int i = borda;
    int x = 0;

    while(i < (colunas - borda)){

        int cont = 0;
        while(cont < largura_area){
            matriz[borda][i] = vetor[x];
            cont = cont + 1;
            i = i + 1;
        }
        x = x + 1;
    }
    for(int linhaAtual = 0; linhaAtual < linhas; ++linhaAtual){
        if(linhaAtual > borda && linhaAtual < linhas - borda){
            matriz[linhaAtual] = matriz[borda];
        }
    }

    free(vetor);
}

// Função que printa a matriz final no arquivo PBM
void print(int** matriz, int linhas, int colunas, char image_name[]) {

    setlocale(LC_ALL, "");
    char confirmacao;
    FILE *saida_pbm;

    saida_pbm = fopen(image_name, "r");

    if (saida_pbm == NULL) {
        saida_pbm = fopen(image_name, "w+");
        fprintf(saida_pbm, "P1\n");
        fprintf(saida_pbm, "%d %d\n", colunas, linhas);

        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                fprintf(saida_pbm, "%d", matriz[i][j]);
            }
            fprintf(saida_pbm, "\n");
        }
        fclose(saida_pbm);

        free(matriz);

    } else {
        printf("O arquivo a ser criado já existe. Deseja sobrescrevê-lo (s/n)?\n");
        scanf(" %c", &confirmacao);
    }

    if (confirmacao == 's') {
        saida_pbm = fopen(image_name, "w+");
        fprintf(saida_pbm, "P1\n");
        fprintf(saida_pbm, "%d %d\n", colunas, linhas);

        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                fprintf(saida_pbm, "%d", matriz[i][j]);
            }
            fprintf(saida_pbm, "\n");
        }
        fclose(saida_pbm);

        free(matriz);

    } else if (confirmacao == 'n') {
        printf("Arquivo resultante já existe!\n");
    }
}

//transformar codigo de barras em matriz

//TODO: criar um vetor com a linha espacamento_superior+1, a partir da coluna espacamento_superior+1 até a coluna espacamento_superior-1
//a partir da coluna espacamento_superior+1 checar quantos 1 seguidos, para saber a area.

int calcular_area(int largura, int espace, FILE *arquivo){

    int area = 0;
    char linha[largura+1];  
    int linha_central = (altura / 2)+2;

    fseek(arquivo, linha_central * largura * sizeof(char), SEEK_SET);

    //pulando para a linha após o espacamento
    for(int i = 0; i<espace+1;i++){ 
        fgets(linha, sizeof(linha), arquivo);
    }

    fgets(linha, sizeof(linha), arquivo); //lê uma linha do código de 

    for (int i = 0; i < largura; i++) { //testando para ver se a linha sendo observada é a certa
        printf("%c", linha[i]);
    }
    printf("\n");  // Nova linha após a impressão de todos os elementos

    
    for (int i = espace; i < largura; i++) { //conta quantos 1s seguidos tem, para descobrir a area
            if (linha[i] == '1') {
                area++;  
            } else if (linha[i] == '0'){
                break;
            }
    }
    
    return area;
}

void processar_codigo(char** vetores, FILE* arquivo, int start, int end, int indice_inicial, int area, int* cont) {
    for (int i = indice_inicial; i < indice_inicial + 4; i++) {
        int j = 0;
        while (*cont < end && j < 7) {
            char c = fgetc(arquivo);
            if (*cont > start && (*cont - start- 1) % area == 0) {
                vetores[i][j++] = c;
            }
            (*cont)++;
        }
        vetores[i][7] = '\0'; // Adicionar terminador de string
    }
}

char** criar_vetores(int largura, int area, int espace, FILE *arquivo){

    char linha[largura*2];
    char **vetores = (char **)malloc(8 * sizeof(char *)); //matriz de strings, 8 linhas de 7 caracteres
    for (int i = 0; i < 8; i++) {
        vetores[i] = (char *)malloc(8 * sizeof(char)); //7 caracteres + 1 para \0
    }
    //pulando para a linha após o espacamento
    for(int i = -2; i<espace+1;i++){ //i=-2 para pular as duas primeiras linhas de cabeçalho
        fgets(linha, sizeof(linha), arquivo);
    }
    
     // Definir limites de leitura baseados nos parâmetros fornecidos
    int start_L = espace + (area * 3);                     // Após o marcador inicial
    int start_R = start_L + (area * 4 * 7) + (area * 5);   // Após o marcador central
    int end_R = start_R + (area * 4 * 8);                  // Após o marcador final
    int end_L = start_L + (area * 4 * 4);                  // Parte L completa
    int cont = 0;


    // Processar as partes L e R do código de barras
    processar_codigo(vetores, arquivo, start_L, end_L, 0, area, &cont); // Parte L
    processar_codigo(vetores, arquivo, start_R, end_R, 4, area, &cont); // Parte R

    return vetores;
}
