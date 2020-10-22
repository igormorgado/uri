#include <stdio.h>

int main(void)
{
    double x0, y0, n;
    double xi;
    double yi;
    double ti;
    size_t g[1000000] = {0};


    scanf("%lf %lf %lf\n", &x0, &y0, &n);
    size_t c = 0;
    for (size_t i = 0; i < (size_t)n; ++i)
    {
        scanf("%lf %lf %lf\n", &xi, &yi, &ti);
        double dx = xi - x0;
        double dy = yi - y0;
        if ((dx * dx + dy * dy) < (ti*ti))
            g[c++] = i+1;
    }
    if(c == 0)
    {
        printf("-1\n");
    }
    else
    {
        for(size_t i = 0; i < c-1; ++i)
            printf("%zu ", g[i]);
        printf("%zu\n", g[c-1]);
    }

    return 0;
}
