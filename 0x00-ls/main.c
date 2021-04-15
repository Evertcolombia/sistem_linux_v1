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
		exit(EXIT_FAILURE);
	if (argc == 1)
		listFiles(".");
	exit(EXIT_SUCCESS);
}
