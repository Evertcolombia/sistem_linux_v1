#include "ls.h"

/**
 * allocBuf - allocates memory for a buffer
 * @dest: destine
 * @path: pointer
 * @name: pointer
 *
 * Return: pointer to char
 */

char *allocBuf(char *dest, char *path, char *name)
{
	int len = 0;

	len = 1 + _strlen(path) + _strlen(name);
	dest = (char *) malloc(len * sizeof(char));
	if (!dest)
	{
		fprintf(stderr, "%s\n", "Error in malloc");
		exit(EXIT_FAILURE);
	}

	dest = _strcpy(dest, path);
	dest = _strcat(dest, name);
	return (dest);
}
