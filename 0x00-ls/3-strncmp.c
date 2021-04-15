#include "ls.h"
/**
 * _strncmp - compare two strings
 * @s1: string 1
 * @s2: string 2
 * @n: int
 * Return: value
 */


int _strncmp(char *s1, char *s2, int n)
{

	(void) n;

	if (*s1 == '.' && *(s1 + 1) != '.')
	{
		return (0);
	}
	return (*s1 - *s2);
}
