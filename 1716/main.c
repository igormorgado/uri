#include <stdio.h>
#include <math.h>


long long int powm(long long int b, long long int e, long long int m)
{
    long long int ans = 1;
    while (e)
    {
        if (e & 1) /* Odd? */
            ans = (ans * b) % m;

        b = (b*b) % m;
        e >>= 1;  // Halve exponents
    }
    return ans;
}

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
    return (x+n) % n;
}

long long int phi(long long int n)
{
    int ans = n;
    for (size_t i = 2; i*i <=n; ++i)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;

            ans -= ans / i;
        }
    }

    if (n > 1)
        ans -= ans / n;

    return ans;
}


int main(void) {
    int N, E, C;
    scanf("%d %d %d\n", &N, &E, &C);

    long long int P = phi(N);
    long long int I = invm(E, P);
    printf("%lld\n", powm(C, I, N));
    return 0;
}

