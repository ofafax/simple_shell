#include "shell.h"
/**
 * tokenize - this function separate the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int v, q, counter = 2, length;

	(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (v = 0; data->input_line[v]; v++)
	{
		for (q = 0; delimiter[q]; q++)
		{
			if (data->input_line[v] == delimiter[q])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	v = 0;
	data->tokens[v] = strdup(_strtok(data->input_line, delimiter));
	data->command_name = strdup(data->tokens[0]);
	while (data->tokens[v++])
	{
		data->tokens[v] = strdup(_strtok(NULL, delimiter));
	}
}
