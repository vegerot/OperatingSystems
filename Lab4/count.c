#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int i = 0;
  for (;; i++) {
    printf("i= %i\n", i);
    sleep(1);
  }
  return 0;
}
