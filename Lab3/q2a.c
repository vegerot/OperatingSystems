
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
int a() {
  fork();
  printf("hello\n");
  return 0;
}

int main() {
  printf("a:\n");
  a();
  return 0;
}
