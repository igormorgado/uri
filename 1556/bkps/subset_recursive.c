#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SZ 5
#define MAXSUBSETS 16

int last_pos = 0;
int total_calls = 0;

void printSubset(char subset[MAXSUBSETS][WORD_SZ])
{
    for(size_t i = 0; i < last_pos; ++i)
        fprintf(stdout, "%s\n", subset[i]);
}

int
hasFound(char *word, char subset[MAXSUBSETS][WORD_SZ])
{
    for(size_t i = 0; i < last_pos; ++i) {
        if(strcmp(word, subset[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void
RecSubset(char *soFar, char *rest, char subset[MAXSUBSETS][WORD_SZ])
{
    total_calls++;
    if((strlen(rest) == 0))
    {
        if(hasFound(soFar, subset) == 0)
        {
            strcpy(subset[last_pos++], soFar);
        }
    } else {
        char *soFar0 = malloc(strlen(soFar + 1));
        sprintf(soFar0, "%s%c", soFar, rest[0]);
        RecSubset(soFar0, rest + 1, subset);
        RecSubset(soFar,  rest + 1, subset);
        free(soFar0);
    }
}

int main(void)
{
    char s[WORD_SZ]; //= "caoc";
    char r[WORD_SZ] = "";
    char subset[MAXSUBSETS][WORD_SZ] = {0};
    scanf("%s", s);
    s[WORD_SZ-1] = '\0';
    RecSubset(r , s, subset);
    printf("======================\n");
    printSubset(subset);
    printf("======================\n");
    fprintf(stdout, "Total calls: %d\n", total_calls);
    printf("======================\n");
    return 0;
}
