#include "ls.h"

/**
 * error_mannager - errno controller
 * @errid: errno num
 * @isDir: know if is dir
 * @path: char path
 * @list: linked list controller
 */
void error_mannager(int errid, bool isDir, char *path, ls_c *list)
{
	char *msg = NULL;

	if (errid == ENOENT)
	{
		msg = "No such file or directory";
		fprintf(stderr, "hls: cannot access '%s': %s\n", path, msg);
	}
	else if (errid == EACCES)
	{
		msg = "Permission denied";
		fprintf(stderr, "hls: cannot open directory '%s': %s\n", path, msg);
	}
	else if (errid == ENOTDIR)
	{
		(void) isDir;
		(void) list;
	}
	exit(EXIT_FAILURE);
}
