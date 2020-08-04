#include <stdio.h>
#include <string.h>

typedef long int li;

#define MODULO (li)100000007
#define WORDSZ 10001

void print_count(int count[26]);
void count_letters(char *s, int count[26]);
void gcde(li a, li b, li *d, li *x, li *y);
li divm(li x, li y, li n);
li invm(li b, li n);
void precomputa_fatorial();

/*
 * GLOBALS
 */
li f[WORDSZ];

void print_count(int count[26])
{
    for(size_t i = 0; i < 25; ++i)
        fprintf(stdout, "%5d, ", count[i]);
    fprintf(stdout, "%5d", count[25]);
}

void count_letters(char *s, int count[26])
{
    for(size_t i = 0; i < strlen(s); ++i)
        count[s[i] - 'a']++;
}

li divm(li x, li y, li n)
{
    return ((x % n) * (invm(y, n) % n)) % n;
}

li invm(li b, li n)
{
    li d = 0;
    li x = 0;
    li y = 0;
    gcde(b, n, &d, &x, &y);
    return (x+n) % n;
}

void gcde(li a, li b, li *d, li *x, li *y)
{
    if (b == 0)
    {
        *d = a;
        *x = 1;
        *y = 0;
        return;
    }

    gcde(b, a%b, d, x, y);
    li nx = *x;
    *x = *y;
    *y = nx - (a / b) * (*y);
}

void precomputa_fatorial()
{
    f[0] = 1;
    f[1] = 1;
    for(size_t i = 2; i < WORDSZ; ++i)
        f[i] = (i * f[i-1]) % MODULO;
}

int main(void) {

    precomputa_fatorial();
    char s[WORDSZ];
    while(scanf("%s", s) != EOF)
    {
        if(strcmp(s, "0") == 0)
            break;

        int count[26];
        memset(count, 0, sizeof(count));
        count_letters(s, count);

        size_t n = strlen(s);

        li d = 1;
        for(size_t i = 0; i < 26; ++i)
            d = (d * f[count[i]]) % MODULO;

        printf("%ld\n", divm(f[n], d, MODULO));
    }
    return 0;
}
