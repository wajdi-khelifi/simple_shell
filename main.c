#include "simple_shell_lib.h"

/**
 * run_shell - Run a simple shell program.
 *
 * This function implements a basic shell that continuously prompts the user
 * for input, reads the input, parses it into command and arguments, and
 * executes the commands. It also keeps track of the line number for error
 * reporting.
 */
void run_shell(void)
{
	char *input;
	char **args;
	int nb = 1;

	while (1)
	{
		printf("$ ");
		input = read_input();
		if (input == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (strcmp(input, "exit\n") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		args = parse_input(input);
		if (args[0] != NULL)
		{
			execute_command(args, nb);
		}
		free(input);
		free(args);
		nb++;
	}
}

/**
 * main - Entry point of the simple shell program.
 *
 * This function serves as the entry point for the simple shell program. It
 * calls the `run_shell` function to start the shell, and then returns 0 upon
 * successful execution.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int main(void)
{
	run_shell();
	return (0);
}
