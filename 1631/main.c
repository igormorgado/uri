#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define MAXN 100
#define EPS  1e-9

struct point
{
    double x;
    double y;
};


static struct point
point_add(struct point a, struct point b)
{
    return (struct point){a.x + b.x,  a.y + b.y};
}


static struct point
point_sub(struct point a, struct point b)
{
    return (struct point){a.x - b.x,  a.y - b.y};
}

static struct point
point_mul(struct point a, double k)
{
    return (struct point){a.x * k,  a.y * k};
}

static double
dotp(struct point a, struct point b)
{
    return a.x * b.x + a.y * b.y;
}

static double
crossp(struct point a, struct point b)
{
    return a.x * b.y - a.y * b.x;
}

static double
triangle_uarea(struct point a, struct point b, struct point c)
{
    return crossp(point_sub(b, a), point_sub(c, a));
}

static struct point
translate(struct point a, struct point b)
{
    return (struct point){a.x + b.x, a.y + b.y};
}


static double
distance_to_line(struct point a, struct point b, struct point c)
{

    struct point ab = point_sub(a, b);
    struct point cb = point_sub(c, b);

    double proj = dotp(ab, cb) / dotp(cb, cb);
    struct point p = translate(b, point_mul(cb, proj));

    return sqrt( (a.x - p.x) * (a.x - p.x) + (a.y - p.y) * (a.y - p.y));
}



int main(void) {
    int N;
    while (scanf ("%d\n", &N), N != 0)
    {

        struct point p[MAXN];
        // Read points
        for (size_t i = 0; i < N ; ++i)
            scanf ("%lf %lf\n", &p[i].x, &p[i].y);

        double dist = 100000.0; // no way to get larger than this... ;-)

        for (size_t i = 0; i < N-1; ++i)
        {
            for (size_t j = i+1; j < N; ++j)
            {
                double dist1 = 0.0;
                double dist2 = 0.0;
                for (size_t k = 0; k < N; ++k)
                {
                    if(k == i || k == j)  // skip same points
                        continue;
                    if(triangle_uarea(p[i], p[j], p[k]) > 0.0)
                        dist1 += distance_to_line(p[k], p[i], p[j]);
                    else
                        dist2 += distance_to_line(p[k], p[i], p[j]);
                }
                dist = fmin(fabs(dist1 - dist2), dist);
            }
        }
        //for (size_t i = 0; i < N ; ++i)
        //    printf ("%zu: %lf %lf\n", i, p.x[i], p.y[i]);
        printf("%.3f\n", dist);
    }

    return 0;
}
