
#include <stdio.h>
#include <stdlib.h>

void task1(void) {
    printf("TASK 1 \n");
    int n, sum = 0;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return;
        }
        sum += arr[i];
    }

    printf("Sum of the array: %d\n\n", sum);

    free(arr);
}

void task2(void) {
    printf("TASK 2 \n");
    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return;
    }

    int *arr = (int *)calloc(n, sizeof(int));
    if (arr == NULL) {
        return;
    }

    printf("Array after calloc:");
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    printf("Enter %d integers: ", n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return;
        }
        sum += arr[i];
    }

    printf("Updated array:");
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    double average = (double)sum / n;
    printf("Average of the array: %.1f\n\n", average);

    free(arr);
}

void task3(void) {
    printf("TASK 3 \n");
    int *arr = (int *)malloc(10 * sizeof(int));
    if (arr == NULL) {
        return;
    }

    printf("Enter 10 integers: ");
    for (int i = 0; i < 10; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return;
        }
    }

    int *temp = (int *)realloc(arr, 5 * sizeof(int));
    if (temp == NULL) {
        free(arr);
        return;
    }
    arr = temp;

    printf("Array after resizing:");
    for (int i = 0; i < 5; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n\n");

    free(arr);
}

void task4(void) {
    printf("TASK 4 \n");
    char **arr = (char **)malloc(3 * sizeof(char *));
    if (arr == NULL) {
        return;
    }

    for (int i = 0; i < 3; i++) {
        arr[i] = (char *)malloc(50 * sizeof(char));
        if (arr[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return;
        }
    }

    printf("Enter 3 strings: ");
    for (int i = 0; i < 3; i++) {
        if (scanf("%49s", arr[i]) != 1) {
            for (int j = 0; j < 3; j++) {
                free(arr[j]);
            }
            free(arr);
            return;
        }
    }

    char **temp = (char **)realloc(arr, 5 * sizeof(char *));
    if (temp == NULL) {
        for (int i = 0; i < 3; i++) {
            free(arr[i]);
        }
        free(arr);
        return;
    }
    arr = temp;

    for (int i = 3; i < 5; i++) {
        arr[i] = (char *)malloc(50 * sizeof(char));
        if (arr[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return;
        }
    }

    printf("Enter 2 more strings: ");
    for (int i = 3; i < 5; i++) {
        if (scanf("%49s", arr[i]) != 1) {
            for (int j = 0; j < 5; j++) {
                free(arr[j]);
            }
            free(arr);
            return;
        }
    }

    printf("All strings:");
    for (int i = 0; i < 5; i++) {
        printf(" %s", arr[i]);
    }
    printf("\n\n");

    for (int i = 0; i < 5; i++) {
        free(arr[i]);
    }
    free(arr);
}

void task5(void) {
    printf("TASK 5 \n");
    int n;
    printf("Enter the number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return;
    }

    int *grades = (int *)malloc(n * sizeof(int));
    if (grades == NULL) {
        return;
    }

    printf("Enter the grades: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &grades[i]) != 1) {
            free(grades);
            return;
        }
    }

    int highest = grades[0];
    int lowest = grades[0];

    for (int i = 1; i < n; i++) {
        if (grades[i] > highest) {
            highest = grades[i];
        }
        if (grades[i] < lowest) {
            lowest = grades[i];
        }
    }

    printf("Highest grade: %d\n", highest);
    printf("Lowest grade: %d\n", lowest);

    free(grades);
}

int main(void) {
    task1();
    task2();
    task3();
    task4();
    task5();
    return 0;
}