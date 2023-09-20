#ifndef SIMPLE_SHELL_LIB_H
#define SIMPLE_SHELL_LIB_H

/* Libraries */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024

char *read_input();
char **parse_input(char *input);
int file_exists_in_directory(const char *file, const char *directory);
void run_shell(void);
void execute_command(char **args, int nb);
void handle_special(char *str);

#endif /* SIMPLE_SHELL_LIB_H */
