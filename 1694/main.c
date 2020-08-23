#include <stdio.h>
#include <math.h>
#include <stdint.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t  i8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef double        f64;
typedef float         f32;

static inline u64
upper_test(const u64 n)
{
    return (u64)(ceil(sqrt((double)n)));
}

/* Fill sieve table */
static void
sieve(u64 const n, u64 * const C)
{

    /* Fill the sieve with each position
     *
     *  This case C[1] == 1 the validades as prime number
     *
     * */
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

static bool
is_prime (u64 const n, u64 const * const C)
{
    if(n == 1)
        return false;
    else
        return C[n] == n ? true : false;
}

u64 C(u64 n, u64 p)
{
    if (p==0) return 1;
    else return (u64)(round((f64)(C(n-1, p-1)) * ((f64)n/(f64)p)));
}

int main(void) {

    u64 S[2510] = {0};
    sieve(2505, S);

    u64 N, M, K;
    while(scanf("%zu%zu%zu", &N, &M, &K))
    {
        if( N == 0 && M == 0 && K == 0) break;

        u64 bets = 0;
        u64 non_primes_count = 0;
        size_t i, j;

        for(i = 0; i < N; ++i)
        {
            non_primes_count = M;
            for(j = 0; j < M; ++j)
            {
                if (is_prime (i * M + j, S))
                {
                    non_primes_count--;
                }
            }

            if (non_primes_count >= K)
            {
                bets += C(non_primes_count, K);
            }
        }

        if (K != 1 && M != N)
        {
            for(i = 0; i < M; ++i)
            {
                non_primes_count = N;
                for(j = 0; j < N; ++j)
                {
                    if (is_prime (j * M + i, S))
                    {
                        non_primes_count--;
                    }
                }
                if (non_primes_count >= K)
                {
                    bets += C(non_primes_count, K);
                }
            }
        }

        printf("%zu\n", bets);
    }

    return 0;
}
