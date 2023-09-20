#include "simple_shell_lib.h"
/**
 * calculate_program - Find a program in the PATH.
 * @data: A pointer to the program's data
 * Return: 0 if found, error code otherwise
 */
int calculate_program(prog *data)
{
	int i = 0, ret_code = 0;
	char **dir;

	if (!data->cmd)
		return (2);

	if (data->cmd[0] == '/' || data->cmd[0] == '.')
		return (examine(data->cmd));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->cmd);
	if (!data->tokens[0])
		return (2);

	dir = calculate_path(data);

	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dir[i]; i++)
	{
		dir[i] = str_concat(dir[i], data->tokens[0]);
		ret_code = examine(dir[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(dir[i]);
			free_array_of_pointers(dir);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(dir);
	return (ret_code);
}

/**
 * calculate_path - Tokenize the PATH into directories.
 * @data: A pointer to the program's data
 * Return: An array of path directories
 */
char **calculate_path(prog *data)
{
	int i = 0;
	int calculate = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			calculate++;
	}

	tokens = malloc(sizeof(char *) * calculate);

	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * examine - Check if a file exists not a directory has execution permissions.
 * @all_path: Pointer to the full file name
 * Return: 0 on success, or an error code if it does not exist or has issues.
 */
int examine(char *all_path)
{
	struct stat sb;

	if (stat(all_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(all_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	errno = 127;
	return (127);
}
int examine(char *full_path);
