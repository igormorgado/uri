#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif


#define EPS     1e-9

enum ORIENTATION
{
    ORI_CLOCKWISE = -1,
    ORI_COLINEAR = 0,
    ORI_COUNTERCLOCKWISE = 1,
    ORI_UNKNOWN = 42
} ORI;

struct vec2
{
    double x;
    double y;
};

typedef struct vec2 Vec2;

struct compute
{
    size_t i;   // index
    double a;   // angle
    double d;   // dist
};

static bool
equal(double a, double b)
{
    return fabs(a - b) < EPS;
}

static enum ORIENTATION
orientation(Vec2 v0, Vec2 v1, Vec2 v2)
{
    double s = (v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y);
    if      (s > 0) return  ORI_COUNTERCLOCKWISE; // counterclockwise
    else if (s < 0) return ORI_CLOCKWISE; // clockwise
    else            return  ORI_COLINEAR; // colinear
}


static int
__cmpcmpt(const void *p1, const void *p2)
{
    struct compute _p1 = *(struct compute *)p1;
    struct compute _p2 = *(struct compute *)p2;

    if      (_p1.a < _p2.a)
    {
        return -1;
    }
    else if (_p1.a > _p2.a)
    {
        return 1;
    }
    else
    {
        if      (_p1.d < _p2.d) { return -1; }
        else if (_p1.d > _p2.d) { return  1; }
        else                    { return  0; }
    }
}


static int
__cmpdistrev (const void *p1, const void *p2)
{
    struct compute _p1 = *(struct compute *)p1;
    struct compute _p2 = *(struct compute *)p2;

    if      (_p1.d < _p2.d)
        return 1;
    else if (_p1.d > _p2.d)
        return -1;
    else
        return 0;
}


/* Find convex hull from src and stores in dst : O( 2n log(n) + 4n + 2 ) and memory O(3n)*/
static size_t
convexhull(const Vec2 * const src, const size_t src_elems,
           Vec2 * dst, size_t * dst_elems)
{
    /* Copy SRC since it's const */
    Vec2 * src_cpy = (Vec2 *)malloc((src_elems + 10) * sizeof *src);

    /* Find the index: O(n) */
    size_t imin = 0;
    for (size_t j = 0; j < src_elems; ++j)
    {
        src_cpy[j].x = src[j].x;
        src_cpy[j].y = src[j].y;
        // Lowest Y and if equal, lowest x.
        if ((src_cpy[j].y < src_cpy[imin].y) ||
            (equal(src_cpy[j].y, src_cpy[imin].y) &&
            (src_cpy[j].x < src_cpy[imin].x)))
        {
            imin = j;
        }
    }

    /* First point in src_cpy should be the one at index imin: O(1) */
    src_cpy[0] = src[imin];
    src_cpy[imin] = src[0];

    /* ISORT START */
    /* Pre compute angle and distances: O(n) */
    struct compute c[src_elems];
    c[0].i = 0;
    c[0].a = 0.0;
    c[0].d = 0.0;
    for (size_t j = 1; j < src_elems; ++j)
    {
        double dy = src_cpy[j].y - src_cpy[0].y;
        double dx = src_cpy[j].x - src_cpy[0].x;
        c[j].i = j;
        c[j].a = atan2(dy, dx);
        c[j].d = dx * dx + dy * dy;
    }

    /* First sort pass: O(n log n)*/
    qsort(&c[1], src_elems-1, sizeof(*c), __cmpcmpt);

    /* Find the last angle to check for colinear points: O(n) */
    double last_angle = c[src_elems-1].a;
    size_t a = 1;
    for(size_t j = src_elems-1; j > 0; --j)
    {
        if(equal(c[j-1].a, last_angle))
            a++;
        else
            break;
    }

    qsort(&c[src_elems-a], a, sizeof(*c), __cmpdistrev);

    /* Create a copy of points: O(n) */
    Vec2 * pcpy = (Vec2 *)malloc((10 + src_elems) * sizeof *pcpy);
    memcpy(pcpy, src_cpy, src_elems * sizeof *src_cpy);

    /* Copy back based on extenal index:  O(n)*/
    for(size_t j = 0; j < src_elems; ++j)
    {
        src_cpy[j].x = pcpy[c[j].i].x;
        src_cpy[j].y = pcpy[c[j].i].y;
    }
    free(pcpy);

    /* ISORT END */
    /* In this point src_cpy is sorted by angle and distance */

    dst[0] = src_cpy[0];

    dst[1] = src_cpy[1];
    size_t stk_pos = 1;
    for (size_t j = 2; j <= src_elems; ++j)
    {
        while(orientation(dst[stk_pos - 1], dst[stk_pos], src_cpy[j%src_elems]) <= 0)
            stk_pos--;

        stk_pos++;
        dst[stk_pos%src_elems].x = src_cpy[j%src_elems].x;
        dst[stk_pos%src_elems].y = src_cpy[j%src_elems].y;
    }

    *dst_elems = stk_pos;
    free(src_cpy);

    return stk_pos;
}

static double
dist(Vec2 a, Vec2 b)
{
    double dy = b.y - a.y;
    double dx = b.x - a.x;
    double res =  sqrt(dy * dy + dx * dx);
    return res;
}

static double
perimetro(Vec2 *P, size_t n)
{
    double ans = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
        double d = dist(P[i], P[(i+1)%n]);
        ans += d;
    }

    return ans;
}

Vec2 V[2010];
Vec2 CH[2010];
int main(void) {
    int N = 0;
    while(scanf("%d\n", &N), N!=0)
    {
        for(size_t i = 0; i < N; ++i)
            scanf("%lf %lf\n", &V[i].x, &V[i].y);

        size_t ch_sz = 0;
        convexhull(V, N, CH, &ch_sz);
        double res = perimetro(CH, ch_sz);
        printf("Tera que comprar uma fita de tamanho %.2f.\n", res);
    }

    return 0;
}
