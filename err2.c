#include "shell.h"

int create_custom_stderr(char **args, int err);
char *int_to_str(int num);
int num_len(int num);
char *error_126(char **args);
char *error_127(char **args);

/**
 * create_custom_stderr - Writes a custom error message to stderr
 * @args: An array of arguments
 * @err: The value of the error
 *
 * Return: The value of the error
 */

int create_custom_stderr(char **args, int err)
{
	char *errorz;

	switch (err)
	{
	case -1:
		errorz = error_env(args);
		break;
	case 1:
		errorz = error_alias(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			errorz = error_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			errorz = error_syntax(args);
		else
			errorz = error_cd(args);
		break;
	case 126:
		errorz = error_126(args);
		break;
	case 127:
		errorz = error_127(args);
		break;
	}
	write(STDERR_FILENO, errorz, _strlength(errorz));

	if (errorz)
		free(errorz);
	return (err);

}

/**
 * int_to_str - Converts an integer to a string
 * @num: The integer to be converted
 *
 * Return: The converted string
 */

char *int_to_str(int num)
{
	char *buff;
	int leng = num_len(num);
	unsigned int num1;

	buff = malloc(sizeof(char) * (leng + 1));
	if (!buff)
		return (NULL);

	buff[leng] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buff[0] = '-';
	}
	else
	{
		num1 = num;
	}

	leng--;
	do {
		buff[leng] = (num1 % 10) + '0';
		num1 /= 10;
		leng--;
	} while (num1 > 0);

	return (buff);
}

/**
 * num_len - Counts the digit length of a no
 * @num: The number to be measured
 *
 * Return: The length of the digits
 */

int num_len(int num)
{
	unsigned int numx;
	int leng = 1;

	if (num < 0)
	{
		leng++;
		numx = num * -1;
	}
	else
	{
		numx = num;
	}
	while (numx > 9)
	{
		leng++;
		numx /= 10;
	}

	return (leng);
}

/**
 * error_126 - Creates an error message for permission denied failure
 * @args: An array of arguments passed to the cmd
 *
 * Return: The error which is a string
 */

char *error_126(char **args)
{
	char *err;
	char *histry_str;
	int leng;

	histry_str = int_to_str(hist);
	if (!histry_str)
		return (NULL);

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
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Permission denied\n");

	free(histry_str);
	return (err);
}

/**
 * error_127 - Creates an error message for cmd not found failure
 * @args: An array of arguments passed to the cmd
 *
 * Return: The error which is a string
 */

char *error_127(char **args)
{
	char *err;
	char *histry_str;
	int leng;

	histry_str = int_to_str(hist);
	if (!histry_str)
		return (NULL);

	leng = _strlength(name) + _strlength(histry_str) + _strlength(args[0]) + 16;
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
	_strcat(err, ": not found\n");

	free(histry_str);
	return (err);
}
