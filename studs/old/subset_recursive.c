#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int last_pos = 0;
int total_calls = 0;

void printSubset(char found[16][5])
{
    for(size_t i = 0; i < last_pos; ++i)
        fprintf(stdout, "%s\n", found[i]);
}

int
hasFound(char *word, char found[16][5])
{
    for(size_t i = 0; i < last_pos; ++i) {
        if(strcmp(word, found[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void
RecSubset(char *soFar, char *rest, char found[16][5])
{
    total_calls++;
    if((strlen(rest) == 0))
    {
        if(hasFound(soFar, found) == 0)
        {
            strcpy(found[last_pos++], soFar);
        }
    } else {
        char *soFar0 = malloc(strlen(soFar + 1));
        sprintf(soFar0, "%s%c", soFar, rest[0]);
        RecSubset(soFar0, rest + 1, found);
        RecSubset(soFar,  rest + 1, found);
        free(soFar0);
    }
}

int main(void)
{
    char s[5] = "caoc";
    char r[5] = "";
    char found[16][5] = {0};
    RecSubset(r , s, found);
    printSubset(found);
    fprintf(stdout, "Total calls: %d\n", total_calls);

    return 0;
}
