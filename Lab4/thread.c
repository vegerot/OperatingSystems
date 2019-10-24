#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void *thread(void *vargp);
char **ptr;
int main(void) {
  const int N = 2;
  int i;
  pthread_t tid[N];
  char *msgs[N] = {"Hello from foo", "Hello from bar"};
  printf("Parent thread started with PID= %d and parent PID %d\n", getpid(),
         getppid());
  ptr = msgs;
  for (i = 0; i < N; i++)
    pthread_create(&tid[i], NULL, thread, (void *)i);
  for (i = 0; i < N; i++)
    pthread_join(tid[i], NULL);
  return 0;
}
void *thread(void *vargp) {
  int myid = (int)vargp;
  static int cnt = 0;
  printf("[%d]: %s (cnt=%d) with PID= %d and parent PID %d\n", myid, ptr[myid],
         ++cnt, getpid(), getppid());
  int i = cnt;
  // when cnt is static and  i isn't, they go one at a time
  // when cnt isn't static or  i is static  and call sleep(1), they go
  // simultaneosly but if sleep(cnt) they aren't simultaneous
  for (;; (i)++) {
    printf("[%d] %d\n", myid, i);
    sleep(cnt);
  }
  return NULL;
}
