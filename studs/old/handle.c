#include <stdio.h>
#include <stdint.h>

struct handle {
    uint32_t index;         // Offset 0
    uint16_t counter;       // Offset 32
    uint16_t type;          // Offset 48
};

union handle_u {
    struct handle fields;
    uint64_t value;
};
typedef union handle_u Handle;

uint64_t handleToInt(struct handle *handle) {
    return  ( (uint64_t)handle->type    << 48 
            | (uint64_t)handle->counter << 32 
            | (uint64_t)handle->index);
}

struct handle intToHandle(uint64_t value)
{
    struct handle handle;

    handle.index   = value & 0xffffffff;
    handle.counter = (value >> 32) & 0xffff;
    handle.type    = (value >> 48) & 0xffff;

    return handle;
}

int main(void) { 
    Handle H1;
    H1.fields.index = 1234;
    H1.fields.counter = 1;
    H1.fields.type = 5;
    printf("%d %d %d\n", H1.fields.index, H1.fields.counter, H1.fields.type);
    printf("Val: %ld\n", H1.value);

    struct handle h1 = { 1234, 1, 5 };
    uint64_t value = 0;
    struct handle h2 = {0};
    uint64_t final = 0;

    printf("%d %d %d\n", h1.index, h1.counter, h1.type);
    value = handleToInt(&h1);
    printf("Val: %ld\n", value);
    h2 = intToHandle(value);
    printf("%d %d %d\n", h2.index, h2.counter, h2.type);
    final = handleToInt(&h2);
    printf("Fin: %ld\n", final);

    printf("Idx: %u\n", value       & 0xffffffff);
    printf("Cnt: %u\n", value >> 32 & 0xffff);
    printf("Typ: %u\n", value >> 48 & 0xffff);

    return 0;
}
