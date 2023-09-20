#include "simple_shell_lib.h"

/**
 * string_length - returns the length of a string.
 * @str: pointer to string.
 * Return: length of string.
 */
int string_length(char *str)
{
	int length = 0;

	if (str == NULL)
		return (0);

	while (str[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * string_duplicate - duplicates a string
 * @str: String to be copied
 * Return: pointer to the array
 */
char *string_duplicate(char *str)
{
	char *result;
	int length, i;

	if (str == NULL)
		return (NULL);

	length = string_length(str) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length; i++)
	{
		result[i] = str[i];
	}

	return (result);
}

/**
 * string_compare - Compare two strings
 * @str1: String one, or the shorter
 * @str2: String two, or the longer
 * @num: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equal, 0 if the strings are different
 */
int string_compare(char *str1, char *str2, int num)
{
	int iterator;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (num == 0) /* infinite length */
	{
		if (string_length(str1) != string_length(str2))
			return (0);
		for (iterator = 0; str1[iterator]; iterator++)
		{
			if (str1[iterator] != str2[iterator])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of characters to be compared */
	{
		for (iterator = 0; iterator < num; iterator++)
		{
			if (str1[iterator] != str2[iterator])
				return (0);
		}
		return (1);
	}
}

/**
 * string_concatenate - concatenates two strings.
 * @str1: String to be concatenated
 * @str2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *string_concatenate(char *str1, char *str2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (str1 == NULL)
		str1 = "";
	length1 = string_length(str1);

	if (str2 == NULL)
		str2 = "";
	length2 = string_length(str2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of str1 */
	for (length1 = 0; str1[length1] != '\0'; length1++)
		result[length1] = str1[length1];
	free(str1);

	/* copy of str2 */
	for (length2 = 0; str2[length2] != '\0'; length2++)
	{
		result[length1] = str2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}

/**
 * string_reverse - reverses a string.
 *
 * @str: pointer to string.
 * Return: void.
 */
void string_reverse(char *str)
{
	int i = 0, length = string_length(str) - 1;
	char hold;

	while (i < length)
	{
		hold = str[i];
		str[i++] = str[length];
		str[length--] = hold;
	}
}

