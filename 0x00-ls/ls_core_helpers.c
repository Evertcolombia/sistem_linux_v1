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
	char *buff = NULL;

	if (pass_hidden(name) == 0)
		return (0);

	else if (_strcmp(path, ".") == 0)
		statinfo(path, name, list, false);
	else
	{
		buff = path_controller(path, name);
		statinfo(buff, name, list, true);
	}
	return (0);
}

/**
 * get_flags - mannage the control for flags
 * @name: char name
 * @path: char path
 * @list: list controller
 * @_opts: flags structure
 *
 * Return: int
 */
int get_flags(char *name, char *path, ls_c *list, _opts *_opts)
{
	char *buff = NULL;

	/*
	 * if (_opts->fa != 0)
	*{
	*	//
	*}
	*/
	if (_opts->f1 != 0)
	{
		if (pass_hidden(name) == 0)
			return (0);

		if (_strcmp(path, ".") == 0)
			statinfo(path, name, list, false);
		else
		{
			buff = path_controller(path, name);
			statinfo(buff, name, list, true);
		}

	}
	return (0);
}

/**
 * pass_hidden - pass hidden files / dir
 * @name: name of the file / dir
 *
 * Return: int
 */
int pass_hidden(char *name)
{
	if (_strcmp(name, ".") == 0 || _strcmp(name, "..") == 0)
		return (0);
	else if (_strncmp(name, ".", 1) == 0)
		return (0);
	return (1);
}

/**
 * path_controller - controller path
 * @path: path of file / dir
 * @name: char name
 *
 * Return: pointer to char
 */
char *path_controller(char *path, char *name)
{
	char *pc = "../", *buff = NULL;

	if (_strstr(path, pc) != NULL)
		buff = allocBuf(buff, path, name, NULL);
	else
		buff = allocBuf(buff, path, name, "/");

	return (buff);
}
