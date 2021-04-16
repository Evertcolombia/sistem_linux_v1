#include "ls.h"

/**
 * get_no_flags - mannage the control for no flags
 * @name: name of the file / dir
 * @path: path file /dir
 * @list: linked list controller
 *
 * Return: int
 */

int get_no_flags(char *name, char *path, ls_c *list)
{
	char *buff = NULL, *p = NULL, *pc = "../";

	if (_strcmp(name, ".") == 0 || _strcmp(name, "..") == 0)
		return (0);

	else if (_strncmp(name, ".", 1) == 0)
		return (0);

	else if (_strcmp(path, ".") == 0)
		statinfo(path, name, list, false);
	else
	{
		p = _strstr(path, pc);
		if (p != NULL)
		{
			buff = allocBuf(buff, path, name, NULL);
		}
		else
		{
			buff = allocBuf(buff, path, name, "/");
		}
		return (statinfo(buff, name, list, true));
	}
	return (0);
}
