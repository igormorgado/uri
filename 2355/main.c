#include <stdio.h>
#include <math.h>

int main(void) { 
    unsigned long tempo = 0;
    unsigned long BR = 0;
    unsigned long GE = 0;
    double gol_da_alemanha = 7./90.;
    double gol_do_brasil = 1./90.;

    while(scanf("%lu\n", &tempo))
    {
        if( tempo != 0 )
        {
            GE = (int)ceil ((double)tempo * gol_da_alemanha);
            BR = (int)floor((double)tempo * gol_do_brasil);
            printf("Brasil %lu x Alemanha %lu\n", BR, GE);
        } else {
            break;
        }
    }

    return 0;
}
