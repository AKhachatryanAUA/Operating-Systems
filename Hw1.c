#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {

    printf("Problem 1\n");
    int num = 42;
    int *ptr_num = &num;
    printf("Address of 'num' via variable (&num): %p\n", (void *)&num);
    printf("Address of 'num' via pointer  (ptr_num): %p\n", (void *)ptr_num);

    *ptr_num = 100;
    printf("Modified value of 'num': %d\n\n", num);


    printf("Problem 2\n");
    

    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr_arr = arr; 
    printf("Original array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr_arr + i));
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        *(ptr_arr + i) *= 2;
    }
    printf("Modified array (pointer):  ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr_arr + i));
    }
    printf("\n");
    printf("Modified array (array name):  ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");


    printf("Problem 3\n");
    

    int x = 5, y = 15;
    printf("Before swap: x = %d, y = %d\n", x, y);
    

    swap(&x, &y);
    printf("After swap:  x = %d, y = %d\n\n", x, y);


    printf("Problem 4\n");

    
    int val = 2024;
    int *p_val = &val;
    int **pp_val = &p_val;

    printf("Value from single dereference (*p_val):   %d\n", *p_val);
    printf("Value from double dereference (**pp_val): %d\n\n", **pp_val);
 
 
    printf("Problem 5\n");
 
    
    char str[] = "Hello";
    char *str_ptr = str; 

    printf("String printed with pointer: ");
    char *temp_ptr = str_ptr;
    while (*temp_ptr != '\0') {
        putchar(*temp_ptr);
        temp_ptr++;
    }
    printf("\n");
    char *end_ptr = str_ptr;
    while (*end_ptr != '\0') {
        end_ptr++;
    }
    long count = end_ptr - str_ptr; 
    printf("Length of string is %ld characters\n", count);

    return 0;
}