#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <assert.h>

#ifndef __cplusplus
# include <stdbool.h>
#endif

#ifndef M_PI
# define M_PI   3.14159265358979323846
#endif

#define EPS     1e-9

struct line
{
    double a;
    double b;
    double c;
};
typedef struct line Line;

struct line_p
{
    double x;
    double a;
    double y;
    double b;
};
typedef struct line_p  LineP;

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

union segment
{
    struct
    {
        double x1;
        double y1;
        double x2;
        double y2;
    };
    struct
    {
        Vec2 u;
        Vec2 v;
    };
    double e[4];
};
typedef union segment Segment;

union rect
{
    struct
    {
        double x;
        double y;
        double w;
        double h;
    };
    struct
    {
        Vec2 origin;
        Vec2 length;
    };
    double e[4];
};
typedef union rect Rect;

union circle
{
    struct
    {
        double x;
        double y;
        double r;
    };
    struct
    {
        Vec2 center;
        double radius;
    };
    double e[3];
};
typedef union circle Circle;


/* Scalar functions
 *************************************************************/


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


/* Return the angle of a point related to origin */
static double
angle_origin(Vec2 p)
{
#if 0
    double angle;
    if (fabs (p.x) < EPS)
    {
        if      (fabs (p.y) < EPS)  angle = 0;
        else if (p.y < 0)           angle = 3 * PI/2;
        else                        angle = PI / 2;
    }
    else
    {
        angle = atan(p.y / p.x);
        if      (p.x < 0)           angle += PI;
        else if (p.y < 0)           angle += 2*PI;
    }
    return angle;
#endif
    return atan2(p.y, p.x);
}



/*
 *
 * Vector functions
 *
 */

static double
dotp_diff(Vec2 p1, Vec2 p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
};

/* 2D dot product */
static double
dotp(Vec2 p1, Vec2 p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

/* 2D euclidian distance */
static double
euclidian_distance(Vec2 p1, Vec2 p2)
{
    return (sqrt ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));

}



/*
 *
 * Vector functions
 *
 */

/* Returns a + b */
static Vec2
v2_add(Vec2 a, Vec2 b)
{
    return (Vec2){a.x + b.x, a.y + b.y};
}


/* Returns a - b */
static Vec2
v2_sub(Vec2 a, Vec2 b)
{
    return (Vec2){ a.x - b.x, a.y - b.y};
}


/* Return k * a */
static Vec2
v2_mul(Vec2 a, double k)
{
    return (Vec2){ a.x * k , a.y * k};
}


/* Inplace a += b */
static void
v2_addi(Vec2 * a, Vec2 * b)
{
    a->x += b->x;
    a->y += b->y;
}

/* Inplace a <= - b */
static void
v2_subi(Vec2 * a, Vec2 * b)
{
    a->x -= b->x;
    a->y -= b->y;
}


/* Inplace k * a */
static void
v2_muli(Vec2 * a, double k)
{
    a->x *= k;
    a->y *= k;
}


/*
 *
 * Point functions
 *
 */

/* Check if point is in the origin */
static bool
point_is_origin(Point p)
{
    return (is_zero(p.x) && is_zero(p.y));
}

