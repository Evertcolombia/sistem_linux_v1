#ifndef _LS_H_
#define _LS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <stdio.h>
#include <errno.h>

/**
 * struct flags_opts - flags struct
 *
 * @fa: int to flag a
 * @f1: int to flag 1
 * @pcount: conunt of flags
 */
typedef struct flags_opts
{
	int fa;
	int f1;
	int count;
} _opts;

/* arguments mannager prototypes */
_opts *arv_mannager(char *arv[], _opts *ar_opts);

/**
 * struct ls_node  - our struct
 *
 * @name: name of the file / dir
 * @next: ponter to next node
 *
 */
typedef struct ls_node
{
	char *name;
	struct ls_node *next;
} ls_n;

/**
 * struct ls_control  - our struct
 *
 * @size: size of l list
 * @match: pointer to function
 * @destroy: pointer to func
 * @head: ehad of l list
 * @last_in: last node inserted
 * @tail: tail of list
 */
typedef struct ls_control
{
	int size;

	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *name);

	ls_n *head;
	ls_n *last_in;
	ls_n *tail;
} ls_c;

/*prototypes for control of the linked list an macros*/
void list_init(ls_c *list, void (*destroy)(void *name));
void list_destroy(ls_c *list);
int list_ins_next(ls_c *list, ls_n *element, const void *name);
int list_rem_next(ls_c *list, ls_n *element, void **name);
void print_list_safe(ls_c *list, ls_n *head, _opts *opts);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_name(element) ((element)->name)
#define list_next(element) ((element)->next)

/* file stat prototypes */
char *filePermStr(mode_t perm);
char fileTypeStr(mode_t type);
char *getLastModTime(time_t mtime);

/* string helpers prototypes */
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
int _strncmp(char *s1, char *s2, int n);
char *_strstr(char *haystack, char *needle);

/* core prototypes */
void listFiles(const char *dirpath, int argc, _opts *ar_opts);
int statinfo(const char *pathname, char *name, ls_c *list, bool isFree);
DIR *open_directory(DIR *dirp, char *path, ls_c *list);
void print_safe(int arc, ls_c *list,  char *copy, _opts *_opts);

/* other helpers*/
char *allocBuf(char *dest, char *path, char *name, char *com);
void error_mannager(int errid, bool isDir, char *path, ls_c *list);
int print_vertical(int size, ls_n *head);
int print_horizontal(int size, ls_n *head);

/* Flags helpers */
int get_no_flags(char *name, char *path, ls_c *list);
int pass_hidden(char *name);
char *path_controller(char *path, char *name);
int get_flags(char *name, char *path, ls_c *list, _opts *_opst);
#endif /* _LS_H_ */
