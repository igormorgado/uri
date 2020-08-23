#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef uint_fast32_t u32;

#define SZ 46343

static inline u32
upper_test(const u32 n)
{
    return (u32)(ceilf(sqrtf((float)n)));
}

static void
prime_table(const u32 n, u32 const * const C,
            u32 * const P, u32 *np)
{
    *np = 0;
    for (size_t i = 2; i < n; ++i)
    {
        if (C[i] == i)
        {
            P[(*np)++] = i;
        }
    }
}

static void
sieve(u32 const n, u32 * const C)
{
    size_t i;
    /* Fill the sieve with each position */
    for (i = 0; i <= n; i++)
        C[i] = i;

    /* Simplest case, even numbers */
    for (i = 0; i <= n; i+=2)
        C[i] = 2;

    u32 t = 2;
    /* All other cases */
    for (i = 3; i <= upper_test(n); ++i)
    {
        if (C[i] == i)
        {
            t = i * i;
            u32 d = i + i;
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

static void
prime_factors_lrg(u32 n,
                  u32 const * const P, u32 const np,
                  u32 * const F, u32 * const nf)
{
    *nf = 0;
    F[(*nf)++] = 1;
    size_t i;
    for(i = 0; i < np; ++i)
    {
        while (n % P[i] == 0)
        {
            F[(*nf)++] = P[i];
            n /= P[i];
        }
        if (n == 1)
        {
            break;
        }
    }
    if (n != 1)
        F[(*nf)++] = n;

    (*nf)--;
}

u32 phi(u32 n, u32 const * const F, u32 const nf)
{
    u32 r = n;
    size_t i;
    for (i = 1; i < nf; i++)
    {
        if(n % F[i] == 0)
        {
            r -= r / F[i];
            while ( n % F[i] == 0)
            {
                n /= F[i];
            }
        }
    }
    if (n > 1)
        r -= r / n;

    return r;
}


int main(void) {

    u32 S[SZ];
    sieve(SZ-1, S);

    u32 P[SZ];
    u32 np = 0;
    prime_table(SZ-1, S, P, &np);

    u32 N;
    while(scanf("%zu", &N) != EOF)
    {
        u32 F[32] = {0};
        u32 nf = 0;
        prime_factors_lrg(N, P, np, F, &nf);
        printf("%zu\n", phi(N, F, nf)/2);
    }

    return 0;
}