/* Given two points return line a, b,c coeffs */
static Line
point_to_line(Point p1, Point p2)
{
    Line r;
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


/* Given a Point and a tangent return line a,b,c coeffs */
static Line
point_tangent_to_line(Point p, double m)
{
    Line r;
    r.a = -m;
    r.b = 1;
    r.c = -(r.a * p.x + r.b * p.y);
    return r;
}



/* Return a parametric line given two points */
static LineP
point_to_line_parametric(Point p1, Point p2)
{
    LineP lp;
    lp.a = p2.x - p1.x;
    lp.x = p1.x;
    lp.b = p2.y - p1.y;
    lp.y = p1.y;

    return lp;
}


static Circle
point_to_circle(Point a, Point b, Point c)
{
    Circle C = { 0.0, 0.0, 0.0};
    Point ab = v2_sub(a, b);          // x12, y12
    Point ba = v2_sub(b, a);          // x21, y21
    Point ac = v2_sub(a, c);          // x13, y12
    Point ca = v2_sub(c, a);          // x31, y31

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

    double dr = C.x * C.x + C.y * C.y - t;
    C.r = sqrt(dr);

    return C;
}

static Point
point_median(Point a, Point b)
{
    return v2_mul(v2_add(b, a), .5);
}



/*
 *
 * LINE FUNCTIONS
 *
 */

/* Check if lines are parallel */
static bool
line_is_parallel(Line l1, Line l2)
{
    return (equal(l1.a, l2.a) && equal(l1.b, l2.b));
}


/* Check if lines are concurrent */
static bool
line_is_concurrent(Line l1, Line l2)
{
    return (line_is_parallel(l1, l2) && equal(l1.c, l2.c));
}


/* Returns a line parallel to l over point p */
static Line
line_parallel(Line l, Point p)
{
    Line lp;
    lp.a = l.a;
    lp.b = l.b;
    lp.c = -(l.a * p.x + l.b * p.y);
    return lp;
}


/* Return a orthogonal line to l over point p */
static Line
line_orthogonal(Line l, Point p)
{
    Line lo;

    if (is_zero (l.b))          /* Vertical line */
    {
#if 0
        Point po;
        // po.x = p.x + 1;
        po.x = -l.c/l.a;
        po.y = p.y;
        lo = point_to_line(p, po);
#endif
        lo.a = 0;
        lo.b = 1;
        lo.c = -p.y;
    }
    else if (is_zero (l.a))     /* Horizontal Line */
    {
#if 0
        Point po;
        po.x = p.x;
        // po.y = p.y + 1;
        po.y = -l.c/l.b;
        lo = point_to_line(p, po);
#endif
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
static Point
line_intersection(Line l1, Line l2)
{
    Point p;
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


/* Returns the angle between two lines */
static double
line_angle(Line l1, Line l2)
{
    return (l1.b * l2.a - l1.a * l2.b)/(l1.a * l2.a + l1.b * l2.b);
}


/* Return the nearest point over the line l to a given point p */
static Point
line_nearest_point(Line l, Point p)
{
    Line lo = line_orthogonal(l, p);
    Point pn = line_intersection(l, lo);
    return pn;
}


/* Return a point given a parametric line l and a scalar parameter t */
static Point
line_parametric_points(LineP l, double t)
{
    Point p;
    p.x = l.x + l.a * t;
    p.y = l.y + l.b * t;
    return p;
}



/*
 *
 * CIRCLE FUNCTIONS
 *
 */

// SLOW - more readeable.
static Circle
point_to_circle2(Point a, Point b, Point c)
{
    Circle C = { 0.0, 0.0, 0.0};

    Line lab = point_to_line(a, b);
    Line lac = point_to_line(a, c);
    Line lab_ortho = line_orthogonal(lab, point_median(a, b));
    Line lac_ortho = line_orthogonal(lac, point_median(a, c));
    C.center = line_intersection(lab_ortho, lac_ortho);
    C.r = sqrt(dotp_diff(C.center, a));
    return C;
}



/*
 * Check if point p is interior to circle c
 */
static bool
circle_point_is_interior(Circle c, Point p)
{
#if 0
    double dist = 0;
    dist = euclidian_distance( p, c.center);
    if ( (dist < c.radius) || (fabs (dist - c.radius) <= EPS))
        return true;
    else
        return false;
#endif
    return (dotp_diff(c.center, p) < (c.radius * c.radius));
}



/*
 *
 * Triangle functions
 *
 */
static double
triangle_area(Point a, Point b, Point c)
{
    return .5 * a.x * (b.y - c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);
}

static double
polygon_area(Vec2 *p, size_t n)
{
    assert(n > 2);
    double result = 0;
    for (size_t i = 0; i < n; ++i)
        result += p[i].x * p[(i+1)%n].y - p[(i+1)%n].x * p[i].y;

    return .5 * result;
}

/*
 *
 * Transformations
 *
 */

static void
translate(Point p, Point *pn, size_t n)
{
    for(size_t i = 0; i < n; ++i)
    {
        pn[i].x -= p.x;
        pn[i].y -= p.y;
    }
}

static void
rotate(Point *p, size_t n, double a)
{
    for (size_t i = 0; i < n; ++i)
    {
        double px_tmp = p[i].x;
        p[i].x = p[i].x * cos(a) - p[i].y * sin(a);
        //p[i].y = p[i].x * sin(a) + p[i].y * cos(a);
        p[i].y = px_tmp * sin(a) + p[i].y * cos(a);
    }
}

#if 0
duasretas Tangentes(ponto p1, circulo c){
    duasretas dr; double alfa,beta,d,b; ponto p0; circulo c1; int nrot;
    c1.raio = c.raio;  c1.pc.x = c.pc.x-p1.x; c1.pc.y = c.pc.y-p1.y;
    p0.x =0;  p0.y = 0;  nrot = 0;
    while (((c1.pc.x < 0) && (fabs(c1.pc.x) > QZERO)) ||
            ((c1.pc.y < 0) && (fabs(c1.pc.y) > QZERO))) {
        nrot++;  c1.pc = RotacaoHoraria(c1.pc, PI/2);
    }
    d = DistPontos(p0,c1.pc);   b = sqrt(d*d-c1.raio*c1.raio);
    alfa = atan(c1.raio/b);
    if (nrot > 1) nrot = nrot -2; // Mesma tangente
    if (fabs(c1.pc.x) <= QZERO) beta = PI/2*(nrot-1);
    else                        beta = atan(c1.pc.y/c1.pc.x) -PI/2*nrot;
    if (fabs(cos(beta-alfa)) <= QZERO) {
        dr.r1.a = 1;  dr.r1.b = 0;  dr.r1.c = -p1.x;
    }
    else dr.r1 = PontoTangenteParaReta(p1,sin(beta-alfa)/cos(beta-alfa));
    if (fabs(cos(beta+alfa)) <= QZERO) {
        dr.r2.a = 1;  dr.r2.b = 0;  dr.r2.c = -p1.x;
    }
    else dr.r2 = PontoTangenteParaReta(p1,sin(beta+alfa)/cos(beta+alfa));
    return dr;
}

doispontos PontosTangencia(ponto p1, circulo c){
    duasretas dr;  doispontos dp;
    dr = Tangentes(p1,c);
    dp.p1 = PontoMaisProximo(c.pc,dr.r1);
    dp.p2 = PontoMaisProximo(c.pc,dr.r2);
    if (fabs(dp.p1.x) < QZERO) dp.p1.x = 0;   // Para evitar -0.00
    if (fabs(dp.p1.y) < QZERO) dp.p1.y = 0;   // Para evitar -0.00
    if (fabs(dp.p2.x) < QZERO) dp.p2.x = 0;   // Para evitar -0.00
    if (fabs(dp.p2.y) < QZERO) dp.p2.y = 0;   // Para evitar -0.00
    return dp;
}

ponto PontoMaisProximo(ponto p1, reta r1){
    ponto p2;  boolponto bp;
    reta r2;
    if (fabs(r1.b)<= QZERO){
        p2.x = -r1.c;  p2.y = p1.y;
    }
    else if (fabs(r1.a)<= QZERO){
        p2.x = p1.x;  p2.y = -r1.c;
    }
    else{
        r2 = PontoTangenteParaReta(p1,1/r1.a);
        bp = PontoIntersecao(r1,r2);
        if (!bp.ret) cout<<"Erro"<<endl;
        p2 = bp.p;
    }
    return p2;
}

#endif

static void
circle_print(Circle c)
{
    printf("(%f, %f)(%f)\n", c.x, c.y, c.r);
}

static void
point_print(Point p)
{
    printf("(%f, %f)\n", p.x, p.y);
}

static void
line_print(Line l)
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


static bool
circol(Circle c0, Circle c1)
{
    double dx = c0.x - c1.x;
    double dy = c0.y - c1.y;
    double dst = sqrt(dx * dx + dy * dy);
    return (dst < c0.r + c1.r);
}


/* Given 2 2d vectors, return a rect */
static Rect
vec_to_rect(Vec2 v0, Vec2 v1)
{
    return (Rect) {v0.x, v0.y, v1.x - v0.x, v1.y - v0.y};
}


static double
orientationf(Vec2 v0, Vec2 v1, Vec2 v2)
{
    return (v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y);
}

static int
orientation(Vec2 v0, Vec2 v1, Vec2 v2)
{
    double s = (v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y);
    if      (s > 0) return  1; // counterclockwise
    else if (s < 0) return -1; // clockwise
    else            return  0; // colinear
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

/* Return true if bounding boxes overlap, false otherwise */
static bool
aabb_rect(Rect r0, Rect r1)
{
    bool res = ((fmax (r0.x, r0.x+r0.w) >= fmin (r1.x, r1.x+r1.w)) &&
                (fmax (r1.x, r1.x+r1.w) >= fmin (r0.x, r0.x+r0.w)) &&
                (fmax (r0.y, r0.y+r0.h) >= fmin (r1.y, r1.y+r1.h)) &&
                (fmax (r1.y, r1.y+r1.h) >= fmin (r0.y, r0.y+r0.h)));
    return res;
}

/* Return true if bounding boxes overlap, false otherwise */
static bool
aabb(Rect r0, Rect r1)
{
    bool res = ((r0.x < r1.x + r1.w) &&
                (r1.x < r0.x + r0.w) &&
                (r0.y < r1.y + r1.h) &&
                (r1.y < r0.y + r0.h));
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


struct compute
{
    size_t i;   // index
    double a;   // angle
    double d;   // dist
};


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


/* Find closed polygon from s and stores in p : O( 2n log(n) + 4n + 2 ) and memory O(2n)*/
static void
polygon_closed(const Vec2 * const s, Vec2 * p, const size_t n)
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
polygon_is_convexhull(Vec2 *p, size_t n)
{
    int t = orientation (p[n-2], p[n-1], p[0]);
    if (t != orientation (p[n-1], p[0], p[1]))
        return false;
    for(size_t i = 0; i < n-2; i++)
        if (t != orientation(p[i], p[i+1], p[i+2]))
            return false;
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


static void
vecsort(Vec2 *p, size_t e, size_t d)
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
        vecsort (p, e, j);
        vecsort (p, i, d);
    }
}


/* Find convex hull from src and stores in dst : O( 2n log(n) + 4n + 2 ) and memory O(3n)*/
static void
convexhull2(const Vec2 * const src, const size_t src_elems,
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

    vecsort(src_cpy, 1, src_elems - 1);

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


/* Find convex hull from src and stores in dst : O( 2n log(n) + 4n + 2 ) and memory O(3n)*/
static size_t
convexhull(const Vec2 * const src, const size_t src_elems,
           Vec2 * dst, size_t * dst_elems)
{
    /* Copy SRC since it's const */
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
    Vec2 * pcpy = malloc(src_elems * sizeof *pcpy);
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
    size_t stk_pos = 1;
    for (size_t j = 0; j <= src_elems; ++j)
    {
        while(orientation(dst[stk_pos - 1], dst[stk_pos], src_cpy[j%src_elems]) <= 0)
            stk_pos--;

        stk_pos++;
        dst[stk_pos].x = src_cpy[j%src_elems].x;
        dst[stk_pos].y = src_cpy[j%src_elems].y;
    }

    *dst_elems = stk_pos;
    free(src_cpy);

    return stk_pos;
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

    for(size_t i = 0; i < n; ++i)
    {
        printf("%zu: ", i);
        point_print(cvxhl[i]);
    }

#if 0
    Vec2 s[12] = {{2, 3}, {7, 4}, {8, 3}, {10, 10}, {8, 5},
                  {2, 4}, {7, 2}, {2, 6}, {5, 0}, {11, 8},
                  {2, 8}, {4, 6}};
    Vec2 p[6] = { {1,1}, {4,1}, {5,2}, {4,4}, {2,4}, {1,3} };
    Vec2 q[8] = { {3,2}, {3,1}, {1,4}, {0,2}, {0,3}, {6,2}, {0,0}, {1,1} };
    Vec2 r[12] = {};
    polygon_closed(s, r, 12);

    for(size_t i = 0; i < 8; ++i)
        printf("Is interior? (%4.1f,%4.1f) %s\n", q[i].x, q[i].y, polygon_point_interior_convexhull (p, 6, q[i]) ? "Yes" : "No");

    printf("\n");
    for(size_t i = 0; i < 8; ++i)
        printf("Is interior? (%4.1f,%4.1f) %s\n", q[i].x, q[i].y, polygon_point_interior(p, 6, q[i]) ? "Yes" : "No");

    printf("Point in segment(Y)? %s\n", point_in_segment (q[1], p[0], p[1]) ? "Yes" : "No");
    printf("Point in segment(Y)? %s\n", point_in_segment (p[0], p[0], p[1]) ? "Yes" : "No");
    printf("Point in segment(N)? %s\n", point_in_segment (q[0], p[0], p[1]) ? "Yes" : "No");

    for(size_t i = 0; i < 7; ++i)
        printf("Is interior? %s\n", polygon_point_interior_convexhull (p, 6, q[i]) ? "Yes" : "No");

    printf("Is convex hull(Y)? %s\n", polygon_is_convexhull(p, 6) ? "Yes" : "No");
    printf("Is convex hull(N)? %s\n", polygon_is_convexhull(r, 12) ? "Yes" : "No");

    const size_t n = 3;
    Vec2 T[3] = {{1, 1}, {4, 3}, {0, 5}};
    Vec2 Y[3] = {{1, 1}, {0, 5}, {4, 3}};

    printf("%f\n", polygon_area(T, n));
    printf("%f\n", polygon_area(Y, n));
    const size_t n = 13;
    Vec2 s[13] = {{2, 3}, {7, 4}, {8, 3}, {10, 10}, {8, 5},
                  {2, 4}, {7, 2}, {2, 6}, {5, 0}, {11, 8},
                  {2, 1}, {2, 8}, {4, 6}};

    for(size_t j = 0; j < n+1; ++j)
        point_print(s[j % n]);

    Vec2 p[13];
    polygon_closed(s, p, n);

    printf("\n");
    for(size_t j = 0; j < n+1; ++j)
        point_print(p[j % n]);
#endif


    return 0;
}

