#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSZ 1001
#define ALPHABET 30

void subset(int u, char word[WORDSZ], int found[WORDSZ][ALPHABET], int s)
{
    int i;
    for (i = 0; i < ALPHABET; ++i)
        if (found[u][i])
        {
            word[s++] = 'a' + i;
            word[s] = '\0';
            fprintf(stdout,"%s\n", word);
            subset(found[u][i], word, found, s--);
        }
}


int main(int argc, char **argv)
{
    size_t t;
    char word[WORDSZ] = {0};
    char input[WORDSZ];
    int found[WORDSZ][ALPHABET];
    while (scanf("%s", &input[1]) != EOF)
    {
        input[0] = ' ';
        int edg[ALPHABET];
        t = strlen(input);

        memset(found, 0, sizeof(found));
        memset(edg, 0, sizeof(edg));

        for (int i = t - 1; i >= 0; --i)
        {
            for (int j = 0; j < ALPHABET; ++j)
                found[i][j] = edg[j];
            edg[input[i] - 'a'] = i;
        }

        subset(0, word, found, 0);
        fprintf(stdout,"\n");
    }

    return 0;

}
