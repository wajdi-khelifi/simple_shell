#include "simple_shell_lib.h"

/**
 * main - Entry point of the simple shell program.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 * @env: An array of strings containing the environment variables.
 *
 * This function serves as the entry point for the simple shell program. It
 * calls the `run_shell` function to start the shell, and then returns 0 upon
 * successful execution.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	run_shell(env);
	return (0);
}
