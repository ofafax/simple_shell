#include "shell.h"

char *get_location(char *cmd);
int run_file_commands(char *file_path, int *exe_ret);
int cant_open_err(char *file_pth);
list_t *get_dir_path(char *pth);
char *fill_dir_path(char *pth);

/**
 * get_location - Locates a cmd in the PATH.
 * @cmd: The cmd to locate.
 *
 * Return: If an error occurs or the command cant be located - NULL.
 * Otherwise return the full pathname of the command.
 */

char *get_location(char *cmd)
{
	char **pth;
	char *tmp;
	list_t *firs, *head;
	struct stat st;

	pth = _getenv("PATH");
	if (!pth || !(*pth))
		return (NULL);

	firs = get_dir_path(*pth + 5);
	head = firs;

	while (firs)
	{
		tmp = malloc(_strlength(firs->dir) + _strlength(cmd) + 2);
		if (!tmp)
			return (NULL);

		_strcpy(tmp, firs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, cmd);

		if (stat(tmp, &st) == 0)
		{
			free_list(head);
			return (tmp);
		}

		firs = firs->next;
		free(tmp);
	}

	free_list(head);

	return (NULL);
}

/**
 * run_file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_opt: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *   If malloc fails - -1.
 *   Otherwise the return value of the last command ran.
 */

int run_file_commands(char *file_path, int *exe_opt)
{
	ssize_t file, be_read, x;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int retn;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_opt = cant_open_err(file_path);
		return (*exe_opt);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		be_read = read(file, buffer, 119);
		if (be_read == 0 && line_size == 0)
			return (*exe_opt);
		buffer[be_read] = '\0';
		line_size += be_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (be_read);
	for (x = 0; line[x] == '\n'; x++)
		line[x] = ' ';
	for (; x < line_size; x++)
	{
		if (line[x] == '\n')
		{
			line[x] = ';';
			for (x += 1; x < line_size && line[x] == '\n'; x++)
				line[x] = ' ';
		}
	}
	var_replacement(&line, exe_opt);
	partition_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_cmd_args(args) != 0)
	{
		*exe_opt = 2;
		free_args_mem(args, args);
		return (*exe_opt);
	}
	front = args;

	for (x = 0; args[x]; x++)
	{
		if (_strncmp(args[x], ";", 1) == 0)
		{
			free(args[x]);
			args[x] = NULL;
			retn = call_cmd_args(args, front, exe_opt);
			args = &args[++x];
			x = 0;
		}
	}

	retn = call_cmd_args(args, front, exe_opt);

	free(front);
	return (retn);
}

/**
 * cant_open_err - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_pth: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open_err(char *file_pth)
{
	char *err;
	char *histry_str;
	int leng;

	histry_str = int_to_str(hist);
	if (!histry_str)
		return (127);

	leng = _strlength(name) + _strlength(histry_str) + _strlength(file_pth) + 16;
	err = malloc(sizeof(char) * (leng + 1));
	if (!err)
	{
		free(histry_str);
		return (127);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, histry_str);
	_strcat(err, ": Can't open ");
	_strcat(err, file_pth);
	_strcat(err, "\n");

	free(histry_str);
	write(STDERR_FILENO, err, leng);
	free(err);
	return (127);
}

/**
 * get_dir_path - Tokenizes a colon-separated list of
 * directories into a list_s linked list.
 * @path: The colon-separated list of directories
 *
 * Return: A pointer to the initialized linked list
 */
list_t *get_dir_path(char *pth)
{
	int ind;
	char **firs;
	char *pth_copy;
	list_t *head = NULL;

	pth_copy = fill_dir_path(pth);
	if (!pth_copy)
		return (NULL);
	firs = _strtok(pth_copy, ":");
	free(pth_copy);
	if (!firs)
		return (NULL);

	for (ind = 0; firs[ind]; ind++)
	{
		if (add_end_node(&head, firs[ind]) == NULL)
		{
			free_list(head);
			free(firs);
			return (NULL);
		}
	}

	free(firs);

	return (head);
}

/**
 * fill_dir_path - Copies path but also replaces leading/sandwiched/
 * trailing colons (:) with current working directory
 * @path: The colon-separated list of directories
 *
 * Return: A copy of path with any leading/sandwiched/trailing
 * colons replaced with the current working directory.
 */
char *fill_dir_path(char *pth)
{
	int x;
	int leng = 0;
	char *pth_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (x = 0; pth[x]; x++)
	{
		if (pth[x] == ':')
		{
			if (pth[x + 1] == ':' || x == 0 || pth[x + 1] == '\0')
				leng += _strlength(pwd) + 1;
			else
				leng++;
		}
		else
			leng++;
	}
	pth_copy = malloc(sizeof(char) * (leng + 1));
	if (!pth_copy)
		return (NULL);
	pth_copy[0] = '\0';
	for (x = 0; pth[x]; x++)
	{
		if (pth[x] == ':')
		{
			if (x == 0)
			{
				_strcat(pth_copy, pwd);
				_strcat(pth_copy, ":");
			}
			else if (pth[x + 1] == ':' || pth[x + 1] == '\0')
			{
				_strcat(pth_copy, ":");
				_strcat(pth_copy, pwd);
			}
			else
				_strcat(pth_copy, ":");
		}
		else
		{
			_strncat(pth_copy, &pth[x], 1);
		}
	}
	return (pth_copy);
}
