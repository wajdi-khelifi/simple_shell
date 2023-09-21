#include "simple_shell_lib.h"
/**
* add_path - adds path to command
* @path: path of command
* @cmd: user entered command
*
* Return: buffer containing command with path on success
* NULL on failure
*/
char *add_path(char *path, char *cmd)
{
	char *buf;
	size_t i = 0, j = 0;

	if (cmd == 0)
		cmd = "";

	if (path == 0)
		path = "";

	buf = malloc(sizeof(char) * (strlen(path) + strlen(cmd) + 2));
	if (!buf)
		return (NULL);

	while (path[i])
	{
		buf[i] = path[i];
		i++;
	}
	if (path[i - 1] != '/')
	{
		buf[i] = '/';
		i++;
	}
	while (cmd[j])
	{
		buf[i + j] = cmd[j];
		j++;
	}
	buf[i + j] = '\0';
	return (buf);

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

/**
* print_env - prints the environment string to stdout
*
* Return: 0
*/
void print_env(void)
{
	int x = 0;
	char **env = env;

	while (env[x])
	{
		write(STDOUT_FILENO, (const void *)env[x], strlen(env[x]));
		write(STDOUT_FILENO, "\n", 1);
		x++;
	}
}
