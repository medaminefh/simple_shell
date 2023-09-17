#include "main.h"

/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
	size_t a = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * list_len - determines length of linked list
 * @oldhead: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *oldhead)
{
	size_t len = 0;

	while (oldhead)
	{
		oldhead = oldhead->next;
		len++;
	}
	return (len);
}

/**
 * list_to_str - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_str(list_t *head)
{
	list_t *node = head;
	size_t b = list_len(head), a;
	char **strs;
	char *str;

	if (!head || !b)
		return (NULL);
	strs = malloc(sizeof(char *) * (b + 1));
	if (!strs)
		return (NULL);
	for (b = 0; node; node = node->next, b++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (a = 0; a < b; a++)
				free(strs[a]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[b] = str;
	}
	strs[b] = NULL;
	return (strs);
}




/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @pref: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *pref, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, pref);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
