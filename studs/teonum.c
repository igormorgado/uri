#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include <assert.h>

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

/* Size hinting:
 *
 * 2^8 < 10e5 < 2^16 < 10e7 < 2^32 < 10e15 < 2^64
 *
 */

struct table
{
    size_t len;
    u64 * table;
};

/*
 * TODO: Change the arguments to use table struct
 * TODO: Function to allocate and destroy tables (malloc/free)
 */

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
    for (size_t i = 2; i < n; ++i)
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
    for (size_t i = 0; i <= n; i++)
        C[i] = i;

    /* Simplest case, even numbers */
    for (size_t i = 0; i <= n; i+=2)
        C[i] = 2;

    u64 t = 2;
    /* All other cases */
    for (size_t i = 3; i <= upper_test(n); ++i)
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
is_prime_lrg (u64 const n, u64 const * const P, u64 const np)
{
    // assert((1e7 <= n) && (n <= 1e15));

    for (size_t i = 1; i < np; i++)
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

static bool
is_prime_avg (u64 const n, u64 const * const C)
{
    // assert((1e5 <= n) && (n <= 1e7));
    return C[n] == n ? true : false;
}

static bool
is_prime_sml (u64 const n)
{
    // assert((0 <= n) && (n <= 1e5));

    for(size_t i = 2; i <= upper_test(n); ++i)
        if (n % i == 0)
            return false;
    return true;
}

static void
prime_factors_lrg(u64 n,
                  u64 const * const P, u64 const np,
                  u64 * const F, u64 * const nf)
{
    *nf = 0;
    F[(*nf)++] = 1;
    for(size_t i = 0; i < np; ++i)
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
prime_factors_avg(u64 n, u64 const * const C,
                  u64 * const F, u64 * const nf)
{
    // assert((1e5 <= n) && (n <= 1e7));

    *nf = 0;
    F[(*nf)++] = 1;
    while (n != 1)
    {
        F[(*nf)++] = C[n];
        n /= C[n];
    }
    (*nf)--;
}

static void
prime_factors_sml (u64 n,
                   u64 * const F, u64 * const nf)
{
    // assert((0 <= n) && (n <= 1e5));

    *nf = 0;
    F[(*nf)++] = 1;
    for (size_t i = 2; i <= upper_test(n); ++i)
    {
        while (n % i == 0)
        {
            F[(*nf)++] = i;
            n /= i;
        }
    }
    if (n > 1)
        F[(*nf)++] = n;

    (*nf)--;
}

static void
divisors_avg(u64 n,
             u64 const * const F, u64 const nf,
             u64 * const D, u64 * const nd)
{
    // assert((1e5 <= n) && (n <= 1e7));

    u64 k = 0;
    u64 nda = 0;

    *nd = 1;
    D[0] = 1;
    for (size_t i = 1; i <= nf; ++i)
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
        for (size_t j = 0; j < nda; ++j)
            D[(*nd)++] = k * D[j];
    }
}

/* Input: n: number to test
 *        C: Sieve table
 *        F, nf: Factors table and number of factors
 *        D, nd: Divisors table and number of divisors
 */
static void
divisors_lrg(u64 const n,
             u64 const * const F, u64 const nf,
             u64 * const D, u64 * const nd)
{
    // assert((1e7 <= n) && (n <= 1e15));
    divisors_avg(n, F, nf, D, nd);
}

static void
divisors_sml(u64 const n, u64 * const D, u64 * const nd)
{
    // assert((0 <= n) && (n <= 1e5));

    *nd = 0;
    for(size_t i = 1; i <= upper_test(n); ++i)
    {
        if (n % i == 0)
        {
            D[(*nd)++] = i;
            D[(*nd)++] = n/i;
        }
    }

    if (D[*nd] == D[*nd - 1])
        *nd = *nd - 1;
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

int
main(void)
{
    // u64 n = 468;
    u64 n = 999999999999989;
    u64 sz = (u64)sqrt(n)+1;

    u64 *S = calloc(sz+1, sizeof *S);
    sieve(sz, S);

    u64 *P = calloc (sz+1, sizeof *P);
    u64 np = 0;
    prime_table(sz, S, P, &np);

    size_t F_sz = (size_t)(ceil(log2((double)n)) + 1);
    u64 *F = calloc (F_sz, sizeof *F);
    u64 nf = 0;
    prime_factors_lrg(n, P, np, F, &nf);

    u64 *D = calloc (sz, sizeof *D);
    u64 nd = 0;
    divisors_lrg(n, F, nf, D, &nd);

    printf("%zu %s prime(lrg)\n", n, is_prime_lrg(n, P, np) ? "is" : "is not");
    printf("%zu %s prime(lrg)\n", n-1, is_prime_lrg(n-1, P, np) ? "is" : "is not");

    printf("\nDivisors(lrg) for %zu (sz: %zu)\n", n, nd);
    print_header(nd);
    print_table(D, nd);

    printf("\nFactors(lrg) for %zu (sz: %zu)\n", n, nf);
    print_header(nf+1);
    print_table(F, nf+1);

    free(D);
    free(S);
    free(P);
    free(F);

#if 0
    u64 n = 2147483659;
    u64 *S = calloc(n+1, sizeof *S);
    sieve(n, S);
    printf("\nSieve for %zu\n", n);
#if DEBUG
    // print_header(n+1);
    // print_table(S, n+1);
#endif

    u64 np;
    size_t P_sz = (size_t)(ceil( 1.5 * (double)(n)/log(n)));
    u64 *P = calloc (P_sz, sizeof *P);
    prime_table(n, S, P, &np);
    printf("\nPrimes to %zu (sz: %zu)\n", n, np);
#if DEBUG
    // print_header(np);
    // print_table(P, np);
#endif

    /*
     * Factorization test
     */
    size_t F_sz = (size_t)(ceil(log2((double)n)) + 1);
    u64 *F = malloc (sizeof *F * F_sz);
    u64 nf = 0;

#if 0
    memset (F, 0, sizeof (*F) * F_sz);
    nf = 0;
    prime_factors_sml(n, F, &nf);
#if DEBUG
    printf("\nFactors(sml) for %zu (sz: %zu)\n", n, nf);
    print_header(nf+1);
    print_table(F, nf+1);
#endif

    memset (F, 0, sizeof (*F) * F_sz);
    nf = 0;
    prime_factors_avg(n, S, F, &nf);
#if DEBUG
    printf("\nFactors(avg) for %zu (sz: %zu)\n", n, nf);
    print_header(nf+1);
    print_table(F, nf+1);
#endif
#endif

    memset (F, 0, sizeof (*F) * F_sz);
    nf = 0;
    prime_factors_lrg(n, P, np, F, &nf);
#if DEBUG
    printf("\nFactors(lrg) for %zu (sz: %zu)\n", n, nf);
    print_header(nf+1);
    print_table(F, nf+1);
#endif

    /*
     * Divisor test
     */
    size_t D_sz = (size_t)(ceil(sqrt((double)n)) + 1);
    u64 *D = malloc (sizeof *D * D_sz);
    u64 nd = 0;

#if 0
    memset (D, 0, sizeof (*D) * D_sz);
    nd = 0;
    divisors_sml(n, D, &nd);
#if DEBUG
    printf("\nDivisors(sml) for %zu (sz: %zu)\n", n, nd);
    print_header(nd);
    print_table(D, nd);
#endif

    memset (D, 0, sizeof (*D) * D_sz);
    nd = 0;
    divisors_avg(n, F, nf, D, &nd);
#if DEBUG
    printf("\nDivisors(avg) for %zu (sz: %zu)\n", n, nd);
    print_header(nd);
    print_table(D, nd);
#endif
#endif

    memset (D, 0, sizeof (*D) * D_sz);
    nd = 0;
    divisors_lrg(n, F, nf, D, &nd);
#if DEBUG
    printf("\nDivisors(lrg) for %zu (sz: %zu)\n", n, nd);
    print_header(nd);
    print_table(D, nd);
#endif

#if 0
    printf("%zu %s prime(sml)\n", n, is_prime_sml(n) ? "is" : "is not");
    printf("%zu %s prime(avg)\n", n, is_prime_avg(n, S) ? "is" : "is not");
#endif
    printf("%zu %s prime(lrg)\n", n, is_prime_lrg(n, P, np) ? "is" : "is not");
#if 0
    printf("%zu %s prime(sml)\n", n-1, is_prime_sml(n-1) ? "is" : "is not");
    printf("%zu %s prime(avg)\n", n-1, is_prime_avg(n-1, S) ? "is" : "is not");
#endif
    printf("%zu %s prime(lrg)\n", n-1, is_prime_lrg(n-1, P, np) ? "is" : "is not");

    free(D);
    free(S);
    free(P);
    free(F);
#endif
}

