#include "shell.h"

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: copy source to this buffer
 * @src: this is the source to copy
 * Return: copy of original source
 */

char *_strcpy(char *dest, char *src)
{	int q, l;

	for (l = 0; src[l] != '\0'; l++)

	for (q = 0; q <= l; q++)
		dest[q] = src[q];
	return (dest);
}
