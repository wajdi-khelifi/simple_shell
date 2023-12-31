#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>

/* Global environment variable */
extern char **environ;

/* Global variables */
extern struct builtin builtin;
extern struct info info;
extern struct flags flags;

/* Function prototypes for path functions */
char *find_path(void);
char *append_path(char *path, const char *command);
char *test_paths(char **path, const char *command);

/* Function prototypes for string functions */
int _strcmp(const char *s1, const char *s2);
int _strlen(const char *s);
int _strncmp(const char *s1, const char *s2, int n);
char *_strdup(const char *s);
const char *_strchr(const char *s, char c);

/* Function prototypes for shell functionality */
void execute(char *pathcommand, char **cmd);
char **tokenize(char *line);
void free_buffers(char **buf);
void prompt_user(void);
void cleanup(char *line, char **command, char **paths, char *pathcommand);

/* Function prototypes for built-in commands */
void exit_cmd(char **command, char *line);
void print_env(void);
int checker(char **cmd, char *buf);
int handle_builtin(char **command, char *line);
void handle_signal(int m);
void initialize_flags(struct flags *flags);
void exit_builtin(void);

/* Allocate functions */
void example_double_free(void);
void example_use_after_free(void);
void example_memory_leak(void);


/* Structures */

/**
 * struct builtin - Represents built-in command names
 * @env: The environment variable command name
 * @exit: The exit command name
 *
 * Description:
 * Defines the names of built-in commands in the shell.
 * It is used to identify and handle specific built-in commands.
 */
struct builtin
{
	char *env;
	char *exit;
} builtin;

/**
 * struct info - Stores shell-related information
 * @final_exit: The final exit status of the shell
 * @ln_count: The line count of user input
 *
 * Description:
 * Stores information related to the behavior and state of the shell.
 * It is used to keep track of the final exit status and line count.
 */
struct info
{
	int final_exit;
	int ln_count;
} info;

/**
 * struct flags - Stores shell-related flags
 * @interactive: Indicates whether the shell is in interactive mode
 *
 * Description:
 * Stores flags that control various aspects of the shell's behavior,
 * such as whether it is running in interactive mode.
 */
struct flags
{
	bool interactive;
} flags;

#endif /* SIMPLE_SHELL_H */
