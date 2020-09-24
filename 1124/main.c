#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static int
distance_squared(int x1, int y1, int x2, int y2)
{
    return (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
}

static int
check(int L, int C, int R1, int R2)
{
    // Exit condition
    if (L == 0 && C == 0 && R1 == 0 && R2 == 0)
        exit(0);

    //  Largest diameter fits in both sides
    if(fmax(R1 * 2.0, R2 * 2.0) > fmin(L,C))
        return 0;

    //  Distance between circle centers are larger than both diameters.
    if(distance_squared (R1, R1, L - R2, C - R2) < (R1 + R2) * (R1 + R2) )
        return 0;

    return 1;
}

int main(void) {

    int L, C, R1, R2;

    while(scanf("%d %d %d %d\n", &L, &C, &R1, &R2) != EOF)
    {
        if(check(L, C, R1,R2))
            putchar('S');
        else
            putchar('N');
        putchar('\n');
    }
    return 0;
}
