#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#define LIM             30000000LU

typedef int_fast64_t i64;
typedef int_fast32_t i32;
typedef int_fast16_t i16;
typedef int_fast8_t  i8;

typedef uint_fast64_t u64;
typedef uint_fast32_t u32;
typedef uint_fast16_t u16;
typedef uint_fast8_t  u8;

typedef double        f64;
typedef float         f32;

/* C is a copy of the sieve */
static void
prime_table(const u64 n, u32 const * const C,
            u32 * const P, u32 *np)
{
    // assert((0 <= n) && (n <= 1e15));

    *np = 0;
    size_t i;
    for (i = 2; i < n; ++i)
    {
        if (C[i] == i)
        {
            P[(*np)++] = i;
        }
    }
}

/* Fill sieve table */
static void
sieve(u64 const n, u32 * const C)
{
    // assert((0 <= n) && (n <= 1e15));

    /* Fill the sieve with each position */
    size_t i;
    for ( i = 0; i <= n; i++)
        C[i] = i;

    /* Simplest case, even numbers */
    for (i = 0; i <= n; i+=2)
        C[i] = 2;

    u64 t = 2;
    /* All other cases */
    for (i = 3; i <= LIM; ++i)
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

static void
prime_factors(u64 n,
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

static u64
count_sum(u64 const n, u32 const * const F, u64 const nf)
{
    u64 ans = 1;
    size_t i = 1;
    while(i <= nf)
    {
        u64 f = F[i];
        u32 fc = 0;
        while (f == F[i]) fc++, i++;
        if (f > 2) ans *= fc + 1;
    }

    return ans;
}

int main(void) {

    u32 *S = calloc(LIM+2, sizeof *S);
    sieve(LIM+1, S);

    u32 *P = calloc (LIM+2, sizeof *P);
    u32 np = 0;
    prime_table(LIM+1, S, P, &np);
    free(S);

    u64 N;
    u32 F[15];
    while(scanf("%zu\n", &N) != EOF)
    {
        memset(F, 0, 15 * sizeof(*F));
        u32 nf = 0;
        prime_factors(N, P, np, F, &nf);
        printf("%zu\n", count_sum(N, F, nf));
    }

    free(P);

    return 0;
}
