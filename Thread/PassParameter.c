#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void *thread_function(void *arg);
int num[2]={3,5};

int  main()
{
pthread_t a_thread;
void *result;
pthread_create(&a_thread,NULL,thread_function,(void*)num);
pthread_join(a_thread,&result);
printf("Inside main program\n");
printf("Thread rreturned:%s\n",(char*)result);
}
// printf("Thread returned: %s\n", (char*)result);
// free(result); // না হলে memory leak হবে

void *thread_function(void *arg){
printf("Inside Thread\n");
int *x=arg;
int sum=x[0]+x[1];
printf("Sum is %d\n",sum);
}
// void *thread_function(void *arg) {
//     int *x = arg;
//     int sum = x[0] + x[1];
//     printf("Sum is %d\n", sum);

//     // Dynamic allocation
//     char *res = malloc(50);
//     sprintf(res, "Sum was %d", sum);
//     return (void *)res;
// }
