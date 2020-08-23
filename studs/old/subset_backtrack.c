#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERNS 16
#define WORD_SZ 5

int last_pos = 0;
int total_calls = 0;

void printSubset(char (*words)[WORD_SZ]);
int hasFound(char *word, char (*words)[WORD_SZ]);
char * BckSubset(char *soFar, char *rest, char (*words)[WORD_SZ]);

void printSubset(char (*words)[WORD_SZ])
{
    for(size_t i = 0; i < last_pos; ++i)
        fprintf(stdout, "%s\n", words[i]);
}


int
hasFound(char *word, char (*words)[WORD_SZ])
{
    for(size_t i = 0; i < last_pos; ++i) {
        if(strcmp(word, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char *
BckSubset(char *soFar, char *rest, char (*found)[WORD_SZ])
{
    char *ret = NULL;
    size_t rest_len = strlen(rest);
    if(rest_len == 0)
    {
        if(!hasFound(soFar, found))
            return soFar;
        return NULL;
    }
    char soFar0[WORD_SZ];
    sprintf(soFar0, "%s%c", soFar, rest[0]);
    ret = BckSubset(soFar0, rest + 1, found);
    if (ret != NULL) {
        sprintf(found[last_pos++], "%s", ret);
        return ret;
    }
    ret = BckSubset(soFar,  rest + 1, found);
    if (ret != NULL) {
        sprintf(found[last_pos++], "%s", ret);
        return ret;
    }
    return NULL;
}

void
RecSubset(char *soFar, char *rest, char found[PATTERNS][WORD_SZ])
{
    total_calls++;
    size_t rest_len = strlen(rest);
    if(rest_len == 0)
    {
        if(!hasFound(soFar, found))
            strcpy(found[last_pos++], soFar);
        return;
    }
    char soFar0[WORD_SZ];
    sprintf(soFar0, "%s%c", soFar, rest[0]);
    RecSubset(soFar0, rest + 1, found);
    RecSubset(soFar,  rest + 1, found);
}

int
main(void)
{
    char s[WORD_SZ] = "acco";
    char r[WORD_SZ] = "";
    char found[PATTERNS][WORD_SZ] = {0};
    BckSubset(r , s, found);
    printSubset(found);
    fprintf(stdout, "Total calls: %d\n", total_calls);

    return 0;
}
