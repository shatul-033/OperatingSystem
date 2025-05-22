#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5  // Buffer size

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;  // Counts empty slots
sem_t full;   // Counts full slots
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item;
    for(int i = 0; i < 10; i++) {
        item = rand() % 100;

        sem_wait(&empty);             // Wait for empty slot
        pthread_mutex_lock(&mutex);   // Lock buffer

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // Unlock buffer
        sem_post(&full);              // Signal that an item is produced

        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for(int i = 0; i < 10; i++) {
        sem_wait(&full);              // Wait for full slot
        pthread_mutex_lock(&mutex);   // Lock buffer

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // Unlock buffer
        sem_post(&empty);             // Signal that an item was consumed

        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
