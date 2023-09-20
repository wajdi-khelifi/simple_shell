#include "simple_shell_lib.h"

/**
 * special_char - Handle special characters in a string by escaping them.
 * @arg: The string to handle.
 *
 * This function escapes special characters in the provided string by
 * adding a backslash before them. The special characters handled are
 * double quotes ("), single quotes ('), backticks (`), backslashes (\),
 * asterisks (*), ampersands (&), and hashtags (#).
 *
 * @arg: The string to be processed for special characters.
 */
void special_char(char *arg)
{
	int len = strlen(arg);
	int x;

	if (arg == NULL)
	{
		return;
	}

	for (x = 0; x < len; x++)
	{
		if (arg[x] == '"' || arg[x] == '\'' ||
				arg[x] == '`' || arg[x] == '\\' ||
				arg[x] == '*' || arg[x] == '&' || arg[x] == '#')
		{
			memmove(arg + x + 1, arg + x, len - x + 1);
			arg[x] = '\\';
			len++;
			x++;
		}
	}
}
