#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

sem_t mutex;

void* thread(void* arg)
{
    printf("Starting new thread\n");
    //wait
    printf("thread id = %lu\n", pthread_self());
    printf("*mutex = %lu\n", mutex);
    sem_wait(&mutex);
    printf("\nEtnered\n");

    printf("thread id = %lu\n", pthread_self());
    printf("*mutex = %lu\n", mutex);
    //critical section
    sleep(4);

    //signal
    printf("\nExiting\n");
    sem_post(&mutex);
    printf("thread id = %lu\n", pthread_self());
    printf("*mutex = %lu\n", mutex);
    int num=0;
    int* retVal; 
    retVal=&num;
    return retVal;
}

int main(void)
{

    sem_init(&mutex, 0, 1);
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_create(&t1, NULL, thread, NULL);
    sleep(2);
    pthread_create(&t2, NULL, thread, NULL);
    sleep(1);
    pthread_create(&t3, NULL, thread, NULL);
    printf("waiting to join t1: %lu\n", t1);
    pthread_join(t1, NULL);
    printf("waiting to join t2: %lu\n", t1);
    pthread_join(t2, NULL);
    printf("waiting to join t3: %lu\n", t1);
    pthread_join(t3, NULL);
    sem_destroy(&mutex);
    return 0;
}
