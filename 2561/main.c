#include <stdio.h>
#include <stdlib.h>

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


        // Caso 1. Não ha interseccao
        // Caso 2. Lado ou altura == 0 -> Linha
        // Caso 3. Lado e alture == 0 -> ponto
        // Caso 4. Lado e altura diferente de 0 -> Area
        //
        if(WI == 0 && HI == 0)

        printf("%d %d %d %d %d\n", RI.x0, RI.y0, RI.x1, RI.y1,
               (abs(RI.x1 - RI.x0) * abs(RI.y1 - RI.y0)));
    }

    return 0;
}
