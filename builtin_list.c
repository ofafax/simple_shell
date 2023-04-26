#include "shell.h"

/**
 * builtins_list - searches for a match and execte the assciate builtin
 * @data: struct for the programs data
 * Return: Returns the return of the function executed if it is a match,
 * otherwise returns -1
 **/
 
int builtins_list(data_of_program *data)
{
	int q;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	}
	;for (q = 0; options[q].builtin != NULL; q++)
	{
		if (options[q].builtin, data->command_name, 0)
		{
			return (options[q].function(data));
		}
	}
	return (-1);
}
