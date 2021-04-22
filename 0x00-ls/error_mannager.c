#include "ls.h"

/**
 * error_mannager - errno controller
 * @errid: errno num
 * @isDir: know if is dir
 * @path: char path
 * @list: linked list controller
 */
int error_mannager(int errid, char *path, ls_c *f_list, _opts *opts)
{
	char *msg = NULL;

	if (errid == ENOENT)
	{
		msg = "No such file or directory";
		fprintf(stderr, "hls: cannot access %s: %s\n", path, msg);
		exit(EXIT_FAILURE);
	}
	else if (errid == EACCES)
	{
		msg = "Permission denied";
		fprintf(stderr, "hls: cannot open directory %s: %s\n", path, msg);
		exit(EXIT_FAILURE);
	}
	else if (errid == ENOTDIR)
	{
		print_files(f_list, opts);
		list_destroy(f_list);
		return (1);
	}

	return (0);
}
