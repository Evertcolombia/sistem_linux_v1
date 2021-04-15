#include "ls.h"

/**
 * _strlen - show the lenght of a string
 * @s: pointe to  pass the array
 *
 * Return: none
 */
int _strlen(char *s)
{
	char *cp = s;

	while (*cp != '\0')
		cp++;
	return (cp - s);
}
