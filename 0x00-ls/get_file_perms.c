#include "ls.h"

#define STR_SIZE sizeof("rwxrwxrwx")

char *filePermStr(mode_t perm)
{
	static char str[STR_SIZE];

	sprintf(str, "%c%c%c%c%c%c%c%c%c",
		(perm & S_IRUSR) ? 'r' : '-', (perm & S_IWUSR) ? 'w' : '-',
		(perm & S_IXUSR) ? 'x' : '-', (perm & S_IRGRP) ? 'r' : '-',
		(perm & S_IWGRP) ? 'w' : '-', (perm & S_IXGRP) ? 'x' : '-',
		(perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-',
		(perm & S_IXOTH) ? 'x' : '-');
	return (str);
}

char fileTypeStr(mode_t type)
{
	char dest;
	switch(type & S_IFMT) {
		case S_IFREG:
			dest = '-';
			break;
		case S_IFDIR:
			dest = 'd';
			break;
	}
	return (dest);
}

char *getLastModTime(time_t mtime)
{
	char *time = NULL;
	int len = 0;

	time = ctime(&mtime);
	len = _strlen(time);
	if (time[len - 1] == '\n')
		time[len - 1] = '\0';
	/*printf("%c\n", time[len - 4]);*/
	return (time);
}
