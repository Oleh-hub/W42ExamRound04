#include <unistd.h> // fork
#include <stdio.h> // printf fflush
#include <sys/wait.h> // waitpid

int main(void)
{
    int pid = fork();
    int n;
    int status;
    printf("n address for:%p %i\n", &n, pid);
    printf("status address for:%p %i\n", &status, pid);

    if (pid == 0)
        n = 1;
    else
        n = 6;
    
    int i;
    if (pid != 0)
        waitpid(pid, &status, 0);
    for (i = n; i < n + 5; i++)
    {
        printf("%i ", i);
        fflush(stdout);
    }
    if (pid != 0)
        printf("\n");
}