#include <stdio.h>
#include <math.h>
#include <float.h>

#ifndef __cplusplus
# include <stdbool.h>
#endif

#define EPS     1e-9

struct point
{
    double x;
    double y;
};

struct line
{
    double a;
    double b;
    double c;
};


struct pad
{
    struct point i;
    struct point f;
    struct line l;
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

static struct line
point_tangent_to_line(struct point p, double m)
{
    struct line r;
    r.a = -m;
    r.b = 1;
    r.c = -(r.a * p.x + r.b * p.y);
    return r;
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



static struct point
line_nearest_point(struct line l, struct point p)
{
    struct line lo = line_orthogonal(l, p);
    struct point pn = line_intersection(l, lo);
    return pn;
}


static double
dist(struct point a, struct point b)
{
    return sqrt( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

int main(void) {
    int N;
    while(scanf("%d\n", &N) != EOF)
    {
        double L, H;
        scanf("%lf %lf\n", &L, &H);

        double msize = L;
        struct pad Lpad;
        struct pad Rpad;
        struct point padp = {0, 0};
        struct point prevp = {0, 0};
        size_t count=0;
        for(size_t i = 0; i < N; ++i)
        {
            double Yi, Xf, Yf;
            scanf("%lf %lf %lf\n", &Yi, &Xf, &Yf);

            if (i % 2 == 0) // Left pad
            {
                Lpad.i.x = 0;
                Lpad.i.y = Yi;

                Lpad.f.x = Xf;
                Lpad.f.y = Yf;

                Lpad.l = point_to_line(Lpad.i, Lpad.f);

                msize = fmin (L - Lpad.f.x, msize);

                if (i > 0)
                {
                    padp = line_nearest_point(Lpad.l, prevp);
                    if( (Lpad.i.x <= padp.x) && (padp.x <= Lpad.f.x) &&
                        (Lpad.i.y >= padp.y) && (padp.y >= Lpad.f.y))
                    {
                        msize = fmin (dist (prevp, padp), msize);   // padp in segment
                    }
                    else
                    {
                        msize = fmin (dist (prevp, Lpad.f), msize); // padp out of segment
                        msize = fmin (dist (prevp, Lpad.i), msize); // padp out of segment
                    }
                }

                prevp.x = Lpad.f.x;
                prevp.y = Lpad.f.y;
            }
            else            // Right pad
            {
                Rpad.i.x = L;
                Rpad.i.y = Yi;

                Rpad.f.x = Xf;
                Rpad.f.y = Yf;

                Rpad.l = point_to_line(Rpad.i, Rpad.f);

                msize = fmin (Rpad.f.x, msize);

                padp = line_nearest_point(Rpad.l, prevp);
                if( (Rpad.i.x >= padp.x) && (padp.x >= Rpad.f.x) &&
                    (Rpad.i.y >= padp.y) && (padp.y >= Rpad.f.y))
                {
                    msize = fmin (dist (padp, prevp), msize); // padp in segment
                }
                else
                {
                    msize = fmin (dist (Rpad.f, prevp), msize);  // padp out of segment
                    msize = fmin (dist (Rpad.i, prevp), msize);  // padp out of segment
                }

                prevp.x = Rpad.f.x;
                prevp.y = Rpad.f.y;
            }
        }
        printf("%.2f\n", msize);
        count++;
    }

    return 0;
}
