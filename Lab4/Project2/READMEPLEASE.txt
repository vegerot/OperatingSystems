I  am pretty sure this is impossible
The instructions for "Project 2—Linux Kernel Module for Listing Tasks":
"Part I—Iterating over Tasks Linearly
As illustrated in Section 3.1, the PCB in Linux is represented by the structure task struct, which is found in the <linux/sched.h> include file. In Linux, the for each process() macro easily allows iteration over all current tasks in the system:
   #include <linux/sched.h>
struct task struct *task;
for each process(task) {
/* on each iteration task points to the next task */
}
The various fields in task struct can then be displayed as the program loops through the for each process() macro."

Please see https://stackoverflow.com/a/38355606/6100005

