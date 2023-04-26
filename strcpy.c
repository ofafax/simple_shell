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
{	int q, l;

	for (l = 0; src[l] != '\0'; l++)

	for (q = 0; q <= l; q++)
		dest[q] = src[q];
	return (dest);
}
