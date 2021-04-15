#include "ls.h"

/**
 * open_directory - list files from a dir path
 * @dirp: DIR strem pointer
 * @path: pointer to pathname
 *
 * Return: None
 */
DIR *open_directory(DIR *dirp, char *path)
{
	char *msg;

	dirp = opendir(path);
	if (dirp == NULL)
	{
		if(errno == ENOENT)
		{
			msg = "No such file or directory";
			fprintf(stderr, "hls: cannot access '%s': %s\n", path, msg);
		}
		else if (errno == EACCES)
		{
			msg = "Permission denied";
			fprintf(stderr, "hls: cannot access %s: %s\n", path, msg);
		}
		exit(2);
	}

	return (dirp);
}

/**
 * listFiles - list files from a dir path
 * @dirpath: pointer to pathname
 * @arc: int
 *
 * Return: None
 */
void listFiles(const char *dirpath, int arc)
{
	DIR *dirp = NULL;
	struct dirent *dp;
	char *buffer, *copy = NULL;
	int ncase = 0;
	ls_c list;

	list_init(&list, NULL);
	dirp = open_directory(dirp, (char *) dirpath);

	copy = (char *) dirpath;
	if (_strcmp((char *) dirpath, "..") == 0)
		dirpath = "../";

	while ((dp = readdir(dirp)))
	{
		if (_strcmp(dp->d_name, ".") == 0 || _strcmp(dp->d_name, "..") == 0)
			continue;

		if (_strcmp((char *)dirpath, ".") == 0)
		{
			ncase = 0;
			statinfo(dp->d_name, dp->d_name, &list, false);
		}
		else
		{
			buffer = allocBuf(buffer, (char *)dirpath, dp->d_name);
			statinfo(buffer, dp->d_name, &list, true);
		}
	}

	print_safe(arc, &list, ncase, copy);
	if (closedir(dirp) == -1)
	{
		perror("closedir");
		exit(EXIT_FAILURE);
	}
}

/**
 * print_safe - print safe
 * @arc: int
 * @list: linked l controller
 * @ncase: int
 * @copy: char pointer
 *
 * Retur: none
 */
void print_safe(int arc, ls_c *list, int ncase, char *copy)
{
	if (arc > 2)
		fprintf(stdout, "%s:\n", copy);

	print_list_safe(list, list->head, ncase);

	if (arc > 2 && list->size > 0)
		fprintf(stdout, "%c", '\n');

	list_destroy(list);
}

/**
 * statinfo - gets file and dir content
 * @pathname: path to go
 * @name: name of the file /dir
 * @list: linked list controller
 * @isFree: flag
 */
void statinfo(const char *pathname, char *name, ls_c *list, bool isFree)
{
	struct stat sb;

	if (lstat(pathname, &sb) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	list_ins_next(list, list->last_in, name);
	if (isFree)
		free((char *)pathname);
}
