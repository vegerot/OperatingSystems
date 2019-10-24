#include<stdlib.h>
#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h>
#include<semaphore.h>
#define BUFF_SIZE 20 
char buffer[BUFF_SIZE]; 
int nextIn = 0;
int nextOut = 0;
//used for synchronization – producer should be blocked if the buffer is full 
sem_t empty_slots;
//used for synchronization – consumer should be blocked if the buffer is empty 
sem_t full_slots;
//used for mutual exclusion – enforces mutual exclusion on the shared buffer 
sem_t mutex;

void Put(char item) {
    sem_wait(&empty_slots);
    sem_wait(&mutex);
    buffer[nextIn] = item;
    nextIn = (nextIn + 1) % BUFF_SIZE; 
    sem_post(&mutex);
    sem_post(&full_slots);
    printf("threadID: %lu: Producing %c ...\n", pthread_self(), item);
}

void * Producer() {
    int i;
    for(i = 0; i < 15; i++) {
        sleep(rand()%6);
        Put((char)('A'+ i % 26)); 
    }
}

void Get(char item) {
    sem_wait(&full_slots);
    sem_wait(&mutex);
    item = buffer[nextOut];
    nextOut = (nextOut + 1) % BUFF_SIZE; 
    sem_post(&mutex);
    sem_post(&empty_slots);
    printf("threadID: %lu: Consuming %c ...\n", pthread_self(), item);

}

void * Consumer() {
    int i;
    char item;
    for(i = 0; i < 15; i++) {
        sleep(rand()%6);
        Get(item); 
    }
}


int main() {
    /* Initialize semaphores */
    sem_init(&mutex, 0, 1);
    sem_init(&empty_slots, 0, BUFF_SIZE);
    sem_init(&full_slots, 0, 0);
    pthread_t pid, pid1, pid2, cid, cid1,cid2;
    pthread_create(&cid, NULL, Consumer, NULL);
    pthread_create(&pid, NULL, Producer, NULL); 
    pthread_create(&pid1, NULL, Producer, NULL); 
    pthread_create(&cid1, NULL, Consumer, NULL);
    pthread_create(&pid2, NULL, Producer, NULL); 
    pthread_create(&cid2, NULL, Consumer, NULL);
    // create more consumer & producer threads.
    pthread_join(pid, NULL); 
    pthread_join(cid, NULL);
    pthread_join(pid1, NULL); 
    pthread_join(cid1, NULL);
    pthread_join(pid2, NULL); 
    pthread_join(cid2, NULL);
}
