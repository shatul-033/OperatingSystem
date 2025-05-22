#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a new process

    if (pid < 0) {
        // fork failed
        printf("Failed to create a process.\n");
        return 1;
    }

    else if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Child is doing some work...\n");
        sleep(2);  // Simulate work
        printf("Child Process is terminating.\n");
        exit(0);   // Terminates child process
    }

    else {
        // Parent process
        printf("Parent Process: PID = %d\n", getpid());
        printf("Parent is waiting for child to finish...\n");
        wait(NULL);  // Waits for the child process to terminate
        printf("Child finished. Parent is terminating.\n");
    }

    return 0;  // Terminates parent process
}
