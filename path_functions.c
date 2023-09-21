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
	char **env = environ;
	char *path = NULL;

	while (*env)
	{
		if (_strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;
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
 * concatenates the provided command to the end of the given path,
 * ensuring that the path is properly formatted.
 *
 * Return:allocated string containing the concatenated path and command,
 * or NULL on allocation failure.
 */
char *append_path(char *path, char *command)
{
	size_t path_len = _strlen(path);
	size_t command_len = _strlen(command);
	size_t total_len = path_len + command_len + 2;

	char *buf = malloc(total_len);

	if (!buf)
	{
		return (NULL);
	}
	strcpy(buf, path);
	if (path_len == 0 || path[path_len - 1] != '/')
	{
		strcat(buf, "/");
	}
	strcat(buf, command);

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
		output = append_path(path[i], (char *) command);
		if (access(output, F_OK | X_OK) == 0)
			return (output);
		free(output);
		i++;
	}
	return (NULL);
}
