#include "simple_shell.h"

/**
 * exit_cmd - handles the exit command
 * @command: tokenized command
 * @line: input read from stdin
 *
 * Return: no return
 */
void exit_cmd(char **command, char *line)
{
	if (line != NULL)
	{
		free(line);
	}
	if (command != NULL)
	{
		free_buffers(command);
	}
	exit(EXIT_SUCCESS);
}
