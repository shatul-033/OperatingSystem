#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt;              // For writer access
pthread_mutex_t mutex;  // For readcount access
int readcount = 0;      // Number of readers currently reading

void *reader(void *arg) {
    int id = *((int *)arg);

    pthread_mutex_lock(&mutex);
    readcount++;
    if(readcount == 1) {
        sem_wait(&wrt);   // First reader blocks writer
    }
    pthread_mutex_unlock(&mutex);

    // Critical Section for Reader
    printf("Reader %d is reading...\n", id);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--;
    if(readcount == 0) {
        sem_post(&wrt);   // Last reader allows writer
    }
    pthread_mutex_unlock(&mutex);
}

void *writer(void *arg) {
    int id = *((int *)arg);

    sem_wait(&wrt);  // Writer waits for readers to finish

    // Critical Section for Writer
    printf("Writer %d is writing...\n", id);
    sleep(1);

    sem_post(&wrt);  // Allow next writer/reader
}

int main() {
    pthread_t rtid[5], wtid[5];
    int i;
    int rids[5] = {1,2,3,4,5};
    int wids[5] = {1,2,3,4,5};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create reader and writer threads
    for(i = 0; i < 5; i++) {
        pthread_create(&rtid[i], NULL, reader, &rids[i]);
        pthread_create(&wtid[i], NULL, writer, &wids[i]);
    }

    for(i = 0; i < 5; i++) {
        pthread_join(rtid[i], NULL);
        pthread_join(wtid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
