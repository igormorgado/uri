#include <stdio.h>

#define M  1000000007

unsigned int T(unsigned int N)
{
    if (N == 1)
        return 1;
    if (N == 2)
        return 2;
    if (N == 3)
        return 2;
    return ((T(N-2) % M) + (T(N-3) % M)) % M;
}

int main(void) {
    unsigned long long int N;
    while(scanf("%llu", &N) != EOF)
    {
        unsigned int n = (unsigned int)(N % M);
        printf("%u\n", T(n));
    }

    return 0;
}
