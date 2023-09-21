#include "simple_shell.h"
/**
 * free_buffers - Frees buffers allocated by the tokenizer
 * @buf: The buffer to be freed
 *
 * Description:
 * This function frees the memory allocated for an array of strings.
 *
 * Return: No return value.
 */
void free_buffers(char **buf)
{
	int i = 0;

	if (!buf || buf == NULL)
		return;
	if (*buf == (char *) -1)
		return;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	*buf = (char *) -1;
	free(buf);
}
