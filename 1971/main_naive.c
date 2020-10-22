#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

int neq(size_t A, size_t B)
{
    return (!eq(A, B));
}

int check(size_t A, size_t B, size_t C)
{
    const size_t P = 4;
    if(eq(A, B) || eq(A, C) || eq(A, P) || eq(B, C) || eq(B, P) || eq(C, P))
        return 1;

    double w1 = (X[A] * (Y[C] - Y[A]) + (Y[P] - Y[A]) * (X[C] - X[A]) - X[P] * (Y[C] - Y[A]))
                / ((Y[B] - Y[A]) * (X[C] - X[A]) - (X[B] - X[A]) * (Y[A] - Y[C]));

    double w2 = (Y[P] - Y[A] - w1 * (Y[B] - Y[A])) / (Y[C] - Y[A]);

    if(w1 >= 0 && w2 >= 0 && (w1+w2) <= 1)
        return 0;           // Inside
    else
        return 1;           // Outside
}

int main(void) {

    for(size_t i = 0; i < 5; ++i)
        scanf("%d %d\n", &X[i], &Y[i]);

    for(size_t i = 0; i < 4; ++i)
        for(size_t j = i+1; j < 4; ++j)
            for(size_t k = j+1; k < 4; ++k)
               if(check(i, j, k))
                   libre();

    jailed();

    return 0;
}
