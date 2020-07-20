#include <stdio.h>
#include <math.h>

#define MU_ASSERTCHECK
#include "../lib/mulib/mu_ds.h" 

int check_dir(unsigned long a[3], unsigned long b[3])
{
    for(size_t i = 0; i < 3; i++)
        for(size_t j = 0; j < 3; j++)
            if(((a[i%3] < b[j%3]) && (a[(i+1)%3] < b[(j+1)%3])) ||
               ((a[i%3] < b[(j+1)%3]) && (a[(i+1)%3] < b[j%3])))
                return 1;
    return 0;
}

int check_stack(unsigned long p[3], unsigned long q[3])
{
    int retval = 0;
    if(check_dir(p, q) == 1) retval +=1;
    if(check_dir(q, p) == 1) retval +=2;
    return retval;
}

int main(void) { 
    int n = 0, t = 0;
    unsigned long p[3], q[3];
    while(scanf("%d\n", &n) != EOF)
    {
        for(t = 0; t < n; t++)
        {
            scanf("%lu %lu %lu %lu %lu %lu\n",
                    &p[0], &p[1], &p[2],
                    &q[0], &q[1], &q[2]);
            printf("%d\n", check_stack(p, q));
        }
    }
    return 0;
}
