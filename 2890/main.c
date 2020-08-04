#include <stdio.h>
#define MODULO 1000007
// #define MAXN 10000

int main(void) {
    // int fat[MAXN];
    // fat[0] = 1;
    // fat[1] = 1;
    // for(size_t i = 2; i < MAXN; ++i)
    //     fat[i] = (i * fat[i-1]) % MODULO;

    int N = 0;
    while(scanf("%d", &N) != EOF)
    {
        if(N == 0) break;
        long int res = N;
        res *= N-1;
         res %= MODULO;
        res *= N-2;
        res %= MODULO;
        res *= N-3;
        res %= MODULO;
        res /= 12;
        fprintf(stdout,"%ld\n", res);
    }


    return 0;
}
