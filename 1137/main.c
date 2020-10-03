#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

typedef long long int lli;

struct points
{
    lli x[MAXN];
    lli y[MAXN];
    lli norm[MAXN];
};

struct compute
{
    lli xy[MAXN][MAXN];
    lli sx[MAXN][MAXN];
    lli sy[MAXN][MAXN];
};

struct points p;
struct compute cm;

static lli
min(lli a, lli b)
{
    return  a < b ? a : b;
}

static lli
max(lli a, lli b)
{
    return  a > b ? a : b;
}

static lli
check_points(size_t a, size_t b, size_t c, lli n, lli ans)
{
    lli t1 = p.x[a] * (p.y[b] - p.y[c]) - p.y[a] * (p.x[b] - p.x[c]) + cm.xy[b][c];
    if(t1 == 0) return ans;

    lli t2 = p.norm[a] * (p.y[b] - p.y[c]) - p.y[a] * (p.norm[b] - p.norm[c]) + cm.sy[b][c];
    lli t3 = p.norm[a] * (p.x[b] - p.x[c]) - p.x[a] * (p.norm[b] - p.norm[c]) + cm.sx[b][c];
    lli t4 = p.norm[a] * cm.xy[b][c] - p.x[a] * cm.sy[b][c] + p.y[a]  * cm.sx[b][c];

    lli tt = 0;
    for(size_t i = 0; i < n; ++i)
    {
        lli F = t1 * p.norm[i] - t2 * p.x[i] + t3 * p.y[i] - t4;
        if(F == 0)
            tt++;
    }
    return max(ans, tt);
}

static void
pre_compute(size_t i, size_t j)
{
    cm.xy[i][j] = p.x[i]    * p.y[j] - p.x[j]    * p.y[i];
    cm.sx[i][j] = p.norm[i] * p.x[j] - p.norm[j] * p.x[i];
    cm.sy[i][j] = p.norm[i] * p.y[j] - p.norm[j] * p.y[i];
}

int main(void) {
    int N;
    while (scanf ("%d\n", &N), N != 0)
    {

        // Read points
        for (size_t i = 0; i < N ; ++i)
        {
            scanf ("%lld %lld\n", &p.x[i], &p.y[i]);
            p.norm[i] = p.x[i] * p.x[i] + p.y[i] * p.y[i];
        }

        // Pre compute products
        for (size_t i = 0; i < N-1; ++i)
            for (size_t j = i+1; j < N; ++j)
                pre_compute(i, j);

        // Verify circle equation
        lli ans = min(2LL, N);
        for(size_t i = 0; i < N - 2; ++i)
            for(size_t j = i + 1; j < N - 1; ++j)
                for(size_t k = j + 1; k < N; ++k)
                    ans = check_points(i, j, k, N, ans);

        printf("%lld\n", ans);
    }

    return 0;
}
