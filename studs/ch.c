#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <stdbool.h>

#define EPS     1e-9

struct v2
{
double x;
double y;
};
typedef struct v2 Vec2;

/* Check "equality" of two scalars */
static bool
equal(double a, double b)
{
    return fabs(a - b) < EPS;
}


static int
orientation(Vec2 v0, Vec2 v1, Vec2 v2)
{
    double s = (v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y);
    if      (s > 0) return  1; // counterclockwise
    else if (s < 0) return -1; // clockwise
    else            return  0; // colinear
}


struct compute
{
    size_t i;   // index
    double a;   // angle
    double d;   // dist
};


/* Order by smaller angle, and if equal, smaller distance */
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


/* Decreasing distance */
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


static void
Isort(Vec2 *p, size_t e, size_t d)
{
    int k;
    size_t i, j;
    Vec2 t, r;
    double d0, d1, d2;

    if (d > e)
    {
        i = e;
        j = d;
        t = p[(e+d)/2];
        d1 = p[0].x - t.x;
        d2 = p[0].y - t.y;
        d0 = d1 * d1 + d2 * d2;

        while (i <= j)
        {
            while(1)
            {
                k = orientation(p[0], p[i], t);
                if (k == 1)
                {
                    i++;
                }
                else if (k == 0)
                {
                    d1 = p[0].x - p[i].x;
                    d2 = p[0].y - p[i].y;
                    d1 = d1 * d1 + d2 * d2;
                    if (d1 < d0)
                    {
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            while(1)
            {
                k = orientation(p[0], t, p[j]);
                if (k == 1)
                {
                    j--;
                }
                else if (k == 0)
                {
                    d1 = p[0].x - p[j].x;
                    d2 = p[0].y - p[j].y;
                    d1 = d1 * d1 + d2 * d2;
                    if (d0 < d1)
                    {
                        j--;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            if (i <= j)
            {
                r = p[i];
                p[i] = p[j];
                p[j] = r;
                i++;
                j--;
            }
        }
        Isort (p, e, j);
        Isort (p, i, d);
    }
}

static int
convexhull2(const Vec2 * const src, const size_t src_elems,
        Vec2 * dst, size_t * dst_elems)
{
    Vec2 * src_cpy = malloc(src_elems * sizeof *src);

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

    Isort(src_cpy, 1, src_elems - 1);

    dst[0] = src_cpy[0];

    size_t ji = 1;
    while (orientation(src_cpy[0], src_cpy[ji], src_cpy[(ji + 1) % src_elems]) == 0)
        ji++;

    dst[1] = src_cpy[ji];
    dst[2] = src_cpy[ji +1];

    size_t stack_pos = 2;
    for (size_t j = ji + 2; j <= src_elems; ++j)
    {
        while (orientation(dst[stack_pos - 1], dst[stack_pos], src_cpy[j%src_elems]) <= 0)
        {
            stack_pos--;
        }
        stack_pos++;
        dst[stack_pos] = src_cpy[ji];
    }
    *dst_elems = stack_pos;
    return stack_pos;

}

/* Find convex hull from src and stores in dst : O( 2n log(n) + 4n + 2 ) and memory O(3n)*/
static void
convexhull(const Vec2 * const src, const size_t src_elems,
           Vec2 * dst, size_t * dst_elems)
{
    /* Copy SRC since it's const */
    Vec2 * src_cpy = malloc(src_elems * sizeof *src);

    /* Find the index: O(n) */
    size_t imin = 0;
    for (size_t i = 0; i < src_elems; ++i)
    {
        src_cpy[i].x = src[i].x;
        src_cpy[i].y = src[i].y;
        // Lowest Y and if equal, lowest x.
        if ((src_cpy[i].y < src_cpy[imin].y) ||
            (equal(src_cpy[i].y, src_cpy[imin].y) &&
            (src_cpy[i].x < src_cpy[imin].x)))
        {
            imin = i;
        }
    }

    /* First point in src_cpy should be the one at index imin: O(1) */
    src_cpy[0] = src[imin];
    src_cpy[imin] = src[0];

    Isort(src_cpy, 1, src_elems - 1);

    /* In this point src_cpy is sorted by angle and distance */
    dst[0] = src_cpy[0];

    size_t j = 1;
    while (orientation(dst[0], src_cpy[j], src_cpy[(j + 1) % src_elems]) == 0)
        j++;

    dst[1] = src_cpy[j];
    dst[2] = src_cpy[(j + 1) % src_elems];

    size_t stk_pos = 2;

    for (size_t i = j + 2; i <= src_elems; ++i)
    {
        while (orientation(dst[stk_pos - 1], dst[stk_pos], src_cpy[i%src_elems]) <= 0)
        {
            stk_pos--;
        }
        stk_pos++;
        dst[stk_pos].x = src_cpy[i%src_elems].x;
        dst[stk_pos].y = src_cpy[i%src_elems].y;
    }
    free(src_cpy);

    *dst_elems = stk_pos;
}


int main(void)
{
    const Vec2 s[7] = {
        {3,6},
        {8,4},
        {5,4},
        {4,3},
        {5,2},
        {1,2},
        {6,1}
    };

    Vec2 cvxhl[7] = {0};
    size_t n = 0;
    convexhull(s, 7, cvxhl, &n);

    printf("Expecting: {6,1}, {8,4}, {3,6}, {1,2}\n");
     for(size_t i = 0; i < n; ++i)
        printf("%zu: (%.1f, %.1f)\n", i, cvxhl[i].x, cvxhl[i].y);
    return 0;
}

