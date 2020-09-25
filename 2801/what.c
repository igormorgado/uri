#include <stdio.h>
#include <stdlib.h>


int main(void) {
    size_t Msz = 0;                              /* Message size */
    scanf("%zu\n", &Msz);

    long int *M = malloc(sizeof *M * Msz);         /* Message */
    for(size_t i = 0; i < Msz; ++i)
        scanf(" %ld", M + i);

    long int N;                                  /* Alphabet size */
    long int A;                                  /* Coprime with N */
    long int B;                                  /* [0, N-1] */
    scanf("%ld %ld %ld\n", &N, &A,&B);

    // for(size_t i = 0; i < Msz-1; ++i)
    //     printf("%ld ", E(M[i], N, A, B));
    // printf("%ld\n", E(M[Msz], N, A, B));
    //printf("%ld %ld %ld %ld\n", M[Msz], N, A, B);

    for(size_t i = 0; i < Msz; ++i)
        printf("(%ld) \n", M[Msz]);

    free(M);
    return 0;
}
