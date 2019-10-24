#include<stdio.h>

#include<sys/types.h>
#include<unistd.h>

#include<stdlib.h>

int main(int argc, char** argv, char** envp)
{
    pid_t i=fork();
    if (i!=0)
    {
        printf("I am the original!\n");
        //for (int j=0; 1; j+=2)
          //  printf("%i\n",j);
    } else
    {
        printf("I am the child!\n");
        //for (int j=1; 1; j+=2)
          //  printf("%i\n",j);
    }
    return 0;
}