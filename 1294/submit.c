#include <stdio.h>
#include <math.h>

static double f(double x, double w, double h)
{
    /* a = 4, b = - 2 * (w + h), c = (w*h), d = 0 */
    return (4.0 * x * x * x) - (2.0 * w * x * x) - (2.0 * h * x * x) + (w * h * x);
}

static double df(double x, double w, double h)
{
    /* a = 12, b = -4(w+h), c = (w*h) */
    return (12.0 * x * x)    - (4.0 * w * x)     - (4.0 * h * x)     + (w * h);
}

static double ddf(double x, double w, double h)
{
    /* a = 24, b = -4(w+h) */
    return (24.0 * x)    - (4.0 * w) - (4.0 * h);
}

static double newton(double x0, double w, double h, double n)
{
    double x = x0;
    for (size_t i = 0; i < n; ++i)
        x -= df(x, w, h)/ddf(x, w, h);
    return x;
}

static void solve_poly_two(double roots[2], double a, double b, double c)
{
    double delta = b*b - 4.0 * a * c;
    double x0 = (-b + sqrt(delta))/(2.0*a);
    double x1 = (-b - sqrt(delta))/(2.0*a);

    roots[0] = x0;
    roots[1] = x1;
}

static double vertex_poly_two(double a, double b, double c)
{
    return -b / (2.0 * a);
}

int main(void) {
    double W = 0, H = 0;

    /*
     * V = x * ( W - 2*x ) * (H - 2 * x)
     * f(x) = 0 se x = 0 ou x = w/2  ou x = h/2
     */

    while(scanf("%lf %lf\n", &W, &H) != EOF)
    {
        /* 0 <= x <= min(w, h)/2  */
        double lower_bound = 0;
        double upper_bound = fmin (W, H)/2;

        // double x = newton( fmin(W + H) / 2.0, W, H, 10);
        // printf("%.3f 0.000 %.3f\n", f(x, W, H), (W+H)/4.0);

        // Coefficients of first derivative
        double a = 12.0;
        double b = -4.0 * W - 4.0 * H;
        double c = W * H;

        double roots[2];
        solve_poly_two(roots, a, b, c);

        double max_x = 0.0;
        double max_vol = 0.0;
        for (size_t i = 0; i < 2; ++i)
        {
            if ((lower_bound < roots[i]) && (roots[i] < upper_bound))
            {
                double y = f(roots[i], W, H);
                if (y > max_vol)
                {
                    max_vol = y;
                    max_x = roots[i];
                }
            }
        }
        printf("%.3f %.3f %.3f\n", max_x, lower_bound, upper_bound);
    }

    return 0;
}
