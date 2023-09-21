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
	char *line = NULL, **pathcommand = NULL, *path = NULL;
	size_t bufsize = 0;
	ssize_t linesize = 0;
	char **command = NULL, **paths = NULL;

	(void)argc, (void)argv, (void)envp;
	signal(SIGINT, handle_signal);
	while (1)
	{
		free_buffers(command);
		free_buffers(paths);
		free(pathcommand);
		prompt_user();
		linesize = getline(&line, &bufsize, stdin);

		if (linesize < 0)
			break;
		info.ln_count++;
		if (line[linesize - 1] == '\n')
			line[linesize - 1] = '\0';
		command = tokenize(line);
		if (command == NULL || *command == NULL || **command == '\0')
			continue;
		if (checker(command, line))
			continue;
		path = find_path();
		paths = tokenize(path);
		pathcommand = test_paths(paths, command[0]);

		if (!pathcommand)
			perror(argv[0]);
		else
			execute(pathcommand, command);
	}
	if (linesize < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line);
	return (0);
}

/**
 * prompt_user - Prints a shell prompt for user input
 *
 * Description:
 * prints a shell prompt, typically '$', to indicate that the
 * shell is ready to accept user input.checks if the shell is in interactive
 * mode before printing the prompt.
 *
 * Return: No return value.
 */
void prompt_user(void)
{
	if (flags.interactive)
		write(STDERR_FILENO, "$ ", 2);
}

/**
 * execute - Executes a command entered by users
 * @cp: The path to the command
 * @cmd: Array of strings containing the command and its arguments
 *
 * Description:
 * creates a child process to execute the specified command. It
 * also handles error checking and cleanup after execution.
 *
 * Return: No return value.
 */
void execute(char *cp, char **cmd)
{
	pid_t child_pid;
	int status;
	char **env = environ;

	child_pid = fork();
	if (child_pid < 0)
		perror(cp);
	if (child_pid == 0)
	{
		execve(cp, cmd, env);
		perror(cp);
		free(cp);
		free_buffers(cmd);
		exit(98);
	}
	else
		wait(&status);
}

/**
 * tokenize - Creates tokens from the given input line
 * @line: The input line to be tokenized
 *
 * Description:
 * tokenizes a string based on delimiters and returns an array
 * of strings (tokens).
 *
 * Return: An array of strings (tokens) or NULL on failure.
 */
char **tokenize(char *line)
{
	char *buf = NULL, *bufp = NULL, *token = NULL, *delim = " :\t\r\n";
	char **tokens = NULL;
	int tokensize = 1;
	size_t index = 0, flag = 0;

	buf = _strdup(line);
	if (!buf)
		return (NULL);
	bufp = buf;

	while (*bufp)
	{
		if (_strchr(delim, *bufp) != NULL && flag == 0)
		{
			tokensize++;
			flag = 1;
		}
		else if (_strchr(delim, *bufp) == NULL && flag == 1)
			flag = 0;
		bufp++;
	}
	tokens = malloc(sizeof(char *) * (tokensize + 1));
	token = strtok(buf, delim);
	while (token)
	{
		tokens[index] = _strdup(token);
		if (tokens[index] == NULL)
		{
			free(tokens);
			return (NULL);
		}
		token = strtok(NULL, delim);
		index++;
	}
	tokens[index] = NULL;
	free(buf);
	return (tokens);
}

/**
 * exit_cmd - handles the exit command
 * @command: tokenized command
 * @line: input read from stdin
 *
 * Return: no return
 */
void exit_cmd(char **command, char *line)
{
	free(line);
	free_buffers(command);
	exit(0);
}
