#include "simple_shell_lib.h"

/**
 * execute_command - Execute a command in a new process.
 * @args: An array of strings containing the command and its arguments.
 * @nb: The line number where the command is executed.
 * @env: The array of environment variables.
 *
 * This function creates a new process to execute the specified command with
 * the given arguments. If the command is not found in the PATH directories,
 * it prints an error message including the line number.
 */
void execute_command(char **args, int nb, char **env)
{
	pid_t pid;
	int status;
	int i;
	char *path_var, *token;

	pid = fork();
	if (pid == 0)
	{
		for (i = 0; args[i] != NULL; i++)
		{
			handle_special(args[i]);
		}
		path_var = get_env("PATH", env);
		if (path_var != NULL)
		{
			char exe[MAX_INPUT_SIZE];

			token = strtok(path_var, ":");
			while (token != NULL)
			{
				snprintf(exe, sizeof(exe), "%s/%s", token, args[0]);
				if (access(exe, X_OK) == 0)
				{
					execv(exe, args);
					fprintf(stderr, "hsh: %d: %s: execution failed\n", nb, args[0]);
					perror("Error");
					exit(EXIT_FAILURE);
				}
				token = strtok(NULL, ":");
			}
		}
		fprintf(stderr, "hsh: %d: %s: not found\n", nb, args[0]);
		exit(EXIT_FAILURE);
	} else if (pid < 0)
	{
		perror("Error");
	} else
	{
		waitpid(pid, &status, 0);
	}
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

		if (c == '"' || c == '\'' || c == '`' ||
				c == '\\' || c == '*' || c == '&' || c == '#')
		{
			escaped[j++] = '\\';
		}

		escaped[j++] = c;
	}

	escaped[j] = '\0';

	strcpy(str, escaped);
	free(escaped);
}

/**
 * read_input - Reads a line of input from the user.
 *
 * Return: A pointer to the input string read from stdin.
 */
char *read_input()
{
	char *input = NULL;
	size_t bufsize = 0;

	getline(&input, &bufsize, stdin);
	return (input);
}

/**
 * parse_input - Tokenizes the input into individual words (tokens).
 * @input: The input string to be tokenized.
 *
 * Return: An array of pointers to tokens (words) in the input string.
 *         The last element of the array is set to NULL.
 */
char **parse_input(char *input)
{
	int bufsize = MAX_INPUT_SIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, " \t\n");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += MAX_INPUT_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\n");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * run_shell - Run a simple shell program.
 *
 * This function implements a basic shell that continuously prompts the user
 * for input, reads the input, parses it into command and arguments, and
 * executes the commands. It also keeps track of the line number for error
 * reporting.
 */
void run_shell(char **env)
{
	char *input;
	char **args;
	int nb = 1;

	while (1)
	{
		printf("$ ");
		input = read_input();
		if (input == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (strcmp(input, "exit\n") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		args = parse_input(input);
		if (args[0] != NULL)
		{
			execute_command(args, nb, env);
		}
		free(input);
		free(args);
		nb++;
	}
}
