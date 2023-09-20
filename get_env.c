#include "simple_shell_lib.h"

/**
 * _getenv - retrieves env variable that matches input string
 * @input: input string
 * @environ: local environmental variables
 * Return: string of env variable
 */
char *_getenv(char *input, char **environ)
{
	register int i = 0;
	char *s, *c;

	while (environ[i])
	{
		s = strtok(environ[i], "=");
		if (strcmp(s, input) == 0)
		{
			c = strtok(NULL, "=");
			return (c);
		}
		i++;
	}
	return (NULL);
}
