#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_calls = 0;

char *
substr(char *dest, const char *src, size_t start, size_t len) {
  strncpy(dest, src + start, len);
  dest[len] = '\0';
  return dest;
}

void
RecPermute(char *soFar, char *rest)
{
    total_calls++;
    size_t rest_len = strlen(rest);
    if(rest_len == 0)
    {
        fprintf(stdout, "%s\n", soFar);
    } else {
        for (size_t i = 0; i < rest_len; ++i)
        {
            char *prestr = malloc (i + 1);
            substr(prestr, rest, 0, i);

            char *posstr = malloc (rest_len - i + 1);
            substr(posstr, rest, i+1, rest_len - i);

            char *remaining = malloc(rest_len + 1);
            sprintf(remaining, "%s%s", prestr, posstr);

            free(posstr);
            free(prestr);

            char *soFar0 = malloc (strlen(soFar) + 2);
            sprintf(soFar0, "%s%c", soFar, rest[i]);

            RecPermute(soFar0, remaining);
            free(soFar0);
            free(remaining);
        }
    }
}

int main(void)
{
    char s[5] = "caoc";
    char r[5] = "";
    RecPermute(r, s);
    fprintf(stdout, "Total calls: %d\n", total_calls);

    return 0;
}
