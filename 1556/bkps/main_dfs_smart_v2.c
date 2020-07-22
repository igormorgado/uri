#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERNS 1001
#define ALPHABET 26

int s;
char p[PATTERNS];
char en[PATTERNS];
int g[PATTERNS][ALPHABET];

void dfs();

int main(int argc, char **argv)
{
    int t;
    while (scanf("%s", en) != EOF)
    {
        int lig[ALPHABET];
        size_t t = strlen(en);

        memset(g, 0, sizeof(g));
        memset(lig, 0, sizeof(lig));

        for (int i = t ; i >= 0; --i)
        {
            for (int j = 0; j < ALPHABET; ++j)
                g[i][j] = lig[j];

            lig[en[i-1] - 'a'] = i;
        }
        s = 0;
        dfs(0);
        putchar('\n');
    }

    return 0;

}

void dfs(int u)
{
    for (int i = 0; i < ALPHABET; ++i)
    {
        if (g[u][i])
        {
            p[s++] = 'a' + i;
            p[s] = '\0';
            printf("%s\n", p);
            dfs(g[u][i]);
            --s;
        }
    }
}
