#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef int64_t i64;
typedef uint64_t u64;


u64 fat_mod(u64 n, u64 modulo, u64 *fat_t)
{
    if(fat_t[n] == 0) {
        if(n == 0)       fat_t[n] = 1;
        else if (n == 1) fat_t[n] = 1;
        else             fat_t[n] = (n * fat_mod(n-1, modulo, fat_t)) % modulo;
    }
    return fat_t[n];
}


int main(void) {

    const u64 MAXN = 100000;
    const u64 MODULO = 1000000009;

    u64 *fat_t = calloc ((MAXN+1), sizeof(*fat_t));

    fat_t[1] = 1;
    fat_t[2] = 1;
    fat_t[3] = 1;

    int N = 0;
    while(scanf("%d", &N) != EOF)
    {
        if(N == 0) break;
        printf("%lu\n", fat_mod(N, MODULO, fat_t));
    }

    return 0;
}
