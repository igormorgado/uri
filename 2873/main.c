#include <stdio.h>
#include <math.h>

int main(void) {
    double A, B, C, D;

    while(scanf("%lf %lf %lf %lf\n", &A, &B, &C, &D), A||B||C||D)
    {
        double ans = (A/2.0 + B) * (C / D);
        printf("%.5f\n", ans);
    }

    return 0;
}
