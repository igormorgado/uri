#include <stdio.h>

int main(void) {
    int n, r;
    while(scanf("%d\n", &n))
    {
        if(n == 0) break;
        for(r=0; n > 0; r+=n*n, n--);
        printf("%d\n", r);
    }
    return 0;
}
