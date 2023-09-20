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
	char *path_token;

	pid = fork();
	if (pid == 0)
	{
		char *path = getenv("PATH");

		if (path == NULL)
		{
			fprintf(stderr, "PATH environment variable not found\n");
			exit(EXIT_FAILURE);
		}
		path_token = strtok(path, ":");
		while (path_token != NULL)
		{
			if (file_exists_in_directory(args[0], path_token))
			{
				char command[MAX_INPUT_SIZE];

				snprintf(command, sizeof(command), "%s/%s", path_token, args[0]);
				if (execv(command, args) == -1)
				{
					fprintf(stderr, "hsh: %d: %s: not found\n", nb, args[0]);
					perror("Error");
				}
				exit(EXIT_FAILURE);
			}
			path_token = strtok(NULL, ":");
		}
		fprintf(stderr, "hsh: %d: %s: not found\n", nb, args[0]);
		exit(EXIT_FAILURE);
	} else if (pid < 0)
		perror("Error");
	else
		waitpid(pid, &status, 0);
}
