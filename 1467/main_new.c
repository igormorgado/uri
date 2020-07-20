#include <stdio.h>

static const char *OutcomesStr[] = {
    "*",
    "C",
    "B",
    "A",
    "A",
    "B",
    "C",
    "*",
    NULL
};

int main(void) { 
    short int A[3];

    while(scanf("%hd %hd %hd\n", &A[0], &A[1], &A[2]) != EOF)
    {
        printf("%s\n", OutcomesStr[(A[2] + (A[1]<<1) + (A[0]<<2))]);
    }

    return 0;
}

