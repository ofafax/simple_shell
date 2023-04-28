#include "shell.h"

char **_copyenv(void);
char *error_env(char **args);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Makes a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 * Otherwise - a double pointer to the new copy.
 */

char **_copyenv(void)
{
	char **new_env;
	size_t s;
	int ind;

	for (s = 0; environ[s]; s++)
		;

	new_env = malloc(sizeof(char *) * (s + 1));
	if (!new_env)
		return (NULL);

	for (ind = 0; environ[ind]; ind++)
	{
		new_env[ind] = malloc(_strlength(environ[ind]) + 1);

		if (!new_env[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(new_env[ind]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[ind], environ[ind]);
	}
	new_env[ind] = NULL;

	return (new_env);
}

/**
 * error_env - Creates an error message for shellin_env errors
 * @args: An array of arguments passed to the cmd
 *
 * Return: The error which is a string
 */

char *error_env(char **args)
{
	char *err;
	char *histry_str;
	int leng;

	histry_str = int_to_str(hist);
	if (!histry_str)
		return (NULL);

	args--;
	leng = _strlength(name) + _strlength(histry_str) + _strlength(args[0]) + 45;
	err = malloc(sizeof(char) * (leng + 1));
	if (!err)
	{
		free(histry_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, histry_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Unable to add/remove from environment\n");

	free(histry_str);
	return (err);
}

/**
 * free_env - Frees the the environment copy
 * doesnt return anything
 */

void free_env(void)
{
	int ind;

	for (ind = 0; environ[ind]; ind++)
		free(environ[ind]);
	free(environ);
}

/**
 * _getenv - Gets an env variable from the PATH
 * @var: The name of the env variable to get
 *
 * Return: If the env variable does not exist - NULL
 * Otherwise - a pointer to the env variable.
 */

char **_getenv(const char *var)
{
	int ind, leng;

	leng = _strlength(var);
	for (ind = 0; environ[ind]; ind++)
	{
		if (_strncmp(var, environ[ind], leng) == 0)
			return (&environ[ind]);
	}

	return (NULL);
}
