#include <stdio.h>

int calc(char *N)
{
    int ans = 0;
    size_t i = 0;
    while(N[i])
        ans = ((ans*10) + (N[i++] - '0')) % 3;

    return ans;
}

int main(void) {
    char N[102];
    scanf("%s\n", N);
    printf("%d\n", calc(N));
    return 0;
}
