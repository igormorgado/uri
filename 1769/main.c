#include <stdio.h>

int main(void) { 
    int a[9] = {0};
    int b[2] = {0};
    int c[2] = {0};
    int i = 0;

    while(scanf("%1d%1d%1d.%1d%1d%1d.%1d%1d%1d-%1d%1d\n",
            &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7], &a[8], 
            &b[0], &b[1]) != EOF)
    {
        c[0] = 0;
        c[1] = 0;
        for(i = 1; i < 10; i++)
        {
            c[0] += a[i-1]*i;
            c[1] += a[i-1]*(10-i);
        }

        c[0] = c[0] % 11;
        c[0] = c[0] % 10;
        if (c[0] != b[0]) {
            printf("CPF invalido\n");
            continue;
        }

        c[1] = c[1] % 11;
        c[1] = c[1] % 10;
        if (c[1] != b[1]) {
            printf("CPF invalido\n");
            continue;
        }

        printf("CPF valido\n");
    }

    return 0;
}
