#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#ifndef __cplusplus
# include <stdbool.h>
#endif

#ifndef M_PI
# define M_PI   3.14159265358979323846
#endif

#define EPS     1e-9

struct point
{
    double x;
    double y;
};

struct circle
{
    struct point center;
    double radius;
};

struct line
{
    double a;
    double b;
    double c;
};


/* Check "equality" of two scalars */
static bool
equal(double a, double b)
{
    return fabs(a - b) < EPS;
}


/* Check if scalar is near zero */
static bool
is_zero(double a)
{
    return (fabs(a) < EPS);
}


static double
dotp_diff(struct point a, struct point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}


/* 2D dot product */
static double
dotp(struct point a, struct point b)
{
    return a.x * b.x + a.y * b.y;
}


static struct point
point_sub(struct point a, struct point b)
{
    return (struct point){ a.x - b.x, a.y - b.y};
}


static struct point
point_add(struct point a, struct point b)
{
    return (struct point){a.x + b.x, a.y + b.y};
}


static struct point
point_mul(struct point a, double k)
{
    return (struct point){ a.x * k , a.y * k};
}


static struct point
point_median(struct point a, struct point b)
{
    return point_mul(point_add(b, a), .5);
}



/* 2D euclidian distance */
static double
euclidian_distance(struct point a, struct point b)
{
    return (sqrt ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}


/* Given two points return line a, b,c coeffs */
static struct line
point_to_line(struct point p1, struct point p2)
{
    struct line r;
    if (p1.x == p2.x)
    {
        r.a = 1;
        r.b = 0;
        r.c = -p1.x;
    }
    else
    {
        r.b = 1;
        r.a = - (p1.y - p2.y) / (p1.x - p2.x);
        r.c = - (r.a  * p1.y) / (r.b  - p1.y);
    }
    return r;
}


/* Check if lines are parallel */
static bool
line_is_parallel(struct line l1, struct line l2)
{
    return (equal(l1.a, l2.a) && equal(l1.b, l2.b));
}


/* Check if lines are concurrent */
static bool
line_is_concurrent(struct line l1, struct line l2)
{
    return (line_is_parallel(l1, l2) && equal(l1.c, l2.c));
}


/* Given a Point and a tangent return line a,b,c coeffs */
static struct line
point_tangent_to_line(struct point p, double m)
{
    struct line r;
    r.a = -m;
    r.b = 1;
    r.c = -(r.a * p.x + r.b * p.y);
    return r;
}


/* Returns point coordinates wher two line intersect
 * point is NAN when lines are parellel
 * point is INFINITY when lines are concurrent
 */
static struct point
line_intersection(struct line l1, struct line l2)
{
    struct point p;
    if (line_is_parallel(l1, l2))
    {
        p.x = NAN;
        p.y = NAN;
    }
    else if (line_is_concurrent(l1, l2))
    {
        p.x = INFINITY;
        p.y = INFINITY;
    }
    else
    {
        p.x = (l2.b * l1.c - l1.b*l2.c) / (l2.a * l1.b - l1.a * l2.b);
        if (is_zero (l1.b))
            p.y = - (l2.a * p.x + l2.c) / l2.b;
        else
            p.y = - (l1.a * p.x + l1.c) / l1.b;
#if 0
        if (is_zero (p.x))
            p.x = 0.0;
        if (is_zero (p.y))
            p.y = 0.0;
#endif
    }
    return p;
}

/* Return a orthogonal line to l over point p */
static struct line
line_orthogonal(struct line l, struct point p)
{
    struct line lo;

    if (is_zero (l.b))          /* Vertical line */
    {
        lo.a = 0;
        lo.b = 1;
        lo.c = -p.y;
    }
    else if (is_zero (l.a))     /* Horizontal Line */
    {
        lo.a = 1;
        lo.b = 0;
        lo.c = -p.x;
    }
    else
    {
        lo = point_tangent_to_line (p, l.b/l.a);
    }
    return lo;
}



static struct circle
point_to_circle(struct point a, struct point b, struct point c)
{
    struct circle C = { {0.0, 0.0}, 0.0};
    struct point ab = point_sub(a, b);          // x12, y12
    struct point ba = point_sub(b, a);          // x21, y21
    struct point ac = point_sub(a, c);          // x13, y12
    struct point ca = point_sub(c, a);          // x31, y31

    double sacx = a.x * a.x - c.x * c.x;         // sx13
    double sacy = a.y * a.y - c.y * c.y;         // sy13
    double sbax = b.x * b.x - a.x * a.x;         // sx21
    double sbay = b.y * b.y - a.y * a.y;         // sy21

    double f = (sacx * ab.x + sacy * ab.x + sbax * ac.x + sbay * ac.x)
                / (2.0 * (ca.y * ab.x - ba.y * ac.x));

    double g = (sacx * ab.y + sacy * ab.y + sbax * ac.y + sbay * ac.y)
                / (2.0 * (ca.x * ab.y - ba.x * ac.y));

    double t = -(a.x * a.x) - (a.y *a.y) - 2.0 * g * a.x - 2.0 * f * a.y;

    C.center.x = -g;
    C.center.y = -f;

    double dr = C.center.x * C.center.x + C.center.y * C.center.y - t;
    C.radius = sqrt(dr);

    return C;
}

static bool
circle_point_is_interior(struct circle c, struct point p)
{
    return (dotp(c.center, p) < (c.radius * c.radius));
}

static void
circle_print(struct circle c)
{
    printf("(%f, %f)(%f)\n", c.center.x, c.center.y, c.radius);
}

static void
point_print(struct point p)
{
    printf("(%f, %f)\n", p.x, p.y);
}

static void
line_print(struct line l)
{
    printf("(%f, %f, %f)\n", l.a, l.b, l.c);
}


static double
double_rand(double min, double max)
{
    double scale = rand() / (double)RAND_MAX;
    return min + scale * (max - min);
}

static double
uniform(void)
{
    return rand() / (double)RAND_MAX;
}

int main(void) {

    // struct point p = {0.0, 0.0};
    // struct point q = {1.0, 1.0};
    // struct point r = {1.0, -1.0};

    // for (size_t i = 0; i < 100000000; ++i)
    // {
    //     point_to_circle ((struct point){uniform(), uniform()},
    //                      (struct point){uniform(), uniform()},
    //                      (struct point){uniform(), uniform()});
    // }

    // for (size_t i = 0; i < 1000000; ++i)
    // {
    //     point_to_circle ((struct point){uniform(), uniform()},
    //                      (struct point){uniform(), uniform()},
    //                      (struct point){uniform(), uniform()});
    // }

    // struct circle C = point_to_circle(p, q, r);
    // struct circle D = point_to_circle2(p, q, r);
    // circle_print(C);
    // circle_print(D);

    // struct point ppq = point_add(p, q);
    // struct point pmq = point_sub(p, q);

    // printf("dotp pmq: %f\n", dotp(pmq, pmq));
    // printf("dotqdiff: %f\n", dotp_diff(p, q));

    // printf("p + q: %f %f", ppq.x, ppq.y);
    // printf("p - q: %f %f", pmq.x, pmq.y);

    return 0;

    // int N;
    // while(scanf("%d\n", &N), N != 0)
    // {

    //     struct point p[N];
    //     for(size_t i = 0; i < N ; ++i)
    //     {
    //         scanf("%lf %lf\n", &p[i].x, &p[i].y);
    //     }

#if 0
        for(size_t i = 0; i < N ; ++i)
        {
            printf("%zu: %f %f\n", i, p[i].x, p[i].y);
        }
        printf("\n");
#endif
    // }

    // return 0;
}
