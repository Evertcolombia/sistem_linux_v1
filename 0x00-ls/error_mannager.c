#include "ls.h"

/**
 * error_mannager - errno controller
 * @errid: errno num
 * @path: char path
 * Return: int
 */
int error_mannager(int errid, char *path)
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
}
