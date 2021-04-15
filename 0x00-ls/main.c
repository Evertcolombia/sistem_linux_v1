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
	if (argc > 1 && _strcmp(argv[1], "--help") == 0)
		return (-2);
	if (argc == 1)
		listFiles(".", argc);
	else
	{
		argv++;
		for (; *argv; argv++)
			listFiles(*argv, argc);
	}

	return (0);
}
