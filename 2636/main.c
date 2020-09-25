#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

typedef long long int i64;
typedef unsigned long long int u64;

static inline u64
upper_test(const u64 n)
{
    return (u64)(ceil(sqrt((double)n)));
}

static bool
is_prime (u64 const n, u64 const * const C)
{
    // assert((1e5 <= n) && (n <= 1e7));
    return C[n] == n ? true : false;
}


long long int gcd(long long int a, long long int b)
{
    long long int r = 0;
    while(b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/* Fill sieve table */
static void
sieve(u64 const n, u64 * const C)
{
    // assert((0 <= n) && (n <= 1e15));

    /* Fill the sieve with each position */
    for (size_t i = 0; i <= n; i++)
        C[i] = i;

    /* Simplest case, even numbers */
    for (size_t i = 0; i <= n; i+=2)
        C[i] = 2;

    u64 t = 2;
    /* All other cases */
    u64 ul = upper_test(n);
    for (size_t i = 3; i <= ul; ++i)
    {
        if (C[i] == i)
        {
            t = i * i;
            u64 d = i + i;
            while (t <= n)
            {
                if (C[t] == t)
                {
                    C[t] = i;
                }
                t += d;
            }
        }
    }
}

int main(void) {
    u64 n = 100000000000000;
    u64 sz = (u64)sqrt(n)+1;

    u64 *S = (u64*)calloc(sz+1, sizeof *S);
    sieve(sz, S);

    i64 N = 0;
    while (scanf("%lld\n", &N) && N)
    {
        i64 BN = N;
        size_t t = 0;
        i64 F[3];
        for(size_t i = 2; i < sz; ++i)
        {
            if(is_prime(i, S))
            {
                if(N % S[i]  == 0)
                {
                    F[t] = S[i];
                    N /= S[i];
                    t++;
                    if (t == 2)
                    {
                        F[t] = N;
                        break;
                    }
                }
            }
        }
        printf("%lld = %lld x %lld x %lld\n", BN, F[0], F[1], F[2]);
    }
    free(S);
    return 0;
}

