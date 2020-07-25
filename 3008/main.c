#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>

#define QMAX 10000
#define MODULO 1000007

int memoT[QMAX + 1];

const int d[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };
const int configuracoes[8] =   { 0, 0, 1, 1, 2, 5, 7, 12};

int T(int n);
int R(int n);

int R(int n) 
{
    int r = T(n) - T(n-6);
    if (r < 0)
        return r+MODULO;
    else
        return r;
}

int T(int n)
{
    if (n < 0)
        return 0;

    if(memoT[n] != -1)
        return memoT[n];

    memoT[n] = ( T(n-2) + T(n-3) + T(n-4) + 3*T(n-5) + 3*T(n-6) + T(n-7)) % MODULO;

#if 0
    int ans = 0;
    ans += T(n-2);
    ans += T(n-3);
    ans += T(n-4);
    ans += 3*T(n-5);
    ans += 3*T(n-6);
    ans += T(n-7);
    ans %= MODULO;
    memoT[n] = ans;
#endif


#if 0
    if (memoT[n] < 0)
        fprintf(stdout, "T(%d): %d\n", n, memoT[n]);
    assert (memoT[n] >= 0);
#endif
    return memoT[n];

}

int main(void) {
    // Initializing memoization of T()
    for(size_t i = 0; i < 8;      i++) memoT[i] = configuracoes[i];
    for(size_t i = 8; i <= QMAX;  i++) memoT[i] = -1;

    int t;
    scanf("%d\n", &t);

    for(size_t i = 0; i < t; ++i)
    {
        int q;
        scanf("%d\n", &q);
        fprintf(stdout, "%d\n", R(q));
    }
    return 0;
}

