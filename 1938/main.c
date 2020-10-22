#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct vec2
{
    int x;
    int y;
};
typedef struct vec2 Vec2;

int __cmp(const void * const _a, const void * const _b)
{
    Vec2 *a = (Vec2 *)_a;
    Vec2 *b = (Vec2 *)_b;

    if (a->y != b->y)
        return a->y > b->y;
    return a->x < b->x;
}

int main(void) {
    int N;
    scanf ("%d\n", &N);

    Vec2 p[3000];
    for (size_t i = 0; i < N; ++i)
        scanf("%d %d\n", &p[i].x, &p[i].y);

    qsort(p, N, sizeof p[0], __cmp);

    int ans = 0;
    for (size_t i = 0; i < N; ++i)
    {
        int LLIM = INT_MIN;
        int RLIM = INT_MAX;
        for (size_t j = i + 1; j < N; ++j)
        {
            if (p[j].x > p[i].x)
            {
                if (p[j].x < RLIM)
                {
                    RLIM = p[j].x;
                    ans++;
                }
            }
            else
            {
                if (p[j].x > LLIM)
                {
                    LLIM = p[j].x;
                    ans++;
                }
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}
