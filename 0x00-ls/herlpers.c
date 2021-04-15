#include "ls.h"

char *allocBuf(char *dest, char *path, char *name)
{
	int len = 0;

	len = 1 + _strlen(path) + _strlen(name);
	dest = (char *) malloc(len * sizeof(char));
	if (!dest) {
		fprintf(stderr, "%s\n", "Error in malloc");
		return (NULL);
	}
	
	dest = _strcpy(dest, path);
	dest = _strcat(dest, name);
	return (dest);
}
