#include <stdio.h>

int memoing[10] = {-1};

int main(void)
{
    for(size_t i = 0 ; i < 10; i++)
    {
        fprintf(stdout, "%d\n", memoing[i]);
    }
    return 0;
}
