#include "simple_shell.h"

/**
 * example_double_free - Demonstrates a double-free error
 *
 * Allocates memory for an integer using malloc, frees it twice,
 * which is a double-free error, and showcases the potential issue.
 */
void example_double_free(void)
{
	int *ptr = malloc(sizeof(int));

	if (ptr == NULL)
	{
		perror("malloc");
		exit(1);
	}
	free(ptr);
	free(ptr);
}

/**
 * example_use_after_free - Demonstrates a use-after-free error
 *
 * Allocates memory for an integer using malloc, frees it, and
 * then attempts to assign a value to the freed memory, which is a
 * use-after-free error, and showcases the potential issue.
 */
void example_use_after_free(void)
{
	int *ptr = malloc(sizeof(int));

	if (ptr == NULL)
	{
		perror("malloc");
		exit(1);
	}
	free(ptr);
	*ptr = 42;
}

/**
 * example_memory_leak - Demonstrates a memory leak
 *
 * Allocates memory for an integer using malloc but does not
 * free it, showcasing a memory leak. It serves as an example to illustrate
 * the potential issue of not releasing allocated memory.
 */
void example_memory_leak(void)
{
	int *ptr = malloc(sizeof(int));

	if (ptr == NULL)
	{
		perror("malloc");
		exit(1);
	}
}
