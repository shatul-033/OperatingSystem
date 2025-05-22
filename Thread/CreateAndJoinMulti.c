#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

void* threadFunction(void* arg) {
    int id = *((int*)arg);
    printf("Thread %d is running...\n", id);
    sleep(1);  // Simulate work
    printf("Thread %d finished.\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    // Create threads
    for(int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;  // Thread ID (1-based)
        if(pthread_create(&threads[i], NULL, threadFunction, &ids[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    // Join threads
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");

    return 0;
}
