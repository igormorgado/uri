#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t alignment = 16;
    uint8_t sz = 23;
    uint8_t p1 = sz + alignment - 1;
    uint8_t p2 = ~(alignment - 1);

    printf("%u %u %u\n", p1, p2, 255 - (alignment -1));
    printf("%u\n", p1 & p2);


    return 0;
}

    11111111
alignment       00010000
       sz       00010001
 sz+align       00100001
sz+align-1      00100000
align-1         00001111
~(align-1)      11110000
