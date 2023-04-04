#include <stdio.h>
#include <string.h>

typedef enum {
    Mais,
    Menos,
    Multiplicacao,
    Divisao,
    Indeterminado
} Token;

int tokenizar(const char* s, Token* tokens, int max_tokens) {
    int tokens_len = 0;
    while (*s && tokens_len < max_tokens) {
        switch (*s) {
            case '+': tokens[tokens_len++] = Mais; break;
            case '-': tokens[tokens_len++] = Menos; break;
            case '*': tokens[tokens_len++] = Multiplicacao; break;
            case '/': tokens[tokens_len++] = Divisao; break;
            case ' ': break;
            default: tokens[tokens_len++] = Indeterminado; break;
        }
        s++;
    }
    return tokens_len;
}

int main() {
    Token tokens[100];
    char input[100];
    char filename[10000];
    FILE *fp;
    printf("Digite o nome do arquivo: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    fgets(input, sizeof(input), fp);
    input[strcspn(input, "\n")] = '\0';

    int tokens_len = tokenizar(input, tokens, 100);

    printf("Tokens encontrados:\n");
    for (int i = 0; i < tokens_len; i++) {
        switch (tokens[i]) {
            case Mais: printf("+ Soma\n"); break;
            case Menos: printf("- Subtração\n"); break;
            case Multiplicacao: printf("* Multiplicação\n"); break;
            case Divisao: printf("/ Divisão\n"); break;
            case Indeterminado: printf("Indeterminado\n"); break;
        }
    }

    fclose(fp);
    return 0;
}