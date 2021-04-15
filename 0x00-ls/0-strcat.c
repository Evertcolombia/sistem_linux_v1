#include "ls.h"
/**
 * *_strcat - concatenate two strings
 * @dest: pointer to a string
 * @src: pointer to the strign to concatenate
 *
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	char *head = dest;

	for (; *dest != '\0'; dest++)
		;
	while ((*dest++ = *src++))
		;
	dest = head;
	return (dest);
}
