#include <stdio.h>
#include <string.h>

#define WORD_SZ 6
#define MAXSUBSETS 40

int last_line = 0;
char subset[MAXSUBSETS][WORD_SZ];

void printSubset(char subset[MAXSUBSETS][WORD_SZ]) {
    size_t i;
    for (i = 0; i < last_line; ++i)
        fprintf(stdout, "%s\n", subset[i]);
}

int hasFound(char *word, char subset[MAXSUBSETS][WORD_SZ]) {
    size_t i;
    for (i = 0; i < last_line; ++i)
        if(strcmp(word, subset[i]) == 0)
            return 1;
    return 0;
}

void recsubset(char sofar[], char pref[], size_t pos) {
    if (! hasFound(sofar, subset))
        sprintf(subset[last_line++], "%s", sofar);

    size_t i;
    for (i = 0; i < strlen(pref); ++i) {
        sofar[pos] = pref[i];
        sofar[pos+1] = '\0';
        recsubset(sofar, pref + i + 1, pos + 1);
    }
}

int main() {
    char input[WORD_SZ] = "acco";
    char sofar[WORD_SZ] = "";
    recsubset(sofar, input, 0);
    printSubset(subset);
    return 0;
}
