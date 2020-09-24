#include <stdio.h>
#include <math.h>

#define R 1.720477400588966920835787277611

int main(void) {
    int C, N;

    scanf("%d\n", &C);
    for (size_t i = 0; i < C; ++i)
    {
        scanf("%d\n", &N);
        printf("%.3f\n", N*N*R);
    }
    return 0;
}
