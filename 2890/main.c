#include <stdio.h>
#include <math.h>

typedef long long int li;

#define MODULO (li)1000007
#define MAXN 10001


li f[MAXN];

void gcde(li a, li b, li *d, li *x, li *y);
li divm(li x, li y, li n);
li invm(li b, li n);
li C(li n, li p);
li mulm(li x, li y, li n);
li powm(li x, li n);
void precomputa_fatorial();


li mulm(li x, li y, li n)
{
    return (x * y) % n;
}

li powm(li x, li n)
{
    return mulm(x, x, n);
}

li divm(li x, li y, li n)
{
    return ((x % n) * (invm(y, n) % n)) % n;
}

li invm(li b, li n)
{
    li d = 0;
    li x = 0;
    li y = 0;
    gcde(b, n, &d, &x, &y);
    return (x+n) % n;
}

void gcde(li a, li b, li *d, li *x, li *y)
{
    if (b == 0)
    {
        *d = a;
        *x = 1;
        *y = 0;
        return;
    }

    gcde(b, a%b, d, x, y);
    li nx = *x;
    *x = *y;
    *y = nx - (a / b) * (*y);
}

li C(li n, li p)
{
    if (p==0) return 1;
    else return (li)(round((double)(C(n-1, p-1)) * ((double)n/(double)p)));
}


void precomputa_fatorial()
{
    f[0] = 1;
    f[1] = 1;
    for(size_t i = 2; i < MAXN; ++i)
        f[i] = (f[i-1] * i) % MODULO;
}


int main(void) {
    precomputa_fatorial();

    int n = 0;
    while(scanf("%d", &n) != EOF)
    {
        if(n == 0) break;
        // a(n) = C(n,1) + 3C(n,2) + 3C(n,3) + 2C(n,4)
        li res = 0;
        res += C(n, 1);
        res %= MODULO;
        res += 3 * C(n, 2);
        res %= MODULO;
        res += 3 * C(n, 3);
        res %= MODULO;
        res += 2 * C(n, 4) % MODULO;
        res %= MODULO;

        fprintf(stdout,"%ld\n", res);
    }

    return 0;
}
