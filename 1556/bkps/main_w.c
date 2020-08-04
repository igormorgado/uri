#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSZ 1001
#define ALPHABET 30

int t, s;
char word[WORDSZ];
char input[WORDSZ];
int graph[WORDSZ][ALPHABET];

void dfs(int u)
{
    int i;
    for (i = 0; i < ALPHABET; ++i)
        if (graph[u][i])
        {
            word[s++] = 'a' + i;
            word[s] = '\0';
            fprintf(stdout,"%s\n", word);
            dfs(graph[u][i]);
            --s;
        }
}


int main(int argc, char **argv)
{
    int i, j;
    while (scanf("%s", &input[1]) != EOF)
    {
        input[0] = 'X';
        int lig[ALPHABET];
        t = strlen(input);

        memset(graph, 0, sizeof(graph));
        memset(lig, 0, sizeof(lig));

        for (i = t - 1; i >= 0; --i)
        {

            for (j = 0; j < ALPHABET; ++j)
                graph[i][j] = lig[j];
            lig[input[i] - 'a'] = i;
        }

        s = 0;
        dfs(0);
        fprintf(stdout,"\n");

    }

    return 0;

}
