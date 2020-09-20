#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
#  define MALLOCINT  (int*)
#else
#  define MALLOCINT
#endif


int main(void) {
    char *M = MALLOCCHAR calloc(10000, 1);
    char *N = MALLOCCHAR calloc(10000, 1);
    scanf("%s\n", M);
    scanf("%s\n", N);

    int m = strlen(M);
    int n = strlen(N);

    printf("%d\n", lcsB(M, N, m, n));

    free(M);
    free(N);

    return 0;
}

