#include "shell.h"

/**
 * _strcpy - copies the string pointed to by pointer src
 * includng the terminating null byte char ('\0')
 * to the buffer pointed to by dest
 * @dest: copies source to this buffer
 * @src: source to be copied
 * Return: original source copy
 */

char *_strcpy(char *dest, char *src)
{	int x, j;

	for (j = 0; src[j] != '\0'; j++)

	for (x = 0; x <= j; x++)
		dest[x] = src[x];
	return (dest);
}
