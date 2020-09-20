#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))


int max(int a, int b)
{
    return (a > b)? a : b;
}

int min(int a, int b)
{
    return (a < b)? a : b;
}

int min3(int a, int b, int c)
{
    return min(min(a,b),c);
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
#if 0
// Following code is used to print LCS
   int index = T[m][n];

   // Create a character array to store the lcs string
   char lcss[index+1];
   lcss[index] = '\0'; // Set the terminating character

   // Start from the right-most-bottom-most corner and
   // one by one store characters in lcss[]
   int i = m, j = n;
   while (i > 0 && j > 0)
   {
      // If current character in X[] and Y are same, then
      // current character is part of LCS
      if (M[i-1] == N[j-1])
      {
          lcss[index-1] = M[i-1]; // Put current character in result
          i--; j--; index--;     // reduce values of i, j and index
      }
      // If not same, then find the larger of two and
      // go in the direction of larger value
      else if (T[i-1][j] > T[i][j-1])
         i--;
      else
         j--;
   }

   // Print the lcs
   // printf("%s\n", lcss);
#endif
}

int edit_dist(char *M, char *N, int m, int n)
{
    if (m == 0) return n;
    if (n == 0) return m;

    if (M[m-1] == N[n -1])
        return edit_dist(M, N, m - 1, n - 1);

    return 1 + min3(edit_dist(M, N, m, n - 1),
                    edit_dist(M, N, m - 1, n),
                    edit_dist(M, N, m - 1, n - 1)
                   );
}

int edit_dist2(char *str1, char *str2)
{
    size_t sz1 = strlen(str1);
    size_t sz2 = strlen(str2);
    int D[sz2+1][sz1+1];
    D[0][0] = 0;

    for (size_t i = 1; i <= sz2; ++i)
        D[i][0] = D[i-1][0] + 1;

    for (size_t j = 1; j <= sz1; ++j)
        D[0][j] = D[0][j-1] + 1;

    for (size_t i = 1; i <= sz2; ++i)
        for(size_t j = 1; j <= sz1; ++j)
            if (str1[j - 1] == str2[i - 1])
                D[i][j] = D[i - 1][j - 1];
            else
                D[i][j] = 1 + min3(D[i - 1][j],
                                   D[i][j - 1],
                                   D[i - 1][j - 1]);

    return D[sz2][sz1];
}

int edit_dist3(char *str1, char *str2, int sz1, int sz2)
{
    if (sz1 == 0) return sz2;
    if (sz2 == 0) return sz1;

    if (str1[sz1 - 1] == str2[sz2 - 1])
        return edit_dist(str1, str2, sz1 - 1, sz2 - 1); // Manteve

    return 1 + min3(edit_dist(str1, str2, sz1, sz2 - 1), // Insercao
                    edit_dist(str1, str2, sz1 - 1, sz2), // Delecao
                    edit_dist(str1, str2, sz1 - 1, sz2 - 1) // Troca
                   );
}

int main()
{
  char X[] = "sunday";
  char Y[] = "saturday";

  int m = strlen(X);
  int n = strlen(Y);

  printf("Length of LCS is %d\n", lcs( X, Y, m, n));

  printf("Edit dist 1:  %d\n", edit_dist( X, Y, m, n));
  printf("Edit dist 2:  %d\n", edit_dist2( X, Y) );
  printf("Edit dist 3:  %d\n", edit_dist3( X, Y, m, n));

  return 0;
}
