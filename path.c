#include "simple_shell_lib.h"

/**
 * add_path - Add the path of the executable to the command.
 * @a: The command or executable.
 * @exe: The buffer to store the full path.
 * @env_path: The value of the PATH environment variable.
 *
 * This function constructs the full path to the specified executable by
 * searching for it in the directories listed in the PATH environment variable.
 */
void add_path(char *a, char *exe, char *env_path)
{
	char *token;
	char *path_copy;
	struct stat st;

	path_copy = strdup(env_path);
	if (path_copy == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		snprintf(exe, MAX_INPUT_SIZE, "%s/%s", token, a);

		if (stat(exe, &st) == 0)
		{
			free(path_copy);
			return;
		}

		token = strtok(NULL, ":");
	}

	exe[0] = '\0';
	free(path_copy);
}
