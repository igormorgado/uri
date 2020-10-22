#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int X[200], Y[200];
int N, M;

double area(size_t A, size_t B, size_t C)
{
    return fabs(.5 * (X[A] * (Y[B] - Y[C]) + X[B] * (Y[C] - Y[A]) + X[C] * (Y[A] - Y[B])));
}

static int
inside(size_t A, size_t B, size_t C, size_t P)
{
    double a0 = area(A, B, C);
    double a1 = area(P, B, C);
    double a2 = area(A, P, C);
    double a3 = area(A, B, P);

    if (a0 == a1 + a2 + a3)
        return 1;           // Inside
    else
        return 0;           // Outside
}

int main(void) {
    while(scanf("%d %d\n", &N, &M) != EOF)
    {
        for(size_t i = 0; i < N+M; ++i)
            scanf("%d %d\n", &X[i], &Y[i]);

        int count = 0;
        int energy = 0;
        for(size_t i = 0; i < N; ++i)
        {
            for(size_t j = 0; j < i; ++j)
            {
                for(size_t k = 0 ; k < j; ++k)
                {
                    count = 0;
                    for(size_t l = N; l < N+M; ++l)
                    {
                        if(inside(i, j, k, l))
                        {
                            count++;
                        }
                    }
                    energy += count * count;
                }
            }
        }
        printf("%d\n", energy);
    }
    return 0;
}
