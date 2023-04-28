#include "shell.h"

void free_args_mem(char **args, char **frnt);
void var_replacement(char **args, int *exe_opt);
char *get_env_var_value(char *start, int length);
char *get_pid(void);

/**
 * free_args_mem - Frees up memory taken by args
 * @args: A null-terminated double pointer containing cmds/argments
 * @frnt: A double pointer to the beginning of args
 */
void free_args_mem(char **args, char **frnt)
{
	size_t x;

	for (x = 0; args[x] || args[x + 1]; x++)
		free(args[x]);

	free(frnt);
}

/**
 * var_replacement - Handles variable replacement
 * @line: A double pointer containing the cmd and arguments
 * @exe_opt: A pointer to the return value of the last executed cmd
 *
 * Description: Replaces $$ with the current PID, $? with the return
 * value of the last executed program, and envrionmental variables
 * preceded by $ with their corresponding value.
 */

void var_replacement(char **line, int *exe_opt)
{
	int i;
	int q = 0;
	int leng;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		if (old_line[i] == '$' && old_line[i + 1] &&
		    old_line[i + 1] != ' ')
		{
			if (old_line[i + 1] == '$')
			{
				replacement = get_pid();
				q = i + 2;
			}
			else if (old_line[i + 1] == '?')
			{
				replacement = int_to_str(*exe_opt);
				q = i + 2;
			}
			else if (old_line[i + 1])
			{
				/* extract the variable name to search for */
				for (q = i + 1; old_line[q] &&
					     old_line[q] != '$' &&
					     old_line[q] != ' '; q++)
					;
				leng = q - (i + 1);
				replacement = get_env_var_value(&old_line[i + 1], leng);
			}
			new_line = malloc(i + _strlength(replacement)
					  + _strlength(&old_line[q]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, i);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[q]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			i = -1;
		}
	}
}

/**
 * get_env_var_value - Gets the value corresponding to an
 * environmental variable.
 * @start: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_var_value(char *start, int length)
{
	char **var_address;
	char *replacement = NULL, *tmp, *var;

	var = malloc(length + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, start, length);

	var_address = _getenv(var);
	free(var);
	if (var_address)
	{
		tmp = *var_address;
		while (*tmp != '=')
			tmp++;
		tmp++;
		replacement = malloc(_strlength(tmp) + 1);
		if (replacement)
			_strcpy(replacement, tmp);
	}

	return (replacement);
}

/**
 * get_pid - Gets the process ID.
 * Description: Opens the stat file, a space-delimited file containing
 * info about the current process. The PID is the first word in the file.
 * The function reads the PID into a buffer and replaces the space at the
 * end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure
 */

char *get_pid(void)
{
	size_t x = 0;
	char *buff;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(file);
		return (NULL);
	}
	read(file, buff, 120);
	while (buff[x] != ' ')
		x++;
	buff[x] = '\0';

	close(file);
	return (buff);
}
