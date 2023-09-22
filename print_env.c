#include "simple_shell.h"

/**
 * print_env - Prints the environment variables to stdout
 *
 * Description:
 * This function prints the environment variables to the standard output.
 */
void print_env(void)
{
	int i = 0;
	char **env = environ;

	while (env[i])
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
