#include "shell.h"

int _strncmp(const char *s1, const char *s2, size_t q);
int _strlength(const char *c);
int _strsub(char *c, char *kubali);


/**
 * _strncmp - Compares two strings
 * @s1: Ptr to a string
 * @s2: Ptr to a string
 * @q: The first n bytes of the strings to be compared
 *
 * Return: Less than 0 if s1 is shorter than s2.
 * 0 if s1 and s2 match.Greater than 0 if s1 is longer than s2.
 */

int _strncmp(const char *s1, const char *s2, size_t q)
{
	size_t x;

	for (x = 0; s1[x] && s2[x] && x < q; x++)
	{
		if (s1[x] > s2[x])
			return (s1[x] - s2[x]);
		else if (s1[x] < s2[x])
			return (s1[x] - s2[x]);
	}
	if (x == q)
		return (0);
	else
		return (-15);
}

/**
 * _strlength - Returns the length of a string
 * @c: A pointer to the char string.
 *
 * Return: The length of the char string.
 */

int _strlength(const char *c)
{
	int leng = 0;

	if (!c)
		return (leng);
	for (leng = 0; c[leng]; leng++)
		;
	return (leng);
}

/**
 * _strsub - Gets the length of a prefixed substring
 * @c: The string to be searched
 * @kubali: The prefix to be measured
 *
 * Return: The number of bytes in c which consist
 * only of bytes from accept.
 */
int _strsub(char *c, char *kubali)
{
	int byt = 0;
	int ind;

	while (*c)
	{
		for (ind = 0; kubali[ind]; ind++)
		{
			if (*c == kubali[ind])
			{
				byt++;
				break;
			}
		}
		c++;
	}
	return (byt);
}
