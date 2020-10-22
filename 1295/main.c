#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DMAX 10000.0

struct vec2
{
    double x;
    double y;
};
typedef struct vec2 Vec2;

int __cmpx(const void *a, const void *b)
{
    Vec2 *p1 = (Vec2 *)a;
    Vec2 *p2 = (Vec2 *)b;
    if      (p1->x > p2->x) return 1;
    else if (p1->x < p2->x) return -1;
    else                    return 0;
}

int __cmpy(const void *a, const void *b)
{
    Vec2 *p1 = (Vec2 *)a;
    Vec2 *p2 = (Vec2 *)b;
    if      (p1->y > p2->y) return 1;
    else if (p1->y < p2->y) return -1;
    else                    return 0;
}

#if 0
int __cmpxy(const void *a, const void *b)
{
    Vec2 *p1 = (Vec2 *)a;
    Vec2 *p2 = (Vec2 *)b;
    if (p1->x > p2->x)
    {
        return 1;
    }
    else if (p1->x < p2->x)
    {
        return -1;
    }
    else
    {
        if(p1->y > p2->y)
        {
            return 1;
        }
        else
        {
            return -1;
        }
        return -1;
    }
}
#endif


double dist(Vec2 a, Vec2 b)
{
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double res = sqrt (dx * dx + dy * dy);
    return res;
}

double nearest_rec(Vec2 * Px, size_t a, size_t b, Vec2 * Py, size_t Py_sz)
{
    double d = 0.0;
    if((b - a + 1) < 2)
    {
        return DMAX;
    }
    else if ( b - a + 1 == 2)
    {
        return dist(Px[a], Px[b]);
    }
    else
    {
        size_t m = (a + b)/2;

        Vec2 *Py_l = malloc( sizeof *Py_l * Py_sz);
        Vec2 *Py_r = malloc( sizeof *Py_r * Py_sz);

        Vec2 *y = Py;
        Vec2 *yl = Py_l;
        Vec2 *yr = Py_r;
        size_t yl_sz = 0;
        size_t yr_sz = 0;

        /* Split Py in two groups: Left and Right */
        for(size_t i = 0; i < Py_sz; ++i)
        {
            if      (y->x < Px[m].x)
            {
                yl->x = y->x;
                yl->y = y->y;
                yl++;
                yl_sz++;
            }
            else if (y->x > Px[m].x)
            {
                yr->x = y->x;
                yr->y = y->y;
                yr++;
                yr_sz++;
            }
            y++;
        }

        double d1 = nearest_rec(Px, a, a + yl_sz - 1, Py_l, yl_sz);
        free(Py_l);

        double d2 = nearest_rec(Px, b - yr_sz + 1, b, Py_r, yr_sz);
        free(Py_r);


        d = fmin(d1, d2);
        Vec2 *S = malloc( sizeof *S * Py_sz);
        Vec2 *ps = S;
        size_t S_sz = 0;
        for (size_t i = 0; i < Py_sz; ++i)
        {
            if (((Px[m].x - d) <= Py[i].x) && (Py[i].x <= (Px[m].x + d)))
            {
                ps->x = Py[i].x;
                ps->y = Py[i].y;
                ps++;
                S_sz++;
            }
        }

        for (size_t i = 0; i < S_sz; ++i)
        {
            for (size_t j = i+1; j < i+7; ++j)
            {
                if(j >= S_sz) break;
                double dp = dist(S[i], S[j]);
                d = fmin(dp, d);
            }
        }
        free(S);
    }
    return d;
}

double nearest(const Vec2  * const p, const size_t sz_p)
{
    Vec2 *Px = malloc(sizeof *p * sz_p);
    Vec2 *Py = malloc(sizeof *p * sz_p);
    memcpy(Px, p, sizeof *p * sz_p);
    memcpy(Py, p, sizeof *p * sz_p);

    qsort(Px, sz_p, sizeof *Px, __cmpx);
    qsort(Py, sz_p, sizeof *Py, __cmpy);
    double result = nearest_rec(Px, 1, sz_p, Py, sz_p);
    return result;
}

int main(void) {

    Vec2 P[10000];
    int N = 0;
    while(scanf("%d\n", &N), N !=0)
    {
        for(size_t i = 0; i < N; ++i)
            scanf("%lf %lf\n", &P[i].x, &P[i].y);

        double d = nearest(P, N);
        if(d >= DMAX)
            printf("INFINITY\n");
        else
            printf("%.4f\n", nearest(P, N));


    }

    return 0;
}
