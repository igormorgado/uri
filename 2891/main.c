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


typedef struct vec2
{
    double x;
    double y;
} Vec2;


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
    if      (s > 0) return ORI_COUNTERCLOCKWISE; // counterclockwise
    else if (s < 0) return ORI_CLOCKWISE; // clockwise
    else            return ORI_COLINEAR; // colinear
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
    Vec2 * src_cpy = (Vec2 *)malloc(src_elems * sizeof *src);

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
    Vec2 * pcpy = (Vec2 *)malloc(src_elems * sizeof *pcpy);
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
polygon_area(Vec2 *p, size_t n)
{
    double result = 0;
    for (size_t i = 0; i < n; ++i)
        result += p[i].x * p[(i+1)%n].y - p[(i+1)%n].x * p[i].y;

    return .5 * result;
}


#if 0
static void
vecprint(Vec2 p)
{
    printf("(%4.0f, %4.0f)\n", p.x, p.y);
}
#endif

int main(void) {
    const int M = 5;
    Vec2 P[5];

    while(scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf\n",
               &P[0].x, &P[0].y,
               &P[1].x, &P[1].y,
               &P[2].x, &P[2].y,
               &P[3].x, &P[3].y,
               &P[4].x, &P[4].y))
    {
        if ((P[0].x || P[0].y ||
             P[1].x || P[1].y ||
             P[2].x || P[2].y ||
             P[3].x || P[3].y ||
             P[4].x || P[4].y) == 0)
            break;

#if 0
        for(size_t i = 0; i < 5; ++i)
        {
            printf("\n* %zu -- %zu %zu %zu %zu*\n", i, i, (i+1)%M, (i+2)%M, (i+3)%M);
            vecprint(P[i]);
            vecprint(P[(i+1)%M]);
            vecprint(P[(i+2)%M]);
            vecprint(P[(i+3)%M]);
        }
#endif
        double max_area = 0;
        for(size_t i = 0; i < 5; ++i)
        {
            Vec2 Q[4] = {P[i], P[(i+1)%M], P[(i+2)%M], P[(i+3)%M]};
            Vec2 CH[4];
            size_t CHSZ = 0;
            convexhull(Q, 4, CH, &CHSZ);
#if 0
            if(CHSZ > 2)
            {
                if (CHSZ == 4)
                    printf("*** ");
                else
                    printf("    ");

                for(size_t j = 0; j < CHSZ - 1; ++j)
                {
                    printf("(%.0f, %.0f), ", CH[j].x, CH[j].y);
                }
                printf("(%.0f, %.0f)\n", CH[CHSZ - 1].x, CH[CHSZ - 1].y);
            }
#endif
            if (CHSZ == 4)
            {
                double area = polygon_area(CH, 4);
                if (area > max_area)
                {
                    max_area = area;
                }
            }
        }
        printf("%.0f\n", max_area);
    }

    return 0;
}
