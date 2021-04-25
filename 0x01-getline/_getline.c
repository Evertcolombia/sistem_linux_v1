#include "_getline.h"
#include <stdio.h>
#include <string.h>
#define READ_SIZE 1

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/**
 * _getline - get line from fd
 * @fd: file descriptor
 *
 * Return: char pointer
 */
char *_getline(const int fd)
{
	char *buf = NULL;
	int count = 0;
	int count_ch = 0;

	buf = (char *) malloc(READ_SIZE * sizeof(char));
	if (buf == NULL)
		return (NULL);

	count = get_l(fd, buf, count, count_ch);
	if (count == 0)
	{
		free(buf);
		return (NULL);
	}

	return (buf);
}

/**
 * get_l - recursive get char
 * @fd: file descriptor
 * @buf: buffer
 * @count: count total
 * @count_ch: int
 *
 * Return: int
 */
int get_l(const int fd, char *buf, int count, int count_ch)
{
	count_ch = read(fd, &buf[count], READ_SIZE);
	if ((count_ch == 0) || (count_ch == -1))
		return (count_ch);
	else if ((buf[count] == '\n'))
	{
		buf[count] = '\0';
		if (count == 0)
			return (++count);
		return (count);
	}
	else
	{
		count += count_ch;
		buf = (char *) _realloc(buf, count, count);
		if (buf)
			return (get_l(fd, buf, count, count_ch));
		return (count);
	}
}

/**
 * _realloc - entry point
 * @ptr: void variable
 * @old_size: unsigned int variable
 * @new_size: unsigned int variable
 * Return: ptr or NULL
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i = 0;
	char *new = NULL;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size * sizeof(char)));
	else if (new_size > old_size)
	{
		new = malloc(new_size * sizeof(char));
		for (i = 0; i < old_size; i++)
			new[i] = ((char *)ptr)[i];
	}
	free(ptr);
	return (new);
}
