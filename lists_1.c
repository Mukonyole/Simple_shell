#include "shell.h"

/**
 * list_len - determine length of linked list
 * @h: pointer to first node
 * Return: list size
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - finds corresponding array member of each node
 * @head: pointer to 1st node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(str[b]);
			free(str);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		/* copy str from nodes string */
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}

/**
 * print_list - prints content of linked list
 * @h: pointer to first node
 * Return: list size
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		/* iterates thru list printing node members */
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
	/* size of list */
}

/**
 * node_starts_with - returns node starting with prefix
 * @node: list head pointer
 * @prefix: string to compare
 * @b: next char after prefix
 * Return: matching node/null
 */
list_t *node_starts_with(list_t *node, char *prefix, char b)
{
	char *pointer = NULL;

	while (node)
	{
		pointer = starts_with(node->str, prefix);
		if (pointer && ((b == -1) || (*pointer == b)))
			return (node);
		/* if node match */
		node = node->next;
	}
	return (NULL);
	/* no node match */
}

/**
 * get_node_index - gets index of node
 * @head: list header pointer
 * @node: node pointer
 * Return: index of node, -1 not found
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
