#include "simple_shell_lib.h"

/**
 * execute_command - Execute a command in a new process.
 * @args: An array of strings containing the command and its arguments.
 * @nb: The line number where the command is executed.
 *
 * This function creates a new process to execute the specified command with
 * the given arguments. If the command is not found in the PATH directories,
 * it prints an error message including the line number.
 */
void execute_command(char **args, int nb)
{
	pid_t pid;
	int status;
	int i;

	pid = fork();
	if (pid == 0)
	{
		for (i = 0; args[i] != NULL; i++)
		{
			handle_special(args[i]);
		}

		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr, "hsh: %d: %s: not found\n", nb, args[0]);
			perror("Error");
			exit(1);
		}
	}
	else if (pid < 0)
		perror("Error");
	else
		waitpid(pid, &status, 0);
}

/**
 * handle_special - Escape special characters in a string.
 * @str: The string to process.
 *
 * Description:
 *   This function takes a string as input and escapes the following special
 *   characters: ", ', `, \, *, &, #. It modifies the input string in place.
 *
 * Return: None (void)
 */
void handle_special(char *str)
{
	int len = strlen(str);
	int i, j = 0;
	char *escaped = malloc(2 * len + 1);

	if (escaped == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < len; i++)
	{
		char c = str[i];

		if (c == '"' || c == '\'' || c == '`' || c == '\\' || c == '*' || c == '&' || c == '#')
		{
			escaped[j++] = '\\';
		}

		escaped[j++] = c;
	}

	escaped[j] = '\0';

	strcpy(str, escaped);
	free(escaped);
}
