#include "shell.h"

void prompt_handler(int blink);
int exec_cmd(char **args, char **first);

/**
 * prompt_handler - Prints a new prompt upon a signal.
 * @blink: The signal from the handler.
 */
void prompt_handler(int blink)
{
	char *new_prompt = "\n#SimpleShell$ ";

	(void)blink;
	signal(SIGINT, prompt_handler);
	write(STDIN_FILENO, new_prompt, 15);
}

/**
 * exec_cmd - Executes a command in a child process.
 * @args: array of arguments.
 * @first: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 * Otherwise - The exit value of the last executed command.
 */
int exec_cmd(char **args, char **first)
{
	pid_t child_pid;
	int status;
	int sth = 0, retn = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		sth = 1;
		cmd = get_location(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			retn = (create_custom_stderr(args, 126));
		else
			retn = (create_custom_stderr(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (sth)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				retn = (create_custom_stderr(args, 126));
			free_env();
			free_args_mem(args, first);
			free_list_alias(aliases);
			_exit(retn);
		}
		else
		{
			wait(&status);
			retn = WEXITSTATUS(status);
		}
	}
	if (sth)
		free(cmd);
	return (retn);
}

/**
 * main - Runs a simple UNIX command interpreter
 * @argc: The number of arguments given to the program.
 * @argv: An array of pointers to the arguments
 *
 * Return: The return value of the last executed cmd.
 */

int main(int argc, char *argv[])
{
	int x = 0;
	int retn;
	int *exe_opt = &retn;
	char *prompt = "#SimpleShell$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, prompt_handler);

	*exe_opt = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		x = run_file_commands(argv[1], exe_opt);
		free_env();
		free_list_alias(aliases);
		return (*exe_opt);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (x != END_OF_FILE && x != EXIT)
			x = handle_cmd_args(exe_opt);
		free_env();
		free_list_alias(aliases);
		return (*exe_opt);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 15);
		x = handle_cmd_args(exe_opt);
		if (x == END_OF_FILE || x == EXIT)
		{
			if (x == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 15);
			free_env();
			free_list_alias(aliases);
			exit(*exe_opt);
		}
	}

	free_env();
	free_list_alias(aliases);
	return (*exe_opt);
}
