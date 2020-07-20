#include <stdio.h>
#include <math.h>

int check_dir(unsigned long a[3], unsigned long b[3])
{
    int i,j;
    // fprintf(stderr,"\n");
    for(i = 0; i < 3; i++) {
        // fprintf(stderr, "A: %lu %lu\n", a[i%3], a[(i+1)%3]);
        for(j = 0; j < 3; j++) {
            // fprintf(stderr, "\tB: %lu %lu\n", b[j%3], b[(j+1)%3]);
            if(((a[i%3] < b[j%3]) && (a[(i+1)%3] < b[(j+1)%3])) ||
               ((a[i%3] < b[(j+1)%3]) && (a[(i+1)%3] < b[j%3]))) {
                // fprintf(stderr, "%lu %lu  >> %lu %lu\n",
                //         a[i%3], a[(i+1)%3],
                //         b[j%3], b[(j+1)%3]);
                return 1;
            }
        }
    }
    return 0;
}

int check_stack(unsigned long p[3], unsigned long q[3])
{
    int retval = 0;
    // fprintf(stderr, "P: %lu %lu %lu\n", p[0], p[1], p[2]);
    // fprintf(stderr, "Q: %lu %lu %lu\n", q[0], q[1], q[2]);
    if(check_dir(p, q) == 1) retval +=1;
    if(check_dir(q, p) == 1) retval +=2;
    return retval;
}

int main(void) { 

    int n = 0;
    int t = 0;
    unsigned long p[3];
    unsigned long q[3];
    while(scanf("%d\n", &n) != EOF)
    {
        for(t = 0; t < n; t++)
        {
            scanf("%lu %lu %lu %lu %lu %lu\n",
                    &p[0], &p[1], &p[2],
                    &q[0], &q[1], &q[2]);
            printf("%d\n", check_stack(p, q));
            // fprintf(stderr, "\n\n\n");
        }
    }

    return 0;
}
