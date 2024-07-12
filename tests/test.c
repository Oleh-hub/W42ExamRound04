#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int err (char *str)
{
    while (*str)
        write(2, str++, 1);
    return (1);
}

int exe (char **argv, int i)
{
    if (!strcmp(argv[0], "cd"))
    {
        if (i != 2)
            return(err("error: cd: bad arguments\n"));
        else if (chdir(argv[1]) == -1)
            return(err("error: cd:	cannot change directory to "), err(argv[1]), err("\n"));
    }
    {
        char *path = getcwd(NULL, 0);
        printf("hrju %s\n", path);
        free (path);
    }
    return (0);
}

int main(int argc, char **argv)
{
    int i = 0;
    int status = 0;
        
    if (argc >= 2)
    {
        while (argv[i] && argv[++i])
        {
            argv += i;
            i = 0;
            while (argv[i] && strcmp(argv[i], "|") &&
                    strcmp(argv[i], ";"))
                i++;
            status = exe(argv, i);
        }
    }
    return (status);
}