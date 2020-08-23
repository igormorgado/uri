#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10
#define MAGIC 0xdeadbeef

int main()
{
    unsigned int * fatores = malloc (sizeof(*fatores) * N);
    for (int i = 0; i < N; i++)
        fatores[i] = MAGIC;
}

