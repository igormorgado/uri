#include <stdio.h>

int main(void) {

    int N = 0;
    scanf("%d\n", &N);

    int M[100][100] = { 0 };
    int xi, xf, yi, yf;
    for (size_t n = 0; n < N; ++n)
    {
        scanf("%d %d %d %d\n", &xi, &xf, &yi, &yf);
        for(size_t i = xi; i < xf; ++i)
            for(size_t j = yi; j < yf; ++j)
                M[i][j] = 1;
    }

    int T = 0;
    for(size_t i = 0; i < 100; ++i)
        for(size_t j = 0; j < 100; ++j)
            T += M[i][j];

    printf("%d\n", T);

    return 0;
}
