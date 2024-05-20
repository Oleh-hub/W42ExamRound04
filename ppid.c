#include <stdio.h> // printf
#include <unistd.h> // fork, getppid, getpid
#include <sys/wait.h> // waitpid

int main(void)
{
    int pid = fork();
    waitpid(pid, NULL, 0);
    printf("pid: %d, ppid: %i\n", getpid(), getppid());
}