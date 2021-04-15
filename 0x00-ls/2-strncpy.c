/*This program copy two strings with n of bytes*/

/**
 * *_strncat - concatenate two  strings with n bytes for the second
 * @dest: pointer to a string
 * @src: pointer to the strign to concatenate
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
