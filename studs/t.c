#include <stdio.h>

typedef struct v2
{
    int x;
    int y;
} Vec;

int main()
{
    Vec V[3] = { {1,2}, {3,4}, {4,5}};
    Vec U = V[2];
    printf("%d %d\n", U.x, U.y);
    printf("%d %d\n", V[2].x, V[2].y);
    return 0;
}
