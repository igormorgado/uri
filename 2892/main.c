#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

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

#define D_SZ 256

static inline u32
upper_test(const u32 n)
{
    return (u32)(ceil(sqrt((double)n)));
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


static void
prime_factors (u32 n,
               u32 const * const P, u32 const np,
               u32 * const F, u32 * const nf)
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
divisors(u32 n,
         u32 const * const F, u32 const nf,
         u32 * const D, u32 * const nd)
{
    u32 k = 0;
    u32 nda = 0;

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


static i64 gcd(i64 a, i64 b)
{
    if (a == 0)
        return b;
    else
        return gcd(b % a, a);
}

static i64 lcm(i64 a, i64 b)
{
    return (a * b) / gcd(a, b);
}

static i64 lcm3(i64 a, i64 b, i64 c)
{
    return lcm(lcm(a, b), c);
}


static void
print_header(u32 const n)
{
    for(size_t i=0; i < n; i++)
        printf("%8zu  ", i);
    printf("\n");
}

static void
print_table(u32 const * const T, u32 const nelem)
{
    for(size_t i = 0; i < nelem-1; ++i)
        printf("%8u, ", T[i]);
    printf("%8u\n", T[nelem-1]);
}

static int
cmpuint(const void *a, const void *b)
{
    if(*(u32*)a < *(u32*)b) return -1;
    else if(*(u32*)a > *(u32*)b) return 1;
    else return 0;
}

int main(void) {

    const u32 max = 1000001;
    const u32 sz = 1000;

    u32 *S = calloc(max+1, sizeof *S);
    sieve(max, S);

    u32 *P = calloc (max+1, sizeof *P);
    u32 np = 0;
    prime_table(sz, S, P, &np);

    int T, A, B;
    while(scanf("%d%d%d\n", &T, &A, &B))
    {
        if (T == 0 && A == 0 && B == 0) break;

        u32 nf = 0;
        u32 F[32];
        for (size_t i = 0; i < 32; ++i) F[i] = 0;
        prime_factors (T, P, np, F, &nf);

        u32 nd = 0;
        u32 D[D_SZ];
        for (size_t i = 0; i < D_SZ; ++i) D[i] = 0;
        divisors (T, F, nf, D, &nd);

        u32 nv = 0;
        u32 V[D_SZ];
        for (size_t i = 0; i < D_SZ; ++i) V[i] = 0;
        for(size_t i = 0; i < nd; i++)
            if ( lcm3(A, B, D[i]) == T)
                V[nv++] = D[i];

        // printf("A: %d, B: %d, D[i]: %d, LCM: %ld\n",
        //         A, B, D[nd-1], lcm3(A, B, D[nd-1]));

        qsort(V, nv, sizeof(*V), cmpuint);
        //print_header(nv);
        //print_table(V, nv);

        // printf("T: %u - nd: %u - nf: %u\n", T, nd, nf);
        // print_header(nd);
        // print_table(D, nd);
        // printf("\n");
        for(size_t i = 0; i < nv-1; ++i)
            printf("%u ", V[i]);
        printf("%u\n", V[nv-1]);
    }


    free(P);
    free(S);

    return 0;
}
