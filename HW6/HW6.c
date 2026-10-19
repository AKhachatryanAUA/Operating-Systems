#include <stdio.h>
#include <stddef.h>

struct OriginalStruct {
    char a;
    int b;
    double c;
};

struct OptimizedStruct {
    double c;
    int b;
    char a;
};

#pragma pack(push, 1)
struct Packed1Struct {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push, 2)
struct Packed2Struct {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct Packed4Struct {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

int main(void) {
    printf("ASSIGNMENT 1\n");
    char v_char;
    short v_short;
    int v_int;
    double v_double;

    printf("sizeof(char):   %zu bytes | Address: %p\n", sizeof(v_char), (void *)&v_char);
    printf("sizeof(short):  %zu bytes | Address: %p\n", sizeof(v_short), (void *)&v_short);
    printf("sizeof(int):    %zu bytes | Address: %p\n", sizeof(v_int), (void *)&v_int);
    printf("sizeof(double): %zu bytes | Address: %p\n\n", sizeof(v_double), (void *)&v_double);

    printf("ASSIGNMENT 2\n");
    struct OriginalStruct orig;
    printf("Original Struct (char, int, double):\n");
    printf("  sizeof(struct): %zu bytes\n", sizeof(orig));
    printf("  &a: %p (offset %zu)\n", (void *)&orig.a, offsetof(struct OriginalStruct, a));
    printf("  &b: %p (offset %zu)\n", (void *)&orig.b, offsetof(struct OriginalStruct, b));
    printf("  &c: %p (offset %zu)\n\n", (void *)&orig.c, offsetof(struct OriginalStruct, c));

    struct OptimizedStruct opt;
    printf("Optimized Struct 1\n");
    printf("  sizeof(struct): %zu bytes\n", sizeof(opt));
    printf("  &c: %p (offset %zu)\n", (void *)&opt.c, offsetof(struct OptimizedStruct, c));
    printf("  &b: %p (offset %zu)\n", (void *)&opt.b, offsetof(struct OptimizedStruct, b));
    printf("  &a: %p (offset %zu)\n\n", (void *)&opt.a, offsetof(struct OptimizedStruct, a));

    printf("ASSIGNMENT 3\n");
    struct Packed1Struct p1;
    printf("#pragma pack(1):\n");
    printf("  sizeof(struct): %zu bytes\n", sizeof(p1));
    printf("  &a: %p (offset %zu)\n", (void *)&p1.a, offsetof(struct Packed1Struct, a));
    printf("  &b: %p (offset %zu)\n", (void *)&p1.b, offsetof(struct Packed1Struct, b));
    printf("  &c: %p (offset %zu)\n\n", (void *)&p1.c, offsetof(struct Packed1Struct, c));
    return 0;
}