#include "shell.h"

/**
 * _strtok - separates a string with delimiters
 * @line: It is a pointer to an array that we receive in getline
 * @delim: It is characters that we mark off strings in parts
 * Return: the pointer to the created token
*/

char *_strtok(char *line, char *delim)
{
	int v;
	static char *sttc;
	char *c;

	if (line != NULL)
		s = line;
	for (; *sttc != '\0'; sttc++)
	{
		for (v = 0; delim[v] != '\0'; v++)
		{
			if (*sttc == delim[v])
			break;
		}
		if (delim[v] == '\0')
			break;
	}
	c = sttc;
	if (*c == '\0')
		return (NULL);
	for (; *sttc != '\0'; sttc++)
	{
		for (v = 0; delim[v] != '\0'; v++)
		{
			if (*sttc == delim[v])
			{
				*sttc = '\0';
				sttc++;
				return (c);
			}
		}
	}
	return (c);
}
