#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {

    long long int S, N, M, ans;
    while(scanf("%lld %lld %lld\n", &S, &N, &M), S || N || M)
    {
        long long int C[3];
        scanf("%lld %lld %lld\n", &C[0], &C[1], &C[2]);
        long long int num = S * C[0] * labs(C[2] - C[1]);
        long long int den = (N + 1) * (M + 1);
        assert(num % den == 0 );
        ans = num / den;
        assert(ans >= 0 );
        // ans = ((S * C[0] * labs(C[2] - C[1])) / ((N + 1) * (M + 1)));
        printf("%lld\n", ans);
    }

    return 0;
}
