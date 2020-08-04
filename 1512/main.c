#include <stdio.h>

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    else
        return gcd(b % a, a);
}

int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

int main(void) {

    int N, A, B;
    while(scanf("%d %d %d", &N, &A, &B))
    {
        if(N == 0 && A == 0 && B == 0) break;
        fprintf(stdout, "%d\n", N/A + N/B - N/lcm(B, A));
    }

    return 0;
}
