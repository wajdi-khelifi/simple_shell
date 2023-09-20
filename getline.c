#include "simple_shell_lib.h"

/**
 * _getline - Custom getline function
 * @data: Pointer to program data
 * Return: Number of characters read
 */
int _getline(prog *data)
{
	size_t buffer_size = 0;
	ssize_t characters_read;

	characters_read = getline(&(data->input), &buffer_size, stdin);

	if (characters_read == -1)
	{
		if (data->exec_counter > 1)
			_print("\n");
		return (EOF);
	}

	return ((int)characters_read);
}

