#include <stdio.h>

#define M 2147483647LLU

long long int powm(long long int b, long long int e)
{
    long long int ans = 1;
    while (e)
    {
        if (e & 1) /* Odd? */
            ans = (ans * b) % M;

        b = (b*b) % M;
        e >>= 1;  // Halve exponents
    }
    return ans;
}


int main(void) {
    unsigned long long int R;
	scanf("%llu", &R);
	printf("%llu\n", powm(3, R));
    return 0;
}

