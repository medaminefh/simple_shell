#include "main.h"

/**
 * add_node - adds a node to the start of the list
 * @oldhead: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **oldhead, const char *str, int num)
{
	list_t *newhead;

	if (!oldhead)
		return (NULL);
	newhead = malloc(sizeof(list_t));
	if (!newhead)
		return (NULL);
	_memset((void *)newhead, 0, sizeof(list_t));
	newhead->num = num;
	if (str)
	{
		newhead->str = _strdup(str);
		if (!newhead->str)
		{
			free(newhead);
			return (NULL);
		}
	}
	newhead->next = *oldhead;
	*oldhead = newhead;
	return (newhead);
}

/**
 * add_node_end - adds a node to the end of the list
 * @oldhead: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **oldhead, const char *str, int num)
{
	list_t *newnode, *node;

	if (!oldhead)
		return (NULL);

	node = *oldhead;
	newnode = malloc(sizeof(list_t));
	if (!newnode)
		return (NULL);
	_memset((void *)newnode, 0, sizeof(list_t));
	newnode->num = num;
	if (str)
	{
		newnode->str = _strdup(str);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newnode;
	}
	else
		*oldhead = newnode;
	return (newnode);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *head)
{
	size_t a = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * delete_node - deletes node at given index
 * @oldhead: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node(list_t **oldhead, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!oldhead || !*oldhead)
		return (0);

	if (!index)
	{
		node = *oldhead;
		*oldhead = (*oldhead)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *oldhead;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @headptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **headptr)
{
	list_t *node, *nextnode, *head;

	if (!headptr || !*headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		nextnode = node->next;
		free(node->str);
		free(node);
		node = nextnode;
	}
	*headptr = NULL;
}
