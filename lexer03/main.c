#include <stdio.h>
#include <string.h>
#include <ctype.h> 

typedef enum {
    Mais,
    Menos,
    Multiplicacao,
    Divisao,
    Potenciacao,
    Inteiro,
    Decimal,
    Indeterminado
} Token;


int tokenizar(const char* s, Token* tokens, int max_tokens) {
    int tokens_len = 0;
    while (*s && tokens_len < max_tokens) {
        if (isdigit(*s)) {  
            int num = 0;
            while (isdigit(*s)) { 
                num = num * 10 + (*s - '0');
                s++;
            }
            if (*s == '.') {
                s++;
                double frac = 0.1;
                double flt = num;
                while (isdigit(*s)) {
                    flt = flt + frac * (*s - '0');
                    frac /= 10;
                    s++;
                }
                tokens[tokens_len++] = Decimal;
            } else {
                tokens[tokens_len++] = Inteiro;
            }
        } else {  
            switch (*s) {
                case '+': tokens[tokens_len++] = Mais; break;
                case '-': tokens[tokens_len++] = Menos; break;
                case '*': {
                    
                    if (*(s+1) == '*') {
                        tokens[tokens_len++] = Potenciacao;
                        s++; 
                    } else {
                        tokens[tokens_len++] = Multiplicacao;
                    }
                    break; 
                }
                case '/': tokens[tokens_len++] = Divisao; break;
                case ' ': break;
                default: tokens[tokens_len++] = Indeterminado; break;
            }
            s++;
        }
    }
    return tokens_len;
}


int main(int argc, char* argv[]) {
    Token tokens[100];
    char input[100];
    char filename[10000];
    FILE *fp;


  
    if (argc != 2) {
        printf("Erro: use %s nome do arquivo\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");

  
    if (fp == NULL) {
        printf("Erro no arquivo.\n");
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
            case Potenciacao: printf("** Potenciação\n"); break;
            case Inteiro: printf("Inteiro\n"); break;
            case Decimal: printf("Decimal\n"); break;
            case Indeterminado: printf("Indeterminado\n"); break;
        }
    }
    fclose(fp);
    return 0;
}