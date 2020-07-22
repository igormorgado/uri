#include <stdio.h>
#include <string.h>

#define INPUTSZ 12
#define ALPHABET 6

int s;
char p[INPUTSZ];
char en[INPUTSZ];
int g[INPUTSZ][ALPHABET];

void dfs(int u)
{
    for (int i = 0; i < ALPHABET; ++i)
        if (g[u][i]) {
            p[s++] = 'a' + i;
            p[s] = '\0';
            printf("%s\n", p);
            dfs(g[u][i]);
            --s;
        }
}

void main(void)
{
    strcpy(en, "bafa");
    int lig[ALPHABET] = {0};
    int t = strlen(en) - 1;

    for (int i = t - 1; i >= 0; --i) {
        for (int j = 0; j < ALPHABET; ++j)
            g[i][j] = lig[j];

        lig[en[i] - 'a'] = i;
    }
    dfs(0);
}

