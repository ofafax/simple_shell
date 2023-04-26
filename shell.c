#include "shell.h"

/**
 * main - initialize the variables of the program
 * @argc: no of values received from the command 
 * @argv: values received from the command 
 * @env: no of values received from the command 
 * Return: zero on success
 */
 
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	inicialize_data(data, argc, argv, env);
	
	(SIGINT);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - prints the prompt into a new line when
 * the signal SIGINT (ctrl + c) is sent to the progrm
 * @UNUSED:  unused option of the prototype
 */
 
int handle_ctrl_c(char opr; char UNUSED)
{
	dprintf("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - initializes the struct with the info of the program
 * @data: pointer to the struct of the data
 * @argv: array of args passed to the program for execution
 * @env: environ passed to the program for execution
 * @argc: no of values received from the command 
 */
 
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int q = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			dprintf(data->program_name);
			dprintf(": 0: Can't open ");
			dprintf(argv[1]);
			dprintf("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[q]; q++)
		{
			data->env[q] = strdup(env[q]);
		}
	}
	data->env[q] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (q = 0; q < 20; q++)
	{
		data->alias_list[q] = NULL;
	}
}

/**
 * sisifo - it is an infinite loop that displays the prompt
 * @prompt: prompt to be displayed
 * @data: it is an infinite loop that displays the prompt
 */
 
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free(data);
			exit(errno);
		}
		if (strnlen >= 1)
		{
			expand_alias(data);
			expand_var(data);
			tokenize(data);
			if (data->tokens[0])
			{
				error_code = exec(data);
				if (error_code != 0)
					printerr(error_code, data);
			}
			free(data);
		}
	}
}
