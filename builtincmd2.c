#include "shell.h"

int shellin_alias(char **args, char __attribute__((__unused__)) **front);
int shellin_cd(char **args, char __attribute__((__unused__)) **front);
int shellin_exit(char **args, char **front);
int shellin_help(char **args, char __attribute__((__unused__)) **front);



/**
 * shellin_alias - Builtin shellin command that either prints all aliases,
 * specific aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1, otherwise 0
 */

int shellin_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tmp = aliases;
	int j;
	int opt = 0;
	char *val;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (opt);
	}
	for (j = 0; args[j]; j++)
	{
		tmp = aliases;
		val = _strchar(args[j], '=');
		if (!val)
		{
			while (tmp)
			{
				if (_strcmpr(args[j], tmp->name) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				opt = create_custom_stderr(args + j, 1);
		}
		else
			set_alias(args[j], val);
	}
	return (opt);
}

/**
 * shellin_cd - Changes the current directory of the process
 * @args: An array of arguments
 * @front: A double pointer to the beginning of args
 *
 * Return: If the given string is not a directory - 2
 *         If an error occurs - -1. otherwise 0
 */

int shellin_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_inf;
	char *newline = "\n";
	char *oldpwdir = NULL, *pwd = NULL;
	struct stat dir;

	oldpwdir = getcwd(oldpwdir, 0);
	if (!oldpwdir)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmpr(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
			    args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwdir);
				return (create_custom_stderr(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
			    && ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwdir);
				return (create_custom_stderr(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_inf = malloc(sizeof(char *) * 2);
	if (!dir_inf)
		return (-1);

	dir_inf[0] = "OLDPWD";
	dir_inf[1] = oldpwdir;
	if (shellin_set_env(dir_inf, dir_inf) == -1)
		return (-1);

	dir_inf[0] = "PWD";
	dir_inf[1] = pwd;
	if (shellin_set_env(dir_inf, dir_inf) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlength(pwd));
		write(STDOUT_FILENO, newline, 1);
	}
	free(oldpwdir);
	free(pwd);
	free(dir_inf);
	return (0);
}

/**
 * shellin_exit - Causes normal termination for shell
 * @args: An array of arguments containing the exit value
 * @front: A double pointer to the beginning of args
 *
 * Return: If there are no arguments -3.If the given exit value
 * is invalid - 2.Otherwise - exits with the given status value
 *
 * Description: Upon returning -3, the program exits back in the
 * main function.
 */

int shellin_exit(char **args, char **front)
{
	int x = 0;
	int len_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			x = 1;
			len_int++;
		}
		for (; args[0][x]; x++)
		{
			if (x <= len_int && args[0][x] >= '0' && args[0][x] <= '9')
				num = (num * 10) + (args[0][x] - '0');
			else
				return (create_custom_stderr(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_custom_stderr(--args, 2));
	args -= 1;
	free_args_mem(args, front);
	free_env();
	free_list_alias(aliases);
	exit(num);
}

/**
 * shellin_help - Shows infor about shellby builtin commands
 * @args: An array of arguments
 * @front: A pointer to the begin of args.
 *
 * Return: If an error occurs - -1.Otherwise 0
 */

int shellin_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmpr(args[0], "alias") == 0)
		help_alias();
	else if (_strcmpr(args[0], "cd") == 0)
		help_cd();
	else if (_strcmpr(args[0], "exit") == 0)
		help_exit();
	else if (_strcmpr(args[0], "env") == 0)
		help_env();
	else if (_strcmpr(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmpr(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmpr(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlength(name));

	return (0);
}
