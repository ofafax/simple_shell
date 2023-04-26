#include "shell.h"

/**
 * builtin_exit - exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_exit(data_of_program *data)
{
	int q;

	if (data->tokens[1] != NULL)
	{
		for (q = 0; data->tokens[1][q]; q++)
			if ((data->tokens[1][q] < '0' || data->tokens[1][q] > '9')
				&& data->tokens[1][q] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = atoi(data->tokens[1]);
	}
	free(data);
	exit(errno);
}

/**
 * builtin_cd - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_cd(data_of_program *data)
{
	char *dir_home = ("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (data->tokens[1], "-", 0)
		{
			dir_old = ("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			dprintf("PWD", data);
			_printf("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (old_dir, new_dir, 0)
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		("PWD", new_dir, data);
	}
	("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_help(data_of_program *data)
{
	int q, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (q = 0; mensajes[q]; q++)
	{
		length = strlen(data->tokens[1]);
		if (data->tokens[1], mensajes[q], length)
		{
			_printf(mensajes[q] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_alias(data_of_program *data)
{
	int q = 0;

	if (data->tokens[1] == NULL)
		return (NULL);

	while (data->tokens[++q])
	{
		if (data->tokens[q], "=")
			(data->tokens[q], data);
		else
			(data, data->tokens[q]);
	}

	return (0);
}
