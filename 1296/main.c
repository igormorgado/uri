#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int cmpdouble(const void * a, const void * b)
{
    double _a = *(double*)a;
    double _b = *(double*)b;
    if ( _a > _b)
        return 1;
    else if ( _a < _b)
        return -1;
    else
        return 0;
}
int main(void) {
    double m[3] = {0};
    double A = 0.0;
    double s = 0;

    while(scanf("%lf %lf %lf\n", &m[0], &m[1], &m[2]) != EOF)
    {
        qsort(m, 3, sizeof(double), cmpdouble);
        if( (m[0] + m[1]) <= m[2])
        {
            A = -1.0;
        }
        else
        {
            s = (m[0] + m[1] + m[2]) * .5;
            A = (4.0/3.0) * sqrt( s * (s - m[0]) * (s - m[1]) * (s - m[2]));
        }
        // printf("%f %f %f\n", m[0], m[1], m[2]);
        printf("%.3f\n", A);
    }

    return 0;
}
