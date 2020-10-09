#include <stdio.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int main(void) {

    int N = 0;
    int T = 1;
    while(scanf("%d\n", &N), N != 0)
    {

        int X, Y, U, V;
        int MX = -10000;
        int MY = 10000;
        int MU = 10000;
        int MV = -10000;
        for (size_t i = 0; i < N; ++i)
        {
            scanf("%d %d %d %d\n", &X, &Y, &U, &V);
            MX = max(MX, X);
            MY = min(MY, Y);
            MU = min(MU, U);
            MV = max(MV, V);
        }

        printf("Teste %d\n", T++);
        if (!((MX < MU) && (MV < MY)))
            printf("nenhum\n\n");
        else
            printf("%d %d %d %d\n\n", MX, MY, MU, MV);
    }

    return 0;
}
