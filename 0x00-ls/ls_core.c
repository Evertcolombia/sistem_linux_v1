#include "ls.h"

void displayStatinfo(const char *pathname, char *name, ls_c *list, bool isFree);

void listFiles(const char *dirpath)
{
	DIR *dirp;
	struct dirent *dp;
	char *buffer;
	int ncase = 0;
	ls_c list;

	list_init(&list, NULL);
	/*bool isCurrent;*/	/* True if 'dirpath' is "." */
	/*isCurrent = _strcmp(dirpath, ".") == 0;*/

	dirp = opendir(dirpath);
	if (dirp == NULL) {
		perror("opendir");
		return;
	}

	for (;;) {
		dp = readdir(dirp);
		if (dp == NULL)
			break;

		if (_strcmp(dp->d_name, ".") == 0 || _strcmp(dp->d_name, "..") == 0)
			continue;
		
		if (_strcmp((char *)dirpath, ".") == 0) {
			ncase = 0;
			displayStatinfo(dp->d_name, dp->d_name, &list, false);
		}
		else {
			buffer = allocBuf(buffer, (char *)dirpath, dp->d_name);
			displayStatinfo(buffer, dp->d_name, &list, true);
		}
	}
	
	print_list_safe(&list, list.head, ncase);
	list_destroy(&list);
	if (closedir(dirp) == -1) {
		perror("closedir");
		return;
	}
}

void displayStatinfo(const char *pathname, char *name, ls_c *list, bool isFree)
{
	struct stat sb;
	/*struct passwd *pp;*/
	/*char *type = NULL;*/
	if (lstat(pathname, &sb) == -1) {
		perror("lstat");
		return;
	}
	list_ins_next(list, list->last_in, name);
	/*
	printf("UID = %ld\n",(long) sb.st_uid);
	pp = getpwuid(sb.st_uid);
	printf("%c%s ", fileTypeStr(sb.st_mode), filePermStr(sb.st_mode));
	if (pp != NULL)
		printf("%s ", pp->pw_dir);
	printf("%lld ", (long long) sb.st_size);
	printf("%s ", getLastModTime(sb.st_mtime));
	printf("%s\n", name);
	*/
	if (isFree)
		free((char *)pathname);
	return;

}
