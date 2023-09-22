#include "simple_shell.h"
/**
 * find_path - Finds the PATH environment variable
 *
 * Description:
 * searches the environment variables to locate the PATH variable.
 *
 * Return: A pointer to the PATH string if found, otherwise NULL.
 */
char *find_path(void)
{
	int i = 0;
	char **env = environ, *path = NULL;

	while (*env)
	{
		if (_strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env;
			while (*path && i < 5)
			{
				path++;
				i++;
			}
			return (path);
		}
		env++;
	}
	return (NULL);
}

/**
 * append_path - Appends a command to a given path
 * @path: The base path
 * @command: The command to append to the path
 *
 * Description:
 * Concatenates the provided command to the end of the given path,
 * ensuring that the path is properly formatted.
 *
 * Return: Allocated string containing the concatenated path and command,
 * or NULL on allocation failure.
 */
char *append_path(char *path, const char *command)
{
	char *buf;
	size_t i = 0, j = 0;

	if (command == 0)
		command = "";

	if (path == 0)
		path = "";

	buf = malloc(sizeof(char) * (_strlen(path) + _strlen(command) + 2));
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
	while (command[j])
	{
		buf[i + j] = command[j];
		j++;
	}
	buf[i + j] = '\0';
	return (buf);
}
/**
 * test_paths - Tests if a command exists in multiple paths
 * @path: An array of paths to search in
 * @command: The command to search for in the paths
 *
 * Description:
 * tests if the specified command exists within any of the given
 * paths.
 * It iterates through each path in the array and appends the command to
 * each path,
 * checking if the resulting file exists and is executable.
 *
 * Return: A pointer to the full path of the command if found and executable,
 * or NULL if command is not found in any of the paths or is not executable.
 */
char *test_paths(char **path, const char *command)
{
	int i = 0;
	char *output = NULL;

	while (path[i])
	{
		output = append_path(path[i], command);
		if (access(output, F_OK | X_OK) == 0)
			return (output);
		free(output);
		i++;
	}
	return (NULL);
}
