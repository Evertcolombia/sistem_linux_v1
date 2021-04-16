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

	ar_opts.fa = 0, ar_opts.f1 = 0;
	f_ops = &ar_opts;

	if (argc == 1)
		listFiles(".", argc, f_ops);
	else if (argc >= 2)
	{
		f_ops = arv_mannager(argv, f_ops);
		if (argc == 2)
		{
			if (f_ops->fa != 0 || f_ops->f1 != 0)
				listFiles(".", argc, f_ops);
			else
				listFiles(*(++argv), argc, f_ops);
		}
		else {
			argv += 1;
			if (*argv)
			{
				for (; *argv; argv++)
					listFiles(*argv, argc, f_ops);
		
			}
		}
	
	}
	return (0);
}
_opts *arv_mannager(char *arv[], _opts *ar_opts)
{
	char *p;

	if (arv[1][0] == '-' && arv[1][1] != '\0')
	{
		p =  (char*) (arv[1] + 1);
		while(*p)
		{
			if (*p == '1')
				ar_opts->f1 = 1;
			else if(*p == 'a')
				ar_opts->fa = 1;
			else
			{
				perror("unknown flag");
				exit(EXIT_FAILURE);
			}
			p++;
		}
	}
	return(ar_opts);
}
