#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFF_SIZE 20

typedef struct {
  char buffer[BUFF_SIZE];
  int nextIn;
  int nextOut;
} shared_data;

shared_data *shm, *s;
char sem_name1[] = "mutex";
char sem_name2[] = "empty_slots";
char sem_name3[] = "full_slots";
sem_t *empty_slots;
sem_t *full_slots;
sem_t *mutex;

void Put(char item) {
  int semVal;
  sem_getvalue(empty_slots, &semVal);
  printf("empty_slots = %i\n", semVal);
  printf("waiting for empty slots...");
  sem_wait(empty_slots);
  printf("waiting for mutex...");
  sem_wait(mutex);
  s->buffer[s->nextIn] = item;
  s->nextIn = (s->nextIn + 1) % BUFF_SIZE;
  sem_post(mutex);
  printf("pid %d: Producing %c ...\n", getpid(), item);
  sem_post(full_slots);
}

void Producer() {
  int i;
  for (i = 0; i < 10; i++) {
    sleep(rand() % 3);
    Put((char)('A' + i % 26));
  }
}
int main() {
  // Create and initialize the semaphores
  mutex = sem_open(sem_name1, O_CREAT, 0644, 1);
  full_slots = sem_open(sem_name3, O_CREAT, 0644, 0);
  empty_slots = sem_open(sem_name2, O_CREAT, 0644, 10);
  // Create a key for the segment
  key_t key;
  key = 1234; // NOTE: you can use ftok() function to generate the key
  // create the segment
  int shmid;
  printf("IPC_CREAT = %i\n", IPC_CREAT);
  printf("IPC_CREAT | 0666= %i\n", IPC_CREAT | 0666);
  if ((shmid = shmget(key, sizeof(shared_data), IPC_CREAT | 0666)) < 0) {
    perror("Shmget");
    exit(1);
  }
  // attach to the segment
  if ((shm = (shared_data *)shmat(shmid, NULL, 0)) == (shared_data *)-1) {
    perror("Shmat");
    exit(1);
  }
  s = shm;
  s->nextIn = 0;
  Producer();
  // detach from the segment
  shmdt((void *)shm);
}
