#include "shell.h"
/**
 * _strtok - separates strings with delimiters
 * @line: It´s pointer to array we receive in getline.
 * @delim: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int v;
	static char *s;
	char *c;

	if (line != NULL)
		s = line;
	for (; *s != '\0'; s++)
	{
		for (v = 0; delim[v] != '\0'; v++)
		{
			if (*s == delim[v])
			break;
		}
		if (delim[v] == '\0')
			break;
	}
	c = s;
	if (*c == '\0')
		return (NULL);
	for (; *s != '\0'; s++)
	{
		for (v = 0; delim[v] != '\0'; v++)
		{
			if (*s == delim[v])
			{
				*s = '\0';
				s++;
				return (c);
			}
		}
	}
	return (c);
}
