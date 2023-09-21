#include "simple_shell_lib.h"

/**
 * main - Entry point of the simple shell program
 * @argc: Number of command-line arguments (unused)
 * @argv: Array of command-line argument strings (unused)
 * @env: Array of environment variables
 *
 * Return: Always 0 (successful execution)
 */
int main(int argc, char **argv, char **env)
{
	char *input;
	char **args;
	int nb = 1;

	(void)argc;
	(void)argv;
	input = NULL;

	while (1)
	{
		printf("$ ");
		input = read_input();
		if (input == NULL)
		{
			printf("\n");
			exit(1);
		}
		if (feof(stdin))
		{
			printf("\n");
			free(input);
			exit(0);
		}
		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}

		args = parse_input(input);
		if (args[0] != NULL)
		{
			execute_command(args, nb, env);
		}
		free(input);
		input = NULL;
		free(args);
	}

	return (0);
}
