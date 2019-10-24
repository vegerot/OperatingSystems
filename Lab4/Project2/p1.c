//#include<sched.h>
//#include <linux/sched.h>
#include<linux/sched/signal.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* the definition of `task_struct` wasn't in /usr/include/linux/sched.h like I
 * would have thought.  Rather it was in the Linux source headers (see `search.log`)
 */




int main(void)
{

    struct task_struct *task;
    for_each_process(task) {
        printf("task is: %s", task);
    printf("name: %s, state: %li, pid: %x", task->nameidata, task->state, task->pid);
    }
    return 0;
}
