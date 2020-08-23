#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#define MAXVALUE 900000000000000LU
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

static inline u64
upper_test(const u64 n)
{
    return (u64)(ceil(sqrt((double)n)));
}

/* C is a copy of the sieve */
static void
prime_table(const u64 n, u64 const * const C,
            u64 * const P, u64 *np)
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
sieve(u64 const n, u64 * const C)
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

/*  1e7 <= n <= 1e15 */
static bool
is_prime (u64 const n, u64 const * const P, u64 const np)
{
    // assert((1e7 <= n) && (n <= 1e15));

    size_t i;
    for (i = 1; i < np; i++)
    {
        if(n % P[i] == 0)
        {
            if (n != P[i])
            {
                return false;
            }
            return true;
        }
    }
    return true;
}

static void
prime_factors(u64 n,
              u64 const * const P, u64 const np,
              u64 * const F, u64 * const nf)
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

static void
divisors(u64 n,
         u64 const * const F, u64 const nf,
         u64 * const D, u64 * const nd)
{
    // assert((1e5 <= n) && (n <= 1e7));

    u64 k = 0;
    u64 nda = 0;

    *nd = 1;
    D[0] = 1;
    size_t i;
    for (i = 1; i <= nf; ++i)
    {
        if (F[i] == F[i-1])
        {
            k *= F[i];
        }
        else
        {
            k = F[i];
            nda = *nd;
        }
        size_t j;
        for (j = 0; j < nda; ++j)
            D[(*nd)++] = k * D[j];
    }
}

static void
print_header(u64 const n)
{
    for(size_t i=0; i < n; i++)
        printf("%4zu  ", i);
    printf("\n");
}

static void
print_table(u64 const * const T, u64 const nelem)
{
    for(size_t i = 0; i < nelem-1; ++i)
        printf("%4zu, ", T[i]);
    printf("%4zu\n", T[nelem-1]);
}

static u64
count_star(u64 const n, u64 const * const F, u64 const nf)
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

    u64 *S = calloc(LIM+2, sizeof *S);
    sieve(LIM+1, S);

    u64 *P = calloc (LIM+2, sizeof *P);
    u64 np = 0;
    prime_table(LIM+1, S, P, &np);
    free(S);

    u64 N;
    while(scanf("%zu\n", &N) != EOF)
    {
        const size_t F_sz = (size_t)(ceil(log2((double)N)) + 1);
        u64 *F = calloc (F_sz, sizeof *F);
        u64 nf = 0;
        prime_factors(N, P, np, F, &nf);


#if DEBUG
        printf("\nFactors(lrg) for %zu (sz: %zu)\n", N, nf);
        print_header(nf+1);
        print_table(F, nf+1);
#endif

        printf("%zu\n", count_star(N, F, nf));

        free(F);
    }

    free(P);

    return 0;
}
