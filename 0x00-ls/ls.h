#ifndef _LS_H_
#define _LS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>

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
void print_list_safe(ls_c *list, ls_n *head, int ncase);

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

/* core prototypes */
void listFiles(const char *dirpath);


/* other helpers*/
char *allocBuf(char *dest, char *path, char *name);
#endif /* _LS_H_ */