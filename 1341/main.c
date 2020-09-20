#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

static int
max(int a, int b)
{
    return (a > b)? a : b;
}

static int
min(int a, int b)
{
    return (a < b)? a : b;
}

static int
min3(int a, int b, int c)
{
    return min(min(a,b),c);
}

#if 0
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
#endif

#if 0
int edit_dist(char *str1, char *str2, int sz1, int sz2)
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
#endif


static int
edit_dist(char *str1, char *str2, size_t sz1, size_t sz2)
{
    // size_t sz1 = strlen(str1);
    // size_t sz2 = strlen(str2);
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


static int
lcs( char *str1, char *str2, size_t sz1, size_t sz2)
{
   int T[sz1+1][sz2+1];

   for (size_t i =0; i <= sz1; i++)
     for (size_t j =0; j <= sz2; j++)
       if (i == 0 || j == 0)
         T[i][j] = 0;
       else if (str1[i-1] == str2[j-1])
         T[i][j] = T[i-1][j-1] + 1;
       else
         T[i][j] = max(T[i-1][j], T[i][j-1]);

   return T[sz1][sz2];
}


static char *
readgrid(size_t height, size_t width)
{
        char *G = calloc(height * width, 1);
        char *Gptr = G;
        for (size_t i = 0; i < height; ++i)
        {
            for (size_t j = 0; j < width; ++j)
            {
                *Gptr++ = getchar();
            }
            /* Discard \n */
            getchar();
        }
        return G;

}

static char *
wordpath(char *grid, size_t height, size_t width,
         size_t n, size_t x0, size_t y0)
{
        char ch = '\0';

        char *word = calloc(n+2, 1);
        size_t x = x0 - 1;
        size_t y = y0 - 1;
        if (n == 0) {
            word[0] = grid[x * width + y];
            word[1] = '\0';
            return word;
        } else {
            for (size_t i = 0; i <= n; ++i)
            {
                word[i] = grid[x * width + y];
                ch = getchar();
                switch(ch)
                {
                    case 'E': {y +=1; break;}
                    case 'W': {y -=1; break;}
                    case 'N': {x -=1; break;}
                    case 'S': {x +=1; break;}
                    default:  {break;}
                }
            }
        }
        word[n+1] = '\0';

        return word;
}

int main(void) {
    int t = 0;
    scanf ("%d\n", &t);
    for (size_t n = 0; n < t; ++n)
    {
        /* Problem variables */
        int H = 0;
        int W = 0;
        int N = 0;
        int X0 = 0;
        int Y0 = 0;

        scanf ("%d %d\n", &H, &W);
        char *G = readgrid(H, W);

        scanf ("%d %d %d\n", &N, &X0, &Y0);
        char *s1 = wordpath(G, H, W, N, X0, Y0);

        scanf ("%d %d %d\n", &N, &X0, &Y0);
        char *s2 = wordpath(G, H, W, N, X0, Y0);

        size_t sz1 = strlen(s1);
        size_t sz2 = strlen(s2);

        int lc = lcs(s1, s2, sz1, sz2);

        printf("Case %zu: %zu %zu\n", n + 1, sz1 - lc, sz2 - lc);

        free (s1);
        free (s2);
        free (G);
    }

    return 0;
}
