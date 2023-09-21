#include "simple_shell.h"

/**
 * _strcmp - Compares two strings
 * @s1: The first string to compare
 * @s2: The second string to compare
 *
 * Description:
 * compares the two strings 's1' and 's2' and returns an integer
 * less than,equal to,or greater than zero if 's1' is found, respectively,
 * to be less than, to match, or to be greater than 's2'.
 *
 * Return:An integer less than, equal to,or greater than zero if s1 is found,
 * respectively, to be less than, to match, or to be greater than s2.
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0, output;

	while (*(s1 + i) == *(s2 + i) && *(s1 + i) != '\0')
		i++;

	output = (*(s1 + i) - *(s2 + i));

	return (output);
}

/**
 * _strlen - Calculates the length of a string
 * @s: The string to measure
 *
 * Description:
 * calculates and returns the length of the string 's', excluding
 * the terminating null byte ('\0').
 *
 * Return: The length of the string 's'.
 */
int _strlen(const char *s)
{
	int count = 0;

	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

/**
 * _strncmp - Compares two strings up to specified number of characters
 * @s1: The first string to compare
 * @s2: The second string to compare
 * @n: The maximum number of characters to compare
 *
 * Description:
 * compares up to 'n' characters of the strings 's1' and 's2'.
 * returns an integer less than, equal to, or greater than zero if 's1' is
 * found, respectively, to be less than, to match, or to be greater than 's2'.
 *
 * Return:integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or to be greater than 's2'.
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strdup - Duplicates a string
 * @s: The string to duplicate
 *
 * Description:
 * duplicates the string 's' and returns a newly allocated string
 * containing a copy of 's'.
 *
 * Return: A pointer to the duplicated string, or NULL if allocation fails.
 */
char *_strdup(const char *s)
{
	char *ptr;
	int i, len;

	if (s == NULL)
		return (NULL);

	len = _strlen(s);

	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	for (i = 0; *s != '\0'; s++, i++)
		ptr[i] = s[0];

	ptr[i++] = '\0';
	return (ptr);
}

/**
 * _strchr - Locates a character in a string
 * @s: The string to search
 * @c: The character to find
 *
 * Description:
 * searches for the first occurrence of the character 'c' in the
 * string s. search terminates upon finding c or reaching the end of s.
 *
 * Return:pointer to the first occurrence of 'c' in 's', or NULL if 'c' is
 * not found.
 */
const char *_strchr(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (!c)
		return (s);
	return (NULL);
}
