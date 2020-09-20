#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b)? a : b;
}

#ifdef __cplusplus
#define MALLOCINT  (int*)
#define MALLOCCHAR  (char*)
#else
#define MALLOCINT
#define MALLOCCHAR
#endif

int lcsA( char *M, char *N, int m, int n )
{
   int T[m+1][n+1];

   for (size_t i = 0; i <= m; i++)
     for (size_t j = 0; j <= n; j++)
       if (i == 0 || j == 0)
         T[i][j] = 0;
       else if (M[i-1] == N[j-1])
         T[i][j] = T[i-1][j-1] + 1;
       else
         T[i][j] = max(T[i-1][j], T[i][j-1]);

   return T[m][n];
}

int lcsB( char *M, char *N, int m, int n )
{

   int *T = MALLOCINT malloc(sizeof *T * (m+1) * (n+1));

   for (size_t i = 0; i <= m; i++)
     for (size_t j = 0; j <= n; j++)
       if (i == 0 || j == 0)
         T[i * n + j] = 0;
       else if (M[i-1] == N[j-1])
         T[i * n + j] =  T[(i-1) * n + (j-1)] + 1;
       else
         T[i * n + j] = max(T[(i-1) * n + j],
                            T[i * n + (j-1)]);

   int retval = T[m * n + n];
   free(T);
   return retval;
}

int main(void) {
    char *M = MALLOCCHAR calloc(10000, 1);
    char *N = MALLOCCHAR calloc(10000, 1);
    scanf("%s\n", M);
    scanf("%s\n", N);

    int m = strlen(M);
    int n = strlen(N);

    printf("%d\n", lcsB(M, N, m, n));

    free(M);
    free(N);

    return 0;
}

