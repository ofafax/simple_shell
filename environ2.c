#include "shell.h"

int shellin_print_env(char **args, char __attribute__((__unused__)) **front);
int shellin_set_env(char **args, char __attribute__((__unused__)) **front);
int shellin_del_env(char **args, char __attribute__((__unused__)) **front);

/**
 * shellin_print_env - Prints the current environment
 * @args: An array of argmnts passed to the shell
 * @front: A double pointer to the beginning of args
 *
 * Return: If an error occurs - -1.otherwise 0
 *
 * Description: Prints one variable per line in the
 * format of 'variable'='value'.
 */

int shellin_print_env(char **args, char __attribute__((__unused__)) **front)
{
	int ind;
	char nice = '\n';

	if (!environ)
		return (-1);

	for (ind = 0; environ[ind]; ind++)
	{
		write(STDOUT_FILENO, environ[ind], _strlength(environ[ind]));
		write(STDOUT_FILENO, &nice, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellin_setenv - Changes or adds an env variable to the PATH
 * @args: An array of arguments that is passed to the shell
 * @front: A double pointer to the beginning of args
 * Description: args[1] the name of the new or existing PATH variable
 * while args[2] the value to set the new or changed variable to
 *
 * Return: If an error occurs - -1.otherwise 0
 */

int shellin_set_env(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL;
	char **new_env;
	char *new_val;
	size_t siz;
	int ind;

	if (!args[0] || !args[1])
		return (create_custom_stderr(args, -1));

	new_val = malloc(_strlength(args[0]) + 1 + _strlength(args[1]) + 1);
	if (!new_val)
		return (create_custom_stderr(args, -1));
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (siz = 0; environ[siz]; siz++)
		;

	new_env = malloc(sizeof(char *) * (siz + 2));
	if (!new_env)
	{
		free(new_val);
		return (create_custom_stderr(args, -1));
	}

	for (ind = 0; environ[ind]; ind++)
		new_env[ind] = environ[ind];

	free(environ);
	environ = new_env;
	environ[ind] = new_val;
	environ[ind + 1] = NULL;

	return (0);
}

/**
 * shellin_del_env - Deletes an env variable from the PATH
 * @args: An array of arguments passed onto  the shell
 * @front: A double pointer to the beg of args
 * Description: args[1] is the PATH variable to be removed
 *
 * Return: If an error occurs - -1.Otherwise 0
 */

int shellin_del_env(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var;
	char **new_env;
	size_t siz;
	int ind;
	int ind2;

	if (!args[0])
		return (create_custom_stderr(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (siz = 0; environ[siz]; siz++)
		;

	new_env = malloc(sizeof(char *) * siz);
	if (!new_env)
		return (create_custom_stderr(args, -1));

	for (ind = 0, ind2 = 0; environ[ind]; ind++)
	{
		if (*env_var == environ[ind])
		{
			free(*env_var);
			continue;
		}
		new_env[ind2] = environ[ind];
		ind2++;
	}
	free(environ);
	environ = new_env;
	environ[siz - 1] = NULL;

	return (0);
}
