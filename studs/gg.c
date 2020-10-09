#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#ifndef __cplusplus
# include <stdbool.h>
#endif

#define EPS     1e-9

union v2
{
    struct
    {
        double x;
        double y;
    };
    struct
    {
        double a;
        double b;
    };
    double e[2];
};
typedef union v2 Vec2;
typedef union v2 Point;


struct compute
{
    size_t i;   // index
    double a;   // angle
    double d;   // dist
};


static void
point_print(Vec2 p)
{
    printf("(%f, %f)\n", p.x, p.y);
}


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
    if      (s > 0) return  1;
    else if (s < 0) return -1;
    else            return  0;
}


/* Return true if bounding boxes overlap, false otherwise */
static bool
aabb_vec(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 v3)
{
    bool res = ((fmax (v0.x, v1.x) >= fmin (v2.x, v3.x)) &&
                (fmax (v2.x, v3.x) >= fmin (v0.x, v1.x)) &&
                (fmax (v0.y, v1.y) >= fmin (v2.y, v3.y)) &&
                (fmax (v2.y, v3.y) >= fmin (v0.y, v1.y)));
    return res;
}

static bool
segment_intercept(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 v3)
{
    bool res = (((orientation(v0, v1, v2) * orientation(v0, v1, v3)) <= 0) &&
                ((orientation(v2, v3, v0) * orientation(v2, v3, v1)) <= 0) &&
                aabb_vec(v0, v1, v2, v3));
    return res;
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


/* Find close polygon: O( 2n log(n) + 4n + 2 ) and memory O(2n)*/
static void
poligon_closed(const Vec2 * s, Vec2 * p, const size_t n)
{
    /* Find the index: O(n) */
    size_t i = 0;
    for (size_t j = 0; j < n; ++j)
    {
        p[j].x = s[j].x;
        p[j].y = s[j].y;
        if ((p[j].x < p[i].x) || (equal(p[j].x, p[i].x) && (p[j].y < p[i].y)))
            i = j;
    }

    /* First point in P should be the one at index i: O(1) */
    p[0] = s[i];
    p[i] = s[0];

    /* Pre compute angle and distances: O(n) */
    struct compute c[n];
    c[0].i = 0;
    c[0].a = 0.0;
    c[0].d = 0.0;
    for (size_t j = 1; j < n; ++j)
    {
        double dy = p[j].y - p[0].y;
        double dx = p[j].x - p[0].x;
        c[j].i = j;
        c[j].a = atan2(dy, dx);
        c[j].d = dx * dx + dy * dy;
    }

    /* First sort pass: O(n log n)*/
    qsort(&c[1], n-1, sizeof(*c), __cmpcmpt);

    /* Find the last angle to check for colinear points: O(n) */
    double last_angle = c[n-1].a;
    size_t a = 1;
    for(size_t j = n-1; j > 0; --j)
    {
        if(equal(c[j-1].a, last_angle))
            a++;
        else
            break;
    }

    /* Sort last n points with same angle by reverse distance: O(n log n) */
    qsort(&c[n-a], a, sizeof(*c), __cmpdistrev);

    /* Create a copy of points: O(n) */
    Vec2 pcpy[n];
    memcpy(pcpy, p, n * sizeof(*s));

    /* Copy back based on extenal index:  O(n)*/
    for(size_t j = 0; j < n; ++j)
    {
        p[j].x = pcpy[c[j].i].x;
        p[j].y = pcpy[c[j].i].y;
    }
}

int main(void)
{
    const size_t n = 13;
    Vec2 s[13] = {{2, 3}, {7, 4}, {8, 3}, {10, 10}, {8, 5},
                  {2, 4}, {7, 2}, {2, 6}, {5, 0}, {11, 8},
                  {2, 1}, {2, 8}, {4, 6}};

    for(size_t j = 0; j < n+1; ++j)
        point_print(s[j % n]);

    Vec2 p[13];
    poligon_closed(s, p, n);

    printf("\n");
    for(size_t j = 0; j < n+1; ++j)
        point_print(p[j % n]);

    return 0;
}

