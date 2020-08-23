#include <stdio.h>

#define M  1000000007
#define SZ 1000000009

unsigned int Tm[SZ];

unsigned int T(unsigned int N)
{
    if (Tm[N] != 0)
        return Tm[N];
    Tm[N] = ((T(N-2) % M) + (T(N-3) % M)) % M;
    return Tm[N];
}

int main(void) {
    Tm[0]=0;
    Tm[1]=1;
    Tm[2]=2;
    Tm[3]=2;
    unsigned long long int N;
    while(scanf("%llu", &N) != EOF)
    {
        unsigned int n = (unsigned int)(N % M);
        printf("%u\n", T(n));
    }

    return 0;
}
