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
    char buf[6];

    while (fread(buf, 1, sizeof(buf), stdin))
    {
        // printf("%hd\n", OutcomesStr[(buf[4] + (buf[2]<<1) + (buf[0]<<2))]);
        //printf("%c-%c-%c\n", buf[0], buf[2], buf[4]);
    }

    // while(scanf("%hd %hd %hd\n", &A[0], &A[1], &A[2]) != EOF)
    // {
    // }

    return 0;
}

