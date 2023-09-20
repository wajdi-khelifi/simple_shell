#include "simple_shell_lib.h"

void run_shell()
{
	char *input;
	char **args;

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
			execute_command(args);
		}
		free(input);
		free(args);
	}
}

int main(void)
{
	run_shell();
	return (0);
}
