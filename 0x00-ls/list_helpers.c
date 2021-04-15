#include "ls.h"

void list_init(ls_c *list, void (*destroy)(void *name)) {
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->last_in = NULL;
	list->tail = NULL;

	return;
}

void list_destroy(ls_c *list)
{
	void *data;

	while (list_size(list) > 0)
		list_rem_next(list, NULL, (void **)&data);
	free(list->head);

	return;
}

int list_ins_next(ls_c *list, ls_n *element, const void *name)
{
	ls_n *new;

	new = (ls_n *) malloc(sizeof(ls_n));
	if (new == NULL)
		return (-1);
	new->name = (void *) name;

	if (element == NULL) {
		if (list_size(list) == 0)
			list->tail = new;
		new->next = list->head;
		list->head = new;
	}
	else {
		if (element->next == NULL)
			list->tail = new;
		new->next = element->next;
		element->next = new;
	}

	list->last_in = new;
	list->size++;
	
	return (0);
}

int list_rem_next(ls_c *list, ls_n *element, void **name)
{
	ls_n *old;

	if (list_size(list) == 0)
		return (-1);

	if (element == NULL) {
		*name = list->head->name;
		old = list->head;
		list->head = list->head->next;
	}
	else {
		if (element->next == NULL)
			return (-1);

		*name = element->next->name;
		old = element->next;
		element->next = element->next->next;

		if (element->next == NULL)
			list->tail = element;
	}
	/*free(*name);*/
	free(old);
	list->size--;
	return (0);
}

void print_list_safe(ls_c *list, ls_n *head, int ncase)
{
	int i = 0, size = 0;
	ls_n *cp = head;

	size = list_size(list);
	if (size == 0)
		return;
	
	while(i < size) {
		if (ncase == 0) {
			if (_strncmp(cp->name, ".", 1) == 0) {
				cp = cp->next, i++;
				continue;
			}
		}
		write(1, cp->name, _strlen(cp->name));
		if (i + 1 == size)
			write(1, "\n", 1);
		else
			write(1, "  ", 2);
		cp = cp->next;
		i++;
	}
	return;
}

