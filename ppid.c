#include <stdio.h> // printf
#include <unistd.h> // fork, getppid, getpid
#include <sys/wait.h> // waitpid

int main(void)
{
    int pid = fork();
    
    int res = wait(NULL);
    if (res == -1)
        printf("No children porcesses in this fork's branch\n");
    else
        printf("Process %d has finished its execution\n", res);
        // sleep(1);
    // waitpid(pid, NULL, 0);
    printf("pid: %d, ppid: %i\n", getpid(), getppid());
}