#include "simple_shell_lib.h"

/**
 * execute_command - Execute a command in a new process.
 * @args: An array of strings containing the command and its arguments.
 * @nb: The line number where the command is executed.
 *
 * This function creates a new process to execute the specified command with
 * the given arguments. If the command is not found in the PATH directories,
 * it prints an error message including the line number.
 */
void execute_command(char **args, int nb)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr, "hsh: %d: %s: not found\n", nb, args[0]);
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("Error");
	else
		waitpid(pid, &status, 0);
}
