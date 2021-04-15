#include "ls.h"

int main(int argc, char *argv[])
{
	if (argc > 1 && _strcmp(argv[1], "--help") == 0)
		return (1);
	if (argc == 1)
		listFiles(".");
	else {
		for (argv++; *argv; argv++)
			listFiles(*argv);
	}
	return (0);
}
