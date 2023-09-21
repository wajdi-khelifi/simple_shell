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
void add_path(char *a, char *exe, char **environ)
{
	char *path_var = _getenv("PATH", environ);
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
