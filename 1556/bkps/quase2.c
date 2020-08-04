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

void recsubset(char *sofar, char *pref, size_t pos)
{
    if (! hasFound(sofar, subset))
    {
        sprintf(subset[last_line++], "%s", sofar);
        if(strlen(sofar) > 0)
            fprintf(stdout, "%s\n", sofar);
    }

    for(size_t i = 0; i < strlen(pref); ++i)
    {
        sofar[pos] = pref[i];
        sofar[pos+1] = '\0';
        recsubset(sofar, pref + i + 1, pos + 1);
    }
}


int main(void)
{
    char s[WORDSZ];
    while(scanf("%s\n", s) != EOF)
    {
        last_line = 0;
        memset(subset, 0, MAXWORDS*WORDSZ);
        char sofar[WORDSZ] = "";
        char input[WORDSZ] = "";
        sprintf(input, "%s", s);
        qsort(input, strlen(input), 1, cmpchar);
        fprintf(stderr, "%s\n", input);
        recsubset(sofar, input, 0);
        fprintf(stdout, "\n");
    }
    return 0;
}
