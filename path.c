#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */

int find_program(data_of_program *data)
{
	int q = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = strcat(strdup("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (q = 0; directories[q]; q++)
	{
		directories[q] = strcat(directories[q], data->tokens[0]);
		ret_code = check_file(directories[q]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = strdup(directories[q]);
			free(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free(directories);
	return (ret_code);
}

/**
 * tokenize_path - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **tokenize_path(data_of_program *data)
{
	int q = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;


	("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = strdup(PATH);


	for (q = 0; PATH[q]; q++)
	{
		if (PATH[q] == ':')
			counter_directories++;
	}


	tokens = malloc(sizeof(char *) * counter_directories);

	q = 0;
	tokens[q] = strdup(_strtok(PATH, ":"));
	while (tokens[q++])
	{
		tokens[q] = strdup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int check_file(char *full_path)
{
	struct stat b;

	if (stat(full_path, &b) != -1)
	{
		if (S_ISDIR(b.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	errno = 127;
	return (127);
}
