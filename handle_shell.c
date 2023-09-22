#include "simple_shell.h"

/**
 * handle_signal - Handles interrupt signals and prompts for input
 * @m: The signal number (unused)
 * Description:
 * Handles interrupt signals (e.g., Ctrl+C) and prints a newline
 * followed by a prompt to indicate that the shell is ready to accept input.
 * The 'm' parameter is unused in this function.
 */
void handle_signal(int m)
{
	(void)m; /* Unused parameter */
	write(STDERR_FILENO, "\n", 1);
	prompt_user();
}

/**
 * handle_builtin - Handles execution of built-in functions
 * @command: Tokenized commands
 * @line: Input read from stdin
 *
 * Description:
 * Checks if the entered command is a built-in command and
 * handles its execution if it is. It supports the env and exit commands.
 *
 * Return: 1 if executed, 0 if not
 */
int handle_builtin(char **command, char *line)
{
	struct builtin builtin = {"env", "exit"};

	if (_strcmp(*command, builtin.env) == 0)
	{
		print_env();
		return (1);
	}
	else if (_strcmp(*command, builtin.exit) == 0)
	{
		if (command[1] != NULL)
		{
			fprintf(stderr, "hsh: exit: too many arguments\n");
			return (1);
		}
		else
		{
			exit_cmd(command, line);
			return (1);
		}
	}
	return (0);
}

/**
 *checker- checks to see weather its a built in function
 *@cmd: tokenized user input
 *@buf: line drived fromgetline function
 *Return: 1 if cmd excuted 0 if cmd is not executed
 */
int checker(char **cmd, char *buf)
{
	if (handle_builtin(cmd, buf))
		return (1);
	else if (**cmd == '/')
	{
		execute(cmd[0], cmd);
		return (1);
	}
	return (0);
}

/**
 * exit_builtin - Handles the exit built-in command
 *
 * Description:
 * Exits the shell without considering any arguments.
 *
 * Return: It doesn't return; it exits the shell.
 */
void exit_builtin(void)
{
	exit(0);
}
