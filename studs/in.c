#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <assert.h>

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


static bool
point_in_segment(Vec2 q, Vec2 p0, Vec2 p1)
{
    bool result = ((orientation(q, p0, p1) == 0) &&
                   (q.x >= fmin(p0.x, p1.x)) && (q.x <= fmax(p0.x, p1.x)) &&
                   (q.y >= fmin(p0.y, p1.y)) && (q.y <= fmax(p0.y, p1.y)));
    return result;

}

static bool
polygon_point_interior_convexhull(Vec2 *p, size_t n, Vec2 q)
{
    int t = orientation(q, p[n-2], p[n-1]);
    if (t == 0)
        return point_in_segment(q, p[n-2], p[n-1]);

    for(size_t i = 1; i < n-2; ++i)
    {
        int tp = orientation(q, p[i-1], p[i]);
        if      (tp == 0)
            return point_in_segment(q, p[i-1], p[i]);
        else if (tp != t)
            return false;
    }
    return true;
}

static bool
polygon_point_interior(Vec2 *p, size_t n, Vec2 q)
{
    if (n < 3) return false;

    for(size_t i = 1; i <= n; ++i)
        if (point_in_segment(q, p[i-1], p[i%n]))
            return true;

    Vec2 qf = {INFINITY, q.y};

    int c = 0;
    for (size_t i = 1; i <= n; ++i)
        if (segment_intercept (q, qf, p[i-1], p[i%n]) &&
            ((p[i%n].y > q.y) && (p[i-1].y <= q.y)  ||
            (p[i-1].y > q.y) && (p[i%n].y <= q.y)))
                c++;

    return ((c % 2) != 0);
}


int main(void)
{

    Vec2 p[6] = { {1,1}, {4,1}, {5,2}, {4,4}, {2,4}, {1,3} };
    Vec2 q[11] = { {3,2}, {3,1}, {1,4}, {0,2}, {.5, 2.5}, {-.5, 1.5}, {-.5, 2}, {0,3}, {6,2}, {0,0}, {1,1} };

    printf("Teste com algoritmo CONVEXHULL\n");
    for(size_t i = 0; i < 11; ++i)
        printf("Is interior? (%4.1f,%4.1f) %s\n", q[i].x, q[i].y, polygon_point_interior_convexhull (p, 6, q[i]) ? "Yes" : "No");

    printf("\n");
    printf("Teste com algoritmo GENERICO\n");
    for(size_t i = 0; i < 11; ++i)
        printf("Is interior? (%4.1f,%4.1f) %s\n", q[i].x, q[i].y, polygon_point_interior(p, 6, q[i]) ? "Yes" : "No");

    return 0;
}

