#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

typedef int64_t i64;
typedef uint64_t u64;

#define MAXLEN 100
#define WORDSZ 10001
#define MODULO (i64)100000007

#define arrsz(arr)  (sizeof((arr))/sizeof(((arr)[0])))

u64 fat_T[100];

void print_count(int count[26]);
void count_letters(char *s, u64 count[26]);

i64 summ(i64 x, i64 y, i64 n);
i64 mulm(i64 x, i64 y, i64 n);
i64 divm(i64 x, i64 y, i64 n);
i64 invm(i64 x, i64 n);

i64 gcd(i64 a, i64 b);
void gcde(i64 a, i64 b, i64 *d, i64 *x, i64 *y);
i64 lcm(i64 a, i64 b);

u64 fat(u64 n);
u64 fat_memo(u64 n, u64 *fat_t);

u64 P(u64 n);
u64 A(u64 n, u64 p);
u64 C(u64 n, u64 p);

u64 Pr(u64 n, u64 *r, u64 k);
u64 Ar(u64 n, u64 k);
u64 Cr(u64 n, u64 k);

u64 fat(u64 n)
{
    /* Factorial = n! */
    if ( n == 0 ) return 1;
    return (n * fat(n - 1));
}

u64 P(u64 n)
{
    /* Permutacoes de n = n! */
    return fat(n);
}

u64 A(u64 n, u64 p)
{
    /* Arranjos de 'n' elementos com 'p'
     * n! / (n-p)!
     */
    return fat(n) / fat(n-p);
}

u64 C(u64 n, u64 p)
{
    /*
     * Combinacao 'n'  elementos com 'p'
     *
     * n!/( p! (n-p)!)
     */
    if (p==0) return 1;
    else return (u64)(round((double)(C(n-1, p-1)) * ((double)n/(double)p)));
}

u64 Pr(u64 n, u64 *r, u64 k)
{
    /*
     * Prermutacoes com repeticao
     *
     * n!/(r_1! r_2! ... r_{x}!)
     */
    if (k == 0)
        return P(n);
    else if (r[k-1] == 0)
        return Pr(n, r, k-1);
    else
        return (u64)(round((double)Pr(n-1, r, k-1) * ((double) n / (double) fat(r[k-1]))));
}

u64 Ar(u64 n, u64 p)
{
    /*
     * Arranjo com  repeticao
     *
     * n^p
     */
    if (p == 0) {
        return 1;
    } else if (p % 2 == 1) {
        return n * Ar(n, p-1);
    } else {
        u64 x = Ar(n, p/2);
        return x * x;
    }
}

u64 Cr(u64 n, u64 k)
{
    /*
     * Combinacao com repeticao
     *
     * Cr(n,k) = C(n+k-1, n)
     */
    return C(n + k - 1, n);
}

i64 summ(i64 x, i64 y, i64 n)
{
    return (x+y)%n;
}

i64 mulm(i64 x, i64 y, i64 n)
{
    return (x*y)%n;
}

i64 divm(i64 x, i64 y, i64 n)
{
    return ((x % n) * (invm(y, n) % n)) % n;
}

i64 invm(i64 b, i64 n)
{
    i64 d = 0;
    i64 x = 0;
    i64 y = 0;
    gcde(b, n, &d, &x, &y);
    return (x+n) % n;
}

i64 gcd(i64 a, i64 b)
{
    if (a == 0)
        return b;
    else
        return gcd(b % a, a);
}

void gcde(i64 a, i64 b, i64 *d, i64 *x, i64 *y)
{
    if (b == 0)
    {
        *d = a;
        *x = 1;
        *y = 0;
        return;
    }

    gcde(b, a%b, d, x, y);
    i64 nx = *x;
    *x = *y;
    *y = nx - (a / b) * (*y);
}


i64 lcm(i64 a, i64 b)
{
    return (a * b) / gcd(a, b);
}

void print_count(int count[26])
{
    for(size_t i = 0; i < 25; ++i)
    {
        fprintf(stdout, "%5d, ", count[i]);
    }
    fprintf(stdout, "%5d", count[25]);
}


void count_letters(char *s, u64 count[26])
{
    for(size_t i = 0; i < strlen(s); ++i)
    {
        count[s[i] - 'a']++;
    }
}

int main(void) {

    i64 x = 0;
    i64 y = 0;
    i64 d = 0;
    i64 a = 5;
    i64 b = 2;
    gcde(a,b,&d,&x,&y);
    printf("gcde(%ld, %ld): d %ld x %ld y %ld\n", a, b, d, x, y);
    printf("invm(%ld, %ld): %ld\n", b, (i64)MODULO, invm((i64)b, MODULO));

#if 0
    char s[WORDSZ];

    while(scanf("%s", s) != EOF)
    {
        if(strcmp(s, "0") == 0)
            break;

        u64 count[26];
        memset(count, 0, 26 * sizeof(count[0]));
        count_letters(s, count);

        printf("%s: %ld\n", s, Pr(strlen(s), count, 26));
    }
    printf("Fat(5): %ld \n", fat(5));
    printf("P(5): %ld \n", P(5));
    printf("A(10, 2): %ld \n", A(10,2));
    printf("C(10, 2): %ld \n", C(8,5));
    u64 r[] = {4,2};
    printf("Pr(9, {4,2}, 2): %ld\n", Pr(9, r, arrsz(r)));
    printf("Ar(5, 2): %ld\n", Ar(5, 2));
#endif

    return 0;
}
