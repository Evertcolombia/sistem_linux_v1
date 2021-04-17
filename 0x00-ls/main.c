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

	if (argc > 1 && _strcmp(argv[1], "--help") == 0)
		exit(EXIT_FAILURE);

	ar_opts.fa = 0, ar_opts.f1 = 0, ar_opts.count = 0;
	f_ops = &ar_opts;

	if (argc == 1)
		listFiles(".", argc, f_ops);
	else if (argc >= 2)
	{
		f_ops = arv_mannager(argv, f_ops);
		if (argc == 2)
		{
			if (f_ops->fa == 1 || f_ops->f1 == 1)
				listFiles(".", argc, f_ops);
			else
				listFiles(argv[1], argc, f_ops);
		}
		else
		{
			argv += 1;
			if (*argv)
			{
				for (; *argv; argv++)
				{
					if (*argv[0] != '-')
						listFiles(*argv, argc, f_ops);
				}
			}
		}
	}
	return (0);
}

/**
 * arv_mannager - mannage argv flags
 * @arv: char to pointer array
 * @ar_opts: struct to save flags
 *
 * Return: flags struct
 */
_opts *arv_mannager(char *arv[], _opts *ar_opts)
{
	char *p;
	int i;

	for (i = 0; arv[i]; i++)
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
				p++;
			}
		}
	}
	return (ar_opts);
}
