#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct painel
{
    char cor[51];
};

int min(int a, int b)
{
    return (a < b)? a : b;
}

int min3(int a, int b, int c)
{
    return min(min(a,b),c);
}

int painel_dist(struct painel *certo, struct painel *errado, size_t sz1, size_t sz2)
{
    int D[sz1 + 1][sz2 + 1];

    for (size_t i = 0; i <= sz1; ++i)
        D[i][0] = i * 30;

    for (size_t j = 0; j <= sz2; ++j)
        D[0][j] = j * 150;

    for (size_t i = 1; i <= sz1; ++i)
        for(size_t j = 1; j <= sz2; ++j)
            if (strcmp(certo[i - 1].cor, errado[j - 1].cor) == 0)
                D[i][j] = D[i - 1][j - 1];              /* Nao muda */
            else
                D[i][j] = min3(D[i - 1][j] + 30,        /* Remocao */
                               D[i][j - 1] + 150,       /* Adicao */
                               D[i - 1][j - 1] + 60);   /* Troca */

    return D[sz1][sz2];
}

int main(void)
{
    int T;              /* t <= 1000 */
    scanf("%d\n", &T);
    for (size_t t = 0; t < T; ++t)
    {
        int R = 0;
        scanf("%d\n", &R);

        int M = 0;
        scanf("%d\n", &M);

        struct painel errado[M];
        for (size_t i = 0; i < M; ++i)
            scanf (" %s", errado[i].cor);

        int N = 0;
        scanf("%d\n", &N);

        struct painel certo[N];
        for (size_t i = 0; i < N; ++i)
            scanf (" %s", certo[i].cor);

        char valor[50];
        sprintf(valor, "%.2f", (float)R*(float)painel_dist(errado, certo, M, N)/60.0f);
        for (size_t i =0; i < strlen(valor); ++i)
        {
            if(valor[i] == '.')
            {
                valor[i] = ',';
            }
        }

        printf("Caso #%zu: R$ %s\n", t + 1, valor);
    }
    return 0;
}
