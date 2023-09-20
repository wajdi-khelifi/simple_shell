#include "simple_shell_lib.h"

/**
 * main - Initialize the variables of the program
 * @argc: Number of values received from the command line
 * @argv: Values received from the command line
 * @env: Number of values received from the command line
 * Return: Zero on success.
 */
int main(int argc, char *argv[], char *env[])
{
	prog data_struct = {NULL};
	prog *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	simple_shell_loop(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - Print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is sent to the program
 * @UNUSED: Option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_data - Initialize the struct with the info of the program
 * @data: Pointer to the structure of data
 * @argv: Array of arguments passed to the program execution
 * @env: environ passed to the program execution
 * @argc: Number of values received from the command line
 */
void initialize_data(prog *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->prog_name = argv[0];
	data->input = NULL;
	data->cmd_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
	{
		data->file_descriptor = STDIN_FILENO;
	} else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->prog_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = string_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * simple_shell_loop - It's an infinite loop that shows the prompt
 * @prompt: Prompt to be printed
 * @data: It's an infinite loop that shows the prompt
 */
void simple_shell_loop(char *prompt, prog *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize_input(data);
			if (data->tokens[0])
			{
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}

