#include "ls.h"

/**
 * allocBuf - allocates memory for a buffer
 * @dest: destine
 * @path: pointer
 * @name: pointer
 * @com: char comparision
 *
 * Return: pointer to char
 */

char *allocBuf(char *dest, char *path, char *name, char *com)
{
	int len = 0;

	if (com != NULL)
		len = 1 + _strlen(com) + _strlen(path) + _strlen(name);
	else
		len = 1 + _strlen(path) + _strlen(name);
	dest = (char *) malloc(len * sizeof(char));
	if (!dest)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	dest = _strcpy(dest, path);
	if (com != NULL)
		dest = _strcat(dest, com);
	dest = _strcat(dest, name);

	return (dest);
}

/**
 * print_horizontal - print horizontal form
 * @size: size of the list
 * @head: head of the list
 *
 * Return: int
 */
int print_horizontal(int size, ls_n *head)
{
	int i = 0;

	while (i < size)
	{
		if (i + 1 == size)
			fprintf(stdout, "%s\n", head->name);
		else
			fprintf(stdout, "%s  ", head->name);
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * print_vertical - print in vertical form
 * @size: size of the list
 * @head: head of the list
 *
 * Return: int
 */
int print_vertical(int size, ls_n *head)
{
	int i = 0;

	while (i < size)
	{
		if (i + 1 == size)
			fprintf(stdout, "%s", head->name);
		else
			fprintf(stdout, "%s\n", head->name);
		head = head->next;
		i++;
	}
	return (i);
}
