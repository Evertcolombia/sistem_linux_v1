#ifndef _GETLINE_
#define _GETLINE_

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char *_getline(const int fd);
int get_l(const int fd, char *buf, int count, int count_ch);

#endif /* _GETLINE_ */
