#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


struct indexed_string
{
    char letter;
    int index;
};

static int
cmpchar(const void *p1, const void *p2)
{
    struct indexed_string * _w1 = (struct indexed_string *) p1;
    struct indexed_string * _w2 = (struct indexed_string *) p2;
    if ((*_w1).letter < (*_w2).letter)
        return -1;
    if ((*_w2).letter < (*_w1).letter)
        return 1;
    else
        return 0;
}


static struct indexed_string *
str_to_indexed_string(const char *s)
{
    size_t len = strlen(s);
    struct indexed_string * i_string = malloc((len+1) * sizeof(*i_string));

    for(int i=0; i<len; ++i)
    {
        i_string[i].letter = s[i];
        i_string[i].index = i;
    }
    i_string[len].index = -1;
    i_string[len].letter = '\0';

    return i_string;
}


static char *
indexed_string_to_str(const struct indexed_string * i_string)
{
    size_t len = 0;
    while(i_string[len++].index >= 0);
    char *s = malloc(len);
    for(size_t i = 0; i < len; i++)
        s[i] = i_string[i].letter;

    return s;
}


static int *
indexed_string_to_index(const struct indexed_string * i_string)
{
    size_t len = 0;
    while(i_string[len++].index >= 0);
    int * index = malloc(len * sizeof(*index));
    for(size_t i = 0; i < len; i++)
        index[i] = i_string[i].index;

    return index;
}


int main(void) {

    unsigned long len;
    char s[1000] = "abba";
    while(scanf("%s\n", s) != EOF)
    {
        len = strlen(s);
        struct indexed_string *i_string = str_to_indexed_string(s);
        qsort(i_string, len, sizeof(*i_string), cmpchar);
        char *sorted_string = indexed_string_to_str(i_string);

        free(sorted_string);
        free(i_string);
    }
    return 0;
}
