#include <stdio.h>

#ifndef __cplusplus
# include <stdbool.h>
#endif

struct rect
{
    double x0;
    double y0;
    double x1;
    double y1;
};
typedef struct rect Rect;

static bool
aabb(Rect r0, Rect r1)
{
    bool res = ((r0.x0 < r1.x1) &&
                (r1.x0 < r0.x1) &&
                (r0.y0 < r1.y1) &&
                (r1.y0 < r0.y1));
    return res;
}


int main(void) {
    struct rect R[2] = {};
    scanf("%lf %lf %lf %lf\n", &R[0].x0, &R[0].y0, &R[0].x1, &R[0].y1);
    scanf("%lf %lf %lf %lf\n", &R[1].x0, &R[1].y0, &R[1].x1, &R[1].y1);

    bool res = aabb(R[0], R[1]);
    if (res)
        printf("1\n");
    else
        printf("0\n");
    return 0;
}
