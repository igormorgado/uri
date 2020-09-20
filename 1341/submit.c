#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
max(int a, int b)
{
    return (a > b)? a : b;
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
