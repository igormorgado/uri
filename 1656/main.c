#include <stdio.h>

void calc(int * a, int c, int * ans, int * na)
{
    int rem[10200];

    for(size_t i = 0; i <= c; ++i) {
        rem[i] = -1;
        ans[i] = 0;
    }

    int sum = 0;
    rem[0] = 0;
    *na = 0;
    for(size_t i = 1; i <= c; ++i)
    {
        sum += a[i];
        sum %= c;

        if(rem[sum] != -1)
        {
            ans[(*na)++] = rem[sum] + 1;
            for(size_t j = rem[sum] + 2; j <= i; ++j)
                ans[(*na)++] = j;
            break;
        }
    }
}

void print_ans(int *ans, int na)
{
    for(size_t i=0; i< na-1; ++i)
        printf("%d ", ans[i]);
    printf("%d\n", ans[na-1]);
}

int main(void) {

    int c = 0;
    int n = 0;
    while(scanf("%d %d\n", &c, &n))
    {
        if(c == 0 && n == 0) break;

        int a[10200];
        a[0] = -1;
        for(size_t i = 1; i <= n; i++)
            scanf("%d", &(a[i]));

        for(size_t i = 1; i <= n; i++)
            a[i] %= c;

        int na = 0;
        int ans[10200];
        calc(a, c, ans, &na);

        print_ans(ans, na);
    }

    return 0;
}
