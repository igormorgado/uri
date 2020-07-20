#include <stdio.h>
#include <math.h>

#define MU_ASSERTCHECK
#include "../lib/mulib/mu_ds.h" 

int main(void) { 
    int a[3] = {0};

    while(scanf("%1d%1d%1d\n", &a[0], &a[1], &a[2]) != EOF)
    {
#ifdef DEBUG
        fprintf(stderr, "DEBUG: %d %d %d\n", a[0], a[1], a[2]);
#endif
        printf("%d %d %d\n", a[0], a[1], a[2]);
    }

    return 0;
}
