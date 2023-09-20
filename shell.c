#include "simple_shell_lib.h"

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
