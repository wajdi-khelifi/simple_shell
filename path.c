#include "simple_shell_lib.h"

/**
 * file_exists_in_directory - Check if a file exists in a directory.
 * @file: The name of the file to check.
 * @directory: The directory in which to search for the file.
 *
 * This function constructs the full path to the specified file within the
 * given directory and checks if it exists and is executable (X_OK).
 *
 * Return: 1 if the file exists and is executable, 0 otherwise.
 */
int file_exists_in_directory(const char *file, const char *directory)
{
	char path[MAX_INPUT_SIZE];

	snprintf(path, sizeof(path), "%s/%s", directory, file);
	return (access(path, X_OK) == 0);
}
