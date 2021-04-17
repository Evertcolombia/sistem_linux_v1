#include "ls.h"

/**
 * list_init - init a l list control struct
 * @list: pointer to struct
 * @destroy: pointer to function
 */
void list_init(ls_c *list, void (*destroy)(void *name))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->last_in = NULL;
	list->tail = NULL;
}

/**
 * list_destroy - destroy list
 * @list: linked list controller
 */
void list_destroy(ls_c *list)
{
	void *data;

	while (list_size(list) > 0)
		list_rem_next(list, NULL, (void **)&data);
	free(list->head);
}

/**
 * list_ins_next - insert node in linked list
 * @list: linked list
 * @element: node
 * @name: element to insert
 *
 * Return: int
 */

int list_ins_next(ls_c *list, ls_n *element, const void *name)
{
	ls_n *new;

	new = (ls_n *) malloc(sizeof(ls_n));
	if (new == NULL)
		return (-1);
	new->name = (void *) name;

	if (element == NULL)
	{
		if (list_size(list) == 0)
			list->tail = new;
		new->next = list->head;
		list->head = new;
	}
	else
	{
		if (element->next == NULL)
			list->tail = new;
		new->next = element->next;
		element->next = new;
	}
	list->last_in = new;
	list->size++;
	return (1);
}

/**
 * list_rem_next - delete element from list
 * @list: linked list
 * @element: element to delete next
 * @name: double pinter
 *
 * Return: int
 */

int list_rem_next(ls_c *list, ls_n *element, void **name)
{
	ls_n *old;

	if (list_size(list) == 0)
		return (-1);

	if (element == NULL)
	{
		*name = list->head->name;
		old = list->head;
		list->head = list->head->next;
	}
	else
	{
		if (element->next == NULL)
			return (-1);

		*name = element->next->name;
		old = element->next;
		element->next = element->next->next;

		if (element->next == NULL)
			list->tail = element;
	}
	free(old);
	list->size--;
	return (0);
}

/**
 * print_list_safe - print linked list
 * @list: list control
 * @head: head of the list
 * @_opts: flags structure
 */
void print_list_safe(ls_c *list, ls_n *head, _opts *_opts)
{
	int size = 0;
	ls_n *cp = head;

	size = list_size(list);
	if (size == 0)
		return;

	if (_opts->count == 0)
		print_horizontal(size, cp);
	else
		print_vertical(size, cp);
}
