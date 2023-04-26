#include "shell.h"

/**
* _getline - reads one line from the user prompt
* @data: struct for the programs data
*
* Return: reading the counting bytes.
*/

int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t  bytes_read, q = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (q = 0; array_commands[q]; q++)
		{
			free(array_commands[q]);
			array_commands[q] = NULL;
		}
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);

		if (bytes_read == 0)
			return (-1);
		q = 0;
		do {
			array_commands[q] = strdup(_strtok(q ? NULL : buff, "\n;"));

			q = check_logic_ops(array_commands, q, array_operators);
		} while (array_commands[q++]);
	}
	data->input_line = array_commands[0];

	for (q = 0; array_commands[q]; q++)
	{
		array_commands[q] = array_commands[q + 1];
		array_operators[q] = array_operators[q + 1];
	}

	return (strlen(data->input_line));
}


/**
* check_logic_ops - checks nd splits for && and || operators
* @array_commands: array of the commnds
* @i: index in the array_commands to be chckd
* @array_operators: array of the logical operators for each previously usd commnd
*
* Return: index of the lst command in the array_commands
*/

int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int v;

	for (v = 0; array_commands[i] != NULL  && array_commands[i][v]; v++)
	{
		if (array_commands[i][v] == '&' && array_commands[i][v + 1] == '&')
		{
			temp = array_commands[i];
			array_commands[i][v] = '\0';
			array_commands[i] = strdup(array_commands[i]);
			array_commands[i + 1] = strdup(temp + v + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			v = 0;
		}
		if (array_commands[i][v] == '|' && array_commands[i][v + 1] == '|')
		{
			temp = array_commands[i];
			array_commands[i][v] = '\0';
			array_commands[i] = strdup(array_commands[i]);
			array_commands[i + 1] = strdup(temp + v + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			v = 0;
		}
	}
	return (i);
}
