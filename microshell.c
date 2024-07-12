
		// for (int j = 0; envp[j]; j++)
		// 	printf("%s\n", envp[j]);
		// printf("%d\n", i);
// #include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return 1;
}

int cd(char **argv, int i)
{
	(void) argv;

	if (i != 2)
		return err("error: cd: bad arguments\n");
	if (chdir(argv[1]) == -1)
		return err("error: cd: cannot change directory to "), err(argv[1]), err("\n");
	return 0;
}

int	exec(char **argv, int i, char **envp)
{
	int has_pipe = argv[i] && !strcmp(argv[i], "|");
	int status = 0;
	int fd[2];

	if (!has_pipe && !strcmp(argv[0], "cd"))
		return cd(argv, i);

	if (has_pipe && pipe(fd) == -1)
		return err("error: fatal\n");
	
	int pid = fork();
	if (!pid)
	{
		if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return err("error: fatal\n");
		if (has_pipe && !strcmp(argv[0], "cd"))
		return cd(argv, i);
		argv[i] = 0;
		execve(argv[0], argv, envp);
		return err("error: cannot execute "), err(argv[0]), err("\n");
	}
	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		return err("error: fatal\n");
	return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv, char **envp)
{
	int		status = 0;
	int 	i = 0;

	if (argc > 1)
	{
		while (argv[i] && argv[++i])
		{
			argv += i;
			i = 0;
			while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
				i++;
			if (i)
				exec(argv, i, envp);
		}
	}
	return status;
}
