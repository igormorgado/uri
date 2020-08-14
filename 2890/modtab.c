#include <stdio.h>

typedef long int li;
#define MODULO (li)1000007

int main() {
    li i = 0;
    li d = 0;
    while(scanf("%ld %ld", &i, &d) != EOF)
        printf("%ld\n", i);

    return 0;
}
