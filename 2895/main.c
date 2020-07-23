#include <stdio.h>

#define MININT(a,b)  (((a) < (b)) ? (a):(b))
#define POT(n)       (next_power_two((n)))
#define POT_2(n)     (prev_power_two((n)))
#define IS_POT(n)    (((n & (n-1)) == 0))

int memoing[2049];

unsigned int
prev_power_two(unsigned int n)
{
    // THIS CASE DO NOT EXIST IN PROBLEM
    // if (n == 0)
    //     return 0;
    n--;
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);
    return n - (n >> 1);
}

unsigned int
next_power_two(unsigned int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

unsigned int T(unsigned int n)
{
    // Encontramos
    if(memoing[n] != -1)
        return memoing[n];

    // Caso base (potencia de 2)
    if (IS_POT(n)) {
        memoing[n] = 1;
        return 1;
    }
    memoing[n] = MININT(T(n - POT_2(n)), T(POT(n)-n))+1;
    return memoing[n];
}

int main(void) {
    // Initialize memoization
    for(size_t i = 0; i<2049; i++) memoing[i] = -1;

    int t;
    scanf("%d\n", &t);
    for(size_t i = 0; i < t; ++i)
    {
        int n;
        scanf("%d\n", &n);
        fprintf(stdout, "%u\n", T(n));
    }
    return 0;
}
