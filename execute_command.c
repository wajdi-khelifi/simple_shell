#include "simple_shell_lib.h"

void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *path_token;

	pid = fork();

	if (pid == 0)
	{
		char *path = getenv("PATH");

		if (path == NULL)
		{
			fprintf(stderr, "PATH environment variable not found\n");
			exit(EXIT_FAILURE);
		}

		path_token = strtok(path, ":");
		while (path_token != NULL) {
			if (file_exists_in_directory(args[0], path_token)) {
				char command[MAX_INPUT_SIZE];
				snprintf(command, sizeof(command), "%s/%s", path_token, args[0]);
				if (execv(command, args) == -1) {
					perror("Error");
				}
				exit(EXIT_FAILURE);
			}
			path_token = strtok(NULL, ":");
		}

		fprintf(stderr, "Command not found: %s\n", args[0]);
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("Error");
	} else {
		waitpid(pid, &status, 0);
	}
}
