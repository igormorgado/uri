#include <stdio.h>
#include <stdint.h>

typedef int i64;

#define MAXFIB 104

i64 fib_memo[MAXFIB];

i64 fib(i64 n)
{
    if(fib_memo[n] == -1)
        fib_memo[n] = fib(n-1) + fib(n-2);
    return fib_memo[n];
}

int main(void)
{
    int n;

    for(size_t i=0; i < MAXFIB; i++)
        fib_memo[i] = -1;

    fib_memo[0] = 0;
    fib_memo[1] = 1;

    scanf("%d", &n);
    for (size_t i = 0; i < n; ++i)
    {
        i64 X;
        scanf("%d", &X);

        printf("fib(%d) = %d calls = %d\n",
                X, 2 * fib(X+1) - 2, fib(X));
        fflush(stdout);
    }

    return 0;
}
