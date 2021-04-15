#include "ls.h"

/**
 * *_strncpy - concatenate two  strings with n bytes for the second
 * @dest: pointer to a string
 * @src: pointer to the strign to concatenate
 * @n: intger
 *
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	char *h = dest;
	int i;

	for (i = 0; i < n; i++)
		*dest++ = (*src != '\0') ? *src++ : '\0';
	dest = h;
	return (dest);
}
