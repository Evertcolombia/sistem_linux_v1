#include "ls.h"

/**
 * open_directory - list files from a dir path
 * @dirp: DIR strem pointer
 * @path: pointer to pathname
 * @list: linked list controller
 *
 * Return: DIR stream on success
 */
DIR *open_directory(DIR *dirp, char *path, ls_c *list)
{
	dirp = opendir(path);
	if (dirp == NULL)
	{
		error_mannager(errno, true, path, list);
	}

	return (dirp);
}

/**
 * listFiles - list files from a dir path
 * @dirpath: pointer to pathname
 * @arc: int
 * @ar_opts: flag structs
 *
 * Return: None
 */
void listFiles(const char *dirpath, int arc, _opts *ar_opts)
{
	DIR *dirp = NULL;
	struct dirent *dp;
	char *copy = NULL;
	ls_c list;

	list_init(&list, NULL);
	dirp = open_directory(dirp, (char *) dirpath, &list);

	copy = (char *) dirpath;
	if (_strcmp((char *) dirpath, "..") == 0)
		dirpath = "../";

	while ((dp = readdir(dirp)))
	{
		if (ar_opts->count == 0)
		{
			get_no_flags(dp->d_name, (char *) dirpath, &list);
		}
		else
		{
			get_flags(dp->d_name, (char *) dirpath, &list, ar_opts);
		}
	}
	print_safe(arc, &list, copy, ar_opts);
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
 * @copy: char pointer
 *
 * Retur: none
 */
void print_safe(int arc, ls_c *list, char *copy, _opts *_opts)
{
	static int count = 1;

	if (arc > 2 && list->size > 0 && _opts->count == 0)
		fprintf(stdout, "%s:\n", copy);

	if (arc > 3 && _opts->count != 0)
		fprintf(stdout, "%s:\n", copy);

	print_list_safe(list, list->head, _opts);

	if (arc > 2 && list->size > 0 && count < (arc - 1))
		fprintf(stdout, "%c", '\n');

	if (_opts->f1 > 0 && count < (arc - 2))
		fprintf(stdout, "%c", '\n');
	count++;
	list_destroy(list);
}

/**
 * statinfo - gets file and dir content
 * @pathname: path to go
 * @name: name of the file /dir
 * @list: linked list controller
 * @isFree: flag
 *
 * Return: int
 */
int statinfo(const char *pathname, char *name, ls_c *list, bool isFree)
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
	return (0);
}
