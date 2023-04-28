#include "shell.h"

void partition_line(char **line, ssize_t length);
ssize_t get_new_length(char *line);
void logic_operator(char *line, ssize_t *new_length);

/**
 * partition_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @length: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||",
 * and "&&".Replaces "#" with '\0'.
 */

void partition_line(char **line, ssize_t length)
{
	char *old_line, *new_line;
	char prev, curr, next;
	size_t x, q;
	ssize_t new_leng;

	new_leng = get_new_length(*line);
	if (new_leng == length - 1)
		return;
	new_line = malloc(new_leng + 1);
	if (!new_line)
		return;
	q = 0;
	old_line = *line;
	for (x = 0; old_line[x]; x++)
	{
		curr = old_line[x];
		next = old_line[x + 1];
		if (x != 0)
		{
			prev = old_line[x - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					new_line[q++] = ' ';
					new_line[q++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					new_line[q++] = ';';
					new_line[q++] = ' ';
					continue;
				}
				if (prev != ' ')
					new_line[q++] = ' ';
				new_line[q++] = ';';
				if (next != ' ')
					new_line[q++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					new_line[q++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					new_line[q++] = '&';
					new_line[q++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					new_line[q++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					new_line[q++] = '|';
					new_line[q++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (x != 0 && old_line[x - 1] != ' ')
				new_line[q++] = ' ';
			new_line[q++] = ';';
			if (next != ' ' && next != ';')
				new_line[q++] = ' ';
			continue;
		}
		new_line[q++] = old_line[x];
	}
	new_line[q] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_length - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_length(char *line)
{
	size_t x;
	ssize_t new_len = 0;
	char curr;
	char next;

	for (x = 0; line[x]; x++)
	{
		curr = line[x];
		next = line[x + 1];
		if (curr == '#')
		{
			if (x == 0 || line[x - 1] == ' ')
			{
				line[x] = '\0';
				break;
			}
		}
		else if (x != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line[x - 1] != ' ' && line[x - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[x - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[x - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logic_operator(&line[x], &new_len);
		}
		else if (curr == ';')
		{
			if (x != 0 && line[x - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logic_operator - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logic_operator(char *line, ssize_t *new_length)
{
	char prev, curr, next;

	prev = *(line - 1);
	curr = *line;
	next = *(line + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
			(*new_length)++;
		else if (prev == '&' && next != ' ')
			(*new_length)++;
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
			(*new_length)++;
		else if (prev == '|' && next != ' ')
			(*new_length)++;
	}
}
