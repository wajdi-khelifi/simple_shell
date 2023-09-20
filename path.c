#include "simple_shell_lib.h"

int file_exists_in_directory(const char *file, const char *directory)
{
	char path[MAX_INPUT_SIZE];
	snprintf(path, sizeof(path), "%s/%s", directory, file);
	return (access(path, X_OK) == 0);
}
