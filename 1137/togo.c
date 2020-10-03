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

static struct point
point_sub(struct point a, struct point b)
{
    return (struct point){ a.x - b.x, a.y - b.y};
}

/* 2D euclidian distance */
static double
euclidian_distance(struct point a, struct point b)
{
    return (sqrt ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
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

int main(void) {
    int N;
    while(scanf("%d\n", &N), N != 0)
    {

        struct point p[N];
        for(size_t i = 0; i < N ; ++i)
        {
            scanf("%lf %lf\n", &p[i].x, &p[i].y);
        }

#if 0
        for(size_t i = 0; i < N ; ++i)
        {
            printf("%zu: %f %f\n", i, p[i].x, p[i].y);
        }
        printf("\n");
#endif
    }

    return 0;
}
