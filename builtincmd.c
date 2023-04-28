#include "shell.h"

int (*get_builtin(char *command))(char **args, char **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
char **replace_aliases(char **args);

/**
 * get_builtin - Matches a cmd with a following
 *               shellin builtin fnction
 * @command: The cmd to match.
 *
 * Return: A function pointer to the corresponding builtin
 * function
 */

int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funq[] = {
		{ "exit", shellin_exit },
		{ "env", shellin_set_env },
		{ "setenv", shellin_set_env },
		{ "unsetenv", shellin_del_env },
		{ "cd", shellin_cd },
		{ "alias", shellin_alias },
		{ "help", shellin_help },
		{ NULL, NULL }
	};
	int j;

	for (j = 0; funq[j].name; j++)
	{
		if (_strcmpr(funq[j].name, command) == 0)
			break;
	}
	return (funq[j].f);
}

/**
 * set_alias - sets an existing alias 'name' with a new value,
 * or creates a new alias with 'name' and 'value'
 * @var_name: Name of the alias created
 * @value: Value of the alias.First character is a '='
 */

void set_alias(char *var_name, char *value)
{
	alias_t *tmp = aliases;
	int leng, i, q;
	char *new_value;

	*value = '\0';
	value++;
	leng = _strlength(value) - _strsub(value, "'\"");
	new_value = malloc(sizeof(char) * (leng + 1));

	if (!new_value)
		return;
	for (i = 0, q = 0; value[i]; i++)
	{
		if (value[i] != '\'' && value[i] != '"')
			new_value[q++] = value[i];
	}
	new_value[q] = '\0';
	while (tmp)
	{
		if (_strcmpr(var_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_value;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_end_alias(&aliases, var_name, new_value);
}

/**
 * print_alias - Prints the alias in the format of name='value'
 * @alias: Pointer to an alias
 */

void print_alias(alias_t *alias)
{
	char *alias_str;
	int leng = _strlength(alias->name) + _strlength(alias->value) + 4;

	alias_str = malloc(sizeof(char) * (leng + 1));
	if (!alias_str)
		return;
	_strcpy(alias_str, alias->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->value);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, leng);
	free(alias_str);
}

/**
 * replace_aliases - replace any matching alias with its
 * value
 * @args: 2D pointer to the args
 *
 * Return: 2D pointer to the args
 */

char **replace_aliases(char **args)
{
	alias_t *tmp;
	int x;
	char *new_val;

	if (_strcmpr(args[0], "alias") == 0)
		return (args);
	for (x = 0; args[x]; x++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmpr(args[x], tmp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlength(tmp->value) + 1));
				if (!new_val)
				{
					free_args_mem(args, args);
					return (NULL);
				}
				_strcpy(new_val, tmp->value);
				free(args[x]);
				args[x] = new_val;
				x--;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (args);
}
