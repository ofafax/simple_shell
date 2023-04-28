#include "shell.h"

char *_strcat(char *des, const char *sstr);
char *_strchar(char *q, char r);
char *_strcpy(char *des, const char *sstr);
int _strcmpr(char *s1, char *s2);
char *_strncat(char *des, const char *sstr, size_t q);



/**
 * _strcat - Concantenates two strings.
 * @des: Pointer to destination string.
 * @sstr: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */

char *_strcat(char *des, const char *sstr)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = des;
	srcTemp =  sstr;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (des);
}

/**
 * _strchar - Locates a character in a string
 * @q: The string to be searched.
 * @r: The character to be located.
 *
 * Return: If q is found - a pointer to the first occurence.
 *         If cqis not found - NULL.
 */
char *_strchar(char *q, char r)
{
	int ind;

	for (ind = 0; q[ind]; ind++)
	{
		if (q[ind] == r)
			return (q + ind);
	}

	return (NULL);
}

/**
 * _strcpy - Copies the string pointed to by src, including
 * the terminating null byte, to the buffer pointed by des.
 * @des: Pointer to the destination of copied string.
 * @sstr: Pointer to the src of the source string.
 *
 * Return: Pointer to des
 */

char *_strcpy(char *des, const char *sstr)
{
	size_t x;

	for (x = 0; sstr[x] != '\0'; x++)
		des[x] = sstr[x];
	des[x] = '\0';
	return (des);
}

/**
 * _strcmpr - Compares two strings
 * @s1: The first string to be compared
 * @s2: The second string to be compared
 *
 * Return: Positive byte diff if s1 > s2,
 * 0 if s1 = s2, Negative byte difference if s1 < s2
 */

int _strcmpr(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncat - Concantenates two strings where n number
 * of bytes are copied from source.
 * @des: Pointer to destination string
 * @sstr: Pointer to source string
 * @q: n bytes to copy from src
 *
 * Return: Pointer to destination string.
 */

char *_strncat(char *des, const char *sstr, size_t q)
{
	size_t dest_len = _strlength(des);
	size_t x;

	for (x = 0; x < q && sstr[x] != '\0'; x++)
		des[dest_len + x] = sstr[x];
	des[dest_len + x] = '\0';

	return (des);
}
