#ifndef MATRIZ_FINAL_H_INCLUDED
#define MATRIZ_FINAL_H_INCLUDED

int** dimensionar(int linhas, int colunas);

void montarMatriz(int** matriz, int* vetor, int borda, int largura_area, int linhas, int colunas);

void print(int** matriz, int linhas, int colunas, char image_name[]);

int calcular_area(int largura, int espace, FILE *arquivo);

char** criar_vetores(int largura, int area, int espace, FILE *arquivo);

void processar_codigo(char** vetores, FILE* arquivo, int start, int end, int indice_inicial, int area, int* cont);

extern char **vetores;

#endif // MATRIZ_FINAL_H_INCLUDED