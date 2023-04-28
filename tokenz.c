#include "shell.h"

int token_count(char *str, char *delimit);
char **_strtok(char *line, char *delimit);
int token_length(char *str, char *delimit);

/**
 * token_count - Counts the number of delimited
 * words contained inside a string
 * @str: The string to be searched
 * @delimit: The delimiter char
 *
 * Return: The no of words contained within str
 */

int token_count(char *str, char *delimit)
{
	int ind;
	int tokenz = 0;
	int leng = 0;

	for (ind = 0; *(str + ind); ind++)
		leng++;

	for (ind = 0; ind < leng; ind++)
	{
		if (*(str + ind) != *delimit)
		{
			tokenz++;
			ind += token_length(str + ind, delimit);
		}
	}

	return (tokenz);
}

/**
 * _strtok - Makes a string into tokens
 * @line: The string
 * @delim: The delimiter character to tokenize the string
 *
 * Return: A pointer to an array containing the tokenized char
 */

char **_strtok(char *line, char *delimit)
{
	char **ptr;
	int ind = 0;
	int tokenz;
	int x;
	int letterz;
	int q;

	tokenz = token_count(line, delimit);
	if (tokenz == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokenz + 2));
	if (!ptr)
		return (NULL);

	for (x = 0; x < tokenz; x++)
	{
		while (line[ind] == *delimit)
			ind++;

		letterz = token_length(line + ind, delimit);

		ptr[x] = malloc(sizeof(char) * (letterz + 1));
		if (!ptr[x])
		{
			for (ind -= 1; ind >= 0; ind--)
				free(ptr[ind]);
			free(ptr);
			return (NULL);
		}

		for (q = 0; q < letterz; q++)
		{
			ptr[x][q] = line[ind];
			ind++;
		}

		ptr[x][q] = '\0';
	}
	ptr[x] = NULL;
	ptr[x + 1] = NULL;

	return (ptr);
}

/**
 * token_length - Locates the delimiter index marking the end of
 * the first token contained within a string
 * @str: The string to be searched
 * @delimit: The delimiter character
 *
 * Return: The delimiter index marking the end of the
 * intitial token pointed to by str.
 */

int token_length(char *str, char *delimit)
{
	int ind = 0;
	int leng = 0;

	while (*(str + ind) && *(str + ind) != *delimit)
	{
		leng++;
		ind++;
	}

	return (leng);
}
