#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>

int main(int argc, char** argv, char** envp)
{
    /*while(*envp)
        printf("%s\n",*envp++);*/
    int pid;
    pid = fork();
    if (pid == -1)
    {
        perror("ERROR – fork \n");
        exit(0);
    }
    else if (pid == 0)
    {
        printf("Child process with pid = %d, and Parent pid = %d\n", getpid(), getppid());
        sleep(5);
        printf("After sleeping. Child process with pid = %d, and Parent pid = %d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        printf("Parent process with pid = %d, and Parent pid = %d\n", getpid(), getppid());
        printf("Parent exiting now\n");
        exit(0);
    }
    return 0;
}