#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b)? a : b;
}

int lcs( char *M, char *N, int m, int n )
{
   int T[m+1][n+1];
   int i, j;

   for (i=0; i<=m; i++)
     for (j=0; j<=n; j++)
       if (i == 0 || j == 0)
         T[i][j] = 0;
       else if (M[i-1] == N[j-1])
         T[i][j] = T[i-1][j-1] + 1;
       else
         T[i][j] = max(T[i-1][j], T[i][j-1]);

   return T[m][n];
}

int main(void) {
    char A[1001];
    char B[1001];
    scanf("%s\n", A);
    scanf("%s\n", B);

    int a = strlen(A);
    int b = strlen(B);
    int l = lcs(A, B, a, b);

    printf("%d", a + b - l);

    return 0;
}

