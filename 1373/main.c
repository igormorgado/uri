#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Quando A[i] == B[j], deve-se procurar qual o tamanho R da maior sequencia
 * consecutiva comum. Então se R > k, tem que se eexaminar todas as posições
 * T[i-l][j-l] e adotar o máximo T[i-l][j-l] +1 para k <= l <= R
 */

int lcsk( char *M, char *N, int m, int n, int k)
{
    int T[m+1][n+1];
    int tmp = 0;
    int k_max = 0;

    for (size_t i = 0; i <= m; ++i)
        T[i][0] = 0;
    for (size_t j = 0; j <= n; ++j)
        T[0][j] = 0;

    for (size_t i = 0; i <= m; ++i)
        for (size_t j = 0; j <= n; ++j)
            if (M[i - 1] == N[j - 1])
                T[i][j] = T[i - 1][j - 1] + 1;
            else
                T[i][j] = 0;

    for (size_t i = 1; i <= m; ++i)
    {
        for (size_t j = 1; j <= n; ++j)
        {
            tmp = max(T[i - 1][j], T[i][j - 1]);
            k_max = T[i][j];
            for(size_t l = k; l <= k_max; ++l)
            {
                tmp = max(tmp, T[i - l][j - l] + l);
            }
            T[i][j] = tmp;
        }
    }

    return T[m][n];
}

int main(void) {
    int k = -1;
    while(scanf("%d\n", &k))
    {
        if(k == 0) break;

        char l1[1002];
        scanf("%s\n", l1);
        char l2[1002];
        scanf("%s\n", l2);

        size_t sz1 = strlen(l1);
        size_t sz2 = strlen(l2);

        printf("%d\n", lcsk(l1, l2, sz1, sz2, k));
    }
    return 0;
}

