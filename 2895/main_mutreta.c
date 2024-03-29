#include <stdio.h>

const int respostas[2048] = { 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 3, 2, 3, 2, 2, 1,
    2, 2, 3, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 2, 2, 1, 2, 2, 3, 2, 3, 3, 3, 2, 3,
    3, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 3, 3, 2, 3, 3, 3, 2, 3, 2, 2, 1, 2, 2,
    3, 2, 3, 3, 3, 2, 3, 3, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4,
    3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3,
    4, 3, 3, 2, 3, 3, 3, 2, 3, 2, 2, 1, 2, 2, 3, 2, 3, 3, 3, 2, 3, 3, 4, 3, 4,
    3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4,
    4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3,
    2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3,
    4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3,
    3, 4, 3, 4, 3, 3, 2, 3, 3, 3, 2, 3, 2, 2, 1, 2, 2, 3, 2, 3, 3, 3, 2, 3, 3,
    4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4,
    3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3,
    4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5,
    5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4,
    4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4,
    3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3,
    4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4,
    4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4,
    5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4,
    3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 3, 3, 2, 3, 3, 3, 2, 3, 2, 2, 1, 2, 2, 3, 2,
    3, 3, 3, 2, 3, 3, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4,
    3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4,
    4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4,
    3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4,
    5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3,
    3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5,
    5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6,
    5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5,
    6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5,
    5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3,
    3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5,
    4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4,
    5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5,
    5, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4,
    5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4,
    3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4,
    5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5,
    4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4,
    4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3,
    2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 3, 3, 2,
    3, 3, 3, 2, 3, 2, 2, 1, 2, 2, 3, 2, 3, 3, 3, 2, 3, 3, 4, 3, 4, 3, 3, 2, 3,
    3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4,
    5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4,
    3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4,
    5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5,
    4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4,
    4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5,
    4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3,
    4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5,
    5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4,
    5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5,
    4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4,
    5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5,
    4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 6,
    6, 5, 6, 6, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 6, 6, 5, 6, 6, 6, 5, 6, 5, 5,
    4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4,
    5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 6, 6, 5, 6, 6, 6, 5, 6, 5, 5, 4, 5,
    5, 6, 5, 6, 6, 6, 5, 6, 6, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5,
    5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6,
    5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4,
    5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4,
    4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4,
    4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5,
    4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4,
    5, 5, 6, 5, 6, 6, 6, 5, 6, 6, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 6, 6, 5, 6,
    6, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4,
    5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 6, 6, 5, 6, 6, 6,
    5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 6, 6, 5, 6, 6, 6, 5, 6, 5, 5, 4, 5, 5, 6, 5,
    6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6,
    5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5,
    5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3,
    2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4,
    5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5,
    5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5,
    6, 5, 6, 5, 5, 4, 5, 5, 6, 5, 6, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5,
    4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3,
    4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5,
    5, 5, 4, 5, 5, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 5, 5, 4, 5, 5, 5, 4, 5, 4,
    4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 4, 4,
    3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 5, 4, 5, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2,
    3, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 3, 2, 3, 3, 4, 3, 4, 3, 3, 2, 3,
    3, 3, 2, 3, 2, 2, 1 };


int main(void) {
    int t;
    scanf("%d\n", &t);
    for(size_t i = 0; i < t; ++i)
    {
        int n;
        scanf("%d\n", &n);
        fprintf(stdout, "%d\n", respostas[n-1]);
    }
    return 0;
}
