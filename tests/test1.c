#include <stdio.h> // printf
#include <string.h> // strcmp
#include <unistd.h> // execve, fork, pipe, dup2, close, chdir
#include <stdlib.h> // free

int err(char *str)
{
    while (*str)
        write(2, str++, 1);
    return 1;   
}

int cd(char **argv, int i)
{
	if (i != 2)
		return (err("error: cd: bad arguments\n"));
	if (chdir(argv[1]) == -1)
		return (err("error: cd: cannot change directory to path_to_change\n"));
	{ //debug
		char *path = getcwd(NULL, 0);
		printf("%s\n", path);
		free(path);
	}
	return (0);
}

int exec(char **argv, int i)
{
	int has_pipe;

	has_pipe = argv[i] && !strcmp(argv[i], "|");
	if (!has_pipe && !strcmp(*argv, "cd"))
		return (cd(argv, i));


	return (0);
}

int main(int argc, char **argv)
{
	int i;
	int status;

	status = 0;
	if (argc > 1)
	{
		i = 0;
		while (argv[i] && argv[++i])
		{
			argv += i;
			i = 0;
			while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
				i++;
			if (i)
				status = exec(argv, i);
		}
	}
	return (status);
}