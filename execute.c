#include "simple_shell_lib.h"
/**
 * execute - execute a command with its entire path variables.
 * @data : a pointer to the program's data
 * Return: If success returns zero, otherwise, return -1.
 */
int execute(prog *data)
{
	int value = 0, status;
	pid_t child_pid;

	value = check(data);
	if (value != -1)
		return (value);
	value = find(data);
	if (value)
	{
		return (value);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(prog->cmd);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			value = execve(prog->tokens[0], prog->tokens, prog->env);
			if (value == -1)
				perror(prog->cmd), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
