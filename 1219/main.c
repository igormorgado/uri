#include <stdio.h>
#include <math.h>

#define M_PI		3.14159265358979323846	/* pi */

int main(void) {
    double a = 0, b = 0, c = 0;
    double p = 0, A = 0, LR = 0, LA = 0, SR = 0, SA = 0, S = 0, V = 0, R = 0;

    while(scanf("%lf %lf %lf\n", &a, &b, &c) != EOF)
    {
        // Triangle semiperimeter
        p = (a + b + c) / 2.0;
        // Triangle area (Heron's formula)
        A = sqrt(p * (p - a) * (p - b) * (p - c));

        // Large circle radius
        LR = (a * b * c) / (4.0 * A);
        // Large circle area
        LA = M_PI * LR * LR;

        // Small circle radius
        SR = sqrt((p - a) * (p - b) * (p - c) / p);
        // Small circle area;
        SA = M_PI * SR * SR;

        R = SA;
        V = A - R;
        S = LA - A;

        printf("%.4f %.4f %.4f\n", S, V, R);

    }

    return 0;
}
