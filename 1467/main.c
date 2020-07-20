#include <stdio.h>

int main(void) { 
    const char OutcomesStr[8] = { '*', 'C', 'B', 'A', 'A', 'B', 'C', '*' };
    char buf[6];
    while (fread(buf, 1, sizeof(buf), stdin) == sizeof(buf)) {
        putchar(OutcomesStr[((buf[0]-48)<<2) + ((buf[2]-48)<<1) + (buf[4]-48)]);
        putchar('\n');
    }
    return 0;
}

