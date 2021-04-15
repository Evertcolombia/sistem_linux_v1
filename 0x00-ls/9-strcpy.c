/**
 * _strcpy - copies the content of a string to other
 * @dest: ponter to save content
 * @src: pointer to copy content
 *
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	char *cp = dest;

	while ((*dest++ = *src++))
		;
	dest = cp;
	return (dest);
}
