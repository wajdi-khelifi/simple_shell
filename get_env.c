#include "simple_shell_lib.h"

/**
 * get_env - Get the value of an environment variable.
 * @env_var: The name of the environment variable to retrieve.
 * @env: The array of environment variables.
 *
 * Return: The value of the specified environment variable,
 * or NULL if not found.
 */
char *get_env(char *env_var, char **env)
{
	int i = 0;
	char *key;

	while (env[i])
	{
		key = strtok(env[i], "=");
		if (strcmp(env_var, key) == 0)
			return (strtok(NULL, "\n"));
		i++;
	}
	return (NULL);
}
