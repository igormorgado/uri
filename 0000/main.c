#include <stdio.h>
#include <math.h>

#define DS_ASSERTCHECK
#include "../ds.h" 

int main(void) { 
    int a[3] = {0};

    while(scanf("%1d%1d%1d\n", &a[0], &a[1], &a[2]) != EOF)
    {
        printf("%d %d %d\n", a[0], a[1], a[2]);
    }

    return 0;
}
