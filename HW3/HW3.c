#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void cleanup_function_1(void) {
    printf("[atexit] Cleanup function 1 executed.\n");
}

void cleanup_function_2(void) {
    printf("[atexit] Cleanup function 2 executed.\n");
}

void assignment_1(void) {
    printf("Assignment 1\n");
    
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child process PID: %d\n", getpid());
        exit(0);
    } else {
        printf("Parent process PID: %d\n", getpid());
        usleep(100000); 
    }
}

void assignment_2(void) {
    printf("Assignment 2\n");
    
    int status;
    
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    } else if (pid1 == 0) {
        printf("First Child (PID: %d) starting...\n", getpid());
        sleep(1);
        printf("First Child (PID: %d) exiting...\n", getpid());
        exit(10);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    } else if (pid2 == 0) {
        printf("Second Child (PID: %d) starting...\n", getpid());
        sleep(2);
        printf("Second Child (PID: %d) exiting...\n", getpid());
        exit(20);
    }

    printf("Parent waiting for First Child (PID: %d) using waitpid()...\n", pid1);
    waitpid(pid1, &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent: First Child exited with status code: %d\n", WEXITSTATUS(status));
    }

    printf("Parent waiting for remaining child using wait()...\n");
    pid_t finished_pid = wait(&status);
    if (WIFEXITED(status)) {
        printf("Parent: Child (PID: %d) exited with status code: %d\n", finished_pid, WEXITSTATUS(status));
    }
}

void assignment_3(void) {
    printf("Assignment 3\n");

    if (atexit(cleanup_function_1) != 0) {
        perror("Failed to register cleanup_function_1");
        exit(1);
    }
    if (atexit(cleanup_function_2) != 0) {
        perror("Failed to register cleanup_function_2");
        exit(1);
    }

    printf("Cleanup functions registered successfully.\n");
    printf("Calling exit(0) now...\n");
    
    exit(0);
}

void assignment_4(void) {
    printf("Assignment 4\n");

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    } else if (pid1 == 0) {
        printf("Child 1 (PID: %d) exiting normally with code 0...\n", getpid());
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    } else if (pid2 == 0) {
        printf("Child 2 (PID: %d) exiting with error code 5...\n", getpid());
        exit(5);
    }

    pid_t children[2] = {pid1, pid2};
    for (int i = 0; i < 2; i++) {
        int status;
        waitpid(children[i], &status, 0);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                printf("Parent: Child PID %d exited normally with status %d.\n", children[i], exit_code);
            } else {
                printf("Parent: Child PID %d exited with an error code %d.\n", children[i], exit_code);
            }
        } else {
            printf("Parent: Child PID %d terminated abnormally.\n", children[i]);
        }
    }
}

void assignment_5(int create_zombie) {
    printf("Assignment 5\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child process (PID: %d) exiting immediately...\n", getpid());
        exit(0);
    } else {
        if (create_zombie) {
            printf("Parent process (PID: %d) sleeping for 20 seconds without calling wait().\n", getpid());
            sleep(20);
            printf("Parent waking up and exiting without reaping child.\n");
        } else {
            printf("Parent process calling wait() to reap child immediately...\n");
            int status;
            wait(&status);
            printf("Child reaped successfully\n");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <assignment_number (1-5)>\n", argv[0]);
        printf("For assignment 5 zombie demo: %s 5 zombie\n", argv[0]);
        return 1;
    }

    int choice = atoi(argv[1]);
    switch (choice) {
        case 1: assignment_1(); break;
        case 2: assignment_2(); break;
        case 3: assignment_3(); break;
        case 4: assignment_4(); break;
        case 5: 
            if (argc >= 3 && strcmp(argv[2], "zombie") == 0) {
                assignment_5(1);
            } else {
                assignment_5(0);
            }
            break;
        default: printf("Invalid choice.\n"); break;
    }

    return 0;
}