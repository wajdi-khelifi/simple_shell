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
void handle_special(char *str);
char *get_env(char *env_var, char **env);
void add_path(char *a, char *exe, char *env_path);
void execute_command(char **args, int nb, char **env);
void run_shell(char **env);
int main(int argc, char **argv, char **env);

#endif /* SIMPLE_SHELL_LIB_H */
