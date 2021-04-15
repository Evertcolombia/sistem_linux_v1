#include "ls.h"

void statinfo(const char *pathname, char *name, ls_c *list, bool isFree);
/**
 * listFiles - list files from a dir path
 * @dirpath: pointer to pathname
 *
 * Return: None
 */
void listFiles(const char *dirpath)
{
	DIR *dirp;
	struct dirent *dp;
	char /**buffer,*/ *msg;
	int ncase = 0;
	ls_c list;

	list_init(&list, NULL);
	/*bool isCurrent;*/	/* True if 'dirpath' is "." */
	/*isCurrent = _strcmp(dirpath, ".") == 0;*/

	dirp = opendir(dirpath);
	if (dirp == NULL)
	{
		msg = "No such file or directory";
		fprintf(stderr, "hls: cannot access '%s': %s\n", dirpath, msg);
		exit(EXIT_FAILURE);
	}

	for (;;)
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break;

		if (_strcmp(dp->d_name, ".") == 0 || _strcmp(dp->d_name, "..") == 0)
			continue;

		statinfo(dp->d_name, dp->d_name, &list, false);
		/**
		 * if (_strcmp((char *)dirpath, ".") == 0)
		 * {
		 * ncase = 0;
		 * statinfo(dp->d_name, dp->d_name, &list, false);
		 * }
		 * else
		 * {
		 * buffer = allocBuf(buffer, (char *)dirpath, dp->d_name);
		 * statinfo(buffer, dp->d_name, &list, true);
		 * }
		 */
	}

	print_list_safe(&list, list.head, ncase);
	list_destroy(&list);
	if (closedir(dirp) == -1)
	{
		perror("closedir");
		exit(EXIT_FAILURE);
	}
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
	/*struct passwd *pp;*/
	/*char *type = NULL;*/
	if (lstat(pathname, &sb) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	list_ins_next(list, list->last_in, name);
	if (isFree)
		free((char *)pathname);
	return;

}
