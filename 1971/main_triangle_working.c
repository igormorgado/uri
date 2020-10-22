#include <stdio.h>
#include <stdlib.h>

int X[5], Y[5];

void libre()
{
    printf(" O>\n<| \n/ >\n");          // Livre
    exit(0);
}

void jailed()
{
    printf("\\O/\n | \n/ \\\n");        // Preso
    exit(0);
}

int eq(size_t A, size_t B)
{
    return ((X[A] == X[B]) && (Y[A] == Y[B]));
}

// Return 0 if colinear
int colinear(size_t A, size_t B, size_t C)
{
    return  X[A] * (Y[B] - Y[C]) + X[B] * (Y[C] - Y[A]) + X[C] * (Y[A] - Y[B]);
}

int inside(size_t A, size_t B, size_t C)
{
    const size_t P = 4;

    double w1n = (X[A] * (Y[C] - Y[A]) + (Y[P] - Y[A]) * (X[C] - X[A]) - X[P] * (Y[C] - Y[A]));
    double w1d = ((Y[B] - Y[A]) * (X[C] - X[A]) - (X[B] - X[A]) * (Y[C] - Y[A]));
    double w1 = w1n / w1d;

    double w2n = (Y[P] - Y[A] - w1 * (Y[B] - Y[A]));
    double w2d = (Y[C] - Y[A]);
    double w2 = w2n / w2d;

    if(w1 >= 0 && w2 >= 0 && (w1+w2) <= 1)
        return 1;           // Inside
    else
        return 0;           // Outside
}

int main(void) {

    for(size_t i = 0; i < 5; ++i)
        scanf("%d %d\n", &X[i], &Y[i]);

    // Dos corpos nao podem ocupar o mesmo lugar no espaço.
    for(size_t i = 0; i < 4; ++i)
        for(size_t j = i+1; j < 4; ++j)
            if(eq(i, j))
                libre();

    // Policiais não estão todos sobre uma mesma reta
    if((colinear(0, 1, 2) == 0) && (colinear(0, 1, 3) == 0))
        libre();

    // Check the triangles
    for(size_t i = 0; i < 4; ++i)
        for(size_t j = i+1; j < 4; ++j)
            for(size_t k = j+1; k < 4; ++k)
                if(inside(i, j, k) == 1)
                    jailed();

    libre();

    return 0;
}
