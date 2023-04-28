#include "shell.h"


char *error_alias(char **args);
char *error_exit(char **args);
char *error_cd(char **args);
char *error_syntax(char **args);


/**
 * error_alias - Creates an error message for shellin_alias error.
 * @args: An array of arguments passed to the cmd.
 *
 * Return: The error string
 */

char *error_alias(char **args)
{
	char *err;
	int leng;

	leng = _strlength(name) + _strlength(args[0]) + 13;
	err = malloc(sizeof(char) * (leng + 1));
	if (!err)
		return (NULL);

	_strcpy(err, "alias: ");
	_strcat(err, args[0]);
	_strcat(err, " not found\n");

	return (err);
}

/**
 * error_exit - Creates an error message for shellin_exit error
 * @args: An array of arguments passed to the cmd
 *
 * Return: The error string
 */
char *error_exit(char **args)
{
	char *err;
	char *histry_str;
	int leng;

	histry_str = int_to_str(hist);
	if (!histry_str)
		return (NULL);

	leng = _strlength(name) + _strlength(histry_str) + _strlength(args[0]) + 27;
	err = malloc(sizeof(char) * (leng + 1));
	if (!err)
	{
		free(histry_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, histry_str);
	_strcat(err, ": exit: Illegal number: ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(histry_str);
	return (err);
}

/**
 * error_cd - Creates an error message for shellin_cd error
 * @args: An array of arguments passed to the cmd
 *
 * Return: The error string
 */

char *error_cd(char **args)
{
	char *err;
	char *histry_str;
	int leng;

	histry_str = int_to_str(hist);
	if (!histry_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	leng = _strlength(name) + _strlength(histry_str) + _strlength(args[0]) + 24;
	err = malloc(sizeof(char) * (leng + 1));
	if (!err)
	{
		free(histry_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, histry_str);
	if (args[0][0] == '-')
		_strcat(err, ": cd: Illegal option ");
	else
		_strcat(err, ": cd: can't cd to ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(histry_str);
	return (err);
}

/**
 * error_syntax - Creates an error message for syntax error
 * @args: An array of arguments passed to the cmd
 *
 * Return: The error string
 */

char *error_syntax(char **args)
{
	char *err;
	char *histry_str;
	int leng;

	histry_str = int_to_str(hist);
	if (!histry_str)
		return (NULL);

	leng = _strlength(name) + _strlength(histry_str) + _strlength(args[0]) + 33;
	err = malloc(sizeof(char) * (leng + 1));
	if (!err)
	{
		free(histry_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, histry_str);
	_strcat(err, ": Syntax error: \"");
	_strcat(err, args[0]);
	_strcat(err, "\" unexpected\n");

	free(histry_str);
	return (err);
}
