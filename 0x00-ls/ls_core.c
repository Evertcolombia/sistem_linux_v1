#include "ls.h"

/**
 * open_directory - list files from a dir path
 * @dirp: DIR strem pointer
 * @path: pointer to pathname
 *
 * Return: DIR stream on success
 */
DIR *open_directory(DIR *dirp, char *path)
{
	dirp = opendir(path);
	if (dirp == NULL)
	{
		if (error_mannager(errno, path) == 1)
			return (NULL);
	}

	return (dirp);
}

/**
 * listFiles - list files from a dir path
 * @dirpath: pointer to pathname
 * @arc: int
 * @ar_opts: flag structs
 * @f_list: file list controller
 *
 * Return: None
 */
void listFiles(const char *dirpath, int arc, _opts *ar_opts, ls_c *f_list)
{
	DIR *dirp = NULL;
	struct dirent *dp;
	char *copy = NULL;
	ls_c list;

	list_init(&list, NULL);
	dirp = open_directory(dirp, (char *) dirpath);

	if (dirp == NULL && ar_opts->pathCount == 0)
		return;
	else if (dirp == NULL)
		return;

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
	if (ar_opts->fileCount > 0)
		print_files(f_list, ar_opts);
	print_safe(arc, &list, copy, ar_opts);
	if (closedir(dirp) == -1)
	{
		perror("closedir");
		exit(EXIT_FAILURE);
	}
}

/**
 * print_files - printf files list
 * @f_list: file list controller
 * @opts: flags struct
 *
 * Return: None
 */
void print_files(ls_c *f_list, _opts *opts)
{
	if (list_size(f_list) > 0)
	{
		if (opts->f1 > 0)
			print_vertical(list_size(f_list), f_list->head);
		else
		{
			print_horizontal(list_size(f_list), f_list->head);
			printf("\n");
		}
	}
}
/**
 * print_safe - print safe
 * @arc: int
 * @list: linked l controller
 * @copy: char pointer
 * @_opts: flags structure
 * Retur: none
 */
void print_safe(int arc, ls_c *list, char *copy, _opts *_opts)
{
	static int count = 1;
	(void) arc;

	if (_opts->pathCount >= 2 && list->size > 0)
		fprintf(stdout, "%s:\n", copy);
	else if (_opts->pathCount == 1 && _opts->fileCount > 0)
	{
		_opts->fileCount = 0;
		fprintf(stdout, "%s:\n", copy);
	}
	print_list_safe(list, list->head, _opts);
	if (_opts->pathCount >= 2 &&  list->size >  0 && count < _opts->pathCount)
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
