#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WORDSZ 1000
#define MAXWORDS 1000

char subset[MAXWORDS][WORDSZ];
int last_line = 0;

static int
cmpchar(const void *p1, const void *p2)
{
    const char _a = *(char*)p1;
    const char _b = *(char*)p2;
    if (_a < _b )
        return -1;
    else if (_b < _a)
        return 1;
    else
        return 0;
}


int hasFound(char *word, char subset[MAXWORDS][WORDSZ])
{
    for(size_t i = 0; i < last_line; ++i)
        if(strcmp(word, subset[i]) == 0)
            return 1;
    return 0;
}

void recsubset(char *arg)
{
    if (hasFound(arg, subset))
        return;

    if (strlen(arg) == 1) {
        sprintf(subset[last_line++], "%s", arg);
        return;
    }

    sprintf(subset[last_line++], "%s", arg);

    for(size_t i = 0; i < strlen(arg); ++i)
    {
        char aux[WORDSZ];
        memset(aux, 0, sizeof(aux));
        sprintf(aux, "%s", arg);
        aux[i] = '\0';
        recsubset(aux);
    }
}


int main(void)
{
    char s[WORDSZ];
    while(scanf("%s\n", s) != EOF)
    {
        last_line = 0;
        memset(subset, 0, MAXWORDS*WORDSZ);
        recsubset(s);

        for(size_t i=0 ; i<last_line; i++)
            fprintf(stdout, "%s\n", subset[i]);
        fprintf(stdout, "\n");
    }
    return 0;
}
