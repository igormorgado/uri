#include "types.h"

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

