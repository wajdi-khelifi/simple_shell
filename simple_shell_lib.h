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

/**
 * struct coordination - Structure to hold program coordination data
 * @prog_name: The program's name
 * @input: Input data or command input
 * @cmd_name: The command name
 * @tokens: Array of tokens (character strings)
 * @env: Array of environment variables (character strings)
 * @alias_list: Array of aliases (character strings)
 * @exec_counter: Execution counter or counter for some operation
 * @file_descriptor: File descriptor or related integer value
 *
 * Description: used to coordinate and store data related to
 * a program's execution.
 * variables, alias list, execution counter, and file descriptor.
 */
typedef struct coordination
{
	char *prog_name;
	char *input;
	char *cmd_name;
	char **tokens;
	char **env;
	char **alias_list;
	int exec_counter;
	int file_descriptor;
} prog;

/* Functions prototypes */
int string_length(char *str);
char *string_duplicate(char *str);
int string_compare(char *str1, char *str2, int num);
char *string_concatenate(char *str1, char *str2);
void string_reverse(char *str);
int execute(prog *data);
int calculate_program(prog *data);
char **calculate_path(prog *data);
int examine(char *all_path);
int main(int argc, char *argv[], char *env[]);
void handle_ctrl_c(int opr UNUSED);
void initialize_data(prog *data, int argc, char *argv[], char **env);
void simple_shell_loop(char *prompt, prog *data);

#endif /* SIMPLE_SHELL_LIB_H */
