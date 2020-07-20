#include <stdio.h>

void mergeptr(int *array, int l, int m, int r)
{
    int tmp[r - l + 1];
    int *tptr = tmp;
    int *lptr = array + l;
    int *rptr = array + m + 1;

    /* Find the smallest in each side */
    while( (lptr <= (array+m)) && rptr <= (array+r))
        if( *lptr <= *rptr) *tptr++ = *lptr++;
        else                *tptr++ = *rptr++;

    /* Copy the remaining */
    while(lptr <= (array+m)) *tptr++ = *lptr++;
    while(rptr <= (array+r)) *tptr++ = *rptr++;

    /* Copy back */
    for(size_t i = 0; i < (r-l+1); ++i)
        array[l+i] = tmp[i];
}

void merge_sort(int *array, int l, int r) {
    if (l < r) {
        int m = (l+r)/2;
        merge_sort(array, l, m);
        merge_sort(array, m+1, r);
        mergeptr(array, l, m, r);
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
        for(size_t i = 0; i < n; ++i)
            printf("%d ", permut[i]);
        printf("\n");

        merge_sort(&permut[0], 0, n-1);
        for(size_t i = 0; i < n; ++i)
            printf("%d ", permut[i]);
        printf("\n");

        printf("\n");
    }
    return 0;
}
