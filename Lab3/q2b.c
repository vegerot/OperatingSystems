

#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
int b() {
  int x = 1;
  if (fork() == 0)
    printf("printf1: x=%d\n", ++x);
  printf("printf2: x=%d\n", --x);
  return 0;
}

int main() {
  printf("b:\n");
  b();
  return 0;
}
