#include <stdio.h>
#include <stdint.h>

int main() { 
    uint32_t value = 0xdeadbeef;
    uint16_t  a;
    uint16_t  b;
    uint8_t   c;
    uint8_t   d;
    uint32_t  e;

    a = value & 0xffff;
    b = (value >> 16) & 0xffff;
    c = value & 0xff;
    d = (value >> 8 ) & 0xff;
    e = (( value >> 16) | (value << 16));

    printf("deadbeef\n");
    printf("beef    : %x\n", a);
    printf("dead    : %x\n", b);
    printf("ef      : %x\n", c);
    printf("be      : %x\n", d);
    printf("beefdead: %x\n", e);

    return 0;
}
