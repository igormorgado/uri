#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_calls = 0;

#define LEXICON_SZ 3
#define WORD_SZ 4

const char lexicon[LEXICON_SZ][WORD_SZ] = {
    "aba",
    "bac",
};

int containsWord(const char *word, const char dict[LEXICON_SZ][WORD_SZ]);
char * substr(char *dest, const char *src, const size_t start, const size_t len);
char * FindWord(const char *soFar, const char *rest, const char dict[LEXICON_SZ][WORD_SZ]);

int
containsWord(const char *word, const char dict[LEXICON_SZ][WORD_SZ])
{
    for(size_t i = 0; i < LEXICON_SZ; ++i)
        if(strcmp(word, dict[i]) == 0)
            return 1;
    return 0;
}

char *
substr(char *dest, const char *src,const size_t start,const size_t len) {
  strncpy(dest, src + start, len);
  dest[len] = '\0';
  return dest;
}

char *
FindWord(const char *soFar, const char *rest, const char dict[LEXICON_SZ][WORD_SZ])
{
    char *ret = NULL;
    total_calls++;
    size_t rest_len = strlen(rest);
    /* We got a full permutation */
    if(rest_len == 0)
    {
        if (containsWord(soFar, dict)) {
            ret = malloc(WORD_SZ);
            sprintf(ret, "%s", soFar);
        }
        return ret;
    }

    /* Need to keep the filling the permutation */
    for (size_t i = 0; i < rest_len; ++i)
    {
        char remaining[WORD_SZ];
        substr(remaining, rest, 0, i);

        char posstr[WORD_SZ];
        substr(posstr, rest, i+1, rest_len - i);

        strcat(remaining, posstr);

        char soFar0[WORD_SZ] = {0};
        strcat(soFar0, soFar);
        soFar0[strlen(soFar)] = rest[i];

        ret = FindWord(soFar0, remaining, dict);

        if(ret != NULL) return ret;
    }
    return NULL;
}

int main(void)
{
    char s[WORD_SZ] = "abc";
    char r[WORD_SZ] = "";
    char *retval = FindWord(r, s, lexicon);
    fprintf(stdout, "retval: %s\n", retval);
    fprintf(stdout, "Total calls: %d\n", total_calls);
    free(retval);

    return 0;
}
