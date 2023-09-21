#include "simple_shell.h"

/**
 * print_env - Prints the environment variables to stdout
 *
 * Description:
 * This function prints the environment variables to the standard output.
 */
void print_env(void)
{
	int x = 0;
	char **env = environ;

	while (env[x])
	{
		write(STDOUT_FILENO, env[x], _strlen(env[x]));
		write(STDOUT_FILENO, "\n", 1);
		x++;
	}
}
