#include "shell.h"

void help_env(void);
void help_help(void);
void help_setenv(void);
void help_unsetenv(void);

/**
 * help_env - Shows info on the builtin shellin command 'env'.
 */
void help_env(void)
{
	char *mseg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, mseg, _strlength(mseg));
}

/**
 * help_help - Shows info on the builtin shellin command 'help'.
 */

void help_help(void)
{
	char *mseg = "help: help\n\tSee all possible Shellin builtin commands.\n";

	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "\n      help [BUILTIN NAME]\n\tSee specific info on each ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "builtin command.\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
}

/**
 * help_setenv - Shows info on the builtin shellin command 'setenv'
 */

void help_setenv(void)
{
	char *mseg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a ";

	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "new environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "\tUpon failure, it prints a message to stderr.\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
}

/**
 * help_unsetenv - Shows info on the shellin builtin command
 * 'unsetenv'
 */

void help_unsetenv(void)
{
	char *mseg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "env variable.\n\n\tUpon failure, prints a message ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "to stderr.\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
}
