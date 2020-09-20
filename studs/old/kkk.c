#include <stdio.h>

int hmm(int n)
{
    int b[131231];
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;

    printf("%d %d %d\n", b[0], b[1], b[2]);
}

int main(int argc, char *argv[]) { 

    hmm(-1);
    return 0;
}
