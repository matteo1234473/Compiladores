#include "tinyexpr.h"
#include <stdio.h>

double fatorial(int n)
{
    if (n <= 1)
        return 1;
    else
        return n * fatorial(n - 1);
}

int main(int argc, char *argv[])
{
    const char *c = "fatorial(2)"; // mude aqui
    double r = te_interp(c, 0);
    printf("A expressão:\n\t%s\n resulta em:\n\t%f\n", c, r);
    return 0;
}