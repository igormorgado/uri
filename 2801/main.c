#include <stdio.h>
#include <stdlib.h>

long long int summ(long long int x, long long int y, long long int n)
{
    return ((x%n)+(y%n))%n;
}

long long int mulm(long long int x, long long int y, long long int n) {
    return ((x%n)*(y%n))%n;
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

#if 0
void gcde(long long int a, long long int b, long long int *x, long long int *y)
{
    long long int t = 0;
    *x = 1;
    *y = 0;

    long long int Pa[64];
    long long int Pb[64];

    long long int f = 0;

    while(b != 0)
    {
        Pa[t] = a;
        Pb[t] = b;
        f = a % b;
        a = b;
        b = f;
        t++;
    }

    for (size_t i = t-1; i >= 0; --i)
    {
        f = *y;
        *y = *x - (Pa[i]/Pb[i]) * (*y);
        *x = f;
    }
}
#endif

void gcde_rec(long long int a, long long int b, long long int *d, long long int *x, long long int *y)
{
    if (b == 0)
    {
        *d = a;
        *x = 1;
        *y = 0;
        return;
    }

    gcde_rec(b, a%b, d, x, y);
    long long int nx = *x;
    *x = *y;
    *y = nx - (a / b) * (*y);
}


long long int invm(long long int b, long long int n)
{
    // TODO: Assert b and n are pairwise prime
    long long int d = 0;
    long long int x = 0;
    long long int y = 0;
    gcde_rec(b, n, &d, &x, &y);
    //gcde(b, n, &x, &y);
    return (x+n) % n;
}

long long int divm(long long int x, long long int y, long long int n)
{
    return ((x % n) * (invm(y, n) % n)) % n;
}


long long int
R(long long int L,
  long long int I,
  long long int N,
  long long int A,
  long long int B)
{
    long long int ans = mulm(I, L - B, N) % N;
    if (ans < 0)
        ans += N;

    return ans;
}


long long int
E(long long int L,
  long long int N,
  long long int A,
  long long int B)
{
    //return (((A % N) * (L % N) % N ) + (B % N)) % N;
    return summ (mulm (A, L, N), B, N);
}

int main(void) {
    size_t Msz = 0;                              /* Message size */
    scanf("%zu\n", &Msz);

    long long int *M = malloc(sizeof *M * Msz);         /* Message */
    for(size_t i = 0; i < Msz; ++i)
        scanf("%lld", M + i);

    long long int N;                                  /* Alphabet size */
    long long int A;                                  /* Coprime with N */
    long long int B;                                  /* [0, N-1] */
    scanf("%lld %lld %lld\n", &N, &A,&B);
    if(gcd(N, A) == 1)
    {
        long long int I = invm(A, N);
        for (size_t i = 0; i < Msz - 1; ++i)
            printf("%lld ", R(M[i], I, N, A, B));
        printf("%lld\n", R(M[Msz-1], I, N, A, B));

        // for(size_t i = 0; i < Msz-1; ++i)
        //     printf("%lld ", E(M[i], N, A, B));
        // printf("%lld\n", E(M[Msz-1], N, A, B));
    }
    else
    {
        printf("DECIFRAGEM AMBIGUA\n");
    }

    free(M);
    return 0;
}
