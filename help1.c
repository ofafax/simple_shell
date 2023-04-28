#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);

/**
 * help_all - Displays all possible builtin shellin commands
 */

void help_all(void)
{
	char *mseg = "Shellin\nThese shell commands are defined here.\n";

	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "Type 'help' to see the list.\nType 'help name' to find ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "Find out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
}

/**
 * help_alias - Shows info on the builtin shellin command 'alias'
 */

void help_alias(void)
{
	char *mseg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "the format of NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
}

/**
 * help_cd - Shows info on the builtin shellin command 'cd'.
 */

void help_cd(void)
{
	char *mseg = "cd: cd [DIRECTORY]\n\tChanges the current directory";

	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "\tThe environment variables PWD and OLDPWD are thus ";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "updated after a change of directory.\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
}

/**
 * help_exit - Shows info on the builtin shellin command 'exit'
 */

void help_exit(void)
{
	char *mseg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = "STATUS argument is the int used to exit the shell.";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = " If no arg is given, the command is interpreted as";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
	mseg = " exit 0.\n";
	write(STDOUT_FILENO, mseg, _strlength(mseg));
}
