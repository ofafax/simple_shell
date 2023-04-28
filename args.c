#include "shell.h"

char *get_cmd_args(char *line, int *exe_opt);
int call_cmd_args(char **args, char **frnt, int *exe_opt);
int run_cmd_args(char **args, char **frnt, int *exe_opt);
int handle_cmd_args(int *exe_opt);
int check_cmd_args(char **args);

/**
 * get_cmd_args - Gets a command from standard inp
 * @line: A buffer to store the cmd
 * @exe_opt: The return value of the last executed command
 *
 * Return: If an error occurs - NULL.Otherwise - a pointer
 * to the stored command.
 */

char *get_cmd_args(char *line, int *exe_opt)
{
	size_t q = 0;
	ssize_t rd;
	char *prompt = "$ ";

	if (line)
		free(line);

	rd = _getline(&line, &q, STDIN_FILENO);
	if (rd == -1)
		return (NULL);
	if (rd == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_cmd_args(line, exe_opt));
	}

	line[rd - 1] = '\0';
	var_replacement(&line, exe_opt);
	partition_line(&line, rd);

	return (line);
}

/**
 * call_cmd_args - Partitions operators from cmds and calls them
 * @args: An array of arguments
 * @frnt: A double pointer to the beginning of args.
 * @exe_opt: The return value of the parent processes last
 * executed command.
 *
 * Return: The return value of the last executed cmd
 */

int call_cmd_args(char **args, char **frnt, int *exe_opt)
{
	int retn;
	int ind;

	if (!args[0])
		return (*exe_opt);
	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], "||", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = replace_aliases(args);
			retn = run_cmd_args(args, frnt, exe_opt);
			if (*exe_opt != 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (retn);
			}
		}
		else if (_strncmp(args[ind], "&&", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = replace_aliases(args);
			retn = run_cmd_args(args, frnt, exe_opt);
			if (*exe_opt == 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (retn);
			}
		}
	}
	args = replace_aliases(args);
	retn = run_cmd_args(args, frnt, exe_opt);
	return (retn);
}

/**
 * run_cmd_args - Calls the execution of a command
 * @args: An array of arguments
 * @frnt: A double pointer to the beginning of args
 * @exe_opt: The return val of the parent process last executed cmd
 *
 * Return: The value of the last executed command
 */

int run_cmd_args(char **args, char **frnt, int *exe_opt)
{
	int retn;
	int x;
	int (*builtin)(char **args, char **frnt);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		retn = builtin(args + 1, frnt);
		if (retn != EXIT)
			*exe_opt = retn;
	}
	else
	{
		*exe_opt = exec_cmd(args, frnt);
		retn = *exe_opt;
	}

	hist++;

	for (x = 0; args[x]; x++)
		free(args[x]);

	return (retn);
}

/**
 * handle_cmd_args - Gets, calls, and runs the execution of a cmd
 * @exe_opt: The return value of the parent process last executed cmd
 *
 * Return: If an end-of-file is read (-2).If the input
 * cannot be tokenized - -1. Otherwise - The exit value
 * of the last executed command.
 */

int handle_cmd_args(int *exe_opt)
{
	int retn = 0;
	int ind;
	char **args, *line = NULL, **frnt;

	line = get_cmd_args(line, exe_opt);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (retn);
	if (check_cmd_args(args) != 0)
	{
		*exe_opt = 2;
		free_args_mem(args, args);
		return (*exe_opt);
	}
	frnt = args;

	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], ";", 1) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			retn = call_cmd_args(args, frnt, exe_opt);
			args = &args[++ind];
			ind = 0;
		}
	}
	if (args)
		retn = call_cmd_args(args, frnt, exe_opt);

	free(frnt);
	return (retn);
}

/**
 * check_cmd_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *   Otherwise - 0.
 */
int check_cmd_args(char **args)
{
	size_t x;
	char *curr, *after;

	for (x = 0; args[x]; x++)
	{
		curr = args[x];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (x == 0 || curr[1] == ';')
				return (create_custom_stderr(&args[x], 2));
			after = args[x + 1];
			if (after && (after[0] == ';' || after[0] == '&' || after[0] == '|'))
				return (create_custom_stderr(&args[x + 1], 2));
		}
	}
	return (0);
}

