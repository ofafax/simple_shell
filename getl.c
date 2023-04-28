#include "shell.h"

void *_realloc(void *ptr, unsigned int old_mem_size, unsigned int new_mem_size);
void assign_lineptr(char **lineptr, size_t *t, char *buff, size_t q);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates memory using malloc and free
 * @ptr: A pointer to the memory previously allocated
 * @old_size: The size in bytes of the allocated space for a ptr
 * @new_size: The size in bytes for the new memory block to
 * be allocated
 *
 * Return: If new_size == old_size - ptr
 * If new_size == 0 and ptr is not NULL return  NULL
 * Otherwise return a pointer to the reallocated memory block
 */

void *_realloc(void *ptr, unsigned int old_mem_size, unsigned int new_mem_size)
{
	void *mem;
	char *ptr_copy;
	char *sth;
	unsigned int ind;

	if (new_mem_size == old_mem_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_mem_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_mem_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_mem_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	sth = mem;

	for (ind = 0; ind < old_mem_size && ind < new_mem_size; ind++)
		sth[ind] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assign_lineptr(char **lineptr, size_t *t, char *buff, size_t q)
{
	if (*lineptr == NULL)
	{
		if (q > 120)
			*t = q;
		else
			*t = 120;
		*lineptr = buff;
	}
	else if (*t < q)
	{
		if (q > 120)
			*t = q;
		else
			*t = 120;
		*lineptr = buff;
	}
	else
	{
		_strcpy(*lineptr, buff);
		free(buff);
	}
}

/**
 * _getline - Reads input from a stream
 * @lineptr: A buffer to store the input from the stream
 * @n: The size of lineptr.
 * @stream: The stream to br read from.
 *
 * Return: The number of bytes to be read.
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t retn;
	char c = 'x';
	char *buff;
	int x;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (c != '\n')
	{
		x = read(STDIN_FILENO, &c, 1);
		if (x == -1 || (x == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (x == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buff = _realloc(buff, input, input + 1);

		buff[input] = c;
		input++;
	}
	buff[input] = '\0';

	assign_lineptr(lineptr, n, buff, input);

	retn = input;
	if (x != 0)
		input = 0;
	return (retn);
}
