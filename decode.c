#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"");
    if (argc != 2) {
        printf("\nNenhum arquivo foi escolhido!");
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) {
        printf("\nO arquivo com o nome informado não existe!");
        return 1;
    }

    // Verificar a primeira linha e segunda linha do arquivo
    if (!verificar_primeira_linha(arquivo) || !verificar_segunda_linha(arquivo)) {
        printf("Arquivo inválido.\n");
        fclose(arquivo);
        return 1;
    }

    // Reabrir o arquivo para checar o espaçamento superior
    fseek(arquivo, 0, SEEK_SET);  // Voltar para o início do arquivo