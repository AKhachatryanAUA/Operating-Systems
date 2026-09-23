#include <stdio.h>
#include "math_utils.h"

int main(void) {
    int val = 5;
    int result = square(val);
    printf("The square of %d is %d\n", val, result);
    return 0;
}