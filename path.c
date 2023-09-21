#include "simple_shell_lib.h"

/**
 * add_path - Add the path of the executable to the command.
 * @a: The command or executable.
 * @exe: The buffer to store the full path.
 * @environ: The environment variables.
 *
 * This function constructs the full path to the specified executable by
 * searching for it in the directories listed in the PATH environment variable.
 */
void add_path(char *a, char *exe, char **env)
{
	char *path_var = get_env("PATH", env);
	struct stat st;
	char *token;

	if (path_var == NULL)
	{
		perror("PATH environment variable not found");
		exit(1);
	}

	token = strtok(path_var, ":");
	while (token != NULL)
	{
		strcpy(exe, token);
		strcat(exe, "/");
		strcat(exe, a);

		if (stat(exe, &st) == 0)
		{
			return;
		}

		token = strtok(NULL, ":");
	}

	exe[0] = '\0';
}

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
