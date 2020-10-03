#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

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

struct line_parametric
{
    double x;
    double a;
    double y;
    double b;
};



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
angle_origin(struct point p)
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
dotp_diff(struct point p1, struct point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
};

/* 2D dot product */
static double
dotp(struct point p1, struct point p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

/* 2D euclidian distance */
static double
euclidian_distance(struct point p1, struct point p2)
{
    return (sqrt ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));

}



/*
 *
 * POINT FUNCTIONS
 *
 */

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

/* Check if point is in the origin */
static bool
point_is_origin(struct point p)
{
    return (is_zero(p.x) && is_zero(p.y));
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



/* Return a parametric line given two points */
static struct line_parametric
point_to_line_parametric(struct point p1, struct point p2)
{
    struct line_parametric lp;
    lp.a = p2.x - p1.x;
    lp.x = p1.x;
    lp.b = p2.y - p1.y;
    lp.y = p1.y;

    return lp;
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

static struct point
point_median(struct point a, struct point b)
{
    return point_mul(point_add(b, a), .5);
}



/*
 *
 * LINE FUNCTIONS
 *
 */

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


/* Returns a line parallel to l over point p */
static struct line
line_parallel(struct line l, struct point p)
{
    struct line lp;
    lp.a = l.a;
    lp.b = l.b;
    lp.c = -(l.a * p.x + l.b * p.y);
    return lp;
}


/* Return a orthogonal line to l over point p */
static struct line
line_orthogonal(struct line l, struct point p)
{
    struct line lo;

    if (is_zero (l.b))          /* Vertical line */
    {
#if 0
        struct point po;
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
        struct point po;
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


/* Returns the angle between two lines */
static double
line_angle(struct line l1, struct line l2)
{
    return (l1.b * l2.a - l1.a * l2.b)/(l1.a * l2.a + l1.b * l2.b);
}


/* Return the nearest point over the line l to a given point p */
static struct point
line_nearest_point(struct line l, struct point p)
{
    struct line lo = line_orthogonal(l, p);
    struct point pn = line_intersection(l, lo);
    return pn;
}


/* Return a point given a parametric line l and a scalar parameter t */
static struct point
line_parametric_points(struct line_parametric l, double t)
{
    struct point p;
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
static struct circle
point_to_circle2(struct point a, struct point b, struct point c)
{
    struct circle C = { {0.0, 0.0}, 0.0};

    struct line lab = point_to_line(a, b);
    struct line lac = point_to_line(a, c);
    struct line lab_ortho = line_orthogonal(lab, point_median(a, b));
    struct line lac_ortho = line_orthogonal(lac, point_median(a, c));
    C.center = line_intersection(lab_ortho, lac_ortho);
    C.radius = sqrt(dotp_diff(C.center, a));
    return C;
}



/*
 * Check if point p is interior to circle c
 */
static bool
circle_point_is_interior(struct circle c, struct point p)
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
triangle_area(struct point a, struct point b, struct point c)
{
    return .5 * a.x * (b.y - c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);
}


/*
 *
 * Transformations
 *
 */

static void
translate(struct point p, struct point *pn, size_t n)
{
    for(size_t i = 0; i < n; ++i)
    {
        pn[i].x -= p.x;
        pn[i].y -= p.y;
    }
}

static void
rotate(struct point *p, size_t n, double a)
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


int main(void)
{
    struct point p = { 1.0, 0.0 };
    printf("(x,y): (%f,%f)\n", p.x, p.y);
    rotate(&p, 1, M_PI/2);
    printf("(x,y): (%f,%f)\n", p.x, p.y);

#if 0
    struct circle c = {
        (struct point){ 0.0, 0.0 },
        1.0
    };
    struct point p = { 1.0-EPS, 0.0 };
    struct point q = { 0.0,     1.0 };
    struct point l = { 1.0,     0.0 };

    printf("Is interior:  %s\n", circle_point_is_interior(c, p) ? "YES":"NO");
    printf("Is interior:  %s\n", circle_point_is_interior(c, q) ? "YES":"NO");
    printf("Is interior:  %s\n", circle_point_is_interior(c, l) ? "YES":"NO");
#endif
    return 0;
}

