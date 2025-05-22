#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *fun1();
void *fun2();

pthread_mutex_t first_mutex,second_mutex;
//pthread_mutex_t r1,r2,r3;

int main() {
    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);

    pthread_t T1,T2;
    pthread_create(&T1, NULL, fun1, NULL);
    pthread_create(&T2, NULL, fun2, NULL);

    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    printf("Thread joined\n");
    return 0;
}
void *fun1()
{
    printf("T1 trying to acquire first mutex\n");
    pthread_mutex_lock(&first_mutex);
    printf("T1  to acquire first mutex\n");
    sleep(1);
    printf("T1 trying to acquire second mutex\n");
    pthread_mutex_lock(&second_mutex);
    printf("T1  to acquire second mutex\n");

}
void *fun2()
{
    printf("T2 trying to acquire second mutex\n");
    pthread_mutex_lock(&second_mutex);
    printf("T1  to acquire second mutex\n");
    sleep(1);
    printf("T1 trying to acquire first mutex\n");
    pthread_mutex_lock(&first_mutex);
    printf("T1  to acquire first mutex\n");

}