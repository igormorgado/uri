#include <stdio.h>
#include <math.h>

#ifndef PI
# define PI 3.14159265358979323846
#endif

static double
cilinder(double r, double h)
{
    return r * r * PI * h;
}

int main(void) {
    double w = 0.0;
    double h = 0.0;

    while(scanf("%lf %lf\n", &w, &h), w || h)
    {
        double r = fmin(w / 2.0, h / (2.0 * PI + 2.0));
        double s = w / (2.0 * PI);
        double ans = fmax(cilinder(r, w), cilinder(s, h - 2.0 * s));
        printf("%.3f\n", ans);
    }

    return 0;
}
