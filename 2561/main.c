#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

struct rect
{
    int x0;
    int y0;
    int x1;
    int y1;
};
typedef struct rect Rect;

static bool
aabb(Rect r0, Rect r1)
{
    bool res = ((r0.x0 <= r1.x1) &&
                (r1.x0 <= r0.x1) &&
                (r0.y0 <= r1.y1) &&
                (r1.y0 <= r0.y1));
    return res;
}


int main(void) {

    Rect R[2] = {0};
    while (scanf("%d %d %d %d\n", &R[0].x0, &R[0].y0, &R[0].x1, &R[0].y1) != EOF)
    {
        scanf("%d %d %d %d\n", &R[1].x0, &R[1].y0, &R[1].x1, &R[1].y1);

        Rect RI = {max (R[0].x0, R[1].x0),
                   max (R[0].y0, R[1].y0),
                   min (R[0].x1, R[1].x1),
                   min (R[0].y1, R[1].y1)};
        int WI = abs(RI.x1 - RI.x0);
        int HI = abs(RI.y1 - RI.y0);
        int A = WI * HI;

        if (!aabb(R[0], R[1]))
        {
        // printf("R0 (x0,y0,x1,y1) (%2d, %2d, %2d, %2d) --  R1 (x0,y0,x1,y1) (%2d, %2d, %2d, %2d) ---",
        //         R[0].x0, R[0].y0, R[0].x1, R[0].y1, R[1].x0, R[1].y0, R[1].x1, R[1].y1);
            printf("inexistente\n");
        }
        else if (WI == 0 && HI == 0)
        {
        // printf("RI (x0,y0) (%2d, %2d) -- (x1, y1) (%2d, %2d) - (WI, HI, AR) (%2d, %2d, %2d) --- ",
        //         RI.x0, RI.y0, RI.x1, RI.y1, WI, HI, A);
            printf("ponto\n");
        }
        else if (WI == 0 || HI == 0)
        {
        // printf("RI (x0,y0) (%2d, %2d) -- (x1, y1) (%2d, %2d) - (WI, HI, AR) (%2d, %2d, %2d) --- ",
        //         RI.x0, RI.y0, RI.x1, RI.y1, WI, HI, A);
            printf("linha\n");
        }
        else if (0 < A && A <= 10)
        {
        // printf("RI (x0,y0) (%2d, %2d) -- (x1, y1) (%2d, %2d) - (WI, HI, AR) (%2d, %2d, %2d) --- ",
        //         RI.x0, RI.y0, RI.x1, RI.y1, WI, HI, A);
            printf("adequada\n");
        }
        else if (A > 10)
        {
        // printf("RI (x0,y0) (%2d, %2d) -- (x1, y1) (%2d, %2d) - (WI, HI, AR) (%2d, %2d, %2d) --- ",
        //         RI.x0, RI.y0, RI.x1, RI.y1, WI, HI, A);
            printf("grande\n");
        }
        else
        {
        // printf("RI (x0,y0) (%2d, %2d) -- (x1, y1) (%2d, %2d) - (WI, HI, AR) (%2d, %2d, %2d) --- ",
        //         RI.x0, RI.y0, RI.x1, RI.y1, WI, HI, A);
            printf("WAT?!?\n");
        }
    }

    return 0;
}
