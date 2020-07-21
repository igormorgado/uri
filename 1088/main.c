#include <stdio.h>


#define MU_ASSERTCHECK
#include "../lib/mulib/mu_ds.h" 

void merge(int *array, int l, int m, int r, int *t)
{
    int inver = 0;
    int cumm = 0;
    int tmp[r - l + 1];
    int *tptr = tmp;
    int *lptr = array + l;
    int *rptr = array + m + 1;

    /* Find the smallest in each side */
    while( (lptr <= (array+m)) && rptr <= (array+r))
        if( *lptr <= *rptr) {
            *tptr++ = *lptr++;
            inver += cumm;
        }
        else {
            *tptr++ = *rptr++;
            cumm++;
        }

    /* Copy the remaining */
    while(lptr <= (array+m)) {
        *tptr++ = *lptr++;
        inver += cumm;
    }
    while(rptr <= (array+r)) {
        *tptr++ = *rptr++;
        cumm++;
    }

    /* Copy back */
    for(size_t i = 0; i < (r-l+1); ++i)
        array[l+i] = tmp[i];

#if DEBUG
    fprintf(stderr, "INVERSIOESSNES: %d\n", inver);
#endif
    *t += inver;
}

void merge_sort(int *array, int l, int r, int *t) {
    if (l < r) {
        int m = (l+r)/2;
        merge_sort(array, l, m, t);
        merge_sort(array, m+1, r, t);
        merge(array, l, m, r, t);
    }
}

int main(void) { 

    int n;
    while(scanf("%d ", &n))
    {
        if(n == 0) break;
        int permut[n];
        for(size_t i = 0; i < n; i++)
        {
            scanf("%d ", &permut[i]);
        }
#if DEBUG
        for(size_t i = 0; i < n; ++i)
            printf("%d ", permut[i]);
        printf("\n");
#endif

        int t = 0;
        merge_sort(&permut[0], 0, n-1, &t);
        printf("%s\n", (t&1) ? "Marcelo":"Carlos");

#if DEBUG
        for(size_t i = 0; i < n; ++i)
            printf("%d ", permut[i]);
        printf(" INV: %d %s\n", t, (t%2) ? "Marcelo":"Carlos");
        printf("\n");
        printf("\n");
#endif
    }
    return 0;
}
