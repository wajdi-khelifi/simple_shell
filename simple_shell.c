#include "simple_shell.h"

/**
 * main - Entry point for the simple shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments as strings
 * @envp: Array of environment variables as strings
 *
 * Description:initializes the simple shell, reads and processes
 * user commands in a loop, and executes them accordingly.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int main(int argc, char **argv, char *envp[])
{
	struct flags flags;
	struct info info;
	char *line = NULL, *pathcommand = NULL, *path = NULL;
	size_t bufsize = 0, x = 1;
	ssize_t linesize = 0;
	char **command = NULL, **paths = NULL;
	(void)argc, (void)argv, (void)envp;
	if (argc < 1)
		return (-1);
	signal(SIGINT, handle_signal);
	initialize_flags(&flags);
	while (1)
	{
		prompt_user();
		linesize = getline(&line, &bufsize, stdin);
		if (linesize < 0)
			break;
		info.ln_count++;
		if (line[linesize - 1] == '\n')
			line[linesize - 1] = '\0';
		if (line[0] == '#')
			continue;
		command = tokenize(line);
		if (command == NULL || *command == NULL || **command == '\0')
			continue;
		if (checker(command, line))
			continue;
		path = find_path();
		paths = tokenize(path);
		pathcommand = test_paths(paths, command[0]);
		if (!pathcommand)
			fprintf(stderr, "hsh: %ld: %s: command not found\n", x, command[0]);
		else
			execute(pathcommand, command);
		x++;
	}
	if (linesize < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	cleanup(line, command, paths, pathcommand);
	return (0);
}
/**
 * initialize_flags - Initialize the flags structure.
 * @flags: Pointer to the flags structure.
 */
void initialize_flags(struct flags *flags)
{
	flags->interactive = isatty(STDIN_FILENO);
}

/**
 * cleanup - Free dynamically allocated memory.
 * @line: Pointer to the input line.
 * @command: Array of command tokens.
 * @paths: Array of path tokens.
 * @pathcommand: Pointer to the path command.
 */

void cleanup(char *line, char **command, char **paths, char *pathcommand)
{
	free_buffers(command);
	free_buffers(paths);
	free(pathcommand);
	free(line);
}

/**
 * prompt_user - prints $ to let user know the program is
 * ready to take their input
 * prints the prompt if the shell is in interactive mode
 * Return: no return
 */
void prompt_user(void)
{
	if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
		flags.interactive = 1;
	if (flags.interactive)
		write(STDERR_FILENO, "$ ", 2);
}

/**
 * execute - Executes a command entered by users
 * @pathcommand: The path to the command
 * @cmd: Array of strings containing the command and its arguments
 *
 * Description:
 * creates a child process to execute the specified command. It
 * also handles error checking and cleanup after execution.
 *
 * Return: No return value.
 */
void execute(char *pathcommand, char **cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		return;
	}
	if (child_pid == 0)
	{
		execve(pathcommand, cmd, environ);
		perror(pathcommand);
		exit(1);
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}

}
