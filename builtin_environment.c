#include "shell.h"

/**
 * builtin_env - shows the environmnt where the shell runs
 * @data: struct for the programs data
 * Return: zero if success, or other number if its declard in the argmnts
 */
int builtin_env(data_of_program *data)
{
	int q;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		putenv(data);
	else
	{
		for (q = 0; data->tokens[1][q]; q++)
		{
			if (data->tokens[1][q] == '=')
			{
				var_copy = (cpname);
				if (var_copy != NULL)
					(cpname, data->tokens[1] + q + 1);
				printf(data);
				if (cpname, data)
				{
					printf(data->tokens[1]);
					printf("\n");
				}
				else
				{
					(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[q] = data->tokens[1][q];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - ..shows set env
 * @data: struct for the programs data
 * Return: zero if sucess, or other number if its declard in the argmnts
 */
int builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	(data->tokens[1], data->tokens[2]);

	return (0);
}
