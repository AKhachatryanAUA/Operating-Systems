#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void assignment_0(void) {
    fork();
    fork();
    fork();
}

void assignment_1(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        execl("/bin/ls", "ls", NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent process done\n");
    }
}

void assignment_2(void) {
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    } else if (pid1 == 0) {
        execl("/bin/ls", "ls", NULL);
        perror("execl ls failed");
        exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    } else if (pid2 == 0) {
        execl("/bin/date", "date", NULL);
        perror("execl date failed");
        exit(1);
    }

    wait(NULL);
    wait(NULL);
    printf("Parent process done\n");
}

void assignment_3(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        execl("/bin/echo", "echo", "Hello from the child process", NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent process done\n");
    }
}

void assignment_4(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        execl("/usr/bin/grep", "grep", "main", "test.txt", NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent process completed\n");
    }
}

int main(void) {
    return 0;
}