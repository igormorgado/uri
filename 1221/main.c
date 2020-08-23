#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// sqrt(2^31)+1
#define SZ 46342

typedef uint_fast32_t u32;

static inline u32
upper_test(const u32 n)
{
    return (u32)(ceilf(sqrtf((float)n)));
}


/* C is a copy of the sieve */
static void
prime_table(const u32 n, u32 const * const C,
            u32 * const P, u32 *np)
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
sieve(u32 const n, u32 * const C)
{
    // assert((0 <= n) && (n <= 1e15));

    /* Fill the sieve with each position */
    for (size_t i = 0; i <= n; i++)
        C[i] = i;

    /* Simplest case, even numbers */
    for (size_t i = 0; i <= n; i+=2)
        C[i] = 2;

    u32 t = 2;
    /* All other cases */
    for (size_t i = 3; i <= upper_test(n); ++i)
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

static bool
is_prime_lrg (u32 const n, u32 const * const P, u32 const np)
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


int main(void) {
    int N, X;

    u32 S[SZ];
    sieve(SZ-1, S);

    u32 P[SZ];
    u32 np = 0;
    prime_table(SZ-1, S, P, &np);

    scanf("%d\n", &N);
    for (size_t i = 0; i < N; ++i)
    {
        scanf("%d\n", &X);
        printf("%s\n", is_prime_lrg(X, P, np) ? "Prime" : "Not Prime");
    }
    return 0;
}
