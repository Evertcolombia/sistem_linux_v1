#include "ls.h"

/**
 * main - main function program
 * @argc: integer
 * @argv: array pointers\
 *
 * Return: integer
 */
int main(int argc, char *argv[])
{
	_opts ar_opts, *f_ops;
	ls_c f_list;

	if (argc > 1 && _strcmp(argv[1], "--help") == 0)
		exit(EXIT_FAILURE);

	ar_opts.fA = ar_opts.fa = ar_opts.f1 = 0;
	ar_opts.count = ar_opts.pathCount = ar_opts.fileCount = 0;
	f_ops = &ar_opts;
	list_init(&f_list, NULL);
	
	if (argc == 1)
		listFiles(".", argc, f_ops, NULL);
	else if (argc >= 2)
	{
		f_ops = arv_mannager(argv, f_ops, &f_list);
		if (argc == 2)
		{
			if (f_ops->count > 0)
				listFiles(".", argc, f_ops, NULL);
			else
				listFiles(argv[1], argc, f_ops, &f_list);
		}
		else
		{
			argv += 1;
			if (f_ops->pathCount == 0 && f_ops->count > 0)
				listFiles(".", argc, f_ops, NULL);

			else if (*argv)
			{
				for (; *argv; argv++)
				{
					if (*argv[0] != '-')
						listFiles(*argv, argc, f_ops, &f_list);
				}
			}
		}
	}
	list_destroy(&f_list);
	return (0);
}

/**
 * arv_mannager - mannage argv flags
 * @arv: char to pointer array
 * @ar_opts: struct to save flags
 *
 * Return: flags struct
 */
_opts *arv_mannager(char *arv[], _opts *ar_opts, ls_c *f_list)
{
	char *p;
	struct stat sb;
	int i;

	for (i = 1; arv[i]; i++)
	{
		if (arv[i][0] == '-' && arv[i][1] != '\0')
		{
			p =  (char *) (arv[i] + 1);
			while (*p)
			{
				if (*p == '1')
					ar_opts->f1 = 1, ar_opts->count++;
				else if (*p == 'a')
					ar_opts->fa = 1, ar_opts->count++;
				else if (*p == 'A')
					ar_opts->fA = 1, ar_opts->count++;
				p++;
			}
		}
		else
		{
			if (lstat(arv[i], &sb) == 0)
			{
				switch (sb.st_mode & S_IFMT)
				{
					case S_IFREG:
					list_ins_next(f_list, f_list->last_in, arv[i]);
					ar_opts->fileCount++;
					break;
					case S_IFDIR:
						ar_opts->pathCount++;
						break;
				}
			}
		}
	}
	return (ar_opts);
}
